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

#include <pni/io/nx/nxpath.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/classification.hpp>


namespace pni{
namespace io{
namespace nx{

    namespace fs   = boost::filesystem;
    namespace algo = boost::algorithm; 
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
        typedef string::const_iterator iterator_t;

        //a file path must contain at least one '.' - the extension of the 
        //file
        bool file_path = algo::contains(input,".");
        //a full path consists of a file path separated from the object path
        //by :// 
        bool full_path = algo::contains(input,"://");
        //an attribute is speparated by an '@' symbol from the rest of the 
        //rest of the path
        bool has_attribute = algo::contains(input,"@");

        string parser_input;
        if(full_path)
            //need to parse a full nexus path
            parser_input = input;
        else if(file_path)
            //if the input is not a full path but satisifies the requirements 
            //for a file path => it can only be a file path.
            parser_input = input + "://";
        else
            //if the input is neither a full path nor a file path it must be 
            //an object path
            parser_input = "://"+input;
        typedef parsers::elements_parser<iterator_t> nxpath_parser_t;

        //split the path entered by the user
        string filename,attribute_name,groups;

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
        stream<<e.first;
        //the colon will only be printed if the second component is not empty
        if(!e.second.empty()) stream<<":"<<e.second;
        return stream;
    }

    // -----------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,
                             const nxpath::elements_type &elements)
    {
        size_t index = 0;

        for(auto e: elements)
        {
            stream<<e;
            if(index++ < elements.size()-1) stream<<"/";
        }

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
