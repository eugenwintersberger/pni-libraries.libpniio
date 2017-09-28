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
#include <pni/io/fio/fio_reader.hpp>

BOOST_AUTO_TEST_SUITE(test_fio_reader)

BOOST_AUTO_TEST_CASE(test_single_column_file)
{
	pni::io::fio_reader reader("scan_mca_00001.fio");
	BOOST_CHECK_EQUAL(reader.nparameters(),102);
	BOOST_CHECK_EQUAL(reader.ncolumns(),1);
}

BOOST_AUTO_TEST_CASE(test_multi_column_file)
{
	pni::io::fio_reader reader("tstfile_00012.fio");
	BOOST_CHECK_EQUAL(reader.nparameters(),4);
	BOOST_CHECK_EQUAL(reader.ncolumns(),14);

}


BOOST_AUTO_TEST_SUITE_END()




