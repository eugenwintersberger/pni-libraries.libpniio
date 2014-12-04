//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 16, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/xml/attribute_data.hpp>
#include <boost/algorithm/string.hpp>
#include <pni/io/exceptions.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    attribute_data::attribute_data(const string &name):
        object_data(),
        _name(name)
    {}

    //-------------------------------------------------------------------------
    string attribute_data::read(const node &n) const
    {
        try
        {
            string data =  n.get<string>(attribute_path(_name));
            boost::algorithm::trim(data);
            return data;
        }
        catch(boost::property_tree::ptree_bad_path &error)
        {
            throw key_error(EXCEPTION_RECORD,
                    "Attribute ("+_name+") does not exist!");
        }
        catch(boost::property_tree::ptree_bad_data &error)
        {
            throw pni::core::value_error(EXCEPTION_RECORD,
                    "Malformed data - cannot read attribute!");
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Unknown error when reading attribute!");
        }
    }

    //-------------------------------------------------------------------------
    void attribute_data::write(const string &data,node &n) const
    {
        try
        {
            n.put<string>(attribute_path(_name),data);
        }
        catch(boost::property_tree::ptree_bad_data &error)
        {
            throw pni::core::value_error(EXCEPTION_RECORD,
                    "Malformed data - cannot write attribute!");
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Unkown error during writing attribute!");
        }
    }
    
//end of namespace
}
}
}
}
