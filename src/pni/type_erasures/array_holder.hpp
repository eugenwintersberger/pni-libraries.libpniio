//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: 11 08, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/algorithms.hpp>
#include <pni/type_erasures/array_holder_interface.hpp>

namespace pni{
namespace core{

    //!
    //! \ingroup type_erasure_classes_internal  
    //! \brief get array pointer
    //! 
    //! Return a pointer to the data stored in an array. 
    //! \tparam ATYPE array type
    //! \param a instance of ATYPE
    //! \return pointer to array data
    //! 
    template<typename ATYPE> 
    const void *get_pointer(const ATYPE &a)
    {
        return (void *)(a.data());
    }


    //-------------------------------------------------------------------------
    //!
    //! \ingroup type_erasure_classes_internal
    //! \brief array holder template 
    //! 
    //! Template for the array holder used in the array type erasure.
    //! \tparam OT array type
    //!
    template<typename OT> 
    class array_holder:public array_holder_interface
    {
        private:
            OT _object; //!< the original object 
        public:
            //==================constructors and destructor====================
            //!construct by copying o
            array_holder(const OT &o):_object(o) {}

            //-----------------------------------------------------------------
            //!construct by moving o
            array_holder(OT &&o):_object(std::move(o)) {}

            //-----------------------------------------------------------------
            //!copy constructor
            array_holder(const array_holder<OT> &o):
                _object(o._object) 
            {}

            //-----------------------------------------------------------------
            //!move constructor
            array_holder(array_holder<OT> &&o):
                _object(std::move(o._object)) 
            {}

            //!
            //! \brief virtual destructor
            //!
            virtual ~array_holder() {}

            //-----------------------------------------------------------------
            //!
            //! \brief clone the holder
            //!
            //! Member function cloning the array holder.
            //! \return pointer to an array holder class
            //!
            virtual array_holder_interface *clone() const 
            {
                return new array_holder<OT>(_object);
            }

            //====================public member functions======================
            //! return type ID of the held array
            virtual type_id_t type_id() const{ return OT::type_id; }
            
            //-----------------------------------------------------------------
            //! return the rank of the held array
            virtual size_t rank() const { return _object.rank(); }

            //-----------------------------------------------------------------
            //! return the shape of the held array
            virtual shape_t shape() const 
            {
                return _object.template shape<shape_t>();
            }

            //-----------------------------------------------------------------
            //! return the total number of elements in the array
            virtual size_t size() const { return _object.size(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get value
            //! 
            //! Get value at linear index i. As this is a const member the 
            //! return value uses the value type erasure to wrap the value 
            //! returned.  This operator does not check the index. If the index 
            //! is larger than the total size of the array a segmentation 
            //! fault will most probably occur.
            //! 
            //! \param i linear index
            //! \return instance of value with the data at i
            //!
            virtual value operator[](size_t i) const
            {
                return value(_object[i]);
            }

            //-----------------------------------------------------------------
            //! 
            //! \brief get value reference
            //! 
            //! Returns a reference to the element at linear index i. The 
            //! reference is wrapped in the value_ref type erasure. No index 
            //! checking is performed. If i exceeds the total size of the 
            //! array a segmentation fault will most probably occur.
            //! 
            //! \param i linear index
            //! \return reference type erasure.
            //!
            virtual value_ref operator[](size_t i) 
            {
                return value_ref(std::ref(_object[i]));
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get value 
            //!
            //! Return the value at linear index i. Unlike the [] operator this
            //! function performs index checking. 
            //! 
            //! \throws index_error if i exceeds the size of the array
            //! \param i linear index
            //! \return instance of value
            //!
            virtual value at(size_t i) const 
            {
                return value(_object.at(i));
            }

            //-----------------------------------------------------------------
            //!
            //!\brief get reference
            //! 
            //! Return a reference to the value at linear index i. Unlike the 
            //! [] operator this function performs index checking.
            //!
            //! \throws index_error if i exceeds the size of the array
            //! \param i linear index 
            //! \return reference to the value
            //!
            virtual value_ref at(size_t i) 
            {
                return value_ref(std::ref(_object.at(i)));
            }

            //-----------------------------------------------------------------
            //! return element value
            virtual value operator()(const element_index &index) const 
            {
                return value(_object(index));
            }

            //-----------------------------------------------------------------
            //! return element reference
            virtual value_ref operator()(const element_index &index) 
            {
                return value_ref(std::ref(_object(index)));
            }

            //-----------------------------------------------------------------
            //! write data to output stream
            virtual std::ostream &write(std::ostream &os) const 
            {
                os<<_object;
                return os;
            }

            //-----------------------------------------------------------------
            //! read data from input stream
            virtual std::istream &read(std::istream &is) 
            {
                is>>_object; 
                return is;
            }

            //-----------------------------------------------------------------
            //! return the name of the type
            virtual string type_name() const
            {
                return typeid(OT).name();
            }

            //-----------------------------------------------------------------
            //! return pointer to data
            virtual const void *ptr() const
            {
                return get_pointer(_object);            
            }

    };

//end of namespace
}
}
