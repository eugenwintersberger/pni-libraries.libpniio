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

#ifdef NOFOREACH
#include <boost/foreach.hpp>
#endif

namespace pni{
namespace io{
namespace nx{


    //!
    //! \ingroup variant_code
    //! \brief get child visitor
    //! 
    //! Retrieves a child object form an object stored in a variant type. 
    //! Virtually the only object where this will work are groups. 
    //! Children can be selected by two criteria: their name and their 
    //! class. Though, the class name is only evaluated if we are 
    //! looking for a group.
    //! \tparam VTYPE variant type
    //!
    template<typename VTYPE> 
    class get_child_visitor : public boost::static_visitor<VTYPE>
    {
        private: 
            string _name;  //!< name of the object
            string _class; //!< object class (in case of a group)
        public:
            //! result type
            typedef VTYPE result_type;
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
                //here comes the interesting part
                result_type result; 

                //searching does not make too much sense if we have neither a
                //name or a class - better throw an exception here
                if(_name.empty() && _class.empty())
                    return result_type(field_type());

                //if the group has no children at all searching is futile
                //better throw an exception here
                if(!g.nchildren()) return result_type(field_type());

                //if we request the root group and g is already root - just
                //return root
                if((_name == "/") && (_name == g.name()))
                    return result_type(g);

                //need to do some treatment for the special cases . and .. as
                //child names 
                if(_name == ".") return result_type(g);
                if(_name == "..") return result_type(g.parent());

                for(auto child: g)
                {
                    if(is_group(child))
                    {
                        //check here for name and type
                        if(_name.empty())
                        {
                            //we only need to check for the class
                            if(pni::io::nx::is_class(child,_class)) 
                                return child;
                        }
                        else 
                        {
                            //we definitly need to check the name
                            if(get_name(child) == _name)
                            {
                                if(_class.empty()) return child;
                                else if(pni::io::nx::is_class(child,_class))
                                    return child;
                            }
                        }
                        continue;
                    }
                    else if(is_field(child))
                    {
                        //check here only for the name
                        if(get_name(child)!=_name) continue;

                        return child;
                    }
                }

                //in the worst case we return an invalid object
                return result_type();
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
    //! \ingroup variant_code
    //! \brief get child wrapper
    //!
    //! Wrapper function for the get_child_visitor template. 
    //!
    //! \throws nxfield_error if the stored object is a field
    //! \throws nxattribute_error if the stored object is an attribute
    //! \tparam VTYPE variant type
    //! \param o instance of VTYPE
    //! \param n name of the child
    //! \param c class of the child (only for groups)
    //! \return child object
    //!
    template<typename VTYPE> 
    typename get_child_visitor<VTYPE>::result_type
    get_child(const VTYPE &o,const string &n,const string &c)
    {
        return boost::apply_visitor(get_child_visitor<VTYPE>(n,c),o);
    }

//end of namespace
}
}
}
