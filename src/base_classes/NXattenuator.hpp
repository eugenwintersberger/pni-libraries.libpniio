/*
 * Declaration of Nexus base class NXattenuator template.
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
 * Declaration of Nexus base class NXattenuator template
 *
 * Created on: Oct 17, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXATTENUATOR_HPP_
#define NXATTENUATOR_HPP_

#include<iostream>
#include<vector>
#include<map>

#include <pni/utils/PNITypes.hpp>
#include "../NXField.hpp"
#include "NXFieldRestriction.hpp"
#include "NXStandardGroup.hpp"

namespace pni{
namespace nx{


enum class AttenuatorStatus{
	in,out,moving;
};


template<typename Base> class NXattenuator:public Base{
public:

	NXattenuator():Base(){
		Base::_standard_fields.insert("distance");
		Base::_standard_fields.insert("thickness");
		Base::_standard_fields.insert("scattering_cross_section");
		Base::_standard_fields.insert("absorption_cross_section");
		Base::_standard_fields.insert("attenuator_transmission");
		Base::_standard_fields.insert("status");
	}

	virtual ~NXattenuator(){}


};



//end of namespace
}
}



#endif /* NXATTENUATOR_HPP_ */
