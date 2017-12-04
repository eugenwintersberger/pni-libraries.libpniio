//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 28, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_internal_code
    //! \brief is_field visitor
    //!
    //! Visitor testing if the object stored in an instance of nxobject
    //! is an instance of nxfield. 
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class is_field_visitor : public boost::static_visitor<bool>
    {
        public:
            //! result type (bool)
            using result_type = bool; 
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type = FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE;
            //! NeXus link type
            using link_type = LTYPE;
           
            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! \param g reference to group instance
            //! \return false
            //!
            result_type operator()(const group_type &) const noexcept
            {
                return false;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! \param f reference to field instance
            //! \return true
            //!
            result_type operator()(const field_type &) const noexcept
            {
                return true;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! \param a reference to attribute instance
            //! \return false
            //!
            result_type operator()(const attribute_type &) const noexcept
            {
                return false;
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief process link instances
            //!
            //! \return false
            //!
            result_type operator()(const link_type &) const noexcept
            {
                return false;
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief check if field
    //!
    //! Function template testing if the object stored in an instance of
    //! nxobject is an instance of nxfield. If this is the case true is 
    //! returned, false otherwise. The function does not test for validity 
    //! of an object. It just helps to retrieve type information at runtime.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    //! \param o instance of nxobject<GTYPE,FTYPE,ATYPE,LTYPE>
    //! \return true if the object is a field, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    bool is_field(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o) noexcept
    {
        using visitor_type = is_field_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
