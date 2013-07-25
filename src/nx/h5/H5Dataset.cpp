/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Implementation of the HDF5 dataset class
 *
 * Created on: Jan 12, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include <pni/core/dbuffer.hpp>

#include "H5Dataset.hpp"
#include "H5ObjectType.hpp"
#include "h5link.hpp"
#include "../nxpath.hpp"
#include "../nxpath_utils.hpp"


namespace pni{
namespace io{
namespace nx{
namespace h5{
    //============implementation of private methods====================
    //throw a ShapeMissmatchError exception if dataset not scalar
    void H5Dataset::__throw_if_not_scalar(const exception_record &rec) const
    {
        string desc = "Dataset ["+this->name()+"] is not scalar!";
        if(_fspace.size()!=1)
            throw shape_mismatch_error(rec,desc);
    }

    //===implementation of constructors and destructors================
    //implementation of the default constructor
    H5Dataset::H5Dataset():H5AttributeObject(){ } 
    
    //-----------------------------------------------------------------
    //implementation of the copy constructor
    H5Dataset::H5Dataset(const H5Dataset &o):
        H5AttributeObject(o),
        _fspace(o._fspace), 
        _mspace(o._mspace)
    { }

    //-----------------------------------------------------------------
    //implementation of the copy conversion constructor
    H5Dataset::H5Dataset(const H5Object &o):H5AttributeObject(o)
    {
        //check if the type is ok for conversion
        if(object_type() != H5ObjectType::DATASET)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                    "Object is not a dataset!\n\n"+
                    get_h5_error_string());

        //copy the datatype and dataspace
        _fspace = __obtain_dataspace();
        _mspace = _fspace;
    }

    //-----------------------------------------------------------------
    //implementation of the move constrcutor
    H5Dataset::H5Dataset(H5Dataset &&o):
        H5AttributeObject(std::move(o)),
        _fspace(std::move(o._fspace)),
        _mspace(std::move(o._mspace))
    { }

    //-----------------------------------------------------------------
    //implementation of the move conversion constructor
    H5Dataset::H5Dataset(H5Object &&o):H5AttributeObject(std::move(o))
    {

        if(object_type() != H5ObjectType::DATASET)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                                "Object is not a dataset!\n\n"+
                                get_h5_error_string());

        //move datatype and data space
        _fspace = __obtain_dataspace();
        _mspace = _fspace;
    }

    //-----------------------------------------------------------------
    //implementation of the constructor for a contigous array
    H5Dataset::H5Dataset(const string &n,const H5Group &g,
            const H5Datatype &t,const H5Dataspace &s)
    {
        
        //create link creation property list
        hid_t lpl = H5Pcreate(H5P_LINK_CREATE);
        H5Pset_create_intermediate_group(lpl,1);

        //create the datase
        hid_t did = H5Dcreate2(g.id(),n.c_str(),t.id(),s.id(),
                lpl,H5P_DEFAULT,H5P_DEFAULT);
        if(did<0)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
            "Cannot create dataset ["+n+"] below ["+path()+"]!\n\n"+
            get_h5_error_string());

        //set id
        *this = H5Dataset(did);
        //close property list
        H5Pclose(lpl);
    }


    //-----------------------------------------------------------------
    //implement construction from an object id
    H5Dataset::H5Dataset(const hid_t &oid):H5AttributeObject(oid)
    {

        if(object_type() != H5ObjectType::DATASET)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                "Object ID does not belong to a dataset!\n\n"+
                get_h5_error_string());

        _fspace = H5Dataspace(H5Dget_space(id()));
        _mspace = _fspace;
    }

    //-----------------------------------------------------------------
    //implementation of the default destructor 
    H5Dataset::~H5Dataset()
    {
        _fspace.close();
        _mspace.close();
        if(is_valid()) H5Dclose(id());
        H5Object::reset_id();
    }

    //=========implementation of the assignment operators==============
    //implementation of the  copy assignment operator
    H5Dataset &H5Dataset::operator=(const H5Dataset &o)
    {
        if(this != &o)
        {
            H5AttributeObject::operator=(o);
            _fspace = o._fspace;
            _mspace = o._mspace;
        }
        return *this;
    }

    //-----------------------------------------------------------------
    //implementation of the  copy conversion assignment
    H5Dataset &H5Dataset::operator=(const H5Object &o)
    {
        if(o.object_type()!=H5ObjectType::DATASET)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD,
                    "Object is not a dataset!\n\n"+
                    get_h5_error_string());

        if(this != &o)
        {
            H5Object::operator=(o);
            //obtain the dataspace from the object
            _fspace = __obtain_dataspace();
            _mspace = _fspace;
        }
        return *this;
    }

    //-----------------------------------------------------------------
    //implementation of the  move assignment operator
    H5Dataset &H5Dataset::operator=(H5Dataset &&o)
    {
        if(this != &o)
        {
            H5AttributeObject::operator=(std::move(o));
            _fspace = std::move(o._fspace);
            _mspace = std::move(o._mspace);
        }
        return *this;
    }

    //-----------------------------------------------------------------
    //! move conversion assignment
    H5Dataset &H5Dataset::operator=(H5Object &&o)
    {
        if(o.object_type() != H5ObjectType::DATASET)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                  "Object is not a dataset!\n\n"+get_h5_error_string());

        if(this != &o)
        {
            H5Object::operator=(std::move(o));
            //obtain the dataspace from the object
            _fspace = __obtain_dataspace();
            _mspace = _fspace;
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
            throw index_error(EXCEPTION_RECORD,ss.str());
        }

        dbuffer<hsize_t> b(_fspace.rank());

        for(size_t i=0;i<_fspace.rank();i++) b[i] = _fspace[i];
        b[e] += n;

        herr_t err = H5Dset_extent(id(),b.ptr());
        if(err < 0)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                  "Grow of dataset ["+name()+"] failed!\n\n"+
                  get_h5_error_string());

        //re-fetch the new dataspace
        _fspace.grow(e,n);
        _mspace = _fspace;
    }

    //------------------------------------------------------------------
    void H5Dataset::write(const string *sptr) const
    {
        typedef const char * char_ptr_t;
        //select the proper memory data type
        
        H5Datatype mem_type(H5Dget_type(id()));
        char_ptr_t *ptr = new char_ptr_t[size()];
        for(size_t i=0;i<size();i++)
            ptr[i] = sptr[i].c_str();

        //write data to disk
        herr_t err = H5Dwrite(id(),mem_type.id(),_mspace.id(),_fspace.id(),
                              H5P_DEFAULT,(const void *)ptr);

        delete [] ptr; //free memory
        if(err<0)
            throw pni::io::nx::nxfield_error(EXCEPTION_RECORD, 
                    "Error writing data to dataset!\n\n"+
                    get_h5_error_string());
    }

    //-----------------------------------------------------------------
    void H5Dataset::read(string *sptr) const
    {
        typedef char * char_ptr_t;
        //select the proper memory data type
        
        H5Datatype mem_type(H5Dget_type(id()));
        char_ptr_t *ptr = new char_ptr_t[size()];
        hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);

        //write data to disk
        herr_t err = H5Dread(id(),mem_type.id(),_mspace.id(),_fspace.id(),
                              xfer_plist,(void *)ptr);
        if(err<0)
        {
            delete [] ptr; //free memory
            pni::io::nx::nxfield_error error(EXCEPTION_RECORD, 
                    "Error writing data to dataset ["+name()+"]!\n\n"+
                    get_h5_error_string());
            throw error;
        }

        for(size_t i=0;i<size();i++)
        {
            try
            {
                sptr[i] = string(ptr[i]);
            }
            catch(...)
            {
                sptr[i] = "";
            }
        }

        H5Dvlen_reclaim(mem_type.id(),_mspace.id(),xfer_plist,ptr);
        delete [] ptr;
    }


    //------------------------------------------------------------------
    H5Group H5Dataset::parent() const
    {
        hid_t fid = H5Iget_file_id(id());
        hid_t gid = H5Oopen(fid,base().c_str(),H5P_DEFAULT);
        H5Group g(gid);
        H5Fclose(fid);

        return g;
    }

    //-------------------------------------------------------------------------
    void H5Dataset::close() 
    {
        _fspace.close();
        _mspace.close();
        H5AttributeObject::close();
    }



//end of namespace
}
}
}
}
