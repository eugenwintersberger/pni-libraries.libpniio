/*
 * H5ErrorStack.hpp
 *
 *  Created on: Jul 28, 2011
 *      Author: eugen
 */

#ifndef H5ERRORSTACK_HPP_
#define H5ERRORSTACK_HPP_

extern "C"{
#include <hdf5.h>
}

#include <iostream>
#include <vector>

#include <pni/utils/PNITypes.hpp>

namespace pni {
namespace nx {
namespace h5 {

extern "C" herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data);

using namespace pni::utils;

#define H5ERROR_MESSAGE_MAX_BUFFER 1024

class H5ErrorStack {
private:
	hid_t _stack_id;
	ssize_t _num_errors;
	std::vector<String> _minor_messages;
	std::vector<String> _major_messages;

public:
	H5ErrorStack();
	virtual ~H5ErrorStack();

	friend std::ostream &operator<<(std::ostream &o,const H5ErrorStack &s);
	friend herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data);
};


//end of namespace
}
}
}

#endif /* H5ERRORSTACK_HPP_ */
