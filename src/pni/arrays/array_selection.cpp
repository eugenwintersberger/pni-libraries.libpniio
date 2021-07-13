//!
//! (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//!
//! This file is part of libpnicore.
//!
//! libpnicore is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 2 of the License, or
//! (at your option) any later version.
//!
//! libpnicore is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//! 
//! ===========================================================================
//!
//! Created on: Jun 1, 2012
//!     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//!

#include <pni/arrays/array_selection.hpp>
#include <numeric>

namespace pni{
namespace core{
    array_selection::array_selection():
       _oshape(0),
	   _offset(0),
	   _stride(0)
    {}

    array_selection::array_selection(index_type &&oshape,index_type &ooffset,
                             index_type &&ostride):
        _oshape(std::move(oshape)),
        _offset(std::move(ooffset)),
        _stride(std::move(ostride))
    {
    }

    array_selection::array_selection(const index_type &oshape,
                             const index_type &ooffset,
                             const index_type &ostride):
        _oshape(oshape),
        _offset(ooffset),
        _stride(ostride)
    {
    }

    array_selection::array_selection(const array_selection &s):
        _oshape(s._oshape),
        _offset(s._offset),
        _stride(s._stride)
    { }

    array_selection::array_selection(array_selection &&s):
         _oshape(std::move(s._oshape)),
         _offset(std::move(s._offset)),
         _stride(std::move(s._stride))
     { }

    array_selection &array_selection::operator=(const array_selection &s)
    {
        if(this == &s) return *this;

        _oshape = s._oshape;
        _offset = s._offset;
        _stride = s._stride;

        return *this;
    }

    array_selection &array_selection::operator=(array_selection &&s)
    {
        if(this == &s) return *this;

        _oshape = std::move(s._oshape);
        _offset = std::move(s._offset);
        _stride = std::move(s._stride);

        return *this;
    }

    size_t array_selection::rank() const
    {
        return _oshape.size() - std::count(_oshape.begin(),_oshape.end(),1);
    }

    size_t array_selection::size() const
    {
        typedef typename index_type::value_type value_type;
        if(_oshape.empty()) return 0; //not initialized

        if(rank() == 0) return 1; //scalar element selected

        //compute the size and return it
        return std::accumulate(_oshape.begin(),_oshape.end(),
                              value_type(1),
                              std::multiplies<value_type>());
    }

    const array_selection::index_type &array_selection::offset() const noexcept
    {
    	return _offset;
    }

    const array_selection::index_type &array_selection::stride() const noexcept
    {
    	return _stride;
    }

    const array_selection::index_type &array_selection::full_shape() const noexcept
    {
    	return _oshape;
    }

    //======================implementation of general purpose methods===========
    std::ostream &operator<<(std::ostream &o,const array_selection &s)
    {
        o<<"original data:"<<std::endl;
        auto oshape = s.full_shape();
        auto offset = s.offset();
        auto stride = s.stride();
        for(size_t i=0;i<oshape.size();i++)
        {
            o<<i<<":\t"<<oshape[i]<<"\t"<<offset[i]<<"\t"<<stride[i];
            o<<std::endl;
        }
        shape_t shape = s.shape<shape_t>();
        o<<"effective shape: ( ";
        for(auto v: shape) o<<v<<" ";
        
        o<<")"<<std::endl;

        return o;
    }

    //-------------------------------------------------------------------------
    size_t rank(const array_selection &s)
    {
        return s.rank();
    }
    
    //-------------------------------------------------------------------------
    size_t size(const array_selection &s)
    {
        return s.size();
    }
//end of namespace
}
}
