/*
 * Implementation of Nexus specific exceptions
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *
 * Implementation of Nexus specific exceptions
 *
 * Created on: Aug 5, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <pni/io/nx/nxexceptions.hpp>

namespace pni{
namespace io{
namespace nx{

    //--------------------------------------------------------------------------
    nxfield_error::nxfield_error():exception("nxfield_error"){ }

    //--------------------------------------------------------------------------
    nxfield_error::nxfield_error(const exception_record &i,const string &d)
                 :exception("nxfield_error",i,d)
    { }

    //--------------------------------------------------------------------------
    nxfield_error::~nxfield_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const nxfield_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    nxattribute_error::nxattribute_error():exception("nxattribute_error"){ }

    //--------------------------------------------------------------------------
    nxattribute_error::nxattribute_error(const exception_record &i,const string &d)
                     :exception("nxattribute_error",i,d)
    { }

    //--------------------------------------------------------------------------
    nxattribute_error::~nxattribute_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const nxattribute_error &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    nxgroup_error::nxgroup_error():exception("nxgroup_error") { }

    //--------------------------------------------------------------------------
    nxgroup_error::nxgroup_error(const exception_record &i,const string &d)
                 :exception("nxgroup_error",i,d)
    { }

    //--------------------------------------------------------------------------
    nxgroup_error::~nxgroup_error() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const nxgroup_error &e)
    {
        return e.print(o);
    }

//end of namespace
}
}
}

