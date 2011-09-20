/*
 * H5Exceptions.hpp
 *
 *  Created on: Jul 6, 2011
 *      Author: eugen
 */

#ifndef H5EXCEPTIONS_HPP_
#define H5EXCEPTIONS_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/Exceptions.hpp>
extern "C"{
#include <hdf5.h>
}

#include "H5ErrorStack.hpp"


namespace pni{
namespace nx{
namespace h5{

using namespace pni::utils;

class H5Exception:public Exception{
protected:
	H5ErrorStack _h5estack;
	std::ostream &print(std::ostream &) const;
public:
	H5Exception();
	H5Exception(const String &n);
	H5Exception(const String &n,const String &i,const String &d);
	H5Exception(const H5Exception &e);
	virtual ~H5Exception();

	friend std::ostream &operator<<(std::ostream &o,const H5Exception &e);

};

class H5DataTypeError:public H5Exception{
public:
	H5DataTypeError();
	H5DataTypeError(const String &i,const String &d);
	virtual ~H5DataTypeError();

	friend std::ostream &operator<<(std::ostream &o,const H5DataTypeError &e);
};

class H5DataSetError:public H5Exception{
public:
	H5DataSetError();
	H5DataSetError(const String &i,const String &d);
	virtual ~H5DataSetError();

	friend std::ostream &operator<<(std::ostream &o,const H5DataSetError &e);
};

class H5DataSpaceError:public H5Exception{
public:
	H5DataSpaceError();
	H5DataSpaceError(const String &i,const String &d);
	virtual ~H5DataSpaceError();

	friend std::ostream &operator<<(std::ostream &o,const H5DataSpaceError &e);
};

class H5AttributeError:public H5Exception{
public:
	H5AttributeError();
	H5AttributeError(const String &i,const String &d);
	virtual ~H5AttributeError();

	friend std::ostream &operator<<(std::ostream &o,const H5AttributeError &e);
};

class H5FileError:public H5Exception{
public:
	H5FileError();
	H5FileError(const String &i,const String &d);
	virtual ~H5FileError();

	friend std::ostream &operator<<(std::ostream &o,const H5FileError &e);
};

class H5GroupError:public H5Exception{
public:
	H5GroupError();
	H5GroupError(const String &i,const String &d);
	virtual ~H5GroupError();

	friend std::ostream &operator<<(std::ostream &o,const H5GroupError &e);
};

class H5PropertyListError:public H5Exception{
public:
	H5PropertyListError();
	H5PropertyListError(const String &i,const String &d);
	virtual ~H5PropertyListError();

	friend std::ostream &operator<<(std::ostream &o,const H5PropertyListError &e);
};

class H5FilterError:public H5Exception{
public:
	H5FilterError();
	H5FilterError(const String &i,const String &d);
	virtual ~H5FilterError();

	friend std::ostream &operator<<(std::ostream &o,const H5FilterError &e);
};

class H5ObjectError:public H5Exception{
public:
	H5ObjectError():H5Exception("H5ObjectError"){

	}
	H5ObjectError(const String &i,const String &d):H5Exception("H5ObjectError",i,d){

	}

	virtual ~H5ObjectError(){

	}

	friend std::ostream &operator<<(std::ostream &o,const H5ObjectError &e);
};

class H5LinkError:public H5Exception{
public:
	H5LinkError():H5Exception("H5LinkError"){

	}
	H5LinkError(const String &i,const String &d):H5Exception("H5LinkError",i,d){

	}

	virtual ~H5LinkError(){

	}

	friend std::ostream &operator<<(std::ostream &o,const H5LinkError &e);
};


//end of namespace
}
}
}


#endif /* H5EXCEPTIONS_HPP_ */
