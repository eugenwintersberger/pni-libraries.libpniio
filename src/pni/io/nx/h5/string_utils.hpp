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
// Created on: Jul 21, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include <vector>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/string_formatter.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{
   
    //!
    //! \ingroup hdf5_internal_classes
    //! \brief vector type for individual characters
    //!
    //! This type is mainly used for reading strings of static size from a 
    //! field or attribute. 
    //! 
    typedef std::vector<char> char_vector_type;

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief vector tyep for char pointers
    //!
    //! Mainly used for reading strings of variable length from a field or
    //! attribute.
    //! 
    typedef std::vector<char*> char_ptr_vector_type;

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief vector type for const char pointers
    //!
    //! This type is mainly used for writing strings of variable length to 
    //! a field or attribute
    //!
    typedef std::vector<const char*> char_const_ptr_vector_type;
    
    //------------------------------------------------------------------------
    //! 
    //! \ingroup nxh5_classes
    //! \brief check variable length string 
    //! 
    //! Returns true if the data type represents a variable length string 
    //! type.
    //! 
    //! \throws object_error if type inquery fails
    //! \throws invalid_object_error if type is not valid
    //! \throws type_error if the datatype is not supported
    //! 
    //! \param type a type instance
    //! \return true if VL string type, false otherwise
    //!
    bool is_vl_string(const h5datatype &type);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief check if static length string
    //! 
    //! Returns true if the data type represents a static length string. 
    //! If type is not a string type at all false will be returned. 
    //!
    //! \throw object_error if information retrieval fails
    //! \throw invalid_object_error if object not valid
    //! \throw type_error if data type is not supported
    //!
    //! \param type instance of h5datatype
    //! \return true if static string type, false otherwise
    //!
    bool is_static_string(const h5datatype &type);

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief get static string size
    //! 
    //! Return the size of the strings for a static string size type. 
    //! 
    //! \throws type_error if type is not a static string type
    //! \throws invalid_type_error if the type is not valid
    //! \throws object_error in any other case
    //!
    //! \param type the datatype from which to retrieve the string size
    //! \return number of characters in each string
    //! 
    size_t static_string_size(const h5datatype &type);


    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief copy char vector to strings
    //!
    //! Copies the content of char vector to a set of strings. An exception is 
    //! throws if the total number of required characters does not match the 
    //! size of the vector.
    //!
    //! \throws size_mismatch_error if nstrs*strsize!=vector.size()
    //!
    //! \param vector the vector with characters
    //! \param nstrs number of strings
    //! \param strsize size of the strings
    //! \param strings pointer to the first string instance
    //!
    void copy_from_vector(const char_vector_type &vector,size_t nstrs,
                          size_t strsize,pni::core::string *strings,
                          const formatter_ptr &formatter);

    //-----------------------------------------------------------------------
    //!
    //! \ingroup nxh5_classes
    //! \brief copy strings from vector to a pointer of strings
    //!
    //! Copies the content of a pointer of stringsa
    //!
    //! \throws size_mismatch_error if number of strings and vector size do
    //! not match
    //!
    //! \param vector the vector with char poitners
    //! \param nstrs number of strings
    //! \param strings pointer to the first string
    //!
    void copy_from_vector(const char_ptr_vector_type &vector,size_t nstrs,
                          pni::core::string *strings,
                          const formatter_ptr &formatter);
                          
    bool is_nullterm_str(const h5datatype &type);
    bool is_nullpad_str(const h5datatype &type);
    bool is_spacepad_str(const h5datatype &type);
    
    bool is_string_type(const h5datatype &type);
                          
                          

}
}
}
}
