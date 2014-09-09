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
#include "is_field.hpp"
#include "get_name.hpp"
#include "is_class.hpp"
#include <type_traits>
#include <functional>

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_internal_code
    //! \brief object predicates 
    //! 
    //! This template class provides predicate methods for object selection. 
    //! 
    //! \tparam OTYPE object type
    //!
    template<typename OTYPE> struct object_predicates
    {
        typedef OTYPE object_type;
        typedef std::function<bool(const object_type &o)> function_type;
        typedef object_predicates<OTYPE> predicate_type;

        //--------------------------------------------------------------------
        //!
        //! \brief name predicate
        //!
        //! This predicate function returns true for a name match. This
        //! predicate can be applied to fields as well as groups.
        //!
        //! \throws invalid_object_error if the object is not valid
        //! \throws type_error if the type does not support name retrieval
        //! \throws io_error if name retrieval fails
        //! \throws object_error in case of any other error
        //!
        //! \param o object to check
        //! \param name the name to match
        //! \return true of o's name matches name
        //!
        static
        bool has_name(const OTYPE &o,const string &name)
        {
            return get_name(o) == name;
        }

        //--------------------------------------------------------------------
        //!
        //! \brief class match
        //!
        //! This predicate function returns true for a class match. If the 
        //! object is a field type the predicate returns false in any case.
        //! Naturally this predicate makes only sense for groups.
        //!
        //! \throws invalid_object_error if the object is not valid
        //! \throws shape_mismatch_error if the NX_class attribute is not 
        //! scalar
        //! \throws type_error if NX_class is of inappropriate type
        //! \throws io_error if attribute retrieval failed
        //! \throws object_error in case of any other error
        //! 
        //! \param o object to check
        //! \param c Nexus class name
        //! \return true if o's NX_class attribute matches c
        //!
        static
        bool has_class(const OTYPE &o,const string &c)
        { 
            if(is_field(o)) return false;
            return is_class(o,c);
        }

        //--------------------------------------------------------------------
        //!
        //! \brief name and class match
        //!
        //! This function returns true in the case of a name and class match.
        //! like the has_class predicate it makes only sense for groups.
        //!
        //! \throws invalid_object_error if the group is not valid
        //! \throws shape_mismatch_error if the NX_class attribute is not a 
        //! scalar
        //! \throws type_error if the NX_class attribute is not of string type
        //! \throws io_error if name or class retrieval fails
        //! \throws object_error in case of any other error
        //!
        //! \param o object to check
        //! \param n object name to match
        //! \param c object class to match
        //! \return true if o's class and name match n and c, false otherwise
        //!
        static
        bool has_name_and_class(const OTYPE &o,const string &n,const string &c)
        {
            if(is_field(o)) return false;
            return has_name(o,n) && has_class(o,c);
        }

        //--------------------------------------------------------------------
        //!
        //! \brief create predicate function
        //!
        //! Static function creating a predicate function which can be used 
        //! in an STL algorithm. 
        //!
        //! \throws key_error value_error if n and c are empty
        //! \throws object_error if the predicate creation fails for some 
        //! other reason.
        //! 
        //! \param n name to look for 
        //! \param c Nexus type to look for
        //! \return predicate function
        //!
        static function_type create(const string &n,const string &c)
        {
            using std::placeholders::_1;

            if(n.empty() && c.empty())
                throw key_error(EXCEPTION_RECORD,"'name' and 'class' field are"
                        "emtpy - do not know what to search for!");
            else if((!n.empty()) && (!c.empty()))
                //search for name and class
                return std::bind(&predicate_type::has_name_and_class,_1,n,c);
            else if((!n.empty()) && (c.empty()))
                return std::bind(&predicate_type::has_name,_1,n);
            else if((n.empty()) && (!c.empty()))
                return std::bind(&predicate_type::has_class,_1,c);
            else
                throw value_error(EXCEPTION_RECORD,
                        "Could not create predicate function!");
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
    //! \throws invalid_object_error if 
    //! \throws key_error if the requested object does not exist
    //! \throws value_error if no predicate function can be constructed 
    //! from n and c
    //! 
    //! \tparam OTYPE parent type
    //! \tparam IMPID implementation id of the parent
    //! \param parent reference to the parent object
    //! \param n name of the object
    //! \param c class of the object (only for groups)
    //! \return requested object as instance of nxobject
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    typename nxobject_trait<IMPID>::object_type
    get_child(const OTYPE<IMPID> &parent,const string &n,const string &c)
    {
        typedef typename nxobject_trait<IMPID>::field_type field_type;
        typedef typename nxobject_trait<IMPID>::attribute_type attribute_type;
        typedef typename nxobject_trait<IMPID>::object_type object_type;
        typedef object_predicates<object_type> predicate_type;
        typedef typename predicate_type::function_type function_type;

        static_assert(!std::is_same<object_type,field_type>::value,
                      "GROUP TYPE REQUIRED - GOT FIELD TYPE!");
        static_assert(!std::is_same<object_type,attribute_type>::value,
                      "GROUP TYPE REQUIRED - GOT ATTRIBUTE TYPE!");

        //if the group has no children at all searching is futile
        //better throw an exception here
        if(!parent.size()) 
            throw key_error(EXCEPTION_RECORD, "Group ["+get_name(parent)
                    +"] does not have any children!");

        //if we request the root group and g is already root - just
        //return root - need to do something about this
        if(((n == "/") && (n == parent.name())) || (n == "."))
            return object_type(parent);
        else if(n == "..")
            return object_type(parent.parent());
        
        //....................................................................
        //searching does not make too much sense if we have neither a
        //name or a class - better throw an exception here
        function_type predicate = predicate_type::create(n,c);

        //here is the important part
        auto result_iter = std::find_if(parent.begin(),parent.end(),predicate);

        //if the iterator is at the end position the object has not been 
        //found - throw an exception here
        if(result_iter == parent.end())
            throw key_error(EXCEPTION_RECORD,"Requested child with name ["+
                    n+"] not found!");

        return *result_iter;
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief get child visitor
    //! 
    //! Visitor wrapper for the get_child function.
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
            //!
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
