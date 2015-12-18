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
#include <pni/core/arrays/slice.hpp>
#include <vector>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief read data
    //! 
    //! Read data form an attribute or field type instance.  This function 
    //! tempalte reads the entire content of the field or attribute. 
    //! The exceptions which are thrown here depend on ATYPE. 
    //! 
    //! \throws invalid_object_error if the field is not valid
    //! \throws io_error if reading the data fails
    //! \throws type_error if the data type of ATYPE is not supported
    //! \throws memory_not_allocated_error if ATYPE is an array type and its
    //! internal buffer has no memory associated with it
    //! \throws size_mismatch_error if the number of elements of ATYPE and the 
    //! field do not match
    //! \throws object_error in case of any other error
    //! 
    //! \tparam OTYPE object template 
    //! \tparam IMPID implementation ID for the object
    //! \tparam ATYPE array type where to store the data
    //! 
    //! \param o field or attribute instance
    //! \param a container instance
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID,
             typename ATYPE
            >
    void read(const OTYPE<IMPID> &o,ATYPE &a)
    {
        typedef nxobject_trait<IMPID> trait_type;
        typedef typename trait_type::field_type field_type;
        typedef typename trait_type::attribute_type attribute_type;

        static_assert(std::is_same<OTYPE<IMPID>,field_type>::value || 
                      std::is_same<OTYPE<IMPID>,attribute_type>::value,
                      "WRITE CAN ONLY BE USED WITH FIELDS AND "
                      "ATTRIBUTES!");
        o.read(a);
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief read data
    //! 
    //! Read data form an attribute or field type instance. This function 
    //! allows reading only a part of the field by passing a multiindex 
    //! selection to the function.
    //! The exceptions which are thrown here depend on ATYPE. 
    //! 
    //! \throws shape_mismatch_error if selection and field rank do not match
    //! \throws invalid_object_error if the field is not valid
    //! \throws io_error if reading the data fails
    //! \throws type_error if the data type of ATYPE is not supported
    //! \throws memory_not_allocated_error if ATYPE is an array type and its
    //! internal buffer has no memory associated with it
    //! \throws size_mismatch_error if the number of elements of ATYPE and the 
    //! field do not match
    //! \throws object_error in case of any other error
    //! 
    //! \tparam OTYPE object template 
    //! \tparam IMPID implementation ID for the object
    //! \tparam ATYPE array type where to store the data
    //! \tparam ITYPES index types
    //! 
    //! \param o field or attribute instance
    //! \param a container instance
    //! \param indices selection indices passed as variadic arguments
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID,
             typename ATYPE,
             typename ...ITYPES
            >
    void read(const OTYPE<IMPID> &o,ATYPE &a,ITYPES ...indices)
    {
        typedef nxobject_trait<IMPID> trait_type;
        typedef typename trait_type::field_type field_type;
        typedef typename trait_type::attribute_type attribute_type;

        static_assert(std::is_same<OTYPE<IMPID>,field_type>::value || 
                      std::is_same<OTYPE<IMPID>,attribute_type>::value,
                      "WRITE CAN ONLY BE USED WITH FIELDS AND "
                      "ATTRIBUTES!");

        o(indices...).read(a);
    }
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief read visitor
    //!
    //! \tparam ATYPE target array type
    //! \tparam GTYPE group type
    //! \tparam FTYPE field_type
    //! \tparam ATTYPE attribute type
    //!
    template<
             typename ATYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATTYPE
            > 
    class read_visitor : public boost::static_visitor<void>
    {
        public: 
            //! selection type for partial IO
            typedef std::vector<pni::core::slice> selection_t;
        private:
            //! reference to the data holding object
            ATYPE &_data;
            //! selection vector
            selection_t _selection;
        public:
            //! result type
            typedef void result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATTYPE attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param data reference to the data holding instance
            //! \param s selection of what to read
            //!
            read_visitor(ATYPE &data,const selection_t &s=selection_t()):
                _data(data),
                _selection(s)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Cannot read data to a group - thus an exception is thrown.
            //! \throws nxgroup_error 
            //! \param g group instance
            //! \return nothing
            //!
            result_type operator()(const group_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "One cannot read data to a group object!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Read data from a field
            //!
            //! \throws shape_mismatch_error if selection and field rank do not
            //! match
            //! \throws invalid_object_error if the field is not valid
            //! \throws io_error if reading the data fails
            //! \throws type_error if the data type of ATYPE is not supported
            //! \throws memory_not_allocated_error if ATYPE is an array type 
            //! and its internal buffer has no memory associated with it
            //! \throws size_mismatch_error if the number of elements of 
            //! ATYPE and the field do not match
            //! \throws object_error in case of any other error
            //!
            //! \param f field instance
            //! \return nothing
            //!
            result_type operator()(const field_type &f) const
            {
                if(_selection.size())
                    f(_selection).read(_data);
                else
                    f.read(_data);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Read data from an attribute. If the selection member is not 
            //! empty an exception will be thrown as partial IO is not 
            //! supported on attributes.
            //!
            //! \throws invalid_object_error if the field is not valid
            //! \throws io_error if reading the data fails
            //! \throws type_error if the data type of ATYPE is not supported
            //! \throws memory_not_allocated_error if ATYPE is an array type 
            //! and its internal buffer has no memory associated with it
            //! \throws size_mismatch_error if the number of elements of 
            //! ATYPE and the field do not match
            //! \throws object_error in case of any other error
            //! 
            //! \param a attribute instance
            //! \return nothing
            //!
            result_type operator()(const attribute_type &a) const
            {
                if(_selection.size())
                    a(_selection).read(_data);
                else
                    a.read(_data);
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief read data from a field or attribute
    //!
    //! This function template is a wrapper for the read_visitor. It will 
    //! read data from the field or attribute stored in the variant type. 
    //! Partial IO is supported only for fields. As data cannot be read from a
    //! group an exception will be thrown if the object stored in the variant 
    //! type is a group object.
    //!
    //! \throws shape_mismatch_error if selection and field rank do not match
    //! \throws invalid_object_error if the field is not valid
    //! \throws io_error if reading the data fails
    //! \throws type_error if the data type of ATYPE is not supported
    //! \throws memory_not_allocated_error if ATYPE is an array type and its
    //! internal buffer has no memory associated with it
    //! \throws size_mismatch_error if the number of elements of ATYPE and the 
    //! field do not match
    //! \throws object_error in case of any other error
    //!
    //! \tparam ATYPE target type for the read 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATTYPE attribute type
    //! \tparam ITPYES index types
    //!
    //! \param o instance of VTYPE
    //! \param a instance of ATYPE with the data
    //! \param indices index type instances
    //! \return nothing
    //!
    template<typename ATYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATTYPE,
             typename ...ITYPES 
            > 
    void read(const nxobject<GTYPE,FTYPE,ATTYPE> &o,ATYPE &a,ITYPES ...indices)
    {
        typedef read_visitor<ATYPE,GTYPE,FTYPE,ATTYPE> visitor_t;
        std::vector<pni::core::slice> sel{pni::core::slice(indices)...};
        visitor_t visitor(a,sel);
        return boost::apply_visitor(visitor,o);
    }

    //------------------------------------------------------------------------
    template<typename ATYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATTYPE,
             typename ...ITYPES 
            > 
    void read(nxobject<GTYPE,FTYPE,ATTYPE> &&o,ATYPE &a,ITYPES ...indices)
    {
        typedef read_visitor<ATYPE,GTYPE,FTYPE,ATTYPE> visitor_t;
        std::vector<pni::core::slice> sel{pni::core::slice(indices)...};
        visitor_t visitor(a,sel);
        return boost::apply_visitor(visitor,o);
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief read data from a field or attribute
    //!
    //! This function template is a wrapper for the read_visitor. It will 
    //! read data from the field or attribute stored in the variant type. 
    //! Partial IO is supported only for fields. As data cannot be read from a
    //! group an exception will be thrown if the object stored in the variant 
    //!  
    //! \throws shape_mismatch_error if selection and field rank do not match
    //! \throws invalid_object_error if the field is not valid
    //! \throws io_error if reading the data fails
    //! \throws type_error if the data type of ATYPE is not supported or the
    //! object passed by the user holds a group instance
    //! \throws memory_not_allocated_error if ATYPE is an array type and its
    //! internal buffer has no memory associated with it
    //! \throws size_mismatch_error if the number of elements of ATYPE and the 
    //! field do not match
    //! \throws object_error in case of any other error
    //!
    //! \tparam ATYPE target type for the read 
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATTYPE attribute type
    //! \tparam ITPYES index types
    //!
    //! \param o instance of VTYPE
    //! \param a instance of ATYPE with the data
    //! \param sel selection from which to read
    //! \return nothing
    //!
    template<
             typename ATYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATTYPE
            >
    void read(const nxobject<GTYPE,FTYPE,ATTYPE> &o,ATYPE &a,
              const std::vector<pni::core::slice> &sel)
    {
        typedef read_visitor<ATYPE,GTYPE,FTYPE,ATTYPE> visitor_t;
        visitor_t visitor(a,sel);
        return boost::apply_visitor(visitor,o);
    }

    //------------------------------------------------------------------------
    template<
             typename ATYPE,
             typename GTYPE,
             typename FTYPE,
             typename ATTYPE
            >
    void read(nxobject<GTYPE,FTYPE,ATTYPE> &&o,ATYPE &a,
                       const std::vector<pni::core::slice> &sel)
    {
        typedef read_visitor<ATYPE,GTYPE,FTYPE,ATTYPE> visitor_t;
        visitor_t visitor(a,sel);
        return boost::apply_visitor(visitor,o);
    }
//end of namespace
}
}
}
