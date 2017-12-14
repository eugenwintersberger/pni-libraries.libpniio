//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
#pragma once

#include <pni/core/types.hpp>
#include <h5cpp/hdf5.hpp>
#include <boost/filesystem.hpp>
#include <vector>

//!
//! \brief base fixture 
//! 
//! This is the base fixture used for most of the tests. It creates a new 
//! file and provides the filename, the file object, and the root group
//! object as public members. 
//! 
struct BaseFixture
{
    boost::filesystem::path filename;    //!< name of the file created
    hdf5::file::File file;  //!< file instancen
    hdf5::node::Group root; //!< root group instance

    //!
    //! \brief constructor
    //!
    //! \param fname name of the file to create or open
    //! \param open_existing decide whether to create a new file or open
    //!                      an existing one
    //! 
    BaseFixture(const boost::filesystem::path &fname,bool open_existing=false);
    virtual ~BaseFixture();
};
