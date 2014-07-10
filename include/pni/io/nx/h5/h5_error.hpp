//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Feb 6, 2013
//      Author: Eugen Wintersberger
//
#pragma once

extern "C"{
#include <hdf5.h>
}

#include <iostream>
#include <vector>

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>


namespace pni {
namespace io {
namespace nx {
namespace h5 {

    using namespace pni::core;
    using pni::core::exception;
    using pni::core::string;

    //! 
    //! \ingroup nxh5_classes
    //! \brief HDF5 error record
    //!
    //! This class describes an HDF5 error record. Such a record consists 
    //! basically of a class id (which is HDF5 for all HDF5 library 
    //! functions), a description, a major and a minor message, and the name 
    //! of the function where the error occurred. Along with this the name 
    //! of the HDF5 source file where the function is defined is stored.
    //!
    class h5_error
    {
        private:
            string _class_name;    //!< name of the error class
            //! name of the source file where the error occurred
            string _file_name;    
            //! name of the HDF5 function where the error occurred
            string _func_name;     
            string _description;   //!< optional description of the error
            string _minor_message; //!< minor message of the error
            string _major_message; //!< major message of the error

            //!
            //! \brief get error message
            //! 
            //! Retrieve the content of an error message as a string.
            //! 
            //! \throws io_error in case of retrieval problems
            //! \param mid message id 
            //! \param mtype pointer to the message type
            //! \return content of the message as a string
            //!
            static string get_message(hid_t mid,H5E_type_t *mtype);
        public:
            //-----------------------------------------------------------------
            //! 
            //! \brief default constructor
            //! 
            //! The default constructor does not throw.
            //! 
            h5_error() noexcept;

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //! 
            h5_error(const h5_error &e) ;

            //-----------------------------------------------------------------
            //! default destructor
            virtual ~h5_error();

            //-----------------------------------------------------------------
            //! 
            //! \brief copy assignment operator
            //! 
            h5_error &operator=(const h5_error &e);
       
            //-----------------------------------------------------------------
            //! 
            //! \brief set class ID
            //! 
            //! Sets the class id from an object. 
            //! 
            //! \throws io_error if buffer allocation fails
            //! \param id object ID
            //!
            void class_name(hid_t id);

            //----------------------------------------------------------------
            //!
            //! \brief get class name
            //! 
            string class_name() const;
           
            //-----------------------------------------------------------------
            //!
            //! \brief set major number
            //! 
            //! Obtains the major number of the Error. 
            //!
            //! \throws io_error if message could not be retrieved
            //! \throws type_error if the message does not contain the major
            //!                    number
            //! \param mid message id 
            //! 
            void major_message(hid_t mid);

            //-----------------------------------------------------------------
            //! 
            //! \brief get major message
            //! 
            string major_message() const;


            //-----------------------------------------------------------------
            //!
            //! \brief set minor number
            //! 
            //! Obtains the minor number message from the Error.
            //! 
            //! \throws io_error if message could not be retrieved
            //! \throws type_error if the message does not contain the minor 
            //!                    number
            //! \param mid message id
            //! 
            void minor_message(hid_t mid);
            
            //-----------------------------------------------------------------
            //! 
            //! \brief get minor message
            //! 
            string minor_message() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief get file name
            //! 
            string file_name() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief get file name
            //! 
            void file_name(const string &n);

            //-----------------------------------------------------------------
            //! 
            //! \brief get function name
            //! 
            string func_name() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief set function name
            //! 
            void func_name(const string &n);

            //-----------------------------------------------------------------
            //! 
            //! \brief get description
            //! 
            string description() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief set description
            //! 
            void description(const string &n);
           
           
    };


    //-----------------------------------------------------------------
    //! 
    //! \brief ouput stream operator
    //! 
    std::ostream &operator<<(std::ostream &o,const h5_error &e);
//end of namespace
}
}
}
}

