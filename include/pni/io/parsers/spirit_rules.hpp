//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Dec 3, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <pni/core/types.hpp>
#include <boost/mpl/map.hpp>
#include <boost/spirit/include/qi_real.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_int.hpp>

namespace pni{
namespace io{

#define PARSER_TYPE(p)\
    std::remove_const<decltype(p)>::type

    //!
    //! \ingroup parser_internal_classes
    //! \brief spirit rule map
    //!
    //! This MPL map provides a mapping from data types to their appropriate
    //! parsing rules provided by the boost::spirit library.
    //!
    typedef boost::mpl::map<
        boost::mpl::pair<
                         pni::core::uint8 ,
                         boost::spirit::qi::uint_parser<pni::core::uint8,
                                                        10,1,4> 
                        >,

        boost::mpl::pair<pni::core::uint16,
                         PARSER_TYPE(boost::spirit::qi::ushort_)
                        >,

        boost::mpl::pair<
                         pni::core::uint32,
                         PARSER_TYPE(boost::spirit::qi::uint_)  
                        >,

        boost::mpl::pair<
                         pni::core::uint64,
                         PARSER_TYPE(boost::spirit::qi::ulong_) 
                        >,
        boost::mpl::pair<
                         pni::core::int8 ,
                         boost::spirit::qi::uint_parser<pni::core::int8,
                                                        10,1,4> 
                        >,

        boost::mpl::pair<
                         pni::core::int16, 
                         PARSER_TYPE(boost::spirit::qi::short_) 
                        >,

        boost::mpl::pair<
                         pni::core::int32, 
                         PARSER_TYPE(boost::spirit::qi::int_)   
                        >,

        boost::mpl::pair<
                         pni::core::int64, 
                         PARSER_TYPE(boost::spirit::long_)      
                        >,

        boost::mpl::pair<
                         core::float32, 
                         PARSER_TYPE(boost::spirit::float_)      
                        >,

        boost::mpl::pair<
                         pni::core::float64, 
                         PARSER_TYPE(boost::spirit::double_)     
                        >,

        boost::mpl::pair<
                         pni::core::float128,
                         PARSER_TYPE(boost::spirit::long_double) 
                        >,

        boost::mpl::pair<
                         pni::core::bool_t,  
                         PARSER_TYPE(boost::spirit::bool_)      
                        >,

        boost::mpl::pair<
                         bool,
                         PARSER_TYPE(boost::spirit::bool_)
                        >
        > spirit_rules;

//end of namespace
}
}
