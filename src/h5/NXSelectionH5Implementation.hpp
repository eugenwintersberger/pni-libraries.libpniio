/*
 * NXSelectionH5Implementation.hpp
 *
 *  Created on: Sep 21, 2011
 *      Author: eugen
 */

#ifndef NXSELECTIONH5IMPLEMENTATION_HPP_
#define NXSELECTIONH5IMPLEMENTATION_HPP_

#include<pni/utils/PNITypes.hpp>
#include<pni/utils/ArrayShape.hpp>

using namespace pni::utils;

namespace pni {
namespace nx {
namespace h5 {

class NXSelectionH5Implementation {
private:
	hsize_t *_offset;  //!< offset buffer
	hsize_t *_stride;  //!< stride buffer
	hsize_t *_count;   //!< count buffer
	hsize_t *_block;   //!< block buffer
	UInt32 _drank;     //!< rank of the data on disk
	UInt32 _mrank;     //!< rank of the data in memory

	void _compute_mem_rank();
	void _allocate_buffers(UInt32 n);
	void _free_buffers();
public:
	NXSelectionH5Implementation();
	NXSelectionH5Implementation(const NXSelectionH5Implementation &s);
	NXSelectionH5Implementation(const UInt32 &i);
	virtual ~NXSelectionH5Implementation();

	NXSelectionH5Implementation &operator=(const NXSelectionH5Implementation &s);

	virtual UInt32 getDiskRank() const;
	virtual void setDiskRank(const UInt32 &i);

	virtual UInt32 getMemRank() const;
	virtual ArrayShape getMemShape() const;

	virtual const hsize_t *getOffset() const;
	virtual hsize_t getOffset(const UInt32 &i) const;
	virtual void setOffset(const UInt32 &i,const UInt32 &v);
	virtual void incOffset(const UInt32 &i);
	virtual void decOffset(const UInt32 &i);

	virtual const hsize_t *getCount() const;
	virtual hsize_t getCount(const UInt32 &i) const;
	virtual void setCount(const UInt32 i,const UInt32 &v);

	virtual const hsize_t *getStride() const;
	virtual hsize_t getStride(const UInt32 &i) const;
	virtual void setStride(const UInt32 &i,const UInt32 &v);


	virtual const hsize_t *getBlock() const;
	virtual hsize_t getBlock(const UInt32 &i) const;
	virtual void setBlock(const UInt32 &i,const UInt32 &v);

	virtual hid_t getMemSpace() const;
};

} /* namespace h5 */
} /* namespace nx */
} /* namespace pni */
#endif /* NXSELECTIONH5IMPLEMENTATION_HPP_ */
