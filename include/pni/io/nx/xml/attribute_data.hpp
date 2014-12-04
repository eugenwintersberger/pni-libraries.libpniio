//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Jul 15, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <pni/core/types.hpp>
#include "node.hpp"
#include "object_data.hpp"


namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    //!
    //! \ingroup xml_classes
    //! \brief attribute IO 
    //! 
    //! This child class of object_data manages data IO for XML attributes.
    //! For for each attribute name a new instance of this class has to 
    //! be created. As the name of the attribute is crucial for this 
    //! class it is not default constructible.
    //! 
    class attribute_data : public object_data
    {
        private:
            string _name; //!< the name of the attribute
        public:
            // no default construction possible
            attribute_data() = delete;

            //----------------------------------------------------------------
            //! 
            //! \brief constructor
            //! 
            //! This constructor with the name of the attribute to 
            //! read or write. 
            //! 
            //! \param name attribute name
            //! 
            explicit attribute_data(const string &name);

            //----------------------------------------------------------------
            //! 
            //! \brief read data 
            //! 
            //! Read the data from an attribute attached to node parent. The 
            //! data is returned as a string where all leading and trailing 
            //! blanks have been removed.
            //! 
            //! \throws key_error if the attribute does not exist at this node
            //! \throws value_error if data is illformed 
            //! \throws parser_error in case of any other error
            //! 
            //! \param parent the parent node to which the attribute is attached
            //! \return data as string
            //! 
            virtual string read(const node &parent) const;

            //----------------------------------------------------------------
            //! 
            //! \brief write data
            //! 
            //! Write data to an attribute attached to its parent node. If the 
            //! attribute does not exist it will be created. The data is passed 
            //! as a string. The input string is not modified in any way.
            //! If the attribute has already data it will be overwritten.
            //! 
            //! \throws value_error if the data is illformed 
            //! \throws parser_error in case of any other error
            //! 
            //! \param data the string to write
            //! \param parent the parent node to which the attribute is
            //! attached
            //! 
            virtual void write(const string &data,node &parent) const;
    };

//end of namespace
}
}
}
}
