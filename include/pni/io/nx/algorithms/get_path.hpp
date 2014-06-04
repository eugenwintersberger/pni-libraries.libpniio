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
// Created on: Jul 18, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get object path
    //! 
    //! Return the path of an object as a string. The object can be either an
    //! instance of nxfield, nxgroup, or nxattribute. 
    //! 
    //! \tparam OTYPE object type template
    //! \tparam IMPID implementation ID
    //! \param o object instance
    //! \return path as string
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    string get_path(const OTYPE<IMPID> &o)
    {
        return o.path();
    }

    //!
    //! \ingroup algorithm_code
    //! \brief get path visitor
    //!
    //! Visitor template used to obtain the path from an object stored in an 
    //! nxobject instance.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa get_path
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_path_visitor : public boost::static_visitor<string>
    {
        public:
            //! result type
            typedef string result_type;
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
            //! Return the path of a group instance
            //! \param g group instance
            //! \return string with the path
            //!
            result_type operator()(const group_type &g) const
            {
                return get_path(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Retrieve the path of a field instance.
            //! \param f field instance
            //! \return path to the field
            //!
            result_type operator()(const field_type &f) const
            {
                return get_path(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Return the path of an attribute.
            //! \param a attribute instance
            //! \return path to the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                return get_path(a);
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get path 
    //!
    //! Return the path of an object stored in an nxobject instance. 
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o instance of nxobject
    //! \return path as string
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    string get_path(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        return boost::apply_visitor(get_path_visitor<GTYPE,FTYPE,ATYPE>(),o);
    }

//end of namespace
}
}
}
