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
// Created on: Jul 1, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject_traits.hpp"
#include "is_group.hpp"
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include "is_valid.hpp"
#include <type_traits>
#include <functional>

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

namespace pni{
namespace io{
namespace nx{

    
    template<typename OTYPE> struct object_predicates
    {
        static
        bool has_name(const OTYPE &o,const string &name)
        {
            return get_name(o) == name;
        }

        static
        bool has_class(const OTYPE &o,const string &c)
        { 
            if(is_field(o)) return false;
            return is_class(o,c);
        }

        static
        bool has_name_and_class(const OTYPE &o,const string &n,const string &c)
        {
            if(is_field(o)) return false;
            return has_name(o,n) && has_class(o,c);
        }

    };


    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief get child from parent
    //! 
    //! Retrieve a child from a parent. Currently the parent can only be a 
    //! group type. 
    //!
    //! \throws key_error if the requested object does not exist
    //! 
    //! \tparam OTYPE parent type
    //! \tparam IMPID implementation id of the parent
    //! \param parent reference to the parent object
    //! \param n name of the object
    //! \param c class of the object (only for groups)
    //! \return requested object as instance of nxobject
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    nxobject<
             typename nxobject_trait<IMPID>::group_type,
             typename nxobject_trait<IMPID>::field_type,
             typename nxobject_trait<IMPID>::attribute_type
            >
    get_child(const OTYPE<IMPID> &parent,const string &n,const string &c)
    {
        typedef OTYPE<IMPID> parent_type;
        typedef typename nxobject_trait<IMPID>::field_type field_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;
        typedef typename nxobject_trait<IMPID>::group_type group_type;
        typedef nxobject<group_type,field_type,attribute_type> object_type;
        typedef object_predicates<object_type> predicate_type;
        typedef std::function<bool(const object_type &o)> function_type;
        using std::placeholders::_1;

        static_assert(!std::is_same<object_type,field_type>::value,
                      "GROUP TYPE REQUIRED - GOT FIELD TYPE!");
        static_assert(!std::is_same<object_type,attribute_type>::value,
                      "GROUP TYPE REQUIRED - GOT ATTRIBUTE TYPE!");

        //searching does not make too much sense if we have neither a
        //name or a class - better throw an exception here
        function_type predicate;
        if(n.empty() && c.empty())
            throw key_error(EXCEPTION_RECORD,"'name' and 'class' field are"
                    "emtpy - do not know what to search for!");
        else if((!n.empty()) && (!c.empty()))
            //search for name and class
            predicate = std::bind(&predicate_type::has_name_and_class,_1,n,c);
        else if((!n.empty()) && (c.empty()))
            predicate = std::bind(&predicate_type::has_name,_1,n);
        else if((n.empty()) && (!c.empty()))
            predicate = std::bind(&predicate_type::has_class,_1,c);


        //if the group has no children at all searching is futile
        //better throw an exception here
        if(!parent.nchildren()) return object_type(field_type());

        //if we request the root group and g is already root - just
        //return root - need to do something about this
        if((n == "/") && (n == parent.name()))
            return object_type(parent);

        //need to do some treatment for the special cases . and .. as
        //child names 
        if(n == ".") return object_type(parent);
        if(n == "..") return object_type(parent.parent());
        
        auto result_iter = std::find_if(parent.begin(),parent.end(),predicate);
        if(result_iter == parent.end())
            throw key_error(EXCEPTION_RECORD,"Requested child with name ["+
                    n+"] not found!");

        return *result_iter;
    }


    //!
    //! \ingroup variant_code
    //! \brief get child visitor
    //! 
    //! Retrieves a child object form an object stored in a variant type. 
    //! Virtually the only object where this will work are groups. 
    //! Children can be selected by two criteria: their name and their 
    //! class. Though, the class name is only evaluated if we are 
    //! looking for a group.
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
    class get_child_visitor : public boost::static_visitor<
                              nxobject<GTYPE,FTYPE,ATYPE> 
                              >
    {
        private: 
            string _name;  //!< name of the object
            string _class; //!< object class (in case of a group)
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
            //! \param n name of the child
            //! \param c Nexus class of the child
            //!
            get_child_visitor(const string &n,const string &c):
                _name(n),
                _class(c)
            {}
           
            //-----------------------------------------------------------------
            //!
            //!\brief process groups
            //!
            //! Groups are currently the only objects that can have children. 
            //! This method iterates over all children of a group and checks 
            //! if the criteria (name and class) match. If the child is a 
            //! field only the name is of importance. In case of a group 
            //! also the class will be checked. If none of the child objects 
            //! matches the criteria an invalid object will be returned.
            //!
            //! There are two special group names '.' and '..' which are 
            //! treated in a special way. In the former case the current 
            //! group is returned (in other words nothing is done) while in 
            //! the latter case the parent group of the current group is 
            //! returned. 
            //!
            //! This method should throw no exceptions. 
            //! \param g group instance
            //! \return child object
            //!
            result_type operator()(const group_type &g) const
            {
                return get_child(g,_name,_class);
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
                throw nxfield_error(EXCEPTION_RECORD,
                        "Fields do not have children!");
            }
#pragma GCC diagnostic pop

            //-----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! Like fields attributes cannot have children - throw an 
            //! exception here.
            //!
            //! \throws nxattribute_error no children for attributes
            //! \param a attribute instance
            //! \return to be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw nxattribute_error(EXCEPTION_RECORD,
                        "Attributes do not have children!");

            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief get child wrapper
    //!
    //! Wrapper function for the get_child_visitor template. 
    //!
    //! \throws nxfield_error if the stored object is a field
    //! \throws nxattribute_error if the stored object is an attribute
    //! \throws key_error if the requested child does not exist
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o parent object as nxobject
    //! \param n the childs name
    //! \param c the childs class (only for groups)
    //! \return the requested child as nxobject
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    nxobject<GTYPE,FTYPE,ATYPE>
    get_child(const nxobject<GTYPE,FTYPE,ATYPE> &o,const string &n,
              const string &c)
    {
        typedef get_child_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(n,c),o);
    }

//end of namespace
}
}
}
