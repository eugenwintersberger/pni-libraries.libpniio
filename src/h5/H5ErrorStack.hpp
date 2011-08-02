/*
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

#include <pni/utils/PNITypes.hpp>

namespace pni {
namespace nx {
namespace h5 {

extern "C" herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data);

using namespace pni::utils;

//! HDF5 error record

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

	H5Error &operator=(const H5Error &e);

	hid_t getClassId() const;
	void setClassId(hid_t id);

	hid_t getMajorNumber() const;
	void setMajorNumber(hid_t v);

	hid_t getMinorNumber() const;
	void setMinorNumber(hid_t v);

	String getFileName() const;
	void setFileName(const String &n);

	String getFuncName() const;
	void setFuncName(const String &n);

	String getDescription() const;
	void setDescription(const String &n);
	String getMajorMessage() const;
	String getMinorMessage() const;

	friend std::ostream &operator<<(std::ostream &o,const H5Error &e);
};

//! HDF5 error stack

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


	ssize_t getNumberOfErrors() const{
		return _errors.size();
	}

	void getStack();

	void appendError(const H5Error &e);

	friend std::ostream &operator<<(std::ostream &o,const H5ErrorStack &s);
	friend herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data);
};


//end of namespace
}
}
}

#endif /* H5ERRORSTACK_HPP_ */
