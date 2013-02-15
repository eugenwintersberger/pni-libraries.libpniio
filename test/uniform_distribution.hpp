/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpnicore is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpnicore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Feb 15, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/type_info.hpp>

#ifdef NOCPPRAND
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#endif

using namespace pni::core;

template<typename T,bool is_int> struct uniform_distribution_map;

template<typename T> struct uniform_distribution_map<T,true>
{
#ifdef NOCPPRAND
    typedef boost::uniform_int<T> distribution_type;
#else
    typedef std::uniform_int_distribution<T> distribution_type;
#endif
};

template<typename T> struct uniform_distribution_map<T,false>
{
#ifdef NOCPPRAND
    typedef boost::uniform_real<T> distribution_type;
#else
    typedef std::uniform_real_distribution<T> distribution_type;
#endif
};

template<typename T> class uniform_distribution
{
    private:
#ifdef NOCPPRAND
        boost::mt19937 _engine;
#else
        std::mt19937_64 _engine;
#endif
        typename uniform_distribution_map<T,type_info<T>::is_integer>::distribution_type _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0.2*type_info<T>::min(),0.2*type_info<T>::max())
        { }

        T operator()() 
        {
            return _distribution(_engine);
        }
};

template<typename T> class uniform_distribution<std::complex<T> >
{
    private:
#ifdef NOCPPRAND
        boost::mt19937 _engine;
#else
        std::mt19937_64 _engine;
#endif
        typename uniform_distribution_map<T,type_info<T>::is_integer>::distribution_type _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0.2*type_info<float32>::min(),0.2*type_info<float32>::max())
        {}
        
        std::complex<T> operator()()
        {
            return std::complex<T>(_distribution(_engine),
                                   _distribution(_engine));
        }
};

template<> class uniform_distribution<bool>
{
    private:
#ifdef NOCPPRAND
        boost::mt19937 _engine;
        boost::uniform_int<> _distribution;
#else
        std::mt19937_64 _engine;
        std::uniform_int_distribution<> _distribution;
#endif
    public:
        uniform_distribution():
            _engine(),
            _distribution(0,1)
        {}

        Bool operator()()
        {
            return _distribution(_engine);
        }
};

template<> class uniform_distribution<binary>
{
    private:
#ifdef NOCPPRAND
        boost::mt19937 _engine;
        boost::uniform_int<uint8> _distribution;
#else
        std::mt19937_64 _engine;
        std::uniform_int_distribution<uint8> _distribution;
#endif
    public:
        uniform_distribution():
            _engine(),
            _distribution(0,255)
        {}

        binary operator()() 
        {
            return _distribution(_engine);
        }
};

template<> class uniform_distribution<string>
{
    private:
        uniform_distribution<unsigned long> _distribution;
    public:
        uniform_distribution(){}

        string operator()()
        {
            std::stringstream ss;
            ss<<_distribution();
            return ss.str();
        }
};

