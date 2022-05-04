//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pninexus.
//
// pninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pninexus.  If not, see <http://www.gnu.org/licenses/>.
//
// ============================================================================
//
//  Created on: Oct 22, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <iostream>
#include <iomanip>
#include <pni/types.hpp>

using namespace pni;

template<typename GeneralT> void show_type_info()
{
    typedef pni::type_info<GeneralT> info_type;
    type_id_t tid = type_id_map<GeneralT>::type_id;
    string type_name = str_from_type_id(tid);
    std::cout<<std::setw(12)<<type_name
        <<"  size = "<<std::setw(2)<<info_type::size
        <<"  range = ["<<std::setw(21)<<info_type::min()
                       <<" : "
                       <<std::setw(21)<<info_type::max()
        <<"]"
        <<std::endl;
}


int main(int,char**)
{
    std::cout<<"Basic parameters of primitive types:"<<std::endl;
    show_type_info<uint8>();
    show_type_info<uint16>();
    show_type_info<uint32>();
    show_type_info<uint64>();

    show_type_info<int8>();
    show_type_info<int16>();
    show_type_info<int32>();
    show_type_info<int64>();

    show_type_info<float32>();
    show_type_info<float64>();
    show_type_info<float128>();

    return 0;
}
