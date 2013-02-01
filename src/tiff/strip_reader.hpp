/*
 * Declaration of class TIFFStripReader
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of class TIFFStripReader.
 *
 * Created on: Jun 22, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "ifd.hpp"
#include "../image_info.hpp"

#include <pni/io/core/types.hpp>
#include <pni/io/core/dbuffer.hpp>

using namespace pni::core;

namespace pni {
namespace io {
namespace tiff {

    //! \ingroup io_classes
    //! \brief reader for strip data in a TIFF file
    class strip_reader 
    {
        private:
            std::vector<size_t> _offsets;   //!< array with the file offsets of the strips
            std::vector<size_t> _byte_cnts; //!< array with byte counts for each strip
            std::vector<size_t> _bits_per_channel; //!< number of bits per channel
            std::vector<type_id_t> _channel_types; //!< type ids of channel data

            /*! \brief template to read interlace data 

            This template method reads image data distributed over several
            strips.  The first template parameter determines the type of the
            image data to read while T is the type of the target array. The
            remaining template parameters belong to the array itself and are not
            of importance here.
            \tparam IT data type used in the image file
            \tparam CTYPE container type where the data shoule be stored
            \param c number of the channel to read
            \param stream input stream from which to read data
            \param data target container where to store the data
            */
            template<typename IT,typename CTYPE> 
                void _read_interlace(size_t c,std::ifstream &stream,
                                     CTYPE &data) const;

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
            /*! 
            \brief standard constructor

            Standard constructor for this class. 
            \param offsets vector with strip offsets
            \param byte_counts vector with byte counts for every strip
            \param bits_per_channel vector with number of pits per channel
            \param channel_types vector with TypeIDs for each channel
            */
            strip_reader(const std::vector<size_t> &offsets,
                         const std::vector<size_t> &byte_counts,
                         const std::vector<size_t> &bits_per_channel,
                         const std::vector<type_id_t> &channel_types);

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
            /*! \brief create StripReader instance

            This static factory method creates a StripReader object from the IFD
            of an image and its ImageInfo structure. 
            \param stream input stream from which to read data
            \param ifd IFD of the image for which the reader should be created
            \param info ImageInfo object for the image
            \return instance of type StripReader
            */
            static strip_reader create(std::ifstream &stream,
                                       const ifd &image_dir,
                                       const image_info &info);

            //=====================public member methods========================
            /*! 
            \brief template to read image data of various type

            Template method to read image data stored as strips from a file. The
            template parameter determines the type of the output array. The
            method assumes that the shape of the array is already set properly.
            \throws type_error if the image data type is unkown
            \param c number of the channel to read
            \param stream input stream from which to read data
            \param data reference to the container where to store the data
            */
            template<typename CTYPE> 
                void read(size_t c,std::ifstream &stream,CTYPE &data) 
            {

                //first we need to determine the datatype of the

                if(this->_channel_types[c] == type_id_t::UINT8)
                    this->_read_interlace<uint8>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::INT8)
                    this->_read_interlace<int8>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::UINT16)
                    this->_read_interlace<uint16>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::INT16)
                    this->_read_interlace<int16>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::UINT32)
                    this->_read_interlace<uint32>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::INT32)
                    this->_read_interlace<int32>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::UINT64)
                    this->_read_interlace<uint64>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::INT64)
                    this->_read_interlace<int64>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::FLOAT32)
                    this->_read_interlace<float32>(c,stream,data);
                else if(this->_channel_types[c] == type_id_t::FLOAT64)
                    this->_read_interlace<float64>(c,stream,data);
                else
                    throw type_error(EXCEPTION_RECORD,
                          "StripReader cannot handle channel type!");
            }

            //=====================output operator==============================
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const strip_reader &r);
        };

    //-------------------------------------------------------------------------
    template<typename IT,typename CTYPE> 
        void strip_reader::_read_interlace(size_t channel,
                std::ifstream &stream,CTYPE &data) const
    {
        //we can assume here that the buffer is already properly allocated
        size_t tot_bits_per_pix = std::accumulate(this->_bits_per_channel.begin(),
                                                  this->_bits_per_channel.end(),0);

        typename CTYPE::iterator piter = data.begin(); //pixel iterator
        while(piter != data.end())
        {
            //loop over all strips
            for(size_t strip=0;strip<this->_offsets.size();strip++)
            {
                //set stream to the starting position of the strip
                stream.seekg(this->_offsets[strip],std::ios::beg);

                //create strip buffer
                dbuffer<char> strip_buffer(this->_byte_cnts[strip]);

                //read strip data to the buffer
                stream.read(const_cast<char *>(strip_buffer.ptr()),strip_buffer.size());

                //now as we have all the strip data in the memory we need to select
                //the proper channel data from it

                //compute the number of pixels in the strip
                size_t npix = (8*this->_byte_cnts[strip])/tot_bits_per_pix;
                //loop over all pixels
                char *ptr = const_cast<char *>(strip_buffer.ptr());

                //loop over all pixels in the strip
                for(size_t i=0;i<npix;i++)
                {
                    //loop over all channels
                    for(size_t c=0;c<this->_bits_per_channel.size();c++)
                    {
                        //extract data from the stream
                        if(c==channel) 
                            *piter++ =  typename CTYPE::value_type(IT(*ptr));

                        //continue with the pointer
                        ptr += this->_bits_per_channel[c]/8;
                    }
                }
            }
        }
    }


//end of namespace
}
}
}
