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
// Created on: Aug 5, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/exceptions.hpp>

namespace pni{
namespace io{

    //--------------------------------------------------------------------------
    io_error::io_error():exception("io_error"){ }

    //--------------------------------------------------------------------------
    io_error::io_error(const exception_record &i,const string &d)
                 :exception("io_error",i,d)
    { }

    //--------------------------------------------------------------------------
    io_error::~io_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const io_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    link_error::link_error():exception("link_error"){ }

    //--------------------------------------------------------------------------
    link_error::link_error(const exception_record &i,const string &d)
                 :exception("link_error",i,d)
    { }

    //--------------------------------------------------------------------------
    link_error::~link_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const link_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    parser_error::parser_error():exception("parser_error"){ }

    //--------------------------------------------------------------------------
    parser_error::parser_error(const exception_record &i,const string &d)
                 :exception("parser_error",i,d)
    { }

    //--------------------------------------------------------------------------
    parser_error::~parser_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const parser_error &e)
    {
        return e.print(o);
    }
    
    //--------------------------------------------------------------------------
    invalid_object_error::invalid_object_error():
        exception("invalid_object_error"){ }

    //--------------------------------------------------------------------------
    invalid_object_error::invalid_object_error(const exception_record &i,
                                               const string &d)
                 :exception("invalid_object_error",i,d)
    { }

    //--------------------------------------------------------------------------
    invalid_object_error::~invalid_object_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const invalid_object_error &e)
    {
        return e.print(o);
    }
    
    //--------------------------------------------------------------------------
    object_error::object_error():exception("object_error"){ }

    //--------------------------------------------------------------------------
    object_error::object_error(const exception_record &i,const string &d)
                 :exception("object_error",i,d)
    { }

    //--------------------------------------------------------------------------
    object_error::~object_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const object_error &e)
    {
        return e.print(o);
    }

//end of namespace
}
}

