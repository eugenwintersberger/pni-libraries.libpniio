//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//  Created on: Jul 17, 2014
//      Author: Eugen Wintersberger
//
#pragma once

extern "C"{
#include<hdf5.h>
}

#include "object_imp.hpp"
#include "../../windows.hpp"

namespace pni{
namespace io{
namespace nx {
namespace h5{


    //! 
    //! \ingroup nxh5_classes
    //! \brief base class for filter implementations
    //! 
    //! This class provides the basic interface for HDF5 filters that can 
    //! be passed to a dataset constructor. All concrete filters must 
    //! implement this interface.  The idea is that a filter can be 
    //! configured before being passed to the constructor. In the 
    //! constructor the setup() method is called which applies the filter 
    //! to the dataset.
    //!
    class PNIIO_EXPORT h5filter
    {
        public:
            //===================public member functions=======================
            //! 
            //! \brief setup method 
            //!
            //! This virtual setup method must be implemented by the concrete 
            //! filter classes. The only argument of this method is the ID of 
            //! the dataset creation property list. 
            //!
            //! \throws object_error in case of problems
            //! \param plist handler to a property list
            //!
            virtual void setup(const object_imp &plist) const;
    };

//end of namespace
}
}
}
}
