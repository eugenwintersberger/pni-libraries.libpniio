/*
 * H5DeflateFilter.hpp
 *
 *  Created on: Aug 10, 2011
 *      Author: eugen
 */

#ifndef H5DEFLATEFILTER_HPP_
#define H5DEFLATEFILTER_HPP_

#include "H5Filter.hpp"

namespace pni {
namespace nx {
namespace h5 {

class H5DeflateFilter:public H5Filter {
private:
	UInt32 _comp_rate;
public:
	H5DeflateFilter();
	H5DeflateFilter(const H5DeflateFilter &);
	virtual ~H5DeflateFilter();

	H5DeflateFilter &operator=(const H5DeflateFilter &o);

	virtual void setup(hid_t id);

	virtual UInt32 getCompressionRate() const;
	virtual void setCompressionRate(UInt32 r);


};


//end of namespace
}
}
}

#endif /* H5DEFLATEFILTER_HPP_ */
