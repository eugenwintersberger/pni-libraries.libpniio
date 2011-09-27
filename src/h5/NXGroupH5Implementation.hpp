/*
 * NXGroupH5Implementation.hpp
 *
 *  Created on: Jul 1, 2011
 *      Author: eugen
 */

#ifndef NXGROUPH5IMPLEMENTATION_HPP_
#define NXGROUPH5IMPLEMENTATION_HPP_

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayShape.hpp>
#include <pni/utils/Exceptions.hpp>

#include "NXObjectH5Implementation.hpp"
#include "NXFieldH5Implementation.hpp"
#include "H5Exceptions.hpp"
#include "../NXFilter.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{
namespace h5{


class NXGroupH5Implementation:public NXObjectH5Implementation {
private:
	//! copy constructor
	NXGroupH5Implementation(const NXGroupH5Implementation &o){}
protected:
	virtual void create(const String &n,const NXObjectH5Implementation &o);
public:
	typedef boost::shared_ptr<NXGroupH5Implementation> sptr;
	//! default constructor
	NXGroupH5Implementation();

	//! default destructor
	virtual ~NXGroupH5Implementation();

	//! assignment operator
	NXGroupH5Implementation &operator=(const NXGroupH5Implementation &o);

	//! create a new group below this group
	virtual void createGroup(const char *n, NXGroupH5Implementation &imp);
	//! open a new group belonging to this group
	virtual void openGroup(const char *n, NXGroupH5Implementation &imp);
	//! create a field

	//! create a field
	void createField(const char *n, PNITypeID tid, UInt32 rank,
			         const UInt32 *dims, NXFieldH5Implementation &imp);
	template<typename Filter>
	void createField(const char *n, PNITypeID tid, UInt32 rank,
				     const UInt32 *dims, NXFieldH5Implementation &imp,
				     pni::nx::NXFilter<Filter> &f);
	//! method to create a field for a single scalar value
	void createField(const char *n,PNITypeID,NXFieldH5Implementation &imp);
	//! create a field to store string data
	void createField(const char *n,UInt64 size,NXFieldH5Implementation &imp);
	//! open an existing field
	virtual void openField(const char *n,NXFieldH5Implementation &imp);

	virtual void remove(const String &n);
	virtual bool exists(const String &n) const;

};

template<typename Filter>
void NXGroupH5Implementation::createField(const char *n, PNITypeID tid,
		                                  UInt32 rank, const UInt32 *dims,
			                              NXFieldH5Implementation &imp,
			                              pni::nx::NXFilter<Filter> &f){
	EXCEPTION_SETUP("void NXGroupH5Implementation::createField(const char *n, "
			        "PNITypeID tid,UInt32 rank, const UInt32 *dims,"
			        "NXFieldH5Implementation &imp)");

	UInt32 *cdims = NULL;
	UInt32 crank = rank;
	cdims = new UInt32[crank];
	cdims[0] = 1;
	for(UInt32 i=1;i<crank;i++) cdims[i] = dims[i];

	try{
		imp.setDataSpace(rank,dims);
		imp.setDataType(tid);
		imp.setChunkedLayout();
		imp.setChunkSize(crank,cdims);
		imp.setShuffle();
		imp.setFilter(f);
		imp.create(String(n),*this);
	}catch(...){
		EXCEPTION_INIT(H5DataSetError,"Error creating array data-set ["+String(n)+"]");
		EXCEPTION_THROW();
	}

	delete [] cdims;
}



//end of namespace
}
}
}


#endif /* NXGROUPH5IMPLEMENTATION_HPP_ */
