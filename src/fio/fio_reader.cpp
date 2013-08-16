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
 * FIOReader class implementation
 *
 * Created on: Apr 30, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */

#include <sstream>
#include <string>
#include <pni/io/fio/fio_reader.hpp>

namespace pni{
namespace io{

    //======================private member functions===========================
    void fio_reader::_parse_file(std::ifstream &stream)
    {
        string::value_type buffer; 
        while(!stream.eof())
        {
            //read a character
            stream>>buffer;
            if(buffer == '%')
            {
                //each section in the file starts with a % sign - now we need to
                //figure out which section we are
                stream>>buffer;
                switch(buffer){
                    case 'p':
                        //parameters section
                        _parse_parameters(stream); break;
                    case 'd':
                        //data section
                        _parse_data(stream); 
                        return; 
                        break;
                }

            }
        }

        //reset EOF bit
        stream.clear();
    }

    //-------------------------------------------------------------------------
    void fio_reader::_parse_parameters(std::ifstream &stream)
    {
        string::value_type buffer;
        string param_name;
        //clear the parameter map
        _param_map.clear();

        //read the parameter section
        while(!stream.eof())
        {
            //read a single character form the file
            stream>>buffer;
            
            //reached end of section
            if(buffer == '%') break;

            //handle comment lines
            if(buffer == '!')
            {
                while(stream.get() != '\n');
                continue;
            }

            //the first = character indicates the end of the parameter name
            if(buffer == '=')
            {
                //finished with this parameter
                _param_map.insert({param_name,stream.tellg()});
               
                //reset the paremter name
                param_name.clear();

                //move stream to end of line before continuing with 
                //all other parameters
                while(stream.get() != '\n');
                continue;
            }

            if(buffer != ' ') param_name.push_back(buffer);

        }

        //reset the stream for one position
        stream.seekg(-1,std::ios::cur);
        
    }

    //-------------------------------------------------------------------------
    void fio_reader::_parse_data(std::ifstream &stream)
    {
        boost::regex comment("^!"); //regular expression for comment lines
        boost::regex col("^ Col.*"); //column description match
        //boost::regex dcol("[+-]?\\d*.?\\d*[e]?[+-]?\\d*");
        boost::regex is_dcol("^\\s+[+-]?\\d+\\.?\\d*e?[+-]?\\d*.*");
        boost::smatch match;

        string linebuffer;
        std::streampos data_offset_tmp = 0;
        size_t nr = 0; //number of records

        while(!stream.eof())
        {
            //save the position of the stream pointer in case we will need it
            //later
            data_offset_tmp = stream.tellg();

            //read a line
            std::getline(stream,linebuffer);                
            
            //check if the line matches a column definition line
            if(boost::regex_match(linebuffer,match,col))
            {
                _append_column(_read_column_info(linebuffer));
                continue;
            }

            //if the column belongs to a data line we save the stream pointer
            //and break the loop - we have everything we wanted 
            if(boost::regex_match(linebuffer,match,is_dcol))
            {
                //if the _dataoffset has not been written yet 
                if(!_data_offset) _data_offset = data_offset_tmp;
                _read_data_line(linebuffer);
                nr++;
            }
        }
       
        //set the number of records in the file
        _nrecords(nr);
        //must be called here to clear EOF error bit
        //must be called before next call to seekg
        stream.clear();
    }

    //-------------------------------------------------------------------------
    void fio_reader::_get_parameter_data(std::ifstream &stream,string &value)
        const
    {
        char buffer;
        value.clear();

        while(!stream.eof())
        {
            stream.get(buffer);
            if(buffer == '\n') break;
            value.push_back(buffer);
        }
    }

    //=================implementation of static private methods================
    type_id_t fio_reader::_typestr2id(const string &tstr)
    {
        if(tstr == "FLOAT") 
            return type_id_t::FLOAT32;
        else if(tstr == "DOUBLE")
            return type_id_t::FLOAT64;
        else
            return type_id_t::NONE;
    }

    //-------------------------------------------------------------------------
    column_info fio_reader::_read_column_info(const string &line)
    {
        string cname;
        string ctype;
        size_t cindex;
        std::stringstream ss(line);
        ss>>cname>>cindex>>cname>>ctype;
        
        return column_info(cname,_typestr2id(ctype),std::vector<size_t>());
    }

    //-------------------------------------------------------------------------
    std::vector<string> fio_reader::_read_data_line(const string &line)
    {
        boost::regex dcol("[+-]?\\d+\\.?\\d*e?[+-]?\\d*");
        std::vector<string> record;

        boost::match_results<string::const_iterator> imatch;
        string::const_iterator start = line.begin();
        string::const_iterator end   = line.end();
        while(boost::regex_search(start,end,imatch,dcol,boost::match_default))
        {
            record.push_back(imatch.str());
            start = imatch[0].second;
        }

        return record;
    }

    //=======================constructors and destructor======================= 
    //default constructor implementation
    fio_reader::fio_reader():spreadsheet_reader() {}

    //--------------------------------------------------------------------------
    //move constructor implementation
    fio_reader::fio_reader(fio_reader &&r):
        spreadsheet_reader(std::move(r)),
        _param_map(std::move(r._param_map)),
        _data_offset(std::move(r._data_offset))
    {}

    //-------------------------------------------------------------------------
    //standard constructor implementation
    fio_reader::fio_reader(const string &n):
        spreadsheet_reader(n),
        _param_map(),
        _data_offset(0)
    {
        _parse_file(_get_stream()); 
    }

    //-------------------------------------------------------------------------
    //! destructor
    fio_reader::~fio_reader()
    {}

    //=================assignment operators====================================
    //move assignment implementation
    fio_reader &fio_reader::operator=(fio_reader &&r)
    {
        if(this == &r) return *this;
        spreadsheet_reader::operator=(std::move(r));
        _param_map = std::move(r._param_map);
        _data_offset = std::move(r._data_offset);

        return *this;
    }

    //=============public memeber methods======================================
    //implementation of nparameters
    size_t fio_reader::nparameters() const
    {
        return _param_map.size();
    }
    
    //-------------------------------------------------------------------------
    //implementation of parameter names
    std::vector<string> fio_reader::parameter_names() const
    {
        std::vector<string> pnames;
#ifdef NOFOREACH
        for(auto iter = _param_map.begin();iter!=_param_map.end();iter++)
        {
            auto value = *iter;
#else
        for(auto value: _param_map) 
        {
#endif
            pnames.push_back(value.first);
        }
        return pnames;
    }



//end of namespace
}
}
