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
// Created on: Jul 3, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject.hpp"

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup algorithm_internal_code
    //! \brief as group visitor
    //!
    //! Visitor extracting a group stored in an nxobject instance.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa as_group
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class as_group_visitor : public boost::static_visitor<GTYPE>
    {
        public:
            //! Nexus group type
            typedef GTYPE     group_type;
            //! Nexus field type
            typedef FTYPE     field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;
            //! result type
            typedef group_type result_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Returns the instance of the group object.
            //! \param g group instance
            //! \return instance of group type
            //!
            result_type operator()(const group_type &g) const
            {
                return g;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Throw an exception as the object is not a field type instance
            //! \throws nxgroup_error instance not a group type
            //! \param f field instance
            //! \return empty instance of group_type
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const field_type &f) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Object is a field but not a group instance!");
                return result_type();
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Throw an exception as the object is not a group object.
            //! \throws nxfield_error no group instance
            //! \param a attribute instance
            //! \return invalid group instance
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "Object is an attribute not a field!");
                return result_type();
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief as group wrapper
    //!
    //! Function template returning a group object stored in an nxobject 
    //! instance. If the stored object is not an instance of nxgroup an
    //! exception  will be thrown.
    //!
    /*!
    \code{.cpp}
    auto object = get_object(root,path_to_group);
    auto group  = as_group(group_obj);
    \endcode
    */
    //!
    //! \throws nxgroup_error if stored object is not a group type
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o instance of nxobject<GTYPE,FTYPE,ATYPE>
    //! \return instance of GTYPE
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    GTYPE as_group(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        return boost::apply_visitor(as_group_visitor<GTYPE,FTYPE,ATYPE>(),o);
    }

//end of namespace
}
}
}
