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
#include <pni/core/error.hpp>

namespace pni{
namespace io{
    using namespace pni::core;
    using pni::core::exception;
    using pni::core::string;

    //! 
    //! \ingroup io_error_classes
    //! \brief general IO error
    //!
    //! This exception is thrown in all situations where IO operations fail.
    //!
    class io_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit io_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit io_error(const exception_record &i,const string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~io_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const io_error &e);
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
    class parser_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit parser_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit parser_error(const exception_record &i,const string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~parser_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const parser_error &e);
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup invalid_object_error
    //! \brief unexpected invalid object
    //!
    //! Raised in cases where an object is unexpectedly in an invalid state. 
    //!
    class invalid_object_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit invalid_object_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit invalid_object_error(const exception_record &i,
                                          const string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~invalid_object_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const invalid_object_error &e);
    };


//end of namespace
}
}
