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
// Created on: Jun 16, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <memory>
#include <vector>
#include <fstream>
#include <iostream>

#include <pni/core/types.hpp>

#include "ifd_entry.hpp"

namespace pni{
namespace io{
namespace tiff{


    //! 
    //! \ingroup image_io_tiff
    //! \brief IFD - Image File Directory class
    //!
    //! This class describes an Image File Directory (IFD) block in a TIFF 
    //! file.  Each IFD is associated with a single image. An IFD can be 
    //! considered as a container for IFD entries. Each of this entries has a 
    //! particular type and one or several values of this type. The entries 
    //! can be obtained using the [] operator in two different fashions: once 
    //! with in integer argument representing the index of the entry in the 
    //! IFD or with a string giving the name of the entry (if the entry is 
    //! according to the standard).  The TIFF specification defines a group 
    //! of standard entries with defines names. 
    //!
    //! The IFD class behaves like a C++ container providing iterators to 
    //! run over all entries stored in the IFD.  
    //!
    class ifd 
    {
        protected:
            std::vector<ifd_entry> _entries; //!< list of IFD entries
        public:
            //===============public data types=================================
            //some data types that can be useful for IFDs
            //! iterator over IDF entries in IDFList
            typedef std::vector<ifd_entry>::iterator       iterator;       
            //! const. iterator over IDF entries in IDF List
            typedef std::vector<ifd_entry>::const_iterator const_iterator; 

            //==================constructors and destructor====================
            //! default constructor
            ifd();

            //-----------------------------------------------------------------
            //! copy constructor
            ifd(const ifd &o);

            //-----------------------------------------------------------------
            //!
            //! \brief standard constructor
            //!
            //! This constructor assumes that the stream points to the first 
            //! element of the IFD which must hold the number of entries. 
            //! Once construction is finished the stream will point to the 
            //! offset of the next IFD.  The calling programm can immediately 
            //! read the offset and proceed with the next IFD.
            //!
            //! \param size number of elements in the entry
            //!
            explicit ifd(size_t size);

            //-----------------------------------------------------------------
            //! move constructor
            ifd(ifd &&o);

            //-----------------------------------------------------------------
            //! destructor
            ~ifd();

            //===================assignment operator===========================
            //! copy assignment operator
            ifd &operator = (const ifd &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            ifd &operator = (ifd &&o);

            //====================public member methods========================
            //!
            //! \brief get number of IFD entries
            //!
            //! Returns the number of entries stored in the IFD. 
            //! \return number of IFDs
            //!
            size_t size() const { return _entries.size(); }

            //-----------------------------------------------------------------
            //!
            //! \brief operator to obtain an entry by index
            //!
            //! This woks for all entries stored in the IFD also for those
            //! not defined by the TIFF specification. If the index requested
            //! exceeds the number of entries stored in the IFD an exception
            //! will be raised.
            //!
            //! \param i unsigned integer with the index of the entry
            //! \return smart pointer to an IFDAbstractEntry object
            //!
            ifd_entry operator[](size_t i) const;

            //-----------------------------------------------------------------
            //! 
            //! \brief operator to obtain an entry by its name
            //!
            //! This operator works only for entries which are defined in the
            //! TIFF specification. If the requested entry is not available
            //! an exception will be raised.
            //!
            //! \param n a string with the name of the entry
            //! \return smart pointer to an IFDAbstractEntry
            //!
            ifd_entry operator[](const string &n) const;

            //-----------------------------------------------------------------
            //!
            //! \brief get first iterator
            //!
            //! Returns an iterator pointing on the first entry stored in 
            //! the IFD.
            //! \return iterator
            //!
            iterator begin() { return _entries.begin(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get last iterator
            //!
            //! Returns an iterator pointing on the last entry stored in the 
            //! IFD.
            //! \return iterator
            //!
            iterator end()   { return _entries.end(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get const first iterator
            //!
            //! Returns a const iterator to the first entry in the IFD.
            //! \return const iterator
            //!
            const_iterator begin() const { return _entries.begin(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get const last iterator
            //!
            //! Returns a const iterator to the last entry in the IFD.
            //! \return const iterator
            //!
            const_iterator end() const { return _entries.end(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief overloaded ostream operator for standard output
            //!
            //! Thiss operator can be used to dump the content of an IFD to 
            //! standard out.
            //!
            //! \param o output stream
            //! \param image_dir Image directory to print
            //! \return output stream
            //!
            friend std::ostream &operator<<(std::ostream &o,const ifd &image_dir);
    };


//end of namespace
}
}
}
