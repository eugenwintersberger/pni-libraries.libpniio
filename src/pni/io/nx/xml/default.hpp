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
    //!
    //! \ingroup xml_classes
    //! \brief default data predicate
    //! 
    //! This is the default predicate used to avoid data to be transfered
    //! between Nexus and XML. 
    //!
    struct write_no_data
    {
        //!
        //! \brief predicate function
        //! 
        //! Always return false
        //!
        //! \tparam GTYPE group type
        //! \tparam FTYPE field type
        //! \tparam ATYPE attribute type
        //! \tparam LTYPE link type
        //! 
        //! \param o instance of nxobject
        //! \return always false
        template<
                 typename GTYPE,
                 typename FTYPE,
                 typename ATYPE,
                 typename LTYPE
                >
        bool operator()(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &)
        {
            return false;
        }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief maximum type maps
    //! 
    //! This map defines the maximum type for every numeric type provided 
    //! by pnicore. It is used when reading data from an attribute or node. 
    //! 
    typedef boost::mpl::map<
        boost::mpl::pair<pni::core::uint8,pni::core::uint64>,
        boost::mpl::pair<pni::core::uint16,pni::core::uint64>,
        boost::mpl::pair<pni::core::uint32,pni::core::uint64>,
        boost::mpl::pair<pni::core::uint64,pni::core::uint64>,
        boost::mpl::pair<pni::core::int8,pni::core::int64>,
        boost::mpl::pair<pni::core::int16,pni::core::int64>,
        boost::mpl::pair<pni::core::int32,pni::core::int64>,
        boost::mpl::pair<pni::core::int64,pni::core::int64>,
        boost::mpl::pair<pni::core::float32,pni::core::float128>,
        boost::mpl::pair<pni::core::float64,pni::core::float128>,
        boost::mpl::pair<pni::core::float128,pni::core::float128>,
        boost::mpl::pair<pni::core::complex32,pni::core::complex128>,
        boost::mpl::pair<pni::core::complex64,pni::core::complex128>,
        boost::mpl::pair<pni::core::complex128,pni::core::complex128>> max_type_map;

    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief bool representation map
    //! 
    //! A static map with all valid representations of boolean values.
    //! 
    static const std::map<pni::core::string,bool>  bool_string_map{
        {"1",true},{"0",false},
        {"True",true},{"False",false},
        {"true",true},{"false",false}
    };
//end of namespace
}
}
}
}
