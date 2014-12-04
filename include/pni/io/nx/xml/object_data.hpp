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
// Created on: Dec 4, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "node.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    //!
    //! \ingroup xml_classes
    //! \brief abstract object data io
    //!
    //! This class provides the abtrasct interface for object data io. 
    //! All data in XML is encoded as strings. The object_data interface
    //! provides two virtual methods: read and write which read and write
    //! strings to an XML object. All objects are currently described by 
    //! nodes. 
    //! 
    class object_data
    {
        public:
            //!
            //! \brief read data
            //! 
            //! Read data as string from an XML object. If the object has 
            //! no data a value_error exception is thrown. 
            //!
            //! \throws value_error if the node has no data
            //! 
            //! \param n the node object from which to read data
            //! \return string with node data
            //! 
            virtual string read(const node &n) const = 0;

            //----------------------------------------------------------------
            //!
            //! \brief write data
            //! 
            //! Write data as a string to the node. If the data string is 
            //! empty nothing will be written. 
            //! 
            //! \param n node where to write the data
            //! \param data a string with the encoded data
            //!
            virtual void write(const node &n,const string &data) const = 0;
    };


}
}
}
}
