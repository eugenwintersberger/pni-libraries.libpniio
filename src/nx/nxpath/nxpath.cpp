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
// Created on: May 06, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/nxpath/nxpath.hpp>
#include <pni/io/nx/nxpath/parser.hpp>


namespace pni{
namespace io{
namespace nx{

    //-------------------------------------------------------------------------
    nxpath::nxpath():
        _file_name(),
        _attribute_name(),
        _elements()
    {}

    //-------------------------------------------------------------------------
    nxpath::nxpath(const string &file,const nxpath::elements_type &objects,
                   const string &attr):
        _file_name(file),
        _attribute_name(attr),
        _elements(objects)
    {}

    //-------------------------------------------------------------------------
    nxpath nxpath::from_string(const string &input)
    {
        return parsers::parse_path(input);
    }

    //-------------------------------------------------------------------------
    string nxpath::to_string(const nxpath &p)
    {

    }

    //-------------------------------------------------------------------------
    bool nxpath::is_absolute() const
    {
        //if the first element in the object path is NXroot the path 
        //is absolute.
        if(size())
            return _elements.front().second=="NXroot";
        else
            return false;
    }

    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,const nxpath::element_type &e)
    {
        if((!e.first.empty() && e.first=="/") || 
           (!e.second.empty() && e.second=="NXroot"))
        {
            stream<<"/";
        }
        else
        {
            stream<<e.first;
            //the colon will only be printed if the second component is not empty
            if(!e.second.empty()) stream<<":"<<e.second;
        }
        return stream;
    }

    //------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,
                             const nxpath::elements_type &e)
    {
        if(!e.size()) return stream;

        for(auto v: e)
            stream<<e<<"/";

        return stream;

    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,const nxpath &p)
    {
        if(!p.filename().empty()) stream<<p.filename()<<"://";

        if(p.is_absolute()) stream<<"/";

        size_t index = 0;
        for(auto e: p)
        {
            stream<<e;
            if(index++ < p.size()-1) stream<<"/";
        }

        if(!p.attribute().empty()) stream<<"@"<<p.attribute();

        return stream;

    }


//end of namespace
}
}
}
