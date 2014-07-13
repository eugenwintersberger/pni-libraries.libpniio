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
// Created on: Jan 10, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//


#include <pni/io/nx/h5/H5Dataspace.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/exceptions.hpp>


namespace pni{
namespace io{
namespace nx {
namespace h5 {

    using pni::io::object_error;
    using pni::io::invalid_object_error;

    //====================private methods======================================

    //implementation of the buffer allocation routine
    void H5Dataspace::__update_buffers()
    {
        if(!is_scalar())
        {
            _maxdims = dim_vector_type(rank());
            _dims    = dim_vector_type(rank());
            hsize_t *dimptr = const_cast<hsize_t*>(_dims.data());
            hsize_t *mdimptr = const_cast<hsize_t*>(_maxdims.data());
            herr_t err = H5Sget_simple_extent_dims(id(),dimptr,mdimptr);
            if(err<0)
                throw object_error(EXCEPTION_RECORD,
                        "Failure obtaining dataspace extent!\n\n"
                        +get_h5_error_string());
        }
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::__update_dataspace()
    {

        herr_t err = H5Sset_extent_simple(id(),_dims.size(),_dims.data(),
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
    H5Dataspace::H5Dataspace():H5Object(H5Screate(H5S_SCALAR))
    {
        //the dataspace is initialized as a scalar dataspace
    }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    H5Dataspace::H5Dataspace(const H5Dataspace &o):
        H5Object(o),
        _maxdims(o._maxdims),
        _dims(o._dims)
    { }

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    H5Dataspace::H5Dataspace(H5Dataspace &&o) noexcept 
        :H5Object(std::move(o)),
        _maxdims(std::move(o._maxdims)),
        _dims(std::move(o._dims))
    { }

    //-------------------------------------------------------------------------
    H5Dataspace::H5Dataspace(hid_t tid):H5Object(tid)
    {
        __update_buffers();
    }

    //-------------------------------------------------------------------------
    //construct dataspace form initializer list
    H5Dataspace::H5Dataspace(const std::initializer_list<hsize_t> &list):
        H5Object(H5Screate(H5S_SCALAR)),
        _maxdims(list),
        _dims(list)
    {
        __update_dataspace();
    }

    //-------------------------------------------------------------------------
    //construction from two initializer lists
    H5Dataspace::H5Dataspace(const std::initializer_list<hsize_t> &dlist,
                             const std::initializer_list<hsize_t> &mlist)
        :H5Object(H5Screate(H5S_SCALAR)),
         _maxdims(mlist),
         _dims(dlist)
    {

        //check if the sizes of the two initializer lists match
        if(mlist.size() != dlist.size())
        {
            std::stringstream ss;
            ss<<"Rank of actual shape ("<<dlist.size()<<") and of ";
            ss<<"maximum shape ("<<mlist.size()<<") do not match!";
            throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
        }

        //finally resize the dataspace
        __update_dataspace();
    }


    //-------------------------------------------------------------------------
    H5Dataspace::~H5Dataspace()
    {
        if(is_valid()) 
            if(H5Sclose(id())<0)
                throw object_error(EXCEPTION_RECORD,
                        "Error closing HDF5 data space - HDF5 error was:\n\n"+
                        get_h5_error_string());

        //reset the object ID
        H5Object::reset_id();
    }

    //===================Assignment operators==================================
    //implementation of the copy assignment operator
    H5Dataspace &H5Dataspace::operator=(const H5Dataspace &o)
    {
        if (this == &o) return *this;

        H5Object::operator=(o);
        _dims  = o._dims;
        _maxdims = o._maxdims;

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of the move assignment operator
    H5Dataspace &H5Dataspace::operator=(H5Dataspace &&o)
    {
        if(this == &o) return *this;

        H5Object::operator=(std::move(o));
        _dims  = std::move(o._dims);
        _maxdims = std::move(o._maxdims);

        return *this;
    }

    //===================Other methods=========================================
    //implementation of is_scalar
    bool H5Dataspace::is_scalar() const 
    {
        H5S_class_t type = H5Sget_simple_extent_type(id());
        if(type == H5S_SCALAR) return true;
        return false;
    }

    //-------------------------------------------------------------------------
    size_t H5Dataspace::rank() const 
    {
        //return 0 if the dataspace is scalar
        if(is_scalar()) return 0;

        //return the number of dimension if the dataspace is simple
        return H5Sget_simple_extent_ndims(id());
    }

    //-------------------------------------------------------------------------
    size_t H5Dataspace::dim(size_t i) const 
    {
        //return 0 if the dataspace is scalar
        if(is_scalar()) return 0;

        //return the number of elements along dimension i if the 
        //dataspace is simple
        return _dims[i];
    }

    //-------------------------------------------------------------------------
    size_t H5Dataspace::max_dim(size_t i) const 
    {
        //return 0 if the dataspace is scalar
        if(is_scalar()) return 0;

        //return the maximum number of elements along i if the 
        //dataspace is simple
        return _maxdims[i];
    }

    //-------------------------------------------------------------------------
    size_t H5Dataspace::size() const 
    {
        //return 1 if the dataspace is scalar
        if(is_scalar()) return 1;

        //return the number of elements in the dataspace if the 
        //dataspcae is simple
        ssize_t size = H5Sget_select_npoints(id());
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
    size_t H5Dataspace::operator[](size_t i) const 
    {
        return dim(i);
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::close()
    {
        if(is_valid()) 
            if(H5Sclose(id())<0)
                throw object_error(EXCEPTION_RECORD,
                        "Error closing HDF5 data space - HDF5 error was:\n\n"+
                        get_h5_error_string());

        H5Object::reset_id();
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::resize(const std::initializer_list<hsize_t> &list)
    {
        _dims    = dim_vector_type(list.size());
        _maxdims = dim_vector_type(list.size());

        std::copy(list.begin(),list.end(),_dims.begin());
        std::copy(list.begin(),list.end(),_maxdims.begin());

        __update_dataspace();
    }


    //-------------------------------------------------------------------------
    void H5Dataspace::resize(const std::initializer_list<hsize_t> &dlist,
                             const std::initializer_list<hsize_t> &mlist)
    {

        if(dlist.size() != mlist.size())
        {
            std::stringstream ss;
            ss<<"Rank of actual shape ("<<dlist.size()<<") and of ";
            ss<<"maximum shape ("<<mlist.size()<<") do not match!";
            throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
        }
        std::copy(dlist.begin(),dlist.end(),_dims.begin());
        std::copy(mlist.begin(),mlist.end(),_maxdims.begin());

        __update_dataspace();
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::grow(size_t dim,size_t ext)
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



    //======================operators==========================================
    std::ostream &operator<<(std::ostream &o,const H5Dataspace &s)
    {
        o<<"HDF5 Dataspace: "<<s.rank()<<" dimensions"<<std::endl;
        o<<"act. # of elements: ( ";
        for(size_t i=0;i<s.rank();i++){
            o<<s.dim(i)<<" ";
        }
        o<<")";

        return o;
    }

        
//end of namespace
}
}
}
}
