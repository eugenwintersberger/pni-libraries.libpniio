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
    const type_imp::index_vector_type &selection::offset() const noexcept
    {
        return _offset;
    }

    //------------------------------------------------------------------------
    void selection::offset(const type_imp::index_vector_type &value) 
    {
        if(value.size()!=_offset.size())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Selection rank and offset size do not match!");

        std::copy(value.begin(),value.end(),_offset.begin());
    }

    //------------------------------------------------------------------------
    void selection::offset(type_imp::index_type value) noexcept
    {
        std::fill(_offset.begin(),_offset.end(),value);
    }
    
    //------------------------------------------------------------------------
    void selection::offset(size_t index,size_t value)
    {
        if(index>=_offset.size())
            throw index_error(EXCEPTION_RECORD,
                    "Dimension index exceeds total rank of selection!");

        _offset[index] = value;
    }

    //------------------------------------------------------------------------
    const type_imp::index_vector_type &selection::stride() const noexcept
    {
        return _stride;
    }

    //------------------------------------------------------------------------
    void selection::stride(const type_imp::index_vector_type &value)
    {
        if(value.size() != _stride.size())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Stride vector size does not match selection rank!");

        std::copy(value.begin(),value.end(),_stride.begin());
    }

    //------------------------------------------------------------------------
    void selection::stride(type_imp::index_type value) noexcept
    {
        std::fill(_stride.begin(),_stride.end(),value);
    }

    //------------------------------------------------------------------------
    void selection::stride(size_t index,type_imp::index_type value)
    {
        if(index>=_stride.size())
            throw index_error(EXCEPTION_RECORD,
                    "Dimension index exceeds selection rank!");

        _stride[index] = value;
    }

    //------------------------------------------------------------------------
    const type_imp::index_vector_type &selection::count() const noexcept
    {
        return _count;
    }


    //------------------------------------------------------------------------
    void selection::count(const type_imp::index_vector_type &value)
    {
        std::copy(value.begin(),value.end(),_count.begin());
    }

    //------------------------------------------------------------------------
    void selection::count(type_imp::index_type value) noexcept
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
        if(s.size()!=_offset.size())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Size of slice vector does not match selection rank!");

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
    size_t effective_rank(const selection &s) noexcept
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
    size_t size(const selection &s) noexcept
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

    //------------------------------------------------------------------------
    type_imp::selection_vector_type create_slice_vector(const selection &s)
    {
        auto offset_iter = s.offset().begin();
        auto end_iter    = s.offset().end();
        auto stride_iter = s.stride().begin();
        auto count_iter  = s.count().begin();

        type_imp::selection_vector_type slices;
        
        for(;offset_iter != end_iter;++offset_iter,++stride_iter,++count_iter)
        {
            size_t first = *offset_iter;
            size_t last  = (*count_iter)*(*stride_iter);
            size_t stride = *stride_iter;

            if(first == last) last=first+1;

            slices.push_back(slice(first,last,stride));
        }

        return slices;
    }


//end of namespace
}
}
}
}

