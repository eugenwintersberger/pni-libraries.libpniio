/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Created on: Dec 17, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include "file_io_benchmark.hpp"

//-----------------------------------------------------------------------------
file_io_benchmark::file_io_benchmark():
    _nx(0),
    _ny(0),
    _nframes(0),
    _filename("pninxbm.h5")
{}

//-----------------------------------------------------------------------------
file_io_benchmark::file_io_benchmark(const string &fname,size_t nx,size_t ny,size_t nframes):
    _nx(nx),
    _ny(ny),
    _nframes(nframes),
    _filename(fname)
{}

//-----------------------------------------------------------------------------
