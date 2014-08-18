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

#include <sstream>
#include <type_traits>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"
#include "is_group.hpp"
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include "is_valid.hpp"
#include "get_size.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief return child by index
    //!
    //! Returns the child of a group by its index. 
    //! 
    //! \tpatram OTYPE object type (a group)
    //! \tparam IMPID implementation ID
    //! \param o group object 
    //! \param index the index of the child
    //! \return child object as nxobject instance
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    nxobject<
             typename nxobject_trait<IMPID>::group_type,
             typename nxobject_trait<IMPID>::field_type,
             typename nxobject_trait<IMPID>::attribute_type
            >
    get_child_by_index(const OTYPE<IMPID> &o,size_t index)
    {
        typedef OTYPE<IMPID> object_type;
        typedef typename nxobject_trait<IMPID>::field_type field_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;
        static_assert(!std::is_same<object_type,field_type>::value,
                      "GROUP TYPE REQUIRED - GOT FIELD TYPE!");
        static_assert(!std::is_same<object_type,attribute_type>::value,
                      "GROUP TYPE REQUIRED - GOT ATTRIBUTE TYPE!");

        if(index>=o.size())
        {
            std::stringstream ss;
            ss<<"Index "<<index<<" exceeds total number of ";
            ss<<" children "<<o.size()<<"!";

            throw index_error(EXCEPTION_RECORD,ss.str());
        }

        //here comes the interesting part
        return o[index]; 
    }
        

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get child by index visitor
    //! 
    //! Retrieves the child of a group according to its index. Clearly this 
    //! works only for groups. In case of attributes and fields an exception 
    //! is thrown.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class get_child_by_index_visitor : public boost::static_visitor<
                                       nxobject<GTYPE,FTYPE,ATYPE> 
                                       >
    {
        private: 
            //! index of the child
            size_t _index;
        public:
            //! result type
            typedef nxobject<GTYPE,FTYPE,ATYPE> result_type;
             
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param index the index of the element
            //!
            get_child_by_index_visitor(size_t index): _index(index) {}
           
            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //! 
            //! Returns the child of a group identified by its index. If the 
            //! index exceeds the total number of elements an index_error 
            //! exception will be thrown.
            //!
            //! \throws pni::core::index_error if index exceeds total number 
            //! of children
            //! \param g group instance
            //! \return child object
            //!
            result_type operator()(const group_type &g) const
            {
                return get_child_by_index(g,_index);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Fields cannot have children - throw an exception here.
            //! \throws nxfield_error no children for fields
            //! \param f field instance
            //! \return to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const field_type &f) const
            {
                throw type_error(EXCEPTION_RECORD,
                        "Fields do not have children!");
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Like fields attributes cannot have children - throw an 
            //! exception here.
            //! \throws nxattribute_error no children for attributes
            //! \param a attribute instance
            //! \return to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
#pragma GCC diagnostic pop
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get child by index wrapper
    //!
    //! Wrapper function for the get_child_by_index_visitor template. 
    //! \throws nxfield_error if the stored object is a field
    //! \throws nxattribute_error if the stored object is an attribute
    //! \throws index_error if the index exceeds the number of children
    //! \throws type_error if the Nexus object is of unknown type
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o parent as nxobject
    //! \param i index of the child
    //! \return requested child as nxobject instance
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    nxobject<GTYPE,FTYPE,ATYPE> 
    get_child_by_index(const nxobject<GTYPE,FTYPE,ATYPE> &o,size_t i)
    {
        typedef get_child_by_index_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(i),o);
    }

//end of namespace
}
}
}
