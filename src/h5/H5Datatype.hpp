/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of a general HDF5 datatype object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5DATATYPE_HPP__
#define __H5DATATYPE_HPP__

#include <pni/utils/Types.hpp>

using namespace pni::utils;

#include "H5Object.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            
            //! \brief HDF5 type wrapper

            //! The class wraps around an HDF5 type object. 
            class H5Datatype:public H5Object{
                private: 
                    hid_t __get_type_from_id(const TypeID &tid);

                    //from this class we would need a singleton - should be available only
                    //once at runtime - most probably as a global object.
                    typedef struct {
                        Float32 r;
                        Float32 i;

                    } _struct_complex_32;  //!< C structure for a 32Bit complex type
                    typedef struct {
                        Float64 r;
                        Float64 i;
                    } _struct_complex_64;  //!< C structure for a 64Bit complex type

                    typedef struct {
                        Float128 r;
                        Float128 i;
                    } _struct_complex_128; //!< C structure for a 128Bit complex type
                    
                    //create a string type 
	                static hid_t _create_string_type();

                    //! private method to create the complex types
                    template<typename T> static hid_t _create_complex_type();
                public:
                    //======================Constructors and destructors=======
                    //! default constructor
                    H5Datatype();
                    //! copy constructor
                    H5Datatype(const H5Datatype &o);
                    //! copy conversion operator
                    H5Datatype(const H5Object &o);
                    //! move constructor
                    H5Datatype(H5Datatype &&o);
                    //! move conversion operator
                    H5Datatype(H5Object &&o);
                    //! constructor from TypeID
                    H5Datatype(const TypeID &tid);
                    //! constructor form HDF5 id
                    H5Datatype(const hid_t &tid);
                    //! destructor
                    virtual ~H5Datatype();

                    //=============factory methods=============================
                    //! creation template

                    //! Use this static template method to create a type from 
                    //! an existing PNI type. This is particularly useful 
                    //! if you want to create a type independant from its
                    //! TypeID.
                    template<typename T> static H5Datatype create();


                    //==========Assignment operators===========================
                    //! copy assignment operator
                    H5Datatype &operator=(const H5Datatype &o);
                    //! copy conversion assignment operator
                    H5Datatype &operator=(const H5Object &o);
                    //! move assignment operator
                    H5Datatype &operator=(H5Datatype &&o);
                    //! move conversion assignment operator
                    H5Datatype &operator=(H5Object &&o);

                    //==========some inquery methods===========================
                    TypeID type_id() const;

                    virtual void close();


                    //!==========comparison operators==========================
                    //! equality comparison
                    friend bool operator==(const H5Datatype &a,const H5Datatype &b);
                    //! inequality 
                    friend bool operator!=(const H5Datatype &a,const H5Datatype &b);
            };


        //end of namespace
        }
    }
}


#endif
