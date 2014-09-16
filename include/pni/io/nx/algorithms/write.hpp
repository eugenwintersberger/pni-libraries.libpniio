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

    //------------------------------------------------------------------------
    //! 
    //! \ingroup algorithm_code
    //! \brief write data to an attribute or field
    //!
    //! This function writes the entire data from a field. 
    //! 
    //! \throws invalid_object_error if the field is not valid
    //! \throws io_error if writing the data fails
    //! \throws type_error if the data type of ATYPE is not supported
    //! \throws memory_not_allocated_error if ATYPE is an array type and its
    //! internal buffer has no memory associated with it
    //! \throws size_mismatch_error if the number of elements of ATYPE and the 
    //! field do not match
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID of the object
    //! \tparam ATYPE storage type where the data is stored
    //!
    //! \param o object instance to which to write the data
    //! \param a instance from which to write the data
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID,
             typename ATYPE
            >
    void write(const OTYPE<IMPID> &o,const ATYPE &a)
    {
        typedef nxobject_trait<IMPID> trait_type;
        typedef typename trait_type::field_type field_type;
        typedef typename trait_type::attribute_type attribute_type;

        static_assert(std::is_same<OTYPE<IMPID>,field_type>::value || 
                      std::is_same<OTYPE<IMPID>,attribute_type>::value,
                      "WRITE CAN ONLY BE USED WITH FIELDS AND "
                      "ATTRIBUTES!");
        o.write(a);
    }

    //------------------------------------------------------------------------
    //! 
    //! \ingroup algorithm_code
    //! \brief write data to an attribute or field
    //!
    //! This function writes the entire data from a field. 
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
    //! \tparam IMPID implementation ID of the object
    //! \tparam ATYPE storage type where the data is stored
    //! \tparam ITYPES index types 
    //!
    //! \param o object instance to which to write the data
    //! \param a instance from which to write the data
    //! \param indices selection indices passed as variadic arguments
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID,
             typename ATYPE,
             typename ...ITYPES
            >
    void write(const OTYPE<IMPID> &o,const ATYPE &a,ITYPES ...indices)
    {
        typedef nxobject_trait<IMPID> trait_type;
        typedef typename trait_type::field_type field_type;
        typedef typename trait_type::attribute_type attribute_type;

        static_assert(std::is_same<OTYPE<IMPID>,field_type>::value || 
                      std::is_same<OTYPE<IMPID>,attribute_type>::value,
                      "WRITE CAN ONLY BE USED WITH FIELDS AND "
                      "ATTRIBUTES!");
        
        o(indices...).write(a);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief write visitor
    //!
    //! \tparam ATYPE source type
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam AATYPE attribute type
    //!
    //! \sa write
    //!
    template<
             typename ATYPE,
             typename GTYPE,
             typename FTYPE,
             typename AATYPE
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
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef AATYPE attribute_type;

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
                throw type_error(EXCEPTION_RECORD,
                        "One cannot write data to a group object!");
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Write data to a field
            //!
            //! \throws shape_mismatch_error if selection and field rank do not
            //! match
            //! \throws invalid_object_error if the field is not valid
            //! \throws io_error if writing the data fails
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
            //! \throws invalid_object_error if the field is not valid
            //! \throws io_error if reading the data fails
            //! \throws type_error if the data type of ATYPE is not supported or
            //! the selection is not empty
            //! \throws memory_not_allocated_error if ATYPE is an array type 
            //! and its internal buffer has no memory associated with it
            //! \throws size_mismatch_error if the number of elements of 
            //! ATYPE and the field do not match
            //! \throws object_error in case of any other error
            //!
            //! \param a attribute instance
            //! \return nothing
            //!
            result_type operator()(attribute_type &a) const
            {
                if(_selection.size())
                    throw type_error(EXCEPTION_RECORD,
                            "Partial IO currently not supported on attribute!");
                else
                    a.write(_data);
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief write wrapper
    //!
    //! This function template is a wrapper for the write_visitor. It will 
    //! write data to the field or attribute stored in the variant type. 
    //! Partial IO is supported only for fields. As data cannot be written to a
    //! group an exception will be thrown if the object stored in the variant 
    //! type is a group object.
    //!
    //! \throws shape_mismatch_error if selection and field rank do not match
    //! \throws invalid_object_error if the field is not valid
    //! \throws io_error if writing the data fails
    //! \throws type_error if the data type of ATYPE is not supported
    //! \throws memory_not_allocated_error if ATYPE is an array type and its
    //! internal buffer has no memory associated with it
    //! \throws size_mismatch_error if the number of elements of ATYPE and the 
    //! field do not match
    //! \throws object_error in case of any other error
    //!
    //! \tparam ATYPE data holding type
    //! \tparam VTYPE variant type
    //! \tparam ITPYES index types
    //! \param o instance of VTYPE
    //! \param a instance of ATYPE with the data
    //! \param indices index type instances
    //!
    template<
             typename ATYPE,
             typename GTYPE,
             typename FTYPE,
             typename AATYPE,
             typename ...ITYPES 
            > 
    void write(nxobject<GTYPE,FTYPE,AATYPE> &o,const ATYPE &a,ITYPES ...indices)
    {
        typedef write_visitor<ATYPE,GTYPE,FTYPE,AATYPE> visitor_type;
        std::vector<slice> sel{slice(indices)...};
        return boost::apply_visitor(visitor_type(a,sel),o);
    }

//end of namespace
}
}
}
