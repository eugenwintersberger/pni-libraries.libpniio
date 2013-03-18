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
 * Declaration of a HDF5 File object.
 *
 * Created on: Jan 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

extern "C"{
#include <hdf5.h>
}

#include "H5Group.hpp"
namespace pni{
namespace io{
namespace nx{
namespace h5{
            
    /*! 
    \ingroup nxh5_classes
    \brief HDF5 file class

    An HDF5 file behaves in nearly all aspects like a group object.  It can be
    considered as the root group for all other groups or the root of a
    filesystem on a UNIX system. File objects are created by using static
    methods for creating and opening files on the filesystem.
    */
    class H5File:public H5Group 
    {
        protected:
            //! constructor from id value
            explicit H5File(hid_t id);
        public:
            //===============constructors and destructors======================
            //! default constructor
            explicit H5File();

            //-----------------------------------------------------------------
            //! copy construction
            H5File(const H5File &f);

            //-----------------------------------------------------------------
            //! move constructor
            H5File(H5File &&o);

            //-----------------------------------------------------------------
            //! destructor
            ~H5File();

            //=====================assignment operators========================
            //! move assignment
            H5File &operator=(H5File &&o);

            //-----------------------------------------------------------------
            //! copy assignment
            H5File &operator=(const H5File &o);
       
            //=====================factory methods=============================
            /*! 
            \brief open an existing file
            
            Static method to open an exing file. Using the ro flag one can open
            the file either for read/write or for read-only acess.
            \throws pni::io::nx::nxfile_error if the file is not an HDF5 file or an error
            occured during opening the file.
            \throws pni::io::nx::nxbackend_error if an error occurs during property list
            creation
            \param n name of the file
            \param ro if true file will be in read only mode
            \return instance of H5File
            */
            static H5File open_file(const string &n,bool ro=true);

            //-----------------------------------------------------------------
            /*! 
            \brief create a new file
               
            Creates a new file on the filesystem. By default this method fails
            if a file of identical name already exists. However, if seting the
            overwrite flag ow to true the existing file will be overwriten and
            all data in this file is lost. In addition files can be split into
            smaller portions. The split size can be set with ssize.
            \throws pni::io::nx::nxfile_error for all file related errors
            \throws pni::io::nx::nxbackend_error for errors during property list creation
            \param n file name
            \param ow overwrite existing file if true
            \param ssize split size
            \return instance of H5File
            */
            static H5File create_file(const string &n,bool ow=false,
                                      ssize_t ssize=0);

            //====================misc methods=================================
            //! close the file
            virtual void close();

            //-----------------------------------------------------------------
            //! flush the file
            void flush() const;

            //-----------------------------------------------------------------
            //! return true if file is read-only
            bool is_readonly() const;

            //-----------------------------------------------------------------
            //! obtain the path of the file
            virtual string path() const;

            //-----------------------------------------------------------------
            //! obtain the base part of the files path
            virtual string base() const;

            //-----------------------------------------------------------------
            //! obtain the name of the file (path without base)
            virtual string name() const;

            //-----------------------------------------------------------------
            /*!
            \brief get number of open fields

            Returns the number of open fields.
            \return number of open fields
            */
            size_t open_fields() const
            {
                return H5Fget_obj_count(id(),H5F_OBJ_DATASET);
            }

            //-----------------------------------------------------------------
            /*!
            \brief get number of open groups

            \return number of open groups
            */
            size_t open_groups() const
            {
                return H5Fget_obj_count(id(),H5F_OBJ_GROUP);
            }

    };


//end of namespace
}
}
}
}
