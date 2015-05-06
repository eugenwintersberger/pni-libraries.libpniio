//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Apr 26, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include<iostream>
#include<fstream>
#include<vector>

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

#include <pni/core/types.hpp>


namespace pni{
namespace io{
namespace tiff{

    //!
    //! \ingroup io_classes
    //! \brief IFD entry reader template
    //!
    //! This template reads IFD entries of a particular type and returns the 
    //! result as a vector of a particular result type. 
    //!
    template<typename RTYPE,typename ETYPE> class ifd_entry_reader
    {
        public:
            //!
            //! \brief read entry data
            //!
            //! This static method reads IFD entry data from a stream. It 
            //! assumes that the stream is already properly positioned at the 
            //! begining of the entries data section. The method does no 
            //! repositioning of the stream once it is finished. This must be 
            //! done by the calling function or method.
            //! \param r number of elements to read
            //! \param stream input stream from which to read data
            //! \return vector of RTYPE values holding the result
            //!
            static void read(std::vector<RTYPE> &r,std::ifstream &stream);
    };

    //-------------------------------------------------------------------------
    template<typename RTYPE,typename ETYPE> void ifd_entry_reader<RTYPE,ETYPE>::
        read(std::vector<RTYPE> &r,std::ifstream &stream)
    {

        ETYPE buffer;

        //check size of entire entry data
        if(sizeof(ETYPE)*r.size()>4){
            //if the data does not fit into 4 Byte we interpret data as an
            //offset and move the stream pointer to this new position
            pni::core::int32 offset;
            stream.read((char *)(&offset),4);
            stream.seekg(offset,std::ios::beg);
        }

        //read the data
        for(RTYPE &value: r)
        {
            stream.read((char*)(&buffer),sizeof(ETYPE));
            value = (RTYPE)(buffer);
        }

    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup io_classes
    //! \brief IFD entry reader specialization for strings
    //!
    //! If the entry data is of type ASCII a special reader is required which 
    //! is provided by this partial specialization of the IFDEntryReader 
    //! template.
    //!
    template<> class ifd_entry_reader<pni::core::string,pni::core::string>
    {
        public:
            //! read string entry 
            static void read(std::vector<pni::core::string> &r,std::ifstream &stream);
    };



//end of namespace 
}
}
}




