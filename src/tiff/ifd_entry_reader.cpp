/*
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
 * Implementation of class template IFDEntryReader.
 *
 * Created on: Apr 26, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include "ifd_entry_reader.hpp"

namespace pni{
namespace io{
namespace tiff{

    void
    ifd_entry_reader<string,string>::read(std::vector<string> &r,std::ifstream &stream)
    {
        //in the special case of strings the size of the vector comming from the
        //calling method is the number of bytes all strings stored occupy. We
        //can use this and reset the vector as it will hold only entire string
        //objects not individual characters.
        size_t size = r.size(); 
        r.clear();

        //check wether or not all the data fits into the first 4 Bytes
        if (sizeof(char) * size > 4) 
        {
            //if data does not fit we interpret the 4 Bytes as offset and jump
            //to this position
            int32 offset = 0;
            stream.read((char *) (&offset), 4);
            stream.seekg(offset, std::ios::beg);
        }

        //start reading data
        std::vector<string> result(0);
        char buffer;
        string s;

        for (size_t i = 0; i < size; i++) 
        {
            //read a character from the stream
            stream.read((char *) (&buffer), sizeof(char));

            if (buffer == '\0') 
            {
                //if the end of a string was reached we store the string in the
                //vector and reset the string object.
                r.push_back(s);
                s.clear();
            }
            else
            {
                //add the character to the existing string
                s += buffer;
            }
        }
    }



//end of namespace
}
}
}
