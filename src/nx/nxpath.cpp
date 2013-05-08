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
 *
 * Created on: May 06, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "nxpath.hpp"

namespace pni{
namespace io{
namespace nx{

   
    //-------------------------------------------------------------------------
    nxpath::nxpath():
        _file_name(),
        _attribute_name(),
        _groups()
    {}

    //-------------------------------------------------------------------------
    nxpath::nxpath(const string &file,const nxpath::group_path_t &groups,
                   const string &attr):
        _file_name(file),
        _attribute_name(attr),
        _groups(groups)
    {}

    //--------------------------------------------------------------------------
    void nxpath::append(const string &gname,const string &gclass)
    {
        group_element_t element(gname,gclass);
        _groups.push_back(element);
    }

    //-------------------------------------------------------------------------
    void nxpath::prepend(const string &gname,const string &gclass)
    {
        group_element_t element(gname,gclass);
        _groups.push_front(element);
    }

    //-------------------------------------------------------------------------
    group_element_t nxpath::pop_front()
    {
        group_element_t element = *(_groups.begin());
        _groups.pop_front();
        return element;
    }

    //-------------------------------------------------------------------------
    group_element_t nxpath::pop_back()
    {
        group_element_t element = *(_groups.rbegin());
        _groups.pop_back();
        return element;
    }

    //-------------------------------------------------------------------------
    void split_path(const string &input,
                    string &file,string &groups,string &attribute)
    {
        //start with file portion
        file = string();
        groups = string();
        attribute = string();

        string::size_type file_pos  = input.find("://");
        if(file_pos != string::npos)
        {
            file = input.substr(0,file_pos);
            file_pos += 3;    
        }
        else
            file_pos = 0;

        //search for attributes
        string::size_type attr_pos = input.find("@");
        if(attr_pos != string::npos)
        {
            attribute = input.substr(attr_pos+1,input.size()-attr_pos);
        }
        else
            attr_pos = input.size();

        groups = input.substr(file_pos,attr_pos-file_pos);
    }

    //-------------------------------------------------------------------------
    nxpath path_from_string(const string &p)
    {
        typedef string::const_iterator iterator_t;
        typedef nxpath_parser<iterator_t> nxpath_parser_t;

        //split the path entered by the user
        string filename,attribute_name,groups;
        split_path(p,filename,groups,attribute_name);

        //parse the group section
        nxpath_parser_t parser;
        iterator_t start = groups.begin();
        iterator_t stop  = groups.end();
        nxpath::group_path_t gpath; 
        parse(start,stop,parser,gpath);

        return nxpath(filename,gpath,attribute_name);
    }

    //-------------------------------------------------------------------------
    nxpath split(size_t i,nxpath &p)
    {
        string file_name = p.filename();
        string attribute_name = p.attribute();

        //now we have to split the elements
        nxpath path(p.filename(),nxpath::group_path_t(p.size()-i),
                    p.attribute());
    }

    //--------------------------------------------------------------------------
    void split(const nxpath &p,size_t i,nxpath &p1,nxpath &p2)
    {
        p1 = p;
        p2 = split(i,p1);
    }

//end of namespace
}
}
}
