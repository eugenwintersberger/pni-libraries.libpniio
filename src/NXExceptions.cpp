/*
 * Implementation of Nexus specific exceptions
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of Nexus specific exceptions
 *
 * Created on: Aug 5, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
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

