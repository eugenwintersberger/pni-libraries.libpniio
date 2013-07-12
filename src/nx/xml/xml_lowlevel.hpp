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
 * Created on: Jul 8, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include <sstream>
#include <pni/core/types.hpp>
#include <pni/core/array.hpp>
#include "../nx.hpp"
#include "../nexus_utils.hpp"
#include "../nxobject_traits.hpp"
#include "../../parsers/exceptions.hpp"
#include "../../parsers/array_parser.hpp"


#include "xml_node.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
    //using namespace pni::io::nx;

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
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
    template<typename T> T read_xml_attribute(const node &n,const string &a)
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

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief read XML data from a node

    Reads the text data from an xml node and returns it as a string. This
    function is merely a wrapper around the data() method provided by node.
    Virtually it is only translating ptree exceptions to libpniio exceptions. 

    \throws parser_error in case of problems
    \param n node object
    \return string with data
    */
    template<typename T> T read_xml_data(const node &n)
    {
        T value;
        try
        {
            value = n.template get_value<T>();
        }
        catch(...)
        {
            throw parser_error(EXCEPTION_RECORD,
                    "Node data does not exist or if of incompatible type!");
        }
        return value;
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief read XML data to array

    Reads XML data to a numeric array. The elements can be separated either by
    blanks or by colons, or semicolons. However, if non of the separator
    characters worked an exception will be thrown. 

    \throws parser_error in case of any parsing problem
    \param n XML node from which to read data
    \return instance of array with the data
    */
    array read_xml_array_data(const node &n);

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create shape form dimensions tag

    Create a shape container from the dimensions tag in the XML file. 
    
    \throws parser_error in case of problems
    \throws shape_mismatch_error if rank attribute and number of 'dim' entries
    do not match
    \tparam CTYPE container type for the shape (default is shape_t)
    \param dims node instance to the dimensions tag
    \return instance of shape_t with the shapea
    */
    template<typename CTYPE = shape_t>
    CTYPE dim2shape(const node &dims)
    {
        auto rank = read_xml_attribute<size_t>(dims,"rank");
        CTYPE s(rank);

        //initialize the shape with zero
        std::fill(s.begin(),s.end(),0);

        size_t valid_indices = 0;
        for(auto dim: dims)
        {
            if(dim.first != "dim") continue; //omit all non 'dim' tags

            //reading the index attribute
            auto index = read_xml_attribute<size_t>(dim.second,"index");
            auto value = read_xml_attribute<size_t>(dim.second,"value");

            s[index-1] = value;
            valid_indices++;
        }

        if(valid_indices!=rank)
        {
            std::stringstream ss;
            ss<<"The value of rank ("<<rank<<") does not match that of";
            ss<<" the number of 'dim' tags ("<<valid_indices<<")!";
            throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
        }

        return s;
    }


    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create group from XML node

    Creates a grou from the data stored in an XML node. The group will be
    created below an instance of PTYPE. 

    \throws nxgroup_error in the case of errors
    \tparam PTYPE paren type
    \param parent the parent instancen
    \param t XML node instance
    \return a new group object
    */
    template<typename PTYPE>
    typename nxobject_traits<PTYPE>::group_type
    create_group(const PTYPE &parent,node &t)
    {
        typedef typename nxobject_traits<PTYPE>::group_type group_type; 
        //create the group and call the function recursively
        auto name = t.template get<string>("<xmlattr>.name");
        auto type = t.template get<string>("<xmlattr>.type");

        group_type g = parent.create_group(name,type);
        return g;
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create field from XML node

    \throws nxfield_error in case of errors
    \tparam PTYPE parent type
    \param parent the parent object
    \param t the XML node
    \return a field instancen
    */
    template<typename PTYPE>
    typename nxobject_traits<PTYPE>::field_type
    create_field(const PTYPE &parent,node &t)
    {
        typedef typename nxobject_traits<PTYPE>::group_type group_type;
        //obtain the name and the type of the field
        auto name = t.template get<string>("<xmlattr>.name");
        auto type = t.template get<string>("<xmlattr>.type");

        //read the shape of the field if it got one
        shape_t shape;
        try
        {
            node dim_node = t.get_child("dimensions");
            shape = dim2shape(dim_node);
        }
        catch(...)
        {}

        //at this point we should have gathered enough information in order to
        //create the field.
        auto f = create_field(parent,name,str2typeid[type],shape);

        //OK - in the next step we try to gather some optional information that
        //might be stored in the field.
        //------------------try to write units attribute--------------------
        try
        {
            auto units = t.template get<string>("<xmlattr>.units");
            f.template attr<string>("units").write(units);
        }
        catch(...)
        {}

        //-------------------try to write long_name attribute--------------
        try
        {
            auto lname = t.template get<string>("<xmlattr>.long_name");
            f.template attr<string>("long_name").write(lname);
        }
        catch(...)
        {}

        return f;      
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create objects from XML

    Recursively creates the objects as described in the XML file below parent.
    \tparam PTYPE parent type
    \param parent instance of PTYPE
    \param t ptree instance with the XML data
    */
    template<typename PTYPE>
    void create_objects(const PTYPE &parent,node &t)
    {
        for(auto child: t)
        {
            if(child.first == "group")
            {
                auto g = create_group(parent,child.second);
                create_objects(g,child.second);
            }
            else if(child.first == "field")
            {
                 create_field(parent,child.second);
            }
            else if(child.first == "link")
            {
                auto name = child.second.template get<string>("<xmlattr>.name");
                auto target = child.second.template get<string>("<xmlattr>.target");
                parent.link(name,target);
            }
        }
    }

//end of namespace 
}
}
}
}
