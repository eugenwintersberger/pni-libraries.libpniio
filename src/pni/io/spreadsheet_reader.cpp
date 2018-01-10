//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 30, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
          

#include <pni/io/spreadsheet_reader.hpp>

namespace pni{
namespace io{

//========implementation of private member functions===========================
void spreadsheet_reader::_append_column(const column_info &i)
{
  _columns_info.push_back(i);
}

column_info spreadsheet_reader::_get_column(size_t i) const
{
  return _columns_info.at(i);
}

column_info spreadsheet_reader::_get_column(const pni::core::string &n) const
{
  using namespace pni::core;
  size_t i=0;
  for(auto c: _columns_info)
  {
    if(c.name() == n)
      return _get_column(i);

    //increment column counter
    i++;
  }

  throw key_error(EXCEPTION_RECORD,"Column ["+n+"] not found!");

  return column_info(); //just to get rid of compiler warning
}

//============constructors and destructor==================================
//default constructor implementation
spreadsheet_reader::spreadsheet_reader():data_reader(){}

//-------------------------------------------------------------------------
//move constructor implementation
spreadsheet_reader::spreadsheet_reader(spreadsheet_reader &&o):
            data_reader(std::move(o)),
            _columns_info(std::move(o._columns_info)),
            _nrec(o._nrec)
{
  o._nrec = 0;
}

//-------------------------------------------------------------------------
//standard constructor implementation
spreadsheet_reader::spreadsheet_reader(const pni::core::string &n):
            data_reader(n)
{}

//-------------------------------------------------------------------------
//destructor implementation
spreadsheet_reader::~spreadsheet_reader()
{}

//=====================assignment operators================================
//move assignment operator implementation
spreadsheet_reader &spreadsheet_reader::operator=(spreadsheet_reader &&r)
{
  if(this == &r) return *this;

  data_reader::operator=(std::move(r));
  _columns_info = std::move(r._columns_info);
  _nrec = r._nrec;
  r._nrec = 0;
  return *this;
}

//=====================public methods implementation=======================
bool spreadsheet_reader::has_column(const pni::core::string &name) const
{
#ifdef NOFOREACH
  for(auto iter = this->begin();iter!=this->end();++iter)
  {
    auto ci = *iter;
#else
    for(auto ci: *this)
    {
#endif
      if(ci.name() == name) return true;
    }

    return false;
  }

  //-------------------------------------------------------------------------
  size_t spreadsheet_reader::column_index(const pni::core::string &name) const
  {
    using namespace pni::core;
    size_t index = 0;
#ifdef NOFOREACH
    for(auto iter = this->begin();iter!=this->end();++iter)
    {
      auto ci = *iter;
#else
      for(auto ci: *this)
      {
#endif
        if(ci.name() == name) return index++;
      }

      //throw exception if the column name does not exist
      exception_record r(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION);
      throw key_error(r,"Column with name ["+name+"] does not exist!");

      return 0; //make the compiler happy - a value is returned.
    }

//end of namespace
}
}
