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

#include <vector>

#include <pni/utils/Types.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/Buffer.hpp>
#include <pni/utils/IDTypeMap.hpp>

#include "H5NamedObject.hpp"
#include "H5Attribute.hpp"
#include "H5DatatypeFactory.hpp"


namespace pni{
    namespace nx{
        namespace h5{
                     

            //forward declarations
            template<typename H5ObjectT,typename ItemT> class H5GroupIterator;
            
            //! \ingroup nxh5_classes
            //! \brief objects which can hold attributes
            class H5AttributeObject:public H5NamedObject{
                private:
                   static herr_t __get_attribute_names(hid_t locid,const char *name,
                            const H5A_info_t *info,void *data);
                protected:
                    explicit H5AttributeObject(const hid_t &oid);
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
                    template<typename T>
                        H5Attribute attr(const String &n) const;
                    template<TypeID ID>
                        H5Attribute attr(const String &n) const;
                    //! create an array attribute

                    //! Create an array attribute. This method acts as a 
                    //! factory method for an attribute object.
                    //! \param n name of the attribute
                    //! \param tid ID of the data-type
                    //! \param s shape of the array
                    //! \return attribute object
                    template<typename T>
                        H5Attribute attr(const String &n, const Shape &s) const;
                    template<TypeID ID>
                        H5Attribute attr(const String &n, const Shape &s) const;

                    //! open an attribute
                    
                    //! Open an existing attribute and returns it to the 
                    //! callee. 
                    //! \param n name of the attribute
                    //! \return attribute object
                    H5Attribute attr(const String &n) const;

                    //! checks for an attributes existance

                    //! Checks if an attribute exists and returns true
                    //! if it does. Otherwise false will be returned.
                    //! \param n name of the attribute to check for
                    //! \return true if exists, false otherwise
                    bool has_attr(const String &n) const;

                    //! delets an attribute

                    //! Deltets an attribute from the object. 
                    //! \throws H5AttributeError if the attribute does not exist
                    //! \param n name of the attribute
                    void del_attr(const String &n) const;

                    //! get number of attributes

                    //! Method returns the number of attributes attached
                    //! to this object.
                    //! \return number of attributes
                    size_t nattr() const;

                    //! list of attribute names

                    //! Returns a vector of names of all attributes
                    //! attached to this object. 
                    //! \return vector of attribute names
                    std::vector<String> attr_names() const;

                    template<typename H5ObjectT,typename ItemT> friend class
                        H5LinkIterator;
            };

            //implementation of the scalar attribute factory method
            template<typename T>
            H5Attribute H5AttributeObject::attr(const String &n) const{
                EXCEPTION_SETUP("H5Attribute H5AttributeObject::create_attr"
                        "(const String &n,const TypeID &tid) const");

                H5Datatype type = H5DatatypeFactory::create_type<T>();
                H5Dataspace space;

                hid_t aid = H5Acreate2(id(),n.c_str(),type.id(),space.id(),
                        H5P_DEFAULT,H5P_DEFAULT);
                if(aid < 0){
                    EXCEPTION_INIT(H5AttributeError,"Cannot create attribute!");
                    EXCEPTION_THROW();
                }

                H5Attribute a(aid);
                H5Aclose(aid);
                return a;
            }
            
            template<TypeID ID>
            H5Attribute H5AttributeObject::attr(const String &n) const{
                return attr<typename IDTypeMap<ID>::type>(n);
            }

            //-----------------------------------------------------------------
            //implementation of the array attribute factory method
            template<typename T>
            H5Attribute H5AttributeObject::attr(const String &n,const Shape &s) const{
                EXCEPTION_SETUP("H5Attribute H5AttributeObject::create_attr"
                        "(const String &n,const TypeID &tid,const Shape &s)"
                        "const");

                H5Datatype type = H5DatatypeFactory::create_type<T>();
                H5Dataspace space(s);

                hid_t aid = H5Acreate2(id(),n.c_str(),type.id(),space.id(),
                        H5P_DEFAULT,H5P_DEFAULT);
                if(aid < 0){
                    EXCEPTION_INIT(H5AttributeError,"Cannot create attribute!");
                    EXCEPTION_THROW();
                }

                H5Attribute a(aid);
                H5Aclose(aid);
                return a;

            }

            template<TypeID ID>
            H5Attribute H5AttributeObject::attr(const String &n,const Shape &s) const{
                return attr<typename IDTypeMap<ID>::type>(n,s);
            }
        

        //end of namespace
        }
    }
}



#endif
