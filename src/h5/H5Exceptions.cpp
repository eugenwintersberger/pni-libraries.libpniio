/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * H5Exceptions.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: Eugen Wintersberger
 *
 *  Implementation of exceptions for the HDF5 interface of the Nexus API.
 */

#include "H5Exceptions.hpp"

namespace pni{
namespace nx{
namespace h5{

    H5Exception::H5Exception():Exception()
    {
        _h5estack.fill();
    }

    H5Exception::H5Exception(const String &n):Exception(n)
    {
        _h5estack.fill();
    }

    H5Exception::H5Exception(const String &n,const ExceptionRecord &i,
                             const String &d):
        Exception(n,i,d)
    {
        _h5estack.fill();
    }

    H5Exception::H5Exception(const H5Exception &e):
        Exception(e)
    {
        _h5estack = e._h5estack;
    }

    H5Exception::~H5Exception() throw() { }

    std::ostream &H5Exception::print(std::ostream &o) const
    {
        o<<Exception::print(o);
        o<<_h5estack;

        return o;
    }

    std::ostream &operator<<(std::ostream &o,const H5Exception &e)
    {
        return e.print(o);
    }

    H5DataTypeError::H5DataTypeError() :H5Exception("H5DataTypeError")
    {}

    H5DataTypeError::H5DataTypeError(const ExceptionRecord &i,const String &d):
        H5Exception("H5DataTypeError",i,d)
    { }

    H5DataTypeError::~H5DataTypeError() throw(){ }

    std::ostream &operator<<(std::ostream &o,const H5DataTypeError &e)
    {
        return e.print(o);
    }

    H5DataSetError::H5DataSetError():H5Exception("H5DataTypeError")
    { }

    H5DataSetError::H5DataSetError(const ExceptionRecord &i,const String &d):
        H5Exception("H5DataTypeError",i,d)
    { }

    H5DataSetError::~H5DataSetError() throw(){ }

    std::ostream &operator<<(std::ostream &o,const H5DataSetError &e)
    {
        return e.print(o);
    }

    H5DataSpaceError::H5DataSpaceError():H5Exception("H5DataSpaceError")
    { }

    H5DataSpaceError::H5DataSpaceError(const ExceptionRecord &i,
                                       const String &d):
        H5Exception("H5DataSpaceError",i,d)
    { }

    H5DataSpaceError::~H5DataSpaceError() throw(){ }

    std::ostream &operator<<(std::ostream &o,const H5DataSpaceError &e)
    {
        return e.print(o);
    }

    H5AttributeError::H5AttributeError():H5Exception("H5AttributeError")
    { }

    H5AttributeError::H5AttributeError(const ExceptionRecord &i,const String &d):
        H5Exception("H5AttributeError",i,d)
    { }

    H5AttributeError::~H5AttributeError() throw(){ }

    std::ostream &operator<<(std::ostream &o,const H5AttributeError &e)
    {
        return e.print(o);
    }

    H5FileError::H5FileError():H5Exception("H5FileError"){ }

    H5FileError::H5FileError(const ExceptionRecord &i,const String &d):
        H5Exception("H5FileError",i,d)
    { }

    H5FileError::~H5FileError() throw(){ } 

    std::ostream &operator<<(std::ostream &o,const H5FileError &e)
    {
        return e.print(o);
    }

    H5GroupError::H5GroupError():H5Exception("H5GroupError") { }

    H5GroupError::H5GroupError(const ExceptionRecord &i,const String &d):
        H5Exception("H5GroupError",i,d)
    { }

    H5GroupError::~H5GroupError() throw(){ }

    std::ostream &operator<<(std::ostream &o,const H5GroupError &e)
    {
        return e.print(o);
    }

    H5PropertyListError::H5PropertyListError():
        H5Exception("H5PropertyListError")
    { }

    H5PropertyListError::H5PropertyListError(const ExceptionRecord &i,
                                             const String &d):
        H5Exception("H5PropertyListError",i,d)
    { }

    H5PropertyListError::~H5PropertyListError() throw(){ } 

    std::ostream &operator<<(std::ostream &o,const H5PropertyListError &e)
    {
        return e.print(o);
    }

    H5FilterError::H5FilterError():H5Exception("H5FilterError"){ }

    H5FilterError::H5FilterError(const ExceptionRecord &i,const String &d):
        H5Exception("H5FilterError",i,d)
    { }

    H5FilterError::~H5FilterError() throw(){ }

    std::ostream &operator<<(std::ostream &o,const H5FilterError &e)
    {
        return e.print(o);
    }

    std::ostream &operator<<(std::ostream &o,const H5ObjectError &e)
    {
        return e.print(o);
    }

    std::ostream &operator<<(std::ostream &o,const H5LinkError &e)
    {
        return e.print(o);
    }
//end of namespace
}
}
}

