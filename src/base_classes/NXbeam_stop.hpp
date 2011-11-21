/*
 * Declaration of Nexus base class NXbeam_stop template
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
 * Declaration of Nexus base class NXbeam_stop template
 *
 * Created on: Oct 17, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXBEAM_STOP_HPP_
#define NXBEAM_STOP_HPP_

namespace pni{
namespace nx{

template<typename Base> class NXbeam_stop:private Base{
public:
	NXbeam_stop():Base(){}
	virtual ~NXbeam_stop(){}
};

//end of namespace
}
}


#endif /* NXBEAM_STOP_HPP_ */
