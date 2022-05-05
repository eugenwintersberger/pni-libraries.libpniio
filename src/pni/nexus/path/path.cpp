//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: May 06, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <sstream>
#include <pni/error.hpp>
#include <pni/nexus/path/path.hpp>
#include <pni/nexus/path/parser.hpp>
#include <pni/nexus/path/utils.hpp>


namespace pni{
namespace nexus{

//-------------------------------------------------------------------------
Path::Path():
            _file_name(),
            _attribute_name(),
            _elements()
{}

Path::Path(const hdf5::Path &path):
    _file_name(),
    _attribute_name(),
    _elements()
{
  //we simply use the string conversion here
  //remove potential . from the list
  *this = Path::from_string(static_cast<std::string>(path));

  if(size()!=0)
  {
    auto new_pos = std::remove_if(_elements.begin(),_elements.end(),
                                  [](const Element &element)
                                  { return element.first == "."; });
    if(new_pos!=_elements.end())
      _elements.erase(new_pos);
  }
}

Path::operator hdf5::Path()
{
  if(is_unique(*this))
  {
    //get all object names from the NeXus path
    std::list<std::string> object_names;
    std::transform(begin(),end(),std::back_inserter(object_names),
                   [](const Element &element) { return element.first; });

    //construct the HDF5 path from the object names
    auto iter_start = object_names.cbegin();
    bool is_absolute = false;
    if(*iter_start == "/")
    {
      is_absolute = true;
      std::advance(iter_start,1);
    }
    hdf5::Path h5path(iter_start,object_names.cend());
    h5path.absolute(is_absolute);
    return h5path;

  }
  else
  {
    std::stringstream ss;
    ss<<"Cannot convert the NeXus path ["<<*this<<"] to an HDF5 path as it is not unique!";
    throw std::runtime_error(ss.str());
  }
}

//-------------------------------------------------------------------------
Path::Path(const boost::filesystem::path &file,
           const Path::ElementList &objects,
           const std::string &attr):
    _file_name(file.string()),
    _attribute_name(attr),
    _elements(objects)
{}

//-------------------------------------------------------------------------
Path Path::from_string(const std::string &input)
{
  return parsers::parse_path(input);
}

//-------------------------------------------------------------------------
std::string Path::to_string(const Path &p)
{
  std::stringstream str_stream;
  str_stream<<p;

  return str_stream.str();
}
           
//-------------------------------------------------------------------------
bool Path::has_filename() const noexcept
{
  return !_file_name.empty();
}

//-------------------------------------------------------------------------
bool Path::has_attribute() const noexcept
{
  return !_attribute_name.empty();
}
    
//-------------------------------------------------------------------------
boost::filesystem::path Path::filename() const noexcept
{
  return _file_name;
}
    
//-------------------------------------------------------------------------
void Path::filename(const boost::filesystem::path &file)
{
  _file_name = file.string();
}
    
//-------------------------------------------------------------------------
pni::string Path::attribute() const noexcept
{
  return _attribute_name;
}

//-------------------------------------------------------------------------
void Path::attribute(const std::string &attribute_name)
{
  _attribute_name = attribute_name;
}

//-------------------------------------------------------------------------
void Path::push_back(const Element &o)
{
  using namespace pni;
  if(is_root_element(o)&&size())
    throw value_error(PNINEXUS_EXCEPTION_RECORD,
                      "Cannot push back a root group to a non-empty path!");

  if(o.first==".")
    return;

  _elements.push_back(o);
}

//-------------------------------------------------------------------------
void Path::push_front(const Element &o)
{
  if(o.first==".")
    return;

  _elements.push_front(o);
}
    
//-------------------------------------------------------------------------
void Path::pop_front()
{
  _elements.pop_front();
}

//-------------------------------------------------------------------------
void Path::pop_back()
{
  _elements.pop_back();
}

//-------------------------------------------------------------------------
Path::Element Path::back() const
{
  return _elements.back();
}

//-------------------------------------------------------------------------
size_t Path::size() const
{
  return _elements.size();
}

//-------------------------------------------------------------------------
Path::ElementIterator Path::begin()
{
  return _elements.begin();
}

//-------------------------------------------------------------------------
Path::ElementIterator Path::end()
{
  return _elements.end();
}

//-------------------------------------------------------------------------
Path::ConstElementIterator Path::begin() const
{
  return _elements.begin();
}

//-------------------------------------------------------------------------
Path::ConstElementIterator Path::end() const
{
  return _elements.end();
}


//end of namespace
} // namespace nexus
} // namespace pni
