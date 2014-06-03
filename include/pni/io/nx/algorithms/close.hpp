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
    //! Invokes the close() method of the passed object. 
    //!
    //! \tparam OTYPE object type
    //!
    template<typename OTYPE> void close(OTYPE &o)
    {
        o.close();
    }

    //------------------------------------------------------------------------
    //!
    //! \ingroup algorithm_code
    //! \brief close an object
    //!
    //! This visitor closes an open object.
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
            //! \param a reference to attribute instance
            //! \return false
            //!
            void operator()(attribute_type &a) const
            {
                close(a);
            }
    };

    //!
    //! \ingroup algorithm_code
    //! \brief close object
    //!
    //! Wrapper function around the close_visitor. The function closes the 
    //! object stored in the variant type passed to it.
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
        return boost::apply_visitor(close_visitor<GTYPE,FTYPE,ATYPE>(),o);
    }


//end of namespace
}
}
}
