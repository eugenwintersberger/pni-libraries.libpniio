//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 30, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
///

#include <sstream>
#include <string>
#include <pni/fio/fio_reader.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

static const boost::regex parameter_section_re("^[[:space:]]*%p[[:space:]]*");
static const boost::regex data_section_re("^[[:space:]]*%d[[:space:]]*");
static const boost::regex key_value_re("^\\s*(?<KEY>[^=]+)\\s*=\\s*(?<VALUE>.+)\\s*");
static const boost::regex col_descriptor_re("^\\s*Col\\s+(?<INDEX>\\d+)\\s+(?<NAME>\\w+)\\s+(?<TYPE>\\w+)\\s*");
static const boost::regex data_record_re("^(?:\\s+[+-\\.0-9eE]+)+\\s*");
static const boost::regex data_cell_re("[+-\\.0-9eE]+");

namespace pni{

    //======================private member functions===========================
void fio_reader::_parse_file(std::ifstream &stream)
{
  pni::string line_buffer;
  boost::smatch match;

  //
  // we use a two step approach here:
  // -> in the first parser run we look for the offsets of the
  //    different sections in the file
  // -> in the second run we parse the sections
  while(!stream.eof())
  {
    //read a character
    std::getline(stream,line_buffer);
    if(boost::regex_match(line_buffer,match,parameter_section_re))
    {
      _parse_parameters(stream);
    }
    else if(boost::regex_match(line_buffer,match,data_section_re))
    {
      _parse_data(stream);

      break; //terminate the loop - the data section is the last one
    }
  }

  //reset EOF bit
  stream.clear();
}

//-------------------------------------------------------------------------
void fio_reader::_parse_parameters(std::ifstream &stream)
{
  pni::string param_name,param_value,line_buffer;
  boost::smatch match;
  //clear the parameter map
  _param_map.clear();

  //read the parameter section
  while(!stream.eof())
  {
    //read a single character form the file
    std::getline(stream,line_buffer);

    if(boost::regex_match(line_buffer,match,key_value_re))
    {
      pni::string key = match.str("KEY");
      pni::string value = match.str("VALUE");
      boost::trim(key);
      boost::trim(value);

      _param_map.insert({key,value});
    }
    else
    {
      return;	//if we encounter a non-key-value line we are done
    }
  }
}

//-------------------------------------------------------------------------
std::vector<pni::string> fio_reader::_read_data_line(const pni::string &line)
{
  boost::regex dcol("[+-]?\\d+\\.?\\d*e?[+-]?\\d*");
  std::vector<pni::string> record;

  boost::match_results<pni::string::const_iterator> imatch;
  pni::string::const_iterator start = line.begin();
  pni::string::const_iterator end   = line.end();
  while(boost::regex_search(start,end,imatch,dcol,boost::match_default))
  {
    record.push_back(imatch.str());
    start = imatch[0].second;
  }

  return record;
}

//-------------------------------------------------------------------------
void fio_reader::_parse_data(std::ifstream &stream)
{
  boost::smatch match;
  size_t nr = 0; //number of records

  pni::string line_buffer;
  std::map<int,pni::string> index_name_map;

  while(!stream.eof())
  {
    std::getline(stream,line_buffer);

    if(boost::regex_match(line_buffer,match,col_descriptor_re))
    {
      pni::string cname = match.str("NAME"),
          ctype = match.str("TYPE");
      boost::trim(cname);
      boost::trim(ctype);

      _append_column(column_info(cname,_typestr2id(ctype),std::vector<size_t>()));
      index_name_map.insert({boost::lexical_cast<int>(match.str("INDEX"))-1,cname});
      _columns.insert({cname,column_type{}});
    }
    else if(boost::regex_match(line_buffer,match,data_record_re))
    {
      size_t column_index=0;
      boost::sregex_iterator iter(line_buffer.begin(),line_buffer.end(),data_cell_re);
      boost::sregex_iterator iter_end;

      for(;iter!=iter_end;++iter,++column_index)
      {
        _columns.at(index_name_map.at(column_index)).push_back(iter->str());
      }
      nr++;
    }
  }

  //set the number of records in the file
  _nrecords(nr);
  //must be called here to clear EOF error bit
  //must be called before next call to seekg
  stream.clear();
}

//-------------------------------------------------------------------------
void fio_reader::_get_parameter_data(std::ifstream &stream,
                                     pni::string &value)
const
{
  char buffer;
  value.clear();

  while(!stream.eof())
  {
    stream.get(buffer);
    if(buffer == '\n') break;
    value.push_back(buffer);
  }
}

//=================implementation of static private methods================
pni::type_id_t fio_reader::_typestr2id(const pni::string &tstr)
{
  if(tstr == "FLOAT")
    return pni::type_id_t::FLOAT32;
  else if(tstr == "DOUBLE")
    return pni::type_id_t::FLOAT64;
  else
    return pni::type_id_t::NONE;
}

//=======================constructors and destructor=======================
//default constructor implementation
fio_reader::fio_reader():
    	    spreadsheet_reader(),
    	    _param_map(),
    	    _columns()
{}

//-------------------------------------------------------------------------
//standard constructor implementation
fio_reader::fio_reader(const pni::string &n):
            spreadsheet_reader(n),
            _param_map(),
            _columns()
{
  _parse_file(_get_stream());
}

//-------------------------------------------------------------------------
//! destructor
fio_reader::~fio_reader()
{}

//=============public memeber methods======================================
//implementation of nparameters
size_t fio_reader::nparameters() const
{
  return _param_map.size();
}
    
//-------------------------------------------------------------------------
//implementation of parameter names
std::vector<pni::string> fio_reader::parameter_names() const
{
  std::vector<pni::string> pnames;
  std::transform(_param_map.begin(),_param_map.end(),
                 std::back_inserter(pnames),
                 [](const parameter_map_type::value_type &pair){return pair.first;});

  return pnames;
}



//end of namespace
}
