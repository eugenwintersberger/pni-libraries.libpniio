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


namespace pni{
namespace io{
namespace nx {
namespace h5 {

    using pni::io::object_error;

    //====================private methods======================================

    //implementation of the buffer allocation routine
    void h5dataspace::__update_buffers()
    {
        if(!is_scalar())
        {
            _maxdims = buffer_type(rank());
            _dims    = buffer_type(rank());
            auto *dimptr = const_cast<value_type*>(_dims.data());
            auto *mdimptr = const_cast<value_type*>(_maxdims.data());
            herr_t err = H5Sget_simple_extent_dims(_object.id(),dimptr,mdimptr);
            if(err<0)
                throw object_error(EXCEPTION_RECORD,
                        "Failure obtaining dataspace extent!\n\n"
                        +get_h5_error_string());
        }
    }

    //-------------------------------------------------------------------------
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

    //=============Constructors and destructors================================
    h5dataspace::h5dataspace() noexcept:
        _object(H5Screate(H5S_SCALAR)),
        _maxdims(),
        _dims()
    {
        //the dataspace is initialized as a scalar dataspace
    }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    h5dataspace::h5dataspace(const h5dataspace &o)
        :_object(o._object),
        _maxdims(o._maxdims),
        _dims(o._dims)
    { }

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    h5dataspace::h5dataspace(h5dataspace &&o) noexcept 
        :_object(std::move(o._object)),
        _maxdims(std::move(o._maxdims)),
        _dims(std::move(o._dims))
    { }

    //-------------------------------------------------------------------------
    h5dataspace::h5dataspace(object_imp &&o)
        :_object(std::move(o))
    {
        if(get_hdf5_type(_object) != h5object_type::DATASPACE)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not a dataspace!");

        __update_buffers();
    }

    //-------------------------------------------------------------------------
    h5dataspace::h5dataspace(const type_imp::index_vector_type &s):
        _object(H5Screate(H5S_SCALAR)),
        _maxdims(s),
        _dims(s)
    {
        __update_dataspace();
    }

    //------------------------------------------------------------------------
    h5dataspace::h5dataspace(const type_imp::index_vector_type &s,
                             const type_imp::index_vector_type &ms):
        _object(H5Screate(H5S_SCALAR)),
        _maxdims(ms),
        _dims(s)

    {
        //check if the ranks of the shapes is equal
        if(!check_equal_size(s,ms))
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Current and maximum shape containers have different "
                    "length!");

        //resize the dataspace to a simple one
        __update_dataspace();
    }
    //===================Assignment operators==================================
    //implementation of the copy assignment operator
    h5dataspace &h5dataspace::operator=(const h5dataspace &o)
    {
        if (this == &o) return *this;
    
        _object = o._object;
        _dims  = o._dims;
        _maxdims = o._maxdims;

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of the move assignment operator
    h5dataspace &h5dataspace::operator=(h5dataspace &&o) noexcept
    {
        if(this == &o) return *this;

        _object = std::move(o._object);
        _dims  = std::move(o._dims);
        _maxdims = std::move(o._maxdims);

        return *this;
    }

    //===================Other methods=========================================
    const object_imp &h5dataspace::object() const noexcept
    {
        return _object;
    }

    //------------------------------------------------------------------------
    //implementation of is_scalar
    bool h5dataspace::is_scalar() const 
    {
        
        if(!_object.is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Dataspace instance is not valid - cannot check if "
                    "scalar!");

        H5S_class_t type = H5Sget_simple_extent_type(_object.id());
        if(type == H5S_SCALAR) return true;
        return false;
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::rank() const 
    {
        //return 0 if the dataspace is scalar
        if(is_scalar()) return 0;

        //return the number of dimension if the dataspace is simple
        return H5Sget_simple_extent_ndims(_object.id());
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::current_dim(size_t i) const 
    {
        //return 0 if the dataspace is scalar
        if(is_scalar()) return 0;

        if(i>=rank())
            throw index_error(EXCEPTION_RECORD,
                    "User index exceeds rank of dataspace!");

        //return the number of elements along dimension i if the 
        //dataspace is simple
        return _dims[i];
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::maximum_dim(size_t i) const 
    {
        //return 0 if the dataspace is scalar
        if(is_scalar()) return 0;

        if(i>=rank())
            throw index_error(EXCEPTION_RECORD,
                    "User index exceeds rank of dataspace!");

        //return the maximum number of elements along i if the 
        //dataspace is simple
        return _maxdims[i];
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::size() const 
    {
        //return 1 if the dataspace is scalar
        if(is_scalar()) return 1;

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

    //-------------------------------------------------------------------------
    void h5dataspace::resize(const type_imp::index_vector_type &shape)
    {
        _dims    = shape;
        _maxdims = shape;

        __update_dataspace();
    }


    //-------------------------------------------------------------------------
    void h5dataspace::resize(const type_imp::index_vector_type &cshape,
                             const type_imp::index_vector_type &mshape)
    {
        if(!check_equal_size(cshape,mshape))
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Current and maximum shape vector do not have equal"
                    " lenght!");

        _dims    = cshape;
        _maxdims = mshape;

        __update_dataspace();
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
    const type_imp::index_vector_type &h5dataspace::current_dims() const noexcept
    {
        return _dims;
    }

    //------------------------------------------------------------------------
    const type_imp::index_vector_type &h5dataspace::maximum_dims() const noexcept
    {
        return _maxdims;
    }

    
    //------------------------------------------------------------------------
    h5dataspace::iterator h5dataspace::current_begin() const noexcept 
    {
        return _dims.begin();
    }

    //------------------------------------------------------------------------
    h5dataspace::iterator h5dataspace::current_end() const noexcept
    {
        return _dims.end();
    }

    //------------------------------------------------------------------------
    h5dataspace::iterator h5dataspace::maximum_begin() const noexcept
    {
        return _maxdims.begin();
    }
    
    //------------------------------------------------------------------------
    h5dataspace::iterator h5dataspace::maximum_end() const noexcept
    {
        return _maxdims.end();
    }
    //======================operators==========================================
    std::ostream &operator<<(std::ostream &o,const h5dataspace &s)
    {
        if(s.is_scalar())
            o<<"HDF5 scalar dataspace";
        else
        {
            o<<"HDF5 Dataspace: "<<s.rank()<<" dimensions"<<std::endl;
            o<<"Current # of elements: (";
            for(auto iter=s.current_begin();iter!=s.current_end();++iter)
            {
                o<<*iter;
                if(iter!=s.current_end()-1) o<<",";
            }
            o<<")"<<std::endl;

            o<<"Maximum # of elements: (";
            for(auto iter=s.maximum_begin();iter!=s.maximum_end();++iter)
            {
                o<<*iter;
                if(iter!=s.maximum_end()-1) o<<",";
            }
            o<<")"<<std::endl;
        }

        return o;
    }

        
//end of namespace
}
}
}
}
