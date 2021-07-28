//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jun 25, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/nexus/path/parser.hpp>
#include <pni/exceptions.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <algorithm>

namespace pni{
namespace nexus{
namespace parsers{

namespace algo = boost::algorithm;

static const std::string file_sep="://";

Path::Element get_element(const std::string &estr)
{
  using namespace pni;
  boost::regex expr("^(?<GNAME>[A-Za-z0-9_-]+)?(:(?<GTYPE>[A-Za-z0-0_-]+))?$");

  if(estr=="." || estr == "..")
    return {estr,string()};

  boost::smatch result;
  if(boost::regex_match(estr,result,expr))
  {
    string group_name = result.str("GNAME"),
        group_type = result.str("GTYPE");

    if(group_name.empty() && group_type.empty())
    {
      throw parser_error(EXCEPTION_RECORD,"Missing path element!");
    }

    return {group_name,group_type};

  }
  else
  {
    std::stringstream ss;
    ss<<"The element ["<<estr<<"] is not a valid NeXus path element!";
    throw parser_error(EXCEPTION_RECORD,ss.str());
  }
}

Path parse_path(const std::string &input)
{
  using namespace pni;

  string file_part,attribute_part;

  // -------------------------------------------------------------------
  // check for an attribute section
  // -------------------------------------------------------------------
  auto attr_sign = std::find(input.begin(),input.end(),'@');

  if(attr_sign!=input.end())
  {
    attribute_part = string(++attr_sign,input.end());
    attr_sign--;
  }

  // -------------------------------------------------------------------
  // check for file section
  // -------------------------------------------------------------------
  auto file_end = std::search(input.begin(),input.end(),
                              file_sep.begin(),file_sep.end());
  if(file_end!=input.end())
  {
    file_part = string(input.begin(),file_end);
    std::advance(file_end,2);
  }
  else
    file_end = input.begin(); //need to reset the iterator here


  // --------------------------------------------------------------------
  // manage elements
  // --------------------------------------------------------------------
  Path::ElementList elements;

  if(*file_end=='/') //check for the root group
  {
    elements.push_back({"/","NXroot"});
    std::advance(file_end,1);
  }

  string elements_part(file_end,attr_sign);

  if(!elements_part.empty())
  {
    //split all element entries in the path by /
    std::vector<string> element_strings;
    boost::split(element_strings,elements_part,
                 boost::is_any_of("/"),boost::token_compress_on);

    //there can be some empty values which we should remove from the list
    auto new_end = std::remove_if(element_strings.begin(),
                                  element_strings.end(),
                                  [](const string &value)
                                  {
      return value.empty();
                                  }
    );
    std::transform(element_strings.begin(),new_end,
                   std::back_inserter(elements),
                   get_element);
  }

  //remove possible duplicate root entries
  if(elements.size()>1)
  {
    auto iter = elements.begin();
    if(iter->first=="/" && iter->second=="NXroot")
    {
      std::advance(iter,1);
      if(iter->second=="NXroot")
      {
        elements.erase(iter);
      }
    }
  }

  return Path(file_part,elements,attribute_part);
}

//end of namespace
} // namespace parsers
} // namespace nexus
} // namespace pni
