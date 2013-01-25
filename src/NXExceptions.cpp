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

#include "NXExceptions.hpp"

namespace pni{
namespace io{
namespace nx{

    //--------------------------------------------------------------------------
    NXFieldError::NXFieldError():exception("NXFieldError"){ }

    //--------------------------------------------------------------------------
    NXFieldError::NXFieldError(const exception_record &i,const string &d)
                 :exception("NXFieldError",i,d)
    { }

    //--------------------------------------------------------------------------
    NXFieldError::~NXFieldError() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const NXFieldError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    NXAttributeError::NXAttributeError():exception("NXAttributeError"){ }

    //--------------------------------------------------------------------------
    NXAttributeError::NXAttributeError(const exception_record &i,const string &d)
                     :exception("NXAttributeError",i,d)
    { }

    //--------------------------------------------------------------------------
    NXAttributeError::~NXAttributeError() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const NXAttributeError &e)
    {
        return e.print(o);
    }

    //--------------------------------------------------------------------------
    NXGroupError::NXGroupError():exception("NXGroupError") { }

    //--------------------------------------------------------------------------
    NXGroupError::NXGroupError(const exception_record &i,const string &d)
                 :exception("NXGroupError",i,d)
    { }

    //--------------------------------------------------------------------------
    NXGroupError::~NXGroupError() throw() { }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &o,const NXGroupError &e)
    {
        return e.print(o);
    }

//end of namespace
}
}
}

