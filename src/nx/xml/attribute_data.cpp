/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Jul 16, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "attribute_data.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{


    //-------------------------------------------------------------------------
    bool has_attribute(const node &n,const string &name) noexcept
    {
        try
        {
            n.get<string>("<xmlattr>."+name);
        }
        catch(...)
        {
            //as we catch all exceptions here we do not have a problem
            return false;
        }
        return true;
    }
   
    //-------------------------------------------------------------------------
    bool has_data(const node &n,const string &name)
    {
        auto value = attribute_data<string>::read(n,name);
        
        return !value.empty();

    }
//end of namespace
}
}
}
}
