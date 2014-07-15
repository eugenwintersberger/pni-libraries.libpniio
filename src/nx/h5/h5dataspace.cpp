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
    h5dataspace::h5dataspace(h5object &&o)
        :_object(std::move(o))
    {
        if(get_hdf5_type(_object) != h5object_type::DATASPACE)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not a dataspace!");

        __update_buffers();
    }

    //-------------------------------------------------------------------------
    //construct dataspace form initializer list
    h5dataspace::h5dataspace(const std::initializer_list<hsize_t> &list):
        _object(H5Screate(H5S_SCALAR)),
        _maxdims(list),
        _dims(list)
    {
        __update_dataspace();
    }

    //-------------------------------------------------------------------------
    //construction from two initializer lists
    h5dataspace::h5dataspace(const std::initializer_list<hsize_t> &dlist,
                             const std::initializer_list<hsize_t> &mlist)
        :_object(H5Screate(H5S_SCALAR)),
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
    h5dataspace &h5dataspace::operator=(h5dataspace &&o)
    {
        if(this == &o) return *this;

        _object = std::move(o._object);
        _dims  = std::move(o._dims);
        _maxdims = std::move(o._maxdims);

        return *this;
    }

    //===================Other methods=========================================
    //implementation of is_scalar
    bool h5dataspace::is_scalar() const 
    {
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

        //return the number of elements along dimension i if the 
        //dataspace is simple
        return _dims[i];
    }

    //-------------------------------------------------------------------------
    size_t h5dataspace::maximum_dim(size_t i) const 
    {
        //return 0 if the dataspace is scalar
        if(is_scalar()) return 0;

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
    void h5dataspace::resize(const std::initializer_list<hsize_t> &list)
    {
        _dims    = buffer_type(list);
        _maxdims = buffer_type(list);

        __update_dataspace();
    }


    //-------------------------------------------------------------------------
    void h5dataspace::resize(const std::initializer_list<hsize_t> &dlist,
                             const std::initializer_list<hsize_t> &mlist)
    {

        if(dlist.size() != mlist.size())
        {
            std::stringstream ss;
            ss<<"Rank of actual shape ("<<dlist.size()<<") and of ";
            ss<<"maximum shape ("<<mlist.size()<<") do not match!";
            throw shape_mismatch_error(EXCEPTION_RECORD,ss.str());
        }
        _dims    = buffer_type(dlist);
        _maxdims = buffer_type(mlist);

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
