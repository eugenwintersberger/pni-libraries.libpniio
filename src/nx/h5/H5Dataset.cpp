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
// Created on: Jan 12, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/current_function.hpp>

#include <pni/io/nx/h5/H5Dataset.hpp>
#include <pni/io/nx/h5/H5ObjectType.hpp>
#include <pni/io/nx/nxpath.hpp>


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

        size_vector_t b(_fspace.rank());

        for(size_t i=0;i<_fspace.rank();i++) b[i] = _fspace[i];
        b[e] += n;

        herr_t err = H5Dset_extent(id(),b.data());
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
        //select the proper memory data type
        H5Datatype mem_type(H5Dget_type(id()));
        
        if(H5Tis_variable_str(mem_type.id()))
            _read_vl_strings(sptr,mem_type);
        else
            _read_static_strings(sptr,mem_type);
    }

    //-------------------------------------------------------------------------
    void H5Dataset::_read_vl_strings(string *s,H5Datatype &stype) const
    {
        std::vector<char *> ptrs(size());

        //need here a more general guard for HDF5 objects
        hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);

        //read data from disk
        herr_t err = H5Dread(id(),stype.id(),_mspace.id(),_fspace.id(),
                              xfer_plist,(void *)ptrs.data());
        if(err<0)
        {
            H5Pclose(xfer_plist); //close the transfer property list
            pni::io::nx::nxfield_error error(EXCEPTION_RECORD, 
                    "Error reading data to dataset ["+name()+"]!\n\n"+
                    get_h5_error_string());
            throw error;
        }

        for(size_t i=0;i<size();i++)
        {
            try
            {
                s[i] = string(ptrs[i]);
            }
            catch(...)
            {
                s[i] = "";
            }
        }

        H5Dvlen_reclaim(stype.id(),_mspace.id(),xfer_plist,ptrs.data());
        H5Pclose(xfer_plist); //close the transfer property list
    }

    //-------------------------------------------------------------------------
    void H5Dataset::_read_static_strings(string *s,H5Datatype &stype) const
    {
        size_t strsize = H5Tget_size(stype.id());

        std::vector<char> ptrs(strsize*size());

        //read data from disk
        herr_t err = H5Dread(id(),stype.id(),_mspace.id(),_fspace.id(),
                              H5P_DEFAULT,(void *)ptrs.data());
        if(err<0)
        {
            pni::io::nx::nxfield_error error(EXCEPTION_RECORD, 
                    "Error reading data to dataset ["+name()+"]!\n\n"+
                    get_h5_error_string());
            throw error;
        }

        for(size_t i=0;i<size();i++)
            s[i] = string(ptrs.data()+i*strsize,strsize);
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
