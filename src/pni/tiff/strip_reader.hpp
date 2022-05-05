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
// Created on: Jun 22, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include <pni/tiff/ifd.hpp>
#include <pni/image_info.hpp>

#include <pni/types.hpp>
#include <pni/arrays.hpp>

#include <pni/windows.hpp>


namespace pni {
namespace tiff {    

    //! \ingroup image_io_tiff
    //! \brief reader for strip data in a TIFF file
    class PNINEXUS_EXPORT strip_reader 
    {
        private:
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
            std::vector<size_t> _offsets;   //!< array with the file offsets of the strips
            std::vector<size_t> _byte_cnts; //!< array with byte counts for each strip
            std::vector<size_t> _bits_per_channel; //!< number of bits per channel
            std::vector<pni::type_id_t> _channel_types; //!< type ids of channel data
#ifdef _MSC_VER
#pragma warning(default:4251)
#endif

            //-----------------------------------------------------------------
            //!
            //! \brief template to read interlace data 
            //!
            //! This template method reads image data distributed over 
            //! several strips.  The first template parameter determines 
            //! the type of the image data to read while T is the type of the 
            //! target array. The remaining template parameters belong to the 
            //! array itself and are not of importance here.
            //!
            //! \tparam IT data type used in the image file
            //! \tparam ContainerT container type where the data shoule be stored
            //! \param c number of the channel to read
            //! \param stream input stream from which to read data
            //! \param data target container where to store the data
            //!
            template<
                     typename BufferT,
                     typename ContainerT
                    > 
            void _read_interlace(size_t c,std::ifstream &stream,
                                 ContainerT &data) const;

        public:
            //====================constructors and destructor==================
            //! default constructor
            strip_reader();

            //-----------------------------------------------------------------
            //! copy constructor
            strip_reader(const strip_reader &r);

            //-----------------------------------------------------------------
            //! move constructor
            strip_reader(strip_reader &&r);

            //-----------------------------------------------------------------
            //!
            //! \brief standard constructor
            //!
            //! Standard constructor for this class. 
            //!
            //! \param offsets vector with strip offsets
            //! \param byte_counts vector with byte counts for every strip
            //! \param bits_per_channel vector with number of pits per channel
            //! \param channel_types vector with TypeIDs for each channel
            //!
            strip_reader(const std::vector<size_t> &offsets,
                         const std::vector<size_t> &byte_counts,
                         const std::vector<size_t> &bits_per_channel,
                         const std::vector<pni::type_id_t> &channel_types);

            //------------------------------------------------------------------
            //! destructor
            ~strip_reader();

            //====================assignemnt operators==========================
            //! copy assignment operator
            strip_reader &operator=(const strip_reader &r);

            //------------------------------------------------------------------
            //! move assignment operator
            strip_reader &operator=(strip_reader &&r);

            //===========static public member functions=========================
            //!
            //! \brief create StripReader instance
            //!
            //! This static factory method creates a StripReader object from 
            //! the IFD of an image and its ImageInfo structure. 
            //!
            //! \param stream input stream from which to read data
            //! \param image_dir IFD of the image for which the reader should 
            //! be created
            //! \param info ImageInfo object for the image
            //! \return instance of type StripReader
            //!
            static strip_reader create(std::ifstream &stream,
                                       const ifd &image_dir,
                                       const image_info &info);

            //=====================public member methods========================
            //! 
            //! \brief template to read image data of various type
            //!
            //! Template method to read image data stored as strips from a 
            //! file. The template parameter determines the type of the output 
            //! array. The method assumes that the shape of the array is 
            //! already set properly.
            //!
            //! \throws type_error if the image data type is unkown
            //! \param c number of the channel to read
            //! \param stream input stream from which to read data
            //! \param data reference to the container where to store the data
            //!
            template<typename ContainerT> 
                void read(size_t c,std::ifstream &stream,ContainerT &data) 
            {
                using namespace pni;
                //first we need to determine the datatype of the

                if(this->_channel_types[c] == type_id_t::UInt8)
                    this->_read_interlace<uint8>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::Int8)
                    this->_read_interlace<int8>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::UInt16)
                    this->_read_interlace<uint16>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::Int16)
                    this->_read_interlace<int16>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::UInt32)
                    this->_read_interlace<uint32>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::Int32)
                    this->_read_interlace<int32>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::UInt64)
                    this->_read_interlace<uint64>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::Int64)
                    this->_read_interlace<int64>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::Float32)
                    this->_read_interlace<float32>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::Float64)
                    this->_read_interlace<float64>(c,stream,data);
                else
                    throw type_error(PNINEXUS_EXCEPTION_RECORD,
                          "StripReader cannot handle channel type!");
            }

            //=====================output operator==============================
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const strip_reader &r);
        };

    //-------------------------------------------------------------------------
    template<typename BufferT,typename ContainerT> 
        void strip_reader::_read_interlace(size_t channel,
                std::ifstream &stream,ContainerT &data) const
    {
        typedef typename ContainerT::value_type value_type;
        //compute the size of a pixel in bytes
        size_t pixel_size = std::accumulate(_bits_per_channel.begin(),
                                            _bits_per_channel.end(),0)/8;
       
        //compute the offset from the begining of a pixel to the requested
        //sample. The offset is given in bytes
        size_t sample_offset = std::accumulate(_bits_per_channel.begin(),
                                               _bits_per_channel.begin()+channel,
                                               0)/8;

        //size of the sample type
        size_t sample_size = sizeof(BufferT);

        BufferT sample_buffer; 

        typename ContainerT::iterator piter = data.begin(); //pixel iterator
        while(piter != data.end())
        {
            //loop over all strips
            for(size_t strip=0;strip<_offsets.size();strip++)
            {
                size_t npixels = _byte_cnts[strip]/pixel_size;

                //set the stream to the offset of the actual strip
                stream.seekg(_offsets[strip]+sample_offset,std::ios::beg);

                //loop over all pixels in the strip
                for(size_t i=0;i<npixels; ++i)
                {
                    stream.read(reinterpret_cast<char*>(&sample_buffer),sample_size);
                    stream.seekg(pixel_size-sample_size,std::ios::cur);
                    *piter++ = value_type(sample_buffer);
                }
            }
        }
    }


//end of namespace
}
}
