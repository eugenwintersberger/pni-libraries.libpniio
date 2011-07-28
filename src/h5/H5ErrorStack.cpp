/*
 * H5ErrorStack.cpp
 *
 *  Created on: Jul 28, 2011
 *      Author: eugen
 */

#include "H5ErrorStack.hpp"
#include <cstdio>
#include <cstdlib>

namespace pni {
namespace nx {
namespace h5 {

herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data){
	H5ErrorStack *stack = (H5ErrorStack *)client_data;


	std::cout<<n<<" "<<eptr->cls_id<<" "<<eptr->maj_num<<" "<<eptr->min_num<<std::endl;
	return 0;
}

H5ErrorStack::H5ErrorStack() {
	hid_t i;
	char *buffer;
	H5E_type_t msg_type;
	ssize_t bsize;

	_stack_id = H5Eget_current_stack();
	_num_errors = H5Eget_num(_stack_id);

	buffer = new char[H5ERROR_MESSAGE_MAX_BUFFER];

	H5Ewalk2(_stack_id,H5E_WALK_UPWARD,_error_walker,(void *)this);

	delete [] buffer;

}

H5ErrorStack::~H5ErrorStack() {
	// TODO Auto-generated destructor stub
}



std::ostream &operator<<(std::ostream &o,const H5ErrorStack &s){
	std::vector<String>::const_iterator iter;

	o<<"HDF5 Error ("<<s._num_errors<<" error messages):"<<std::endl;
	H5Eprint2(s._stack_id,stdout);
	//for(iter = s._major_messages.begin();iter != s._major_messages.end();iter++){
	//	o<<*iter<<std::endl;
	//}

	return o;
}

}

}

}
