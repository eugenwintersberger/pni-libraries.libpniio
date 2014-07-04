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

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief get object name
    //! 
    //! Return the name of an object. This template function is called in case
    //! that the object is an instance of 
    //! 
    //! \li nxgroup
    //! \li nxfile
    //! \li nxattribute
    //! \li nxfield
    //! 
    //! \tparam OTYPE object type template
    //! \tparam IMPID implementation ID
    //! \param o reference to the object
    //! \return name of the object
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    string get_name(const OTYPE<IMPID> &o)
    {
        return o.name();
    }


    //!
    //! \ingroup algorithm_internal_code
    //! \brief get name visitor
    //!
    //! Visitor retrieving the name of an object stored in an nxobject 
    //! instance.
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa get_name
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_name_visitor : public boost::static_visitor<string>
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
            //! Retrieve the name from a group instance.
            //! \param g group instance
            //! \return string with the group name
            //!
            result_type operator()(const group_type &g) const
            {
                return get_name(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Retrieve the name of a field instance.
            //! \param f field instance
            //! \return name of the field
            //!
            result_type operator()(const field_type &f) const
            {
                return get_name(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Retrieve the name of an attribute instance.
            //! \param a attribute instance
            //! \return name of the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                return get_name(a);
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get name 
    //!
    //! Retriev the name of an object stored in an instance of the nxobject
    //! template. 
    //! 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o instance of nxobject
    //! \return name of the object
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    string get_name(const nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        return boost::apply_visitor(get_name_visitor<GTYPE,FTYPE,ATYPE>(),o);
    }

//end of namespace
}
}
}
