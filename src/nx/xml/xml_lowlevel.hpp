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
#include <boost/lexical_cast.hpp>

#include "xml_node.hpp"
#include "node_data.hpp"
#include "attribute_data.hpp"



namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    /*!
    \ingroup xml_lowlevel_utils
    \brief create shape form dimensions tag

    Create a shape container from the dimensions tag in the XML file. A
    dimension tag has the structure
    \code{.xml}
    <dimensions rank="3">
        <dim value="100" index="1" />
        <dim value="123" index="2" />
        <dim value="5"   index="3" />
    </dimensions>
    \endcode
    All attributes appearing here are mandatory and hence, if one of them is
    missing a parser_error exception will be thrown. Furthermore, the function
    checks if the number of valid \c dim entries in \c dimensions matches the \c
    rank attribute of the \c dimensions tag. If this is not the case a
    shape_mismatch_error will be thrown to indicate that there is an error in
    the setup of this tag.
    
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
        auto rank = attribute_data<size_t>::read(dims,"rank");
        CTYPE s(rank);

        //initialize the shape with zero
        std::fill(s.begin(),s.end(),0);

        size_t valid_indices = 0;
        for(auto dim: dims)
        {
            if(dim.first != "dim") continue; //omit all non 'dim' tags

            //reading the index attribute
            auto index = attribute_data<size_t>::read(dim.second,"index");
            auto value = attribute_data<size_t>::read(dim.second,"value");

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
    A group tag has in general the following form 
    \code{.xml}
    <group name="entry" type="NXentry"> </group>
    \endcode
    Wile the \c type attribute is optional the \c name attribute is absolutely
    mandatory as you cannot create a group without a name. The content of the \c
    type attribute goes to the \c NX_class attribute of the newly create group
    and determines the Nexus base class the new gruop belongs too. 

    \throws nxgroup_error in the case of errors
    \throws parser_error in case of errors in parsing XML attributes
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

        //this attribute is absolutely mandatory - an exception will be thrown
        //if it does not exist
        auto name = attribute_data<string>::read(t,"name");

        string type;
        try
        {
            //the type is optional
            type = attribute_data<string>::read(t,"type");
        }
        catch(...)
        {}

        /* create the gruop
           This will throw an exception in case of any IO error. One possibility
           would be that a group with this name already exists.
        */
        group_type g = parent.create_group(name,type);
        return g;
    }

    template<typename T,typename FTYPE>
    void copy_node_to_field(const node &n,const FTYPE &f)
    {
        if(f.size() == 1)
        {
            T buffer = node_data<T>::read(n);
            f.write(buffer);
        }
        else
        {
            //manage multidimensional data
            auto buffer = node_data<array>::read(n,',');
            f.write(buffer);
        }
    }

    template<typename FTYPE>
    void copy_node_to_field(const node &n,const FTYPE &f)
    {
        if(f.type_id() == type_id_t::UINT8)
            copy_node_to_field<uint8>(n,f);
        else if(f.type_id() == type_id_t::INT8)
            copy_node_to_field<int8>(n,f);
        
        else if(f.type_id() == type_id_t::UINT8)
            copy_node_to_field<uint16>(n,f);
        else if(f.type_id() == type_id_t::INT8)
            copy_node_to_field<int16>(n,f);

        else if(f.type_id() == type_id_t::UINT32)
            copy_node_to_field<uint32>(n,f);
        else if(f.type_id() == type_id_t::INT32)
            copy_node_to_field<int32>(n,f);
        
        else if(f.type_id() == type_id_t::UINT64)
            copy_node_to_field<uint64>(n,f);
        else if(f.type_id() == type_id_t::INT64)
            copy_node_to_field<int64>(n,f);

        else if(f.type_id() == type_id_t::FLOAT32)
            copy_node_to_field<float32>(n,f);
        else if(f.type_id() == type_id_t::FLOAT64)
            copy_node_to_field<float64>(n,f);
        else if(f.type_id() == type_id_t::FLOAT128)
            copy_node_to_field<float128>(n,f);

        else if(f.type_id() == type_id_t::STRING)
            copy_node_to_field<string>(n,f);
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create field from XML node

    Field objects are described in XML as follows
    \code{.xml}
    <field name="data" type="float64" unit="m" long_name="detector data">
        <dimensions ....>

        </dimensions>
    </field>
    \endcode
    The \c name and the \c type attribute are mandatory. Thus, a parser_error is
    thrown if they do not exist. The \c dimensions tag is optional and must be
    used only when a multidimensional field is created.
    
    The \c field tag itself has two optional attributes \c unit and \c
    long_name. The former one is a string attribute with the string
    representation of the physical unit of the data. The latter one is a string
    attribute too with a more detailed description of the data. 

    \throws nxfield_error in case of errors
    \throws parser_error in case of missing attributes
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
        auto name = attribute_data<string>::read(t,"name");
        auto type = attribute_data<string>::read(t,"type");

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
        if(has_attribute(t,"units"))
        {
            auto units = attribute_data<string>::read(t,"units");
            f.template attr<string>("units").write(units);
        }

        //-------------------try to write long_name attribute--------------
        if(has_attribute(t,"long_name"))
        {
            auto lname = attribute_data<string>::read(t,"long_name");
            f.template attr<string>("long_name").write(lname);
        }

        //now we read the data from the field  and write it
        if(has_data(t))
            copy_node_to_field(t,f);

        return f;      
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup xml_lowlevel_utils
    \brief create objects from XML

    Recursively creates the objects as described in the XML file below parent.
    \throws parser_error in case of XML parsing problems
    \throws nxgroup_error in case of group creation or access issues
    \throws nxfield_error in case of field creation issues
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
                //recursive call of create_objects
                create_objects(g,child.second);
            }
            else if(child.first == "field")
            {
                 create_field(parent,child.second);
            }
            else if(child.first == "link")
            {
                auto name = attribute_data<string>::read(child.second,"name");
                auto target = attribute_data<string>::read(child.second,"target");
                parent.link(name,target);
            }
        }
    }

//end of namespace 
}
}
}
}
