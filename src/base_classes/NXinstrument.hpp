/*
 * Declaration of Nexus base class NXinstrument template
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
 * Declaration of Nexus base class NXinstrument template
 *
 * Created on: Sep 23, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXINSTRUMENT_HPP_
#define NXINSTRUMENT_HPP_

#include "NXGroup.hpp"


namespace pni{
namespace nx{

template<typename Imp>
class NXinstrument:public NXGroup<Imp>{
public:
	NXinstrument():NXGroup<Imp>(){}
	NXinstrument(const NXInstrument &o):NXGroup<Imp>(o){}
	virtual ~NXinstrument(){}

	NXinstrument &operator=(const NXinstrument &o){
		if(this != &o){
			(NXGroup<Imp> &)(*this) = (NXGroup<Imp> &)o;
		}

		return *this;
	}


};

//end of namespace
}
}



#endif /* NXINSTRUMENT_HPP_ */
