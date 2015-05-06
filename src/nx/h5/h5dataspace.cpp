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
#include <pni/io/exceptions.hpp>
#include <functional>
#include <pni/io/nx/h5/selection.hpp>


namespace pni{
namespace io{
namespace nx {
namespace h5 {

    using namespace pni::core;

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
    }

    //-------------------------------------------------------------------------
    void h5dataspace::__init_buffers() noexcept
    {
        std::fill(_maxdims.begin(),_maxdims.end(),H5S_UNLIMITED);
    }

    //=============Constructors and destructors================================
    h5dataspace::h5dataspace():
        _object(),
        _dims({1}),
        _maxdims({H5S_UNLIMITED})
    {
        _object = object_imp(H5Screate_simple(1,_dims.data(),_maxdims.data()));
    }
    
    //-------------------------------------------------------------------------
    h5dataspace::h5dataspace(object_imp &&o):
        _object(std::move(o))
    {
        if(get_hdf5_type(_object) != h5object_type::DATASPACE)
            throw type_error(EXCEPTION_RECORD, "Object is not a dataspace!");

        __update_buffers();
    }


    //-------------------------------------------------------------------------
    h5dataspace::h5dataspace(const type_imp::index_vector_type &shape):
        _object(),
        _dims(shape),
        _maxdims(shape.size())
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
        _maxdims(_dims.size())
    {
        __init_buffers();
        _object = object_imp(H5Screate_simple(_dims.size(),
                                              _dims.data(),
                                              _maxdims.data()));
    }

    //===================Other methods=========================================
    hid_t h5dataspace::id() const noexcept
    {
        return _object.id();
    }

    //-------------------------------------------------------------------------
    bool h5dataspace::is_valid() const
    {
        return _object.is_valid();
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::rank() const 
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot obtain the rank of an invalid dataspace!");

        return H5Sget_simple_extent_ndims(_object.id());
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::size() const 
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot obtain size of an invalid dataspace!");

        typedef std::multiplies<size_t> mult_type;
        return std::accumulate(_dims.begin(),_dims.end(),1,mult_type());
                               
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
    void h5dataspace::apply_selection(const selection &s) const  
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot apply a selection to an invalid dataspace!");

        //apply the selection
        herr_t err = H5Sselect_hyperslab(_object.id(),H5S_SELECT_SET,
                                         s.offset().data(),
                                         s.stride().data(),
                                         s.count().data(),
                                         nullptr);
        if(err<0)
            throw object_error(EXCEPTION_RECORD,
                    "Error applying selection to dataset!\n\n"+
                    get_h5_error_string());
    }
           
    //------------------------------------------------------------------------
    void h5dataspace::reset_selection() const noexcept
    {
        H5Sselect_all(_object.id());
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
