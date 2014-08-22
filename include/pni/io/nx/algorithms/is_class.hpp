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

#include "../nxobject_traits.hpp"
#include "get_class.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief checks group type
    //!
    //! This function template checks whether or not a group is of a particular
    //! type. 
    //!
    //! \throws invalid_object_error if parent group is not valid
    //! \throws shape_mismatch_error the attribute is not a scalar
    //! \throws type_error the attribute type is not supported
    //! \throws io_error attribute data retrieval failed
    //! \throws object_error in case of any other error
    //!
    //! \tparam OTYPE nexus object template
    //! \tparam IMPID implementation ID of the object
    //!
    //! \param object the group to check
    //! \param type the type we want ot check for
    //! \return true if the group is of that type, false otherwise
    //!
    template<
             template<nximp_code> class OTYPE,
             nximp_code IMPID
            >
    bool is_class(const OTYPE<IMPID> &object,const string &type)
    {
        return get_class(object)==type;
    }

    //!
    //! \ingroup algorithm_internal_code
    //! \brief is class visitor
    //!
    //! This visitor is used to check the class a group belongs too.
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
    class is_class_visitor : public boost::static_visitor<bool>
    {
        private:
            string _class; //!< class type
        public:
            //! result type
            typedef bool result_type;
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
            //! \param s class type
            //!
            is_class_visitor(const string &s):_class(s) {}
           
            //-----------------------------------------------------------------
            //!
            //! \brief process groups
            //!
            //! \throws invalid_object_error if parent group is not valid
            //! \throws shape_mismatch_error the attribute is not a scalar
            //! \throws type_error the attribute type is not supported
            //! \throws io_error attribute data retrieval failed
            //! \throws object_error in case of any other error
            //!
            //! \param g group instance
            //! \return true if class types match, false otherwise
            //!
            result_type operator()(const group_type &g) const
            {
                return is_class(g,_class);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process fields
            //! 
            //! \throws type_error fields do not have a class
            //! \param f field instance
            //! \return can be ignored 
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const field_type &f) const
            {
                throw type_error(EXCEPTION_RECORD,
                        "Fields do not have a class!");
                return false;
            }
#pragma GCC diagnostic pop

            //----------------------------------------------------------------
            //!
            //! \brief process attributes
            //!
            //! \throws type_error attributes have no class
            //! \param a attribute instance
            //! \return can be ignored
            //!
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
            result_type operator()(const attribute_type &a) const
            {
                throw type_error(EXCEPTION_RECORD,
                        "Attributes do not have a class!");
                return false;
            }
#pragma GCC diagnostic pop
    };

    //!
    //! \ingroup algorithm_code
    //! \brief is class function
    //!
    //! Returns true if a group stored in an instance of nxobject is member
    //! of a particular class.
    //!
    //! \throws invalid_object_error if parent group is not valid
    //! \throws shape_mismatch_error the attribute is not a scalar
    //! \throws type_error the attribute type is not supported
    //! \throws io_error attribute data retrieval failed
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //!
    //! \param o instance of nxobject
    //! \param c Nexus class to check for
    //! \return true if group class and c match, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    bool is_class(const nxobject<GTYPE,FTYPE,ATYPE> &o,const string &c)
    {
        typedef is_class_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(c),o);
    }

//end of namespace
}
}
}
