//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
// 
// Created on: Oct 20, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <iostream>
#include <sstream>
#include <array>
#include <numeric>
#include <algorithm>
#include <functional>

#include <pni/error/exceptions.hpp>
#include <pni/error/exception_utils.hpp>

namespace pni{

    //!
    //! \ingroup index_mapping_classes
    //! \brief C index map implementation
    //! 
    //! This class implements common functions for C index maps. Indices are
    //! mapped to a linear offset with the last index varying fastest.
    //! 
    class c_index_map_imp
    {
        private:
            //!
            //! \brief compute the offset 
            //! 
            //! Compute the offset for an index range and a given shape.
            //!
            //! \tparam IITERT index iterator type
            //! \tparam SITERT shape iterator type
            //! \param index_start start iterator for the index range
            //! \param index_stop   stop iterator for the index range
            //! \param shape_start start iterator for the shape range
            //! \return offset value
            //! 
            template<typename IITERT,
                     typename SITERT> 
            static size_t offset(IITERT &&index_start,
                                 IITERT &&index_stop, 
                                 SITERT &&shape_start)
            {
                //initialize the offset and the stride variable
                size_t offset = *index_start++,stride=1;

                //loop over all indices - remember that the iterators are
                //reverse iterators
                while(index_start!=index_stop)
                {
                    //compute the actuall stride 
                    stride *= *shape_start++;
                    //compute the offset contribution
                    offset += stride*(*index_start++);
                }

                return offset;
            }

            //------------------------------------------------------------------
            //!
            //! \brief compute selection offset 
            //! 
            //! Compute the linear offset for an index range and a particular
            //! selection. This private member function actually implements this
            //! feature.  The index passed is the effective index of the 
            //! selection and must not have the same rank as the original array.
            //!
            //! \tparam SELITER selection iterator
            //! \tparam SITER   iterator type of the original shape
            //! \tparam IITER   index container iterator
            //! \param sel_shape_start begin of selection shape
            //! \param sel_shape_end   end of selection shape
            //! \param sel_offset begin of selection offset
            //! \param sel_stride begin of selection stride
            //! \param shape_start begin of original shape
            //! \param sel_index begin of selection index
            //! \return linear offset
            //!
            template<
                     typename SELITER,
                     typename SITER,
                     typename IITER
                    > 
            static size_t offset(SELITER &&sel_shape_start,
                                 SELITER &&sel_shape_end,
                                 SELITER &&sel_offset, 
                                 SELITER &&sel_stride,
                                 SITER   &&shape_start,
                                 IITER   &&sel_index)
            {
                size_t index = *sel_offset++;

                if(*sel_shape_start++ != 1) index += (*sel_index++)*(*sel_stride);
                ++sel_stride;

                //initialize the offset and the stride variable
                size_t offset = index ,dim_stride=1;

                //loop over all indices - remember that the iterators are
                //reverse iterators
                while(sel_shape_start!=sel_shape_end)
                {
                    //compute the index from the selection
                    index = *sel_offset++;
                    if(*sel_shape_start++ != 1) 
                        index += (*sel_index++)*(*sel_stride);

                    ++sel_stride; //increment the selection stride in any case

                    //compute the actuall stride 
                    dim_stride *= *shape_start++;
                    //compute the offset contribution
                    offset += dim_stride*index;
                }

                return offset;
            }


            //------------------------------------------------------------------
            //!
            //! \brief compute the index
            //! 
            //! Compute the index for a given linear offset according to 
            //! C-ordering rules. 
            //! 
            //! \tparam IITERT index iterator type
            //! \tparam SITERT shape iterator type
            //! \param shape_start iterator to first shape element
            //! \param shape_stop iterator to last shape element
            //! \param index_start iterator to first index
            //! \param offset the linear offset for which to compute the index
            //!
            template<
                     typename IITERT,
                     typename SITERT
                    >
            static void index(SITERT &&shape_start,
                              SITERT &&shape_stop,
                              IITERT &&index_start,
                              size_t offset)
            {
                size_t t;
                size_t stride = std::accumulate(++shape_start,shape_stop,1,
                                                std::multiplies<size_t>());
                t = offset%stride;
                *(index_start++) = (offset-t)/stride;
                offset = t;
                while(shape_start != shape_stop)
                {
                    //increment here the shape_start iterator - we already start
                    //with start+1 with the stride computation
                    stride /= *shape_start++;
                    t = offset%stride;
                    *(index_start++) = (offset-t)/stride;
                    offset = t;
                }
            }
        public:

            //-----------------------------------------------------------------
            //!
            //! \brief compute the offset
            //!
            //! Compute the linear offset for a given shape and index. The 
            //! functions assumes that the index and the shape container are 
            //! of equal size.  However, this must be ensured by the calling 
            //! function.
            //!
            //! \tparam CSHAPE container type for the shape data
            //! \tparam CINDEX container type for the index data
            //! \param shape instance of CSHAPE with shape data
            //! \param index instance of CINDEX with index data
            //! \return linear offset
            //!
            template<
                     typename CSHAPE,
                     typename CINDEX
                    >
            static size_t offset(const CSHAPE &shape,const CINDEX &index)
            {
                //use here reverse iterators as required by the c-ordering
                return offset(index.rbegin(),index.rend(),shape.rbegin());
            }

            //-----------------------------------------------------------------
            //!
            //! \brief compute offset for selection
            //! 
            //! Computes the linear offset for a given selection index. The
            //! selection index is not required to have the same rank as the
            //! original array. 
            //! 
            //! \tparam SELTYPE selection type
            //! \tparam CSHAPE original shape of the array
            //! \tparam SINDEX selection index type
            //! \param sel reference to the selection
            //! \param shape the original shape
            //! \param index selection index
            //! \return linear offset
            //!
            template<
                     typename SELTYPE,
                     typename CSHAPE,
                     typename SINDEX
                    >
            static size_t offset(const SELTYPE &sel,const CSHAPE &shape,
                                 const SINDEX &index)
            {
                return offset(sel.full_shape().rbegin(), //original selection shape
                              sel.full_shape().rend(),   //
                              sel.offset().rbegin(), //selection offset
                              sel.stride().rbegin(), //selection stride
                              shape.rbegin(), //original shape begin
                              index.rbegin()); //selection index start
            }

            //-----------------------------------------------------------------
            //!
            //! \brief compute index
            //!
            //! Compute the multidimensional index for a given shape and offset. 
            //! The function assumes that the index container is of appropriate 
            //! size (the size of the shape container) which must be ensured 
            //! by the calling function.
            //! 
            //! \tparam CINDEX container type for index values
            //! \tparam CSHAPE container type for shape values
            //! \param shape instance of CSHAPE with shape information
            //! \param idx instance of CINDEX for index data
            //! \param offset linear offset 
            //!
            template<
                     typename CINDEX,
                     typename CSHAPE
                    >
            static void index(const CSHAPE &shape,CINDEX &idx,size_t offset)
            {
                //for index computation we can use the forward iterators
                index(shape.begin(),shape.end(),idx.begin(),offset); 
            }


    };
//end of namespace
}
