//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpnicore.
//
// libpnicore is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpnicore is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpnicore.  If not, see <http://www.gnu.org/licenses/>.
//
// ===========================================================================
//
// Created on: Apr 2, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

//-----------------------------------------------------------------------------
#include <vector>
#include <iostream>
#include <fstream>
#include <pni/types.hpp>
#include <pni/type_erasures.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

using namespace pni;
using namespace boost::spirit;

typedef int32                    int_type;
typedef float64                  float_type;
typedef complex64                complex_type;
typedef std::vector<value>       record_type;
typedef std::vector<record_type> table_type;

//----------------------------------------------------------------------------
// complex number praser
//----------------------------------------------------------------------------
template<typename IteratorT>
struct complex_parser : public qi::grammar<IteratorT,complex_type()>
{
    qi::rule<IteratorT,complex_type()> complex_rule;

    complex_parser() : complex_parser::base_type(complex_rule)
    {
        using namespace boost::fusion;
        using namespace boost::phoenix;
        using qi::_1;
        using qi::_2;
        using qi::double_;
        
        complex_rule = ('('>>double_>>','>>double_>>')')
                        [_val = construct<complex_type>(_1,_2)];
    }
};

//----------------------------------------------------------------------------
// parse a single value
//----------------------------------------------------------------------------
template<typename IteratorT>
struct value_parser : public qi::grammar<IteratorT,pni::value()>
{
    qi::rule<IteratorT,pni::value()> value_rule;

    complex_parser<IteratorT> complex_;

    value_parser() : value_parser::base_type(value_rule)
    {
        using namespace boost::fusion;
        using namespace boost::phoenix;
        using qi::_1;
        using qi::char_;
        using qi::int_;
        using qi::double_;
        using qi::_val;

        value_rule = (
                     (int_ >> !(char_('.')|char_('e')))[_val =
                     construct<pni::value>(_1)]
                     || 
                     double_[_val = construct<pni::value>(_1)]
                     ||
                     complex_[_val = construct<pni::value>(_1)]
                     );
    }
};

//----------------------------------------------------------------------------
// parse an entire record
//----------------------------------------------------------------------------
template<typename IteratorT>
struct record_parser : public qi::grammar<IteratorT,record_type()>
{
    qi::rule<IteratorT,record_type()> record_rule;

    value_parser<IteratorT> value_;

    record_parser() : record_parser::base_type(record_rule)
    {
        using qi::blank;

        record_rule = value_ % (*blank);
    }
};

//-----------------------------------------------------------------------------
// read a single record from the stream
//-----------------------------------------------------------------------------
record_type parse_record(const string &line)
{
    typedef string::const_iterator iterator_type;
    typedef record_parser<iterator_type> parser_type;

    parser_type parser;
    record_type record;

    qi::parse(line.begin(),line.end(),parser,record);

    return record;
}

//-----------------------------------------------------------------------------
// read an entire table from a stream
//-----------------------------------------------------------------------------
table_type read_table(std::istream &stream)
{
    table_type table;
    string line;

    while(!stream.eof())
    {
        std::getline(stream,line);
        if(!line.empty())
            table.push_back(parse_record(line));
    }

    return table;
}

//-----------------------------------------------------------------------------
void write_value(std::ostream &stream,const value &v)
{
    type_id_t tid = v.type_id();
    switch(tid)
    {
        case type_id_t::Float64: stream<<v.as<float64>(); break;
        case type_id_t::Complex64: stream<<v.as<complex64>(); break;
        case type_id_t::Int32:     stream<<v.as<int32>(); break;
        default:
            type_error(PNINEXUS_EXCEPTION_RECORD,
                    "Value holds unkown data type!");
    }
}
//-----------------------------------------------------------------------------
// write a single record to the output stream
//-----------------------------------------------------------------------------
void write_record(std::ostream &stream,const record_type &r)
{
    for(auto v: r) 
    {
        write_value(stream,v);
        stream<<"\t";
    }
    stream<<std::endl; //terminate the output with a newline
}

//-----------------------------------------------------------------------------
// write the entire table to the output stream
//-----------------------------------------------------------------------------
void write_table(std::ostream &stream,const table_type &table)
{
    for(auto r: table) write_record(stream,r);
}

void file_to_stream(std::ostream &output_stream,const string fname)
{
    std::ifstream input_stream(fname);
    table_type table = read_table(input_stream);

    //check the different data types
    auto record = table.front();
    for(auto entry: record) output_stream<<type_id(entry)<<std::endl;

    write_table(output_stream,table);
}

//-----------------------------------------------------------------------------
int main(int ,char **)
{
    std::cout<<"File: record.dat"<<std::endl;
    file_to_stream(std::cout,"record.dat");
    std::cout<<std::endl<<"File: record2.dat"<<std::endl;
    file_to_stream(std::cout,"record2.dat");

    return 0;
}
