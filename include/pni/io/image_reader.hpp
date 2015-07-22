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
//
// Created on: Apr 23, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <pni/core/types.hpp>
#include "data_reader.hpp"
#include "image_info.hpp"

namespace pni{
namespace io{

    //! 
    //! \ingroup image_io
    //! \brief base class for image readers
    //!
    //! The image_reader class provides the basic functionality for all other
    //! image readers. It opens the file and provides a stream from which to
    //! read data. ImageReader objects cannot be copied or copy-assigned. 
    //! However, they can be moved using std::move. 
    //!
    //! Like data_reader (from which it is derived) an ImageReader object 
    //! cannot be instantiated using this class. All constructors and 
    //! assignment operators are thus protected making them only available 
    //! to derived classes.
    //!
    class image_reader:public data_reader
    {
        protected:
            //===================constructors and destructor===================
            //! default constructor
            image_reader();
            //! copy constructor is deleted
            image_reader(const image_reader &) = delete;
            //! move constructor
            image_reader(image_reader &&r);
            //! standard constructor taking the filename as string object
            explicit image_reader(const pni::core::string &fname,
                                  bool binary=false);
            
            //==================assignment operators===========================
            //!copy assignment is deleted
            image_reader &operator=(const image_reader &r) = delete;

            //! move assignment operator
            image_reader &operator=(image_reader &&r);

        public:
            //! destructor
            virtual ~image_reader();


            //====================methods======================================
            //!
            //! \brief get number of images
            //!
            //! Returns the number of images stored in the file. This methods
            //! reflects the fact that many image formats can hold more than 
            //! one image in a single file (CBF, TIFF). Although this feature 
            //! is hardly used for experiments it should be taken into 
            //! account.  This is a virtual function which must be 
            //! implemented by the concrete reader classes.
            //!
            //! \return number of images
            //!
            virtual size_t nimages() const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief get image info
            //!
            //! Return an instance of ImageInfo with the information of image 
            //! i in the image stack. This is a virtual function which must 
            //! be implemented by the concrete reader classes.
            //!
            //! \param i index of the image
            //! \return vector with ImageInfo objects
            //!
            virtual image_info info(size_t i) const = 0;

            //-----------------------------------------------------------------
            //!
            //! \brief method to read a single channel
            //!
            //! This method returns an object determined by ArrayType holding 
            //! the data from channel c (default is 0) of image i in the file.  
            //! This method must be implemented by all child classes of 
            //! ImageReader. It is assumed that the method will allocate 
            //! enough memory and configure the returning object appropriately.
            //!
            //! \param i index of the image in the file
            //! \param c (default = 0) image channel to read
            //! \return instance of ArrayType holding the channel data
            //!
            template<typename ATYPE> ATYPE image(size_t,size_t c) 
            {
                using namespace pni::core;
                throw not_implemented_error(EXCEPTION_RECORD,
                        "Method not implemented!");

                return ATYPE(); //just to make the compiler happy
            }
           
            //-----------------------------------------------------------------
            //!
            //! \brief method to read a single image channel
            //!
            //! This method reads the data from channle c (default = 0) of 
            //! image i in the file and stores it in an Array template 
            //! supplied by the user.  The array must provide enough space to 
            //! hold the data otherwise exceptions will be thrown. The 
            //! addvantage of this method is that it does not waste time 
            //! with memory allocation. It is thus useful in cases where data 
            //! from many files of same size must be read.
            //!
            //! \param array array where to store the data
            //! \param i index of the image in the file
            //! \param c (default = 0) index of the channel from which to read data.
            //!
            template<typename ATYPE> 
                void image(ATYPE &,size_t,size_t c) 
            {
                using namespace pni::core;
                throw not_implemented_error(EXCEPTION_RECORD,
                        "Method not implemented!");
            }

    };


//end of namepsace
}
}
