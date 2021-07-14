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
// ===========================================================================
//
//  Created on: Oct 22, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include <iomanip>
#include <pni/types.hpp>
#include <pni/configuration.hpp>
#include <boost/lexical_cast.hpp>

#include "data_generator.hpp"

using namespace pni;

template<typename T> struct formatter { };

template<typename T> 
std::ostream &operator<<(std::ostream &stream,const formatter<T> &)
{
    return stream;
}

template<> struct formatter<float32> {};

std::ostream &operator<<(std::ostream &stream,const formatter<float32> &)
{
    stream<<std::scientific<<std::setprecision(32);
    return stream;
}

template<> struct formatter<float64> {};

std::ostream &operator<<(std::ostream &stream,const formatter<float64> &)
{
    stream<<std::scientific<<std::setprecision(32);
    return stream;
}

template<> struct formatter<float128> {};

std::ostream &operator<<(std::ostream &stream,const formatter<float128> &)
{
    stream<<std::scientific<<std::setprecision(32);
    return stream;
}

template<typename GENT>
void output_numbers(size_t n,GENT &&generator)
{
    typedef decltype(generator()) value_type;
    typedef formatter<value_type> formatter_type; 

    formatter_type format;

    for(size_t index=0;index<n;index++)
        std::cout<<format<<generator()<<std::endl;
}

template<typename T>
void generate_numbers(size_t n,const string &lbound,const string &ubound)
{
    typedef random_generator<T> generator_type; 

    T lower_bound = pni::type_info<T>::min();
    T upper_bound = pni::type_info<T>::max();

    if(!lbound.empty())
        lower_bound = boost::lexical_cast<T>(lbound);

    if(!ubound.empty())
        upper_bound = boost::lexical_cast<T>(ubound);
    
    std::cerr<<"Produce numbers in the range of: ["
             <<lower_bound<<":"<<upper_bound<<"]"<<std::endl;
    output_numbers(n,generator_type(lower_bound,upper_bound));

}


int main(int argc,char **argv)
{
    configuration config;
    config.add_option(config_option<string>("type","t","data type","int32"));
    config.add_option(config_option<string>("lower-bound","l",
                                            "lower bound of the range",""));
    config.add_option(config_option<string>("upper-bound","u",
                                            "upper bound of the range",""));
    config.add_option(config_option<size_t>("counts","c",
                                            "number of numbers to generate",
                                            size_t(10)));

    parse(config,cliargs2vector(argc,argv));

    type_id_t tid = type_id_from_str(config.value<string>("type"));
    size_t n = config.value<size_t>("counts");
    string ubound = config.value<string>("upper-bound");
    string lbound = config.value<string>("lower-bound");

    switch(tid)
    {
        case type_id_t::UINT32: 
            generate_numbers<uint32>(n,lbound,ubound); break;
        case type_id_t::INT32:
            generate_numbers<int32>(n,lbound,ubound); break;
        case type_id_t::UINT16:
            generate_numbers<uint16>(n,lbound,ubound); break;
        case type_id_t::INT16:
            generate_numbers<int16>(n,lbound,ubound); break;
        case type_id_t::FLOAT32:
            generate_numbers<float32>(n,lbound,ubound); break;
        case type_id_t::FLOAT64:
            generate_numbers<float64>(n,lbound,ubound); break;
        case type_id_t::FLOAT128:
            generate_numbers<float128>(n,lbound,ubound); break;
        default:
            std::cerr<<"Unkown type "<<config.value<string>("type")<<std::endl;
            return 1;
    }

    return 0;
}
