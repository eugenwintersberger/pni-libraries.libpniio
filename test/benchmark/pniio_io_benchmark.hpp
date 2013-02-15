/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Jan 05, 2013
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <pni/core/types.hpp>
#include <pni/core/darray.hpp>
#include "file_io_benchmark.hpp"

#include <pni/io/nx/nx.hpp>

#include "../uniform_distribution.hpp"

using namespace pni::core;
using namespace pni::io::nx::h5;

template<typename T> class pniio_io_benchmark : public file_io_benchmark
{
    private:
        //! array holding the buffer for the frame data
        darray<T> _frame_buffer; 
        nxfield   _field;
        nxfile    _file;
    public:
        //===================constructors and destructor=======================
        //! default constructor
        pniio_io_benchmark():
            file_io_benchmark(),
            _frame_buffer()
        {}

        //---------------------------------------------------------------------
        //! constructor
        pniio_io_benchmark(const string &fname,size_t nx,size_t ny,
                           size_t nframes,bool random_fill):
            file_io_benchmark(fname,nx,ny,nframes)
        {
            //create the frame buffer
            shape_t fshape{nx,ny};
            _frame_buffer = darray<T>(fshape);

            if(random_fill)
            {
                uniform_distribution<T> random_dist;
                for(auto iter = _frame_buffer.begin();iter!=_frame_buffer.end();
                         ++iter)
                    *iter = random_dist();
            }
            else
                std::fill(_frame_buffer.begin(),_frame_buffer.end(),T(0));

        }

        //---------------------------------------------------------------------


        //======================public member functions========================
        //! create data structures
        virtual void create();
        virtual void close();

        //---------------------------------------------------------------------
        //! run the benchmark
        virtual void run() ;

};

//-----------------------------------------------------------------------------
template<typename T> void pniio_io_benchmark<T>::create()
{
    //create the file
    _file = nxfile::create_file(filename(),true,0);
    shape_t s{0,nx(),ny()};
    shape_t cs{1,nx(),ny()};
    _field = _file.template create_field<T>("data",s,cs);
}

//-----------------------------------------------------------------------------
template<typename T> void pniio_io_benchmark<T>::close()
{
    _field.close();
    _file.close();
}


//-----------------------------------------------------------------------------
template<typename T> void pniio_io_benchmark<T>::run() 
{
    for(size_t n = 0; n<nframes();n++)
    {
        _field.grow(0);
        _field(n,slice(0,nx()),slice(0,ny())).write(_frame_buffer);
        _file.flush();
    }
}
