//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ============================================================================
//
//  Created on: Dec 27, 2012
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#include <boost/test/included/unit_test.hpp>
#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif
#include <boost/current_function.hpp>

#include <vector>
#include <list>

#include <pni/configuration/config_parser.hpp>
#include <pni/configuration/cli_args.hpp>

using namespace pni;

struct configuration_test_fixture
{
    configuration config_file;
    configuration config_cli;

    configuration_test_fixture()
    {
        config_file.add_option(config_option<size_t>("pninexus.nthreads","",
                               "number of threads"));

        config_cli.add_option(config_option<size_t>("nthreads","n",
                                                    "number of threads",3));
        config_cli.add_option(config_option<std::vector<size_t>>("nruns","r","number of runs"));
    }
    
};

BOOST_FIXTURE_TEST_SUITE(configuration_test,configuration_test_fixture)


//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_configfile)
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;

    parse(config_file,"pni.cfg");
    BOOST_CHECK_EQUAL((config_file.value<size_t>("pninexus.nthreads")),4u);

    configuration c = std::move(config_file);
    BOOST_CHECK_EQUAL((c.value<size_t>("pninexus.nthreads")),4u);

}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_configcli)
{
    std::cout<<BOOST_CURRENT_FUNCTION<<std::endl;
    std::vector<string> args{"-n4","-r1","-r4","-r10"};

    parse(config_cli,args);

    BOOST_CHECK_EQUAL(config_cli.value<size_t>("nthreads"),4u);

    auto o = config_cli.value<std::vector<size_t>>("nruns");
    BOOST_CHECK_EQUAL(o.size(),3u);
    BOOST_CHECK_EQUAL(o[0],1u);
    BOOST_CHECK_EQUAL(o[1],4u);
    BOOST_CHECK_EQUAL(o[2],10u);

    configuration conf;
    BOOST_CHECK_THROW(
    conf.add_option(config_option<std::vector<string>>("names","n",
                "user names",std::vector<string>{})),
    index_error);

    BOOST_CHECK_NO_THROW(
    conf.add_option(config_option<std::vector<string>>("names","n",
            "user names",std::vector<string>{"me"})));

}

BOOST_AUTO_TEST_SUITE_END()

