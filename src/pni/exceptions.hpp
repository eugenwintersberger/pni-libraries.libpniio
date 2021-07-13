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
// Created on: Jul 7, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <iostream>
#include <pni/error.hpp>

#include <pni/windows.hpp>

namespace pni{
namespace io{   

    //! 
    //! \ingroup io_error_classes
    //! \brief general IO error
    //!
    //! This exception is thrown in all situations where IO operations fail.
    //! This includes reading and writing of payload- or meta-data.
    //!
    class PNIIO_EXPORT io_error:public pni::core::exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit io_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit io_error(const pni::core::exception_record &i,
                              const pni::core::string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~io_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend PNIIO_EXPORT std::ostream &operator<<(std::ostream &o,
                                                         const io_error &e);
    };


    //! 
    //! \ingroup io_error_classes
    //! \brief link error
    //!
    //! Exception is thrown when link operations fails.
    //!
    class PNIIO_EXPORT link_error:public pni::core::exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit link_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit link_error(const pni::core::exception_record &i,
                                const pni::core::string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~link_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend PNIIO_EXPORT std::ostream &operator<<(std::ostream &o,
                                                         const link_error &e);
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup io_error_classes
    //! \brief general parser related error
    //!
    //! Raised in case of a general parser error. This exception can be 
    //! expected to be thrown by all functions and methods that are somehow 
    //! related to parsing strings.
    //!
    class PNIIO_EXPORT parser_error:public pni::core::exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit parser_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit parser_error(const pni::core::exception_record &i,
                                  const pni::core::string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~parser_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend PNIIO_EXPORT std::ostream &operator<<(std::ostream &o,
                                                         const parser_error &e);
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup io_error_classes
    //! \brief unexpected invalid object
    //!
    //! Raised in cases where an object is unexpectedly in an invalid state. 
    //! An object uses this exception in cases where the user makes a request 
    //! on a feature not availabel as the object is in an invalid state.
    //!
    class PNIIO_EXPORT invalid_object_error:public pni::core::exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit invalid_object_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit invalid_object_error(const pni::core::exception_record &i,
                                          const pni::core::string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~invalid_object_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend PNIIO_EXPORT std::ostream &operator<<(std::ostream &o,
                                                         const invalid_object_error &e);
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup io_error_classes
    //! \brief general error on IO objects
    //!
    //! Used for general errors on IO objects. This includes the failure 
    //! to create or close an object. 
    //!
    class PNIIO_EXPORT object_error:public pni::core::exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit object_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit object_error(const pni::core::exception_record &i,
                                  const pni::core::string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~object_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend PNIIO_EXPORT std::ostream &operator<<(std::ostream &o,
                                                         const object_error &e);
    };


//end of namespace
}
}
