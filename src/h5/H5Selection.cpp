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
 * Implementation of a HDF5 selection class.
 *
 * Created on: Jan 16, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <sstream>
#include <cstdarg>
#include "H5Selection.hpp"
#include "H5Exceptions.hpp"


namespace pni{
namespace nx{
namespace h5{
            //==============Implementation of constructors and destructors======
            //implementation of the destructor
            H5Selection::~H5Selection()
            {
                _offset.free();
                _stride.free();
                _counts.free();
                _dataset = nullptr;

            }

            //==============Implementation of assignment operators==============
            //implementation of the copy assignment operator
            H5Selection &H5Selection::operator=(const H5Selection &o)
            {

                if(this != &o){
                    _stride  = o._stride;
                    _offset  = o._offset;
                    _counts  = o._counts;
                    _dataset = o._dataset;
                }

                return *this;
            }

            //------------------------------------------------------------------
            //implementation of the move assignment operator
            H5Selection &H5Selection::operator=(H5Selection &&o)
            {
                //original names 
                if(this != &o){
                    _stride  = std::move(o._stride);
                    _offset  = std::move(o._offset);
                    _counts  = std::move(o._counts);
                    _dataset = o._dataset;
                    o._dataset = nullptr;
                }
                return *this;
            }

            //========implementation of inquery methods=========================
            //get size
            size_t H5Selection::size() const
            {
                if(rank() == 0) return 1;
                
                size_t s = 1;
#ifdef NOFOREACH
                for(size_t i=0;i<rank();i++) s *= _counts[i];
#else
                for(auto v: _counts) s *= v;
#endif

                return s;
            }

            

            //------------------------------------------------------------------
            //return reference to the dataspace
            H5Dataspace H5Selection::space() const
            {
                H5Dataspace s(shape<std::vector<hsize_t> >());
                return s;
            }

            
            //=================implementation of modifier methods===============
            //------------------------------------------------------------------
            void H5Selection::offset(const std::initializer_list<hsize_t> &l)
            {
                if(l.size() != rank())
                {
                    std::stringstream ss;
                    ss<<"Size of initializer list ("<<l.size()<<") does not ";
                    ss<<"match selection rank ("<<rank()<<")!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }
                std::copy(l.begin(),l.end(),_offset.begin());
            }

            //------------------------------------------------------------------
            void H5Selection::stride(const std::initializer_list<hsize_t> &l)
            {
                if(l.size() != rank())
                {
                    std::stringstream ss;
                    ss<<"Size of initializer list ("<<l.size()<<") does not ";
                    ss<<"match selection rank ("<<rank()<<")!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                std::copy(l.begin(),l.end(),_stride.begin());
            }


            //-----------------------------------------------------------------
            void H5Selection::count(const std::initializer_list<hsize_t> &l)
            {
                if(l.size() != rank())
                {
                    std::stringstream ss;
                    ss<<"Size of initializer list ("<<l.size()<<") does not ";
                    ss<<"match selection rank ("<<rank()<<")!";
                    throw SizeMissmatchError(EXCEPTION_RECORD,ss.str());
                }

                std::copy(l.begin(),l.end(),_counts.begin());
            }


            //=============specializations of the IO methods===================
            //implementation of the write string method 
            void H5Selection::write(const String &value) const
            {
                if(size()!=1)
                    throw ShapeMissmatchError(EXCEPTION_RECORD,
                            "Selection is not scalar!");

                const char *ptr = value.c_str();

                herr_t err;
                //select the proper memory data type
                H5Datatype mem_type = H5Datatype(H5Dget_type(_dataset->id()));
                H5Dataspace ms;
                
                //set selection to the file datasets original dataset
                //==========>here we would have to lock the dataset object 
                err = H5Sselect_hyperslab(_dataset->space().id(),
                        H5S_SELECT_SET,
                        this->offset().ptr(), //set the offset pointer
                        this->stride().ptr(), //set the stride pointer
                        this->count().ptr(),  //set the count pointer
                        NULL);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error applying selection to dataset!");

                //write data to disk
                err = H5Dwrite(_dataset->id(),
                        mem_type.id(),          //set memory data type
                        ms.id(),           //set selection data space
                        _dataset->space().id(),  //set file data space
                        H5P_DEFAULT,
                        &ptr);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error writing string to dataset via selection!");

                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());
            }

            //------------------------------------------------------------------
            //implementation of the read string method 
            void H5Selection::read(String &value) const
            {
                if(size()!=1)
                    throw ShapeMissmatchError(EXCEPTION_RECORD,
                            "Selection is not scalar!");

                herr_t err;
                //set selection to the file datasets original dataset
                //==========>here we would have to lock the dataset object 
                err = H5Sselect_hyperslab(_dataset->space().id(),
                        H5S_SELECT_SET,
                        this->offset().ptr(), //set the offset pointer
                        this->stride().ptr(), //set the stride pointer
                        this->count().ptr(),  //set the count pointer
                        NULL);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error applying selection to dataset ["+
                            _dataset->name()+"]!");

                const char *ptr = nullptr;
	            hid_t xfer_plist = H5Pcreate(H5P_DATASET_XFER);
                
                //select the proper memory data type
                H5Datatype mem_type = H5Datatype(H5Dget_type(_dataset->id()));
                H5Dataspace ms;

                //write data to disk
                err = H5Dread(_dataset->id(),
                        mem_type.id(),          //set memory data type
                        ms.id(),           //set selection data space
                        _dataset->space().id(),  //set file data space
                        xfer_plist,
                        &ptr);
                if(err<0)
                    throw H5DataSetError(EXCEPTION_RECORD,
                            "Error writing string data to dataset ["+
                            _dataset->name()+"] via selection!");

                //copy content of the pointer to the string object
                try{
                    value = String(ptr);
                }catch(...){
                    value = "";
                }
                
                //remove selection from the dataspace
                H5Sselect_none(_dataset->space().id());

                //reclaim memory from HDF5 library.
                H5Dvlen_reclaim(mem_type.id(),_dataset->space().id(),
                                xfer_plist,&ptr);
            }
           

//end of namespace
}
}
}



