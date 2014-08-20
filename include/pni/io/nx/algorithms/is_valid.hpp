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
//
// Created on: Jun 28, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject.hpp"


namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief visitor checking object validity
    //! 
    //! Check if the passed object is valid and return true if this is the 
    //! case. This template code takes instances 
    //! \li nxattribute
    //! \li nxfield
    //! \li nxgroup
    //! \li nxfile
    //!
    //! as input arguments.
    //! 
    //! \throws object_error if the validity check fails
    //!
    //! \tparam OTYPE object type
    //! \param o instance of OTYPE
    //! \return true if the object is valid
    //! 
    template<typename OTYPE> bool is_valid(const OTYPE &o) noexcept
    {
        return o.is_valid();
    }

    //!
    //! \ingroup algorithm_internal_code
    //! \brief check object validity
    //!
    //! Visitor to call the is_valid method on objects stored in an nxobject
    //! instance.
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \sa is_valid
    //!
    template<
             typename GTYPE,
             typename FTYPE, 
             typename ATYPE
            > 
    class is_valid_visitor : public boost::static_visitor<bool>
    {
        public:
            //! result type (bool)
            typedef bool result_type;
            //! Nexus group type
            typedef GTYPE group_type;
            //! Nexus field type
            typedef FTYPE field_type;
            //! Nexus attribute type
            typedef ATYPE attribute_type;
          
            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Checks a group instance for its validity. If the group is 
            //! valid true is returned, otherwise false. 
            //! 
            //! \throws object_error if validity check fails
            //!
            //! \param g group instance
            //! \return true if valid, false otherwise
            //!
            result_type operator()(const group_type &g) const 
            {
                return is_valid(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Checks a field instance for its validity. If the field is 
            //! valid true is returned, otherwise false. 
            //! 
            //! \throws object_error if validity check fails
            //!
            //! \param f field instance
            //! \return true if valid, false otherwise
            //!
            result_type operator()(const field_type &f) const 
            {
                return is_valid(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Checks a attribute instance for its validity. If the attribute 
            //! is valid true is returned, otherwise false. 
            //!
            //! \throws object_error if validity check fails
            //!
            //! \param a attribute instance
            //! \return true if valid, false otherwise
            //!
            result_type operator()(const attribute_type &a) const 
            {
                return is_valid(a);
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief is_valid wrapper 
    //!
    //! Test the validity of an object stored in an nxobject instance by calling 
    //! the is_valid method on the particular instance.
    /*! 
    \code{.cpp}
    auto o = ....;
    if(!is_valid(o))
    {
        std::cerr<<"Nexus object is not valid - abort program!"<<std::endl;
        return -1;
    }
    \endcode
    */
    //!
    //! \throws object_error if validity check fails
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \param o reference to nxobject<GTYPE,FTYPE,ATYPE>
    //! \return true if valid, false otherwise
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    bool is_valid(const nxobject<GTYPE,FTYPE,ATYPE> &o) noexcept
    {
        typedef is_valid_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }

//end of namespace
}
}
}
