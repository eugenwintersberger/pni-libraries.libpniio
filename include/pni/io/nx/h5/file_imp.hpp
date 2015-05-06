//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
//
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

extern "C"{
#include <hdf5.h>
}

#include "object_imp.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{    

    //forward declaration of group implemenation
    class group_imp;
            
    //! 
    //! \ingroup nxh5_classes
    //! \brief HDF5 file implementation
    //!
    //! An HDF5 file behaves in nearly all aspects like a group object.  It 
    //! can be considered as the root group for all other groups or the root 
    //! of a filesystem on a UNIX system. File objects are created by using 
    //! static methods for creating and opening files on the filesystem.
    //!
    class file_imp
    {
        private:
            //! the HDF5 object
            object_imp _object;
        public:
            //===============constructors and destructors======================
            //!
            //! \brief default constructor
            //! 
            explicit file_imp() noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief object constructor
            //! 
            //! \throws type_error in cases where the object is not a file
            //! object
            //! \throws invalid_object_error if the passed object is not valid
            //! \throws object_error in any other case of failure
            //!
            //! \param o rvalue reference to an object instance
            //! 
            explicit file_imp(object_imp &&o);

            //=====================factory methods=============================
            //! 
            //! \brief open an existing file
            //! 
            //! Static method to open an exing file. Using the ro flag one can 
            //! open the file either for read/write or for read-only acess.
            //! 
            //! \throws file_error if the file is not an HDF5 file
            //! \throws object_error in case of any object creation error
            //! \throws invalid_object_error if the file object opened is not
            //! valid
            //!
            //! \param n name of the file
            //! \param ro if true file will be in read only mode
            //! \return instance of file_imp
            //! 
            static file_imp open(const pni::core::string &n,bool ro=true);

            //-----------------------------------------------------------------
            //! 
            //! \brief create a new file
            //! 
            //! Creates a new file on the filesystem. By default this method 
            //! fails if a file of identical name already exists. However, if 
            //! setting the overwrite flag ow to true the existing file will 
            //! be overwriten and all data in this file is lost. In addition 
            //! files can be split into smaller portions. The split size can 
            //! be set with ssize.
            //!
            //! \throws object_error in case of object creation fails
            //! \throws invalid_object_error if the created file is not valid
            //!
            //! \param path the path to the file to create
            //! \param ow overwrite existing file if true
            //! \param ssize split size
            //! \return instance of H5File
            //!
            static file_imp create(const pni::core::string &path,bool ow=false,
                                   ssize_t ssize=0);

            //====================misc methods=================================
            //!
            //! \brief close the file
            //! 
            //! \throws object_error if something goes wrong
            //! \throws type_error if the object type could not be determined
            //!
            void close();

            //-----------------------------------------------------------------
            //!
            //! \brief flush the file
            //!
            //! \throws io_error if flush fails
            //! \throws object_error if validity status could not be determined
            //!
            void flush() const;

            //-----------------------------------------------------------------
            //!
            //! \brief return true if file is read-only
            //!
            //! \throws invalid_object_error if file is not valid
            //! \throws file_error if file intent cannot be retrieved
            //! \throws object_error in case of any other error
            //!
            //! \return true if readonly, false otherwise
            //!
            bool is_readonly() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief check object validity
            //! 
            //! \throws object_error if the validity of the object could not
            //! be determined
            //! 
            //! \return true if file valid, false otherwise
            //!
            bool is_valid() const;

            //----------------------------------------------------------------
            //!
            //! \brief get root
            //! 
            //! Return the root group of the file. 
            //! 
            //! \throws invalid_object_error if file is not valid
            //! \throws type_error if group type cannot be determined
            //! \throws object_error in case of any other error
            //! 
            //! \return root group instance
            //!
            group_imp root() const;


    };


//end of namespace
}
}
}
}
