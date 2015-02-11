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

#include <iterator>
#include <pni/core/types.hpp>
#include <boost/spirit/include/karma.hpp>

#include "get_generator.hpp"

namespace pni{
namespace io{

    using namespace pni;
    using namespace boost::spirit;

    template<typename T> 
    class formatter
    {
        private: 
            typedef std::back_insert_iterator<core::string> iterator_type;
            typedef typename get_generator<iterator_type,T>::type generator_type; 

            generator_type generator;
    
        public:

            core::string operator()(const T &value) const
            {
                core::string buffer;
                iterator_type inserter(buffer);

                karma::generate(inserter,generator,value);

                return buffer;
            }

            
    };

//end of namespace
}
}
