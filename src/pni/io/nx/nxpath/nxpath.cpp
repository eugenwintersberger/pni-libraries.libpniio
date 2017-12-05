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

#include <sstream>
#include <pni/core/error.hpp>
#include <pni/io/nx/nxpath/nxpath.hpp>
#include <pni/io/nx/nxpath/parser.hpp>
#include <pni/io/nx/nxpath/utils.hpp>


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
    nxpath::nxpath(const pni::core::string &file,
                   const nxpath::elements_type &objects,
                   const pni::core::string &attr):
        _file_name(file),
        _attribute_name(attr),
        _elements(objects)
    {}

    //-------------------------------------------------------------------------
    nxpath nxpath::from_string(const pni::core::string &input)
    {
        return parsers::parse_path(input);
    }

    //-------------------------------------------------------------------------
    pni::core::string nxpath::to_string(const nxpath &p)
    {
        std::stringstream str_stream;
        str_stream<<p;

        return str_stream.str();
    }
           
    //-------------------------------------------------------------------------
    bool nxpath::has_filename() const noexcept 
    { 
        return !_file_name.empty(); 
    }

    //-------------------------------------------------------------------------
    bool nxpath::has_attribute() const noexcept 
    { 
        return !_attribute_name.empty(); 
    }
    
    //-------------------------------------------------------------------------
    pni::core::string nxpath::filename() const noexcept 
    { 
        return _file_name; 
    }
    
    //-------------------------------------------------------------------------
    void nxpath::filename(const pni::core::string &f) 
    {
        _file_name = f; 
    }
    
    //-------------------------------------------------------------------------
    pni::core::string nxpath::attribute() const noexcept 
    { 
        return _attribute_name; 
    }

    //-------------------------------------------------------------------------
    void nxpath::attribute(const pni::core::string &a) 
    { 
        _attribute_name = a; 
    }

    //-------------------------------------------------------------------------
    void nxpath::push_back(const element_type &o) 
    {
        using namespace pni::core;
        if(is_root_element(o)&&size())
            throw value_error(EXCEPTION_RECORD,
                    "Cannot push back a root group to a non-empty path!");

        _elements.push_back(o); 
    }

    //-------------------------------------------------------------------------
    void nxpath::push_front(const element_type &o) 
    { 
        _elements.push_front(o); 
    }
    
    //-------------------------------------------------------------------------
    void nxpath::pop_front() 
    { 
        _elements.pop_front(); 
    }

    //-------------------------------------------------------------------------
    void nxpath::pop_back() 
    { 
        _elements.pop_back(); 
    }
    
    //-------------------------------------------------------------------------
    nxpath::element_type nxpath::back() const 
    { 
        return _elements.back(); 
    }
    
    //-------------------------------------------------------------------------
    size_t nxpath::size() const 
    { 
        return _elements.size(); 
    }

    //-------------------------------------------------------------------------
    nxpath::iterator nxpath::begin() 
    { 
        return _elements.begin(); 
    }
    
    //-------------------------------------------------------------------------
    nxpath::iterator nxpath::end()   
    { 
        return _elements.end();   
    }

    //-------------------------------------------------------------------------
    nxpath::const_iterator nxpath::begin() const 
    { 
        return _elements.begin(); 
    }
    
    //-------------------------------------------------------------------------
    nxpath::const_iterator nxpath::end() const   
    { 
        return _elements.end();   
    }


//end of namespace
}
}
}
