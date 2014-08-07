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
//
// Created on: Aug 1, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include "type_imp.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{

    using namespace pni::core;

    //!
    //! \ingroup nxh5_classes
    //! \brief describe a selection in an HDF5 file
    //!
    class selection
    {
        private:
            //! buffer for offset values
            type_imp::index_vector_type _offset;
            //! buffer for stride values
            type_imp::index_vector_type _stride;
            //! buffer for count values
            type_imp::index_vector_type _count;

        public:
            //----------------------------------------------------------------
            //                Constructors
            //----------------------------------------------------------------
            //!
            //! \brief default constructor
            //!
            selection() noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            selection(size_t n);

            //----------------------------------------------------------------
            //               Data access methods
            //----------------------------------------------------------------
            //!
            //! \brief get reference to offset vector
            //!
            const type_imp::index_vector_type &offset() const;

            //----------------------------------------------------------------
            void offset(const type_imp::index_vector_type &offset);

            //----------------------------------------------------------------
            void offset(type_imp::index_type value);
            
            //----------------------------------------------------------------
            void offset(size_t index,size_t value);

            //----------------------------------------------------------------
            //!
            //! \brief get refeference to stride vector
            //!
            const type_imp::index_vector_type &stride() const;

            void stride(const type_imp::index_vector_type &value);

            void stride(type_imp::index_type value);
            
            //----------------------------------------------------------------
            //! 
            //! \brief get reference to count vector
            //!
            const type_imp::index_vector_type &count() const;

            void count(const type_imp::index_vector_type &value);

            void count(type_imp::index_type value);

            void count(size_t index,type_imp::index_type value);

            //----------------------------------------------------------------
            //!
            //! \brief update selection
            //! 
            void update(const type_imp::selection_vector_type &s);

    };

    //!
    //! \ingroup nxh5_classes
    //! \brief get effective rank
    //!
    //! The effective rank for a selection is the number of dimension for  
    //! whome the count value is >1. 
    //!
    //! \param s selection instance
    //! \return effective rank
    size_t effective_rank(const selection &s);

    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief get effective shape
    //! 
    //! The effective shape of a selection is basically the count buffer with 
    //! those entries removed where its value is 1.
    //! 
    //! \param s selection instance
    //! \return vector with effective shape
    //!
    type_imp::index_vector_type effective_shape(const selection &s);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get selection size
    //! 
    //! Get the number of elements referenced by the selection.
    //! 
    //! \param s selection instance
    //! \return number of selected elements
    //! 
    size_t size(const selection &s);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //!
    selection create_selection(const type_imp::selection_vector_type &s);




//end of namespace
}
}
}
}

