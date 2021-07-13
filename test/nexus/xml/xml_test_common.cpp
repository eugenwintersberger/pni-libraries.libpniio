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
#include <pni/types.hpp>
#include <pni/nexus/xml/node.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace pni::io::nexus;
using namespace pni::core;

namespace std{
    
//    ostream &operator<<(ostream &stream,const xml::Node &n)
//    {
//        using boost::property_tree::ptree;
//        boost::property_tree::write_xml(stream,dynamic_cast<const ptree&>(n));
//        return stream;
//    }
}


bool compare_trees(const xml::Node &,const xml::Node &)
{

    return true;
}
