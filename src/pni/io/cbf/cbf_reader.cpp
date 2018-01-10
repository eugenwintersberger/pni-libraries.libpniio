//
// Implementation of class CBFReader
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
// Created on: Apr 19, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/io/cbf/cbf_reader.hpp>
#include <pni/io/strutils.hpp>
#include <pni/core/error.hpp>
#include <pni/core/types.hpp>

//need to use regular expressions from boost
#include<boost/regex.hpp>


namespace pni{
namespace io{

//================implementation of constructors and destructor========
//implementation of the default constructor
cbf_reader::cbf_reader():image_reader()
{
  _set_binary();
}

//---------------------------------------------------------------------
//implementation of the standard constructor
cbf_reader::cbf_reader(const pni::core::string &fname):
            image_reader(fname,true)
{
  //here the file is immediately opened  - we have to parse the
  //header to obtain information about the data
  _parse_file();

}

//----------------------------------------------------------------
void cbf_reader::close()
{
  //close the stream
  data_reader::close();
  //reset data offset
  _data_offset = 0;
  //clear the _image_info vector
  _image_info.clear();
}

//-----------------------------------------------------------------
void cbf_reader::open()
{
  close();
  data_reader::open();
  _parse_file();
}

//-----------------------------------------------------------------
size_t cbf_reader::nimages() const
{
  return _image_info.size();
}

//-----------------------------------------------------------------
image_info cbf_reader::info(size_t i) const
{
  return _image_info[i];
}

//---------------------------------------------------------------------
//implementation of the destructor
cbf_reader::~cbf_reader()
{ }

//===============implemenetation of private methods====================
void cbf_reader::_parse_file()
{
  using namespace pni::core;
  char linebuffer[1024];
  std::ifstream &_istream = _get_stream();

  boost::regex header_convention("^_array_data.header_convention.*");
  boost::regex regex_sls("SLS");
  boost::regex regex_dectris("DECTRIS");
  boost::regex regex_pilatus("PILATUS");
  boost::regex quoted_text("\".*\"");
  boost::cmatch match;

  while(!_istream.eof())
  {
    _istream.getline(linebuffer,1024);
    if(boost::regex_match(linebuffer,match,header_convention)){
      //extract the convention string from the header
      //convention
      boost::regex_search(linebuffer,match,quoted_text);
      if(boost::regex_search(match.str(0),regex_sls)||
          boost::regex_search(match.str(0),regex_dectris) ||
          boost::regex_search(match.str(0),regex_pilatus))
      {
        _data_offset = cbf::dectris_reader::read_header(_istream,
                                                        _image_info,_compression_type);
        _detector_vendor = cbf::vendor_id::DECTRIS;
        return;
      }else{
        //should raise an exception here
        throw file_error(EXCEPTION_RECORD,"Unknown CBF style!");
      }
    }
  }

  if(_istream.eof())
    throw file_error(EXCEPTION_RECORD,
                     "File is most probably not a CBF file");
}


//end of namespace
}
}

