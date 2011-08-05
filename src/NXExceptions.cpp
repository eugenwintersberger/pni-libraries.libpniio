/*
 * NXExceptions.cpp
 *
 *  Created on: Aug 5, 2011
 *      Author: Eugen Wintersberger
 */

#include "NXExceptions.hpp"

namespace pni{
namespace nx{

NXFieldError::NXFieldError():Exception("NXFieldError"){
}

NXFieldError::NXFieldError(const String &i,const String &d)
		     :Exception("NXFieldError",i,d){
}

NXFieldError::~NXFieldError(){
}

std::ostream &operator<<(std::ostream &o,const NXFieldError &e){
	return e.print(o);
}

NXAttributeError::NXAttributeError():Exception("NXAttributeError"){
}

NXAttributeError::NXAttributeError(const String &i,const String &d)
                 :Exception("NXAttributeError",i,d){
}

NXAttributeError::~NXAttributeError(){
}

std::ostream &operator<<(std::ostream &o,const NXAttributeError &e){
	return e.print(o);
}

NXGroupError::NXGroupError():Exception("NXGroupError"){
}

NXGroupError::NXGroupError(const String &i,const String &d)
			 :Exception("NXGroupError",i,d){
}

NXGroupError::~NXGroupError(){
}

std::ostream &operator<<(std::ostream &o,const NXGroupError &e){
	return e.print(o);
}

//end of namespace
}
}

