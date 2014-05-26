//
// Declaration of the basic NXFilter template
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
// Created on: Aug 8, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#pragma once

#include <pni/core/types.hpp>

#include "nximp_map.hpp"


namespace pni{
namespace io{
namespace nx{
    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    //! 
    //! \ingroup nexus_utilities
    //! \brief Filter object
    //!
    //! Base class for all filter objects in the Nexus world.
    //!
    template<typename FIMP> class nxfilter
    {
        public:
            typedef FIMP imp_type;
            typedef nxfilter<imp_type> filter_type;
        private:
            imp_type _imp; //!< filter implementation object
        protected:

            /*! 
            \brief get non-const ref

            This returns a non constant refernce to the implementation.  This is
            necessary for derived classes that want to export some functionality
            of the implementation object to derived clases.  This makes
            perfectly sense since the class hierachrchy is not directly for
            encapsulation but only for avoiding writing work.
            \return reference to implementation object
            */
            imp_type &imp(){ return _imp; }
        public:
            //================constructors  and destructor======================
            //! default constructor
            explicit nxfilter():_imp() { }

            //------------------------------------------------------------------
            //! copy constructor
            nxfilter(const filter_type &f):_imp(f._imp) { }
            
            //------------------------------------------------------------------
            //! copy implementation constructor 
            nxfilter(const imp_type &i):_imp(i) { }

            //-----------------------------------------------------------------
            //! move constructor
            nxfilter(filter_type &&f):_imp(std::move(f._imp)) { }
            
            //-----------------------------------------------------------------
            //! move constructor from implementation
            nxfilter(imp_type &&i):_imp(std::move(i)) { }

            //-----------------------------------------------------------------
            //! destructor
            virtual ~nxfilter() { }

            //==================assignment operators===========================
            //! copy assignment operator
            filter_type &operator=(const filter_type &f)
            {
                if(this != &f) _imp = f._imp;
                return *this;
            }

            //-----------------------------------------------------------------
            //! move assignment operator
            filter_type &operator=(filter_type &&f)
            {
                if(this != &f) _imp = std::move(f._imp);
                return *this;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief return const ref to implementation

            This method returns a const reference to the implementation 
            of the filter object. 
            \return const ref. to implementation
            */
            const imp_type& imp() const { return _imp; }

    };

    //end of namespace
}
}
}


