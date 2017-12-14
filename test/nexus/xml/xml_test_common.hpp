//
// (c) Copyright 2015 DESY,Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// ===========================================================================
#pragma once

#include <fstream>
#include <pni/io/nexus/xml/node.hpp>

namespace std{

//    ostream &operator<<(ostream &stream,const pni::io::nexus::xml::Node &n);
    
}

bool compare_trees(const pni::io::nexus::xml::Node &a,
                   const pni::io::nexus::xml::Node &b);
