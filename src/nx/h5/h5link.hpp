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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of the H5Link link manager class.
 *
 * Created on: Feb 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/core/types.hpp>
#include <pni/core/exceptions.hpp>


namespace pni{
namespace io {
namespace nx{
namespace h5{

    using namespace pni::core;
    //avoid namespace collisions with std
    using pni::core::exception;
    using pni::core::string;

    //some forward declarations
    class H5File;
    class H5Dataset;
    class H5Group;
   
    /*! 
    \ingroup nxh5_classes

    This class holds only static methods which can be used
    to create internal and external links. 
    */
    class H5Link
    {
        private:
            /*! 
            \brief split the target path

            This method splits the target path into a file and a object-path
            part. If the former one is an empty string the like that must be
            created is an internal link.  Otherwise an external link will be
            created.
            \throws pni::io::nx::nxlink_error in case of errors
            \param path target path provided by the user
            \param file will hold the file portion of the path
            \param opath will hold the object portion of the path
            */
            static void __split_path(const string &path,string &file,
                    string &opath);

            //-----------------------------------------------------------------
            /*! 
            \brief create an external link

            Create an external link to an object.
            \throws pni::io::nx::nxlink_error in case of errors
            \param file path to the file where to find the target
            \param opath path of the object in the external file
            \param ref reference object for the link
            \param name name of the new link
            */
            static void __create_ext_link(const string &file,
                    const string &opath,const H5Group &ref,
                    const string &name);

            //-----------------------------------------------------------------
            /*! 
            \brief create an internal link

            Creates and internal link to an object in the same file as the ref
            object.
            \throws pni::io::nx::nxlink_error in case of errors
            \param opath path to the target object
            \param ref reference object in the file
            \param n name of the new link
            */
            static void __create_int_link(const string &opath,
                    const H5Group &ref,const string &n);
        public:

            //-----------------------------------------------------------------
            //! create a link
            static void create(const string &s,const H5Group &ref,
                    const string &name);

            //-----------------------------------------------------------------
            //! create a link from a group object
            static void create(const H5Group &g,const H5Group &ref,
                    const string &name);

            //-----------------------------------------------------------------
            //! create a link from a dataset object
            static void create(const H5Dataset &d,const H5Group &ref,
                    const string &name);

    };

//end of namespace
}
}
}
}
