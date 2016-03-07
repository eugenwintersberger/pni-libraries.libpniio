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
    template<typename OTYPE> void close(OTYPE &o)
    {
        o.close();
    }

    //!
    //! \ingroup algorithm_code
    //! \brief close link
    //!
    //! Overload of the close() template for instances of nxfield. As the
    //! function is just a stub (we do not have to close links explicitely),
    //! it does not throw anything.
    //!
    //! 
    void close(nxlink &l);

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
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    class close_visitor : public boost::static_visitor<void>
    {
        public:
            //! result type (bool)
            typedef void result_type;   
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
            void operator()(const nxlink &) const
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
    //! \param o instance of nxobject<GTYPE,FTYPE,ATYPE>
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            > 
    void close(nxobject<GTYPE,FTYPE,ATYPE> &o)
    {
        typedef close_visitor<GTYPE,FTYPE,ATYPE> visitor_type;
        return boost::apply_visitor(visitor_type(),o);
    }


//end of namespace
}
}
}
