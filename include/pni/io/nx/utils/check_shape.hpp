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
#include "check_rank.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

namespace pni{
namespace io{
namespace nx{

    /*!
    \ingroup nexus_utilities
    \brief check the shape of two array objects 

    Compares the number of elements along each dimension. If they are equal true
    is returned, otherwise false.
    \tparam AT1 array type 1
    \tparam AT2 array type 2
    \param o1 instance of AT1
    \param o2 instance of AT2
    \return true if ranks match, false otherwise
    */
    template<typename AT1,typename AT2>
    bool check_shape(const AT1 &o1,const AT2 &o2)
    {
        //we first have to check the rank - if this does not match no further
        //investigation should be done
        if(!check_rank(o1,o2)) return false;

        auto s1=o1.template shape<shape_t>();
        auto s2=o2.template shape<shape_t>();

        if(!std::equal(s1.begin(),s1.end(),s2.begin()))
            return false;

        return true;
    }

    //-------------------------------------------------------------------------
    /*!
    \ingroup nexus_utilities
    \brief check the shape of two arrays

    Compares the number of elements along each dimension. If they are not equal
    an exception is thrown. The exception record is passed as the last argument
    of the function template and thus can be set to point to the location in the
    code where the check was made rather than the location in this function. 

    \throws shape_mismatch_error
    \tparam AT1 first array type
    \tparam AT2 second array type
    \param o1 instance of AT1
    \param o2 instance of AT2
    \param r exception record of the check position
    */
    template<typename AT1,typename AT2>
    void check_shape(const AT1 &o1,const AT2 &o2,const exception_record &r)
    {
        if(!check_shape(o1,o2))
        {
            auto s1 = o1.template shape<shape_t>();
            auto s2 = o1.template shape<shape_t>();
            std::stringstream ss;
            ss<<"Objects have different shape ( ";
#ifdef NOFOREACH
            BOOST_FOREACH(auto s, s1)
#else
            for(auto s: s1) 
#endif
                ss<<s<<" ";
            ss<<") and ( ";
#ifdef NOFOREACH
            BOOST_FOREACH(auto s, s2)
#else
            for(auto s: s2) 
#endif 
                ss<<s<<" ";
            ss<<")!";
            throw shape_mismatch_error(r,ss.str());
        }
    }

//end of namespace
}
}
}
