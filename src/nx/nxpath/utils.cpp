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
// Created on: Jun 26, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <sstream>
#include <pni/io/nx/nxpath/utils.hpp>
#include <pni/io/nx/nxpath/parser.hpp>
#include <pni/core/error.hpp>


namespace pni{
namespace io{
namespace nx{

    //--------------------------------------------------------------------------
    nxpath::element_type object_element(const string &name,const string &type)
    {
        if(name.empty()&&type.empty())
            throw value_error(EXCEPTION_RECORD,
                    "Namen and type of the object are empty!");

        return nxpath::element_type{name,type};
    }

    //--------------------------------------------------------------------------
    void split_path(const nxpath &p,size_t s,nxpath &p1,nxpath &p2)
    {

        if(s>=p.size())
        {
            std::stringstream ss;
            ss<<"Split index "<<s<<" exceeds input path size ";
            ss<<p.size()<<"!";
            throw index_error(EXCEPTION_RECORD,ss.str());
        }
        auto split_iter = p.begin();
        std::advance(split_iter,s);

        nxpath::elements_type gp1(s),gp2(p.size()-s);
        std::copy(p.begin(),split_iter,gp1.begin());
        std::copy(split_iter,p.end(),gp2.begin());

        //if the original path was absolute also the first part of the two 
        //must be absolute
        p1 = nxpath(p.filename(),gp1,"");
        p2 = nxpath("",gp2,p.attribute());
    }

    //--------------------------------------------------------------------------
    void split_last(const nxpath &p,nxpath &gpath,nxpath &opath)
    {
        split_path(p,p.size()-1,gpath,opath);
    }

    //--------------------------------------------------------------------------
    bool has_file_section(const nxpath &p)
    {
        if(p.filename().empty()) return false;
        return true;
    }

    //-------------------------------------------------------------------------
    bool has_attribute_section(const nxpath &p)
    {
        if(p.attribute().empty()) return false;
        return true;
    }
    
    //-------------------------------------------------------------------------
    bool is_root_element(const nxpath::element_type &e)
    {
        return (has_name(e) && (e.first=="/") && 
                has_class(e) && (e.second=="NXroot"));
    }

    //--------------------------------------------------------------------------
    bool is_absolute(const nxpath &p)
    {
        return is_root_element(p.front());
    }

    //--------------------------------------------------------------------------
    bool has_name(const nxpath::element_type &e)
    {
        return !e.first.empty();
    }

    //--------------------------------------------------------------------------
    bool has_class(const nxpath::element_type &e)
    {
        return !e.second.empty();
    }

    //--------------------------------------------------------------------------
    bool is_complete(const nxpath::element_type &e)
    {
        return has_name(e)&&has_class(e);
    }


    //--------------------------------------------------------------------------
    std::istream &operator>>(std::istream &i,nxpath &p)
    {   
        string buffer;
        i>>buffer;
        p = nxpath::from_string(buffer);
        return i;
    }

    //--------------------------------------------------------------------------
    bool operator==(const nxpath &lhs,const nxpath &rhs)
    {
        if(lhs.filename()!=rhs.filename()) return false;

        if(rhs.size() != lhs.size()) return false;

        for(auto lhs_iter = lhs.begin(), rhs_iter = rhs.begin();
                 lhs_iter != lhs.end();
                 ++lhs_iter,++rhs_iter)
        {
            if((lhs_iter->first != rhs_iter->first)||
               (lhs_iter->second != rhs_iter->second)) return false;
        }

        if(lhs.attribute() != rhs.attribute()) return false;

        return true;
    }

    //--------------------------------------------------------------------------
    bool operator!=(const nxpath &lhs,const nxpath &rhs)
    {
        return !(lhs == rhs);
    }
    
    //-------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,const nxpath::element_type &e)
    {
        stream<<e.first;
        //the colon will only be printed if the second component is not empty
        if(!e.second.empty() && !is_root_element(e) ) stream<<":"<<e.second;
        return stream;
    }

    //--------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream,const nxpath &p)
    {
        if(!p.filename().empty()) stream<<p.filename()<<":/";

        size_t index = 0;
        for(auto e: p)
        {
            stream<<e;
            if((index++ < p.size()-1) && !is_root_element(e)) 
                stream<<"/";
        }

        if(!p.attribute().empty()) stream<<"@"<<p.attribute();

        return stream;

    }

//end of namespace
}
}
}
