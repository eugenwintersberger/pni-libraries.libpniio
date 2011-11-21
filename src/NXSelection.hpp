/*
 * Declaration of Nexus selection template
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
 * Declaration of Nexus selection template.
 *
 * Created on: Sep 21, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXSELECTION_HPP_
#define NXSELECTION_HPP_

#include<pni/utils/PNITypes.hpp>
#include<pni/utils/ArrayObject.hpp>

using namespace pni::utils;

namespace pni{
namespace nx{

//! \brief selection decorator for array fields
template<typename Imp> class NXSelection:public Imp{
public:
	NXSelection():Imp(){}
	virtual ~NXSelection(){}

};


}
}


#endif /* NXSELECTION_HPP_ */
