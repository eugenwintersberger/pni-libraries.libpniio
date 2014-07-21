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
#include <pni/io/nx/h5/string_utils.hpp>
#include <pni/io/nx/h5/h5_error_stack.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{
    using pni::core::exception;
    using pni::core::shape_mismatch_error;
    using pni::core::string;

    //============implementation of private methods====================
    void field_imp::_update()
    {
        _file_space = h5dataspace(object_imp(H5Dget_space(_object.id())));
        _type       = h5datatype(object_imp(H5Dget_type(_object.id())));
        _memory_space = _file_space;
    }

    //===implementation of constructors and destructors================
    //implementation of the default constructor
    field_imp::field_imp() noexcept
        :_object(),
         _file_space(),
         _memory_space(),
         _type()
    { } 
    
    //-----------------------------------------------------------------
    //implementation of the copy conversion constructor
    field_imp::field_imp(object_imp &&o):
        _object(std::move(o)),
        _file_space(),
        _memory_space(),
        _type()
    {
        if(get_hdf5_type(_object) != h5object_type::DATASET)
            throw type_error(EXCEPTION_RECORD,
                    "Object is not an HDF5 dataset!");
        _update();
    }
    
    //-----------------------------------------------------------------
    //implementation of the copy constructor
    field_imp::field_imp(const field_imp &o)
        :_object(o._object),
         _file_space(o._file_space), 
         _memory_space(o._memory_space),
         _type(o._type)
    { }


    //-----------------------------------------------------------------
    //implementation of the move constrcutor
    field_imp::field_imp(field_imp &&o) noexcept
        :_object(std::move(o._object)),
         _file_space(std::move(o._file_space)),
         _memory_space(std::move(o._memory_space)),
         _type(std::move(o._type))
    { }

    //-----------------------------------------------------------------
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



    //=========implementation of the assignment operators==============
    //implementation of the  copy assignment operator
    field_imp &field_imp::operator=(const field_imp &o)
    {
        if(this == &o) return *this;

        _object       = o._object;
        _file_space   = o._file_space;
        _memory_space = o._memory_space;
        _type         = o._type;

        return *this;
    }

    //-----------------------------------------------------------------
    //implementation of the  move assignment operator
    field_imp &field_imp::operator=(field_imp &&o) noexcept
    {
        if(this == &o) return *this;

        _object       = std::move(o._object);
        _file_space   = std::move(o._file_space);
        _memory_space = std::move(o._memory_space);
        _type         = std::move(o._type);

        return *this;
    }


    //=========implementation of inquery methods========================
    void field_imp::grow(const size_t &e,const size_t &n)
    {
        if(e>=rank())
        {
            std::stringstream ss;
            ss<<"Dimension index ("<<e<<") exceeds rank of ";
            ss<<"dataspace ["<<get_path(_object)
              <<"] which is ("<<rank()<<")!";
            throw index_error(EXCEPTION_RECORD,ss.str());
        }

        type_imp::index_vector_type b(_file_space.rank());
        std::copy(_file_space.current_begin(),
                  _file_space.current_end(),
                  b.begin());
        b[e] += n;

        if(H5Dset_extent(_object.id(),b.data())<0)
            throw object_error(EXCEPTION_RECORD, 
                  "Grow of dataset ["+get_path(_object)
                  +"] failed!\n\n"+get_h5_error_string());

        //re-fetch the new dataspace
        _file_space.grow(e,n);
        _memory_space = _file_space;
    }

    //------------------------------------------------------------------------
    void field_imp::resize(const type_imp::index_vector_type &s)
    {
        if(s.size() != _file_space.rank())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                  "New shape does not have the same rank!");

        if(H5Dset_extent(_object.id(),s.data())<0)
            throw object_error(EXCEPTION_RECORD, 
                 "Resizing of dataset ["+get_path(_object)
                 +"] failed!\n\n"+ get_h5_error_string());

        _update();
    }


    //------------------------------------------------------------------------
    type_imp::index_vector_type field_imp::shape() const
    {
        type_imp::index_vector_type s(_memory_space.rank());
        std::copy(_memory_space.current_begin(),
                  _memory_space.current_end(),
                  s.begin());
        return s;
    }
    //------------------------------------------------------------------------
    type_id_t field_imp::type_id() const 
    { 
        return pni::io::nx::h5::type_id(_type); 
    }

    //------------------------------------------------------------------------
    size_t field_imp::size() const 
    { 
        return _memory_space.size(); 
    }
    
    //------------------------------------------------------------------------
    size_t field_imp::rank() const 
    { 
        return _memory_space.rank(); 
    }

    //------------------------------------------------------------------------
    void field_imp::_read_data(const h5datatype &memtype,
                               const h5dataspace &memspace,
                               const h5dataspace &filespace,
                               const object_imp &xfer_list,
                               void *ptr) const
    {
        if(H5Dread(_object.id(),memtype.object().id(),
                             memspace.object().id(),filespace.object().id(),
                             xfer_list.id(),ptr)<0)
        {
            io_error error(EXCEPTION_RECORD, 
                    "Error reading data to dataset ["
                    +get_path(_object)+"]!\n\n"+
                    get_h5_error_string());
            throw error;
        }
    }
    
    //------------------------------------------------------------------------
    void field_imp::read(type_id_t tid,void *ptr) const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot read data from invalid object!");

        if((tid==type_id_t::STRING) && is_vl_string(_type))
        {
            char_ptr_vector_type ptrs(size());

            //need here a more general guard for HDF5 objects
            object_imp xfer_plist(H5Pcreate(H5P_DATASET_XFER));
            _read_data(_type,_memory_space,_file_space,xfer_plist,
                       static_cast<void*>(ptrs.data()));
       
            copy_from_vector(ptrs,static_cast<string*>(ptr));
            H5Dvlen_reclaim(_type.object().id(),
                            _memory_space.object().id(),
                            xfer_plist.id(),
                            ptrs.data());
        }
        else if((tid==type_id_t::STRING) && is_static_string(_type))
        {
            char_vector_type ptrs(static_string_size(_type)*size());

            _read_data(_type,_memory_space,_file_space,
                       object_imp(H5Pcreate(H5P_DATASET_XFER)),
                       static_cast<void*>(ptrs.data()));

            copy_from_vector(ptrs,size(),static_string_size(_type),
                             static_cast<string *>(ptr));
        }
        else
        {
            //select the proper memory data type
            const h5datatype &mem_type = get_type(tid);

            _read_data(mem_type,_memory_space,_file_space,
                       object_imp(H5Pcreate(H5P_DATASET_XFER)),
                       ptr);
        }
    }

    //------------------------------------------------------------------------
    void field_imp::write(type_id_t tid,const void *ptr) const
    {
        if(!is_valid())
            throw invalid_object_error(EXCEPTION_RECORD,
                    "Cannot write data to invalid object!");

        if(tid == type_id_t::STRING)
        {
            auto *sptr = static_cast<const string*>(ptr);
            char_const_ptr_vector_type data(size());
            
            h5datatype mem_type(object_imp(H5Dget_type(_object.id())));

            size_t index=0;
            for(auto &v: data) v = sptr[index++].c_str();

            _write_data(mem_type,_memory_space,_file_space,
                        static_cast<const void*>(data.data()));
        }
        else
        {
            //select the proper memory data type
            const h5datatype &mem_type = get_type(tid);

            _write_data(mem_type,_memory_space,_file_space,ptr);
        }
    }

    //------------------------------------------------------------------------
    void field_imp::_write_data(const h5datatype &memtype,
                                const h5dataspace &memspace,
                                const h5dataspace &filespace,
                                const void *ptr) const
    {
        //write data to disk
        if(H5Dwrite(_object.id(),memtype.object().id(),memspace.object().id(),
                    filespace.object().id(),H5P_DEFAULT,ptr)<0)
            throw io_error(EXCEPTION_RECORD, 
                "Error writing data to dataset ["
                +get_path(_object)+"]!\n\n"+
                get_h5_error_string());
    }
    //-------------------------------------------------------------------------
    void field_imp::close() 
    {
        _file_space = h5dataspace();
        _memory_space = h5dataspace();
        _type = h5datatype();
        _object.close();
    }

    //------------------------------------------------------------------------
    string field_imp::name() const
    {
        return get_name(_object);
    }

    //------------------------------------------------------------------------
    object_imp field_imp::parent() const
    {
        return get_parent(_object);
    }

    //------------------------------------------------------------------------
    string field_imp::filename() const 
    {
        return get_filename(_object);
    }

    //------------------------------------------------------------------------
    bool field_imp::is_valid() const
    {
        return _object.is_valid() && 
               _file_space.object().is_valid() && 
               _memory_space.object().is_valid() && 
               _type.object().is_valid();
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
    size_t field_imp::nattr() const noexcept
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
    void field_imp::apply_selection(const type_imp::selection_vector_type &s)
        const
    {
        //create an array selection
        array_selection asel = array_selection::create(s);
        
        //create buffers
        auto offset = asel.offset<type_imp::index_vector_type>();
        auto stride = asel.stride<type_imp::index_vector_type>();
        auto count = asel.full_shape<type_imp::index_vector_type>();

        //need to throw an exception if the rank of the selection and
        //that of the 
        if(offset.size() != _file_space.rank())
            throw shape_mismatch_error(EXCEPTION_RECORD,
                    "Selection and field rank do not match!");

        //apply the selection
        herr_t err = H5Sselect_hyperslab(_file_space.object().id(),
                H5S_SELECT_SET,offset.data(),stride.data(),count.data(),
                nullptr);
        if(err<0)
            throw object_error(EXCEPTION_RECORD,
                    "Error applying selection to dataset!\n\n"+
                    get_h5_error_string());

        //need to set the memory dataspace to the effective shape of the
        //selection
        _memory_space = h5dataspace(asel.shape<type_imp::index_vector_type>());

    }

    //------------------------------------------------------------------------
    void field_imp::clear_selections() const
    {
        //this should be quite easy - there is nothing special we have
        ///to do.
        if(_file_space.object().is_valid())
        {
            H5Sselect_all(_file_space.object().id());
            _memory_space = _file_space;
        }
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
    
//end of namespace
}
}
}
}
