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
 * Created on: Jul 11, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/core/types.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    /*!
    \ingroup xml_lowlevel_utils
    \brief alias for ptree

    This alias creates the new type name node which can be used within the xml
    namespace instread of boost::property_tree::ptree;
    */
    using node = boost::property_tree::ptree;

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create xml node from string

    \throws parser_error in case of parsing problems
    \param s string from which to read the data
    \return node instance
    */
    node create_from_string(const string &s);

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create xml node from file

    \throws pni::io::parser_error in case of parsing issues
    \throws file_error in case of problems opening the file
    \param s name of the file
    \return node instance
    */
    node create_from_file(const string &s);

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief XML stream output

    Write property tree structure as XML to an output stream.
    */
    std::ostream &operator<<(std::ostream &o,const node &n);


//end of namespace
}
}
}
}
