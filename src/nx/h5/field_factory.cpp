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
// Created on: Jul 17, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <pni/io/nx/h5/field_factory.hpp>
#include <pni/io/nx/h5/object_imp.hpp>
#include <pni/io/nx/h5/group_imp.hpp>
#include <pni/io/nx/h5/field_imp.hpp>
#include <pni/io/nx/h5/h5datatype.hpp>
#include <pni/io/nx/h5/h5dataspace.hpp>

namespace pni{
namespace io{
namespace nx{
namespace h5{

    field_imp field_factory::create(const object_imp &parent,
                                    const string &name,
                                    const object_imp &create_plist,
                                    const h5datatype &type,
                                    const h5dataspace &space)
    {
        return field_imp(object_imp(H5Dcreate2(parent.id(),
                                               name.c_str(),
                                               type.object().id(),
                                               space.object().id(),
                                               H5P_DEFAULT,
                                               create_plist.id(),
                                               H5P_DEFAULT)));
    }

    //------------------------------------------------------------------------
    object_imp field_factory::create_cplist()
    {
        return object_imp(H5Pcreate(H5P_DATASET_CREATE));
    }

    //------------------------------------------------------------------------
    object_imp 
    field_factory::create_cplist(const type_imp::index_vector_type &chunk)
    {
        if(!chunk.size())
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Chunk shape must not have rank zero!");

        object_imp cplist(create_cplist());

        //set chunked layout
        if(H5Pset_layout(cplist.id(),H5D_CHUNKED)<0)
            throw object_error(EXCEPTION_RECORD,
                  "Error setting dataset layout to chunked!\n\n"
                  +get_h5_error_string());

        //set the chunk shape
        if(H5Pset_chunk(cplist.id(),chunk.size(),chunk.data())<0)
            throw object_error(EXCEPTION_RECORD,
                  "Error setting chunk shape!\n\n"+get_h5_error_string());

        return cplist;
    }

    //-----------------------------------------------------------------------
    h5dataspace 
    field_factory::create_dataspace(const type_imp::index_vector_type &shape)
    {
        type_imp::index_vector_type current_dims(shape);

        if(current_dims.empty()) 
            throw size_mismatch_error(EXCEPTION_RECORD,
                    "Field shape must not be empty!");

        type_imp::index_vector_type maximum_dims(current_dims.size());
        std::fill(maximum_dims.begin(),maximum_dims.end(),H5S_UNLIMITED);

        return h5dataspace{current_dims,maximum_dims};
    }

   
    //-----------------------------------------------------------------------
    field_imp field_factory::create(const group_imp &parent,
                                    const string &name,
                                    type_id_t tid,
                                    const type_imp::index_vector_type &shape,
                                    const type_imp::index_vector_type &chunk,
                                    const h5filter &filter)
    {
        //if chunk and shape do not match we can stop immediately
        check_equal_size(shape,chunk,EXCEPTION_RECORD); 
                                    
        //create datatype and dataspace
        h5datatype type   = get_type(tid);
        h5dataspace space = create_dataspace(shape);
        
        //create creation property list
        object_imp plist = create_cplist(chunk);

        //apply filter
        filter.setup(plist);

        //create the field
        return create(parent.object(),name,plist,type,space);

    }
    


//end of namespace
}
}
}
}
