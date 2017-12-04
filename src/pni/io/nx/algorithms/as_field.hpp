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
    //! \brief as field visitor
    //!
    //! Visitor extracting a field stored in an nxobject instance.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa as_field
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE 
            > 
    class as_field_visitor : public boost::static_visitor<FTYPE>
    {
        public:
            //! field type
            using field_type = FTYPE;
            //! group type
            using group_type = GTYPE;
            //! attribute type
            using attribute_type = ATYPE;
            //! link type
            using link_type = LTYPE;
            //! result type of the visitor
            using result_type = field_type;

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Throws an exception as the stored object is not a field.
            //!
            //! \throws type_error groups do not have a rank
            //!
            //! \param g group instance
            //! \return invalid field instance
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Object is not an instance of nxfield, "
                        "but of nxgroup!");
                return field_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Returns the field stored in the variant.
            //!
            //! \param f field instance
            //! \return field instance
            //!
            result_type operator()(const field_type &f) const
            {
                return f;
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Throw an exception as the object is not a field object.
            //!
            //! \throws tpye_error no field instance
            //!
            //! \param a attribute instance
            //! \return invalid field instance
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Object is not an instance of nxfield, "
                        "but of nxattribute!");
                return field_type();
            }

            //----------------------------------------------------------------
            //!
            //! \brief process link instances
            //!
            //! Throws type_error exception as there is no conversion from 
            //! a link to nxfield.
            //!
            //! \throws type_error
            //!
            //! \return invalid field instance
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Object is not an instance of nxfield but of "
                        "link!");
                return result_type();
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief as field wrapper
    //!
    //! function template extracting a field stored in an nxobject instance. 
    //! If the stored object is not an instance of nxfield an exception of 
    //! type nxfield_error will be thrown. 
    /*!
    \code{.cpp}
    auto object = get_object(root,path_to_field);
    auto field = as_field(field_obj);
    \endcode
    */
    //!
    //! \throws type_error if stored object is not a field type
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o instance of nxobject
    //! \return instance of FTYPE
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    FTYPE as_field(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = as_field_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
