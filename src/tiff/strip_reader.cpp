/*
 * Implementation of class TIFFStripReader
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of class TIFFStripReader.
 *
 * Created on: Jun 22, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include <pni/core/exceptions.hpp>
#include "strip_reader.hpp"

namespace pni {
namespace io {
namespace tiff {
    //======================implementation of constructors and destructor======
    //implementation of the default constructor
    strip_reader::strip_reader() { }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    strip_reader::strip_reader(const strip_reader &o):
        _offsets(o._offsets),
        _byte_cnts(o._byte_cnts),
        _bits_per_channel(o._bits_per_channel),
        _channel_types(o._channel_types)
    { }

    //-------------------------------------------------------------------------
    //implementation of move constructor
    strip_reader::strip_reader(strip_reader &&o):
        _offsets(std::move(o._offsets)),
        _byte_cnts(std::move(o._byte_cnts)),
        _bits_per_channel(std::move(o._bits_per_channel)),
        _channel_types(std::move(o._channel_types))
    { }

    //------------------------------------------------------------------------
    //implementation of the standard constructor
    strip_reader::strip_reader(const std::vector<size_t> &offsets,
                             const std::vector<size_t> &byte_counts,
                             const std::vector<size_t> &bits_per_channel,
                             const std::vector<type_id_t> &channel_types):
        _offsets(offsets),
        _byte_cnts(byte_counts),
        _bits_per_channel(bits_per_channel),
        _channel_types(channel_types)
    { }

    //-------------------------------------------------------------------------
    //implementation of the destructor
    strip_reader::~strip_reader() 
    { }

    //=========================implementation of assignment operators==========
    //implementation of copy assignment
    strip_reader &strip_reader::operator=(const strip_reader &o)
    {
        if(this == &o) return *this;

        _offsets = o._offsets;
        _byte_cnts = o._byte_cnts;
        _bits_per_channel = o._bits_per_channel;
        _channel_types = o._channel_types;
        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of move assignment
    strip_reader &strip_reader::operator=(strip_reader &&o)
    {
        if(this == &o) return *this;

        _offsets = std::move(o._offsets);
        _byte_cnts = std::move(o._byte_cnts);
        _bits_per_channel = std::move(o._bits_per_channel);
        _channel_types = std::move(o._channel_types);
        return *this;
    }

    //======================implementation of public methods===================
    strip_reader strip_reader::create(std::ifstream &stream,const ifd &image_dir,
                                    const image_info &info)
    {
       return strip_reader(image_dir["StripOffsets"].value<size_t>(stream),
                           image_dir["StripByteCounts"].value<size_t>(stream),
                           info.bits_per_channel(),
                           info.types_per_channel());
    }

   
    //-------------------------------------------------------------------------
    //output operator
    std::ostream &operator<<(std::ostream &o,const strip_reader &r)
    {
        for(size_t i=0;i<r._bits_per_channel.size();i++)
        {
            o<<"channel "<<i<<" of type "<<r._channel_types[i];
            o<<" with "<<r._bits_per_channel[i]<<" bits"<<std::endl;
        }

        o<<"Total number of strip: "<<r._offsets.size()<<std::endl;
        for(size_t i=0;i<r._offsets.size();i++)
        {
            o<<"strip "<<i<<" at offset "<<r._offsets[i];
            o<<" of size "<<r._byte_cnts[i]<<std::endl;
        }
        return o;
    }



//end of namespace
}
}
}
