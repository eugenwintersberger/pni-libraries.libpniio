//
// (c) Copyright 2016 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Mar 04, 2016
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "nxpath/nxpath.hpp"
#include "nxlink_type.hpp"
#include "nxlink.hpp"
#include "nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{
    
    template<nximp_code IMPID> class nxlink
    {
        public:
            using parent_type = typename nxobject_trait<IMPID>::group_type;
            using object_type = typename nxobject_trait<IMPID>::object_type;
            using link_type = nxlink<IMPID>;
        private:
            parent_type _parent;
            pni::core::string  _name;
        public:
            nxlink():
                _parent{},
                _name{}
            {}

            nxlink(const parent_type &parent,
                   const pni::core::string &name):
                _parent(parent),
                _name(name)
            {}

            nxlink(const parent_type &parent,size_t index):
                _parent(parent),
                _name(link_name(parent,index))
            {}
                   
    
            pni::core::string filename() const noexcept
            {
                return _parent.filename();
            }

            pni::core::string name() const noexcept
            {
                return _name;
            }

            object_type parent() const noexcept
            {
                return _parent;
            }


            const nxpath& target_path() const
            {
                return link_target(_parent,_name);
            }

            nxlink_status status() const
            {
                return link_status(_parent,_name);
            }

            nxlink_type type() const 
            {
                return link_type(_parent,_name);
            }

            bool is_valid() const
            {
                if(status() == nxlink_status::VALID)
                    return true;
                else
                    return false;
            }

    };


//end of namespace
}
}
}
