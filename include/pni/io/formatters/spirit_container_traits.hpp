//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Feb 11, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>
#include <boost/spirit/include/karma.hpp>




namespace boost{
namespace spirit{
namespace traits{
    
    //-------------------------------------------------------------------------
    // Traits for Karma and the mdarray template
    //-------------------------------------------------------------------------
    template<typename ...OTYPES> 
    struct is_container<pni::core::mdarray<OTYPES...> const>: mpl::true_
    { };
    
    //-------------------------------------------------------------------------
    template<typename ...OTYPES>
    struct container_iterator<pni::core::mdarray<OTYPES...> const>
    {
        typedef typename pni::core::mdarray<OTYPES...>::const_iterator type;
    };
    
    //-------------------------------------------------------------------------
    template<typename ...OTYPES>
    struct begin_container<pni::core::mdarray<OTYPES...> const>
    {
        static typename pni::core::mdarray<OTYPES...>::const_iterator
        call(pni::core::mdarray<OTYPES...> const& c)
        {            
            return c.begin();
        }
    };
    
    //-------------------------------------------------------------------------
    template<typename ...OTYPES>
    struct end_container<pni::core::mdarray<OTYPES...> const>
    {
        static typename pni::core::mdarray<OTYPES...>::const_iterator
        call(pni::core::mdarray<OTYPES...> const &c)
        {            
            return c.end();
        }
    };
        
    //-------------------------------------------------------------------------
    // Traits for Karma and the array type erasure
    //-------------------------------------------------------------------------
    template<> 
    struct is_container<pni::core::array const>: mpl::true_
    { };
    
    //-------------------------------------------------------------------------
    template<>
    struct container_iterator<pni::core::array const>
    {
        typedef pni::core::array::const_iterator type;
    };
    
    //-------------------------------------------------------------------------
    template<>
    struct begin_container<pni::core::array const>
    {
        static pni::core::array::const_iterator
        call(pni::core::array const& c)
        {
            std::cout<<"begin"<<std::endl;
            return c.begin();
        }
    };
    
    //-------------------------------------------------------------------------
    template<>
    struct end_container<pni::core::array const>
    {
        static pni::core::array::const_iterator
        call(pni::core::array const &c)
        {
            std::cout<<"end"<<std::endl;
            return c.end();
        }
    };
    
//end of namespace
}
}
}
