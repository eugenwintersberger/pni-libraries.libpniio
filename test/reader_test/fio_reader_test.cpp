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
//************************************************************************
//
//  Created on: Sep 17, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <pni/io/fio/fio_reader.hpp>

BOOST_AUTO_TEST_SUITE(test_fio_reader)

BOOST_AUTO_TEST_CASE(test_single_column_file)
{
	pni::io::fio_reader reader("scan_mca_00001.fio");
	BOOST_CHECK_EQUAL(reader.nparameters(),101);
	BOOST_CHECK_EQUAL(reader.parameter<int>("EH1_MOT12"),-6);
	BOOST_CHECK_CLOSE(reader.parameter<float>("OH2_400TH"),0.01438125,0.0001);

	BOOST_CHECK_EQUAL(reader.ncolumns(),1);
	BOOST_CHECK_EQUAL(reader.nrecords(),2048);
}

BOOST_AUTO_TEST_CASE(test_multi_column_file)
{
	pni::io::fio_reader reader("tstfile_00012.fio");
	BOOST_CHECK_EQUAL(reader.nparameters(),4);
	BOOST_CHECK_EQUAL(reader.parameter<pni::core::string>("sweepMotor"),"eh1b_mot04");
	BOOST_CHECK_CLOSE(reader.parameter<float>("sweepOffset"),0.005,0.0001);

	BOOST_CHECK_EQUAL(reader.ncolumns(),14);
	BOOST_CHECK_EQUAL(reader.nrecords(),2001);

}


BOOST_AUTO_TEST_SUITE_END()




