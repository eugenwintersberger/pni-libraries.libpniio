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
// Created on: Jun 26, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <sstream>
#include <pni/nexus/path/utils.hpp>
#include <pni/nexus/path/parser.hpp>
#include <pni/error.hpp>
#include <algorithm>


namespace pni{
namespace io{
namespace nexus{

void throw_if_empty(const Path::Element &e,
                    const pni::exception_record &r)
{
  using namespace pni;
  if(e.first.empty()&&e.second.empty())
    throw value_error(r,"Both name and type are empty!");
}

//--------------------------------------------------------------------------
Path::Element object_element(const std::string &name,const std::string &type)
{
  using namespace pni;
  Path::Element e = Path::Element{name,type};
  throw_if_empty(e,EXCEPTION_RECORD);

  return e;
}

//--------------------------------------------------------------------------
void split_path(const Path &p,size_t s,Path &p1,Path &p2)
{
  using namespace pni;
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
  using namespace pni;
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
  using namespace pni;
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
  using namespace pni;
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
  pni::string buffer;
  i>>buffer;
  p = Path::from_string(buffer);
  return i;
}
    
//-------------------------------------------------------------------------
bool match(const Path::Element &a,const Path::Element &b)
{
  //if both elements are complete they must be equal
  if(is_complete(a) && is_complete(b))
    return a==b;

  // both have their name element set - but ony one the class
  if(has_name(a) && has_name(b))
  {
    //if both have their names set we can exclude here the case that also
    // both have their class set (in this case they would be complete an
    // already handled by the above case. So we only have to check
    // the names:
    return a.first == b.first;
  }

  // both have their class set - but only on the name
  if(has_class(a) && has_class(b))
  {
    //similar to above in this case we only have to check for class
    //equality
    return a.second == b.second;
  }

  //
  // if only one of the two elements has its name set we have to check the
  // the class
  //
//  if( (a.first.empty() && !b.first.empty()) ||
//      (!a.first.empty() && b.first.empty()) )
//  {
//    if(a.second == b.second)
//      return true;
//  }
//  else
//  {
//    return a.first == b.first && a.second == b.second;
//  }

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

bool is_unique(const Path &path)
{
  return std::all_of(path.begin(),path.end(),
                     [](const Path::Element &element) { return !element.first.empty() ;});
}

} // namespace nexus
} // namespace io
} // namespace pni
