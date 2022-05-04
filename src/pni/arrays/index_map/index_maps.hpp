//!
//! (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//! Created on: Oct 25, 2013
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#pragma once
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <pni/arrays/index_map/index_map.hpp>
#include <pni/arrays/index_map/static_index_map.hpp>
#include <pni/arrays/index_map/c_index_map_imp.hpp>
#include <pni/utilities/container_utils.hpp>

namespace pni{

    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief template for  a static C map
    //!  
    //! A template alias for a static index map with c ordering. To define the 
    //! index map for a 3x3 matrix use something like this
    //! 
    //! \code
    //! static_cindex_map<3,3> matrix_map; 
    //! \endcode
    //! 
    //! \tparam TDimsN number of elements along each dimension
    //! 
    template<size_t... TDimsN> 
    using static_cindex_map = static_index_map<c_index_map_imp,TDimsN...>;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief definition of a dynamic C index map
    //!  
    //! Type definition of a fully dynamic C index map. The structure of the 
    //! map can be fully determined at runtime. The structure of an array.
    //! 
    typedef index_map<std::vector<size_t>,c_index_map_imp> dynamic_cindex_map;

    //-------------------------------------------------------------------------
    //!
    //! \ingroup index_mapping_classes
    //! \brief fixed dimension dynamic C index map
    //! 
    //! For such a map the number of elements along each dimension can be 
    //! changed, however the total size (rank) of the map cannot be changed 
    //! once the concrete type has been defined. 
    //!
    //! A typical example would be to define a map for an image which has 
    //! always a rank of 2 like this
    //!
    //! \code
    //! typedef fixed_dim_cindex_map<2> image_map; 
    //! \endcode
    //!
    //! \tparam TDimN number of dimensions
    template<size_t TDimN> 
    using fixed_dim_cindex_map = index_map<std::array<size_t,TDimN>,c_index_map_imp>;

    //=================define some convienance function========================

    /*!
    \ingroup index_mapping_classes
    \brief utility class for index maps

    This template provides static utility member functions to create index maps.
    Several specializations exist for this template to handle different index
    map types. The major difference between the different types is the storage
    container used to hold the shape information. 
    This is the default implementation for STL compliant containers and
    maps using std::array as a storage. In the latter case an exception is
    thrown if one tries to construct a map of a rank which does not match the
    size of the std::array storage.

    \tparam MapT index map type
    */
    template<typename MapT> struct map_utils
    {
        //! index map type
        typedef MapT map_type;
        //! storage type for MapT
        typedef typename map_type::storage_type storage_type;

        /*!
        \brief create map from container

        Create a new map from a container. In this case the map can do a full
        resizeing. This would be the case when the map allows also resizeing its
        internal storage.

        A typicall application would be 
        \code
        typedef .... index_map_type;
        std::vector<size_t> shape{3,2,4};
        auto map = map_utils<index_map_type>::create(shape);
        \endcode

        If the index map type has a constant rank which cannot be changed an
        exception will be thrown. 

        \throws shape_mismatch_error in case of shape problems.
        \tparam ContainerT container type
        \param c instance of ContainerT with shape information
        \return instance of MapT
        */
        template<typename ContainerT> static MapT create(const ContainerT &c)
        {
            storage_type storage; 

            //try to create a storage type
            try
            {
                storage = container_utils<storage_type>::create(c.size());
            }
            catch(size_mismatch_error &)
            {
                std::stringstream ss;
                ss<<"The map supports only a fixed number of dimensions ("
                    <<storage.size()<<")! However, the container you are "
                    <<"passing has ("<<c.size()<<") elements!"<<std::endl;
                throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
            }
            std::copy(c.begin(),c.end(),storage.begin());
            return MapT(std::move(storage)); 
        }

        //---------------------------------------------------------------------
        /*!
        \brief create map from initializer list

        Create anew map from an initializer list. 
        \throws shape_mismatch_error
        \param shape initializer list with shape data
        \return instance of MapT
        */
        template<typename IndexT> 
        static MapT create(std::initializer_list<IndexT> shape)
        {
            storage_type storage;

            try
            {
                storage = container_utils<storage_type>::create(shape);
            }
            catch(size_mismatch_error &)
            {
                throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Rank of user shape ("
                    +boost::lexical_cast<string>(shape.size())+
                    ") does not match the map rank ("
                    +boost::lexical_cast<string>(map_type().rank())+")!");
            }
            std::copy(shape.begin(),shape.end(),storage.begin());
            return MapT(std::move(storage));
        }
    };

    //-------------------------------------------------------------------------
    /*!
    \ingroup index_mapping_classes
    \brief utility class for static index maps

    Static index maps are quite special as they cannot be altered after
    instantiation (all information is fixed at compile time. 
    
    
    \tparam PolicyT policy type
    \tparam TDimsN number of elements along each dimension
    */
    template<typename PolicyT,size_t...TDimsN>
    struct map_utils<static_index_map<PolicyT,TDimsN...> >
    {
        //! index map type
        typedef static_index_map<PolicyT,TDimsN...> map_type;

        //!
        //! \brief creat map from container
        //! 
        //! Create an index map from a container. The number of elements along
        //! dimension are passed in a container of type ContainerT.
        //! 
        //! \tparam ContainerT shape container type
        //! \param c container instance with shape information
        //! \return instance of map_type
        //! 
        template<typename ContainerT> static map_type create(const ContainerT &c)
        {
            map_type map;
            if(c.size() != map.rank())
                throw size_mismatch_error(EXCEPTION_RECORD,
                        "rank does not match");

            if(!std::equal(map.begin(),map.end(),c.begin()))
                throw shape_mismatch_error(EXCEPTION_RECORD,
                        "Elements counts do not match!");

            return map;
        }

        //---------------------------------------------------------------------
        //!
        //! \brief create index map from initializer list
        //! 
        //! Uses an initializer list to build an index map.
        //! 
        //! \tparam IndexT index typ
        //! \param shape initializer list with shape information
        //! \return map_type instance
        //!
        template<typename IndexT> 
        static map_type create(std::initializer_list<IndexT> shape)
        {
            map_type map;
            if(shape.size() != map.rank())
                throw size_mismatch_error(EXCEPTION_RECORD,
                        "rank does not match");

            if(!std::equal(map.begin(),map.end(),shape.begin()))
                throw shape_mismatch_error(EXCEPTION_RECORD,
                        "Elements counts do not match!");

            return map;
        }
        
    };

//end of namespace
}
