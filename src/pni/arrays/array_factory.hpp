//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Mar 12, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <sstream>
#include <pni/utilities/container_utils.hpp>

namespace pni{


    //-------------------------------------------------------------------------
    //!
    //! \ingroup mdim_array_internal_classes
    //! \brief array factory 
    //!
    //! This utility template provides static functions for array construction. 
    //! This version of the array_factory template can will be used for 
    //! fully dynamic arrays and arrays of fixed dimension. A special overload 
    //! exists for static arrays.
    //! 
    //! \tparam ArrayT array type
    //!
    template<typename ArrayT> struct array_factory
    {
        //! shortcut for the array type
        using array_type =  ArrayT;
        //! value type of the array
        using value_type = typename array_type::value_type;
        //! map type of the array
        using map_type =  typename array_type::map_type;
        //! storage type of the array
        using storage_type = typename array_type::storage_type;


        //---------------------------------------------------------------------
        //!
        //! \brief create array from shape
        //!
        //! Create an array from a container with shape data and initialize 
        //! all its elements with a default value.
        /*!
        \code
        typedef ......................... array_type; 
        typedef array_type::value_type    value_type
        typedef arrya_factory<array_type> factory;
        
        //create array without initial value
        auto a = factory::create(shape_t{100,200});
        
        //create array with initial value
        auto b = factory::create(shape_t{1024,1024},value_type(0));
        \endcode
        */
        //! 
        //! \tparam ShapeT container type for shape information
        //! \param s shape of the array
        //! \param def_val default value for data
        //! \return instance of array_type
        //!
        template<typename ShapeT> 
        static array_type create(const ShapeT &s,
                                 value_type def_val = value_type())
        {
            //create the index map
            auto map = map_utils<map_type>::create(s);
            auto storage = container_utils<storage_type>::create(map.max_elements());
            std::fill(storage.begin(),storage.end(),def_val);
            
            return array_type(std::move(map),std::move(storage));
        }

        //---------------------------------------------------------------------
        //!
        //! \brief create array from shape and data
        //! 
        //! Usually array types can only be created from their original index 
        //! map and storage type. This function allows construction from a 
        //! shape and data stored in arbitrary containers. 
        //! 
        /*! \code 
        typedef ...................... array_type; 
        typedef array_type::value_type value_type;
        typedef std::list<size_t>     shape_type;
        typedef std::list<value_type> storage_type;
        typedef array_factory<array_type> factory;


        shape_type shape  = ....;
        storage_type data = ....;
        auto a = factory::create(shape,data);
        \endcode
        */
        //!
        //! \throws size_mismatch_error if data and shape size do not match
        //! 
        //! \tparam ShapeT container type for shape
        //! \tparam DataT container type for data
        //! \param s reference to shape container
        //! \param data reference to data container
        //! \return instance of ArrayT
        //!
        template<typename ShapeT,
                 typename DataT
                >
        static array_type create(const ShapeT &s,const DataT &data)
        {
            auto map = map_utils<map_type>::create(s);
            if(map.max_elements() != data.size())
            {
            	std::stringstream ss;
            	ss<<"Total number of elements from map ("
                  <<map.max_elements()
				  <<") does not match data size ("
				  <<data.size()<<")!";
                throw size_mismatch_error(PNINEXUS_EXCEPTION_RECORD,ss.str());
            }

            auto storage = container_utils<storage_type>::create(data.size());
            std::copy(data.begin(),data.end(),storage.begin());
            return array_type(std::move(map),std::move(storage));
        }

        //---------------------------------------------------------------------
        //!
        //! \brief construct from initializer list 
        //!
        //! This is maybe the lazy mans version of an array construction 
        //! function.  It uses initializer lists and is thus best suited for 
        //! the construction of small arrays (like matrices). 
        /*!
        \code
        typedef ......................... array_type;
        typedef array_type::value_type    value_type;
        typedef array_factory<array_type> factory;

        auto a = factory::create({3,3},{1,2,3,4,5,6,7,8,9});
        \endcode
        */
        //!
        //! \tparam ShapeT shape value type
        //! \tparam DataT data value type
        //! \param shape initializer list with shape data
        //! \param data initializer list with array data
        //! \return instance of ArrayT
        //!
        template<
                 typename ShapeT,
                 typename DataT
                >
        static array_type create(std::initializer_list<ShapeT> shape,
                                 std::initializer_list<DataT> data)
        {
            auto map = map_utils<map_type>::create(shape);
            if(map.max_elements() != data.size())
            {
            	std::stringstream ss;
            	ss<<"Total number of elements from map ("
            	  <<map.max_elements()
				  <<"does not match data size ("
				  <<data.size()<<")!";
                throw size_mismatch_error(PNINEXUS_EXCEPTION_RECORD,ss.str());
            }

            auto storage = container_utils<storage_type>::create(data.size());
            std::copy(data.begin(),data.end(),storage.begin());
            return array_type(std::move(map),std::move(storage));
        }
        
    };
    
//end of namespace
}

