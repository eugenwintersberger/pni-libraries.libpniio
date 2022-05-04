//
// (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
//
//  Created on: Feb 15, 2013
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
///
#pragma once

#include <sstream>
#include <random>
#include <pni/types.hpp>
#include <hdf5/contrib/nexus/ebool.hpp>
#include <random>

using namespace pni;

//----------------------------------------------------------------------------
template<typename GeneralT,bool is_int> struct uniform_distribution_map;

//----------------------------------------------------------------------------
template<typename GeneralT> struct uniform_distribution_map<GeneralT,true>
{
    typedef std::uniform_int_distribution<GeneralT> distribution_type;
};

//----------------------------------------------------------------------------
template<typename GeneralT> struct uniform_distribution_map<GeneralT,false>
{
    typedef std::uniform_real_distribution<GeneralT> distribution_type;
};

//----------------------------------------------------------------------------
template<typename GeneralT>
using uniform_dist_map = uniform_distribution_map<GeneralT,pni::type_info<GeneralT>::is_integer>;

//----------------------------------------------------------------------------
template<typename GeneralT> class uniform_distribution
{
    private:
        std::mt19937_64 _engine;
        typename uniform_dist_map<GeneralT>::distribution_type _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0.2*pni::type_info<GeneralT>::min(),
                          0.2*pni::type_info<GeneralT>::max())
        {
            _engine.seed(std::random_device()());
        }

        GeneralT operator()()
        {
            return _distribution(_engine);
        }
};

//----------------------------------------------------------------------------
template<typename GeneralT> class uniform_distribution<std::complex<GeneralT> >
{
    private:
        std::mt19937_64 _engine;
        typename uniform_dist_map<GeneralT>::distribution_type _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0.2*pni::type_info<float32>::min(),
                          0.2*pni::type_info<float32>::max())
        {
            _engine.seed(std::random_device()());
        }

        std::complex<GeneralT> operator()()
        {
            return std::complex<GeneralT>(_distribution(_engine),
                                   _distribution(_engine));
        }
};

//----------------------------------------------------------------------------
template<> class uniform_distribution<bool_t>
{
    private:
        std::mt19937_64 _engine;
        std::uniform_int_distribution<> _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0,1)
        {
            _engine.seed(std::random_device()());
        }

        bool_t operator()()
        {
            return _distribution(_engine)!=0;
        }
};

//----------------------------------------------------------------------------
template<> class uniform_distribution<hdf5::datatype::EBool>
{
    private:
        std::mt19937_64 _engine;
        std::uniform_int_distribution<> _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0,1)
        {
            _engine.seed(std::random_device()());
        }

        hdf5::datatype::EBool operator()()
        {
            return hdf5::datatype::EBool(distribution(_engine)!=0);
        }
};

#ifdef _MSC_VER
//----------------------------------------------------------------------------
template<> class uniform_distribution<pni::uint8>
{
    private:
        std::mt19937_64 _engine;
        std::uniform_int_distribution<pni::uint16> _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0,255)
        {
            _engine.seed(std::random_device()());
        }

        pni::uint8 operator()()
        {
            return _distribution(_engine)!=0;
        }
};

template<> class uniform_distribution<pni::int8>
{
    private:
        std::mt19937_64 _engine;
        std::uniform_int_distribution<pni::int16> _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(-127,128)
        {
            _engine.seed(std::random_device()());
        }

        pni::int8 operator()()
        {
            return _distribution(_engine)!=0;
        }
};

#endif


//----------------------------------------------------------------------------
template<> class uniform_distribution<binary>
{
    private:
        std::mt19937_64 _engine;
        std::uniform_int_distribution<uint16> _distribution;
    public:
        uniform_distribution():
            _engine(),
            _distribution(0,255)
        {
            _engine.seed(std::random_device()());
        }

        binary operator()()
        {
            return _distribution(_engine);
        }
};

//----------------------------------------------------------------------------
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
