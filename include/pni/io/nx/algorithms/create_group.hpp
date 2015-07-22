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

#include <pni/core/types.hpp>
#include "../nxobject.hpp"
#include "get_object.hpp"
#include "utils.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_internal_code
    //! \brief create group visitor
    //!
    //! This visitor creates a group below the group stored in the variant 
    //! type.  If the stored object is not a group an exception will be 
    //! thrown. 
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \sa create_group
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class create_group_visitor : public boost::static_visitor<
                                    nxobject<GTYPE,FTYPE,ATYPE>  
                                 >
    {
        private:
            //! the name of the group
            pni::core::string _name; 
            //! the Nexus class of the group
            pni::core::string _class; 
        public:
            //! result type
            typedef nxobject<GTYPE,FTYPE,ATYPE> result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;

            //!
            //! \brief constructor
            //!
            //! Constructor of the visitor.
            //!
            //! \param n name of the group
            //! \param c class of the group
            //!
            create_group_visitor(const pni::core::string &n,
                                 const pni::core::string &c):
                _name(n),
                _class(c)
            {}

            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Create a new group of name _name and class _class below the 
            //! parent group g. The new group will be stored as object_types 
            //! variant.
            //!
            //! \throws invalid_object_error if the parent is not valid
            //! \throws object_error in case of any other error 
            //! \throws value_error if the name for the group was not set
            //!
            //! \param g parent group instance
            //! \return new group stored as object_types
            //!
            result_type operator()(const group_type &g) const
            {
                using namespace pni::core;
                
                group_type group;
                if(!_name.empty())
                {
                    if(!_class.empty())
                        group = g.create_group(_name,_class);
                    else
                        group = g.create_group(_name);
                }
                else
                    //you have to at least provide a name
                    throw value_error(EXCEPTION_RECORD,
                            "No name provided for the new group!");

                return result_type(group);

            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! A field cannot have a child group. Thus an exception will be 
            //! thrown. 
            //!
            //! \throws type_error  
            //!
            //! \param f field instance
            //! \return empty result type
            //!
            result_type operator()(const field_type &) const
            {
                using namespace pni::core;
                
                throw type_error(EXCEPTION_RECORD,
                        "Cannot create a group below a field!");
                return result_type();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! An attribute cannot create a group - thus an exception will be
            //! thrown.
            //!
            //! \throws type_error 
            //!
            //! \param a attribute instance
            //! \return an empty result type
            //!
            result_type operator()(const attribute_type &) const
            {
                using namespace pni::core;
                throw type_error(EXCEPTION_RECORD,
                        "Cannot create a group below an attribute!");
                return result_type();
            }
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief create_group wrapper
    //!
    //! Wrapper function for the create_group_visitor. This wrapper creates a 
    //! new group of a particular name and class directly below the parent 
    //! group.  In order to successfully create a group at least the name 
    //! argument must be non-empty. If an empty string is passed as the groups 
    //! class then the NX_class attribute will not be set.
    //! The function does not create intermediate groupw which do not exist.
    //! In this case an key_error exception will be thrown.
    //!
    //! \throws invalid_object_error if the parent is not valid
    //! \throws key_error if an element in the path provided by the user does
    //! not exist
    //! \throws type_error if the parent object is not a group
    //! \throws object_error in case of any other error
    //! \throws value_error if the user did not provide a name for the new
    //! group
    //! \throws io_error if metadata retrieval failed 
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam PATHT path type
    //!
    //! \param o reference to the parent 
    //! \param path the path or name of the new group
    //! \return object_types with the newly created group
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename PATHT
            > 
    nxobject<GTYPE,FTYPE,ATYPE>
    create_group(const nxobject<GTYPE,FTYPE,ATYPE> &o,const PATHT &path)
    {
        typedef create_group_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        typedef nxobject<GTYPE,FTYPE,ATYPE> object_type;

        nxpath parent_path(get_path(path));
        nxpath::element_type e = parent_path.back();
        parent_path.pop_back();

        object_type parent;

        if(parent_path.size())
            parent = get_object(o,parent_path);
        else
            parent = o;

        return boost::apply_visitor(visitor_type(e.first,e.second),parent);
    }

//end of namespace
}
}
}
