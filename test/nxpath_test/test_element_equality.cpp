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
//  Created on: May 4, 2015
//      Author: Eugen Wintersberger
//

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nxpath.hpp>

using namespace pni::core;
using namespace pni::io::nx;

namespace std{
    
    ostream &operator<<(ostream &stream,const nxpath::element_type &e)
    {
        stream<<e.first<<":"<<e.second;
        return stream;
    }
}

BOOST_AUTO_TEST_SUITE(test_element_equality)
    
    typedef nxpath::element_type element_type;

    BOOST_AUTO_TEST_CASE(test_equality)
    {
        BOOST_CHECK_EQUAL(element_type("entry","NXentry") , 
                       element_type("entry","NXentry"));

        BOOST_CHECK_EQUAL(element_type("","NXentry") , 
                       element_type("","NXentry"));
        
        BOOST_CHECK_EQUAL(element_type("entry","") , 
                       element_type("entry",""));
    }

    //-------------------------------------------------------------------------
    BOOST_AUTO_TEST_CASE(test_inequality)
    {
        BOOST_CHECK_NE(element_type("entry","NXentry") ,
                       element_type("scan_1","NXentry"));
        BOOST_CHECK_NE(element_type("entry","NXinstrument") ,
                       element_type("entry","NXentry"));
                       
        BOOST_CHECK_NE(element_type("","NXentry"),
                       element_type("entry","NXentry"));
        BOOST_CHECK_NE(element_type("entry","NXentry"),
                       element_type("entry",""));

        BOOST_CHECK_NE(element_type("entry","NXentry") , 
                       element_type("","NXentry"));
        BOOST_CHECK_NE(element_type("","NXentry") , 
                       element_type("entry","NXentry"));
                       
        BOOST_CHECK_NE(element_type("","NXentry") , 
                       element_type("","NXinstrument"));
        BOOST_CHECK_NE(element_type("entry","") ,
                       element_type("scan1",""));
       
    }

BOOST_AUTO_TEST_SUITE_END()

