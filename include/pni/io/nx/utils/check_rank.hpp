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
#include <pni/core/error.hpp>
#include "types.hpp"

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup nexus_utilities
    \brief check the rank of two array objects 

    Checks the number of dimensions of two objects. If they match return true,
    false otherwise. 
    \tparam AT1 array type 1
    \tparam AT2 array type 2
    \param o1 instance of AT1
    \param o2 instance of AT2
    \return true if ranks match, false otherwise
    */
    template<typename AT1,typename AT2>
    bool check_rank(const AT1 &o1,const AT2 &o2)
    {
        auto s1=o1.template shape<shape_t>();
        auto s2=o2.template shape<shape_t>();
        return s1.size() == s2.size();
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utilities
    \brief check the rank of two arrays

    Checks the number of dimensions of two objects and throws an exception if
    they do not match. 
    \throws shape_mismatch_error
    \tparam AT1 first array type
    \tparam AT2 second array type
    \param o1 instance of AT1
    \param o2 instance of AT2
    \param r exception record of the check position
    */
    template<typename AT1,typename AT2>
    void check_rank(const AT1 &o1,const AT2 &o2,const exception_record &r)
    {
        if(!check_rank(o1,o2))
        {
            std::stringstream ss;
            ss<<"Objects have different rank ("<<o1.rank();
            ss<<" and "<<o2.rank()<<")!";
            throw shape_mismatch_error(r,ss.str());
        }
    }

//end of namespace
}
}
}
