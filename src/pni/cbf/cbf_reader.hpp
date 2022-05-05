//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Apr 19, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<cstdlib>
#include<vector>

#include<boost/regex.hpp>

#include <pni/types.hpp>

#include <pni/image_reader.hpp>
#include <pni/cbf/dectris_reader.hpp>
#include <pni/cbf/types.hpp>
#include <pni/windows.hpp>

namespace pni{


//!
//! \ingroup image_io_cbf
//! \brief base clase for CBF readers
//!
//! CBFReader is the base class for all readers of data stored in binary
//! CIF format.  Although CBF is standardized by the ICUR the guys from
//! Dectris (the vendor of the Pilatus detector) use a kind of dialect
//! which must be treated in a slightly different way.  The field
//! _header_convention in the class indicates whether or not the header is
//! in standard CBF format or in the Dectris dialect.
//!
//! Reading a CBF file is a two step process:
//! - the header is read and the information stored there kept in in a
//! CIFBinaryHeader object
//! - the binary data is read from the stream using a CBFBinStreamReader
//! object
//! The header information contains enough information to decide which
//! binary reader to use and to construct the data objects which will
//! hold the data read from the file.  From such a point of view the
//! header object can be consideres as a factory for the binary
//! readers and the array objects holding the data.
//!
class PNINEXUS_EXPORT cbf_reader: public image_reader
{
  private:
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
    //! string holding the detector vendor ID
    cbf::vendor_id _detector_vendor;
    //! info structure for data
    std::vector<image_info> _image_info;
    //! store data offset
    std::streampos _data_offset;
    //! compression type
    cbf::compression_id _compression_type;
#ifdef _MSC_VER
#pragma warning(default:4251)
#endif
    //-----------------------------------------------------------------
    //!
    //! @brief parse the file
    //!
    //! Parse the file and setup member variables of the class.
    //!
    void _parse_file();

  public:
    //=================constructors and destructor==================
    //!
    //! @brief default constructor
    //!
    cbf_reader();

    //-----------------------------------------------------------------
    //!
    //! @brief construct reader object
    //!
    //! The name of the CBFFile is passed as a String object. During
    //! instantiation of class the file is parsed. Throws an
    //! exception if the flavor of the CBF file cannot be deduced
    //! from the header.
    //! @throw file_error if the CBF flavor cannot be deduced
    //! @param fname name of the file
    //!
    cbf_reader(const pni::string &fname);

    //-----------------------------------------------------------------
    //! destructor
    virtual ~cbf_reader();

    //-----------------------------------------------------------------
    //! the copy constructor is deleted
    cbf_reader(const cbf_reader &r) = delete;

    //! the copy assignment operator is deleted
    cbf_reader &operator=(const cbf_reader &r) = delete;

    //====================assignment operators=======================
    //!
    //! @brief move assignment
    //!
    //! Use compiler provided default implementation here
    //!
    cbf_reader &operator=(cbf_reader &&r) = default;


    virtual void close();

    virtual void open();

    virtual size_t nimages() const;

    virtual image_info info(size_t i) const;

    //-----------------------------------------------------------------
    //!
    //! @brief read image
    //!
    //! @tparam ContainerT container type for storing data
    //!
    //! @throw memory_allocation_error if container allocation failes
    //! @throw file_error in case of IO errors
    //!
    //! @param i image number to read
    //! @param c channel to read (default = 0)
    //!
    //! @return instance of ContainerT with image data
    //!
    template<typename ContainerT> ContainerT image(size_t i,size_t c=0);

    //-----------------------------------------------------------------
    //!
    //! @brief read data from detector file
    //!
    //! Reads a single image from a detector file and stores it in an
    //! container of type ContainerT.
    //!
    //! @throws file_error if case of IO errors
    //! @throws size_mismatch_error if container and image size do not match
    //!
    //! @tparam ContainerT container type holding the image data
    //! @param array instance of ContainerT where data will be stored
    //!
    //! @param i image number
    //! @param c channel number
    //!
    template<typename ContainerT>
    void image(ContainerT &array,size_t i,size_t c=0);

};

//-------------------------------------------------------------------------
template<typename ContainerT> ContainerT cbf_reader::image(size_t i,size_t c)
{
  using namespace pni;
  image_info info = _image_info[i];
  ContainerT data;
  try
  {
    data=ContainerT(info.npixels());
  }
  catch(...)
  {
    throw memory_allocation_error(PNINEXUS_EXCEPTION_RECORD,
                                  "Allocation of container for image data failed!");
  }

  try
  {
    image(data,i,c);
  }
  catch(file_error &error)
  {
    //propagate exception
    error.append(PNINEXUS_EXCEPTION_RECORD);
    throw error;
  }

  return data;
}

//-------------------------------------------------------------------------
template<typename ContainerT>
void cbf_reader::image(ContainerT &data,size_t i,size_t c)
{
  using namespace pni;
  //load image information and throw exception if image and container size
  //to not match
  image_info inf = _image_info[i];
  if(data.size()!= inf.npixels())
  {
    std::stringstream ss;
    ss<<"Container size ("<<data.size()<<") does not match image ";
    ss<<"size ("<<inf.npixels()<<")!";
    throw size_mismatch_error(PNINEXUS_EXCEPTION_RECORD,ss.str());
  }

  //load the channel information
  image_channel_info channel = inf.get_channel(c);

  if(_detector_vendor == cbf::vendor_id::Dectris)
  {
    if(channel.type_id() == type_id_t::Int16)
      //read 16Bit signed data
      cbf::dectris_reader::read_data_byte_offset<int16>(
          _get_stream(),inf,data);
    if(channel.type_id() == type_id_t::Int32)
      //read 32Bit signed data
      cbf::dectris_reader::read_data_byte_offset<int32>(
          _get_stream(),inf,data);
    else
    {
      file_error error(PNINEXUS_EXCEPTION_RECORD,
                       "No data reader for this data type!");
      throw error;
    }

  }
  else
    throw file_error(PNINEXUS_EXCEPTION_RECORD,"Unknown detector vendor!");

}
//end of namespace
}

