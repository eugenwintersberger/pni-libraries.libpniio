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

#include "H5ErrorStack.hpp"
#include <cstdio>
#include <cstdlib>

namespace pni {
namespace io {
namespace nx {
namespace h5 {


    //--------------------------------------------------------------------------
    herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data)
    {
        H5ErrorStack *stack = (H5ErrorStack *)client_data;

        H5Error h5e;
        if(eptr->file_name!=NULL) h5e.file_name(String(eptr->file_name));
        if(eptr->func_name!=NULL) h5e.func_name(String(eptr->func_name));
        if(eptr->desc != NULL) h5e.description(String(eptr->desc));
        h5e.minor_number(eptr->min_num);
        h5e.major_number(eptr->maj_num);
        h5e.class_id(eptr->cls_id);
        stack->append(h5e);

        return 0;
    }

    //--------------------------------------------------------------------------
    H5ErrorStack::H5ErrorStack() { } 

    //--------------------------------------------------------------------------
    void H5ErrorStack::fill()
    {
        //fill the stack with error messages
        _stack_id = H5Eget_current_stack();
        H5Ewalk2(_stack_id,H5E_WALK_DOWNWARD,_error_walker,(void *)this);
    }

    //--------------------------------------------------------------------------
    H5ErrorStack::H5ErrorStack(const H5ErrorStack &s)
    {
        _stack_id = s._stack_id;
        _errors = std::vector<H5Error>(s._errors);
    }

    //--------------------------------------------------------------------------
    H5ErrorStack &H5ErrorStack::operator=(const H5ErrorStack &s)
    {
        if(this != &s){
            _stack_id = s._stack_id;
            _errors = std::vector<H5Error>(s._errors);
        }

        return *this;
    }

    //--------------------------------------------------------------------------
    H5ErrorStack::~H5ErrorStack() 
    {
        _errors.clear();
        H5Eclear2(_stack_id);
        H5Eclose_stack(_stack_id);
    }

    //--------------------------------------------------------------------------
    void H5ErrorStack::append(const H5Error &e){ _errors.push_back(e); }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const H5ErrorStack &s)
    {
        std::vector<H5Error>::const_iterator iter;

        o<<"HDF5 Errors ("<<s.number_of_errors()<<" error records):"
         <<std::endl;

        for(iter=s._errors.begin();iter!=s._errors.end();iter++)
            o<<*iter<<std::endl;

        return o;
    }

//end of namespace
}
}
}
}
