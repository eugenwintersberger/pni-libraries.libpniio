//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 11, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <iostream>

#include <pni/windows.hpp>

namespace pni{

    //!
    //! \ingroup type_classes
    //! \brief boolean type
    //! 
    //! There is a particular problem when using the standard bool type in
    //! connection with std::vector. The std::vector template is overloaded 
    //! for bool in a sense that each boolean value is stored in an individual 
    //! bit. Thus elements cannot be addressed. Thus std::vector<bool> cannot 
    //! be used in connection with libpninexus. 
    //! This type prevents the C++ compiler to overload std:vector<bool_t> 
    //! making boolean values available for libpninexus.
    //!
    class PNINEXUS_EXPORT bool_t
    {
        private:
            bool _value; //!< data element holding the current boolean value
        public:
            //! default constructor
            bool_t():_value(false) {}

            //! conversion constructor
            bool_t(bool v):_value(v) {}

            //! conversion operator
            operator bool() const
            {
                return _value;
            }

    };

    
    //! output operator for bool_t
    PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &stream,const bool_t &b);

    //! input operator for bool_t
    PNINEXUS_EXPORT std::istream &operator>>(std::istream &stream,bool_t &b);
//end of namespace
}
