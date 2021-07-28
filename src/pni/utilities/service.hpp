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
//
// ============================================================================
//
// Created on: Dec 8, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/types/types.hpp>

namespace pni{

    //!
    //! \ingroup utility_classes
    //! \brief runtime warning for functions
    //! 
    //! This macro inserts a warning message shown at runtime when a deprecated
    //! function or class member function is used. It should remaind the 
    //! developer that the function in use will most probably vanish in a 
    //! future release. Call the macro at the beginning of the deprecated 
    //! function. It uses the BOOST_CURRENT_FUNCTION macro to get the name of 
    //! the actual function.  The only argument is the signature of the new 
    //! function to be used instread.
    //! 
    /*!
    \code 
    void old_function()
    {
       DEPRECATED_FUNCTION("void new_function()");
       .......
    }
    
    void new_function()
    {
      .......
    }
    \endcode
    !*/
    //! 
    //! \param newfunc the new function to use
    //!
#define DEPRECATED_FUNCTION(newfunc)\
    std::cerr<<"DEPRECATION WARNING:"<<std::endl; \
    std::cerr<<""<<BOOST_CURRENT_FUNCTION;\
    std::cerr<<" is deprecated use "<<newfunc<<" instread!";\
    std::cerr<<std::endl

//end of namespace
}
