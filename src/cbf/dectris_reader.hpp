/*
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
 * DectrisCBFReader class definition
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#pragma once

#include<iostream>
#include<fstream>
#include<vector>

#include "../image_info.hpp"
#include "types.hpp"

using namespace pni::core;

namespace pni{
namespace io{
namespace cbf{
    
    /*! 
    \ingroup io_classes
    \brief reader for DECTRIS detector data

    This type provides static method to read data from CBF files written by
    detectors from DECTRIS. 
    */
    class dectris_reader
    {
        public:
            /*! \brief read header information

            This static method reads the header data from a CBF file. The header
            information is collected and stored in an ImageInfo type. In
            addition the ct argument holds the ID of the compression use for
            this image.
            \param is input stream from which to read
            \param info ImageInfo vector where to store image data
            \param ct compression id 
            \return position of data section
            */
            static std::streampos read_header(std::ifstream &is,
                    std::vector<pni::io::image_info> &info,compression_id &ct);

            //-----------------------------------------------------------------
            /*! \brief read data 

            Static method to read byte offset compressed data from DECTRIS CBF
            files. 
            \tparam CBFT type used for data in the file
            \tparam CTYPE container type where to store the data
            \param is input stream
            \param info instance of ImageInfo for the image to read
            \param data container instance where to store the data
            */
            template<typename CBFT,typename CTYPE>
                static void read_data_byte_offset(
                        std::ifstream &is,
                        const pni::io::image_info &info,
                        CTYPE &data);


    };

    //-------------------------------------------------------------------------
    template<typename CBFT,typename CTYPE>
        void dectris_reader::read_data_byte_offset( std::ifstream &is,
                const pni::io::image_info &info, CTYPE &data)
    {

        //unsigned long i;
        size_t ecnt = 0; // element counter
        CBFT buffer = 0; // single element buffer

        //initializing the container with 0
        std::fill(data.begin(),data.end(),0);
        typename CTYPE::iterator iter = data.begin();
        typename CTYPE::value_type v_old = 0;

#ifdef NOFOREACH
        for(auto iter = data.begin();iter!=data.end();++iter)
        {
            typename CTYPE::value_type &v = *iter;
#else
        for(typename CTYPE::value_type &v: data)
        {
#endif
            v = v_old; //set the new value to the previous

            buffer = 0; //reset the read buffer
            //read one byte from the stream an throw an exception in case of an
            //error
            try { is.read((char *)(&buffer),1); }
            catch(...)
            {
                throw file_error(EXCEPTION_RECORD,
                        "Error reading 1Byte from the CBF stream!");
            }

            if (((unsigned char) buffer) != 0x80)
            {
                v += (char) buffer;
                v_old = v;
                continue;
            }
          
            //read two byte from the stream and throw an exception in case of an
            //error
            try { is.read((char *) (&buffer), 2); }
            catch(...)
            {
                throw file_error(EXCEPTION_RECORD,
                        "Error reading 2Byte from the CBF stream!");
            }

            if (((unsigned short) buffer) != 0x8000) 
            {
                v += (short) buffer;
                v_old = v;
                continue;
            }

            //read 4 byte from the stream and throw an exception in the case of
            //an error
            try { is.read((char*) (&buffer), 4); }
            catch(...)
            {
                throw file_error(EXCEPTION_RECORD,
                        "Error reading 4byte from the CBF stream!");
            }

            if (((unsigned int) buffer) != 0x800000) 
            {
                v += (int) buffer;
                v_old = v;
                continue;
            }

        }

    }

//end of namespace
}
}
}
