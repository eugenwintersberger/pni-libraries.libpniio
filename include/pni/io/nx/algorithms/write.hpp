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
// Created on: Jul 5, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{
    
    using namespace pni::core;

    //!
    //! \ingroup variant_code
    //! \brief write visitor
    //!
    //! This visitor writes data to  a field or attribute. Partial IO is 
    //! supported only for fields. If partial IO is tried on an attribute 
    //! object a selection will be thrown. As one cannot write data to a 
    //! group an exception will be thrown if the stored type is a group type.
    //!
    //! \tparam VTYPE variant type
    //! \sa write
    //!
    template<
             typename ATYPE,
             typename VTYPE
            > 
    class write_visitor : public boost::static_visitor<void>
    {
        public: 
            //! selection type for partial IO
            typedef std::vector<slice> selection_t;
        private:
            //! reference to the data holding object
            const ATYPE &_data;
            //! selection vector
            selection_t _selection;
        public:
            //! result type
            typedef void result_type;
            //! Nexus group type
            typedef typename nxobject_group<VTYPE>::type group_type;
            //! Nexus field type
            typedef typename nxobject_field<VTYPE>::type field_type;
            //! Nexus attribute type
            typedef typename nxobject_attribute<VTYPE>::type attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param data reference to the data holding instance
            //! \param s selection of what to write
            //!
            write_visitor(const ATYPE &data,const selection_t &s=selection_t()):
                _data(data),
                _selection(s)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Cannot write data to a group - thus an exception is thrown.
            //! \throws nxgroup_error 
            //! \param g group instance
            //! \return nothing
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const group_type &g) const
            {
                throw nxgroup_error(EXCEPTION_RECORD,
                        "One cannot write data to a group object!");
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Write data to a field
            //! \throws nxfield_error in case of IO errors
            //! \param f field instance
            //! \return nothing
            //!
            result_type operator()(field_type &f) const
            {
                if(_selection.size())
                    f(_selection).write(_data);
                else
                    f.write(_data);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Write data to an attribute. If the selection member is not 
            //! empty an exception will be thrown as partial IO is not 
            //! supported on attributes.
            //!
            //! \throw nxattribute_error in case or IO errors or partial IO 
            //! on an attribute
            //! \param a attribute instance
            //! \return nothing
            //!
            result_type operator()(attribute_type &a) const
            {
                if(_selection.size())
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Partial IO currently not supported on attribute!");
                else
                    a.write(_data);
            }
    };

    //!
    //! \ingroup variant_code
    //! \brief write wrapper
    //!
    //! This function template is a wrapper for the write_visitor. It will 
    //! write data to the field or attribute stored in the variant type. 
    //! Partial IO is supported only for fields. As data cannot be written to a
    //! group an exception will be thrown if the object stored in the variant 
    //! type is a group object.
    //!
    //! Simple IO can be done with
    /*!
    \code{.cpp}
    darray<float64> data = ....;
    object_types field = get_object(root,path_to_field);

    //here the entire field is written 
    write(field,data);
    \endcode
    */
    //! Due to some limitations of the variadic template engine partial IO 
    //! has a bit unintuitive syntax. 
    /*!
    \code{.cpp}
    darray<float64> frame = ...;
    auto field = get_object(root,path_to_field);

    //here we write the slice (10,:1024,:512)
    write(field,frame,10,slice(0,1024),slice(0,512));
    \endcode
    */
    //! Partial IO is however only supported for field but not for attributes. 
    //! The following code will work
    /*!
    \code{.cpp}
    auto field = get_object(root,path_to_field);

    write(create_attribute<string>(field,"units"),"string");
    \endcode
    */
    //! but this one will not
    /*!
    \code{.cpp}
    auto field = get_object(root,path_to_field);

    auto attr = create_attribute<float32>(field,"tensor",shape_t{3,3});

    //this will fail
    write(attr,float32(1.23),0,0);
    \endcode
    */
    //! \throws nxgroup_error if stored object is a group
    //! \throws nxattribute_error for partial IO on an attribute
    //! \tparam ATYPE data holding type
    //! \tparam VTYPE variant type
    //! \tparam ITPYES index types
    //! \param o instance of VTYPE
    //! \param a instance of ATYPE with the data
    //! \param indices index type instances
    //! \return nothing
    //!
    template<
             typename ATYPE,
             typename VTYPE,
             typename ...ITYPES 
            > 
    typename write_visitor<ATYPE,VTYPE>::result_type 
    write(VTYPE &o,const ATYPE &a,ITYPES ...indices)
    {
        std::vector<slice> sel{slice(indices)...};
        return boost::apply_visitor(write_visitor<ATYPE,VTYPE>(a,sel),o);
    }

//end of namespace
}
}
}
