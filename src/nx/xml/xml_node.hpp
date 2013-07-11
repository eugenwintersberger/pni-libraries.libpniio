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

#include <iostream>
#include <sstream>
#include <fstream>
#include <pni/core/types.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    /*!
    \ingroup xml_lowlevel_utils
    \brief basic xml node

    This template represents an XML node that is used for all XML routines. 
    It is currently a very thin wrapper around boost::property_tree::ptree. 
    However, in cases where this library will no longer be maintained an
    alternative could be easily developed. 

    */
    template<typename ITYPE> class basic_node
    {
        public:
            typedef basic_node<ITYPE> node_type;
            typedef typename ITYPE::iterator iterator;
            typedef typename ITYPE::const_iterator const_iterator;
        private:
            ITYPE _imp;
        public:
            /*!
            \brief constructor

            The standard constructor using an input stream to parse the data. 
            \param s input stream
            */
            basic_node(std::istream &s)
            {
                boost::property_tree::read_xml(s,_imp);
            }

            //===============static creation functions=========================
            /*!
            \brief create node from string

            \param s string with XML data
            \return instance of node_type
            */
            static node_type create_from_string(const string &s);

            //-----------------------------------------------------------------
            /*!
            \brief create node from file

            \param fname filename 
            \return instance of node_type
            */
            static node_type create_from_file(const string &fname);

            //=================public members==================================
            //! get node name
            string type() const;

            //-----------------------------------------------------------------
            /*! 
            \brief get node data

            returns the text-data stored in the node.
            \return data as string
            */
            string data() const;

            //-----------------------------------------------------------------
            //! get the number of children
            size_t size() const { return _imp.size(); }

            //! check if there are children at all
            bool empty() const { return _imp.empty(); }

        

    };

    //-------------------------------------------------------------------------
    template<typename ITYPE> 
    typename basic_node<ITYPE>::node_type
    basic_node<ITYPE>::create_from_string(const string &s)
    {
        std::stringstream stream(s);
        return node_type(stream);
    }

    //-------------------------------------------------------------------------
    template<typename ITYPE> 
    typename basic_node<ITYPE>::node_type
    basic_node<ITYPE>::create_from_file(const string &s)
    {
        std::ifstream stream(s);
        if(!stream.is_open())
            throw file_error(EXCEPTION_RECORD,
                    "Error opening "+s+" for reading!");
        return node_type(stream);
    }

    typedef basic_node<boost::property_tree::ptree> node;


//end of namespace
}
}
}
}
