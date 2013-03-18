/*
 * Implementation of class TIFFIFD
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 * Implementation of class IFD.
 *
 * Created on: Jun 16, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "ifd.hpp"
#include "ifd_entry.hpp"

namespace pni{
namespace io{
namespace tiff{

    //================implementation of constructors and destructor============ 
    //implementation of the default constructor
    ifd::ifd():
        _entries(0)
    { }

    //-------------------------------------------------------------------------
    //implementation of the copy constructor
    ifd::ifd(const ifd &ifd):
        _entries(ifd._entries)
    { }

    //-------------------------------------------------------------------------
    //implementation fo the move constructor
    ifd::ifd(ifd &&ifd):
        _entries(std::move(ifd._entries))
    {}

    //-------------------------------------------------------------------------
    //implementation of the standard constructor
    ifd::ifd(size_t size):
        _entries(size)
    { }

    //------------------------------------------------------------------------------
    //implementation of the destructor
    ifd::~ifd() 
    {
        _entries.clear();
    }

    //==============implementation of assignment operators=====================
    //implementation of copy assignment operator
    ifd &ifd::operator=(const ifd &o)
    {
        if(this != &o)
            _entries = o._entries;

        return *this;
    }

    //-------------------------------------------------------------------------
    //implementation of the move assignment operator
    ifd &ifd::operator=(ifd &&o)
    {
        if(this != &o) _entries = std::move(o._entries);
        return *this;
    }

    //===============implementation of public member methods===================
    //implementation of the index access operator 
    ifd_entry ifd::operator[](const size_t i) const
    {
        return _entries[i];
    }

    //------------------------------------------------------------------------------
    ifd_entry ifd::operator[](const string &n) const{
#ifdef NOFOREACH
        for(auto iter=(*this).begin();iter!=(*this).end();iter++)
        {
            auto entry = *iter;
#else
        for(auto entry: *this)
        {
#endif
            if(entry.name() == n) return entry;
        }

        throw key_error(EXCEPTION_RECORD,"IFD entry key ["+n+"] not found in IFD!");
    }

    //==================implementation of friend operators=====================
    std::ostream &operator<<(std::ostream &o,const ifd &image_dir)
    {
        o<<"IFD content ("<<image_dir.size()<<" entries):"<<std::endl;
#ifdef NOFOREACH
        for(auto iter=image_dir.begin();iter!=image_dir.end();iter++)
        {
            auto entry = *iter;
#else
        for(auto entry: image_dir)
        {
#endif
            o<<entry<<std::endl;
        }
        return o;
    }

//------------------------------------------------------------------------------
    /*
std::ostream &operator<<(std::ostream &o,const TIFFIFD &idf){
	o<<"IDF at offset "<<idf._idf_offset<<" with "<<idf._number_of_idf_entries<<" entries"<<std::endl;
	o<<idf._entry_list.size()<<std::endl;
	IFDAbstractEntry::sptr e;
	IFDAbstractEntry::const_iterator iter;

	for(iter = idf._entry_list.begin();iter!=idf._entry_list.end();iter++){
		e = *iter;

		switch(e->getEntryTypeCode()){
		case IDFE_BYTE:
			o<<*std::dynamic_pointer_cast<ByteEntry>(e)<<std::endl; break;
		case IDFE_ASCII:
			o<<*std::dynamic_pointer_cast<ASCIIEntry>(e)<<std::endl; break;
		case IDFE_SHORT:
			o<<*std::dynamic_pointer_cast<ShortEntry>(e)<<std::endl; break;
		case IDFE_LONG:
			o<<*std::dynamic_pointer_cast<LongEntry>(e)<<std::endl; break;
		case IDFE_RATIONAL:
			o<<*std::dynamic_pointer_cast<RationalEntry>(e)<<std::endl; break;
		case IDFE_UNDEFINED:
			o<<*std::dynamic_pointer_cast<ASCIIEntry>(e)<<std::endl; break;
		case IDFE_SBYTE:
			o<<*std::dynamic_pointer_cast<SByteEntry>(e)<<std::endl; break;
		case IDFE_SSHORT:
			o<<*std::dynamic_pointer_cast<SShortEntry>(e)<<std::endl; break;
		case IDFE_SLONG:
			o<<*std::dynamic_pointer_cast<SLongEntry>(e)<<std::endl; break;
		case IDFE_SRATIONAL:
			o<<*std::dynamic_pointer_cast<SRationalEntry>(e)<<std::endl; break;
		case IDFE_FLOAT:
			o<<*std::dynamic_pointer_cast<FloatEntry>(e)<<std::endl; break;
		case IDFE_DOUBLE:
			o<<*std::dynamic_pointer_cast<DoubleEntry>(e)<<std::endl; break;
		default:
			o<<*e<<std::endl;

		};
	}

	return o;
}*/

//------------------------------------------------------------------------------
/*
std::ifstream &operator>>(std::ifstream &in,TIFFIFD &idf){
	UInt64 i;
	UInt16 tag,ttype;
	UInt32 cnt;
	IFDAbstractEntry::sptr e;
	String ename;

	idf._idf_offset = in.tellg();
	//first we have to read the number of entries in the IDF
	in.read((char *)(&idf._number_of_idf_entries),2);

	//loop over all IDF entries
	for(i=0;i<idf._number_of_idf_entries;i++){
		//read some basic information required to decide which reader to use
		in.read((char*)(&tag),2);
		in.read((char*)(&ttype),2);
		in.read((char*)(&cnt),4);
		//in.read((char*)(&vo),4);
		ename = TIFFTagNameMap[tag];

		//now we have to do something with the data

		//switch for the proper data type
		switch(ttype){
		case ENTRY_TYPE_BYTE:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(ByteEntry::sptr(new ByteEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<ByteEntry>(e);
			break;
		case ENTRY_TYPE_ASCII:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(
					ASCIIEntry::sptr(new ASCIIEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<ASCIIEntry>(e);
			//actually no Idea how to handle this - most probably as string
			break;
		case ENTRY_TYPE_SHORT:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(ShortEntry::sptr(new ShortEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<ShortEntry>(e);
			break;
		case ENTRY_TYPE_LONG:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(LongEntry::sptr(new LongEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<LongEntry>(e);
			break;
		case ENTRY_TYPE_RATIONAL:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(RationalEntry::sptr(new RationalEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<RationalEntry>(e);
			//here one could define a kind of Pair type
			break;
		case ENTRY_TYPE_SBYTE:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(SByteEntry::sptr(new SByteEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<SByteEntry>(e);
			break;
		case ENTRY_TYPE_UNDEFINED:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(ASCIIEntry::sptr(new ASCIIEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<ASCIIEntry>(e);
			//need something like void - differs in interpretation
			break;
		case ENTRY_TYPE_SSHORT:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(SShortEntry::sptr(new SShortEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<SShortEntry>(e);
			break;
		case ENTRY_TYPE_SLONG:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(SLongEntry::sptr(new SLongEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<SLongEntry>(e);
			break;
		case ENTRY_TYPE_SRATIONAL:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(SRationalEntry::sptr(new SRationalEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<SRationalEntry>(e);
			//like above - something like a Pair type can do the job
			break;
		case ENTRY_TYPE_FLOAT:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(FloatEntry::sptr(new FloatEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<FloatEntry>(e);
			break;
		case ENTRY_TYPE_DOUBLE:
			e = std::dynamic_pointer_cast<IFDAbstractEntry>(DoubleEntry::sptr(new DoubleEntry(ename,cnt)));
			in>>*std::dynamic_pointer_cast<DoubleEntry>(e);
			break;
		default:
			std::cerr<<"IDF entry has unknow type code - do not know what to do with it!";
		}

		idf._entry_list.push_back(e);

	}

	//the last entry should be the offset to the next IDF entry
	in.read((char*)(&idf._idf_next_offset),4);

	return in;
}
*/


//end of namespace
}
}
}
