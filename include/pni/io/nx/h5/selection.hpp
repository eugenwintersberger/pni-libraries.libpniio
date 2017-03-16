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
#include "../../windows.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{    

    //!
    //! \ingroup nxh5_classes
    //! \brief describe a selection in an HDF5 file
    //!
    class PNIIO_EXPORT selection
    {
        private:
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
            //! buffer for offset values
            type_imp::index_vector_type _offset;
            //! buffer for stride values
            type_imp::index_vector_type _stride;
            //! buffer for count values
            type_imp::index_vector_type _count;
#ifdef _MSC_VER
#pragma warning(default:4251)
#endif
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
            //! \param n number of dimensions of the original field
            //!
            selection(size_t n);

            //----------------------------------------------------------------
            //               Data access methods
            //----------------------------------------------------------------
            //!
            //! \brief get reference to offset vector
            //!
            const type_imp::index_vector_type &offset() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief set offset vector
            //!
            //! Use offset data from an user provided vector.
            //!
            //! \throws shape_mismatch_error if rank of selection an size of 
            //! offset vector do not match
            //!
            //! \param offset vector with new offset data
            //!
            void offset(const type_imp::index_vector_type &offset);

            //----------------------------------------------------------------
            //!
            //! \brief set offset vector
            //!
            //! Set all elements of the offset vector to value.
            //!
            //! \param value new offset value
            //!
            void offset(type_imp::index_type value) noexcept;
            
            //----------------------------------------------------------------
            //!
            //! \brief set offset 
            //!
            //! Set offset value for dimension index to value.
            //!
            //! \throws index_error if index exceeds the total rank of the
            //! selection
            //!
            //! \param index dimension index for which to set the offset
            //! \param value new offset value 
            //!
            void offset(size_t index,size_t value);

            //----------------------------------------------------------------
            //!
            //! \brief get refeference to stride vector
            //!
            const type_imp::index_vector_type &stride() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief set stride vector
            //!
            //! Set the stride vector from a user provided vector.
            //!
            //! \throws shape_mismatch_error if vector size does not match 
            //! the total rank of the selection
            //!
            //! \param value vector with new stride values
            //!
            void stride(const type_imp::index_vector_type &value);

            //----------------------------------------------------------------
            //!
            //! \brief set stride 
            //!
            //! Set all stride components to value.
            //!
            //! \param value new value for all stride components
            //!
            void stride(type_imp::index_type value) noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief set stride
            //!
            //! Set the stride value for a particular dimension.
            //! 
            //! \throws index_error if the dimension index exceeds the 
            //! rank of the selection
            //!
            //! \param index dimension index
            //! \param value stride value for the selected dimension
            //!
            void stride(size_t index,type_imp::index_type value);
            
            //----------------------------------------------------------------
            //! 
            //! \brief get reference to count vector
            //!
            const type_imp::index_vector_type &count() const noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief set count values
            //!
            //! Set count values from a user provided vector.
            //!
            //! \throws shape_mismatch_error if vector size does not match 
            //! selection rank
            //!
            //! \param value vector with new count values
            //!
            void count(const type_imp::index_vector_type &value);

            //----------------------------------------------------------------
            //!
            //! \brief set count values
            //!
            //! Set all count entries to value.
            //!
            //! \param value new value for all count entries
            //!
            void count(type_imp::index_type value) noexcept;

            //----------------------------------------------------------------
            //!
            //! \brief set count value
            //!
            //! Set the count value for a particular dimension.
            //! 
            //! \throws index_error if dimension index exceeds the rank of the 
            //! dimension
            //!
            //! \param index dimension index
            //! \param value new count value for the selected dimension
            //!
            void count(size_t index,type_imp::index_type value);

            //----------------------------------------------------------------
            //!
            //! \brief update selection
            //! 
            //! Set selection propertires from a vector of slices. 
            //!
            //! \throws shape_mismatch_error if vector size and selection 
            //! length do not match
            //! 
            //! \param s slice vector
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
    PNIIO_EXPORT size_t effective_rank(const selection &s) noexcept;

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
    PNIIO_EXPORT type_imp::index_vector_type effective_shape(const selection &s);

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
    PNIIO_EXPORT size_t size(const selection &s) noexcept;

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! 
    //! Create a selection from a slice vector. 
    //! 
    //! \param s reference to the slice vector
    //! \return selection instance
    //!
    PNIIO_EXPORT selection create_selection(const type_imp::selection_vector_type &s);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //!
    //! Create a slice vector from a selection. Such a slice vector might 
    //! be used to create an array selection from an mdarray instance. 
    //! 
    //! \param s reference to the selection object
    //! \return slice vector
    //! 
    PNIIO_EXPORT type_imp::selection_vector_type create_slice_vector(const selection &s);



//end of namespace
}
}
}
}

