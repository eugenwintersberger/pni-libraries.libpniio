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
//************************************************************************
//
//  Created on: Jul 28, 2011
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

extern "C"{
#include <hdf5.h>
}

#include <iostream>
#include <vector>

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>

#include "h5_error.hpp"

namespace pni {
namespace io {
namespace nx {
namespace h5 {


using namespace pni::core;
//avoid namespace collisions with std
using pni::core::exception;
using pni::core::string;


    //! 
    //! \ingroup nxh5_error_classes
    //! \brief HDF5 error stack
    //!
    //! Class HDF5ErrorStack provides a simple object oriented interface to 
    //! the HDF5 error stack.
    //!
    class h5_error_stack 
    {
        public:
            typedef h5_error value_type;
            typedef std::vector<value_type> container_type;
            typedef container_type::iterator iterator;
            typedef container_type::const_iterator const_iterator;
        private:
            //! id of the error stack
            hid_t _stack_id;      
            //! vector with error records on this stack
            container_type _errors; 

        public:
            //-----------------------------------------------------------------
            //! 
            //! \brief default constructor
            //! 
            h5_error_stack() noexcept;

            //-----------------------------------------------------------------
            //! 
            //! \brief copy constructor
            //! 
            h5_error_stack(const h5_error_stack &s);

            //-----------------------------------------------------------------
            //!
            //! \brief default destructor
            //! 
            virtual ~h5_error_stack();

            //-----------------------------------------------------------------
            //!
            //! \brief copy constructor
            //!
            h5_error_stack &operator=(const h5_error_stack &s);

            //-----------------------------------------------------------------
            //! 
            //! \brief get number of errors
            //!
            //! Returns the total number of HDF5 errors in the stack.
            //! \return number of errors
            //!
            ssize_t number_of_errors() const{ return _errors.size(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief fill stack
            //!
            //! Reads error messages from the current HDF5 error stack and 
            //! add them to the stack.	
            //!
            void fill();

            //-----------------------------------------------------------------
            //! 
            //! \brief append error
            //! 
            //! Appends a single error to the stack.
            //! \param e HDF5 error record
            //!
            void append(const h5_error &e);

            //-----------------------------------------------------------------
            //!
            //! \brief iterator to first error
            //! 
            const_iterator begin() const;

            //----------------------------------------------------------------
            //!
            //! \brief iterator to last element
            //! 
            const_iterator end() const;


    };
            
    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_error_classes
    //! \brief ostream operator
    //!
    std::ostream &operator<<(std::ostream &o, const h5_error_stack &s);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_error_classes
    //! \brief Walker functins to read over error messages
    //! 
    //! \param n undocumented
    //! \param eptr pointer to error stack
    //! \param client_data data passed by the client to the walker code
    //! \return HDF5 error code
    //! 
extern "C" herr_t _error_walker(unsigned n,const H5E_error2_t *eptr,
                                void *client_data);

    //------------------------------------------------------------------------
    //!
    //! \ingroup nxh5_error_classes
    //! \brief return HDF5 error messages
    //!
    //! Returns all the error messages in the actual HDF5 error stack as a 
    //! string. 
    //! 
    //! \return error messages
    //!
    string get_h5_error_string();


//end of namespace
}
}
}
}
