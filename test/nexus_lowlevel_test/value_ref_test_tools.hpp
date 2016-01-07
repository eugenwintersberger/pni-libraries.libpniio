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
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================

#pragma once

#include <boost/test/unit_test.hpp>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <iostream>


namespace boost {
namespace test_tools {

    template<> struct print_log_value<pni::core::value_ref>
    {
        void operator()(std::ostream &stream,const pni::core::value_ref &v);
    };

namespace tt_detail{

    bool operator==(pni::core::value_ref const& a,
                    pni::core::value_ref const& b);

    bool operator!=(pni::core::value_ref const& a,
                    pni::core::value_ref const& b);
}
}
}

namespace std{

    std::ostream& operator<<(std::ostream &stream,
                             const pni::core::value_ref &v);

}
