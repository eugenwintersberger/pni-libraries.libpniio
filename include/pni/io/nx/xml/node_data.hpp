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

#include "../../parsers/exceptions.hpp"
#include "../nexus_utils.hpp"
#include <pni/core/array.hpp>
#include "xml_node.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    /*!
    \ingroup xml_lowlevel_utils
    \brief xml data reader

    This class template provides a static reader function to retrieve the data
    stored in an XML node. The template parameter type determines the data type
    as which the XML data should be interpreted. 
    This template is the default implementation supporting virtually all POD
    data types. The reader was implemented as a template class to allow
    specialization of the reader type for more exotic data types to be read from
    the node.

    \tparam T data type of XML data
    */ 
    template<typename T> struct node_data
    {
        /*!
        \brief read data from an XML node

        This function retrieves the data stored in an XML node as an instance of
        type T. An exception is thrown in case of errors. 

        \throws parser_error 
        \param node node from which to read data
        \return instance of T with the data
        */
        static T read(const xml::node &node)
        {
            T value;
            try
            {
                value = node.template get_value<T>();
            }
            catch(boost::property_tree::ptree_bad_data &error)
            {
                type_id_t id = type_id_map<T>::type_id;
                auto buffer = node.template get_value<string>();
                throw parser_error(EXCEPTION_RECORD,
                        "Node data \""+buffer+"\" cannot be converted to"
                        +typeid2str[id]+"!");
            }
            catch(...)
            {
                auto buffer = node.template get_value<string>();
                throw parser_error(EXCEPTION_RECORD,
                        "Unknown error when parsing node data \""+buffer+"\"!");
            }

            return value;
        }

    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief read array data from a node

    This is a specialization of the node_data<T> template allowing the user to
    read array data from an XML node and store it in an instance of the array
    type erasure. 
    
    In general the only assumption the provided functions make is that the data
    is stored as a homogeneous type. Separators and start-stop-symbols can be
    individually configured if required. 
    */
    template<> struct node_data<array>
    {
        //!< iterator type for parsing array data
        typedef string::const_iterator iterator_t;
        //!< parser type 
        typedef pni::io::array_parser<iterator_t> array_parser_t;

        /*!
        \brief reading array data

        Reading array data from a string without start and stop character but
        with a single element separator.

        \param node XML node to read data from
        \param sep separator character.
        \return array with data
        */
        static array read(const xml::node &node,char sep);

        //---------------------------------------------------------------------
        /*!
        \brief reading array data

        Reading array data not only using a separator character but also a start
        and a stop character. 

        \param node XML node where to read data from
        \param start start symbol for the array
        \param stop stop symbol for the array
        \param sep element separator symbol
        \return instance of array with node data
        */
        static array read(const xml::node &node,char start,char stop,char sep);

        //---------------------------------------------------------------------
        /*!
        \brief reading array data

        Read array data using a custom reader. In this case you can setup the
        parser in your own code.

        \param node XML node from which to read data
        \param p parser 
        \return array with node data
        */
        static array read(const xml::node &node,const array_parser_t &p);
    };


    //-------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief check node data

    Returns true if a node contains any data. False otherwise.
    \param n node instance
    \return true if node contains data, false otherwise
    */
    bool has_data(const node &n);



//end of namespace
}
}
}
}
