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
//  Created on: Jul 16, 2014
//      Author: Eugen Wintersberger
//

#include <pni/io/nx/h5/file_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/attribute_imp.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>

#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/nxexceptions.hpp>

#include <sstream>

namespace pni{
namespace io{
namespace nx{
namespace h5{

    //=================private functions=======================================
    bool is_family_filename(const string &fname)
    {
        if(fname.find("%")!=string::npos) return true;
        return false;
    }


    //=========Implementation fo constructors an destructors===================
    //implementation of the default constructor
    file_imp::file_imp() noexcept
        :_object()
    {}
   
    //-------------------------------------------------------------------------
    //implementation of copy constructor
    file_imp::file_imp(const file_imp &o)
        :_object(o._object)
    {}

    //--------------------------------------------------------------------------
    //implementation of the move constructor
    file_imp::file_imp(file_imp &&o) noexcept
        :_object(std::move(o._object))
    {}

    //-------------------------------------------------------------------------
    file_imp::file_imp(object_imp &&o)
        :_object(std::move(o))
    {
        if(get_hdf5_type(_object)!=h5object_type::FILE)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not a file object!");
    }

    //=================Implementation of assignment operators==================
    file_imp &file_imp::operator=(file_imp &&o) noexcept
    {
        if(this == &o) return *this;

        _object = std::move(o._object);

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of copy assignment
    file_imp &file_imp::operator=(const file_imp &o)
    {
        if(this == &o) return *this;

        _object = o._object;

        return *this;
    }


    //=================Implementation of file specific methods=================
    void file_imp::close()
    {
        //check for open objects in the file
        if(_object.is_valid()) flush();

        _object.close();
    }
    
    //-------------------------------------------------------------------------
    file_imp file_imp::open(const string &path,bool ro)
    {
        //check if the file is a valid HDF5 file
        if(!H5Fis_hdf5(path.c_str()))
            throw type_error(EXCEPTION_RECORD, 
                  "File ["+path+"] is not an HDF5 file!\n\n"+
                  get_h5_error_string());

        object_imp acc_plist(H5Pcreate(H5P_FILE_ACCESS));

        //need to determine the file driver used to create the file: 
        //A possible solution would be to check the file name (could reuse the 
        //testing code from above).
        if(is_family_filename(path))
            H5Pset_fapl_family(acc_plist.id(),H5F_FAMILY_DEFAULT,H5P_DEFAULT);

        //open the file in the appropriate mode
        if(ro)
            return file_imp(object_imp(H5Fopen(path.c_str(),
                                               H5F_ACC_RDONLY,
                                               acc_plist.id())));
        else
            return file_imp(object_imp(H5Fopen(path.c_str(),
                                               H5F_ACC_RDWR,
                                               acc_plist.id())));
    }


    //-------------------------------------------------------------------------
    file_imp file_imp::create(const string &n,bool overwrite,ssize_t ssize)
    {
        //create property lists for file creation an access
        object_imp create_plist(H5Pcreate(H5P_FILE_CREATE));

        object_imp acc_plist(H5Pcreate(H5P_FILE_ACCESS));

        if(ssize > 0)
            //enable splitting
            H5Pset_fapl_family(acc_plist.id(),ssize*1024*1024,H5P_DEFAULT);

        object_imp file;
        if(overwrite)
            file = object_imp(H5Fcreate(n.c_str(),
                                        H5F_ACC_TRUNC,
                                        create_plist.id(),
                                        acc_plist.id()));
        else
            file = object_imp(H5Fcreate(n.c_str(),
                                        H5F_ACC_EXCL,
                                        create_plist.id(),
                                        acc_plist.id()));

        //in the end we need to set the HDF5 version to the correct
        //value
        unsigned major,minor,rel;
        H5get_libversion(&major,&minor,&rel);
        std::ostringstream vstring;
        vstring<<major<<"."<<minor<<"."<<rel;
   
        attribute_imp a(create_attribute(file,
                                         "HDF5_verison",
                                         get_type(type_id_t::STRING),
                                         h5dataspace(),
                                         true));
        string version(vstring.str());
        a.write(type_id_t::STRING,&version);

        return file_imp(std::move(file));
    }

    //-------------------------------------------------------------------------
    void file_imp::flush() const
    {
        if(_object.is_valid()) 
            H5Fflush(_object.id(),H5F_SCOPE_LOCAL);
    }
   
    //------------------------------------------------------------------------
    bool file_imp::is_valid() const
    {
        return _object.is_valid();
    }

    //-------------------------------------------------------------------------
    bool file_imp::is_readonly() const
    {
        unsigned int stat;
        H5Fget_intent(_object.id(),&stat);

        if(stat==H5F_ACC_RDWR) return false;
        return true;
    }
    
    //------------------------------------------------------------------------
    group_imp file_imp::root() const
    {
        return group_imp(object_imp(H5Oopen(_object.id(),"/",H5P_DEFAULT)));
    }

//end of namespace
}
}
}
}
