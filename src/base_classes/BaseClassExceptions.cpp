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
 * Created on: Sep 23, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "BaseClassExceptions.hpp"

namespace pni {
namespace nx {

std::ostream &operator<<(std::ostream &o,const NXrootError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NXentryError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NXinstrumentError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NXdetectorError &e){
	return e.print(o);
}

std::ostream &operator<<(std::ostream &o,const NXnoteError &e){
	return e.print(o);
}

} /* namespace nx */
} /* namespace pni */
