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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================


#include <pni/core/types.hpp>
#include <pni/core/nx.hpp>
#include <vector>

struct base_fixture
{
    pni::io::nx::h5::nxfile file;
    pni::io::nx::h5::nxgroup root;

    nxlowlevel_fixture(const pni::core::string &fname);
    virtual ~nxlowlevel_fixture(); 
};


template<typename T>
struct nxfield_io_fixture
