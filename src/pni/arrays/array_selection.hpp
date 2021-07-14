//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 1, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <algorithm>

#include <pni/utilities/container_utils.hpp>
#include <pni/error/exception_utils.hpp>
#include <pni/arrays/slice.hpp>
#include <pni/windows.hpp>

namespace pni{


    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief selection from a multidimensional array
    //! 
    //! The array_selection class is a utility class for selecting subranges of
    //! multidimensional arrays. The effective rank of such a selection can be
    //! smaller than that of the original array. Thus the number of indices 
    //! used to address an element in a selection might be smaller than for 
    //! the original array.  This class has to major purposes
    //! 
    //! \li compute the original index of the array for a
    //! \li compute the original offset for a given offset
    //! 
    //! This type represents the selection of elements from a multidimensional
    //! array and is primarily used by the ArrayView template. 
    //! Its primary purpose is to map selection indices to indices of the
    //! original array. This is required as a selection might does not have the 
    //! same rank as the original array. Consider an array of shape (4,10,28) 
    //! from which we select (1,10,28). The effective rank of this selection is 
    //! 2 while that of the original array would be 3. Additionally, such a 
    //! selection would have the effective rank (10,28) as the first index can 
    //! be omitted. This allows to select data of a particular dimensionality 
    //! from an array of arbitrary rank.
    //! The only assumption that must be made is that the rank of the original 
    //! array is larger than that of the required selection. 
    //! Clearly, one wants to use a two dimensional index (i,j) to address an
    //! element in the selection. However, to get the data from the original 
    //! array //! this must be modified to (1,i,j) which is the major purpose 
    //! of this type.
    //!
    class PNINEXUS_EXPORT array_selection
    {
        private:
            //! private index type
            typedef std::vector<size_t> index_type;

            //member variables describing the selection in the original array
            //all of these containers have the same size which is equal to the
            //rank of the original array
            //! shape of the selection in the original array
            index_type _oshape;             
            //! offset in the original array
            index_type _offset;
            //! stride in the original array
            index_type _stride;

        public:
            //===================constructors and destructor====================
            //! 
            //! \brief constructor
            //! 
            //! Selection construction from arbitary containers.
            //! 
            //! \tparam CTYPE container template for arguments
            //! \tparam OTS template parameters for CTYPE
            //! \param oshape selection shape in the original array
            //! \param ooffset offset of the selection 
            //! \param ostride stride of the selection
            //!
            template<template<typename ...> class CTYPE,typename ...OTS>
            explicit array_selection(const CTYPE<OTS...> &oshape,
                                     const CTYPE<OTS...> &ooffset,
                                     const CTYPE<OTS...> &ostride):
                _oshape(oshape.size()),
                _offset(ooffset.size()),
                _stride(ostride.size())
            {
                std::copy(oshape.begin(),oshape.end(),_oshape.begin());
                std::copy(ooffset.begin(),ooffset.end(),_offset.begin());
                std::copy(ostride.begin(),ostride.end(),_stride.begin());
            }

            //------------------------------------------------------------------
            //!
            //! \brief default constructor
            //!
            explicit array_selection();

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! This constructor does not require any memory allocation as all
            //! parameters are passed as rvalue references.
            //! \param oshape the original array shape
            //! \param ooffset original offset 
            //! \param ostride strides of the selection in the original array
            //!
            explicit array_selection(index_type &&oshape,index_type &ooffset,
                                     index_type &&ostride);
            
            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! Copy construct from parameters. 
            //! \param oshape selection shape in the original array
            //! \param ooffset offset of the selection in the original shape
            //! \param ostride selection stride in the original array
            //!
            explicit array_selection(const index_type &oshape,
                                     const index_type &ooffset,
                                     const index_type &ostride);

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            explicit array_selection(const array_selection &s);

            //-----------------------------------------------------------------
            //!
            //! \brief move constructor
            //!
            array_selection(array_selection &&s);

            //-----------------------------------------------------------------
            //!
            //! \brief copy assignment operator
            //!
            array_selection &operator=(const array_selection &s);

            //-----------------------------------------------------------------
            //!
            //! \brief move asignment operator
            //!
            array_selection &operator=(array_selection &&s);


            //-----------------------------------------------------------------
            //! static creation function
            template<typename CTYPE,
                     typename = typename std::enable_if<
                     std::is_same<typename CTYPE::value_type,pni::slice>::value
                     >::type
                    >
            static array_selection create(const CTYPE &s)
            {
                typedef container_utils<index_type> cutils_type;
                auto shape  = cutils_type::create(s.size());
                auto offset = cutils_type::create(s.size());
                auto stride = cutils_type::create(s.size());

                size_t index = 0;
                for(auto sl: s)
                {
                    offset[index] = sl.first();
                    stride[index] = sl.stride();
                    shape[index]  = pni::size(sl);
                    index++;
                }

                return array_selection(std::move(shape),
                                       std::move(offset),
                                       std::move(stride));
            }

           
            //=================inquery methods=================================
            //! 
            //! \brief get effective rank
            //! 
            //! Return the effective rank of the selection. If a single element 
            //! is selected the element count along each of the dimensions of 
            //! the selection will be 1. As a result the rank will be zero. 
            //! For scalar selections the rank is 0. 
            //! 
            //! \return effective rank
            //! 
            size_t rank() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get effective shape
            //! 
            //! Return the effective shape of the selection in an arbitary
            //! container. If a single scalar element is selected the return 
            //! value will be an empty container. 
            //! 
            //! \tparam CTYPE container type
            //! \return instance of CTYPE with effective shape
            //!
            template<typename CTYPE> CTYPE shape() const;

            //----------------------------------------------------------------- 
            //! 
            //! \brief get selection size
            //! 
            //! Get the number of elements stored in the selection. If a single
            //! element is selected the size is 1. If the selection is not
            //! initialized the size is 0;
            //! 
            //! \return number of elements
            //!
            size_t size() const;

            //=========methods to retrieve full selection information==========
            //!
            //! \brief get full shape reference
            //! 
            //! Return a reference to the container holding the full shape of 
            //! the selection. 
            //! 
            //! \return reference to full shape
            //!
            const index_type &full_shape() const noexcept;

            //-----------------------------------------------------------------
            //! 
            //! \brief get full shape 
            //! 
            //! Return the full shape of the selection stored in an arbitrary
            //! container type.
            //! 
            //! \tparam CTYPE container type
            //! \return instance of CTYPE with the full shape
            //!
            template<typename CTYPE> CTYPE full_shape() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get reference to offset
            //! 
            //! Return a reference to the offset container of the selection 
            //! object.
            //!
            //! \return reference to offsets
            //!
            const index_type &offset() const noexcept;

            //-----------------------------------------------------------------
            //! 
            //! \brief get offset 
            //! 
            //! Return the offset values of the selection in an arbitary container.
            //! \tparam CTYPE container type
            //! \return instance of CTYPE with offset values
            //!
            template<typename CTYPE> CTYPE offset() const;

            //-----------------------------------------------------------------
            //! 
            //! \brief get reference to stride
            //! 
            //! Return a reference to the stride container of the selection.
            //! \return stride reference
            //!
            const index_type &stride() const noexcept;

            //-----------------------------------------------------------------
            //! 
            //! \brief get stride
            //! 
            //! Return the stride of the selection stored in an arbitrary STL
            //! container type. 
            //! \tparam CTYPE container type
            //! \return instance of CTYPE with the stride values
            //!
            template<typename CTYPE> CTYPE stride() const;

            //================get indices======================================
            //! 
            //! \brief compute original index
            //! 
            //! The functionality of this template method can be best 
            //! explained using an example. 
            /*!
            \code
            typedef std::vector<size_t> itype;
            
            //create a (1,25,128) selection from a 3D array at offset (1,1,1)
            //and with stride (1,1,1)
            array_selection s(itype{1,25,128},itype{1,1,1},itype{1,1,1});
            
            //selection index
            itype sindex{2,100};
            
            //if we want to access data from the original array we need to
            //convert this to a 3D index
            itype oindex(3);
            s.index(sindex,oindex);
            
            //now the vector oindex holds the values {1,2,100} which can be used
            //to obtain data form the original array.
            
            \endcode
            !*/
            //! The method assumes that all index containers are of appropriate
            //! size. If this is not the case an exception will be thrown
            //! 
            //! \throws size_mismatch_error if sindex does not match the rank 
            //! of the selection or if oindex does not match the rank of the 
            //! original array
            //! 
            //! \tparam ITYPE container type for the indices
            //! \param sindex original index of the selection
            //! \param oindex new index with the rank of the original array
            //!
            template<
                     typename ITYPE,
                     typename OITYPE
                    > 
            void index(const ITYPE &sindex,OITYPE &oindex) const;

            //-----------------------------------------------------------------
            //!
            //! \brief compute the original index
            //! 
            //! This is virtually the same as index(const ITYPE &sindex,
            //! const ITYPE &oindex) except that one does not have to take 
            //! care about allocating the container for the original index.
            //! 
            //! \tparam ITYPE container type (determined by the argument)
            //! \tparam OITYPE container type for the original index
            //! \param sindex selection index
            //! \return instance of ITYPE with the index in the original array
            //! \sa template<typename ITYPE> index(const ITYPE &sindex,const ITYPE
            //! &oindex) const
            //!
            template<
                     typename OITYPE,
                     typename ITYPE
                    > 
            OITYPE index(const ITYPE &sindex) const;
    };

    template<typename CTYPE>
    CTYPE array_selection::shape() const
    {
        typedef container_utils<CTYPE>  cutils_type;
        auto c = cutils_type::create(rank());

        //now we have to copy only those values from the original shape
        //that are not equal 1
        std::copy_if(_oshape.begin(),_oshape.end(),c.begin(),
                     [](size_t i){ return i!=1; });
        return c;
    }

    template<typename CTYPE> CTYPE
	array_selection::full_shape() const
    {
        typedef container_utils<CTYPE> cutils_type;
        auto c = cutils_type::create(_oshape.size());
        std::copy(_oshape.begin(),_oshape.end(),c.begin());
        return c;
    }

    template<typename CTYPE>
    CTYPE array_selection::offset() const
    {
        typedef container_utils<CTYPE> cutils_type;
        auto c = cutils_type::create(_offset.size());
        std::copy(_offset.begin(),_offset.end(),c.begin());
        return c;
    }

    template<typename CTYPE>
    CTYPE array_selection::stride() const
    {
    	typedef container_utils<CTYPE> cutils_type;
    	auto c = cutils_type::create(_stride.size());

    	std::copy(_stride.begin(),_stride.end(),c.begin());
    	return c;
    }

    template<
	typename ITYPE,
	typename OITYPE
	>
    void array_selection::index(const ITYPE &sindex,OITYPE &oindex) const
    {
#ifdef DEBUG
//check here if the size (rank) of the original shape of the
    	//selection matches that of the original index.
    	check_equal_size(_oshape,oindex,EXCEPTION_RECORD);
    	//check if the size of the selection index container matches the
    	//effective rank of the selection
    	check_equal_size(shape<ITYPE>(),sindex,EXCEPTION_RECORD);
#endif

    	//now we have to add index*stride from the selection index too
    	//the appropriate locations
    	auto os_iter = _oshape.begin(); //iter. over original shape
    	auto st_iter = _stride.begin(); //iter. over selection strides
    	auto si_iter = sindex.begin();  //iter. over selection index
    	auto of_iter = _offset.begin(); //iter. over the offset

    	//loop over output index
    	for(auto &oi: oindex)
    	{
    		size_t index = *of_iter++;
    		//oi = *of_iter++;
    		if(*os_iter++ != 1) index += (*st_iter)*(*si_iter++);
    		++st_iter;  //need to increment this guy in any case
    		oi = index;
    	}
    }

    template<
	typename OITYPE,
	typename ITYPE
	>
    OITYPE array_selection::index(const ITYPE &sindex) const
    {
    	typedef container_utils<OITYPE> cutils_type;
    	auto oindex = cutils_type::create(_oshape.size());

    	try{ index(sindex,oindex); }
    	EXCEPTION_FORWARD(size_mismatch_error);

    	return oindex;
    }

    
    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief compute offset 
    //! 
    //! Compute the offset of a selection element in the original array. The
    //! original array is not required but only its index map. 
    //! The index is expected to have the effective size of the selection. This
    //! means that its rank can be smaller than that of the map.
    //! 
    //! \tparam MAPT map type of the original array
    //! \tparam CTYPE index type for the selection index 
    //! \param map reference to the original index map
    //! \param s reference to the selection object
    //! \param index reference to the selection index 
    //! \return linear offset of the element in the original array
    //!
    template<
             typename MAPT,
             typename CTYPE
            >
    size_t offset(const MAPT &map,const array_selection &s,
                  const CTYPE &index)
    {
        //compute the original index of the selection index 
        auto orig_index = container_utils<CTYPE>::create(map.rank());
        s.index(index,orig_index);

        return map.offset(orig_index);
    }
  
    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief compute first element offset 
    //!
    //! Compute the offset in the original array of the first element in the
    //! selection. 
    //! 
    //! \tparam MAPT original index map type
    //! \tparam INDEXT index type of the selection
    //! \param map reference to the original index map
    //! \param s reference to the selection 
    //! \return offset of the first selection element
    //!
    template<typename MAPT>
    size_t start_offset(const MAPT &map,const array_selection &s)
    {
        typedef std::vector<size_t> index_type;

        auto index = s.template shape<index_type>();
        //set all elements to zero
        std::fill(index.begin(),index.end(),size_t(0));

        return offset(map,s,index);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief compute last element offset 
    //! 
    //! Compute the linear offset in the original array for the last element 
    //! in a selection. 
    //! 
    //! \tparam MAPT index map type of the original array
    //! \tparam INDEXT index type of the array selection
    //! \param map reference to the original index map
    //! \param s reference to the selection object
    //! \return offset of the last element
    //!
    template<typename MAPT>
    size_t last_offset(const MAPT &map,const array_selection &s)
    {
        typedef std::vector<size_t> index_type;

        auto index = s.template shape<index_type>();
        std::transform(index.begin(),index.end(),index.begin(),
                       [](const size_t &i){ return i-size_t(1); });

        return offset(map,s,index);

    }

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup mdim_array_internal_classes
    //! \brief check continuity of a selection
    //! 
    //! This function returns true if a selection is continuous within a
    //! index map. A selection is considered as contiguous if the number of
    //! it spans in the original array is equal to the size of the selection.
    //!
    //! \tparam MAPT index map type
    //! \param map reference to the index mape
    //! \param s reerence to the selection. 
    //! \return true if contiguous, false otherwise
    template<typename MAPT>
    bool is_contiguous(const MAPT &map,const array_selection &s)
    {

        size_t orig_first_offset = start_offset(map,s);
        size_t orig_last_offset  = last_offset(map,s);

        //check if the size of the selection matches the offset-difference in
        //the original array - in this case we have a contiguous selection.
        if( (orig_last_offset - orig_first_offset + 1) == s.size())
            return true;

        return false;
    }
    

//end of namespace
}
