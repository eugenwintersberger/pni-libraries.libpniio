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
 * H5Exceptions.hpp
 *
 *  Created on: Jul 6, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef H5EXCEPTIONS_HPP_
#define H5EXCEPTIONS_HPP_

#include <pni/utils/Types.hpp>
#include <pni/utils/Exceptions.hpp>
extern "C"{
#include <hdf5.h>
}

#include "H5ErrorStack.hpp"


namespace pni{
namespace nx{
namespace h5{

using namespace pni::utils;
//! \ingroup HDF5-Implementation

//! \brief HDF5 exceptions base class

//! Base class for all HDF5 related exceptions. The class is a descendant
//! of the Exception class declared in libpniutils and adds managment for the
//! HDF5 error stack (H5ErrorStack).
class H5Exception:public Exception{
protected:
	H5ErrorStack _h5estack;  //!< HDF5 error stack
	std::ostream &print(std::ostream &) const; //!< print method
public:
	//! default constructor
	H5Exception();
	//! constructor

	//! \param n name of the exception
	H5Exception(const String &n);
	//! constructor

	//! \param n exception name
	//! \param i exception issuer
	//! \param d exception description
	H5Exception(const String &n,const String &i,const String &d);
	//! copy constructor
	H5Exception(const H5Exception &e);
	//! destructor
	virtual ~H5Exception();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5Exception &e);

};

//! \ingroup HDF5-Implementation

//! \brief data-type error

//! Exception is thrown in cases where errors concerning HDF5 data-type objects
//! are involved occur.
class H5DataTypeError:public H5Exception{
public:
	//! default constructor
	H5DataTypeError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d exception description
	H5DataTypeError(const String &i,const String &d);
	//! destructor
	virtual ~H5DataTypeError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5DataTypeError &e);
};

//! \ingroup HDF5-Implementation
//! \brief dataset error

//! Exception thrown in situations where errors concering an HDF5 data-set
//! occur.
class H5DataSetError:public H5Exception{
public:
	//! default constructor
	H5DataSetError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d exception description
	H5DataSetError(const String &i,const String &d);
	//! default destructor
	virtual ~H5DataSetError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5DataSetError &e);
};

//! \ingroup HDF5-Implementation
//! \brief data-space error

//! Exception thrown in error situations involving HDF5 data-spaces.
class H5DataSpaceError:public H5Exception{
public:
	//! default constructor
	H5DataSpaceError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the exception
	H5DataSpaceError(const String &i,const String &d);
	//! destructor
	virtual ~H5DataSpaceError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5DataSpaceError &e);
};

//! \ingroup HDF5-Implementation
//! \brief attribute error

//! Exception thrown in situations where errors occur involving HDF5 attributes.
class H5AttributeError:public H5Exception{
public:
	//! default constructor
	H5AttributeError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	H5AttributeError(const String &i,const String &d);
	//! destructor
	virtual ~H5AttributeError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5AttributeError &e);
};

//! \ingroup HDF5-Implementation
//! \brief file error

//! Exception thrown in situations where error occur involving HDF5 file objects.
class H5FileError:public H5Exception{
public:
	//! default constructor
	H5FileError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	H5FileError(const String &i,const String &d);
	//! destructor
	virtual ~H5FileError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5FileError &e);
};

//! \ingroup HDF5-Implementation
//! \brief group error

//! Exception thrown in situations where errors occur involving HDF5 group objects.
class H5GroupError:public H5Exception{
public:
	//! default constructor
	H5GroupError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	H5GroupError(const String &i,const String &d);
	//! destructor
	virtual ~H5GroupError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5GroupError &e);
};

//! \ingroup HDF5-Implementation
//! \brief property list error

//! Exception thrown in situations where errors occur involving HDF5 property
//! lists.
class H5PropertyListError:public H5Exception{
public:
	//! default constructor
	H5PropertyListError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	H5PropertyListError(const String &i,const String &d);
	//! destructor
	virtual ~H5PropertyListError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5PropertyListError &e);
};

//! \ingroup HDF5-Implementation
//! \brief filter error

//! Exception thrown for errors involving HDF5 filters.
class H5FilterError:public H5Exception{
public:
	//! default constructor
	H5FilterError();
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	H5FilterError(const String &i,const String &d);
	//! destructor
	virtual ~H5FilterError();

	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5FilterError &e);
};

//! \ingroup HDF5-Implementation
//! \brief object error

//! Exception thrown in all cases where HDF5 objects in general are involved.
class H5ObjectError:public H5Exception{
public:
	//! default constructor
	H5ObjectError():H5Exception("H5ObjectError"){

	}
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	H5ObjectError(const String &i,const String &d):H5Exception("H5ObjectError",i,d){

	}
	//! destructor
	virtual ~H5ObjectError(){

	}
	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5ObjectError &e);
};

//! \ingroup HDF5-Implementation
//! \brief link error

//! Exception thrown in all cases where errors occur during link creation.
class H5LinkError:public H5Exception{
public:
	//! default constructor
	H5LinkError():H5Exception("H5LinkError"){

	}
	//! constructor

	//! \param i signature of the exception issuer
	//! \param d description of the error
	H5LinkError(const String &i,const String &d):H5Exception("H5LinkError",i,d){

	}
	//! destructor
	virtual ~H5LinkError(){

	}
	//! output operator
	friend std::ostream &operator<<(std::ostream &o,const H5LinkError &e);
};


//end of namespace
}
}
}


#endif /* H5EXCEPTIONS_HPP_ */
