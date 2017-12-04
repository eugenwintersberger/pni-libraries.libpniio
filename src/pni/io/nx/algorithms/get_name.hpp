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

#include <pni/core/types.hpp>
#include <pni/io/nx/nximp_code.hpp>
#include <pni/io/nx/nxobject.hpp>

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
    //! \li nxlink
    //! 
    //! \throws io_error in case of problems
    //! \throws invalid_object_erro in case of an invalid object
    //! \throws type_error if a type cannot be retrieved for this type
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object type template
    //! \tparam IMPID implementation ID
    //!
    //! \param o reference to the object
    //! \return name of the object
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    pni::core::string get_name(const OTYPE<IMPID> &o)
    {
        return o.name();
    }

    //------------------------------------------------------------------------
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
    //! \tparam LTYPE link type
    //! \sa get_name
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class get_name_visitor : public boost::static_visitor<pni::core::string>
    {
        public:
            //! result type
            using result_type = pni::core::string;
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type = FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE; 
            //! NeXus link type
            using link_type = LTYPE;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Retrieve the name from a group instance.
            //!
            //! \throws io_error in case of IO issues
            //! \throws invalid_object_error if group not valid
            //! \throws type_error if a type cannot be retrieved for this type
            //! \throws object_error in case of any other error
            //!
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
            //!
            //! \throws io_error in case of IO issues
            //! \throws invalid_object_error if the field is not valid
            //! \throws type_error if a type cannot be retrieved for this type
            //! \throws object_error in case of any other error
            //!
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
            //!
            //! \throws io_error in case of IO issues
            //! \throws invalid_object_error in case the attribute is not valid
            //! \throws type_error if a type cannot be retrieved for this type
            //! \throws object_error in case of any other error
            //!
            //! \param a attribute instance
            //! \return name of the attribute
            //!
            result_type operator()(const attribute_type &a) const
            {
                return get_name(a);
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief process nxlink instances
            //!
            //! Retrieve the name of an nxlink instance.
            //!
            //! \param a attribute instance
            //! \return name of the attribute
            //!
            result_type operator()(const link_type &a) const
            {
                return a.name();
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get name 
    //!
    //! Retriev the name of an object stored in an instance of the nxobject
    //! template. 
    //! 
    //! \throws io_error in case of IO errors
    //! \throws invalid_oject_error if the object is not valid
    //! \throws type_error if a type cannot be retrieved for this type
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    //! \param o instance of nxobject
    //! \return name of the object
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    pni::core::string get_name(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = get_name_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
