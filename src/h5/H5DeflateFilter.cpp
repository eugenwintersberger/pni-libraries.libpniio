/*
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
 * H5DeflateFilter.cpp
 *
 *  Created on: Aug 10, 2011
 *      Author: Eugen Wintersberger
 */

#include "H5DeflateFilter.hpp"
#include "H5Exceptions.hpp"

namespace pni {
namespace nx {
namespace h5 {

    //-------------------------------------------------------------------------
    H5DeflateFilter::H5DeflateFilter():
        H5Filter(),
        _comp_rate(0),
        _shuffle(false)
    { }

    //-------------------------------------------------------------------------
    H5DeflateFilter::H5DeflateFilter(UInt32 rate,bool shuffle):
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
            throw H5FilterError(EXCEPTION_RECORD, 
                                "Error setting up shuffle filter for deflate!");

        if((H5Pset_deflate(id,_comp_rate))<0)
            throw H5FilterError(EXCEPTION_RECORD,
                                "Cannot setup deflate filter!");
    }

    //-------------------------------------------------------------------------
    UInt32 H5DeflateFilter::compression_rate() const
    {
        return _comp_rate;
    }

    //-------------------------------------------------------------------------
    void H5DeflateFilter::compression_rate(UInt32 r)
    {
        if(r<=9)
            _comp_rate = r;
        else
            throw H5FilterError(EXCEPTION_RECORD,
                                "Compression level for " 
                                "deflate filter must be between 0 and 9!");
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
