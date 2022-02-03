//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
//  Created on: Jan 8, 2013
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif 
#include "../boost_unit_test.hpp"
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include "../boost_unit_test.hpp"
#include <boost/mpl/list.hpp>
#include <boost/current_function.hpp>
#include <vector>
#include <iostream>

#include <pni/arrays/index_iterator.hpp>
#include <pni/arrays/index_map/index_maps.hpp>

using namespace pni;

namespace std{
        
    ostream &operator<<(ostream &stream,const shape_t &s)
    {
        stream<<"(";
        for(auto i: s) stream<<i;
        stream<<")";
        return stream;
    }
}

typedef boost::mpl::list<shape_t> test_types; 

BOOST_AUTO_TEST_SUITE(index_iterator_test)

BOOST_AUTO_TEST_CASE_TEMPLATE(test_forward,CT,test_types)
{
    typedef index_iterator<CT,dynamic_cindex_map> iterator_t;
    std::vector<CT> ref_index{{0,0},{0,1},{0,2},{0,3},
                              {1,0},{1,1},{1,2},{1,3}};
    

    auto i_start = iterator_t::begin(shape_t{2,4});
    auto i_end   = iterator_t::end(shape_t{2,4});
    auto r_start = ref_index.begin();
    auto r_end   = ref_index.end();
    BOOST_CHECK_EQUAL_COLLECTIONS(i_start,i_end,r_start,r_end);
}


BOOST_AUTO_TEST_SUITE_END()


