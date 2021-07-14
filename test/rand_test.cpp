/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pninexus.
 *
 * pninexus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pninexus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Oct 29, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

//program to test random number sequences

#include <vector>
#include <boost/lexical_cast.hpp>

#include <pni/types.hpp>
#include <pni/configuration.hpp>


#include "data_generator.hpp"

using namespace pni;

template<typename T> struct bound_type
{
    typedef T type;
};

template<typename T> struct bound_type<std::complex<T>>
{
    typedef T type;
};

template<> struct bound_type<string>
{
    typedef unsigned long type;
};

template<typename GT> void execute(size_t n,GT &&g)
{
    for(size_t i=0;i<n;i++) std::cout<<g()<<std::endl;
}

template<typename T> struct generator_builder
{
    static random_generator<T> build(T lbound,T ubound)
    {
        return random_generator<T>(lbound,ubound);
    }
};

template<typename T> struct generator_builder<std::complex<T>>
{
    static random_generator<std::complex<T>> build(T lbound,T ubound)
    {
        return random_generator<std::complex<T>>(lbound,ubound);
    }
};

template<> struct generator_builder<string>
{
    static random_generator<string> build(size_t nchars)
    {
        return random_generator<string>(nchars);
    }
};

template<> struct generator_builder<bool_t>
{
    static random_generator<bool_t> build()
    {
        return random_generator<bool_t>();
    }
};

template<> struct generator_builder<binary>
{
    static random_generator<binary> build()
    {
        return random_generator<binary>();
    }
};



int main(int argc,char **argv)
{
    configuration config;
    config.add_option(config_option<string>("type","t",
                "data type to use","float32"));
    config.add_option(config_option<size_t>("nruns","n",
                "number of random numbers to generate",1));
    config.add_option(config_option<string>("lower-bound","l",
                "lower bound of the distribution",string()));
    config.add_option(config_option<string>("upper-bound","u",
                "upper bound of the distribution",string()));
    
    parse(config,cliargs2vector(argc,argv));
    
    size_t nruns = config.value<size_t>("nruns");
    type_id_t type_id  = type_id_from_str(config.value<string>("type"));
    auto a = config.value<string>("lower-bound");
    auto b = config.value<string>("upper-bound");


    switch(type_id)
    {
        case type_id_t::INT32: 
            execute(nruns,generator_builder<int32>::build(boost::lexical_cast<int32>(a),
                                                   boost::lexical_cast<int32>(b)));
            break;
        case type_id_t::UINT32:
            execute(nruns,generator_builder<uint32>::build(boost::lexical_cast<uint32>(a),
                                                    boost::lexical_cast<uint32>(b)));
            break;

        case type_id_t::INT64:
            execute(nruns,generator_builder<int64>::build(boost::lexical_cast<int64>(a),
                                                   boost::lexical_cast<int64>(b)));
            break;
        case type_id_t::UINT64:  
            execute(nruns,generator_builder<uint64>::build(boost::lexical_cast<uint64>(a),
                                                    boost::lexical_cast<uint64>(b)));
            break;
        case type_id_t::FLOAT32: 
            execute(nruns,generator_builder<float32>::build(boost::lexical_cast<float32>(a),
                                                     boost::lexical_cast<float32>(b)));
            break;
        case type_id_t::FLOAT64: 
            execute(nruns,generator_builder<float64>::build(boost::lexical_cast<float64>(a),
                                                     boost::lexical_cast<float64>(b)));
            break;
        case type_id_t::FLOAT128: 
            execute(nruns,generator_builder<float128>::build(boost::lexical_cast<float128>(a),
                                                      boost::lexical_cast<float128>(b)));
            break;
        case type_id_t::COMPLEX32: 
            execute(nruns,generator_builder<complex32>::build(boost::lexical_cast<float32>(a),
                                                       boost::lexical_cast<float32>(b)));
            break;
        case type_id_t::COMPLEX64: 
            execute(nruns,generator_builder<complex64>::build(boost::lexical_cast<float64>(a),
                                                       boost::lexical_cast<float64>(b)));
            break;
        case type_id_t::COMPLEX128: 
            execute(nruns,generator_builder<complex128>::build(boost::lexical_cast<float128>(a),
                                                        boost::lexical_cast<float128>(b)));
            break;
        case type_id_t::STRING: 
            execute(nruns,generator_builder<string>::build(boost::lexical_cast<size_t>(a)));
            break; 
        case type_id_t::BOOL: 
            execute(nruns,generator_builder<bool_t>::build());
            break;
        default:
            std::cerr<<"Unknown data type!"<<std::endl;
            return -1;
    }

    return 0;
}
