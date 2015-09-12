//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// Created on: Sep 12, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>
#include <pni/core/types.hpp>
#include "nxpath.hpp"

namespace pni{
namespace io{
namespace nx{    

    //!
    //! \ingroup nxpath_utils
    //! \brief make a relative path
    //! 
    //! Take a given path and make it relative with respect to a particular 
    //! other path (typically the path of a parent object). 
    //! 
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! nxpath entry = nxpath::from_string("/:NXentry");
    //! nxpath det   = nxpath::from_string("/:NXentry/:NXinstrument/:NXdetector");
    //! 
    //! nxpath det_rel = make_relative(entry,det);
    //! std::cout<<det_rel<<std::endl;
    //! // output: :NXinstrument/:NXdetector
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //! 
    //! For this procedure to work both paths must be absolute as we need a
    //! common starting point (which would be the root group). In the case that 
    //! Both 
    //! 
    //! * both paths must be absolute (as we need a common starting point which 
    //!   would be the root group
    //! * if boths paths have a file section it must be equal 
    //! * if 
    //! 
    //! A typical application would be to find all instances of `NXdetector` 
    //! in a given instrument group. 
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! 
    //! std::vector<h5::nxobject> detectors; 
    //! 
    //! 
    nxpath make_relative(const nxpath &parent_path,const nxpath &orig_path);
    nxpath make_relative(const pni::core::string &parent_path,
                         const pni::core::string &orig_path);

    nxpath make_relative(const nxpath &parent_path,
                         const pni::core::string &orig_path);
    nxpath make_relative(const pni::core::string &parent_path,
                         const nxpath &orig_path);

}
}
}
