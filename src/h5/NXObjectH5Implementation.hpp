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
 * NXObjectH5Implementation.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef NXOBJECTH5IMPLEMENTATION_HPP_
#define NXOBJECTH5IMPLEMENTATION_HPP_

extern "C" {
#include <hdf5.h>
}

#include <pni/utils/Types.hpp>
#include <pni/utils/Scalar.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>

#include "H5TypeFactory.hpp"
#include "H5Exceptions.hpp"
#include "../NXImpCode.hpp"
#include "../NXTypes.hpp"

namespace pni{
namespace nx{
namespace h5{


using namespace pni::utils;
//! \ingroup nxh5_classes
//! \brief Implementation of an NXObject

//! This object basically implements the basic functionality of an NXObject.
//! You can
//! - set and get attributes
//! - and obtain the name of an object
//! In addition basic object inquiry methods are implemented in this class.
//! Attributes can be either objects of class NumericObject or String.
//! In the former case the description and unit attribute of the
//! NumericObject are ignored. Thus, attributes are not a good place to store
//! data which depends on physical units. Subsequent calls to setAttribute
//! with the same attribute name will overwrite an exsisting attribute of
//! that name.
class NXObjectH5Implementation {
private:
	//! create and write an attribute
	void _create_and_write_attribute(hid_t pid,const char *n,hid_t type_id,
			                         hid_t space_id,const void *ptr) const;
	//! open an attribute
	void _open_attribute(const hid_t &pid,const char *n,hid_t &attr_id,
			             hid_t &type_id,hid_t &space_id) const;

	hid_t  _id;    //!< handler of the object this class referes too
protected:

	//! get object ID
	//should be moved to protected and thus not exposed to the public
	//interface of the class
	inline hid_t get_id() const{
		return _id;
	}

	//! set object ID
	//should be moved to protected and thus not be exposed to the public
	//interface of the class
	inline void set_id(hid_t id){
		//if the object has already a valid ID we need to decrement the
		//reference counter on this object - the object will be destroyed
		//if its reference counter approaches 0
		if(H5Iis_valid(_id)) H5Idec_ref(_id);

		//set _id to its new value
		//we need to check if we maybe must increment the reference counter
		//of the object refered to by id
		_id = id;
	}
public:
	typedef boost::shared_ptr<NXObjectH5Implementation> sptr;
	static const ImpCodes IMPCODE = HDF5;
	//! default constructor
	NXObjectH5Implementation();
	NXObjectH5Implementation(hid_t id){
		set_id(id);
	}
	//! destructor
	virtual ~NXObjectH5Implementation();

	//! copy constructor
	NXObjectH5Implementation(const NXObjectH5Implementation &);
	//! move constructor
	NXObjectH5Implementation(NXObjectH5Implementation &&o);

	//! copy assignment operator

	//! HDF5 objects can be assigned to each other - the basic idea is that
	//! the new object holds a reference to an already existing object.
	NXObjectH5Implementation &operator=(const NXObjectH5Implementation &o);

	//! move assignment operator
	NXObjectH5Implementation &operator=(NXObjectH5Implementation &&o);

	//! write attribute from ArrayObject

	//! Write an attribute from an ArrayObject. The unit and description
	//! of the array object are ignored.
	//! \throws H5AttributeError in case of errors
	//! \throws TypeError if data type creation failed
	//! \param n attribute name
	//! \param a attribute value
	void set_attr(const String &n,const ArrayObject &a) const;
	//! write attribute from ScalarObject

	//! Write an attribute of type ScalarObject. The unit and description
	//! of the ScalarObject are ignored.
	//! \throws H5AttributeError in case of errors
	//! \throws TypeError if data type creation failed
	//! \throws H5DataSetError if data-set creation failed
	//! \param n attribute name
	//! \param s attribute value
	void set_attr(const String &n,const ScalarObject &s) const;
	//! write attribute data from a String object
	void set_attr(const String &n,const String &) const;

	//! read attribute data to an ArrayObject
	void get_attr(const String &n,ArrayObject &a) const;
	//! read attribute data to a ScalarObject
	void get_attr(const String &n,ScalarObject &s) const;
	//! read attribute data to a String object
	void get_attr(const String &n,String &s) const;

    //! template to write attribute
    template<typename T> void attribute(const String &n,const T &value);
    //! template to read attribute
    template<typename T> T attribute(const String &n);

	//! get object path

	//! Returns the path of the object within the HDF5 tree.
	//! \return full path of the object
	virtual String path() const;
	//! get object path base

	//! Returns the base name of an object. The base name is the path of an
	//! object without the very last entitiy (the object name).
	//! So if an object has the path /scan/detector/data the base name
	//! would be /scan/detector.
	//! \return base name of the object
	virtual String base() const;
	//! get object name

	//! The name of an object is the last entity of the full path.
	//! If an object has the full path /scan/detector/data the name would be
	//! data.
	//! \return object name
	virtual String name() const;
	//! close the object
	virtual void close();
	//! check if open

	//! Return true if the object is opened. This method can be used to check
	//! whether or not an object can be used for read or write data or
	//! as a root object for other objects.
	//! \return true if open, false otherwise
	virtual bool is_open() const;
	//! return the object class
	virtual pni::nx::NXObjectClass object_class() const;

	//! create link to this object

	//! Creates a link from this object below pos under name n.
	//! \throws H5ObjectError if this object is not open or pos is invalid
	//! \throws H5LinkError if linking failed
	//! \param pos parent object for the link
	//! \param name name of the link below its parent object
	virtual void link(const NXObjectH5Implementation &pos,const String &n) const;
	//! create link to this object

	//! Creates a link to this object specified by path.
	//! \throws H5ObjectError if this object is not open
	//! \throws H5LinkError if link creation failed.
	//! \param path path of the link
	virtual void link(const String &path) const;

};

//default function to obtain the address of an object
//This needs to be specialized for several special data types.
template<typename T> void *get_object_data_ptr(const T &value){
    return (void *)(&value);
}

//default function template to obtain the data type
template<typename T> hid_t get_object_datatype(const T &value){
    return H5TFactory.create_type<T>();
}

//default function to obtain the data space of an object
template<typename T> hid_t get_object_dataspace(const T &value){
    hid_t space_id;
    //in the default case we return a scalar data space
    
    space_id = H5Screate(H5S_SCALAR);
     
    return space_id;
}

//default reading routine - here we assume that the return 
//type is plain old data.
template<typename T> T read_attribute_data(hid_t id)
{
    EXCEPTION_SETUP("template<typename T> T "
                    "read_attribute_data(hid_t id)");
    hid_t space_id = 0;
    hid_t type_id  = 0;
    T value;

    //fetch everything we need from the attribute
    space_id = H5Aget_space(id);
    //check if the data space is scalar (a requirement for 
    //reading data to a POD variable
    if(H5Sis_simple(space_id)!=0){
        EXCEPTION_INIT(H5AttributeError,"Attribute is not scalar!");
        EXCEPTION_THROW();
    }

    type_id  = H5TFactory.create_type<T>(); //set the memory type

    herr_t err;
    err = H5Aread(id,type_id,(void *)(&value));
    if(err<0){
        //a possible source of error could be that the data types are
        //not convertible
        EXCEPTION_INIT(H5AttributeError,"Error reading attribute!");
        EXCEPTION_THROW();
    }

    return value;
}

//-----------------------------------------------------------------------------
//! template to write attribute
template<typename T> void NXObjectH5Implementation::attribute(const String &n,
                                                    const T &value)
{
    EXCEPTION_SETUP("template<typename T> void NXObjectH5Implementation::"
                    "attribute(const String &n,const T &value)");
    htri_t retval;

    //delete the attribute if it exists
    retval = H5Aexists(_id,n.c_str());
    if(retval>0){
        H5Adelete(_id,n.c_str());
    }else if(retval<0){
        EXCEPTION_INIT(H5AttributeError,
                    "Existence check of attribute ["+n+"]failed!");
        EXCEPTION_THROW();
    }

    //now we have to determine the data type and dataspace from 
    //the object passed
    hid_t type_id = get_object_datatype(value);
    hid_t space_id = get_object_dataspace(value);
    void *ptr = get_object_data_ptr(value);

    //with this we can now write the attribute to the file

	//create the attribute and check for errors
	hid_t aid = H5Acreate2(_id,n.c_str(),type_id,space_id,
                           H5P_DEFAULT,H5P_DEFAULT);
	if(aid<0){
		EXCEPTION_INIT(H5AttributeError,
                "Error creating array attribute ["+n+"]!");
        H5Tclose(type_id);
		H5Sclose(space_id);
		EXCEPTION_THROW();
	}

	//write data and check for errors
	if((H5Awrite(aid,type_id,ptr))<0){
		EXCEPTION_INIT(H5AttributeError,
                "Error writing data to array attribute ["+n+"]!");
		H5Aclose(aid);
        H5Tclose(type_id);
		H5Sclose(space_id);
		EXCEPTION_THROW();
	}

	H5Aclose(aid);
}

//-----------------------------------------------------------------------------
//! template to read attribute
template<typename T> T NXObjectH5Implementation::attribute(const String &n)
{
    EXCEPTION_SETUP("template<typename T> T NXObjectH5Implementation::"
                    "attribute(const String &n)");
    //the first thing we have to check is whether or not the attribute 
    //exists and if not raise an exception
    htri_t retval;

    //delete the attribute if it exists
    retval = H5Aexists(_id,n.c_str());
    if(retval<=0){
        EXCEPTION_INIT(H5AttributeError,"Attribute ["+n+"] does not exist!");
        EXCEPTION_THROW();
    }
    
    
}


//end of namespace
}
}
}




#endif /* NXOBJECTH5IMPLEMENTATION_HPP_ */
