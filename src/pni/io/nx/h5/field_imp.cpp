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
// Created on: Jul 16, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <vector>
#include <sstream>

#include <pni/core/arrays.hpp>
#include <pni/core/error.hpp>

#include <pni/io/nx/h5/field_imp.hpp>
#include <pni/io/nx/h5/field_factory.hpp>
#include <pni/io/nx/h5/hdf5_utilities.hpp>
#include <pni/io/nx/h5/attribute_utils.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>
#include <pni/io/nx/h5/selection_guard.hpp>
#include "../../pni/io/nx/h5/string_formatter_factory.hpp"
#include "../../pni/io/nx/h5/string_utils.hpp"

namespace pni{
namespace io{
namespace nx{
namespace h5{
    using namespace pni::core;

    //============implementation of private methods====================
    void field_imp::_update()
    {
        //obtain the dataspace on the file
        _file_space = h5dataspace(object_imp(H5Dget_space(_object.id())));
        //we cannot do more here as the parameters of a selection 
        //cannot be retrieved from the dataspace
        _selection = selection(_file_space.rank());
    }

    //===implementation of constructors and destructors================
    //implementation of the default constructor
    field_imp::field_imp() noexcept
        :_object(),
         _file_space(),
         _selection(),
         _selection_applied(false)
    { } 
    
    //-----------------------------------------------------------------
    //implementation of the copy conversion constructor
    field_imp::field_imp(object_imp &&o):
        _object(std::move(o)),
        _file_space(),
        _selection(),
        _selection_applied(false)
    {
        if(get_hdf5_type(_object) != h5object_type::DATASET)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not an HDF5 dataset!");
        _update();
    }
    
    //---------------------------------------------------------------------
    field_imp::field_imp(const group_imp &parent,
                         const string &name,
                         type_id_t tid,
                         const type_imp::index_vector_type &shape,
                         const type_imp::index_vector_type &chunk,
                         const h5filter &filter)
    {
        *this = field_factory::create(parent,name,tid,shape,chunk,
                                      filter);
    }

    //------------------------------------------------------------------------
    void field_imp::grow(const size_t &e,const size_t &n) 
    {
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot grow invalid dataset!");

        //these methods will throw an exception if e exceeds the rank 
        //of the dataspaces
        _file_space.grow(e,n);

        //if(H5Dset_extent(_object.id(),b.data())<0)
        if(H5Dset_extent(_object.id(),_file_space.shape().data())<0)
            throw object_error(EXCEPTION_RECORD, 
                  "Grow of dataset ["+get_path(_object)
                  +"] failed!\n\n"+get_h5_error_string());

    }


    //=========implementation of inquery methods========================

    //------------------------------------------------------------------------
    type_imp::index_vector_type field_imp::shape() const
    {
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot obtain the shape of an invalid field!");

        if(_selection_applied)
            return effective_shape(_selection);
        else
            return _file_space.shape();
    }
    //------------------------------------------------------------------------
    pni::core::type_id_t field_imp::type_id() const 
    { 
        using pni::io::nx::h5::type_id;
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot obtain type from an invalid field!");

        return type_id(h5datatype(object_imp(H5Dget_type(_object.id())))); 
    }

    //------------------------------------------------------------------------
    size_t field_imp::size() const 
    { 
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot obtain the size from an invalid field!");

        if(_selection_applied)
            return pni::io::nx::h5::size(_selection); 
        else
            return _file_space.size();
    }
    
    //------------------------------------------------------------------------
    size_t field_imp::rank() const 
    { 
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot determine the rank of an invalid field!");
       
        if(_selection_applied)
            return effective_rank(_selection); 
        else
            return _file_space.rank();
    }

    //------------------------------------------------------------------------
    void field_imp::_read_data(const h5datatype &memtype,
                               const h5dataspace &memspace,
                               const h5dataspace &filespace,
                               const object_imp &xfer_list,
                               void *ptr) const
    {
        typedef selection_guard<h5dataspace> guard_type;
        guard_type guard(_selection,_file_space,_selection_applied);

        if(H5Dread(_object.id(),memtype.object().id(),
                             memspace.id(),filespace.id(),
                             xfer_list.id(),ptr)<0)
            throw io_error(EXCEPTION_RECORD, 
                    "Error reading data to dataset ["
                    +get_path(_object)+"]!\n\n"+
                    get_h5_error_string());
    }
    
    //------------------------------------------------------------------------
    void field_imp::read(type_id_t tid,
                         const type_imp::index_vector_type &shape,
                         void *ptr) const
    {
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot read data from invaliid field!");
        h5datatype file_type{object_imp(H5Dget_type(_object.id()))};
        const h5datatype &memory_type = get_type(tid);
        h5dataspace memory_space{shape};

        if((tid==type_id_t::STRING) && is_vl_string(file_type))
        {
            char_ptr_vector_type ptrs(size());

            //need here a more general guard for HDF5 objects
            object_imp xfer_plist(H5Pcreate(H5P_DATASET_XFER));
            _read_data(memory_type,memory_space,_file_space,xfer_plist,
                       static_cast<void*>(ptrs.data()));
       
            copy_from_vector(ptrs,size(),static_cast<string*>(ptr),
                             string_formatter_factory::create(file_type));
            H5Dvlen_reclaim(memory_type.object().id(),
                            memory_space.id(),
                            xfer_plist.id(),
                            ptrs.data());
        }
        else if((tid==type_id_t::STRING) && is_static_string(file_type))
        {
            char_vector_type ptrs(static_string_size(file_type)*size());

            _read_data(memory_type,memory_space,_file_space,
                       object_imp(H5Pcreate(H5P_DATASET_XFER)),
                       static_cast<void*>(ptrs.data()));

            copy_from_vector(ptrs,size(),static_string_size(file_type),
                             static_cast<string *>(ptr),
                            string_formatter_factory::create(file_type));
        }
        else
            _read_data(memory_type,memory_space,_file_space,
                       object_imp(H5Pcreate(H5P_DATASET_XFER)),
                       ptr);
    }

    //------------------------------------------------------------------------
    void field_imp::write(type_id_t tid,
                          const type_imp::index_vector_type &shape,
                          const void *ptr) const
    {
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot write data to invalid object!");

        const h5datatype &memory_type = get_type(tid);
        h5dataspace memory_space{shape};

        if(_selection_applied)
            memory_space = h5dataspace(_selection.count());


        if(tid == type_id_t::STRING)
        {
            auto *sptr = static_cast<const string*>(ptr);
            char_const_ptr_vector_type data(size());
            
            size_t index=0;
            for(auto &v: data) v = sptr[index++].c_str();

            _write_data(memory_type,memory_space,_file_space,
                        static_cast<const void*>(data.data()));
        }
        else
        {
            _write_data(memory_type,memory_space,_file_space,ptr);
        }
    }


    //------------------------------------------------------------------------
    void field_imp::_write_data(const h5datatype &memtype,
                                const h5dataspace &memspace,
                                const h5dataspace &filespace,
                                const void *ptr) const
    {
        typedef selection_guard<h5dataspace> guard_type;
        guard_type guard(_selection,_file_space,_selection_applied);

        //write data to disk
        if(H5Dwrite(_object.id(),memtype.object().id(),memspace.id(),
                    filespace.id(),H5P_DEFAULT,ptr)<0)
            throw io_error(EXCEPTION_RECORD, 
                "Error writing data to dataset ["
                +get_path(_object)+"]!\n\n"+
                get_h5_error_string());

    }

    //-------------------------------------------------------------------------
    void field_imp::close() 
    {
        _file_space = h5dataspace();
        _object.close();
    }

    //------------------------------------------------------------------------
    string field_imp::name() const
    {
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot retrieve name of invalid field!");

        return get_name(_object);
    }

    //------------------------------------------------------------------------
    object_imp field_imp::parent() const
    {
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot obtain parent of an invalid field!");

        return get_parent(_object);
    }

    //------------------------------------------------------------------------
    string field_imp::filename() const 
    {
        _throw_if_not_valid(EXCEPTION_RECORD,
                            "Cannot obtain filename from an invalid field!");

        return get_filename(_object);
    }

    //------------------------------------------------------------------------
    bool field_imp::is_valid() const
    {
        return _object.is_valid() && _file_space.is_valid() ;
    }

    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(const string &name) const 
    {
        return attribute_imp(get_attribute_by_name(_object,name));
    }

    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(size_t i) const
    {
        return attribute_imp(get_attribute_by_index(_object,i));
    }

    //-----------------------------------------------------------------------
    size_t field_imp::nattr() const 
    {
        return get_number_of_attributes(_object);
    }

    //-----------------------------------------------------------------------
    bool field_imp::has_attr(const string &name) const
    {
        return has_attribute(_object,name);
    }
     
    //------------------------------------------------------------------------
    void field_imp::del_attr(const string &name) const
    {
        delete_attribute(_object,name);
    }
    
    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(const string &name,type_id_t tid,
                                  bool overwrite) const
    {
        return attribute_imp(create_attribute(_object,
                                              name,
                                              get_type(tid),
                                              h5dataspace(),
                                              overwrite));
    }

    //------------------------------------------------------------------------
    attribute_imp field_imp::attr(const string &name,type_id_t tid,
                                  const type_imp::index_vector_type &shape,
                                  bool overwrite) const
    {
        return attribute_imp(create_attribute(_object,
                                              name,
                                              get_type(tid),
                                              h5dataspace(shape),
                                              overwrite));
    }

    //========================================================================
    // SELECTION RELATED METHODS
    //========================================================================
    void field_imp::apply_selection(const type_imp::selection_vector_type &s)
    {  
        if(s.size() != _file_space.rank())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Field and selection rank do not match!");

        _selection.update(s);
        _selection_applied = true;
    }

    //------------------------------------------------------------------------
    void field_imp::clear_selections() 
    {
        _selection_applied=false;
    }

    
//end of namespace
}
}
}
}
