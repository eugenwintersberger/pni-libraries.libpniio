/*
 * Declaration of the NXFile template
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
 *
 * Declaration of the NXFile template
 *
 * Created on: Jun 30, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include <boost/shared_ptr.hpp>
#include <pni/utils/PNITypes.hpp>


#ifndef NXFILE_HPP_
#define NXFILE_HPP_

#include "NXObject.hpp"
#include "NXGroup.hpp"
#include "NXDateTime.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

//! \ingroup Low level objects
//! \brief File object

//! NXFile represents a file for reading and writing data too. It is
//!
template<typename Imp>
class NXFile:public NXGroup<Imp> {
private:
	// a file object can neither be copied
	NXFile(const NXFile &o){}
	// nor can it be assigned
	NXFile &operator=(const NXFile &){return *this;}
protected:
	bool _read_only;    //!< open the file in read only mode (default is appending)
	bool _overwrite;    //!< create a new file even if one with the same name already exists
	UInt64 _split_size; //!< size of a file for splitting
	String _fname;      //!< name of the file
public:
	typedef boost::shared_ptr<NXFile > sptr; //! shared pointer to a file object
	//! default constructor
	NXFile();
	virtual ~NXFile();

	//! set filename

	//! Set the  name of the file object.
	//! \param n name of the file
	virtual void setFileName(const String &n);
	//! get filename

	//! Get the name of the file object.
	//! \return filename as String
	virtual String getFileName() const;

	//! get read/write state

	//! Returns the read/write state of the file.
	//! \return true of in read-only mode, false otherwise
	virtual bool isReadOnly() const;
	//! set read/write state

	//! SEt the
	virtual void setReadOnly(bool v);

	//! return true if existing file will be overwritten
	virtual bool isOverwrite() const;
	//! set file to overwrite mode
	virtual void setOverwrite(bool v);

	//! set the split size
	virtual void setSplitSize(UInt64 ssize);
	//! get the split size
	virtual UInt64 getSplitSize() const;

	//! create a new file

	//! Creates a new NeXus file and raises an exception if
	//! the file already exists.
	virtual void create();
	//! open an NeXus file

	//! Opens an already existing nexus file
	virtual void open();
	//! closes the file
	virtual void close();
	//! flush the file
	virtual void flush() const;

};

//-----------------------------------------------------------------------------
template<typename Imp> NXFile<Imp>::NXFile():NXGroup<Imp>() {
	_read_only = true;
	_overwrite = false;
	_split_size = 0;

}

//-----------------------------------------------------------------------------
template<typename Imp> NXFile<Imp>::~NXFile() {
	//we need this construction here for cases where the user allready
	//called close before the file object goes out of scope.
	//In this case close would raise an exception because it tries to
	//write the file_update_time attribute to a closed HDF5 object.
	try{
		this->close();
	}catch(...){

	}
}

//-----------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::setFileName(const String &n){
	_fname = n;
}

//-----------------------------------------------------------------------------
template<typename Imp> String NXFile<Imp>::getFileName() const{
	return _fname;
}

//-----------------------------------------------------------------------------
template<typename Imp> bool NXFile<Imp>::isReadOnly() const{
	return _read_only;
}

//-----------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::setReadOnly(bool v){
	_read_only = v;
}

//-----------------------------------------------------------------------------
template<typename Imp> bool NXFile<Imp>::isOverwrite() const{
	return _overwrite;
}

//-----------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::setOverwrite(bool v){
	_overwrite = v;
}

//-----------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::setSplitSize(UInt64 ssize){
	_split_size = ssize;
}

//-----------------------------------------------------------------------------
template<typename Imp>  UInt64 NXFile<Imp>::getSplitSize() const{
	return _split_size;
}

//-----------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::create(){
	this->getImplementation().create(_fname.c_str(),_overwrite,_split_size);

	//set here nexus specific attributes
	this->setAttribute("NX_class","NXroot");
	this->setAttribute("NXfile_name",getFileName());
	this->setAttribute("NeXus_version","2.4.3"); //should not be hardcoded
	this->setAttribute("creator","DESY");   //should not be hardcoded


	this->setAttribute("file_time",NXDateTime::getDateTimeStr());
	this->setAttribute("file_update_time",NXDateTime::getDateTimeStr());



}

//------------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::open(){
	this->getImplementation().open(_fname.c_str(),_read_only);


}

//------------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::close(){
	//set last modification time stamp
	if(!isReadOnly()) this->setAttribute("file_update_time",NXDateTime::getDateTimeStr());

	this->getImplementation().close();
}

//------------------------------------------------------------------------------
template<typename Imp> void NXFile<Imp>::flush() const{
	this->getImplementation().flush();
}

//end of namespace
}
}

#endif /* NXFILE_HPP_ */
