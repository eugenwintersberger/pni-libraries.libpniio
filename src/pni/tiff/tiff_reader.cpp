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
// Created on: Jun 15, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//

#include <numeric>
#include <sstream>

#include <pni/error.hpp>
#include <pni/types.hpp>
#include <pni/tiff/tiff_reader.hpp>

using namespace pni;

namespace pni{

    //============implementation of private methods============================
    //implementation of _set_endianess
    bool tiff_reader::_is_little_endian(std::ifstream &stream)
    {
        std::streampos orig_pos = stream.tellg();

        //set the stream to the very beginning of the file
        stream.seekg(0,std::ios::beg);
        //TIFF file and how it looks with endieness
        char buffer[2];
        stream.read(buffer,2);
        //reset the stream to its original position
        stream.seekg(orig_pos,std::ios::beg);

        if((buffer[0]=='I')&&(buffer[1]=='I')) return true;
        if((buffer[0]=='M')&&(buffer[1]=='M')) return false;

        return false; //just to avoid compiler warnings
    }

    //-------------------------------------------------------------------------
    //implementation of check tiff
    void tiff_reader::_check_if_tiff(std::ifstream &stream)
    {
        using namespace pni;
        std::streampos orig_pos = stream.tellg();

        //set stream to the correct position in the TIFF file
        stream.seekg(2,std::ios::beg);

        //read the magic number
        uint16 magic;
        stream.read(reinterpret_cast<char*>(&magic),2);
            
        //reset stream position
        stream.seekg(orig_pos,std::ios::beg);
        if(magic!=42)
            throw file_error(EXCEPTION_RECORD,"Not a TIFF file!");
        
    }
    
    //--------------------------------------------------------------------------
    //implementation of read IFD offset
    pni::uint32 tiff_reader::_read_ifd_offset(std::ifstream &stream)
    {
        //no we need to read the IFD entries read the first IFD offset
        pni::uint32 offset = 0;
        stream.read(reinterpret_cast<char*>(&offset),4);
        return offset;
    }
    
    //-------------------------------------------------------------------------
    size_t tiff_reader::_read_ifd_size(std::ifstream &stream)
    {
        size_t size = 0;
        stream.read(reinterpret_cast<char*>(&size),2);
        return size;
    }

    //-------------------------------------------------------------------------
    //implementation of _read_image_info
    void tiff_reader::_read_ifds()
    {
        using namespace pni;
        //obtain stream
        std::ifstream &stream = _get_stream();

        //check endianess of the data - we need to do this before all other
        //things in order to interpret binary data correctly
        _little_endian = tiff_reader::_is_little_endian(stream);
        
        //now we check if the file is really a TIFF file
        tiff_reader::_check_if_tiff(stream);


        //set the stream to the position of the first IFD offse
        stream.seekg(4,std::ios::beg);
        //no we need to read the IFD entries read the first IFD offset
        uint32 ifd_offset = _read_ifd_offset(stream);
        if(ifd_offset == 0)
            throw file_error(EXCEPTION_RECORD,"File "+filename()+" does not "
                    "contain an IDF entry!");

        //read IFDs from the file
        do{
            //move the stream to the staring position of the IDF
            stream.seekg(ifd_offset, std::ios::beg);

            //create the IDF from the stream - here we assume that the IFD
            //constructor returns the stream at the position where the offset of
            //the next IFD is stored.
            tiff::ifd ifd(_read_ifd_size(stream));

            for(tiff::ifd_entry &entry: ifd) 
            {
                entry = std::move(tiff::ifd_entry::create_from_stream(stream));
            }
            
            //store the IFD
            _ifds.push_back(ifd);

            //read next IFD offset
            ifd_offset = _read_ifd_offset(stream);
        }while(ifd_offset);
    }

    //-------------------------------------------------------------------------
    std::vector<size_t> tiff_reader::
        _get_bits_per_sample(std::ifstream &stream,const tiff::ifd &ifd) 
    {
        std::vector<size_t> bits_per_sample(1);
        try
        {
            bits_per_sample =
                ifd["BitsPerSample"].value<size_t>(stream);
        }catch(...)
        {
            //ok - a bilevel image has only one bit per sample and only one
            //sample per pixel 
            bits_per_sample[0] = 1; 
        }
        return bits_per_sample;
    }

    //-------------------------------------------------------------------------
    std::vector<size_t> tiff_reader::
        _get_sample_format(std::ifstream &stream,const tiff::ifd &ifd)
    {
        std::vector<size_t> sample_format(1);
        try
        {
            sample_format = ifd["SampleFormat"].value<size_t>(stream);
        }
        catch(...)
        {
            sample_format[0] = 1;
        }
        return sample_format;
    }

    //---------------------------------------------------------------------
    type_id_t tiff_reader::_get_type_id(size_t bps,size_t sf) 
    {
        using namespace pni;
        std::stringstream error_stream;
        switch(sf)
        {
            case 1:
                //unsigned integer data
                switch(bps)
                {
                    case 8: return type_id_t::UInt8;
                    case 16: return type_id_t::UInt16;
                    case 32: return type_id_t::UInt32;
                    case 64: return type_id_t::UInt64;
                    default:
                            error_stream<<"Invalid unsigned integer type - ";
                            error_stream<<"Bits per sample = "<<bps<<" ";
                            error_stream<<"Sign flag = "<<sf;
                         throw type_error(EXCEPTION_RECORD,error_stream.str());
                }
                break;
            case 2:
                //signed integer data
                switch(bps)
                {
                    case 8: return type_id_t::Int8;
                    case 16: return type_id_t::Int16;
                    case 32: return type_id_t::Int32;
                    case 64: return type_id_t::Int64;
                    default:
                             error_stream<<"Invalid signed integer type - ";
                             error_stream<<"Bits per sample = "<<bps<<" ";
                             error_stream<<"Sign flag = "<<sf;
                        throw type_error(EXCEPTION_RECORD,error_stream.str());
                }
                break;
            case 3: 
                //IEEE floating point data
                switch(bps)
                {
                    case 32: return type_id_t::Float32;
                    case 64: return type_id_t::Float64;
                    default:
                             error_stream<<"Invalid floating point type - ";
                             error_stream<<"Bits per sample = "<<bps<<" ";
                             error_stream<<"Sign flag = "<<sf;
                        throw type_error(EXCEPTION_RECORD,error_stream.str());
                }
                break;

            default:
                //throw an exception here
                throw type_error(EXCEPTION_RECORD,"Cannot derive type id!");

        }
	return type_id_t::UInt8;
    }

    //=============implementation of constructors and destructor===========
    //implementation of the default constructor
    tiff_reader::tiff_reader():image_reader()
    { 
        //set the stream format to binary
        data_reader::_set_binary();
    }

    //---------------------------------------------------------------------
    //implementation of the move constructor
    tiff_reader::tiff_reader(tiff_reader &&r):
        image_reader(std::move(r)),
        _little_endian(std::move(r._little_endian)),
        _ifds(std::move(r._ifds))
    {}

    //---------------------------------------------------------------------
    //implementation of the standard constructor
    tiff_reader::tiff_reader(const string &fname):image_reader(fname,true)
    { 
        _read_ifds(); 
    }

    //---------------------------------------------------------------------
    //imlementation of the destructor
    tiff_reader::~tiff_reader() 
    { }

    //==================implementation of assignment operators=============
    tiff_reader &tiff_reader::operator=(tiff_reader &&r)
    {
        if(this == &r) return *this;
        image_reader::operator=(std::move(r));
        _ifds = std::move(r._ifds);

        return *this;
    }

    //=====================implementation of member methods====================

    size_t tiff_reader::nimages() const
    {
        return _ifds.size();
    }

    //-------------------------------------------------------------------------
    image_info tiff_reader::info(size_t i) const 
    {
        //get the right ifd
        const tiff::ifd &ifd = _ifds[i];

        //the number of pixels in x-direction is associated with the image width
        //in TIFF
        size_t nx = ifd["ImageLength"].value<size_t>(_get_stream())[0];
        //the number of pixels in y-direction is associated with the image
        //length in TIFF
        size_t ny = ifd["ImageWidth"].value<size_t>(_get_stream())[0];

        
        //need to obtain the number of bits per sample. From this field we can
        //also obtain the number of channels. If the field BitsPerSample does
        //not exists the image is Bilevel image which is very unlikely to be
        //used for detectors :)
        std::vector<size_t> bits_per_sample(_get_bits_per_sample(_get_stream(),ifd));

        //the other information required is the sample format for each channel
        std::vector<size_t> sample_format(_get_sample_format(_get_stream(),ifd));

        //the information gathered so far should be enough to assemble image
        //information
        image_info info(nx,ny);
        //now we need to add the channels
        for(size_t i=0;i<bits_per_sample.size();i++)
        {
            image_channel_info channel(_get_type_id(bits_per_sample[i],
                                                  sample_format[i]),
                                     bits_per_sample[i]);
            info.append_channel(channel);
        }

        //assemble the ImageInfo object form the IFD
        return info;

    }

    //-------------------------------------------------------------------------
    //implementation of open
    void tiff_reader::open()
    {
        data_reader::open();
        _read_ifds();
    }

    //-------------------------------------------------------------------------
    //implementation of close
    void tiff_reader::close()
    {
        data_reader::close();
        _ifds.clear();
    }

    //=====================implementation of friend functions and operators====
    std::ostream &operator<<(std::ostream &o,const tiff_reader &r)
    {
        o<<"TIFFReader for file: "<<r.filename()<<std::endl;
        o<<"File contains: "<<r.nimages()<<" images"<<std::endl; 

        for(auto ifd: r._ifds) o<<ifd;
        
        return o;
    }


//end of namespace
}
