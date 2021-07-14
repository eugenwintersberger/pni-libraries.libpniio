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
// Created on: Apr 23, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <iostream>
#include <vector>
#include <numeric>

#include <pni/types.hpp>
#include <pni/error.hpp>
#include <pni/image_channel_info.hpp>
#include <pni/windows.hpp>

namespace pni{
namespace io{
       
//!
//! @brief image information type
//!
//! ImageInfo holds basic information about a particular image.
//!
class PNINEXUS_EXPORT image_info
{
  private:
    //! number of pixels in x-direction
    size_t _nx;
    //! number of pixels in y-direction
    size_t _ny;
    //! channel information
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
    std::vector<image_channel_info> _channel_info;
#ifdef _MSC_VER
#pragma warning(default:4251)
#endif
  public:
    //!
    //! @brief default constructor
    //!
    image_info():
      _nx(0),
      _ny(0),
      _channel_info(0)
    {}

    //!
    //! @brief constructor
    //!
    //! @param nx number of pixels in x-direction
    //! @param ny number of pixels in y-direction
    //!
    image_info(size_t nx,size_t ny);

    //!
    //! @brief move constructor
    //!
    //! Use compiler provided default implementation.
    //!
    image_info(image_info &&i) = default;

    //!
    //! @brief copy constructor
    //!
    //! Use compiler provided default implementation
    //!
    image_info(const image_info &i) = default;

    //!
    //! @brief move assignment operator
    //!
    //! Use compiler provided default implementation
    //!
    image_info &operator=(image_info &&i) = default;

    //!
    //! @brief copy assignment operator
    //!
    //! Use compiler provided default implementation
    //!
    image_info &operator=(const image_info &i) = default;

    //====================general class methods========================
    //!
    //! @brief get pixels along x
    //!
    //! @return number of pixels in x-direction (the slow direction)
    //!
    size_t nx() const noexcept { return _nx; }

    //-----------------------------------------------------------------
    //!
    //! @brief get pixels along y
    //!
    //! @return number of pixels in y-direction (the fast direction)
    //!
    size_t ny() const noexcept { return _ny; }

    //-----------------------------------------------------------------
    //!
    //! @brief get total number of pixels
    //!
    //! Computes the total number of pixels of the image (nx*ny).
    //! @return total number of pixels.
    //!
    size_t npixels() const noexcept { return _nx*_ny;}

    //-----------------------------------------------------------------
    //!
    //! @brief get number of bits per pixel
    //!
    //! Return the number of bits per pixel.
    //! @return number of bits per pixel
    //!
    size_t bit_per_pixel() const
    {
      std::vector<size_t> bpc = bits_per_channel();
      return std::accumulate(bpc.begin(),
                             bpc.end(),0);
    }

    //-----------------------------------------------------------------
    //!
    //! @brief get bits per channel
    //!
    //! Return the number of bits used to store data for each channel.
    //! @return vector with the number of bits for each channel
    //!
    std::vector<size_t> bits_per_channel() const;

    //-----------------------------------------------------------------
    //!
    //! @brief get types per channel
    //!
    //! Return a vector with the different types per channel.
    //! @return vector with data types for each channel
    //!
    std::vector<pni::type_id_t> types_per_channel() const;

    //-----------------------------------------------------------------
    //!
    //! @brief get number of channels
    //!
    //! @return number of channels
    //!
    size_t nchannels() const { return _channel_info.size(); }

    //-----------------------------------------------------------------
    //!
    //! @brief append a new channel
    //!
    //! Append information about a channel to the image information
    //! class.
    //! @param i channel information
    //!
    void append_channel(const image_channel_info &i);

    //-----------------------------------------------------------------
    //!
    //! @brief get channel information
    //!
    //! Return the channel information for channle i.
    //! @param i channel number
    //! @return channel information.
    //!
    image_channel_info get_channel(size_t i) const;



};

//!
//! @brief brief output operator for ImageInfo
//! @relates image_info
//!
//! Overloaded output stream operator for the ImageInfo type.
//! @param o reference to output stream
//! @param i reference to an instance of ImageInfo
//! @return reference to the output stream
//!
PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &o,const image_info &i);




//end of namespace
}
}
