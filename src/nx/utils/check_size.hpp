/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Utilty functions and function templates concerning NXField objects.
 *
 * Created on: Jul 9, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/exceptions.hpp>
#include <pni/core/type_id_map.hpp>
#include "types.hpp"

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup nexus_utilities
    \brief check object size

    Checks if the sizes of two objects is equal and returns true if they are. 
    All two types involved in this template function must provide a size()
    method returning an integral size representation of the object. 

    \tparam ST1 type 1
    \tparam ST2 type 2
    \param o1 instance of ST1
    \param o2 instance of ST2
    \return true if sizes are equal, false otherwise
    */
    template<typename ST1,typename ST2>
    bool check_size(const ST1 &o1,const ST2 &o2)
    {
        return o1.size() == o2.size();
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utilities
    \brief check object size

    Compares the size of two objects and throws an exception if it does not
    match. This function template is quite handy in cases where a size mismatch
    should trigger an exception at a particular position of the code. 

    \throws size_missmatch_error if objects have different size
    \tparam ST1 type 1
    \tparam ST2 type 2
    \param o1 instance of ST1
    \param o2 instance of ST2
    \param r expcetion record of the code position where the check is performed
    */
    template<typename ST1,typename ST2>
    void check_size(const ST1 &o1,const ST2 &o2,const exception_record &r)
    {
        if(!check_size(o1,o2))
        {
            std::stringstream ss;
            ss<<"Objects are of different size ("<<o1.size()<<" and ";
            ss<<o2.size()<<")!";
            throw size_missmatch_error(r,ss.str());
        }
    }

    template<typename ST1,typename ST2>
    bool check_rank(const ST1 &o1,const ST2 &o2)
    {
        auto s1=o1.template shape<shape_t>();
        auto s2=o2.template shape<shape_t>();
        return s1.size() == s2.size();
    }

//end of namespace
}
}
}
