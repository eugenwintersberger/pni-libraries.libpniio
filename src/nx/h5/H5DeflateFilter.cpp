//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//  Created on: Aug 10, 2011
//      Author: Eugen Wintersberger
//

#include <pni/io/nx/h5/H5DeflateFilter.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/nxexceptions.hpp>

namespace pni {
namespace io {
namespace nx {
namespace h5 {

    //-------------------------------------------------------------------------
    H5DeflateFilter::H5DeflateFilter():
        H5Filter(),
        _comp_rate(0),
        _shuffle(false)
    { }

    //-------------------------------------------------------------------------
    H5DeflateFilter::H5DeflateFilter(uint32 rate,bool shuffle):
        H5Filter(),
        _comp_rate(rate),
        _shuffle(shuffle)
    { }

    //-------------------------------------------------------------------------
    H5DeflateFilter::~H5DeflateFilter() { }

    //-------------------------------------------------------------------------
    H5DeflateFilter::H5DeflateFilter(const H5DeflateFilter &o):
        H5Filter(o),
        _comp_rate(o._comp_rate),
        _shuffle(o._shuffle)
    { }

    //-------------------------------------------------------------------------
    H5DeflateFilter::H5DeflateFilter(H5DeflateFilter &&o):
        H5Filter(std::move(o)),
        _comp_rate(std::move(o._comp_rate)),
        _shuffle(std::move(o._shuffle))
    { }

    //-------------------------------------------------------------------------
    H5DeflateFilter &H5DeflateFilter::operator=(const H5DeflateFilter &o)
    {
        if(this != &o){
            H5Filter::operator=(o);
            _comp_rate = o._comp_rate;
            _shuffle   = o._shuffle;
        }

        return *this;
    }

    //-------------------------------------------------------------------------
    H5DeflateFilter &H5DeflateFilter::operator=(H5DeflateFilter &&o)
    {
        if(this != &o){
            H5Filter::operator=(std::move(o));
            _comp_rate = o._comp_rate;
            _shuffle   = o._shuffle;
            o._comp_rate = 0;
            o._shuffle   = false;
        }

        return *this;
    }

    //-------------------------------------------------------------------------
    void H5DeflateFilter::setup(hid_t id) const
    {

        if(H5Pset_shuffle(id)<0)
            throw pni::io::nx::nxfilter_error(EXCEPTION_RECORD, 
                "Error setting up shuffle filter for deflate!\n\n"+
                get_h5_error_string());

        if((H5Pset_deflate(id,_comp_rate))<0)
            throw pni::io::nx::nxfilter_error(EXCEPTION_RECORD,
                "Cannot setup deflate filter!\n\n"+
                get_h5_error_string());
    }

    //-------------------------------------------------------------------------
    uint32 H5DeflateFilter::compression_rate() const
    {
        return _comp_rate;
    }

    //-------------------------------------------------------------------------
    void H5DeflateFilter::compression_rate(uint32 r)
    {
        if(r<=9)
            _comp_rate = r;
        else
            throw pni::io::nx::nxfilter_error(EXCEPTION_RECORD,
                "Compression level for deflate filter must be between "
                "0 and 9!\n\n"+get_h5_error_string());
    }

    //------------------------------------------------------------------
    void H5DeflateFilter::shuffle(bool value)
    {
        _shuffle = value;
    }

    //------------------------------------------------------------------
    bool H5DeflateFilter::shuffle() const
    {
        return _shuffle;
    }

//end of namespace
}
}
}
}
