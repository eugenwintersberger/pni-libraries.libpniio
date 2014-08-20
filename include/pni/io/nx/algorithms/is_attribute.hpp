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
    //! \brief is_attribute visitor
    //!
    //! Visitor checking if the object stored in an instance of nxobject is 
    //! an instance of nxattribute.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class is_attribute_visitor : public boost::static_visitor<bool>
    {
        public:
            //! result type (bool)
            typedef bool result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;
          
            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! \param g refernece to group instance
            //! \return false
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const  noexcept
            { 
                return false; 
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
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
            //! \brief process attribute instances
            //!
            //! \param a reference to attribute instance
            //! \return true
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const noexcept
            { 
                return true; 
            }
#pragma GCC diagnostic pop
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief check if attribute
    //! 
    //! Function template checking if the object stored in an nxobject 
    //! instance is an instance of nxattribute. If this is the case true is 
    //! returned, otherwise false. The function does not test for the validity 
    //! of an object.  It just provides runtime information about the type 
    //! of the object stored in the nxobject instance.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o reference to an instance of nxobject<GTYPE,FTYPE,ATYPE>
    //! \return true if o is an attribute, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    bool is_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &o) noexcept
    {
        typedef is_attribute_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
