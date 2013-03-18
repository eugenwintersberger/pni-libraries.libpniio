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
 * H5ErrorStack.cpp
 *
 *  Created on: Jul 28, 2011
 *      Author: Eugen Wintersberger
 */

#include "h5_error_stack.hpp"
#include <cstdio>
#include <cstdlib>
#include <sstream>

namespace pni {
namespace io {
namespace nx {
namespace h5 {


    //--------------------------------------------------------------------------
    herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data)
    {
        h5_error_stack *stack = (h5_error_stack *)client_data;

        h5_error h5e;
        if(eptr->file_name!=NULL) h5e.file_name(string(eptr->file_name));
        if(eptr->func_name!=NULL) h5e.func_name(string(eptr->func_name));
        if(eptr->desc != NULL) h5e.description(string(eptr->desc));
        h5e.minor_number(eptr->min_num);
        h5e.major_number(eptr->maj_num);
        h5e.class_id(eptr->cls_id);
        stack->append(h5e);

        return 0;
    }

    //--------------------------------------------------------------------------
    h5_error_stack::h5_error_stack() { } 

    //--------------------------------------------------------------------------
    void h5_error_stack::fill()
    {
        //fill the stack with error messages
        _stack_id = H5Eget_current_stack();
        H5Ewalk2(_stack_id,H5E_WALK_DOWNWARD,_error_walker,(void *)this);
    }

    //--------------------------------------------------------------------------
    h5_error_stack::h5_error_stack(const h5_error_stack &s)
    {
        _stack_id = s._stack_id;
        _errors = std::vector<h5_error>(s._errors);
    }

    //--------------------------------------------------------------------------
    h5_error_stack &h5_error_stack::operator=(const h5_error_stack &s)
    {
        if(this != &s){
            _stack_id = s._stack_id;
            _errors = std::vector<h5_error>(s._errors);
        }

        return *this;
    }

    //--------------------------------------------------------------------------
    h5_error_stack::~h5_error_stack() 
    {
        _errors.clear();
        H5Eclear2(_stack_id);
        H5Eclose_stack(_stack_id);
    }

    //--------------------------------------------------------------------------
    void h5_error_stack::append(const h5_error &e){ _errors.push_back(e); }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const h5_error_stack &s)
    {
        std::vector<h5_error>::const_iterator iter;

        o<<"HDF5 Errors ("<<s.number_of_errors()<<" error records):"
         <<std::endl;

        for(iter=s._errors.begin();iter!=s._errors.end();iter++)
            o<<*iter<<std::endl;

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
