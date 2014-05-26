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

#include "../nxobject_traits.hpp"
#include "nxvariant_algo_helper.hpp"


namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup variant_code
    //! \brief check object validity
    //!
    //! This visitor checks a Nexus object stored in a variant type for its
    //! validity. You will hardly ever use this visitory directly but rather 
    //! the is_valid wrapper function.
    //!
    //! \tparam VTYPE variant type
    //! \sa is_valid
    //!
    template<typename VTYPE> 
    class is_valid_visitor : public boost::static_visitor<bool>
    {
        public:
            //! result type (bool)
            typedef bool result_type;
            //! Nexus group type
            typedef typename nxobject_group<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxobject_field<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type;
          
            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Checks a group instance for its validity. If the group is 
            //! valid true is returned, otherwise false. 
            //! \param g group instance
            //! \return true if valid, false otherwise
            //!
            result_type operator()(const group_type &g) const
            {
                return g.is_valid();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Checks a field instance for its validity. If the field is 
            //! valid true is returned, otherwise false. 
            //!
            //! \param f field instance
            //! \return true if valid, false otherwise
            //!
            result_type operator()(const field_type &f) const
            {
                return f.is_valid();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Checks a attribute instance for its validity. If the attribute 
            //! is valid true is returned, otherwise false. 
            //!  \param a attribute instance
            //! \return true if valid, false otherwise
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a.is_valid();
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief is_valid wrapper 
    //!
    //! This function acts as a wrapper around the is_valid_visitor. It 
    //! returns true if the object stored in the variant type VTYPE is valid  
    //! and false otherwise.
    /*! 
    \code{.cpp}
    typedef nxvariant_trait<h5::nxfile>::object_types object_types;

    object_types o = ....;
    if(!is_valid(o))
    {
        std::cerr<<"Nexus object is not valid - abort program!"<<std::endl;
        return -1;
    }
    \endcode
    */
    //! \tparam VTYPE
    //! \param o reference to instance of VTYPE
    //! \return true if valid, false otherwise
    //!
    template<typename VTYPE> 
    typename is_valid_visitor<VTYPE>::result_type is_valid(const VTYPE &o)
    {
        return boost::apply_visitor(is_valid_visitor<VTYPE>(),o);
    }

//end of namespace
}
}
}
