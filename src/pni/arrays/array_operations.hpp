//!
//! (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpninexus.
//!
//! libpninexus is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpninexus is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: May 22, 2012
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!/

#pragma once

#include <pni/types/types.hpp>


namespace pni{

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes
    \brief get minimum value of an array type

    Returns the minimum value stored in an array type. The result is of the same
    type as the array elements. This function does not work for array types with
    complex numbers as their elements as there are no order relations defined
    for complex numbers.
    \param a array type
    \return value of type T
    */
    template<typename ArrayT> typename ArrayT::value_type min(const ArrayT &a) 
    {
        typedef typename ArrayT::value_type RType;
        RType result(a[0]);

#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            auto v = *iter;
#else
        for(auto v: a)
        {
#endif
            if(v<result) result = v;
        }

        return result;
    }

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_clases
    \brief get maximum value of an array type

    Returns the larges value in an array type object. The result is of same type
    as the elements in the array type. This function does not work for arrays of
    complex numbers as there are no order relations for complex numbers.
    \param a array for which to determine the maximum
    \return value of type T
    */
    template<typename ArrayT> typename ArrayT::value_type max(const ArrayT &a)
    {
        typedef typename ArrayT::value_type RType;

        RType result(a[0]);

#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            auto v = *iter;
#else
        for(auto v: a)
        {
#endif
            if(v>result) result = v;
        }

        return result;
    }

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes  
    \brief minimum and maximum in the array

    Return the minimunm and maximum values appearing in an array type. This
    function will not work on arrays with complex elements as there are no order
    relations for complex numbers.
    \param a array object
    \param min minimum value
    \param max maximum value
    */
    template<typename ArrayT> void min_max(const ArrayT &a,
                                           typename ArrayT::value_type &min,
                                           typename ArrayT::value_type &max)
    {
        min=typename ArrayT::value_type(a[0]);
        max=typename ArrayT::value_type(a[0]);
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            auto v=*iter;
#else
        for(auto v: a)
        {
#endif
            if(v<min) min = v;
            if(v>max) max = v;
        }
    }

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes  
    \brief clip the array data

    Set values greater or equal maxth to maxth and those smaller or equal minth
    to minth. 
    \param a array which to clip
    \param minth minimum threshold
    \param maxth maximum threshold
    */
    template<typename ArrayT> void clip(ArrayT &a,
                                        typename ArrayT::value_type minth, 
                                        typename ArrayT::value_type maxth)
    {
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            typename ArrayT::value_type &v = *iter;
#else
        for(typename ArrayT::value_type &v: a)
        {
#endif
            if(v <= minth)
            {
                v = minth;
                continue;
            }

            if(v >= maxth)
            {
                v = maxth;
                continue;
            }
        }
    }

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes  
    \brief clip the array data

    Set values greater or equal maxth to maxval and those smaller or equal minth
    to minval. 
    \param a array which to clip
    \param minth minimum threshold
    \param maxth maximum threshold
    \param minval value to which values small minth will be set
    \param maxval value to which values larger maxth will be set
    */
    template<typename ArrayT> void clip(ArrayT &a,
                                        typename ArrayT::value_type minth, 
                                        typename ArrayT::value_type maxth,
                                        typename ArrayT::value_type minval,
                                        typename ArrayT::value_type maxval)
    {
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            typename ArrayT::value_type &v = *iter;
#else
        for(typename ArrayT::value_type &v: a)
        {
#endif
            if(v <= minth)
            {
                v = minval;
                continue;
            }

            if(v >= maxth)
            {
                v = maxval;
                continue;
            }
        }
    }

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes 
    \brief clip minimum values

    Set values smaller or equal than threshold to threshold. 
    \param a array which to clip
    \param threshold threshold value
    */
    template<typename ArrayT>
    void min_clip(ArrayT &a,typename ArrayT::value_type threshold)
    {
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            typename ArrayT::value_type &v = *iter;
#else
        for(typename ArrayT::value_type &v: a)
        {
#endif
            if(v<=threshold) v = threshold;
        }
    }

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes 
    \brief clip minimum values

    Set values smaller or equal than threshold to value. 
    \param a array which to clip
    \param threshold threshold value
    \param value the value to which to set data
    */
    template<typename ArrayT>
    void min_clip(ArrayT &a,typename ArrayT::value_type threshold,
                            typename ArrayT::value_type value)
    {
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            typename  ArrayT::value_type &v = *iter;
#else
        for(typename ArrayT::value_type &v: a)
        {
#endif
            if(v<=threshold) v = value;
        }
    }
    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes 
    \brief clip maximum values

    Set values larger or equal than threshold to threshold.
    \param a array to clip
    \param threshold threshold value
    */
    template<typename ArrayT> 
    void max_clip(ArrayT &a,typename ArrayT::value_type threshold)
    {
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            typename  ArrayT::value_type &v = *iter;
#else
        for(typename ArrayT::value_type &v: a)
        {
#endif
            if(v>=threshold) v = threshold;
        }
    }

    //--------------------------------------------------------------------------
    /*! 
    \ingroup data_classes  
    \brief clip maximum values

    Set values larger or equal than threshold to valuer.
    \param a array to clip
    \param threshold threshold value
    \param value value to set 
    */
    template<typename ArrayT> 
    void max_clip(ArrayT &a,typename ArrayT::value_type threshold,
                            typename ArrayT::value_type value)
    {
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            typename  ArrayT::value_type &v = *iter;
#else
        for(typename ArrayT::value_type &v: a)
        {
#endif
            if(v>=threshold) v = value;
        }
    }
    //--------------------------------------------------------------------------
    /*!
    \ingroup data_classes
    \brief get linear offset of maximum

    Return the linear offset of the maximum value in the array.
    \param a array object to search for
    \return linear offset of maximum value
    */
    template<typename ArrayT> size_t max_offset(const ArrayT &a)
    {
        typedef typename ArrayT::value_type value_type;
        size_t offset = 0;
        size_t index = 0;
        value_type max_value = value_type(a[0]);

        index = 0;
#ifdef NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            auto v = *iter;
#else
        for(auto v: a)
        {
#endif
            if(v > max_value)
            {
                max_value = v;
                offset  = index;
            }
            index++;
        }
        return offset;
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup data_classes
    \brief get index of maximum

    Return the multidimensional index of the maximum value in the array.
    \param a array where to search
    \return index in a container format requested by the user
    */
    template<typename ContainerT,typename ArrayT> ContainerT max_index(const ArrayT &a)
    {
        size_t offset = max_offset(a);
        return a.map().template index<ContainerT>(offset);
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup data_classes
    \brief get linear offset of minimum

    Return the linear offset of the minimum value in the array.
    \param a array object to search for
    \return linear offset of minimum value
    */
    template<typename ArrayT> size_t min_offset(const ArrayT &a)
    {
        
        typedef typename ArrayT::value_type value_type;
        size_t offset = 0;
        size_t index = 0;
        value_type min_value = value_type(a[0]);

        index = 0;
#ifdef  NOFOREACH
        for(auto iter=a.begin();iter!=a.end();iter++)
        {
            auto v = *iter;
#else
        for(auto v: a)
        {
#endif
            if(v < min_value)
            {
                min_value = v;
                offset  = index;
            }
            index++;
        }
        return offset;
    }

    //--------------------------------------------------------------------------
    /*!
    \ingroup data_classes
    \brief get index of minimum

    Return the multidimensional index of the minimum value in the array.
    \param a array where to search
    \return index in a container format requested by the user
    */
    template<typename ContainerT,typename ArrayT> ContainerT min_index(const ArrayT &a)
    {
        size_t offset = min_offset(a);
        return a.map().template index<ContainerT>(offset);
    }


//end of namespace
}

