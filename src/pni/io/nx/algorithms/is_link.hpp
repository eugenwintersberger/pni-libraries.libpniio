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
// Created on: Mar 07, 2016
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nx/nxobject.hpp>

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_internal_code
    //! \brief is_link visitor
    //!
    //! Visitor testing if the object stored in an nxobject instance is an 
    //! instance of nxlink.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //! 
    //! \return true if the object is a link, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class is_link_visitor : public boost::static_visitor<bool>
    {
        public:
            //! result type 
            using result_type = bool;
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type = FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE;
            //! NeXus link type
            using link_type = LTYPE;
          
            //----------------------------------------------------------------
            //!
            //! \brief process group objects
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
            //! \brief process field objects
            //!
            //! \param f reference to field instance
            //! \return false
            //!
            result_type operator()(const field_type &) const noexcept
            {
                return false;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute objects
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
            //! \brief process link objects
            //! 
            //! \return false
            //!
            result_type operator()(const link_type &) const noexcept
            {
                return true;
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief test for group
    //!
    //! Template function testing if the object stored in an instance of 
    //! nxobject is an instance of nxlink. If this is the case true is 
    //! returned, false otherwise. The function does not test for the 
    //! validity of the stored object. It just provides type information 
    //! about the stored object at runtime.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    //! \param o reference to nxobject<GTYPE,FTYPE,ATYPE,LTYPE>
    //! \return true if object is a group, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    bool is_link(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o) noexcept
    {
        using visitor_type = is_link_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
