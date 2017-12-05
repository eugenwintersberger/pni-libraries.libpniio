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

#include <pni/core/error.hpp>
#include <pni/io/nx/nxobject.hpp>

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup algorithm_internal_code
    //! \brief as attribute visitor
    //!
    //! Visitor to extract an attribute stored in an nxobject instance.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa as_attribute
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class as_attribute_visitor : public boost::static_visitor<ATYPE>
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
            using result_type = attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Throws an exception as the stored object is not an attribute 
            //! type.
            //!
            //! \throws type_error object not an attribute
            //!
            //! \param g group instance
            //! \return invalid attribute instance
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                      "Object is not an instance of nxattribute "
                      "but of s nxgroup!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Throw an exception as the object is not an attribute type 
            //! instance
            //!
            //! \throws type_error instance not a group type
            //!
            //! \param f field instance
            //! \return invalid attribute instance
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
            //! Returns the atttribute instance.
            //! \param a attribute instance
            //! \return attribute instance
            //!
            result_type operator()(const attribute_type &a) const
            {
                return a;
            }
            
            //----------------------------------------------------------------
            //!
            //! \brief process link instances
            //!
            //! Throw type_error exception as there is no conversion from a 
            //! link to an attribute. 
            //!
            //! \throws type_error 
            //!
            //! \return invalid instance of nxattribute
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Object is a link and not an instance of "
                        "nxattribute!");

                return result_type();
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief as attribute wrapper
    //!
    //! Function template extracting an attribute stored in an nxobject
    //! instance. If the object is not an attribute an nxattribute_error 
    //! exception will be thrown.
    //! The object is returned as an nxattribute instance. 
    /*!
    \code{.cpp}
    auto attr_obj = get_object(root,path_to_atribute);
    auto a = as_attribute(attr_obj);
    \endcode
    */
    //!
    //! \throws type_error if stored object is not a attribute type
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o instance of nxobject
    //! \return instance of ATYPE
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    ATYPE as_attribute(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = as_attribute_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
