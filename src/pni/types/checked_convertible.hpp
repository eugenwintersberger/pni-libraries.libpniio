//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Dec 18, 2014
//      Author: Eugen Wintersberger
//
#pragma once

#include <boost/mpl/pair.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <pni/types/id_type_map.hpp>

namespace pni{
namespace core{


    //!
    //! \ingroup type_classes_internal
    //! \brief unchecked convertible map
    //! 
    //! This map provides for each type a list of types to which this type 
    //! can be converted only with range checking. 
    typedef boost::mpl::map<
        //-------------source type uint8--------------------------------------
        boost::mpl::pair<uint8,boost::mpl::vector<int8>>,

        //----------------source type uint16----------------------------------
        boost::mpl::pair<
                         uint16,
                         boost::mpl::vector<uint8,int8,int16>
                       >,

        //----------------------source type uint32----------------------------
        boost::mpl::pair<
                         uint32,
                         boost::mpl::vector<uint8,uint16,
                                            int8,int16,int32>
                       >,

        //--------------------------source type uint64------------------------
        boost::mpl::pair<
                         uint64,
                         boost::mpl::vector<uint8,uint16,uint32,
                                            int8,int16,int32,int64>
                       >,

        //------------------------source type int8 ---------------------------
        boost::mpl::pair<
                         int8,
                         boost::mpl::vector<uint8,uint16,uint32,uint64>
                       >,

        //-----------------------source type int16----------------------------
        boost::mpl::pair<
                         int16,
                         boost::mpl::vector<uint8,uint16,uint32,uint64,int8>
                       >,

        //------------------------source type int32---------------------------
        boost::mpl::pair<
                         int32,
                         boost::mpl::vector<uint8,uint16,uint32,uint64,
                                            int8,int16>
                       >,

        //------------------------source type int64----------------------------
        boost::mpl::pair<
                         int64,
                         boost::mpl::vector<uint8,uint16,uint32,uint64,
                                            int8,int16,int32>
                       >,

        //-------------------------source type float64------------------------
        boost::mpl::pair<float32,boost::mpl::vector<>>,
        boost::mpl::pair<float64,boost::mpl::vector<float32,complex32> >,

        //-------------------source type float128-----------------------------
        boost::mpl::pair<float128,boost::mpl::vector<float32,float64,
                                  complex32,complex64>>,

        //-------------------source type complex64----------------------------
        boost::mpl::pair<complex32,boost::mpl::vector<>>,
        boost::mpl::pair<
                         complex64,
                         boost::mpl::vector<complex32>
                        >,

        //-------------------source type complex128---------------------------
        boost::mpl::pair<complex128,boost::mpl::vector<complex32,complex64>>,

        boost::mpl::pair<string,boost::mpl::vector<>>,
        boost::mpl::pair<binary,boost::mpl::vector<>>,
        boost::mpl::pair<bool_t,boost::mpl::vector<>>

        > checked_type_vectors;

    //------------------------------------------------------------------------
    //!
    //! \ingroup type_classes
    //! \brief check if a type is unchecked convertible
    //!
    //! This template provides information about if a type can be converted
    //! to another without having the range checked. 
    //! 
    //! \tparam ST source type
    //! \tparam TT target type
    template<
             typename ST,
             typename TT
            >
    struct checked_convertible
    {
        //! select the type vector
        typedef typename boost::mpl::at<checked_type_vectors,ST>::type map_element;
        //! type to check if TT is in the map
        typedef boost::mpl::contains<map_element,TT> c;
        //! result of the search
        static const bool value = c::value;
    };


//end of namespace
}
}
