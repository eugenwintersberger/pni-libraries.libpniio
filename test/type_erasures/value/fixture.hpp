//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Createyd on: Oct 17, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once
#include "../../data_generator.hpp"


template<typename T> struct fixture
{   
    typedef random_generator<T> generator_type;
    generator_type generator;
    T value_1;
    T value_2;

    fixture(T lbound=1,T ubound=10):
        generator(lbound,ubound),
        value_1(generator()),
        value_2(generator())
    {}
};

template<typename T> struct fixture<std::complex<T>>
{   
    typedef random_generator<T> generator_type;
    generator_type generator;
    std::complex<T> value_1;
    std::complex<T> value_2;

    fixture(T lbound=1,T ubound=10):
        generator(lbound,ubound),
        value_1(generator()),
        value_2(generator())
    {}
};

template<> struct fixture<binary>
{
    typedef random_generator<binary> generator_type;
    generator_type generator;
    binary value_1;
    binary value_2;

    fixture():
        generator(),
        value_1(generator()),
        value_2(generator())
    {}

};

template<> struct fixture<string>
{
    typedef random_generator<string> generator_type;
    generator_type generator;
    string value_1;
    string value_2;

    fixture(size_t nchars=20):
        generator(nchars),
        value_1(generator()),
        value_2(generator())
    {}

};

template<> struct fixture<bool_t>
{
    typedef random_generator<bool_t> generator_type;
    generator_type generator;
    bool_t value_1;
    bool_t value_2;

    fixture():
        generator(),
        value_1(generator()),
        value_2(generator())
    {}

};



