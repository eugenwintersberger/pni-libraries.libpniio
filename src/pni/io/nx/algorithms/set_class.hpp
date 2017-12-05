//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: May 29, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include <pni/io/nx/nxobject_traits.hpp>
#include <pni/io/nx/algorithms/is_group.hpp>

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief set class for a group
    //!
    //! Sets the NX_class attribute at a group to a particular value. 
    //!
    //! \throws type_error if o is not a group
    //! \throws invalid_object_error if the group is not valid
    //! \throws type_error if the data type is not supported
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE object template
    //! \tparam IMPID implementation ID of the object
    //!
    //! \param o group instance for which to set NX_class
    //! \param nxclass the value of NX_class
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    void set_class(const OTYPE<IMPID> &o,const pni::core::string &nxclass)
    {
        using namespace pni::core;
        typedef typename nxobject_trait<IMPID>::object_type object_type;
        typedef typename nxobject_trait<IMPID>::field_type field_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;

        static_assert(!std::is_same<OTYPE<IMPID>,field_type>::value,
                      "EXEPCTED A GROUP TYPE - GOT A FIELD!");
        static_assert(!std::is_same<OTYPE<IMPID>,attribute_type>::value,
                      "EXPECTED A GROUP TYPE - GOT AN ATTRIBUTE!");

        if(!is_group(object_type(o)))
            throw type_error(EXCEPTION_RECORD,
                             "Cannot set the nexus class for a non-group "
                             "object!");

        auto attr = o.attributes.template create<string>("NX_class",true);
        attr.write(nxclass);
    }

    
    //!
    //! \ingroup algorithm_internal_code
    //! \brief set class visitor
    //!
    //! This visitor sets the class on a Nexus group stored in a variant type.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //! \sa set_class
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class set_class_visitor : public boost::static_visitor<void>
    {
        private:
            pni::core::string _class; //!< Nexus class
        public:
            //! result type
            using result_type = void;
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
            //! \brief constructor
            //!
            //! \param s class type as string
            //!
            set_class_visitor(const pni::core::string &s):_class(s) {}

            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! \throws type_error if o is not a group
            //! \throws invalid_object_error if the group is not valid
            //! \throws type_error if the data type is not supported
            //! \throws object_error in case of any other error
            //!
            //! \param g group instance
            //! \return nothing
            //!
            result_type operator()(const group_type &g) const
            {
                set_class(g,_class);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! \throws type_error cannot set the type of a field
            //!
            //! \param f field instance
            //! \return nothing
            //!
            result_type operator()(const field_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,"Fields do not have a class!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! \throws type_error cannot set the type of an attribute
            //!
            //! \param a attribute instance
            //! \return nothing
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have a class!");
            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief process links
            //!
            //! \throws type_error cannot set the type of link
            //!
            //! \return nothing
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Links do not have a class!");
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief set class 
    //!
    //! Set the NX_class attribute for a group stored in an instance of 
    //! nxobject.
    //!
    //! \throws type_error if o is not a group
    //! \throws invalid_object_error if the group is not valid
    //! \throws type_error if the data type is not supported
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    //! \param o group as instance of nxobject
    //! \param c Nexus class as string
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    void set_class(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o,
                   const pni::core::string &c)
    {
        using visitor_type = set_class_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        boost::apply_visitor(visitor_type(c),o);
    }

//end of namespace
}
}
}
