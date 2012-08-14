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
 * Implementation of the HDF5 dataset class
 *
 * Created on: Jan 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include <pni/utils/DBuffer.hpp>

#include "H5Dataset.hpp"
#include "H5ObjectType.hpp"
#include "H5Exceptions.hpp"
#include "H5Link.hpp"
#include "H5Selection.hpp"


namespace pni{
namespace nx{
namespace h5{
    //============implementation of private methods====================
    //throw a ShapeMissmatchError exception if dataset not scalar
    void H5Dataset::__throw_if_not_scalar(const ExceptionRecord &rec) const
    {
        String desc = "Dataset ["+this->name()+"] is not scalar!";
        if(_space.size()!=1)
            throw ShapeMissmatchError(rec,desc);
    }

    //===implementation of constructors and destructors================
    //implementation of the default constructor
    H5Dataset::H5Dataset():H5AttributeObject(){
    
    }

    //-----------------------------------------------------------------
    //implementation of the copy constructor
    H5Dataset::H5Dataset(const H5Dataset &o):
        H5AttributeObject(o),
        _space(o._space) 
    {
    }

    //-----------------------------------------------------------------
    //implementation of the copy conversion constructor
    H5Dataset::H5Dataset(const H5Object &o):H5AttributeObject(o)
    {
        //check if the type is ok for conversion
        if(object_type() != H5ObjectType::DATASET)
            throw H5DataSetError(EXCEPTION_RECORD,
                    "Object is not a dataset!");

        //copy the datatype and dataspace
        _space = __obtain_dataspace();
    }

    //-----------------------------------------------------------------
    //implementation of the move constrcutor
    H5Dataset::H5Dataset(H5Dataset &&o):
        H5AttributeObject(std::move(o)),
        _space(std::move(o._space)) 
    { }

    //-----------------------------------------------------------------
    //implementation of the move conversion constructor
    H5Dataset::H5Dataset(H5Object &&o):H5AttributeObject(std::move(o))
    {

        if(object_type() != H5ObjectType::DATASET)
            throw H5DataSetError(EXCEPTION_RECORD, 
                                "Object is not a dataset!");

        //move datatype and data space
        _space = __obtain_dataspace();
    }

    //-----------------------------------------------------------------
    //implementation of the constructor for a contigous array
    H5Dataset::H5Dataset(const String &n,const H5Group &g,
            const H5Datatype &t,const H5Dataspace &s)
    {
        
        //create link creation property list
        hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
        H5Pset_create_intermediate_group(lpl,1);

        //create the datase
        hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                lpl,H5P_DEFAULT,H5P_DEFAULT);
        if(did<0)
            throw H5DataSetError(EXCEPTION_RECORD, 
            "Cannot create dataset ["+n+"] below ["+path()+"]!");

        //set id
        H5Object::id(did);

        //get dataspace
        _space = __obtain_dataspace();

        //close property list
        H5Pclose(lpl);
    }


    //-----------------------------------------------------------------
    //implement construction from an object id
    H5Dataset::H5Dataset(const hid_t &oid):H5AttributeObject(oid)
    {

        if(object_type() != H5ObjectType::DATASET)
            throw H5DataSetError(EXCEPTION_RECORD,
                "Object ID does not belong to a dataset!");

        _space = H5Dataspace(H5Dget_space(id()));
    }

    //-----------------------------------------------------------------
    //implementation of the default destructor 
    H5Dataset::~H5Dataset()
    {
        _space.close();
        if(is_valid()) H5Dclose(id());
        H5Object::id(0);
    }

    //=========implementation of the assignment operators==============
    //implementation of the  copy assignment operator
    H5Dataset &H5Dataset::operator=(const H5Dataset &o)
    {
        if(this != &o){
            (H5AttributeObject &)(*this) = (H5AttributeObject &)o;
            _space = o._space;
        }
        return *this;
    }

    //-----------------------------------------------------------------
    //implementation of the  copy conversion assignment
    H5Dataset &H5Dataset::operator=(const H5Object &o)
    {
        if(o.object_type()!=H5ObjectType::DATASET)
            throw H5DataSetError(EXCEPTION_RECORD,
                    "Object is not a dataset!");

        if(this != &o)
        {
            (H5Object &)(*this) = o;
            _space = __obtain_dataspace();
        }
        return *this;
    }

    //-----------------------------------------------------------------
    //implementation of the  move assignment operator
    H5Dataset &H5Dataset::operator=(H5Dataset &&o)
    {
        if(this != &o)
        {
            (H5AttributeObject &)(*this) = std::move((H5AttributeObject
                        &)o);
            _space = std::move(o._space);
        }
        return *this;
    }

    //-----------------------------------------------------------------
    //! move conversion assignment
    H5Dataset &H5Dataset::operator=(H5Object &&o)
    {
        if(o.object_type() != H5ObjectType::DATASET)
            throw H5DataSetError(EXCEPTION_RECORD, 
                                 "Object is not a dataset!");

        if(this != &o)
        {
            (H5Object &)(*this) = std::move(o);
            _space = __obtain_dataspace();
        }
        return *this;
    }

    //=========implementation of inquery methods========================
    void H5Dataset::grow(const size_t &e,const size_t &n)
    {
        if(e>=rank())
        {
            std::stringstream ss;
            ss<<"Dimension index ("<<e<<") exceeds rank of ";
            ss<<"dataspace ["<<name()<<"] which is ("<<rank()<<")!";
            throw IndexError(EXCEPTION_RECORD,ss.str());
        }

        DBuffer<hsize_t> b(_space.rank());

        for(size_t i=0;i<_space.rank();i++) b[i] = _space[i];
        b[e] += n;

        herr_t err = H5Dset_extent(id(),b.ptr());
        if(err < 0)
            throw H5DataSetError(EXCEPTION_RECORD, 
                  "Grow of dataset ["+name()+"] failed!");

        //re-fetch the new dataspace
        _space.grow(e,n);
    }

    //------------------------------------------------------------------

    //------------------------------------------------------------------
    //implementation of selection creation  
    H5Selection H5Dataset::selection() const
    {

        if(_space.is_scalar())
            throw ShapeMissmatchError(EXCEPTION_RECORD, 
                    "You cannot create a selection from the scalar"
                    "dataset ["+name()+"]!");

        H5Selection selection(*this,_space.shape<std::vector<hsize_t> >(),0,1);
        return selection;
    }

    //------------------------------------------------------------------
    //implementation of writing a string scalar
    void H5Dataset::write(const String &b) const
    {
        if(size()!=1)
            throw ShapeMissmatchError(EXCEPTION_RECORD,
                    "Dataset is not scalar!");

        //select the proper memory data type
        
        H5Datatype mem_type(H5Dget_type(id()));
        const char *ptr = b.c_str();

        //write data to disk
        herr_t err = H5Dwrite(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                              H5P_DEFAULT,(const void *)&ptr);
        if(err<0)
            throw H5DataSetError(EXCEPTION_RECORD, 
                    "Error writing data to dataset!");
    }

    //------------------------------------------------------------------
    //implementation of reading string scalar
    void H5Dataset::read(String &b) const
    {
        if(size()!=1)
            throw ShapeMissmatchError(EXCEPTION_RECORD,
                    "Dataset is not scalar!");

        H5Datatype mem_type(H5Dget_type(id()));
        const char *ptr = nullptr;
        hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);

        //write data to disk
        herr_t err = H5Dread(id(),mem_type.id(),H5S_ALL,H5S_ALL,
                              xfer_plist,(void *)&ptr);
        if(err<0)
            throw H5DataSetError(EXCEPTION_RECORD, 
                    "Error writing data to dataset ["+name()+"]!");

        try{
            b = String(ptr);
        }catch(...){
            b = "";
        }

        H5Dvlen_reclaim(mem_type.id(),_space.id(),xfer_plist,&ptr);

    }

    //-----------------------------------------------------------------
    void H5Dataset::link(const String &linkname) const
    {
        H5Link::create(path(),parent(),linkname);
    }

    //------------------------------------------------------------------
    void H5Dataset::link(const H5Group &g,const String &n) const
    {
        H5Link::create(path(),g,n);
    }

    //------------------------------------------------------------------
    H5Group H5Dataset::parent() const
    {
        hid_t fid = H5Iget_file_id(id());
        hid_t gid = H5Oopen(fid,base().c_str(),H5P_DEFAULT);
        H5Group g(gid);
        H5Fclose(fid);
        H5Oclose(gid);

        return g;
    }



//end of namespace
}
}
}

