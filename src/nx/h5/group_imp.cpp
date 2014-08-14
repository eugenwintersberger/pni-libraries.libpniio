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


#include <sstream>
extern "C"{
#include<hdf5.h>
}

#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/nxexceptions.hpp>
#include <pni/io/nx/nxpath.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{

    //============implementation of constructors and destructors===============
    //implementation of the default constructor
    group_imp::group_imp() noexcept
        :_object()
    {}

    //-------------------------------------------------------------------------
    group_imp::group_imp(object_imp &&o) 
        :_object(o)
    {
        if(get_hdf5_type(_object)!=h5object_type::GROUP)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not a group instance!");
    }

    //-------------------------------------------------------------------------
    //implementation of the standard constructor
    group_imp::group_imp(const group_imp &parent,const string &name)
    {
        _object = object_imp(H5Gcreate2(parent.object().id(),
                                        name.c_str(),
                                        H5P_DEFAULT,
                                        H5P_DEFAULT,
                                        H5P_DEFAULT));
    }

    //-------------------------------------------------------------------------
    object_imp group_imp::at(const string &name) const
    {
        if(!has_child(name))
            throw key_error(EXCEPTION_RECORD,
                    "Group ["+get_path(_object)+"] has no child ["
                    +name+"]!\n\n"+get_h5_error_string());

        
        return object_imp(H5Oopen(_object.id(),name.c_str(),H5P_DEFAULT));
    }

    //-------------------------------------------------------------------------
    object_imp group_imp::at(size_t i) const
    {
        if(i >= size())
        {
            std::stringstream sstream;
            sstream<<"Index ("<<i<<") exceeds number of child nodes ("
                <<size()<<")!";
            throw index_error(EXCEPTION_RECORD,sstream.str());
        }

        return object_imp(H5Oopen_by_idx(_object.id(),".",
                                         H5_INDEX_NAME,
                                         H5_ITER_INC,
                                         hsize_t(i),
                                         H5P_DEFAULT));
    }

    //-------------------------------------------------------------------------
    bool group_imp::has_child(const string &name) const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Group instance not valid!");

        object_imp plist(H5Pcreate(H5P_LINK_ACCESS));
        H5Pset_nlinks(plist.id(),1);
        htri_t result = H5Lexists(_object.id(),name.c_str(),plist.id());
        if(result>0)
            return true;
        else if(result == 0)
            return false;
        else
            throw object_error(EXCEPTION_RECORD,
                    "Could not obtain link information from gruop!\n\n"
                    +get_h5_error_string());
    }

    //------------------------------------------------------------------------
    string group_imp::filename() const
    {
        return get_filename(_object);
    }

    //-------------------------------------------------------------------------
    size_t group_imp::size() const
    {
        H5G_info_t ginfo;
        herr_t err = H5Gget_info(_object.id(),&ginfo);
        if(err < 0)
            throw object_error(EXCEPTION_RECORD,
                    "Cannot obtain group information!\n\n"+
                    get_h5_error_string());

        return ginfo.nlinks;
    }            

    //------------------------------------------------------------------------
    string group_imp::name() const
    {
        return get_name(_object);
    }

    //------------------------------------------------------------------------
    object_imp group_imp::parent() const
    {
        return get_parent(_object);
    }

    //------------------------------------------------------------------------
    void group_imp::close()
    {
        _object.close();
    }

    //------------------------------------------------------------------------
    bool group_imp::is_valid() const
    {
        return _object.is_valid();
    }

    //------------------------------------------------------------------------
    attribute_imp group_imp::attr(const string &name) const 
    {
        return attribute_imp(get_attribute_by_name(_object,name));
    }

    //------------------------------------------------------------------------
    attribute_imp group_imp::attr(size_t i) const
    {
        return attribute_imp(get_attribute_by_index(_object,i));
    }

    //-----------------------------------------------------------------------
    size_t group_imp::nattr() const noexcept
    {
        return get_number_of_attributes(_object);
    }

    //-----------------------------------------------------------------------
    bool group_imp::has_attr(const string &name) const
    {
        return has_attribute(_object,name);
    }
     
    //------------------------------------------------------------------------
    void group_imp::del_attr(const string &name) const
    {
        delete_attribute(_object,name);
    }

    //------------------------------------------------------------------------
    attribute_imp group_imp::attr(const string &name,type_id_t tid,
                       bool overwrite) const
    {
        return attribute_imp(create_attribute(_object,
                                              name,
                                              get_type(tid),
                                              h5dataspace(),
                                              overwrite));
    }
   
    //-------------------------------------------------------------------------
    attribute_imp group_imp::attr(const string &name,type_id_t tid,
                                  const type_imp::index_vector_type &shape,
                                  bool overwrite) const
    {
        return attribute_imp(create_attribute(_object,
                                              name,
                                              get_type(tid),
                                              h5dataspace(shape),
                                              overwrite));
    }

    //------------------------------------------------------------------------
    const object_imp &group_imp::object() const 
    { 
        return _object; 
    }
//end of namespace
}
}
}
}

