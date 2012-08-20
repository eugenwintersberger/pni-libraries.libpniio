/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of a general HDF5 Dataspace object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#include "H5Dataspace.hpp"
#include "H5Exceptions.hpp"



namespace pni{
namespace nx {
namespace h5 {

    //====================private methods======================================

    //implementation of the buffer allocation routine
    void H5Dataspace::__setup_buffers()
    {
        if(!is_scalar())
        {
            _maxdims.allocate(rank());
            _dims.allocate(rank());
            H5Sget_simple_extent_dims(id(),
                    const_cast<hsize_t*>(_dims.ptr()),
                    const_cast<hsize_t*>(_maxdims.ptr()));
        }
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::__setup_dataspace()
    {

        herr_t err = H5Sset_extent_simple(id(),_dims.size(),_dims.ptr(),_maxdims.ptr());
                        
        if(err<0)
        {
            H5DataSpaceError error(EXCEPTION_RECORD,
                    "Cannot create HDF5 dataspace!");
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
    //implementation of the copy conversion constructor
    H5Dataspace::H5Dataspace(const H5Object &o):H5Object(o)
    {
        //now we have to set the shape object
        __setup_buffers();
    }

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    H5Dataspace::H5Dataspace(H5Dataspace &&o):
        H5Object(std::move(o)),
        _maxdims(std::move(o._maxdims)),
        _dims(std::move(o._dims))
    { }

    //-------------------------------------------------------------------------
    //implementation of the move conversion constructor
    H5Dataspace::H5Dataspace(H5Object &&o):H5Object(std::move(o))
    {
        //this is a perfekt application for the __set_buffers() method
        __setup_buffers();
    }


    //-------------------------------------------------------------------------
    //construct dataspace form initializer list
    H5Dataspace::H5Dataspace(const std::initializer_list<hsize_t> &list):
        H5Object(H5Screate(H5S_SCALAR)),
        _maxdims(list),
        _dims(list)
    {
        __setup_dataspace();
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
            throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
        }

        //finally resize the dataspace
        __setup_dataspace();
    }

    //-------------------------------------------------------------------------
    H5Dataspace::H5Dataspace(hid_t tid):H5Object(tid)
    {
        __setup_buffers();
    }

    //-------------------------------------------------------------------------
    H5Dataspace::~H5Dataspace()
    {
        if(is_valid()) H5Sclose(id());
        //reset the object ID
        H5Object::id(0);
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
    //implementation of the copy conversion assignment operator
    H5Dataspace &H5Dataspace::operator=(const H5Object &o)
    {
        if(this == &o) return *this;
            
        H5Object::operator=(o);
        __setup_buffers();

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

    //-------------------------------------------------------------------------
    //implementation of the move conversion operator
    H5Dataspace &H5Dataspace::operator=(H5Object &&o)
    {
        if(this == &o) return *this;

        H5Object::operator=(std::move(o));
        __setup_buffers();

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
        return (size_t)H5Sget_select_npoints(id());
    }

    //-------------------------------------------------------------------------
    size_t H5Dataspace::operator[](size_t i) const 
    {
        return dim(i);
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::close()
    {
        if(is_valid()) H5Sclose(id());
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::resize(const std::initializer_list<hsize_t> &list)
    {
        _dims.allocate(list.size());
        _maxdims.allocate(list.size());

        std::copy(list.begin(),list.end(),_dims.begin());
        std::copy(list.begin(),list.end(),_maxdims.begin());

        __setup_dataspace();
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
            throw ShapeMissmatchError(EXCEPTION_RECORD,ss.str());
        }
        std::copy(dlist.begin(),dlist.end(),_dims.begin());
        std::copy(mlist.begin(),mlist.end(),_maxdims.begin());

        __setup_dataspace();
    }

    //-------------------------------------------------------------------------
    void H5Dataspace::grow(size_t dim,size_t ext)
    {

        if(dim >= rank())
        {
            std::stringstream ss;
            ss<<"Dimension index ("<<dim<<") exceeds rank (";
            ss<<rank()<<")!";
            throw IndexError(EXCEPTION_RECORD,ss.str());
        }

        //set extension
        _dims[dim] += ext;
        __setup_dataspace();
    }



    //======================operators==========================================
    std::ostream &operator<<(std::ostream &o,const H5Dataspace &s)
    {
        o<<"HDF5 Dataspace: "<<s.rank()<<" dimensions"<<std::endl;
        o<<"act. # of elements: ( ";
        for(size_t i=0;i<s.rank();i++){
            o<<s._dims[i]<<" ";
        }
        o<<")";

        return o;
    }

        
//end of namespace
}
}
}
            
