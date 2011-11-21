/*
 * NXSelectionH5Implementation.cpp
 *
 *  Created on: Sep 21, 2011
 *      Author: eugen
 */

#include "H5Exceptions.hpp"
#include "NXSelectionH5Implementation.hpp"
#include "H5Utilities.hpp"

namespace pni {
namespace nx {
namespace h5 {

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::_allocate_buffers(UInt32 n){
	EXCEPTION_SETUP("void NXSelectionH5Implementation::_allocate_buffers(UInt32 n)");
	_free_buffers();

	_offset = new hsize_t[n];
	if(_offset == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for offset buffer!");
		EXCEPTION_THROW();
	}

	_stride = new hsize_t[n];
	if(_stride == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for stride buffer!");
		EXCEPTION_THROW();
	}

	_count = new hsize_t[n];
	if(_count == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for count buffer!");
		EXCEPTION_THROW();
	}

	_block = new hsize_t[n];
	if(_block == NULL){
		EXCEPTION_INIT(MemoryAllocationError,"Cannot allocate memory for block buffer!");
		EXCEPTION_THROW();
	}

}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::_free_buffers(){
	if(_offset != NULL) delete [] _offset;
	if(_stride != NULL) delete [] _stride;
	if(_count != NULL) delete [] _count;
	if(_block != NULL) delete [] _block;

	_offset = NULL;
	_stride = NULL;
	_count = NULL;
	_block = NULL;
}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::_compute_mem_rank(){
	//determine the rank of the data in memory according to the selection
	_mrank = 0;
	for(UInt32 i=0;i<getDiskRank();i++){
		if(getCount(i) != 1) _mrank++;
	}
}

//------------------------------------------------------------------------------
NXSelectionH5Implementation::NXSelectionH5Implementation() {
	_offset = NULL;
	_stride = NULL;
	_count = NULL;
	_block = NULL;
	_drank = 0;

}

//------------------------------------------------------------------------------
NXSelectionH5Implementation::NXSelectionH5Implementation(const NXSelectionH5Implementation &s){
	EXCEPTION_SETUP("NXSelectionH5Implementation::NXSelectionH5Implementation(const NXSelectionH5Implementation &s)");

	_drank = s.getDiskRank();
	_free_buffers();

	//allocate buffer memory if necessary
	if(_drank != 0) _allocate_buffers(_drank);
}

//------------------------------------------------------------------------------
NXSelectionH5Implementation::NXSelectionH5Implementation(const UInt32 &i){
	_allocate_buffers(i);
	_drank = i;
	_mrank = 0;
}

//------------------------------------------------------------------------------
NXSelectionH5Implementation::~NXSelectionH5Implementation() {
	_free_buffers();
}

//------------------------------------------------------------------------------
NXSelectionH5Implementation &NXSelectionH5Implementation::operator=(const NXSelectionH5Implementation &s){
	EXCEPTION_SETUP("NXSelectionH5Implementation &NXSelectionH5Implementation::operator=(const NXSelectionH5Implementation &s)");

	if(this != &s){
		//setting the source rank also sets the buffers
		setDiskRank(s.getDiskRank());

		//copy data if necessary
		if(getDiskRank() != 0){
			for(UInt32 i=0;i<getDiskRank();i++){
				setOffset(i,s.getOffset(i));
				setStride(i,s.getStride(i));
				setCount(i,s.getCount(i));
				setBlock(i,s.getBlock(i));
			}
		}
		_compute_mem_rank();
	}

	return *this;
}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::setDiskRank(const UInt32 &i){
	EXCEPTION_SETUP("void NXSelectionH5Implementation::setSourceRank(const UInt32 &i)");
	_drank = i;
	_free_buffers();

	//allocate buffer if necessary
	if(_drank != 0) _allocate_buffers(_drank);
	_compute_mem_rank();
}

//------------------------------------------------------------------------------
UInt32 NXSelectionH5Implementation::getDiskRank() const {
	return _drank;
}

//------------------------------------------------------------------------------
UInt32 NXSelectionH5Implementation::getMemRank() const {
	return _mrank;
}

//------------------------------------------------------------------------------
ArrayShape NXSelectionH5Implementation::getMemShape() const{
	ArrayShape s(getMemRank());

	if(s.getRank()!=0){
		for(UInt32 i=0,r=0;i<getDiskRank();i++){
			if(getCount(i) != 1){
				s.setDimension(r,getCount(i));
				r++;
			}
		}
	}

	return s;
}



//------------------------------------------------------------------------------
UInt32 NXSelectionH5Implementation::getOffset(const UInt32 &i) const{
	EXCEPTION_SETUP("hsize_t NXSelectionH5Implementation::getOffset(const UInt32 &i) const");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Offset index is out of bounds!");
		EXCEPTION_THROW();
	}

	return (UInt32)_offset[i];
}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::setOffset(const UInt32 &i,const UInt32 &v){
	EXCEPTION_SETUP("NXSelectionH5Implementation::setOffset(const UInt32 &i,const UInt32 &v)");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Offset index is out of bounds!");
		EXCEPTION_THROW();
	}

	_offset[i] = v;
}

//-----------------------------------------------------------------------------
void NXSelectionH5Implementation::incOffset(const UInt32 &i){
	_offset[i]++;
}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::decOffset(const UInt32 &i){
	_offset[i]--;
}

//------------------------------------------------------------------------------
UInt32 NXSelectionH5Implementation::getCount(const UInt32 &i) const{
	EXCEPTION_SETUP("hsize_t NXSelectionH5Implementation::getCount(const UInt32 &i) const");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Count index is out of bounds!");
		EXCEPTION_THROW();
	}

	return (UInt32)_count[i];
}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::setCount(const UInt32 i,const UInt32 &v){
	EXCEPTION_SETUP("void NXSelectionH5Implementation::setCount(const UInt32 i,const UInt32 &v)");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Count index is out of bounds!");
		EXCEPTION_THROW();
	}

	_count[i] = v;
	_compute_mem_rank();
}

//------------------------------------------------------------------------------
UInt32 NXSelectionH5Implementation::getStride(const UInt32 &i) const{
	EXCEPTION_SETUP("hsize_t NXSelectionH5Implementation::getStride(const UInt32 &i) const");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Stride index is out of bounds!");
		EXCEPTION_THROW();
	}

	return (UInt32)_stride[i];
}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::setStride(const UInt32 &i,const UInt32 &v){
	EXCEPTION_SETUP("void NXSelectionH5Implementation::setStride(const UInt32 &i,const UInt32 &v)");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Stride index is out of bounds!");
		EXCEPTION_THROW();
	}

	_stride[i] = v;
}

//-----------------------------------------------------------------------------
UInt32 NXSelectionH5Implementation::getBlock(const UInt32 &i) const{
	EXCEPTION_SETUP("hsize_t NXSelectionH5Implementation::getBlock(const UInt32 &i) const");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Block index is out of bounds!");
		EXCEPTION_THROW();
	}

	return (UInt32)_block[i];
}

//------------------------------------------------------------------------------
void NXSelectionH5Implementation::setBlock(const UInt32 &i,const UInt32 &v){
	EXCEPTION_SETUP("void NXSelectionH5Implementation::setBlock(const UInt32 &i,const UInt32 &v)");

	if(i>=_drank){
		EXCEPTION_INIT(IndexError,"Block index is out of bounds!");
		EXCEPTION_THROW();
	}

	_block[i] = v;
}


} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */
