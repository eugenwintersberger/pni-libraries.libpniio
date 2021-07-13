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
// Created on: Dec 22, 2014
//     Author: Eugen Wintersberger
//

#include <functional>
#include <pni/types/types.hpp>
#include <pni/types/type_id_map.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/at.hpp>

namespace pni{
namespace core{

    //!
    //! \ingroup type_classes
    //! \brief type id container builder
    //!
    template<typename CTYPE> class type_id_container_builder
    {
        private:
            CTYPE _container;
        public:

            template<typename T> void operator()(T)
            {
                type_id_t tid = type_id_map<T>::type_id;
                _container.push_back(tid);
            }

            CTYPE get() const
            {
                return _container;
            }
        
    };

    //------------------------------------------------------------------------
    template<
             typename CTYPE,
             typename TS
            >
    CTYPE build_type_id_container()
    {
        type_id_container_builder<CTYPE> builder;
            
        boost::mpl::for_each<TS>(std::ref(builder));

        return builder.get();
    }
   
    //-------------------------------------------------------------------------
    typedef std::vector<type_id_t> type_id_vector; 

    //!
    //! \brief generate type map pairs
    //!
    //! \tparam T key type
    //! \tparam MAPT MPL map type
    //! 
    template<
             typename T,
             typename MAPT
            >
    std::pair<type_id_t,type_id_vector> generate_map_element()
    {
        typedef typename boost::mpl::at<MAPT,T>::type vector_t;
        
        return {type_id_t(type_id_map<T>::type_id),
                build_type_id_container<type_id_vector,vector_t>()};

    }
//end of namespace
}
}
