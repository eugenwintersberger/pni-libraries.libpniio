/*
 * Declaration of Nexus specific exceptions
 *
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
 * H5ErrorStack.hpp
 *
 *  Created on: Jul 28, 2011
 *      Author: eugen
 */

#ifndef H5ERRORSTACK_HPP_
#define H5ERRORSTACK_HPP_

extern "C"{
#include <hdf5.h>
}

#include <iostream>
#include <vector>

#include <pni/utils/Types.hpp>
#include <pni/utils/Exceptions.hpp>

namespace pni {
namespace nx {
namespace h5 {

//Walker functins to read over error messages
extern "C" herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data);

using namespace pni::utils;

//! \ingroup nxh5_classes error_classes
//! \brief HDF5 error record

//! This class describes an HDF5 error record. Such a record consists basically
//! of a class id (which is HDF5 for all HDF5 library functions),
//! a description, a major and a minor message, and the name of the function
//! where the error occurred. Along with this the name of the HDF5 source file
//! where the function is defined is stored.
class H5Error{
private:
	hid_t _class_id;       //!< error class
	String _class_name;    //!< name of the error class
	hid_t _major_number;   //!< major number of the error
	hid_t _minor_number;   //!< minor number of the error
	String _file_name;     //!< name of the source file where the error occurred
	String _func_name;     //!< name of the HDF5 function where the error occurred
	String _description;   //!< optional description of the error
	String _minor_message; //!< minor message of the error
	String _major_message; //!< major message of the error
public:
	//! default constructor
	H5Error();

	//! copy constructor
	H5Error(const H5Error &e);

	//! default destructor
	virtual ~H5Error();

	//! assignment operator
	H5Error &operator=(const H5Error &e);
	
	//! get class ID
	
	//! Get the error class ID
	//! \return error class ID
	hid_t class_id() const;
	
	//! set class ID
	
	//! Sets the class id from an object. 
	//! If internal buffer allocation fails an exception will be 
	//! thrown.
	//! \throws MemoryAllocationError if buffer allocation fails
	//! \param id object ID
	void class_id(hid_t id);
	
	//! get major number
	hid_t major_number() const;
	//! set major number
	void major_number(hid_t v);

	//! get minor number
	hid_t minor_number() const;
	//! set minor number
	void minor_number(hid_t v);

	//! get file name
	String file_name() const;
	//! get file name
	void file_name(const String &n);

	//! get function name
	String func_name() const;
	//! set function name
	void func_name(const String &n);

	//! get description
	String description() const;
	//! set description
	void description(const String &n);
	
	//! get major message
	String major_message() const;
	//! get minor message
	String minor_message() const;
	
	//! ouput stream operator
	friend std::ostream &operator<<(std::ostream &o,const H5Error &e);
};

//! \ingroup nxh5_classes error_classes
//! \brief HDF5 error stack

//! Class HDF5ErrorStack provides a simple object oriented interface to the
//! HDF5 error stack.
class H5ErrorStack {
private:
	hid_t _stack_id;      //!< id of the error stack
	std::vector<H5Error> _errors; //!< vector with error records on this stack

public:
	//! default constructor
	H5ErrorStack();
	//! copy constructor
	H5ErrorStack(const H5ErrorStack &s);
	//! default destructor
	virtual ~H5ErrorStack();

	H5ErrorStack &operator=(const H5ErrorStack &s);

	//! get number of errors

	//! Returns the total number of HDF5 errors in the stack.
	//! \return number of errors
	ssize_t number_of_errors() const{
		return _errors.size();
	}

	//! fill stack

	//! Reads error messages from the current HDF5 error stack 
	//! and add them to the stack.	
	void fill();

	//! append error

	//! Appends a single error to the stack.
	//! \param e HDF5 error record
	void append(const H5Error &e);

	//! ostream operator
	friend std::ostream &operator<<(std::ostream &o,const H5ErrorStack &s);
	//! walker function

	//! This function is used to walk through the HDF5 error stack. 
	friend herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data);
};


//end of namespace
}
}
}

#endif /* H5ERRORSTACK_HPP_ */
