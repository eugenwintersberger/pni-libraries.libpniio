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
#include <pni/io/nexus/path/utils.hpp>
#include <pni/io/nexus/path/parser.hpp>
#include <pni/core/error.hpp>


namespace pni{
namespace io{
namespace nexus{

void throw_if_empty(const Path::Element &e,
                    const pni::core::exception_record &r)
{
  using namespace pni::core;
  if(e.first.empty()&&e.second.empty())
    throw value_error(r,"Both name and type are empty!");
}

//--------------------------------------------------------------------------
Path::Element object_element(const std::string &name,const std::string &type)
{
  using namespace pni::core;
  Path::Element e = Path::Element{name,type};
  throw_if_empty(e,EXCEPTION_RECORD);

  return e;
}

//--------------------------------------------------------------------------
void split_path(const Path &p,size_t s,Path &p1,Path &p2)
{
  using namespace pni::core;
  if(s>=p.size())
  {
    std::stringstream ss;
    ss<<"Split index "<<s<<" exceeds input path size ";
    ss<<p.size()<<"!";
    throw index_error(EXCEPTION_RECORD,ss.str());
  }
  auto split_iter = p.begin();
  std::advance(split_iter,s);

  Path::ElementList gp1(s),gp2(p.size()-s);
  std::copy(p.begin(),split_iter,gp1.begin());
  std::copy(split_iter,p.end(),gp2.begin());

  //if the original path was absolute also the first part of the two
  //must be absolute
  p1 = Path(p.filename(),gp1,"");
  p2 = Path("",gp2,p.attribute());
}

//--------------------------------------------------------------------------
void split_last(const Path &p,Path &gpath,Path &opath)
{
  split_path(p,p.size()-1,gpath,opath);
}

//--------------------------------------------------------------------------
bool has_file_section(const Path &p)
{
  if(p.filename().empty()) return false;
  return true;
}

//-------------------------------------------------------------------------
bool has_attribute_section(const Path &p)
{
  if(p.attribute().empty()) return false;
  return true;
}
    
//-------------------------------------------------------------------------
bool is_root_element(const Path::Element &e)
{
  using namespace pni::core;
  throw_if_empty(e,EXCEPTION_RECORD);

  return (has_name(e) && (e.first=="/") &&
      has_class(e) && (e.second=="NXroot"));
}

//--------------------------------------------------------------------------
bool is_absolute(const Path &p)
{
  return is_root_element(p.front());
}

//--------------------------------------------------------------------------
bool has_name(const Path::Element &e)
{
  return !e.first.empty();
}

//--------------------------------------------------------------------------
bool has_class(const Path::Element &e)
{
  return !e.second.empty();
}

//--------------------------------------------------------------------------
bool is_complete(const Path::Element &e)
{
  using namespace pni::core;
  throw_if_empty(e,EXCEPTION_RECORD);

  return has_name(e)&&has_class(e);
}

//--------------------------------------------------------------------------
bool is_empty(const Path &p)
{
  return !has_file_section(p) &&
      !has_attribute_section(p) &&
      (p.size() == 0);
}

//--------------------------------------------------------------------------
Path join(const Path &a,const Path &b)
{
  using namespace pni::core;
  if(is_empty(a) && is_empty(b)) return Path();

  if(is_empty(a)) return b;
  if(is_empty(b)) return a;

  if(has_attribute_section(a))
    throw value_error(EXCEPTION_RECORD,"First path must not have an "
                      "attribute section!");

  if(is_absolute(b))
    throw value_error(EXCEPTION_RECORD,"Second path must not be"
                      " absolute!");

  if(has_file_section(b))
    throw value_error(EXCEPTION_RECORD,"Second path must not have a "
                      "file section!");

  //ok - here we are ready to do the join
  Path::ElementList elements;

  for(auto e: a) elements.push_back(e);
  for(auto e: b) elements.push_back(e);

  return Path(a.filename(),elements,b.attribute());
}


//--------------------------------------------------------------------------
std::istream &operator>>(std::istream &i,Path &p)
{
  pni::core::string buffer;
  i>>buffer;
  p = Path::from_string(buffer);
  return i;
}

//========================================================================
// Utility functions for the implementation of the element equality check
//
bool rule_1(const Path::Element &a,const Path::Element &b)
{
  if(is_complete(a) && is_complete(b))
    return (a.first==b.first) && (a.second == b.second);
  else
    return false;
}

//------------------------------------------------------------------------
bool rule_2_applies(const Path::Element &a,const Path::Element &b)
{
  if(!a.second.empty() && !b.second.empty())
  {
    if(a.first.empty() && !b.first.empty())
      return true;
    else if(!a.first.empty() && b.first.empty())
      return true;
    else
      return false;
  }

  return false;
}

//------------------------------------------------------------------------
inline bool both_no_name(const Path::Element &a,const Path::Element &b)
{
  return a.first.empty() && b.first.empty();
}

//------------------------------------------------------------------------
inline bool both_no_class(const Path::Element &a,const Path::Element &b)
{
  return a.second.empty() && b.second.empty();
}

//------------------------------------------------------------------------
inline bool both_have_name(const Path::Element &a,const Path::Element &b)
{
  return !a.first.empty() && !b.first.empty();
}

//------------------------------------------------------------------------
inline bool both_have_class(const Path::Element &a,const Path::Element &b)
{
  return !a.second.empty() && !b.second.empty();
}

//------------------------------------------------------------------------
bool rule_3_applies(const Path::Element &a,const Path::Element &b)
{
  if(both_no_name(a,b) && both_have_class(a,b))
    return true;
  else if(both_have_name(a,b) && both_no_class(a,b))
    return true;
  else
    return false;
}

//------------------------------------------------------------------------
bool rule_3(const Path::Element &a,const Path::Element &b)
{
  if(both_no_name(a,b))
    return a.second == b.second;
  else if(both_no_class(a,b))
    return a.first == b.first;
  else
    return false;
}
    
//-------------------------------------------------------------------------
bool match(const Path::Element &a,const Path::Element &b)
{
  //if both are complete paths we have to check the equality of
  //each of their elements
  if(rule_1(a,b)) return true;

  if(rule_2_applies(a,b))
    return a.second == b.second;

  if(rule_3_applies(a,b)) return rule_3(a,b);

  return false;
}
    
//-------------------------------------------------------------------------
bool match(const Path &a,const Path &b)
{
  //paths of different size cannot match
  if(a.size() != b.size()) return false;

  //iterate over all elements of the object sections
  for(auto liter = a.begin(),riter = b.begin();
      liter!=a.end();
      ++liter,++riter)
  {
    if(!match(*liter,*riter)) return false;
  }

  //finally we need to check the attribute section
  if(a.attribute() != b.attribute()) return false;

  return true;
}

//-------------------------------------------------------------------------
bool match(const std::string &a,const std::string &b)
{
  return match(Path::from_string(a),Path::from_string(b));
}

//-------------------------------------------------------------------------
bool operator==(const Path::Element &a,const Path::Element &b)
{
  if(a.first != b.first) return false;

  if(a.second != b.second) return false;

  return true;
}

//-------------------------------------------------------------------------
bool operator!=(const Path::Element &a,const Path::Element &b)
{
  return !(a==b);
}

//--------------------------------------------------------------------------
bool operator==(const Path &lhs,const Path &rhs)
{
  if(lhs.filename()!=rhs.filename()) return false;

  if(lhs.size() != rhs.size()) return false;

  if(lhs.attribute() != rhs.attribute()) return false;

  return std::equal(lhs.begin(),lhs.end(),rhs.begin());
}

//--------------------------------------------------------------------------
bool operator!=(const Path &lhs,const Path &rhs)
{
  return !(lhs == rhs);
}
    
//-------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &stream,const Path::Element &e)
{
  stream<<e.first;
  //the colon will only be printed if the second component is not empty
  if(!e.second.empty() && !is_root_element(e) ) stream<<":"<<e.second;
  return stream;
}

//--------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &stream,const Path &p)
{
  //write the file name
  if(!p.filename().empty())
  {
    stream<<p.filename().string();

    //if the object section has some content we have to add the
    //leading :/ to the output stream, denoting the end of the
    //file section
    if(p.size()) stream<<":/";
  }

  //write the object section
  size_t index = 0;
  for(auto e: p)
  {
    stream<<e;
    if((index++ < p.size()-1) && !is_root_element(e))
      stream<<"/";
  }

  //write the attribute section
  if(!p.attribute().empty()) stream<<"@"<<p.attribute();

  return stream;

}

} // namespace nexus
} // namespace io
} // namespace pni
