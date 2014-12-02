//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//************************************************************************
// Created on: Dec 2, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject.hpp"
#include <boost/mpl/map.hpp>
#include <map>

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace boost;

    //!
    //! \ingroup xml_classes
    //! \brief default data predicate
    //! 
    //! This is the default predicate used to avoid data to be transfered
    //! between Nexus and XML. 
    //!
    struct write_no_data
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
        //!
        //! \brief predicate function
        //! 
        //! Always return false
        //!
        //! \tparam GTYPE group type
        //! \tparam FTYPE field type
        //! \tparam ATYPE attribute type
        //! 
        //! \param o instance of nxobject
        //! \return always false
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE
                >
        bool operator()(const nxobject<GTYPE,FTYPE,ATYPE> &o)
        {
            return false;
        }
#pragma GCC diagnostic pop
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief maximum type maps
    //! 
    //! This map defines the maximum type for every numeric type provided 
    //! by pnicore. It is used when reading data from an attribute or node. 
    //! 
    typedef mpl::map<
        mpl::pair<uint8,uint64>,
        mpl::pair<uint16,uint64>,
        mpl::pair<uint32,uint64>,
        mpl::pair<uint64,uint64>,
        mpl::pair<int8,int64>,
        mpl::pair<int16,int64>,
        mpl::pair<int32,int64>,
        mpl::pair<int64,int64>,
        mpl::pair<float32,float128>,
        mpl::pair<float64,float128>,
        mpl::pair<float128,float128> > max_type_map;

    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief bool representation map
    //! 
    //! A static map with all valid representations of boolean values.
    //! 
    static const std::map<string,bool>  bool_string_map{
        {"1",true},{"0",false},
        {"True",true},{"False",false},
        {"true",true},{"false",false}
    };
//end of namespace
}
}
}
}
