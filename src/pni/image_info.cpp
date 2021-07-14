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
// ImageInfo class implementation
//
// Created on: Apr 23, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <pni/image_info.hpp>

namespace pni{
    
using namespace pni;

//---------------------------------------------------------------------
//implementation of the standard constructor
image_info::image_info(size_t nx,size_t ny):
            _nx(nx),
            _ny(ny),
            _channel_info()
{}

//-------------------------------------------------------------------------
std::vector<size_t> image_info::bits_per_channel() const
{
  std::vector<size_t> result;
  for(auto c: _channel_info)
  {
    result.push_back(c.bits());
  }

  return result;
}

//-------------------------------------------------------------------------
std::vector<type_id_t> image_info::types_per_channel() const
{
  std::vector<type_id_t> types;

  for(auto c: _channel_info)
  {

    types.push_back(c.type_id());
  }

  return types;
}

//---------------------------------------------------------------------
void image_info::append_channel(const image_channel_info &i)
{
  _channel_info.push_back(i);
}

//---------------------------------------------------------------------
image_channel_info image_info::get_channel(size_t i) const
{
  return _channel_info[i];
}

//=================implementation of the output operator===============
std::ostream &operator<<(std::ostream &o,const image_info &i)
{
  o<<"Image of size ("<<i.nx()<<" x "<<i.ny()<<"):"<<std::endl;
  o<<"Total pixels:   "<<i.npixels()<<std::endl;
  o<<"Bits per pixel: "<<i.bit_per_pixel()<<std::endl;
  o<<"Number of channels: "<<i.nchannels()<<std::endl;
  o<<"Channel information: "<<std::endl;
  for(size_t n=0;n<i.nchannels();n++)
  {
    o<<"channel "<<n<<" of type "<<i.get_channel(n).type_id();
    o<<std::endl;
  }
  return o;
}


//end of namespace
}
