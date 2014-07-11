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
//  Created on: Jul 28, 2011
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/exceptions.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <cstdio>
#include <cstdlib>
#include <sstream>

namespace pni {
namespace io {
namespace nx {
namespace h5 {

    using pni::io::object_error;
    using pni::io::io_error;


    //--------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
    herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data)
    {
        h5_error_stack *stack = (h5_error_stack *)client_data;

        h5_error h5e;
        if(eptr->file_name!=NULL) h5e.file_name(string(eptr->file_name));
        if(eptr->func_name!=NULL) h5e.func_name(string(eptr->func_name));
        if(eptr->desc != NULL) h5e.description(string(eptr->desc));
        h5e.minor_message(eptr->min_num);
        h5e.major_message(eptr->maj_num);
        h5e.class_name(eptr->cls_id);
        stack->append(h5e);

        return 0;
    }
#pragma GCC diagnostic pop

    //--------------------------------------------------------------------------
    h5_error_stack::h5_error_stack() noexcept { } 
    
    //--------------------------------------------------------------------------
    h5_error_stack::h5_error_stack(const h5_error_stack &s):
        _stack_id(s._stack_id),
        _errors(s._errors)
    { }

    //--------------------------------------------------------------------------
    void h5_error_stack::fill()
    {
        //fill the stack with error messages
        _stack_id = H5Eget_current_stack();
        if(_stack_id>0)
            H5Ewalk2(_stack_id,H5E_WALK_DOWNWARD,_error_walker,(void *)this);
        else
            std::cerr<<"Failure to retrieve the HDF5 error stack!"<<std::endl;
    }


    //--------------------------------------------------------------------------
    h5_error_stack &h5_error_stack::operator=(const h5_error_stack &s)
    {
        if(this != &s)
        {
            _stack_id = s._stack_id;
            _errors = std::vector<h5_error>(s._errors);
        }

        return *this;
    }

    //--------------------------------------------------------------------------
    h5_error_stack::~h5_error_stack() 
    {
        _errors.clear();
        if(H5Eclear2(_stack_id)<0)
            std::cerr<<"Failure clearing HDF5 error stack!"<<std::endl;

        if(H5Eclose_stack(_stack_id)<0)
            std::cerr<<"Failure closing HDF5 error stack!"<<std::endl;
    }

    //--------------------------------------------------------------------------
    void h5_error_stack::append(const h5_error &e){ _errors.push_back(e); }

    //--------------------------------------------------------------------------
    h5_error_stack::const_iterator h5_error_stack::begin() const
    {
        return _errors.begin();
    }

    //--------------------------------------------------------------------------
    h5_error_stack::const_iterator h5_error_stack::end() const
    {
        return _errors.end();
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const h5_error_stack &s)
    {
        o<<"HDF5 Errors ("<<s.number_of_errors()<<" error records):"
         <<std::endl;

        for(auto error: s)
            o<<error<<std::endl;

        return o;
    }

    //-------------------------------------------------------------------------
    string get_h5_error_string()
    {
        h5_error_stack stack;
        stack.fill();

        std::stringstream ss;
        ss<<stack<<std::endl;

        return ss.str();
    }

//end of namespace
}
}
}
}
