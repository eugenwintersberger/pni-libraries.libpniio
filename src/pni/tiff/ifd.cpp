//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jun 16, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/tiff/ifd.hpp>
#include <pni/tiff/ifd_entry.hpp>

using namespace pni;


namespace pni{
namespace tiff{

    //================implementation of constructors and destructor============ 
    //implementation of the default constructor
    ifd::ifd():
        _entries(0)
    { }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    ifd::ifd(const ifd &ifd):
        _entries(ifd._entries)
    { }

    //-------------------------------------------------------------------------
    //implementation fo the move constructor
    ifd::ifd(ifd &&ifd):
        _entries(std::move(ifd._entries))
    {}

    //-------------------------------------------------------------------------
    //implementation of the standard constructor
    ifd::ifd(size_t size):
        _entries(size)
    { }

    //------------------------------------------------------------------------------
    //implementation of the destructor
    ifd::~ifd() 
    {
        _entries.clear();
    }

    //==============implementation of assignment operators=====================
    //implementation of copy assignment operator
    ifd &ifd::operator=(const ifd &o)
    {
        if(this != &o)
            _entries = o._entries;

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of the move assignment operator
    ifd &ifd::operator=(ifd &&o)
    {
        if(this != &o) _entries = std::move(o._entries);
        return *this;
    }

    //===============implementation of public member methods===================
    //implementation of the index access operator 
    ifd_entry ifd::operator[](const size_t i) const
    {
        return _entries[i];
    }

    //------------------------------------------------------------------------------
    ifd_entry ifd::operator[](const string &n) const
    {
        using namespace pni;
        for(auto entry: *this)
        {
            if(entry.name() == n) return entry;
        }

        throw key_error(EXCEPTION_RECORD,"IFD entry key ["+n+"] not found in IFD!");
    }

    //==================implementation of friend operators=====================
    std::ostream &operator<<(std::ostream &o,const ifd &image_dir)
    {
        o<<"IFD content ("<<image_dir.size()<<" entries):"<<std::endl;
        for(auto entry: image_dir)
        {
            o<<entry<<std::endl;
        }

        return o;
    }


//end of namespace
}
}
