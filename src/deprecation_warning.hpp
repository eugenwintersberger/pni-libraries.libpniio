/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jul 22, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#pragma once

#include <boost/current_function.hpp>

#define REMOVE_FUNCTION(sig)\
    std::cerr<<"Function "<<sig<<" is deprecated and will be removed";\
    std::cerr<<" in a future release!"<<std::endl

#define REPLACE_FUNCTION(oldsig,newsig)\
    REMOVE_FUNCTION(oldsig);\
    std::cerr<<"Use "<<newsig<<" instread!"<<sdt::endl;


