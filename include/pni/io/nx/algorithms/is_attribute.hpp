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
    //! \ingroup algorithm_code
    //! \brief check attribute visitor
    //!
    //! This visitor checks if the object stored in a variant type is an 
    //! attribute instance. In this case true will be returne. False 
    //! otherwise. 
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
            result_type operator()(const group_type &g) const 
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
            result_type operator()(const field_type &f) const 
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
            result_type operator()(const attribute_type &a) const 
            { 
                return true; 
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief check if attribute
    //! 
    //! A wrapper around the is_attribute_visitor template. The function 
    //! returns true if the object stored in nxobject<GTYPE,FTYPE,ATYPE> is 
    //! an attribute. In all other cases false is returned.
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
    bool is_attribute(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        return boost::apply_visitor(is_attribute_visitor<GTYPE,FTYPE,ATYPE>(),o);
    }

//end of namespace
}
}
}
