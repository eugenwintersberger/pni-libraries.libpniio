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
 * Created on: Jul 17, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/exceptions.hpp>
#include <sstream>
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
    missing a parser_error exception will be thrown.  Furthermore, the function
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
#ifdef NOFOREACH
        BOOST_FOREACH(auto dim,dims)
#else
        for(auto dim: dims)
#endif
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

//end of namespace
}
}
}
}
