/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jul 15, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include "xml_node.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    /*!
    \ingroup xml_lowlevel_utils
    \brief XML attribute data

     
    */
    template<typename T> struct attribute_data
    {
        /*!
        \brief read an XML attribute from a node

        Reads an attribute from an XML node and returns it as a value of type T. 
        If the attribute string cannot be converted to T or the node does not
        posses this attribute an exception will be thrown. 
       
        \throws parser_error in case of errors
        \tparam T value type 
        \param n node instancen
        \param a name of the attribute
        \return attribute value as instance of T
        */
        static T read(const node &n,const string &a)
        {
            T value;
            try
            {
                value = n.get<T>("<xmlattr>."+a);
            }
            catch(...)
            {
                throw pni::io::parser_error(EXCEPTION_RECORD,
                        "Attribute '"+a+"' does not exist or has inappropriate"
                        " value!");
            }

            return value;
        }
    };


//end of namespace
}
}
}
}
