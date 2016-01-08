//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// ===========================================================================
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/io/nx/nx.hpp>
#include "../uniform_distribution.hpp"
#include "../base_fixture.hpp"

struct nxfield_test_fixture : base_fixture
{
    static const pni::core::shape_t default_shape;
    static const size_t default_size;

    nxfield_test_fixture(const pni::core::string &filename):
        base_fixture(filename)
    {}

    virtual ~nxfield_test_fixture() {} 

    template<typename T> 
    pni::io::nx::h5::nxfield create_field(const pni::core::string &field_name,
                                          const pni::core::shape_t &s) const
    {
        return root.create_field<T>(field_name,s);
    }

    template<typename T> 
    pni::core::dynamic_array<T> create_array(const pni::core::shape_t &s) const
    {
        return pni::core::dynamic_array<T>::create(s);
    }

    template<typename T>
    pni::core::dynamic_array<T> create_random_array(const pni::core::shape_t &s) const
    {
        auto a = create_array<T>(s);
        std::generate(a.begin(),a.end(),uniform_distribution<T>());
        return a;
    }

    template<typename T>
    T create_random_scalar() const
    {
        uniform_distribution<T> rand_dist;
        return rand_dist();
    }

    template<typename T> 
    std::vector<T> create_buffer(size_t size) const
    {
        return std::vector<T>(size);
    }

    template<typename T> 
    std::vector<T> create_random_buffer(size_t size) const
    {
        auto b = create_buffer<T>(size);
        std::generate(b.begin(),b.end(),uniform_distribution<T>());
        return b;
    }

};
