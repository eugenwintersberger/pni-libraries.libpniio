//!
//! (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpninexus.
//!
//! libpninexus is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpninexus is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Implementation of the exception classes declared in Exceptions.hpp.
//!
//! Created on: Apr 19, 2011
//!     Author: Eugen Wintersberger
//!
//!

#include<iostream>
#include<string>

#include <pni/error/exceptions.hpp>

namespace pni{

    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const exception_record &rec)
    {
        o<<rec.file()<<"\t"<<rec.line()<<"\t"<<rec.function()<<std::endl;
        return o;
    }

    //============Implementation of constructors and destructor================
    exception::exception():
        std::exception()
    {}

    //--------------------------------------------------------------------------
    exception::exception(const string &n):
        std::exception(),
        _name(n),
        _description(),
        _records()
    {}

    //--------------------------------------------------------------------------
    exception::exception(const string &n,const exception_record &i):
        std::exception(),
        _name(n),
        _description(),
        _records()
    { 
        _records.push_back(i); 
    }

    //--------------------------------------------------------------------------
    exception::exception(const string &n,const exception_record &i,const string &d):
        std::exception(),
        _name(n),
        _description(d),
        _records()
    {
        _records.push_back(i);
    }

    //==========Implementation of output methods and operator===================
    std::ostream &exception::print(std::ostream &o) const 
    {
        o<<"Exception: "<<this->name()<<std::endl<<std::endl;
        o<<std::endl<<"Description:"<<std::endl;
        o<<this->description()<<std::endl<<std::endl;
        o<<"Exception thrown by:"<<std::endl;
#ifdef NOFOREACH
        for(auto iter = this->begin();iter != this->end(); iter++)
        {
            auto rec = *iter;
#else
        for(auto rec: *this){
#endif
            o<<rec<<std::endl;
        }
    
        o<<std::endl;

        return o;
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &ostr,const exception &ex)
    {
        return ex.print(ostr);
    }

    //=========Implementation of the output operators for other errors==========
    std::ostream &operator<<(std::ostream &o,const memory_allocation_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const filter_not_available &e)
    {
        return e.print(o);
    }
    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const shape_mismatch_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const size_mismatch_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const index_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const file_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const type_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const value_error &e)
    {
        return e.print(o);
    }
    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const range_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const not_implemented_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const iterator_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const key_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const memory_not_allocated_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const cli_argument_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const cli_option_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const cli_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const cli_help_request &e)
    {
        return e.print(o);
    }


//end of namespace
}
