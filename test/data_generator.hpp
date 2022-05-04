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
//************************************************************************
//
//  Created on: Jan 21, 2013
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#pragma once

#include <sstream>
#include <pni/types.hpp>
#include <boost/lexical_cast.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

#ifdef NOCPPRAND
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#else
#include <random>
#endif

using namespace pni;

//=============we need different distributions for integer and float============
template<typename GeneralT,bool is_int> struct distribution_map;

//------------distribution for integral types-----------------------------------
template<typename GeneralT> struct distribution_map<GeneralT,true>
{
    typedef std::uniform_int_distribution<GeneralT> distribution_type;
};

#ifdef _MSC_VER
template<> struct distribution_map<uint8, true>
{
	typedef std::uniform_int_distribution<uint16> distribution_type;
};

template<> struct distribution_map<int8, true>
{
	typedef std::uniform_int_distribution<int16> distribution_type;
};
#endif

//------------------distribution for floating point types-----------------------
template<typename GeneralT> struct distribution_map<GeneralT,false>
{
    typedef std::uniform_real_distribution<GeneralT> distribution_type;
};

//=================the default generator=======================================
template<typename GeneralT> class random_generator
{
    private:
        std::mt19937_64 _engine;
		typedef distribution_map<GeneralT, pni::type_info<GeneralT>::is_integer> map_t;
        typename map_t::distribution_type _distribution;

    public:
        random_generator(GeneralT a,GeneralT b):
            _engine(std::random_device()()),
            _distribution(a,b)
        {}

        random_generator():
            _engine(std::random_device()()),
#ifdef _MSC_VER
// the bounds are computed as doubles due to the 0.2 prefactors. 
// However, for an interger random generator these values will be converted 
// back to an integer which most naturally causes some loss of information. 
// Anyhow for our purpose this is ok and we can safely ignore the 
// warning of MSVC.
#pragma warning(disable:4244)
#endif
            _distribution(0.2*pni::type_info<GeneralT>::min(),
				          0.2*pni::type_info<GeneralT>::max())
        {}
#ifdef _MSC_VER
#pragma warning(default:4244)
#endif

        GeneralT operator()()
        {
            return _distribution(_engine);
        }
};

#ifdef _MSC_VER
template<> class random_generator<uint8>
{
    private:        
        random_generator<uint16> _generator;

	public:
		random_generator(uint8 a,uint8 b):
			_generator(uint16(a),uint16(b))
		{}

		random_generator():
			_generator(0,255)
		{}

		uint8 operator()()
		{
			return uint8(_generator());
		}
};

template<> class random_generator<int8>
{
private:
	random_generator<int16> _generator;

public:
	random_generator(int8 a, int8 b) :
		_generator(int16(a), int16(b))
	{}

	random_generator() :
		_generator(-127,127)
	{}

	int8 operator()()
	{
		return int8(_generator());
	}
};
#endif
//--------------------------------------			----
template<typename GeneralT> class random_generator<std::complex<GeneralT>>
{
    private:
        typedef pni::type_info<GeneralT> tinfo_type;
        random_generator<GeneralT> _real_generator;
       	random_generator<GeneralT> _imag_generator;
    public:
        random_generator(GeneralT a,GeneralT b):
            _real_generator(a,b),
            _imag_generator(a,b)
        {}

        random_generator():
            _real_generator(),
            _imag_generator()
        {}
        
        std::complex<GeneralT> operator()()
        {
            return std::complex<GeneralT>(_real_generator(),
                                   _imag_generator());
        }
};

//-----------------------------------------------------------------------------
template<> class random_generator<bool_t>
{
    private:
        random_generator<unsigned short> _generator;
    public:

        random_generator();

        bool_t operator()();
};

//-----------------------------------------------------------------------------
template<> class random_generator<hdf5::datatype::EBool>
{
    private:
        random_generator<unsigned short> _generator;
    public:

        random_generator();

        hdf5::datatype::EBool operator()();
};

//-----------------------------------------------------------------------------
//!
//! \brief generating random strings
//! 
//! This random number generator
template<> class random_generator<string>
{
    private:
        static const std::vector<char> _char_vector ;
        random_generator<size_t> _line_size_generator;
        random_generator<size_t> _char_index_generator;
    public:
        random_generator(size_t nchars);

        random_generator();

        string operator()();
};


//-----------------------------------------------------------------------------
//!
//! \brief binary random generator
//!
//! Generates random binary values. These values are unsigned integers between
//! 0 and 255. Due to its simple nature the generator has no customizable 
//! constructor.
//! 
template<> class random_generator<binary>
{
    private:
        random_generator<uint8> _generator;
    public:
        random_generator():
            _generator(0,255)
        {}

        binary operator()()
        {
            return binary(_generator());
        }
};
    
