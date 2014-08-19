//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 17, 2014
//      Author: Eugen Wintersberger
//

#include <pni/io/nx/h5/h5deflate_filter.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>

namespace pni {
namespace io {
namespace nx {
namespace h5 {

    //-------------------------------------------------------------------------
    h5deflate_filter::h5deflate_filter() noexcept:
        h5filter(),
        _comp_rate(0),
        _shuffle(false)
    { }
    
    //-------------------------------------------------------------------------
    h5deflate_filter::h5deflate_filter(uint32 rate,bool shuffle) noexcept:
        h5filter(),
        _comp_rate(rate),
        _shuffle(shuffle)
    { }


    //-------------------------------------------------------------------------
    void h5deflate_filter::setup(const object_imp &plist) const
    {
        
        if(_shuffle)
        {
            if(H5Pset_shuffle(plist.id())<0)
                throw object_error(EXCEPTION_RECORD, 
                    "Error setting up shuffle filter for deflate!\n\n"+
                    get_h5_error_string());
        }

        if((H5Pset_deflate(plist.id(),_comp_rate))<0)
            throw object_error(EXCEPTION_RECORD,
                "Error setting compression rate for deflate filter!\n\n"+
                get_h5_error_string());
    }

    //-------------------------------------------------------------------------
    uint32 h5deflate_filter::compression_rate() const noexcept
    {
        return _comp_rate;
    }

    //-------------------------------------------------------------------------
    void h5deflate_filter::compression_rate(uint32 r)
    {
        if(r<=9)
            _comp_rate = r;
        else
            throw range_error(EXCEPTION_RECORD,
                "Compression level for deflate filter must be between "
                "0 and 9!\n\n"+get_h5_error_string());
    }

    //------------------------------------------------------------------
    void h5deflate_filter::shuffle(bool value) noexcept
    {
        _shuffle = value;
    }

    //------------------------------------------------------------------
    bool h5deflate_filter::shuffle() const noexcept
    {
        return _shuffle;
    }

//end of namespace
}
}
}
}
