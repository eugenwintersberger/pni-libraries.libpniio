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
 * Class Reader is the base class for all readers which retrieve data from
 * files and other sources.
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */


#include <pni/io/image_reader.hpp>

namespace pni{
namespace io{

    //================implementation of constructors===========================
    //implementation of the default constructor
    image_reader::image_reader():data_reader() {}

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    image_reader::image_reader(image_reader &&i):
        data_reader(std::move(i))
    {}

    //-------------------------------------------------------------------------
    //implementation of the standard constructor
    image_reader::image_reader(const string &fname,bool binary):
        data_reader(fname,binary)
    {}

    //-------------------------------------------------------------------------
    //implementation of the destructor
    image_reader::~image_reader() {} 

    //===========implementation of assignment operators========================
    //implementation of move assignment
    image_reader &image_reader::operator=(image_reader &&i)
    {
        if(this == &i) return *this;

        data_reader::operator=(std::move(i));
        return *this;
    }

//end of namespace
}
}
