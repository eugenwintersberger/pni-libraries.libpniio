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
// Created on: Apr 24, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//



#include <pni/error.hpp>
#include <pni/tiff/ifd_entry.hpp>
#include <pni/tiff/standard.hpp>

using namespace pni;


namespace pni{
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
                               {{1,ifd_entry_type_id::Byte},
                               {2,ifd_entry_type_id::ASCII},
                               {3,ifd_entry_type_id::Short},
                               {4,ifd_entry_type_id::Long},
                               {5,ifd_entry_type_id::Rational},
                               {6,ifd_entry_type_id::SByte},
                               {7,ifd_entry_type_id::Undefined},
                               {8,ifd_entry_type_id::SShort},
                               {9,ifd_entry_type_id::SLong},
                               {10,ifd_entry_type_id::SRational},
                               {11,ifd_entry_type_id::Float},
                               {12,ifd_entry_type_id::Double}};

    //map object associating IDFEntryTypeIds to PNI TypeIDs
    std::map<ifd_entry_type_id,type_id_t> entry_type_to_type_id = 
                          {{ifd_entry_type_id::Byte,pni::type_id_t::UInt8},
                          {ifd_entry_type_id::ASCII,pni::type_id_t::String},
                          {ifd_entry_type_id::Short,pni::type_id_t::UInt16},
                          {ifd_entry_type_id::Long,pni::type_id_t::UInt32},
                          {ifd_entry_type_id::Rational,pni::type_id_t::Float64},
                          {ifd_entry_type_id::SByte,pni::type_id_t::Int8},
                          {ifd_entry_type_id::Undefined,pni::type_id_t::None},
                          {ifd_entry_type_id::SShort,pni::type_id_t::Int16},
                          {ifd_entry_type_id::SLong,pni::type_id_t::Int32},
                          {ifd_entry_type_id::SRational,pni::type_id_t::Float64},
                          {ifd_entry_type_id::Float,pni::type_id_t::Float32},
                          {ifd_entry_type_id::Double,pni::type_id_t::Float64}};


    //==================constructors and destructor========================
    //implementation of the  default constructor
    ifd_entry::ifd_entry():
        _tag(0),
        _tid(ifd_entry_type_id::Undefined),
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
    ifd_entry::ifd_entry(pni::uint16 tag,ifd_entry_type_id tid,size_t size, 
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
        pni::uint16 tag = 0;
        stream.read(reinterpret_cast<char*>(&tag),2);
        
        pni::uint16 tid = 0;
        stream.read(reinterpret_cast<char*>(&tid),2);

        pni::uint32 count = 0;
        stream.read(reinterpret_cast<char*>(&count),4);

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
    pni::string ifd_entry::name() const
    {
       try{
           return tiff_tag_name_map[_tag];
       }catch(...){
           return string("unknown");
       }
    }

    //-----------------------------------------------------------------------
    pni::type_id_t ifd_entry::type_id() const
    {
        return entry_type_to_type_id[_tid];
    }

    //-----------------------------------------------------------------------
    void ifd_entry::_read_entry_data(std::vector<pni::string> &r,
                                     std::ifstream &stream)
    {
        using namespace pni;
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
