//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
#pragma once

#include <pni/types.hpp>
#include <h5cpp/hdf5.hpp>
#include <pni/nexus.hpp>
#include <vector>

//!
//! \brief base fixture 
//! 
//! This is the base fixture used for most of the tests. It creates a new 
//! file and provides the filename, the file object, and the root group
//! object as public members. 
//! 
struct base_fixture
{
    pni::string filename;    //!< name of the file created
    hdf5::file::File file;   //!< file instancen
    hdf5::node::Group root;  //!< root group instance

    //!
    //! \brief constructor
    //!
    //! \param fname name of the file to create or open
    //! \param open_existing decide whether to create a new file or open
    //!                      an existing one
    //! 
    base_fixture(const pni::string &fname,bool open_existing=false);
    virtual ~base_fixture(); 
};
