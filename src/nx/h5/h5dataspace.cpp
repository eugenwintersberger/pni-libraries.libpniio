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
// Created on: Jul 15, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <algorithm>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/exceptions.hpp>
#include <functional>


namespace pni{
namespace io{
namespace nx {
namespace h5 {

    using pni::io::object_error;

    //====================private methods======================================
    void h5dataspace::__update_dataspace()
    {
        herr_t err = H5Sset_extent_simple(_object.id(),_dims.size(),_dims.data(),
                                          _maxdims.data());
                        
        if(err<0)
        {
            object_error error(EXCEPTION_RECORD,
                              "Cannot create HDF5 dataspace!\n\n"+
                               get_h5_error_string());
#ifdef DEBUG
            std::cerr<<error<<std::endl;
#endif
            throw error;
        }
    }

    //-------------------------------------------------------------------------
    void h5dataspace::__update_buffers()
    {
        _dims = type_imp::index_vector_type(rank());
        _maxdims = type_imp::index_vector_type(rank());

        if(H5Sget_simple_extent_dims(_object.id(),_dims.data(),_maxdims.data())<0)
            throw object_error(EXCEPTION_RECORD,
                    "Error retrieving dataspace dimensions!");

        _offset = type_imp::index_vector_type(rank());
        _stride = type_imp::index_vector_type(rank());
        _count  = type_imp::index_vector_type(rank());

        std::fill(_offset.begin(),_offset.end(),0);
        std::fill(_stride.begin(),_stride.end(),1);
        std::fill(_count.begin(),_count.end(),1);
    }

    //-------------------------------------------------------------------------
    void h5dataspace::__init_buffers() noexcept
    {
        std::fill(_maxdims.begin(),_maxdims.end(),H5S_UNLIMITED);
        std::fill(_offset.begin(),_offset.end(),0);
        std::fill(_stride.begin(),_stride.end(),1);
        std::fill(_count.begin(),_count.end(),1);
    }

    //=============Constructors and destructors================================
    h5dataspace::h5dataspace():
        _object(),
        _dims{{1}},
        _maxdims{{H5S_UNLIMITED}},
        _offset{{0}},
        _stride{{1}},
        _count{{1}}
    {
        _object = object_imp(H5Screate_simple(1,_dims.data(),_maxdims.data()));
    }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    h5dataspace::h5dataspace(const h5dataspace &o):
        _object(o._object),
        _dims(o._dims),
        _maxdims(o._maxdims),
        _offset(o._offset),
        _stride(o._stride),
        _count(o._count)
    { }

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    h5dataspace::h5dataspace(h5dataspace &&o) noexcept :
        _object(std::move(o._object)),
        _dims(std::move(o._dims)),
        _maxdims(std::move(o._maxdims)),
        _offset(std::move(o._offset)),
        _stride(std::move(o._stride)),
        _count(std::move(o._count))
    { }


    //-------------------------------------------------------------------------
    h5dataspace::h5dataspace(const type_imp::index_vector_type &shape):
        _object(),
        _dims(shape),
        _maxdims(shape.size()),
        _offset(shape.size()),
        _stride(shape.size()),
        _count(shape.size())
    {
        __init_buffers();
        _object = object_imp(H5Screate_simple(_dims.size(),
                                              _dims.data(),
                                              _maxdims.data()));
    }

    //------------------------------------------------------------------------
    h5dataspace::h5dataspace(type_imp::index_vector_type &&shape):
        _object(),
        _dims(std::move(shape)),
        _maxdims(_dims.size()),
        _offset(_dims.size()),
        _stride(_dims.size()),
        _count(_dims.size())
    {
        __init_buffers();
        _object = object_imp(H5Screate_simple(_dims.size(),
                                              _dims.data(),
                                              _maxdims.data()));
    }

    //-------------------------------------------------------------------------
    h5dataspace::h5dataspace(object_imp &&o):
        _object(o)
    {
        if(get_hdf5_type(_object) != h5object_type::DATASPACE)
            throw type_error(EXCEPTION_RECORD, "Object is not a dataspace!");

        __update_buffers();
    }

    //===================Assignment operators==================================
    //implementation of the copy assignment operator
    h5dataspace &h5dataspace::operator=(const h5dataspace &o)
    {
        if (this == &o) return *this;
    
        _object  = o._object;
        _dims    = o._dims;
        _maxdims = o._maxdims;
        _offset  = o._offset;
        _stride  = o._stride;
        _count   = o._count;

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of the move assignment operator
    h5dataspace &h5dataspace::operator=(h5dataspace &&o) noexcept
    {
        if(this == &o) return *this;

        _object  = std::move(o._object);
        _dims    = std::move(o._dims);
        _maxdims = std::move(o._maxdims);
        _offset  = std::move(o._offset);
        _stride  = std::move(o._stride);
        _count   = std::move(o._count);

        return *this;
    }

    //===================Other methods=========================================
    hid_t h5dataspace::id() const noexcept
    {
        return _object.id();
    }

    bool h5dataspace::is_valid() const
    {
        return _object.is_valid();
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::rank() const 
    {
        return H5Sget_simple_extent_ndims(_object.id());
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::size() const 
    {
        return
            std::accumulate(_dims.begin(),_dims.end(),1,std::multiplies<size_t>());
                               
    }
    
    //------------------------------------------------------------------------
    const type_imp::index_vector_type &h5dataspace::shape() const noexcept
    {
        return _dims;
    }

    //------------------------------------------------------------------------
    bool h5dataspace::has_selection() const
    {
        H5S_sel_type type = H5Sget_select_type(_object.id());

        if(type == H5S_SEL_ALL)
            return false;
        else if(type < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Could not determine selection type!");
        else
            return true;

    }

    //-------------------------------------------------------------------------
    void h5dataspace::grow(size_t dim,size_t ext)
    {
        if(dim >= rank())
        {
            std::stringstream ss;
            ss<<"Dimension index ("<<dim<<") exceeds rank (";
            ss<<rank()<<")!";
            throw index_error(EXCEPTION_RECORD,ss.str());
        }

        //set extension
        _dims[dim] += ext;
        __update_dataspace();
    }

    //------------------------------------------------------------------------
    void h5dataspace::apply_selection(const type_imp::selection_vector_type
            &selection) const  
    {
        if(selection.size() != rank())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Selection and dataspace rank do not match!");

        size_t index=0;
        for(const auto &sl: selection)
        {
            _offset[index] = sl.first();
            _stride[index] = sl.stride();
            _count[index] = pni::core::size(sl);
            index++;     
        }


        //apply the selection
        herr_t err = H5Sselect_hyperslab(_object.id(),
                H5S_SELECT_SET,_offset.data(),_stride.data(),_count.data(),
                nullptr);
        if(err<0)
            throw object_error(EXCEPTION_RECORD,
                    "Error applying selection to dataset!\n\n"+
                    get_h5_error_string());


    }
           
    //------------------------------------------------------------------------
    void h5dataspace::reset_selection() const
    {
        H5Sselect_all(_object.id());
    }

    //------------------------------------------------------------------------
    size_t h5dataspace::selection_size() const
    {
        //return the number of elements in the dataspace if the 
        //dataspcae is simple
        ssize_t size = H5Sget_select_npoints(_object.id());
        if(size<0) 
        {
            object_error error( EXCEPTION_RECORD,
                    "Could not determine dataspace size\n\n"+
                    get_h5_error_string());
            std::cerr<<error<<std::endl;
            throw error;
        }

        return (size_t)(size);
    }

    //------------------------------------------------------------------------
    size_t h5dataspace::selection_rank() const
    {
        return std::count_if(_count.begin(),_count.end(),
                             [](hsize_t v){ return v>1; });
    }

    //------------------------------------------------------------------------
    type_imp::index_vector_type h5dataspace::selection_shape() const
    {
        type_imp::index_vector_type shape;

        for(auto c: _count)
            if(c>1) shape.push_back(c);

        return shape;
    }


    
    //======================operators==========================================
    std::ostream &operator<<(std::ostream &o,const h5dataspace &s)
    {
        o<<"HDF5 Dataspace: "<<s.rank()<<" dimensions"<<std::endl;
        o<<"Current # of elements: (";
        for(auto iter=s.shape().begin();iter!=s.shape().end();++iter)
        {
            o<<*iter;
            if(iter!=s.shape().end()-1) o<<",";
        }
        o<<")";
        return o;
    }

        
//end of namespace
}
}
}
}
