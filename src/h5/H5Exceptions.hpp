/*
 * H5Exceptions.hpp
 *
 *  Created on: Jul 6, 2011
 *      Author: eugen
 */

#ifndef H5EXCEPTIONS_HPP_
#define H5EXCEPTIONS_HPP_

#include <pni/utils/PNITypes.hpp>

namespace nx{
namespace h5{

using namespace pni::utils;

class H5Exception{
protected:
	String _name;
	String _issuer;
	String _description;
public:
	H5Exception();
	H5Exception(const String &n);
	H5Exception(const String &n,const String &i,const String &d);
	virtual ~H5Exception();

	virtual void setName(const String &n);
	virtual String getName() const;

	virtual void setIssuer(const String &i);
	virtual String getIssuer() const;

	virtual void setDescription(const String &d);
	virtual String getDescription() const;

	friend std::ostream &operator<<(std::ostream &o,const H5Exception &e);

};

class H5DataTypeException:public H5Exception{
public:
	H5DataTypeException();
	H5DataTypeException(const String &i,const String &d);
	virtual ~H5DataTypeException();

	friend std::ostream &operator<<(std::ostream &o,const H5DataTypeException &e);
};

class H5DataSetException:public H5Exception{
public:
	H5DataSetException();
	H5DataSetException(const String &i,const String &d);
	virtual ~H5DataSetException();

	friend std::ostream &operator<<(std::ostream &o,const H5DataSetException &e);
};

class H5DataSpaceException:public H5Exception{
public:
	H5DataSpaceException();
	H5DataSpaceException(const String &i,const String &d);
	virtual ~H5DataSpaceException();

	friend std::ostream &operator<<(std::ostream &o,const H5DataSpaceException &e);
};

class H5AttributeException:public H5Exception{
public:
	H5AttributeException();
	H5AttributeException(const String &i,const String &d);
	virtual ~H5AttributeException();

	friend std::ostream &operator<<(std::ostream &o,const H5AttributeException &e);
};

//end of namespace
}
}


#endif /* H5EXCEPTIONS_HPP_ */
