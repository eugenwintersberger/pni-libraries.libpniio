//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//************************************************************************
//
//  Created on: Sep 17, 2014
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#include "../boost_unit_test.hpp"
#include <boost/test/tools/floating_point_comparison.hpp>
#include <pni/fio/fio_reader.hpp>
#include "tstfile_00012_pos.hpp"
#include "tstfile_00012_eh1b_c01.hpp"
#include "tstfile_00012_eh1b_c02.hpp"
#include "tstfile_00012_eh1b_c03.hpp"
#include "tstfile_00012_eh1b_c04.hpp"
#include "tstfile_00012_eh1b_c05.hpp"
#include "tstfile_00012_eh1b_c06.hpp"
#include "tstfile_00012_eh1b_c07.hpp"
#include "tstfile_00012_eh1b_c08.hpp"
#include "tstfile_00012_eh1b_c09.hpp"
#include "tstfile_00012_eh1b_c10.hpp"
#include "tstfile_00012_eh1b_c32.hpp"
#include "tstfile_00012_corr.hpp"
#include "tstfile_00012_deltaPos.hpp"

static const std::vector<int> single_column{
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 ,
    0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , 0 ,
    0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 ,
    0 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 2 , 0 ,
    0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 1 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    1 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 1 , 0 , 0 , 0 , 2 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 ,
    1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 0 , 1 , 0 , 1 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
    0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
    0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 2 , 0 , 0 ,
    1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 2 , 1 , 1 ,
    0 , 1 , 0 , 1 , 0 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 1 , 1 , 1 , 1 , 1 , 4 , 2 , 1 , 0 , 2 , 1 , 1 , 0 , 0 , 0 , 0 , 0 ,
    0 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 2 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 2 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 , 1 , 2 , 1 , 1 , 2 , 0 , 1 ,
    0 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 3 , 2 , 4 , 5 , 2 , 0 , 1 , 2 , 0 , 1 , 2 ,
    0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 1 , 3 , 3 , 2 , 1 , 1 , 0 , 1 , 3 ,
    1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 2 , 0 , 0 , 1 , 0 , 2 , 2 , 0 , 2 ,
    0 , 3 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 4 , 1 , 5 , 2 , 3 , 1 , 1 ,
    2 , 0 , 0 , 0 , 2 , 1 , 0 , 1 , 0 , 0 , 1 , 3 , 3 , 3 , 3 , 5 , 3 , 5 , 3 ,
    4 , 0 , 3 , 4 , 0 , 2 , 2 , 0 , 0 , 0 , 0 , 2 , 0 , 1 , 2 , 2 , 2 , 1 , 2 ,
    3 , 3 , 3 , 2 , 0 , 0 , 0 , 3 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 2 , 2 , 4 ,
    1 , 0 , 2 , 0 , 2 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 1 , 0 , 4 , 3 , 1 ,
    3 , 4 , 2 , 3 , 2 , 4 , 3 , 2 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 3 , 4 ,
    5 , 2 , 3 , 3 , 5 , 7 , 1 , 8 , 4 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 1 , 1 , 3 ,
    4 , 3 , 5 , 4 , 6 , 8 , 6 , 1 , 3 , 4 , 4 , 2 , 1 , 0 , 0 , 1 , 0 , 0 , 1 ,
    0 , 0 , 2 , 1 , 2 , 0 , 1 , 2 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
    1 , 2 , 1 , 0 , 1 , 2 , 1 , 3 , 2 , 2 , 0 , 2 , 2 , 1 , 0 , 0 , 1 , 0 , 0 ,
    0 , 2 , 0 , 3 , 6 , 5 , 5 , 5 , 8 , 7 , 2 , 8 , 0 , 4 , 4 , 1 , 3 , 1 , 0 ,
    0 , 0 , 1 , 1 , 2 , 3 , 4 , 6 , 3 , 4 , 1 , 5 , 6 , 4 , 4 , 1 , 0 , 1 , 0 ,
    0 , 0 , 0 , 0 , 0 , 1 , 1 , 2 , 3 , 1 , 0 , 2 , 3 , 4 , 5 , 3 , 2 , 0 , 0 ,
    1 , 0 , 1 , 0 , 0 , 0 , 1 , 1 , 5 , 1 , 6 , 1 , 2 , 5 , 2 , 2 , 1 , 1 , 0 ,
    1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 4 , 2 , 2 , 6 , 7 , 4 , 10 , 5 , 4 , 0 , 3 ,
    3 , 2 , 2 , 1 , 2 , 1 , 0 , 2 , 2 , 0 , 4 , 1 , 2 , 2 , 2 , 7 , 2 , 1 , 4 ,
    4 , 2 , 2 , 0 , 0 , 1 , 2 , 0 , 0 , 1 , 1 , 0 , 4 , 1 , 4 , 2 , 3 , 3 , 2 ,
    3 , 1 , 1 , 0 , 3 , 0 , 0 , 2 , 1 , 0 , 1 , 0 , 0 , 2 , 2 , 4 , 1 , 1 , 4 ,
    5 , 2 , 2 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 3 , 6 , 7 , 3 , 5 , 12 , 12
    , 5 , 11 , 9 , 8 , 4 , 4 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 2 , 3 , 4 , 5 , 4 , 4
    , 4 , 4 , 5 , 3 , 7 , 2 , 2 , 2 , 0 , 1 , 1 , 0 , 0 , 1 , 1 , 3 , 1 , 6 , 2
    , 3 , 2 , 3 , 4 , 1 , 2 , 0 , 3 , 3 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 2 , 4 , 6
    , 4 , 7 , 7 , 7 , 4 , 2 , 3 , 1 , 2 , 1 , 2 , 2 , 0 , 1 , 1 , 0 , 4 , 2 , 4
    , 4 , 8 , 17 , 15 , 6 , 7 , 8 , 11 , 8 , 0 , 1 , 3 , 1 , 0 , 4 , 1 , 1 , 0 ,
    1 , 1 , 2 , 6 , 4 , 3 , 6 , 10 , 6 , 3 , 3 , 5 , 5 , 1 , 1 , 0 , 0 , 1 , 0 ,
    1 , 1 , 1 , 4 , 3 , 3 , 3 , 3 , 4 , 5 , 3 , 2 , 5 , 0 , 1 , 1 , 0 , 0 , 1 ,
    0 , 0 , 1 , 2 , 3 , 5 , 5 , 5 , 5 , 4 , 7 , 9 , 7 , 2 , 5 , 5 , 2 , 1 , 2 ,
    0 , 0 , 2 , 1 , 2 , 4 , 4 , 7 , 8 , 8 , 3 , 3 , 6 , 5 , 5 , 6 , 0 , 3 , 2 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 4 , 3 , 3 , 3 , 4 , 5 , 3 , 4 , 6 , 5 , 1 , 1 ,
    1 , 2 , 1 , 0 , 1 , 0 , 1 , 0 , 4 , 2 , 0 , 1 , 3 , 3 , 4 , 2 , 1 , 1 , 2 ,
    2 , 0 , 1 , 0 , 0 , 1 , 0 , 2 , 2 , 3 , 0 , 3 , 2 , 4 , 4 , 3 , 3 , 3 , 3 ,
    2 , 1 , 0 , 3 , 0 , 1 , 0 , 2 , 0 , 5 , 3 , 4 , 7 , 6 , 7 , 6 , 4 , 7 , 7 ,
    1 , 4 , 2 , 3 , 0 , 0 , 0 , 1 , 0 , 0 , 2 , 2 , 5 , 3 , 9 , 1 , 2 , 6 , 6 ,
    7 , 4 , 3 , 3 , 0 , 2 , 0 , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 2 , 2 , 1 , 2 , 2 ,
    2 , 3 , 4 , 1 , 1 , 0 , 0 , 1 , 1 , 1 , 2 , 1 , 0 , 1 , 3 , 2 , 3 , 2 , 5 ,
    1 , 4 , 4 , 4 , 2 , 6 , 0 , 0 , 1 , 0 , 2 , 0 , 0 , 0 , 4 , 0 , 2 , 3 , 6 ,
    7 , 3 , 9 , 8 , 3 , 3 , 4 , 4 , 0 , 0 , 2 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 3 ,
    2 , 3 , 4 , 3 , 4 , 2 , 4 , 2 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,
    1 , 0 , 0 , 2 , 2 , 1 , 3 , 2 , 1 , 0 , 2 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 ,
    1 , 2 , 0 , 5 , 5 , 5 , 0 , 1 , 2 , 5 , 2 , 2 , 0 , 0 , 1 , 0 , 1 , 0 , 0 ,
    0 , 4 , 1 , 1 , 4 , 2 , 1 , 3 , 4 , 2 , 3 , 1 , 2 , 2 , 2 , 6 , 0 , 0 , 1 ,
    1 , 0 , 0 , 3 , 4 , 1 , 2 , 5 , 4 , 3 , 2 , 2 , 3 , 2 , 3 , 2 , 0 , 0 , 0 ,
    1 , 1 , 0 , 1 , 1 , 1 , 1 , 2 , 4 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 0 ,
    1 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 1 , 0 , 0 , 0 , 0 ,
    0 , 0 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 0 , 3 , 1 , 2 , 1 , 4 , 1 , 2 , 1 , 0 ,
    1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 0 , 1 , 0 , 1 , 3 , 1 , 2 ,
    2 , 1 , 1 , 1 , 2 , 3 , 3 , 0 , 4 , 2 , 0 , 1 , 1 , 1 , 2 , 2 , 6 , 4 , 3 ,
    1 , 1 , 0 , 2 , 2 , 3 , 1 , 0 , 3 , 2 , 5 , 4 , 1 , 3 , 3 , 4 , 1 , 1 , 4 ,
    7 , 4 , 2 , 5 , 2 , 3 , 4 , 4 , 3 , 2 , 4 , 3 , 3 , 4 , 6 , 1 , 7 , 3 , 7 ,
    5 , 14 , 12 , 8 , 15 , 9 , 8 , 8 , 5 , 6 , 3 , 5 , 1 , 2 , 3 , 2 , 5 , 5 , 2
    , 2 , 4 , 2 , 2 , 5 , 0 , 4 , 0 , 3 , 1 , 3 , 1 , 4 , 2 , 6 , 5 , 1 , 1 , 5
    , 6 , 4 , 3 , 3 , 6 , 3 , 3 , 1 , 4 , 3 , 1 , 2 , 1 , 4 , 4 , 6 , 5 , 2 , 2
    , 2 , 4 , 4 , 3 , 1 , 3 , 3 , 4 , 0 , 1 , 0 , 1 , 2 , 2 , 0 , 1 , 0 , 2 , 0
    , 0 , 1 , 0 , 1 , 0 , 0 , 1 , 2 , 0 , 3 , 3 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 2 , 0 , 1 , 2 , 0 , 0 , 4 , 1 , 5 , 1 , 2 , 0 , 1 , 0 , 2
    , 3 , 7 , 12 , 14 , 35 , 55 , 94 , 157 , 262 , 428 , 615 , 876 , 1264 , 1567
    , 1782 , 1791 , 2002 , 2631 , 4030 , 6596 , 9033 , 10207 , 9694 , 6994 ,
    3510 , 1407 , 416 , 96 , 11 , 3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
};

BOOST_AUTO_TEST_SUITE(test_fio_reader)

BOOST_AUTO_TEST_CASE(test_single_column_file)
{
	pni::fio_reader reader("scan_mca_00001.fio");
	BOOST_CHECK(reader.nparameters() == 101);
	BOOST_CHECK(reader.parameter<int>("EH1_MOT12") == -6);
	BOOST_CHECK_CLOSE(reader.parameter<float>("OH2_400TH"),0.01438125,0.0001);

	BOOST_CHECK(reader.ncolumns() == 1);
	BOOST_CHECK(reader.nrecords() == 2048);
	BOOST_CHECK(reader.has_column("SCAN_MCA_00001_EXP_MCA01"));

	auto data = reader.column<std::vector<int>>("SCAN_MCA_00001_EXP_MCA01");
	BOOST_CHECK(data.size() == single_column.size());
	auto data_iter = data.begin();
	auto ref_iter  = single_column.begin();
	size_t index=0;
	for(;data_iter!=data.end();++data_iter,++ref_iter,index++)
	{
		BOOST_CHECK(*data_iter == *ref_iter);
	}

}

BOOST_AUTO_TEST_CASE(test_multi_column_file)
{
	using container_type = std::vector<double>;
	pni::fio_reader reader("tstfile_00012.fio");
	BOOST_CHECK(reader.nparameters() == 4);
	BOOST_CHECK(reader.parameter<pni::string>("sweepMotor") == "eh1b_mot04");
	BOOST_CHECK_CLOSE(reader.parameter<float>("sweepOffset"),0.005,0.0001);

	BOOST_CHECK(reader.ncolumns() == 14);
	BOOST_CHECK(reader.nrecords() == 2001);

	BOOST_CHECK(reader.has_column("tstfile_00012_pos"));
	auto data = reader.column<container_type>("tstfile_00012_pos");
	BOOST_CHECK(data.size() == tstfile_00012_pos.size());
	auto data_iter = data.begin();
	auto ref_iter  = tstfile_00012_pos.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);


	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c01"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c01");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c01.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c01.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c02"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c02");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c02.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c02.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c03"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c03");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c03.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c03.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c04"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c04");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c04.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c04.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c05"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c05");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c05.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c05.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c06"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c06");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c06.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c06.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c07"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c07");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c07.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c07.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c08"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c08");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c08.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c08.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c09"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c09");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c09.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c09.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c10"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c10");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c10.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c10.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_eh1b_c32"));
	data = reader.column<container_type>("tstfile_00012_eh1b_c32");
	BOOST_CHECK(data.size() == tstfile_00012_eh1b_c32.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_eh1b_c32.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_corr"));
	data = reader.column<container_type>("tstfile_00012_corr");
	BOOST_CHECK(data.size() == tstfile_00012_corr.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_corr.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);

	BOOST_CHECK(reader.has_column("tstfile_00012_deltaPos"));
	data = reader.column<container_type>("tstfile_00012_deltaPos");
	BOOST_CHECK(data.size() == tstfile_00012_deltaPos.size());
	data_iter = data.begin();
	ref_iter  = tstfile_00012_deltaPos.begin();
	for(;data_iter!=data.end();++data_iter,++ref_iter)
		BOOST_CHECK_CLOSE(*data_iter,*ref_iter,0.0001);
}


BOOST_AUTO_TEST_SUITE_END()




