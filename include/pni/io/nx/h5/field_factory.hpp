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
// Created on: Jul 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

extern "C"{
#include <hdf5.h>
}

#include <pni/io/nx/h5/h5filter.hpp>
#include <pni/core/types.hpp>
#include <vector>

namespace pni{
namespace io{
namespace nx{
namespace h5{

    //forward declaration of filter
    class object_imp;
    class h5dataspace;
    class group_imp;
    class field_imp;
    class h5datatype;

    //add namespace form core library
    using namespace pni::core;

    //!
    //! \ingroup nxh5_classes
    //! \brief factory for field construction
    //! 
    //! Constructing field implementations is a rather complex thing and thus
    //! the code has been removed from the constructors of the field
    //! implementation class to this factory. 
    //! 
    //! All static methods for field construction follow basically the same
    //! approach: an object_imp instance is constructed representing the 
    //! field which is then used to construct the field_imp instance. 
    //! 
    //! This approach keeps constructors for field_imp simple while still 
    //! providing a convenient way to construct the objects.
    //! 
    //! For Nexus fields some restrictions will be made to how the dataset 
    //! is created
    //! \li each nexus field is extensible along its first dimension
    //! 
    class field_factory
    {
        public:
            //! vector type used for sizes
            typedef std::vector<hsize_t> size_vector_type;
        private:


            //----------------------------------------------------------------
            //!
            //! \brief create field without filter
            //!
            //! This is the fundamental function used to create a field without
            //! a filter.
            //! 
            //! \throws object_error in case of errors
            //! 
            static field_imp create(const object_imp &parent,
                                    const string &name,
                                    const object_imp &create_plist,
                                    const h5datatype &type,
                                    const h5dataspace &space);


            //----------------------------------------------------------------
            //! 
            //! \brief create a default creation property list
            //! 
            //! \throws object_error in case of object creation failure
            //! \return instance of dataset creation property list
            //! 
            static object_imp create_cplist();

            //----------------------------------------------------------------
            //!
            //! \brief create chunk property list
            //!
            //! \throws size_mismatch_error if chunk is empty
            //! \throws object_error in case of any other error
            //! \param chunk container with chunk shape data
            //! \return instance of property list
            //! 
            static object_imp create_cplist(const size_vector_type &chunk);

            //----------------------------------------------------------------
            //!
            //! \brief create dataspace
            //! 
            //! Create a dataspace form a user supplied shape vector.
            //!
            //! \throws size_mismatch_error if shape empty
            //! \throws object_error in case of failures
            //! \param shape user provided shape vector
            //! \return instance of h5dataspace
            //!
            static h5dataspace create_dataspace(const size_vector_type &shape);

        public:
            //----------------------------------------------------------------
            //! 
            //! \brief conversion function to size_vector_type
            //!
            //! Take an arbitrary, STL compliant container type as an input 
            //! and convert it to size_vector_type.
            //! 
            //! \tparam CTYPE container type
            //! \param c instance of CTYPE
            //! \return instance of size_vector_type
            //! 
            template<typename CTYPE> 
            static size_vector_type to_size_vector(const CTYPE &c) noexcept
            {
                size_vector_type v(c.size());
                std::copy(c.begin(),c.end(),v.begin());
                return v;
            }


            //----------------------------------------------------------------
            //!
            //! \brief create a field
            //! 
            //! 
            //! \throws size_mismatch_error if either chunk or shape are empty
            //! or their size does not match
            //! \throws object_error in case of any other error
            //! 
            static field_imp create(const group_imp &parent,
                                    const string &name,
                                    type_id_t tid,
                                    const size_vector_type &shape,
                                    const size_vector_type &chunk,
                                    const h5filter &filter);

    };

//end of namespace
}
}
}
}
