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
 *  Created on: May 06, 2013
 *      Author: Eugen Wintersberger
 */

#include "record_parser_test.hpp"
#include "../EqualityCheck.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(record_parser_test);

//-----------------------------------------------------------------------------
void record_parser_test::setUp() 
{
}

//-----------------------------------------------------------------------------
void record_parser_test::tearDown() {}

//-----------------------------------------------------------------------------
void record_parser_test::test_pure_scalar()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    
    string r1 = "0. 1 1.234 7 -3 1.e-4";
    string r2 = " 0. ; 1; 1.234 ;7 ; -3; 1.e-4  ";
    iterator_t start,stop; 

    record_parser_t p1;
    record_parser_t p2(';','[',']',',');
    record_t rec;
   
    start = r1.begin(); stop = r1.end();
    parse(start,stop,p1,rec);
    auto iter = rec.begin();
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::INT32);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::INT32);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::INT32);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::FLOAT64);

    start = r2.begin(); stop = r2.end();
    parse(start,stop,p2,rec);
    iter = rec.begin();
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::INT32);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::FLOAT64);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::INT32);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::INT32);
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*(iter++))==type_id_t::FLOAT64);
    
}

//-----------------------------------------------------------------------------
void record_parser_test::test_array_value()
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    string r1 = "0. 1 1.234 7 [1,2,3,4,5] -3 1.e-4";
    string r2 = " 0. ; 1; 1.234 ;7 ;(1.  2. 3. 4. 5.); -3; 1.e-4  ";
    iterator_t start,stop; 

    record_parser_t p1;
    record_parser_t p2(';','(',')',' ');
    record_t rec;

    start = r1.begin(); stop = r1.end();
    parse(start,stop,p1,rec);
    auto iter = rec.begin();
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::FLOAT64);
    check_equality(boost::apply_visitor(get_value<float64>(),*iter),0.);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::INT32);
    check_equality(boost::apply_visitor(get_value<int32>(),*iter),1);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::FLOAT64);
    check_equality(boost::apply_visitor(get_value<float64>(),*iter),1.234);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::INT32);
    check_equality(boost::apply_visitor(get_value<int32>(),*iter),7);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::INT32);
    check_equality(boost::apply_visitor(get_value<int32,0>(),*iter),1);
    check_equality(boost::apply_visitor(get_value<int32,1>(),*iter),2);
    check_equality(boost::apply_visitor(get_value<int32,2>(),*iter),3);
    check_equality(boost::apply_visitor(get_value<int32,3>(),*iter),4);
    check_equality(boost::apply_visitor(get_value<int32,4>(),*iter),5);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::INT32);
    check_equality(boost::apply_visitor(get_value<int32>(),*iter),-3);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::FLOAT64);
    check_equality(boost::apply_visitor(get_value<float64>(),*iter),1.e-4);
    
    start = r2.begin(); stop = r2.end();
    parse(start,stop,p2,rec);
    iter = rec.begin();
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::FLOAT64);
    check_equality(boost::apply_visitor(get_value<float64>(),*iter),0.);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::INT32);
    check_equality(boost::apply_visitor(get_value<int32>(),*iter),1);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::FLOAT64);
    check_equality(boost::apply_visitor(get_value<float64>(),*iter),1.234);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::INT32);
    check_equality(boost::apply_visitor(get_value<int32>(),*iter),7);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::FLOAT64);
    check_equality(boost::apply_visitor(get_value<float64,0>(),*iter),1.);
    check_equality(boost::apply_visitor(get_value<float64,1>(),*iter),2.);
    check_equality(boost::apply_visitor(get_value<float64,2>(),*iter),3.);
    check_equality(boost::apply_visitor(get_value<float64,3>(),*iter),4.);
    check_equality(boost::apply_visitor(get_value<float64,4>(),*iter),5.);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::INT32);
    check_equality(boost::apply_visitor(get_value<int32>(),*iter),-3);
    ++iter;
    CPPUNIT_ASSERT(boost::apply_visitor(get_type_id(),*iter)==type_id_t::FLOAT64);
    check_equality(boost::apply_visitor(get_value<float64>(),*iter),1.e-4);
}
