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
 * Declaration of an HDF5 attribute object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __H5ATTRIBUTEOBJECT_HPP__
#define __H5ATTRIBUTEOBJECT_HPP__

#include <pni/utils/Types.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Buffer.hpp>

#include "H5NamedObject.hpp"
#include "H5Attribute.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            
            //! \ingroup nxh5_classes
            //! \brief objects which can hold attributes
            class H5AttributeObject:public H5NamedObject{
                protected:
                    H5AttributeObject(const hid_t &oid);
                public:
                    //===========constructors and destructors==================
                    //! default constructor
                    explicit H5AttributeObject();
                    //! copy constructor
                    explicit H5AttributeObject(const H5AttributeObject &o);
                    //! copy conversion constructor
                    H5AttributeObject(const H5Object &o);
                    //! move constructor
                    explicit H5AttributeObject(H5AttributeObject &&);
                    //! move conversion constructor
                    H5AttributeObject(H5Object &&o);
                    //! destructor

                    //! Destructor - must be virtual in order to use this 
                    //! class as a base class.
                    virtual ~H5AttributeObject();

                    //===========assignment operators==========================
                    //! copy assignment operator
                    H5AttributeObject &operator=(const H5AttributeObject &o);
                    //! copy conversion assignment operator
                    H5AttributeObject &operator=(const H5Object &o);
                    //! move assignment operator
                    H5AttributeObject &operator=(H5AttributeObject &&o);
                    //! move conversion assignment operator
                    H5AttributeObject &operator=(H5Object &&o);


                    //===========attribute management methods==================
                    //! create scalar attribute

                    //! Create a scalar attribute. This method acts as a 
                    //! factory method for an attribute object.
                    //! \param n name of the attribute
                    //! \param tid ID of the data-type
                    //! \return attribute object
                    H5Attribute attr(const String &n,const TypeID &tid) const;
                    //! create an array attribute

                    //! Create an array attribute. This method acts as a 
                    //! factory method for an attribute object.
                    //! \param n name of the attribute
                    //! \param tid ID of the data-type
                    //! \param s shape of the array
                    //! \return attribute object
                    H5Attribute attr(const String &n,const TypeID &tid,
                                     const Shape &s) const;

                    //! open an attribute
                    
                    //! Open an existing attribute and returns it to the 
                    //! callee. 
                    //! \param n name of the attribute
                    //! \return attribute object
                    H5Attribute attr(const String &n) const;

            };
        

        //end of namespace
        }
    }
}



#endif
