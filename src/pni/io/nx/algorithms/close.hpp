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
// Created on: Jul 17, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "../nxobject.hpp"
#include "../nximp_code.hpp"
#include "../link.hpp"

namespace pni{
namespace io{
namespace nx{

    //!
    //! \ingroup algorithm_code
    //! \brief close object
    //!
    //! Invokes the close() method of the passed object.  The objects accepted
    //! by this function template are either of type nxfield, nxattribute,  
    //! nxgroup, or nxfile. 
    //!
    //! \throws object_error in case of errors
    //! \throws type_error if internal object type is not supported
    //!
    //! \tparam OTYPE object type
    //! \param o instance of the object to close
    //!
    template<nximp_code IMPID> void close(nxlink<IMPID> &)
    {}
    template<typename OTYPE> void close(OTYPE &o)
    {
        o.close();
    }



    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_internal_code
    //! \brief close an object
    //!
    //! This visitor closes an open stored in an instance of nxobject.
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
    class close_visitor : public boost::static_visitor<void>
    {
        public:
            //! result type (bool)
            using result_type = void;
            //! Nexus group type
            using group_type = GTYPE;
            //! Nexus field type
            using field_type = FTYPE;
            //! Nexus attribute type
            using attribute_type = ATYPE;
            //! link type
            using link_type = LTYPE;
           
            //-----------------------------------------------------------------
            //!
            //! \brief process group instances
            //!
            //! Close the group.
            //!
            //! \throws object_error in case closing the group fails
            //! \throws type_error if internal object type could not be 
            //!                    determined
            //!
            //! \param g reference to group instance
            //! \return false
            //!
            void operator()(group_type &g) const
            {
                close(g);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process field instances
            //!
            //! Close the field.
            //!
            //! \throws object_error in case closing the field fails
            //! \throws type_error if internal object type could not be 
            //!                    determined
            //!
            //! \param f reference to field instance
            //! \return true
            //!
            void operator()(field_type &f) const
            {
                close(f);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief process attribute instances
            //!
            //! Close the attribute.
            //!
            //! \throws object_error in case closing the attribute fails
            //! \throws type_error if internal object type could not be 
            //!                    determined
            //!
            //! \param a reference to attribute instance
            //! \return false
            //!
            void operator()(attribute_type &a) const
            {
                close(a);
            }

            //----------------------------------------------------------------
            //!
            //! \brief process a link instance
            //!
            //! There is nothing we have to do here.
            //!
            void operator()(const link_type &) const
            {
                
            }
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief close object
    //!
    //! Wrapper function around the close_visitor. The function closes the 
    //! object stored in the variant type passed to it.
    //!
    //! \throws object_error in case of an error during closing the object
    //! \throws type_error if the internal object type could not be 
    //!                    determined
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute type
    //! \tparam LTYPE link  type
    //! \param o instance of nxobject<GTYPE,FTYPE,ATYPE,LTYPE>
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE,
             typename LTYPE
            > 
    void close(nxobject<GTYPE,FTYPE,ATYPE,LTYPE> &o)
    {
        using visitor_type = close_visitor<GTYPE,FTYPE,ATYPE,LTYPE>;
        return boost::apply_visitor(visitor_type(),o);
    }


//end of namespace
}
}
}
