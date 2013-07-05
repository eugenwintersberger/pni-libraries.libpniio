/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jul 5, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include "../nxvariant_traits.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    /*!
    \ingroup variant_code
    \brief read visitor

    This visitor reads data from a field or an attribute. Partial IO is
    supported only for fields. If partial IO is tried on an attribute object a
    selection will be thrown. As one cannot write data to a group an exception
    will be thrown if the stored type is a group type.

    \tparam VTYPE variant type
    \sa read
    */
    template<typename ATYPE,typename VTYPE> 
    class read_visitor : public boost::static_visitor<void>
    {
        public: 
            typedef std::vector<slice> selection_t;
        private:
            //! reference to the data holding object
            ATYPE &_data;
            //! selection vector
            selection_t _selection;
        public:
            //! first type of the variant type
            typedef typename nxvariant_member_type<VTYPE,0>::type first_member;
            //! result type
            typedef void result_type;
            //! Nexus group type
            DEFINE_NXGROUP(first_member) group_type;
            //! Nexus field type
            DEFINE_NXFIELD(first_member) field_type;
            //! Nexus attribute type
            DEFINE_NXATTRIBUTE(first_member) attribute_type;

            //-----------------------------------------------------------------
            /*!
            \brief constructor

            \param data reference to the data holding instance
            \param s selection of what to read
            */
            read_visitor(ATYPE &data,const selection_t &s=selection_t()):
                _data(data),
                _selection(s)
            {}

            //-----------------------------------------------------------------
            /*!
            \brief process group instances

            Cannot read data to a group - thus an exception is thrown.
            \throws nxgroup_error 
            \param g group instance
            \return nothing
            */ 
            result_type operator()(const group_type &g) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "One cannot read data to a group object!");
            }

            //-----------------------------------------------------------------
            /*!
            \brief process field instances

            Read data from a field
            \throws nxfield_error in case of IO errors
            \param f field instance
            \return nothing
            */
            result_type operator()(field_type &f) const
            {
                if(_selection.size())
                    f(_selection).read(_data);
                else
                    f.read(_data);
            }

            //-----------------------------------------------------------------
            /*!
            \brief process attribute instances

            Read data from an attribute. If the selection member is not empty an
            exception will be thrown as partial IO is not supported on
            attributes.

            \throw nxattribute_error in case or IO errors or partial IO on an
            attribute
            \param a attribute instance
            \return nothing
            */
            result_type operator()(attribute_type &a) const
            {
                if(_selection.size())
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Partial IO currently not supported on attribute!");
                else
                    a.read(_data);
            }
    };

    /*!
    \ingroup variant_code
    \brief read wrapper

    This function template is a wrapper for the read_visitor. It will read
    data from the field or attribute stored in the variant type. 
    Partial IO is supported only for fields. As data cannot be read from a
    group an exception will be thrown if the object stored in the variant type
    is a group object.

    Simple IO can be done with
    \code{.cpp}
    darray<float64> data = ....;
    object_types field = get_object(root,path_to_field);

    //here the entire field is read 
    read(field,data);
    \endcode
    Due to some limitations of the variadic template engine partial IO has a bit
    unintuitive syntax. 
    \code{.cpp}
    darray<float64> frame = ...;
    auto field = get_object(root,path_to_field);

    //here we read the slice (10,:1024,:512)
    read(field,frame,10,slice(0,1024),slice(0,512));
    \endcode
    Partial IO is however only supported for field but not for attributes. 
    The following code will work
    \code{.cpp}
    auto attribute = get_object(root,path_to_attribiute);
    
    string value;
    read(attribute,value);
    \endcode
    but this one will not
    \code{.cpp}
    auto field = get_object(root,path_to_field);
    auto attr = create_attribute<float32>(field,"tensor",shape_t{3,3});

    //this will fail
    float32 buffer;
    read(attr,buffer,0,0); //throws an exception
    \endcode

    \throws nxgroup_error if stored object is a group
    \throws nxattribute_error for partial IO on an attribute
    \throws nxfield_error for IO errors during reading from field
    \tparam ATYPE data holding type
    \tparam VTYPE variant type
    \tparam ITPYES index types
    \param o instance of VTYPE
    \param data instance of ATYPE with the data
    \param indices index type instances
    \return nothing
    */
    template<typename ATYPE,
             typename VTYPE,
             typename ...ITYPES 
            > 
    typename read_visitor<ATYPE,VTYPE>::result_type 
    read(VTYPE &o,ATYPE &a,ITYPES ...indices)
    {
        std::vector<slice> sel{slice(indices)...};
        return boost::apply_visitor(read_visitor<ATYPE,VTYPE>(a,sel),o);
    }

    template<typename ATYPE,typename VTYPE>
    typename read_visitor<ATYPE,VTYPE>::result_type
    read(VTYPE &o,ATYPE &a,const std::vector<slice> &sel)
    {
        return boost::apply_visitor(read_visitor<ATYPE,VTYPE>(a,sel),o);
    }

//end of namespace
}
}
}
