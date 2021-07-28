//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Apr 23, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//


#include <pni/error.hpp>
#include <pni/data_reader.hpp>


namespace pni{

    using namespace pni;
    //================implementation of private methods=========================
    //default implementation
    std::unique_ptr<std::ifstream> data_reader::
        _open_stream(const pni::string &fname) const
    {        
        std::unique_ptr<std::ifstream> stream(new std::ifstream()); 
        if(!stream)
            throw memory_allocation_error(EXCEPTION_RECORD,
            "Cannot allocate memory for stream object!");

        if(_is_binary)
            stream->open(fname.c_str(),std::ifstream::binary);
        else
            stream->open(fname.c_str());

        return stream;
    }

    //====================Implementation of constructors=======================
    //implementation of the default constructor
    data_reader::data_reader():
        _fname(),
        _is_binary(true),
        _istream(nullptr)
    {}

    //-------------------------------------------------------------------------
    //implementation of the standard constructor
    data_reader::data_reader(const pni::string &fname,bool binary):
        _fname(fname),
        _is_binary(binary),
        _istream(_open_stream(fname))
    { 
        
        if(_istream->fail())
            throw file_error(EXCEPTION_RECORD,
                    "Error opening file ["+fname+"]!");
    }

    //-------------------------------------------------------------------------
    //implementation of the move constructor
    data_reader::data_reader(data_reader &&r):
        _fname(std::move(r._fname)),
        _is_binary(std::move(r._is_binary)),
        _istream(std::move(r._istream))
    {}

    //-------------------------------------------------------------------------
    //implementation of the destructor
    data_reader::~data_reader() 
    {
        //close the file in case the object is getting destroied.
        if(_istream)
            if(_istream->good() && _istream->is_open()) _istream->close();
    }

    //=============implementation of assignment operators======================
    data_reader &data_reader::operator=(data_reader &&r)
    {
        if(this == &r) return *this;

        _fname = std::move(r._fname);
        _istream = std::move(r._istream);

        return *this;
    }

    //============implementation of utilty methods=============================
    string data_reader::filename() const
    {
        return _fname;
    }

    //-------------------------------------------------------------------------
    void data_reader::filename(const string &fname)
    {
        _fname = fname;
    }
    
    //-------------------------------------------------------------------------
    void data_reader::close()
    {
        if(_istream)
            if(_istream->is_open()) _istream->close();
    }

    //-------------------------------------------------------------------------
    void data_reader::open()
    {
        close(); //close the file if it is already open
        _istream = _open_stream(filename());
    }

//end of namespace
}
