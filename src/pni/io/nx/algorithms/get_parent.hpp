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
// Created on: Jul 1, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/nx/nxobject.hpp>
#include <pni/io/nx/nxobject_traits.hpp>

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief return parent
    //! 
    //! Returns the parent object of an instance of nxfield, nxattribute, or 
    //! nxgroup object. The parent is returned as an instance of nxobject.
    //! 
    //! \throws invalid_object_error if the child is not valid
    //! \throws type_error if there are some issues with the internal type
    //! \throws object_error in case of errors generating parent object
    //!
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID
    //!
    //! \param o object instance
    //! \return parent as nxobject instance
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    typename nxobject_trait<IMPID>::object_type
    get_parent(const OTYPE<IMPID> &o)
    {
        return o.parent();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get parent visitor
    //!
    //! Visitor template used to retrieve the parent object from an instance of 
    //! nxobject.
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
    class get_parent_visitor : public boost::static_visitor<
                               nxobject<GTYPE,FTYPE,ATYPE,LTYPE>
                               >
    {
        public:
            //! result type
            using result_type = nxobject<GTYPE,FTYPE,ATYPE,LTYPE>;
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type =  FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE;
            //! link type
            using link_type = LTYPE;

            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! Return the parent group of a group. 
            //!
            //! \throws invalid_object_error if the group is not valid
            //! \throws type_error in case of issues with the internal type
            //! \throws object_error in case of errors generating parent object
            //! 
            //! \param g group instance
            //! \return parent group
            //!
            result_type operator()(const group_type &g) const
            {
                return get_parent(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Return the fields parent group.
            //! 
            //! \throws invalid_object_error if the field is not valid
            //! \throws type_error in case of internal type issues
            //! \throws object_error in case of errors generating parent object
            //!
            //! \param f field instance
            //! \return parent group of the field
            //!
            result_type operator()(const field_type &f) const
            {
                return get_parent(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute
            //!
            //! Retrieve the type of an object.
            //!
            //! \throws invalid_object_error if the attribute is not valid
            //! \throws type_error in case of internal type issues
            //! \throws object_error in case of errors generating parent object
            //!
            //! \param a attribute instance
            //! \return to be ignored
            //!
            result_type operator()(const attribute_type &a) const
            {
                return get_parent(a);
            }

            result_type operator()(const link_type &l) const
            {
                return get_parent(l);
            }
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get parent 
    //!
    //! Return the parent object of an instance of nxobject as a new instance of 
    //! nxobject.
    //!
    //! \throws invalid_object_error if the object is not valid
    //! \throws type_error in case of internal type issues
    //! \throws object_error in case of errors generating parent object
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    //! \param o instance of nxobject
    //! \return parent object as instance of nxobject
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    nxobject<GTYPE,FTYPE,ATYPE,LTYPE> 
    get_parent(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = get_parent_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
