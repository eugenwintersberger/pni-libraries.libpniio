//!
//! (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with lipniutils.  If not, see <http://www.gnu.org/licenses/>.
//!
//! ===========================================================================
//!
//! Created on: May 23, 2012
//!     Author: Eugen Wintersberger
//!
//!

#include <pni/error/exception_utils.hpp>

namespace pni{
namespace core{

    //------------------------------------------------------------------------
    bool check_index_in_dim(size_t index,size_t dimsize)
    {
        return index<dimsize;
    }

    //-------------------------------------------------------------------------
    void check_index_in_dim(size_t index,size_t dimsize,
                            const exception_record &i)
    {
        if(!check_index_in_dim(index,dimsize))
        {
            std::stringstream ss;
            ss<<"Index ("<<index<<") exceeds dimension range ("<<dimsize<<")!";
            throw index_error(i,ss.str());
        }
    }

//end of namespace
}
}
