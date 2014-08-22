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
//
// Created on: Aug 22, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <boost/spirit/home/phoenix/function/function.hpp>

namespace pni{
namespace io{
namespace nx{

    namespace stl
    {
        //!
        //! \ingroup nxpath_code
        //! \brief custom inserter
        //!
        //! This is a specialized version of the standard STL inserter 
        //! provided by boost::spirit. The original version includes a return
        //! statement though the return type of the () operator is void.
        //! This situation was recognized as an error by g++ 4.9.. To get a
        //! clean build this stripped down version was neccessary. 
        //!
        struct insert
        {
            template <
                typename C
              , typename Arg1
              , typename Arg2 
              , typename Arg3 
            >
            class result
            {

            public:

                typedef void type;
            };

            template <typename C, typename Arg1, typename Arg2, typename Arg3>
            void operator()( C& c, Arg1 const& arg1, Arg2 const& arg2, Arg3 const& arg3) const
            {
                c.insert(arg1, arg2, arg3);
            }
        };
    }

    //create function object
    boost::phoenix::function<stl::insert> const  insert = stl::insert();
//end of namespace
}
}
}
