//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Mar 7, 2016
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/error.hpp>
#include "../nxobject.hpp"

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup algorithm_internal_code
    //! \brief as link visitor
    //!
    //! Visitor to extract a link stored in an nxobject instance.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa as_link
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class as_link_visitor : public boost::static_visitor<LTYPE>
    {
        public:
            //! Nexus group type
            using group_type =  GTYPE;
            //! Nexus field type
            using field_type = FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE;
            //! Nexus link type
            using link_type = LTYPE;

            //! result type
            using result_type = link_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Throws an exception as the stored object is not a link type.
            //!
            //! \throws type_error object not a link
            //!
            //! \param g group instance
            //! \return invalid link instance
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                      "Object is not an instance of nxlink "
                      "but of nxgroup!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Throw an exception as the object is not a link type 
            //! instance
            //!
            //! \throws type_error instance not a link type
            //!
            //! \param f field instance
            //! \return invalid link instance
            //!
            result_type operator()(const field_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Object is not an instance of nxattribute "
                        "but of nxfield!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! \throws type_error instance is not a link type
            //! \param a attribute instance
            //! \return invalid link instance
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Object is an attribute and not an instance of "
                        "nxlink!");

                return result_type();
            }
            
            //----------------------------------------------------------------
            //!
            //! \brief process link instances
            //!
            //! Return the link instance.
            //!
            //! \param l instance of nxlink
            //! \return instance of nxlink
            //!
            result_type operator()(const link_type &l) const
            {
                return l;
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief as link wrapper
    //!
    //! Function template extracting a link stored in an nxobject
    //! instance. If the object is not a link a type_error 
    //! exception will be thrown.
    //! The object is returned as an nxlink instance. 
    /*!
    \code{.cpp}
    auto link_obj = get_object(root,path_to_link);
    auto l = as_link(link_obj);
    \endcode
    */
    //!
    //! \throws type_error if stored object is not a attribute type
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //! \param o instance of nxobject
    //! \return instance of ATYPE
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    LTYPE as_link(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = as_link_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
