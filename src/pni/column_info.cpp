//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 30, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//


#include <pni/column_info.hpp>

namespace pni{
namespace io{

    //==================implementation of constructors and destructor==========
    //implementation of the  default constructor
    column_info::column_info():
        _name(),
        _tid(pni::core::type_id_t::NONE),
        _shape()
    {}

    //--------------------------------------------------------------------------
    //implementation of the copy constructor
    column_info::column_info(const column_info &ci):
        _name(ci._name),
        _tid(ci._tid),
        _shape(ci._shape)
    {}

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    column_info::column_info(column_info &&ci):
        _name(std::move(ci._name)),
        _tid(std::move(ci._tid)),
        _shape(std::move(ci._shape))
    {}

    //-------------------------------------------------------------------------
    //implementation of the standard constructor
    column_info::column_info(const pni::core::string &n,
                             pni::core::type_id_t tid,
                             const std::vector<size_t> &s):
        _name(n),
        _tid(tid),
        _shape(s)
    {}

    //-------------------------------------------------------------------------
    //implementation of the destructor
    column_info::~column_info()
    {}

    //===================implementation of assignment operators================
    //implementation of the  copy assignment operator
    column_info &column_info::operator=(const column_info &ci)
    {
        if(this == &ci) return *this;

        _name = ci._name;
        _shape = ci._shape;
        _tid = ci._tid;

        return *this;
    }

    //-------------------------------------------------------------------------
    //! move assignment operator
    column_info &column_info::operator=(column_info &&ci)
    {
        if(this == &ci) return *this;

        _name = std::move(ci._name);
        _shape = std::move(ci._shape);
        _tid = std::move(ci._tid);
        return *this;
    }

    //=================implementation of non-member operators==================
    std::ostream &operator<<(std::ostream &o,const column_info &ci)
    {
        o<<"Column ["<<ci.name()<<"] of type ["<<ci.type_id();
        o<<"] and element shape [ ";
#ifdef NOFOREACH
        for(auto iter=ci.shape().begin();iter!=ci.shape().end();++iter)
        {
            auto v = *iter;
#else
        for(auto v: ci.shape()) 
        {
#endif 
            o<<v<<" ";
        }
        o<<"]";
        return o;
    }

//end of namespace
}
}
