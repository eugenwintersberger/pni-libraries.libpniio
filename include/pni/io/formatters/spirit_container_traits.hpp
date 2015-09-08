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
    //! \ingroup formatter_classes
    //! \brief mdarrya container trait
    //! 
    //! Trait to identify mdarray as a container type for boost::spirit::karma
    //!
    //! \tparam OTYPES template parameters for mdarray
    //!
    template<typename ...OTYPES> 
    struct is_container<pni::core::mdarray<OTYPES...> const>: mpl::true_
    { };
    
    //-------------------------------------------------------------------------
    //! 
    //! \ingroup formatter_classes
    //! \brief mdarray iterator trait
    //! 
    //! Iterator trait for the mdarray template for boost::spirit::karma.
    //! 
    //! \tparam OTYPES template parameters for mdarray
    //! 
    template<typename ...OTYPES>
    struct container_iterator<pni::core::mdarray<OTYPES...> const>
    {
        //! iterator type for mdarray
        typedef typename pni::core::mdarray<OTYPES...>::const_iterator type;
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief begin trait for mdarray
    //! 
    //! Static function used by boost::spirit::karam to retrieve the iterator
    //! to the first element for an mdarray instance. 
    //! 
    //! \tparam OTYPES template parameters for mdarray
    //! 
    template<typename ...OTYPES>
    struct begin_container<pni::core::mdarray<OTYPES...> const>
    {
        //!
        //! \brief get iterator for first element
        //! 
        //! \param c const reference to an mdarray instance
        //! \return iterator to the first element
        //!
        static typename pni::core::mdarray<OTYPES...>::const_iterator
        call(pni::core::mdarray<OTYPES...> const& c)
        {            
            return c.begin();
        }
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief end trait for mdarray
    //! 
    //! Provides a static function used by boost::spirit::karam to retreive the 
    //! end iterator for an instance of mdarray.
    //! 
    //! \tparam OTYPES template parameters for mdarray
    //! 
    template<typename ...OTYPES>
    struct end_container<pni::core::mdarray<OTYPES...> const>
    {
        //!
        //! \brief get end iterator
        //! 
        //! \param c const reference to an instance of mdarray
        //! \return iterator refering to the end of the sequence
        //!
        static typename pni::core::mdarray<OTYPES...>::const_iterator
        call(pni::core::mdarray<OTYPES...> const &c)
        {            
            return c.end();
        }
    };
        
    //-------------------------------------------------------------------------
    // Traits for Karma and the array type erasure
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief container trait for array
    //! 
    //! Container trait used by boost::spirit::karma to identify the array
    //! type erasure as a container type.
    //! 
    template<> 
    struct is_container<pni::core::array const>: mpl::true_
    { };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief iterator trait for array
    //! 
    //! Trait used by boost::spirit::karma to obtain the iterator type 
    //! for the array type erasure.
    //!
    template<>
    struct container_iterator<pni::core::array const>
    {
        typedef pni::core::array::const_iterator type;
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief begin trait for array
    //!
    //! Provides a static function used by boost::spirit::karma to retrieve 
    //! an iterator to the first element of an array instance. 
    //!
    template<>
    struct begin_container<pni::core::array const>
    {
        //!
        //! \brief get iterator to first element
        //! 
        //! \param c const reference to an instance of array
        //! \return iterator the first element
        //!
        static pni::core::array::const_iterator
        call(pni::core::array const& c)
        {
            std::cout<<"begin"<<std::endl;
            return c.begin();
        }
    };
    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup formatter_classes
    //! \brief end trait for array
    //!
    //! Provides a static function used by boost::spirit::karma to retrieve
    //! an interator to the last element of an array instance.
    //!
    template<>
    struct end_container<pni::core::array const>
    {
        //!
        //! \brief get iterator to last element
        //! 
        //! \param c const reference to an array instance
        //! \return iterator to the end of the sequence
        //!
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
