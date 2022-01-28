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
//************************************************************************
//
//  Created on: Oct 18, 2015
//  Authors:
//          Eugen Wintersberger <eugen.wintersberger@desy.de>
//          Jan Kotanski <jan.kotanski@desy.de>
//
#include "data_generator.hpp"
#include <h5cpp/contrib/nexus/ebool.hpp>

//----------------------------------------------------------------------------
random_generator<hdf5::datatype::EBool>::random_generator()
    :_generator(0,1)
{}

//----------------------------------------------------------------------------
hdf5::datatype::EBool random_generator<hdf5::datatype::EBool>::operator()()
{
    return hdf5::datatype::EBool(_generator());
}
//----------------------------------------------------------------------------
random_generator<bool_t>::random_generator()
    :_generator(0,1)
{}

//----------------------------------------------------------------------------
bool_t random_generator<bool_t>::operator()()
{
    return bool(_generator());
}

//----------------------------------------------------------------------------
random_generator<string>::random_generator(size_t nchars):
            _line_size_generator(0,nchars),
            _char_index_generator(0,_char_vector.size()-1)
{}

//----------------------------------------------------------------------------
random_generator<string>::random_generator():
    _line_size_generator(0,10),
    _char_index_generator(0,_char_vector.size()-1)
{}

//----------------------------------------------------------------------------
string random_generator<string>::operator()()
{
    size_t nchars = _line_size_generator();

    string s;
    for(size_t index=0;index<nchars;index++)
        s.push_back(_char_vector[_char_index_generator()]);

    return s;
}

//----------------------------------------------------------------------------
const std::vector<char> random_generator<string>::_char_vector = 
{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
 't','u','v','w','x','y','z',
 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S',
 'T','U','V','W','X','Y','Z',
 '0','1','2','3','4','5','6','7','8','9',
 '~','!','@','#','$','%','&','*','(',')','-','_','+','='};
