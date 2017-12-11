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

#include <iostream>
#include <pni/core/types.hpp>
#include <pni/io/nexus/xml/node.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace pni::io::nexus;
using namespace pni::core;
using namespace boost::property_tree;

namespace std{
    
    ostream &operator<<(ostream &stream,const xml::Node &n)
    {
        write_xml(stream,n);
        return stream;
    }
}


bool compare_trees(const xml::Node &,const xml::Node &)
{

    return true;
}
