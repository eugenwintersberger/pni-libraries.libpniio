/*
 * NXFile.hpp
 *
 *  Created on: Jun 30, 2011
 *      Author: eugen
 */

#include <boost/shared_ptr.hpp>
#include <pni/utils/PNITypes.hpp>


#ifndef NXFILE_HPP_
#define NXFILE_HPP_

#include "NXObject.hpp"
#include "NXGroup.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{

//!

template<typename Imp>
class NXFile:public NXGroup<Imp> {
private:
	//Imp _imp; //implementation of the object
	// a file object cannot be copied
	NXFile(const NXFile &o){}
	// nor can it be assigned
	NXFile &operator=(const NXFile &){return *this;}
	void _set_nexus_attributes();
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

	//! set the name of the file
	virtual void setFileName(const String &n);
	//! get the name of the file
	virtual String getFileName() const;

	//! returns true if the file is in read only mode
	virtual bool isReadOnly() const;
	//! set file to read only
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
	virtual void flush();

	//===================Nexus specific functions==============================
	void createNXentry(const String n);
	void openNXentry(const String n);

};

template<typename Imp> NXFile<Imp>::NXFile():NXGroup<Imp>() {
	_read_only = true;
	_overwrite = false;
	_split_size = 0;

}

template<typename Imp> NXFile<Imp>::~NXFile() {
	this->_imp.close();
}

template<typename Imp> void NXFile<Imp>::setFileName(const String &n){
	_fname = n;
}

template<typename Imp> String NXFile<Imp>::getFileName() const{
	return _fname;
}

template<typename Imp> bool NXFile<Imp>::isReadOnly() const{
	return _read_only;
}

template<typename Imp> void NXFile<Imp>::setReadOnly(bool v){
	_read_only = v;
}


template<typename Imp> bool NXFile<Imp>::isOverwrite() const{
	return _overwrite;
}

template<typename Imp> void NXFile<Imp>::setOverwrite(bool v){
	_overwrite = v;
}


template<typename Imp> void NXFile<Imp>::setSplitSize(UInt64 ssize){
	_split_size = ssize;
}

template<typename Imp>  UInt64 NXFile<Imp>::getSplitSize() const{
	return _split_size;
}

//create a new Nexus file
template<typename Imp> void NXFile<Imp>::create(){
	this->_imp.create(_fname.c_str(),_overwrite,_split_size);

	//set the proper attributes after file creation

}
	//! open an NeXus file

template<typename Imp> void NXFile<Imp>::open(){
	this->_imp.open(_fname.c_str(),_read_only);

	if(!_read_only){
		//if the file was not opened read only update the time stamp
	}
}

template<typename Imp> void NXFile<Imp>::close(){
	this->_imp.close();
}


template<typename Imp> void NXFile<Imp>::flush(){
	this->_imp.flush();
}

//end of namespace
}
}

#endif /* NXFILE_HPP_ */
