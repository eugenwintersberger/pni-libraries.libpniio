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
// Created on: Aug 1, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <functional>
#include <algorithm>
#include <pni/io/nx/h5/selection.hpp>


namespace pni{
namespace io{
namespace nx{
namespace h5{

    selection::selection() noexcept:
        _offset(),
        _stride(),
        _count()
    {}

    //------------------------------------------------------------------------
    selection::selection(const selection &s):
        _offset(s._offset),
        _stride(s._stride),
        _count(s._count)
    {}

    //-----------------------------------------------------------------------
    selection::selection(selection &&s) noexcept:
        _offset(std::move(s._offset)),
        _stride(std::move(s._stride)),
        _count(std::move(s._count))
    {}

    //------------------------------------------------------------------------
    selection::selection(size_t n):
        _offset(n),
        _stride(n),
        _count(n)
    {
        std::fill(_offset.begin(),_offset.end(),0);
        std::fill(_stride.begin(),_stride.end(),1);
        std::fill(_count.begin(),_count.end(),0);
    }

    //------------------------------------------------------------------------
    selection &selection::operator=(const selection &s)
    {
        if(this == &s) return *this;

        _offset = s._offset;
        _stride = s._stride;
        _count  = s._count;

        return *this;
    }

    //------------------------------------------------------------------------
    selection &selection::operator=(selection &&s) noexcept
    {
        if(this == &s) return *this;

        _offset = std::move(s._offset);
        _stride = std::move(s._stride);
        _count  = std::move(s._count);

        return *this;
    }

    //------------------------------------------------------------------------
    const type_imp::index_vector_type &selection::offset() const
    {
        return _offset;
    }

    //------------------------------------------------------------------------
    void selection::offset(const type_imp::index_vector_type &value) 
    {
        std::copy(value.begin(),value.end(),_offset.begin());
    }

    //------------------------------------------------------------------------
    void selection::offset(type_imp::index_type value)
    {
        std::fill(_offset.begin(),_offset.end(),value);
    }

    //------------------------------------------------------------------------
    const type_imp::index_vector_type &selection::stride() const
    {
        return _stride;
    }

    //------------------------------------------------------------------------
    void selection::stride(const type_imp::index_vector_type &value)
    {
        std::copy(value.begin(),value.end(),_stride.begin());
    }

    //------------------------------------------------------------------------
    void selection::stride(type_imp::index_type value)
    {
        std::fill(_stride.begin(),_stride.end(),value);
    }

    //------------------------------------------------------------------------
    const type_imp::index_vector_type &selection::count() const
    {
        return _count;
    }

    //------------------------------------------------------------------------
    void selection::offset(size_t index,size_t value)
    {
        _offset[index] = value;
    }

    //------------------------------------------------------------------------
    void selection::count(const type_imp::index_vector_type &value)
    {
        std::copy(value.begin(),value.end(),_count.begin());
    }

    //------------------------------------------------------------------------
    void selection::count(type_imp::index_type value)
    {
        std::fill(_count.begin(),_count.end(),value);
    }

    //------------------------------------------------------------------------
    void selection::count(size_t index,type_imp::index_type value)
    {
        _count[index] = value;
    }

    //------------------------------------------------------------------------
    void selection::update(const type_imp::selection_vector_type &s)
    {
        size_t index=0;
        for(const auto &sl: s)
        {
            _offset[index] = sl.first();
            _stride[index] = sl.stride();
            _count[index]  = pni::core::size(sl);
            index++;     
        }
    }

    //========================================================================
    // Implementation of utility functions
    //========================================================================
    size_t effective_rank(const selection &s)
    {
        return std::count_if(s.count().begin(),
                             s.count().end(),
                             [](type_imp::index_type v){ return v>1; });
    }

    //------------------------------------------------------------------------
    type_imp::index_vector_type effective_shape(const selection &s)
    {
        type_imp::index_vector_type shape;

        for(auto c: s.count()) if(c>1) shape.push_back(c);

        return shape;
    }

    //------------------------------------------------------------------------
    size_t size(const selection &s)
    {
        typedef std::multiplies<type_imp::index_type> mult_type;

        return (size_t)(std::accumulate(s.count().begin(),
                                        s.count().end(),
                                        1,
                                        mult_type()));
    }

    //------------------------------------------------------------------------
    selection create_selection(const type_imp::selection_vector_type &s)
    {
        selection sel{s.size()};

        sel.update(s);
        return sel;
    }


//end of namespace
}
}
}
}

