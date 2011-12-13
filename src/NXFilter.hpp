/*
 * Declaration of the basic NXFilter template
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
 * Declaration of the NXFilter template
 *
 * Created on: Aug 8, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXFILTER_HPP_
#define NXFILTER_HPP_

#include <pni/utils/Types.hpp>

#include "NXObject.hpp"

using namespace pni::utils;

namespace pni{
namespace nx{


template<typename Filter>
class NXFilter:public Filter{
public:
	NXFilter();
	NXFilter(const NXFilter<Filter> &f);
	virtual ~NXFilter();

	NXFilter<Filter> &operator=(const NXFilter<Filter> &f);

	const Shape &getChunkShape() const;
	void setChunkShape(const Shape &s);
};

template<typename Filter> NXFilter<Filter>::NXFilter():Filter(){
}

template<typename Filter> NXFilter<Filter>::NXFilter(const NXFilter<Filter> &o){
	Filter::Filter(o);
}

template<typename Filter> NXFilter<Filter>::~NXFilter(){

}

template<typename Filter>
NXFilter<Filter> &NXFilter<Filter>::operator=(const NXFilter<Filter> &f){
	if ( this != &f){

	}

	return *this;
}




//end of namespace
}
}


#endif /* NXFILTER_HPP_ */
