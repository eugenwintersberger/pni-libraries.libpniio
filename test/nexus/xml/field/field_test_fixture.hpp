//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
//  Created on: Jan 15, 2016
//      Author: Eugen Wintersberger
//
#pragma once

#include <pni/core/types.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/nexus.hpp>
#include "../xml_base_fixture.hpp"
#include "../../base_fixture.hpp"


struct FieldTestFixture : BaseFixture,XMLBaseFixture
{
    hdf5::node::Node nx_parent;
    std::string group_prefix;

    FieldTestFixture(const std::string &prefix):
        BaseFixture("field_test.nxs",true),
        XMLBaseFixture(),
        nx_parent(),
        group_prefix(prefix)
    { }

    //-------------------------------------------------------------------------
    ~FieldTestFixture()
    {
    }

    //-------------------------------------------------------------------------
    template<typename T>
    static pni::core::type_id_t get_type_id() 
    {
        return pni::core::type_id_map<T>::type_id;
    }

    //-------------------------------------------------------------------------
    template<typename T> 
    pni::core::string xml_file_name()
    {
        return group_prefix+pni::core::str_from_type_id(get_type_id<T>())+".xml";
    }

    //-------------------------------------------------------------------------
    template<typename T>
    pni::core::string parent_name()
    {
        return group_prefix+pni::core::str_from_type_id(get_type_id<T>());
    }

    //-------------------------------------------------------------------------
    template<typename T> void set_parent()
    {
        if(root.nodes.exists(parent_name<T>()))
            nx_parent = root.nodes[parent_name<T>()];
        else
            nx_parent = pni::io::nexus::BaseClass(root,parent_name<T>(),"NXentry");
    }

};

