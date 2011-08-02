/*
 * H5ErrorStack.cpp
 *
 *  Created on: Jul 28, 2011
 *      Author: Eugen Wintersberger
 */

#include "H5ErrorStack.hpp"
#include <cstdio>
#include <cstdlib>

namespace pni {
namespace nx {
namespace h5 {


herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,void *client_data){
	H5ErrorStack *stack = (H5ErrorStack *)client_data;

	H5Error h5e;
	if(eptr->file_name!=NULL) h5e.setFileName(String(eptr->file_name));
	if(eptr->func_name!=NULL) h5e.setFuncName(String(eptr->func_name));
	if(eptr->desc != NULL) h5e.setDescription(String(eptr->desc));
	h5e.setMinorNumber(eptr->min_num);
	h5e.setMajorNumber(eptr->maj_num);
	h5e.setClassId(eptr->cls_id);
	stack->appendError(h5e);

	return 0;
}

H5ErrorStack::H5ErrorStack() {

}

void H5ErrorStack::getStack(){
	_stack_id = H5Eget_current_stack();
	H5Ewalk2(_stack_id,H5E_WALK_DOWNWARD,_error_walker,(void *)this);
}

H5ErrorStack::H5ErrorStack(const H5ErrorStack &s){
	_stack_id = s._stack_id;
	_errors = std::vector<H5Error>(s._errors);
}

H5ErrorStack &H5ErrorStack::operator=(const H5ErrorStack &s){
	if(this != &s){
		_stack_id = s._stack_id;
		_errors = std::vector<H5Error>(s._errors);
	}

	return *this;
}

H5ErrorStack::~H5ErrorStack() {
	_errors.clear();
	H5Eclear2(_stack_id);
	H5Eclose_stack(_stack_id);
}

void H5ErrorStack::appendError(const H5Error &e){
	_errors.push_back(e);
}


std::ostream &operator<<(std::ostream &o,const H5ErrorStack &s){
	std::vector<H5Error>::const_iterator iter;

	o<<"HDF5 Errors ("<<s.getNumberOfErrors()<<" error records):"<<std::endl;

	for(iter=s._errors.begin();iter!=s._errors.end();iter++){
		o<<*iter<<std::endl;
	}

	return o;
}

}

}

}
