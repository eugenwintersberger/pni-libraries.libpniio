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
// Created on: Sep 12, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/error.hpp>
#include "../nxobject.hpp"
#include "../nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get iterator to first element
    //!
    //! Returns an iterator to the first child element of a group object. 
    //! 
    //! \param group reference to a group instance
    //! \return iterator to first child
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    auto begin(const OTYPE<IMPID> &group) -> decltype(group.begin())
    {
        using group_type = typename nxobject_trait<IMPID>::group_type;
        static_assert(std::is_same<group_type,OTYPE<IMPID>>::value,
                      "Object must be a group type!");

        return group.begin();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get iterator to last element
    //! 
    //! Returns an iterator to the last+1 child of a group. 
    //! 
    //! \param group reference to the group instance
    //! \return iterator to last+1 element
    //! 
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    auto end(const OTYPE<IMPID> &group) -> decltype(group.end())
    {
        using group_type = typename nxobject_trait<IMPID>::group_type;
        static_assert(std::is_same<group_type,OTYPE<IMPID>>::value,
                      "Object must be a group type!");

        return group.end();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get iterator to first element
    //! 
    //! This visitor returns an iterator to the first child attached to a group
    //! or throws a type_error exception of the passed nxobject instance is not
    //! a group.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class begin_visitor : public boost::static_visitor<typename GTYPE::iterator>
    {
        public:
            //! result type
            using result_type = typename GTYPE::iterator;
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
            //!\brief process groups
            //!
            result_type operator()(const group_type &g) const
            {
                return begin(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //!
            //! Throws type_error as fields do not have children over which 
            //! we can iterate.
            //!
            //! \throws type_error in any case
            //! \param f field instance
            //! \return to be ignored
            //!
            result_type operator()(const field_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Fields do not have children!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Throws type_error - an attribute does not have an interator.
            //!
            //! \throws type_error in any case
            //! \param a attribute instance
            //! \return to be ignored
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief process links
            //!
            //! Throws type_error - links does not have an interator.
            //!
            //! \throws type_error in any case
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "links do not have children!");

            }
    };

    //========================================================================
    //!
    //! \ingroup algorithm_code
    //! \brief get iterator to first child
    //!
    //! Returns an iterator to the first child attached to a group stored 
    //! in an nxobject instance. If the nxobject instance does not hold 
    //! a group type_error is thrown.
    //!
    //! \throws type_error if the stored object is not a group
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //! \param o group object
    //! \return iterator to the first child
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    typename GTYPE::iterator
    begin(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = begin_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get iterator to last element
    //! 
    //! Returns the iterator to the last+1 element attached to a group instance. 
    //! If the nxobject instanced passed does not hold a group instance 
    //! type_error is thrown
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    class end_visitor : public boost::static_visitor<typename GTYPE::iterator>
    {
        public:
            //! result type
            using result_type = typename GTYPE::iterator;
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
            //!\brief process groups
            //!
            result_type operator()(const group_type &g) const
            {
                return end(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //! 
            //! \throws type_error in any case 
            //!
            //! \param f field instance
            //! \return to be ignored
            //!
            result_type operator()(const field_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Fields do not have children!");
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! \throws type_error in any case
            //! \param a attribute instance
            //! \return to be ignored
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
            
            //-----------------------------------------------------------------
            //!
            //! \brief process links
            //!
            //! \throws type_error in any case
            //!
            result_type operator()(const link_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Links do not have children!");

            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get iterator to last+1 child
    //!
    //! Return an interator to the last+1 child attached to a group stored 
    //! in an instance of nxobject or throw type_error if the nxobject 
    //! instance does not hold  a gruop.
    //!
    //! \throws type_error if the stored object is not a group
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link type
    //! \param o the group from which we want the iterator
    //! \return iterator to last+1 child 
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    typename GTYPE::iterator
    end(const nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = end_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }
//end of namespace
}
}
}

    


