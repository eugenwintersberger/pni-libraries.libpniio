/*
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
 * H5Filter.cpp
 *  Definition of the HDF5 filter base class.
 *
 *  Created on: Feb 7, 2012
 *      Author: Eugen Wintersberger
 */
#pragma once

extern "C"{
#include<hdf5.h>
}

namespace pni{
namespace io{
namespace nx {
namespace h5{

    //avoid namespace collisions with std
    using pni::core::string;

    /*! 
    \ingroup nxh5_classes
    \brief base class for filter implementations

    This class provides the basic interface for HDF5 filters that can be passed
    to a dataset constructor. All concrete filters must implement this
    interface.  The idea is that a filter can be configured before being passed
    to the constructor. In the constructor the setup() method is called which
    applies the filter to the dataset.
    */
    class H5Filter
    {
        public:
            //=================constructor and destructor======================
            //! default constructor
            explicit H5Filter();

            //-----------------------------------------------------------------
            //! copy constructor
            H5Filter(const H5Filter &o);

            //-----------------------------------------------------------------
            //! move constructor
            H5Filter(H5Filter &&o);

            //-----------------------------------------------------------------
            //! destructor
            virtual ~H5Filter();

            //===================assignment operators==========================

            //! copy assignment operator
            H5Filter &operator=(const H5Filter &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            H5Filter &operator=(H5Filter &&o);
       
            //===================public member functions=======================
            /*! 
            \brief setup method 

            This virtual setup method must be implemented by the concrete filter
            classes. The only argument of this method is the ID of the dataset
            creation property list. In cases of errors
            pni::io::nx::nxfilter_error should be thrown.
            \throw pni::io::nx::nxfilter_error in case of errors
            \param id id of the
            */
            virtual void setup(hid_t id) const{}

    };

//end of namespace
}
}
}
}
