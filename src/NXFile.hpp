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
	virtual pni::utils::String getFileName() const;

	//! returns true if the file is in read only mode
	virtual bool isReadOnly() const;
	//! set file to read only
	virtual void setReadOnly();
	//! set file to append mode (write access)
	virtual void unsetReadOnly();

	//! return true if existing file will be overwritten
	virtual bool isOverrite() const;
	//! set file to overwrite mode
	virtual void setOverwrite();
	//! unset file from overwrite
	virtual void unsetOverwrite();

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

	virtual void flush();


};

template<typename Imp> NXFile<Imp>::NXFile():NXGroup<Imp>() {
	_read_only = true;
	_overwrite = false;

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

template<typename Imp> void NXFile<Imp>::setReadOnly(){
	_read_only = true;
}

template<typename Imp> void NXFile<Imp>::unsetReadOnly(){
	_read_only = false;
}

template<typename Imp> bool NXFile<Imp>::isOverrite() const{
	return _overwrite;
}

template<typename Imp> void NXFile<Imp>::setOverwrite(){
	_overwrite = true;
}

template<typename Imp> void NXFile<Imp>::unsetOverwrite(){
	_overwrite = false;
}

template<typename Imp> void NXFile<Imp>::setSplitSize(UInt64 ssize){
	_split_size = ssize;
}

template<typename Imp>  UInt64 NXFile<Imp>::getSplitSize() const{
	return _split_size;
}

//create a new Nexus file
template<typename Imp> void NXFile<Imp>::create(){
	this->_imp.create(_fname.c_str(),_overwrite);
}
	//! open an NeXus file

template<typename Imp> void NXFile<Imp>::open(){
	this->_imp.open(_fname.c_str(),_read_only);
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
