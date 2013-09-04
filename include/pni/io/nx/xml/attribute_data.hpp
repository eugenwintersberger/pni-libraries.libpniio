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

#include <pni/core/types.hpp>
#include <pni/core/array.hpp>
#include "../../parsers/array_parser.hpp"
#include "../../parsers/exceptions.hpp"
#include "xml_node.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    /*!
    \ingroup xml_lowlevel_utils
    \brief XML attribute data

    Provide a single static read method to read data from an attribute.
    There is currently an issue with unsigned data types that produce an
    overflow wen parsing a number with a negative sign. This should be fixed
    in future. See issue #26.
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
            catch(boost::property_tree::ptree_bad_path &error)
            {
                throw pni::io::parser_error(EXCEPTION_RECORD,
                        "Attribute \""+a+"\" does not exist!");
            }
            catch(boost::property_tree::ptree_bad_data &error)
            {
                throw pni::io::parser_error(EXCEPTION_RECORD,
                        "Error parsing attribute \""+a+"\"!");
            }
            catch(...)
            {
                throw pni::io::parser_error(EXCEPTION_RECORD,
                        "Unknown error during parsing of attribute \""+a+"\"!");
            }

            return value;
        }
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief read array data from attribute

    Provide several static methods to read array data from an attribute. 
    */
    template<> struct attribute_data<array>
    {
        
        //! iterator type for parsing array data
        typedef string::const_iterator iterator_t;
        //! parser type 
        typedef pni::io::array_parser<iterator_t> array_parser_t;

        /*!
        \brief reading array data

        Reading array data from a string without start and stop character but
        with a single element separator.

        \param n XML node holding the attribute
        \param name name of the attribute
        \param sep separator character.
        \return array with data
        */
        static array read(const node &n,const string &name,char sep);

        //---------------------------------------------------------------------
        /*!
        \brief reading array data

        Reading array data not only using a separator character but also a start
        and a stop character. 

        \param n XML node holding theattribute
        \param name name of the attribute to read data from
        \param start start symbol for the array
        \param stop stop symbol for the array
        \param sep element separator symbol
        \return instance of array with node data
        */
        static array read(const node &n,const string &name,
                          char start,char stop,char sep);

        //---------------------------------------------------------------------
        /*!
        \brief reading array data

        Read array data using a custom reader. In this case you can setup the
        parser in your own code.

        \param n XML node from which to read data
        \param name attribute name
        \param p parser 
        \return array with node data
        */
        static array read(const node &n,const string &name,
                          const array_parser_t &p);

    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief check for attributes existance

    Returns true if an attribute exists on a node. 
    \param n node instance 
    \param name name of the attribute
    \return true if attribute exists, false otherwise
    */
    bool has_attribute(const node &n,const string &name) ;

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief check if an attribute has non-empty data

    Returns true if the attribute contains data. Use this function in order to
    check if one should read data or not.
    \param n node holding the attribute
    \param name name of the attribute
    \return true if attribute contains data, false otherwise
    */
    bool has_data(const node &n,const string &name);


//end of namespace
}
}
}
}
