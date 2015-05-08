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
// Created on: Sep 10, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include "algorithms/is_valid.hpp"
#include "algorithms/is_group.hpp"
#include "algorithms/as_group.hpp"
#include "nxobject_traits.hpp"

namespace pni{
namespace io{
namespace nx{

    //! 
    //! \ingroup nexus_lowlevel
    //! \brief flat group adapter
    //!
    //! The flat_group adapter provides a recursive view on a group and all its
    //! children. It is typically constructed with the utility function
    //! make_flat and can be used to iterate recursively over all child nodes 
    //! below a group. 
    //!
    //! A typical example would be to list the path of every object stored
    //! below a particular group
    /*!
    \code
    auto group = get_object(file.root(),"/:NXentry");
    auto flat = make_flat(group);

    for(auto child: flat)
        std::cout<<get_path(child)<<std::endl;
    \endcode
    */
    //! 
    //! Providing an STL compliant container interface it can be used to 
    //! do all kind of search operations. For instance consider the case 
    //! where we would like to find all instances of NXdetector in an 
    //! entry:
    /*!
    \code
    std::vector<nxgroup> detector;
    auto entry = get_object(file.root(),"/:NXentry");
    
    for(auto e: entry)
        if(is_class(e,"NXdetector")) detector.push_back(e);
    \endcode
    */
    //! \tparam GTYPE group type
    //!
    template<typename GTYPE> class flat_group
    {
        public:
            //! the group type
            typedef  GTYPE group_type;
            //! nxobject is the value type of the flat_group container
            typedef typename nxobject_trait<nximp_code_map<group_type>::icode>::object_type value_type;
            //! the internal container type
            typedef std::vector<value_type> container_type;
            //! the iterator type
            typedef typename container_type::iterator iterator;
            //! the constant interator type
            typedef typename container_type::const_iterator const_iterator;
        private:
            //! internal container holding the objects
            container_type _container;

            //!
            //! \brief append children to container
            //! 
            //! Function appending all children of a parent to the internal 
            //! container. If a child is a group instance this function is 
            //! called recursively.
            //! 
            //! \throws invalid_object_error if parent is not valid
            //! \throws type_error if group conversion fails
            //! \throws object_error in case of any other error
            //!
            //! \param parent the parent group whose children are appended
            //!
            void append_children(const group_type &parent)
            {
                for(auto c: parent) //will throw invalid_object_error or 
                                    //object_error
                {
                    //add the child to the container
                    _container.push_back(c);

                    //if the child is a group recusively call append_children
                    if(is_group(c)) append_children(as_group(c));
                }
            }
        public:
            //====================public types==================================
            //!
            //! \brief constructor
            //! 
            //! \throws invalid_object_error if parent is not valid
            //! \throws type_error if group conversion fails
            //! \throws object_error in case of any other error
            //!
            //! \param parent the parent group from which all elements should be 
            //! gahtered
            //!
            explicit flat_group(const group_type &parent):
                _container()
            { 
                if(!is_valid(parent))
                    throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot create an flat group from an invalid object!");
                append_children(parent); 
            }

            //------------------------------------------------------------------
            //!
            //! \brief get element 
            //! 
            //! Return the element with index from the group. 
            //!
            //! \param index the index of the child in the recursive group
            //! \return copy of the child stored at index
            //!
            value_type operator[](size_t index) const noexcept
            {
                return _container[index];
            }

            //------------------------------------------------------------------
            //!
            //! \brief get element reference
            //!
            //! Return a reference to the element addressed by index in the 
            //! recursive group.
            //! 
            //! \param index the index of the child
            //! \return reference to the child
            //!
            value_type &operator[](size_t index) noexcept
            {
                return _container[index];
            }

            //------------------------------------------------------------------
            //!
            //! \brief get size
            //! 
            //! Return the total number of elements attached (recursively) 
            //! below this group.
            //! 
            //! \return number of children (direct or indirect)
            //!
            size_t size() const noexcept
            {
                return _container.size();
            }

            //------------------------------------------------------------------
            //! 
            //! \brief get iterator to first
            //! 
            //! Return a non const iterator to the first element in the group
            //! 
            //! \return interator to first element
            //! 
            iterator begin() noexcept
            {
                return _container.begin();
            }

            //------------------------------------------------------------------
            //! 
            //! \brief get iterator to last+1
            //!
            //! Return a non const iterator to the last+1 element in the group.
            //! 
            //! \return iterator to the last+1 element
            //!
            iterator end() noexcept
            {
                return _container.end();
            }

            //------------------------------------------------------------------
            //! 
            //! \brief get iterator to first
            //! 
            //! Return a const iterator to the first element in the group
            //! 
            //! \return const interator to first element
            //! 
            const_iterator begin() const noexcept
            {
                return _container.begin();
            }

            //------------------------------------------------------------------
            //! 
            //! \brief get iterator to last+1
            //!
            //! Return a const iterator to the last+1 element in the group.
            //! 
            //! \return const iterator to the last+1 element
            //!
            const_iterator end() const noexcept
            {
                return _container.end();
            }
    };

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief create a flat group
    //! 
    //! Create a flat group from a group instance.
    //!
    //! \throws invalid_object_error if the group is not valid
    //! \throws object_error in case of any other error
    //! \throws type_error if group conversion fails
    //!
    //! \tparam GTYPE group type template
    //! \tparam IMPID implementation ID
    //! 
    //! \param group instance of a group
    //! \return flat_group instance
    //!
    template<
             template<nximp_code> class GTYPE,
             nximp_code IMPID
            >
    flat_group<GTYPE<IMPID>> make_flat(const GTYPE<IMPID> group)
    {
        return flat_group<GTYPE<IMPID>>(group);
    }

    //-------------------------------------------------------------------------
    //!
    //! \ingroup nexus_lowlevel
    //! \brief create a flat group
    //!
    //! Create a flat group from an instance from nxobject.
    //!
    //! \throws type_error if the parent object does not hold a group
    //! \throws invalid_object_error if the parent is not valid
    //! \throws object_error in case of any other error
    //!
    //! \tparam GTYPE group type
    //! \tparam FTYPE field type
    //! \tparam ATYPE attribute_type
    //!
    //! \param object instance of nxobject with the parent group
    //! \return instance of flat_group
    //!
    template<
             typename GTYPE,
             typename FTYPE,
             typename ATYPE
            >

    flat_group<GTYPE> make_flat(const nxobject<GTYPE,FTYPE,ATYPE> object)
    {
        return flat_group<GTYPE>(as_group(object));
    }


//end of namespace
}
}
}
