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
#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <boost/current_function.hpp>

#include <pni/types.hpp>
#include <pni/error.hpp>
#include <pni/tiff/rational.hpp>
#include <pni/tiff/ifd_entry_reader.hpp>

namespace pni{
namespace io{
namespace tiff{
   
    //possible data values of an IFD entry according to the TIFF standard
    enum class ifd_entry_type_id 
    { 
        BYTE,  //!< 8Bit unsigned int
        ASCII, //!< string of 8Bit values with binary terminated with a binary 0
        SHORT, //!< 16Bit unsigned integer
        LONG,  //!< 32Bit unsigned integer
        RATIONAL,  //!< two LONG values
        SBYTE,     //!< 8Bit signed integer
        UNDEFINED, //! as said: undefined 
        SSHORT,    //!< 16Bit signed integer
        SLONG,     //!< 32Bit signed integer
        SRATIONAL, //!< like RATIONAL but signed
        FLOAT,     //!< 4Byte IEEE float
        DOUBLE     //!< 8Byte IEEE float
    };

#ifdef ENUMBUG
    bool operator<(ifd_entry_type_id a,ifd_entry_type_id b);
    bool operator>(ifd_entry_type_id a,ifd_entry_type_id b);
    bool operator<=(ifd_entry_type_id a,ifd_entry_type_id b);
    bool operator>=(ifd_entry_type_id a,ifd_entry_type_id b);
#endif

    //!
    //! \ingroup image_io_tiff
    //! \brief class for IFD entries
    //!
    //! This class can manage the content of a single IFDEntry. 
    //!
    class ifd_entry
    {
        private:
            pni::uint16 _tag;            //!< ID of the entry
            ifd_entry_type_id _tid;   //!< type id of the entry
            size_t _size;          //!< number of elements of the entry
            std::streampos _data;  //!< marks data position

            //===============private methods===================================
            //!
            //! \brief read entry data from stream
            //!
            //! Reads the entrys data from an input stream. This method 
            //! assumes that the input stream points to the first element of 
            //! the entry. The position of the stream is altered. It is the 
            //! responsibility of the calling method to take care about the 
            //! position of the stream.
            //!
            //! \param r vector where to store the data
            //! \param stream input stream from which to read
            //! 
            template<typename T> 
            void _read_entry_data(std::vector<T> &r,std::ifstream &stream);

            //----------------------------------------------------------------
            //!
            //! \brief read string entry from stream
            //!
            //! Reads a string entry from the stream. The stream position 
            //! will be altered by this method. Thus the calling method must 
            //! take care about this.
            //!
            //! \param r vector where to store data
            //! \param stream input stream from which to read
            //!
            void _read_entry_data(std::vector<pni::string> &r,
                                  std::ifstream &stream);
            
        public:
            //=============constructors and destructor=========================
            //! default constructor
            ifd_entry();

            //-----------------------------------------------------------------
            //! copy constructor
            ifd_entry(const ifd_entry &e);

            //-----------------------------------------------------------------
            //! move constructor
            ifd_entry(ifd_entry &&e);

            //-----------------------------------------------------------------
            //!
            //! \brief standard constructor
            //! 
            //! Standard constructor to create a IFDEntry.
            //!
            //! \param tag TIFF tag of the entry
            //! \param tid type ID of the entry
            //! \param size number of elements stored in this entry
            //! \param data starting position of data in the stream
            //!
            ifd_entry(pni::uint16 tag,ifd_entry_type_id tid,size_t size,
                      std::streampos data);

            //-----------------------------------------------------------------
            //! destructor
            ~ifd_entry();

            //=====================assignment operators========================
            //! copy assignment operator
            ifd_entry &operator=(const ifd_entry &e);

            //! move assignment operator
            ifd_entry &operator=(ifd_entry &&e);

            //===============static methods====================================
            //!
            //! \brief create entry from stream
            //!
            //! A static factory method to create an instance of IFDEntry 
            //! from a stream.
            //!
            //! \param stream input stream from which to read data
            //! \return instance of IFDEntry
            //!
            static ifd_entry create_from_stream(std::ifstream &stream);

            //==================class methods==================================
            //!
            //! \brief number of elements
            //!
            //! Returns the number of elements that make up the entry.
            //! \return number of elements
            //!
            size_t size() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get name
            //!
            //! Returns the name of the entry as a string.
            //! \return name as string
            //!
            pni::string name() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get type ID
            //!
            //! Returns the TypeID of the entries type. 
            //! \return type ID of entry
            //!
            pni::type_id_t type_id() const;

            //-----------------------------------------------------------------
            //!
            //! \brief get entry value
            //!
            //! Template returns the value of the entry and returs it as a 
            //! vector of type T. Entries are in general considered as arrays
            //! (vectors) in TIFF. Thus the std::vector type is used to 
            //! represent each entry.
            //!
            //! The method makes no assumption about the position of the stream
            //! pointer neither does it alter its state. 
            //! \param stream input stream from which data will be read
            //! \return entry as vector
            //!
            template<typename T> std::vector<T> value(std::ifstream &stream);

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,const ifd_entry &e);

    };


    //==============implementation of public template methods===================
    template<typename T> std::vector<T> ifd_entry::value(std::ifstream &stream)
    {
        using namespace pni;

        //create a vector of appropriate length
        std::vector<T> result(this->size());
        //save the original stream position
        std::streampos orig_stream_pos = stream.tellg();

        //set the stream to the begining of the data section
        stream.seekg(this->_data,std::ios::beg);

        //here comes the tricky part. Though the user defines the type T he
        //wants to have the IFD entry not all entry types can be converted to T
        //without loss of information. Thus wee need a selection function that
        //picks for each T all acceptable types and throws an exception if the
        //entry is of an incompatible type. 
        //
        //This operation is carried out by the next function which cann choose
        //the proper version by argument type deduction.
        try{
            this->_read_entry_data(result,stream);
        }
        catch(type_error &e)
        {
            e.append(EXCEPTION_RECORD);
            //reset the stream to its original position
            stream.seekg(orig_stream_pos,std::ios::beg);
            throw e;
        }
            
       
        //reset stream to its original position
        stream.seekg(orig_stream_pos,std::ios::beg);

        return result;
    }

    //--------------------------------------------------------------------------
    template<typename T> void ifd_entry:: 
        _read_entry_data(std::vector<T> &r,std::ifstream &stream)
    {
        using namespace pni;

        if(this->_tid == ifd_entry_type_id::BYTE) 
            ifd_entry_reader<T,uint8>::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::SHORT)
            ifd_entry_reader<T,uint16>::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::LONG)
            ifd_entry_reader<T,uint32>::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::RATIONAL)
            ifd_entry_reader<T,rational<uint16> >::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::SBYTE)
            ifd_entry_reader<T,int8>::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::SSHORT)
            ifd_entry_reader<T,int16>::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::SLONG)
            ifd_entry_reader<T,int32>::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::SRATIONAL)
            ifd_entry_reader<T,rational<int32> >::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::FLOAT)
            ifd_entry_reader<T,float32>::read(r,stream);
        else if(this->_tid == ifd_entry_type_id::DOUBLE)
            ifd_entry_reader<T,float64>::read(r,stream);
        else
            //reset stream position
            throw type_error(EXCEPTION_RECORD,"IFD entry ["+this->name()+
                    "] contains unknown data!");
    }


//end of namespace
}
}
}

