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
// Created on: Jun 28, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief check if group
    //!
    //! Visitor testing if the object stored in an nxobject instance is an 
    //! instance of nxgroup.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \return true if the object is a group, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class is_group_visitor : public boost::static_visitor<bool>
    {
        public:
            //! result type 
            typedef bool result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;
          
            //----------------------------------------------------------------
            //!
            //! \brief process group objects
            //!
            //! \param g reference to group instance
            //! \return true
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const noexcept
            {
                return true;
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field objects
            //!
            //! \param f reference to field instance
            //! \return false
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const field_type &f) const noexcept
            {
                return false;
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute objects
            //! 
            //! \param a reference to attribute instance
            //! \return false
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const noexcept
            {
                return false;
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief test for group
    //!
    //! Template function testing if the object stored in an instance of 
    //! nxobject is an instance of nxgroup. If this is the case true is 
    //! returned, false otherwise. The function does not test for the 
    //! validity of the stored object. It just provides type information 
    //! about the stored object at runtime.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o reference to nxobject<GTYPE,FTYPE,ATYPE>
    //! \return true if object is a group, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    bool is_group(const nxobject<GTYPE,FTYPE,ATYPE> &o) noexcept
    {
        return boost::apply_visitor(is_group_visitor<GTYPE,FTYPE,ATYPE>(),o);
    }

//end of namespace
}
}
}
