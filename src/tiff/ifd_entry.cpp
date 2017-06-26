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
// Created on: Apr 24, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//



#include <pni/core/error.hpp>
#include <pni/io/tiff/ifd_entry.hpp>
#include <pni/io/tiff/standard.hpp>

using namespace pni::core;


namespace pni{
namespace io{
namespace tiff{
    //================manage enum types if the compiler does not do it=========
#ifdef ENUMBUG
    bool operator<(ifd_entry_type_id a,ifd_entry_type_id b)
    {
        return int(a)<int(b);
    }

    //-------------------------------------------------------------------------
    bool operator>(ifd_entry_type_id a,ifd_entry_type_id b)
    {
        return int(a)>int(b);
    }

    //-------------------------------------------------------------------------
    bool operator<=(ifd_entry_type_id a,ifd_entry_type_id b)
    {
        return int(a)<=int(b);
    }

    //-------------------------------------------------------------------------
    bool operator>=(ifd_entry_type_id a,ifd_entry_type_id b)
    {
        return int(a)>=int(b);
    }
#endif

    //map object associating TIFF type tags to IDFEntryTypeId enums
    std::map<uint16,ifd_entry_type_id> type_tag_to_entry_type_id = 
                               {{1,ifd_entry_type_id::BYTE},
                               {2,ifd_entry_type_id::ASCII},
                               {3,ifd_entry_type_id::SHORT},
                               {4,ifd_entry_type_id::LONG},
                               {5,ifd_entry_type_id::RATIONAL},
                               {6,ifd_entry_type_id::SBYTE},
                               {7,ifd_entry_type_id::UNDEFINED},
                               {8,ifd_entry_type_id::SSHORT},
                               {9,ifd_entry_type_id::SLONG},
                               {10,ifd_entry_type_id::SRATIONAL},
                               {11,ifd_entry_type_id::FLOAT},
                               {12,ifd_entry_type_id::DOUBLE}};

    //map object associating IDFEntryTypeIds to PNI TypeIDs
    std::map<ifd_entry_type_id,type_id_t> entry_type_to_type_id = 
                          {{ifd_entry_type_id::BYTE,pni::core::type_id_t::UINT8},
                          {ifd_entry_type_id::ASCII,pni::core::type_id_t::STRING},
                          {ifd_entry_type_id::SHORT,pni::core::type_id_t::UINT16},
                          {ifd_entry_type_id::LONG,pni::core::type_id_t::UINT32},
                          {ifd_entry_type_id::RATIONAL,pni::core::type_id_t::FLOAT64},
                          {ifd_entry_type_id::SBYTE,pni::core::type_id_t::INT8},
                          {ifd_entry_type_id::UNDEFINED,pni::core::type_id_t::NONE},
                          {ifd_entry_type_id::SSHORT,pni::core::type_id_t::INT16},
                          {ifd_entry_type_id::SLONG,pni::core::type_id_t::INT32},
                          {ifd_entry_type_id::SRATIONAL,pni::core::type_id_t::FLOAT64},
                          {ifd_entry_type_id::FLOAT,pni::core::type_id_t::FLOAT32},
                          {ifd_entry_type_id::DOUBLE,pni::core::type_id_t::FLOAT64}};


    //==================constructors and destructor========================
    //implementation of the  default constructor
    ifd_entry::ifd_entry():
        _tag(0),
        _tid(ifd_entry_type_id::UNDEFINED),
        _size(0),
        _data(0)
    {}

    //---------------------------------------------------------------------
    //implementation of the copy constructor
    ifd_entry::ifd_entry(const ifd_entry &e):
        _tag(e._tag),
        _tid(e._tid),
        _size(e._size),
        _data(e._data)
    {}

    //---------------------------------------------------------------------
    //implementation of the  move constructor
    ifd_entry::ifd_entry(ifd_entry &&e):
        _tag(std::move(e._tag)),
        _tid(std::move(e._tid)),
        _size(std::move(e._size)),
        _data(std::move(e._data))
    {}

    //---------------------------------------------------------------------
    //implementation of the standard constructor
    ifd_entry::ifd_entry(pni::core::uint16 tag,ifd_entry_type_id tid,size_t size, 
                      std::streampos data):
        _tag(tag),
        _tid(tid),
        _size(size),
        _data(data)
    { }

    //---------------------------------------------------------------------
    //implementation of the destructor
    ifd_entry::~ifd_entry()
    {}

    //=====================assignment operators============================
    //implementation of the copy assignment operator
    ifd_entry &ifd_entry::operator=(const ifd_entry &e)
    {
        if(this == &e) return *this;
        
        _tag = e._tag;
        _tid = e._tid;
        _size = e._size;
        _data = e._data;
        return *this;
    }

    //---------------------------------------------------------------------
    //implementation of the move assignment operator
    ifd_entry &ifd_entry::operator=(ifd_entry &&e)
    {
        if(this == &e) return *this;
        _tag = std::move(e._tag);
        _tid = std::move(e._tid);
        _size = std::move(e._size);
        _data = std::move(e._data);
        return *this;
    }

    //===========implementation of static methods==========================
    ifd_entry ifd_entry::create_from_stream(std::ifstream &stream)
    {
        pni::core::uint16 tag = 0;
        stream.read((char *)(&tag),2);
        
        pni::core::uint16 tid = 0;
        stream.read((char *)(&tid),2);

        pni::core::uint32 count = 0;
        stream.read((char *)(&count),4);

        ifd_entry e(tag,type_tag_to_entry_type_id[tid],count,stream.tellg());
        //add additional for byte 
        stream.seekg(4,std::ios::cur);
        return e;
    
    }

    //=======================class methods=================================
    //implementation of nelements
    size_t ifd_entry::size() const
    {
        return _size;
    }

    //----------------------------------------------------------------------
    pni::core::string ifd_entry::name() const
    {
       try{
           return tiff_tag_name_map[_tag];
       }catch(...){
           return string("unknown");
       }
    }

    //-----------------------------------------------------------------------
    pni::core::type_id_t ifd_entry::type_id() const
    {
        return entry_type_to_type_id[_tid];
    }

    //-----------------------------------------------------------------------
    void ifd_entry::_read_entry_data(std::vector<pni::core::string> &r,
                                     std::ifstream &stream)
    {
        using namespace pni::core;
        //now we have to walk through all types available in TIFF - not very
        //nice but we have no other choice at runtime
        if(this->_tid == ifd_entry_type_id::ASCII)
            ifd_entry_reader<string,string>::read(r,stream);
        else
            throw type_error(EXCEPTION_RECORD,
            "IFD entry is of unknown or incompatible type!");
       
    }

    //=================implementation of friend methods and operators========
    std::ostream &operator<<(std::ostream &o,const ifd_entry &e)
    {
        o<<"IFD entry: "<<e.name()<<" (tag="<< e._tag<<") with "<<e.size()<<" of type ";
        o<<e.type_id();
        return o;
    }

//end of namespace
}
}
}
