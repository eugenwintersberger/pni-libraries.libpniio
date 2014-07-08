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

#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

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
    //! \throws object_error in case of errors generating parent object
    //! \throws io_error in case of errors during metadata retrieval
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID
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
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_parent_visitor : public boost::static_visitor<
                               nxobject<GTYPE,FTYPE,ATYPE>
                               >
    {
        public:
            //! result type
            typedef nxobject<GTYPE,FTYPE,ATYPE> result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! Return the parent group of a group. 
            //! \throws object_error in case of errors generating parent object
            //! \throws io_error in case of errors during metadata retrieval
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
            //! \throws object_error in case of errors generating parent object
            //! \throws io_error in case of errors during metadata retrieval
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
            //! \throws object_error in case of errors generating parent object
            //! \throws io_error in case of errors during metadata retrieval
            //! \param a attribute instance
            //! \return to be ignored
            //!
            result_type operator()(const attribute_type &a) const
            {
                return get_parent(a);
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
    //! \throws object_error in case of errors generating parent object
    //! \throws io_error in case of errors during metadata retrieval
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o instance of nxobject
    //! \return parent object as instance of nxobject
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    nxobject<GTYPE,FTYPE,ATYPE> get_parent(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef get_parent_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
