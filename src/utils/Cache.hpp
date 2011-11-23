/*
 * Cache.hpp
 *
 *  Created on: Nov 23, 2011
 *      Author: Eugen Wintersberger
 */

#ifndef CACHE_HPP_
#define CACHE_HPP_

namespace pni {
namespace nx {

class Cache {
private:
	void *_object_address;
public:
	Cache();
	virtual ~Cache();

	//! set a new object to the cache
	virtual set(const void *ptr){
		_object_address = ptr;
	}

	//! reset the cache
	virtual reset(){
		_object_address = nullptr;
	}

	//! true if the object is in the cache
	virtual bool is_chached(const void *ptr){
		if(_object_address == ptr) return true;
		return false;
	}

};

} /* namespace nx */
} /* namespace pni */
#endif /* CACHE_HPP_ */
