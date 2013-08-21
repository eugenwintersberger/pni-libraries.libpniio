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
 * Created on: Jul 19, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/exceptions.hpp>
#include <sstream>
#include <utility>
#include "xml_node.hpp"
#include "attribute_data.hpp"

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;
    using namespace pni::io::nx;


    /*!
    \ingroup xml_lowlevel_utils
    \brief converts a shape in an xml string.

    This template function takes a container with shape information an converts
    it to an xml node with the shape information. 
    \code{.cpp}
    auto shape = array.shape<shape_t>();
    xml::node field_node;

    field_node.add_child("dimensions",shape2dim(shape));
    \endcode
    The resulting XML node will have for instance the following structure.
    \code{.xml}
    <dimensions rank="3">
        <dim value="100" index="1" />
        <dim value="123" index="2" />
        <dim value="5"   index="3" />
    </dimensions>
    \endcode
    
    \tparam CTYPE container type for the shape (default is shape_t)
    \param dims node instance to the dimensions tag
    \return instance of shape_t with the shapea
    */
    template<typename CTYPE> node shape2dim(const CTYPE &shape)
    {
        node dimensions;

        dimensions.put("<xmlattr>.rank",shape.size());

        size_t index = 1;
#ifdef NOFOREACH
        BOOST_FOREACH(auto s,shape)
#else
        for(auto s: shape)
#endif
        {
            node dim;
            dim.put("<xmlattr>.index",index++);
            dim.put("<xmlattr>.value",s);

            dimensions.push_back(std::make_pair("dim",dim));
        }

        return dimensions;
    }

//end of namespace
}
}
}
}
