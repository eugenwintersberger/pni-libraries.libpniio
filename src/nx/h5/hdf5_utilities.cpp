//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Aug 20, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include "hdf5_utilities.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{

    string get_filename(hid_t id)
    {
        //first we need to determine the size of the file name
        ssize_t nsize = H5Fget_name(id,nullptr,0);
        if(nsize<0)
            return string(); //return an empty string

        //nsize is now the number of characters in the file name.
        string buffer(nsize,' ');
        //we have to read one more character to get the binary 0
        if(H5Fget_name(id,const_cast<char*>(buffer.data()),nsize+1)<0)
            return string();

        return buffer;
    }
   
    //-------------------------------------------------------------------------
    string get_object_path(hid_t id)
    {
        //if the object has already been created return this value
        hsize_t bsize = H5Iget_name(id,NULL,1);
        string buffer(bsize,' ');

        H5Iget_name(id,const_cast<char*>(buffer.data()),bsize+1);
        return buffer;
    }

//end of namespace
}
}
}
}
