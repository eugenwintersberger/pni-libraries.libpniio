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

#include <cstdarg>
#include "H5Selection.hpp"
#include "H5Exceptions.hpp"


namespace pni{
    namespace nx{
        namespace h5{
            //==============Implementation of constructors and destructors======
            //implementation of the default constructor
            H5Selection::H5Selection(){
            
            }

            //------------------------------------------------------------------
            //implementation of the copy constructor
            H5Selection::H5Selection(const H5Selection &o){
                _sspace = o.space();
                _offset = o._offset;
                _stride = o._stride;
                _counts = o._counts;
            }

            //------------------------------------------------------------------
            //implementation of the move constructor
            H5Selection::H5Selection(H5Selection &&o){
                _sspace = std::move(o._sspace);
                _offset = std::move(o._offset);
                _stride = std::move(o._stride);
                _counts = std::move(o._counts);
            }

            //------------------------------------------------------------------
            //implementation of the standard constructor
            H5Selection::H5Selection(const size_t &r){
                _offset.allocate(r);
                _stride.allocate(r);
                _counts.allocate(r);

                //set initial values where it makes sense
                _offset = 0;
                _stride = 1;
                _counts = 0;

            }

            //------------------------------------------------------------------
            //implementation of the destructor
            H5Selection::~H5Selection(){
            }

            //==============Implementation of assignment operators==============
            //implementation of the copy assignment operator
            H5Selection &H5Selection::operator=(const H5Selection &o){
                EXCEPTION_SETUP("H5Selection &H5Selection::operator="
                        "(const H5Selection &o)");

                if(this != &o){
                    _sspace = o._sspace;
                    _stride = o._stride;
                    _offset = o._offset;
                    _counts  = o._counts;
                }

                return *this;
            }

            //------------------------------------------------------------------
            //implementation of the move assignment operator
            H5Selection &H5Selection::operator=(H5Selection &&o){
                EXCEPTION_SETUP("H5Selection &H5Selection::operator="
                        "(H5Selection &&o)");

                if(this != &o){
                    _sspace = std::move(o._sspace);
                    _stride = std::move(o._stride);
                    _offset = std::move(o._offset);
                    _counts  = std::move(o._counts);
                }
                return *this;
            }

            //========implementation of inquery methods=========================
            //get size
            size_t H5Selection::size() const{
                return _sspace.size();
            }

            //------------------------------------------------------------------
            //get shape
            Shape H5Selection::shape() const {
                return _sspace.shape();
            }

            //------------------------------------------------------------------
            //return reference to the dataspace
            const H5Dataspace &H5Selection::space() const{
                return _sspace;
            }
            
            //=================implementation of modifier methods===============
            //access single offset values
            size_t &H5Selection::offset(size_t i){
                return _offset[i];
            }

            //------------------------------------------------------------------
            //access single offset value
            size_t H5Selection::offset(size_t i) const {
                return _offset[i];
            }

            //------------------------------------------------------------------
            //set all offset values in a single call
            void H5Selection::offset(size_t i,...) const{
                va_list alist;

                va_start(alist,i);
                _offset[0] = i;

                //loop over all other offset values



                va_end(alist);
            }

            //------------------------------------------------------------------
            size_t &H5Selection::stride(size_t i){
                return _stride[i];
            }

            //------------------------------------------------------------------
            size_t H5Selection::stride(size_t i) const{
                return _stride[i];
            }

            //------------------------------------------------------------------
            void H5Selection::stride(size_t i,...) const{

            }

            //------------------------------------------------------------------
            size_t &H5Selection::count(size_t i){
                return _counts[i];
            }

            //------------------------------------------------------------------
            size_t H5Selection::count(size_t i) const{
                return _counts[i];
            }

            //------------------------------------------------------------------
            void H5Selection::count(size_t i,...) const{

            }


        }
    }
}



