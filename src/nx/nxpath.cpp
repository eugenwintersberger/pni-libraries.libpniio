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
    nxpath::group_element_t nxpath::pop_front()
    {
        group_element_t element = *(_groups.begin());
        _groups.pop_front();
        return element;
    }

    //-------------------------------------------------------------------------
    nxpath::group_element_t nxpath::pop_back()
    {
        group_element_t element = *(_groups.rbegin());
        _groups.pop_back();
        return element;
    }

    //-------------------------------------------------------------------------
    bool is_file_path(const string &s)
    {
        fs::path p(s);

        //if the path has no extension we assume it to be an object path
        if(extension(p).empty()) return false;

        return true;
        
    }

    //-------------------------------------------------------------------------
    void split_object_path(const string &input,string &groups,
                           string &attributes)
    {
        //define a string container 
        typedef std::vector<string> str_cont_t;

        str_cont_t result;
        algo::split(result,input,algo::is_any_of("@"));

        groups = string();
        attributes = string();
        
        for(size_t i=0;i<result.size();++i)
        {
            if(i==0) groups = result[i];
            else if(i==1) attributes = result[i];
            else
            {
                //throw an exception here.
            }
        }


    }

    //-------------------------------------------------------------------------
    void split_path(const string &input,
                    string &file,string &groups,string &attribute)
    {
        //define a string container 
        typedef std::vector<string> str_cont_t;

        //start with file portion
        file = string();
        groups = string();
        attribute = string();

         
        if(algo::contains(input,"://"))
        {
            //here it is easy we know that which part of the path is the file
            //section and which the object path within the file 
            auto result = algo::find_first(input,"://");
            file = string(input.begin(),result.begin());
            split_object_path(string(result.end(),input.end()),groups,
                              attribute);
             
        }
        else
        {
            //here we need some additional check - in this case the string can
            //be either a file path or an object path
            if(is_file_path(input)) file = input;
            else
            {
                //in this case the string is an object path and we have to check
                //for a possible attribute
                split_object_path(input,groups,attribute);

            }

        }
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
