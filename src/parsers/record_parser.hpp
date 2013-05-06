
#pragma once
#include<iostream>
#include<pni/core/types.hpp>
#include<pni/core/value.hpp>
#include<pni/core/array.hpp>
#include<vector>

#include <boost/variant.hpp>

#include "value_parser.hpp"
#include "delimiter_parser.hpp"
#include "array_parser.hpp"


namespace pni{
namespace io{

    typedef boost::variant<value,array> record_entry_t;
    typedef std::vector<record_entry_t> record_t;
    template<typename ITERT>
    struct record_parser : boost::spirit::qi::grammar<ITERT,record_t()>
    {
        boost::spirit::qi::rule<ITERT,record_t()> record_rule;
        boost::spirit::qi::rule<ITERT,record_entry_t()> entry_rule;
        
        value_parser<ITERT> value_;
        delimiter_parser<ITERT> delimiter_;
        array_parser<ITERT> array_;

        record_parser() : 
            record_parser::base_type(record_rule),
            delimiter_(),
            array_()
        {
            init();
        }

        record_parser(char column_separator,
                      char array_start,char array_stop,
                      char array_separator) :
            record_parser::base_type(record_rule),
            delimiter_(column_separator),
            array_(array_start,array_stop,array_separator)
        {
            init();
        }

        void init() 
        {
            using namespace boost::spirit::qi;
            using namespace boost::fusion;
            using namespace boost::phoenix;
            using boost::phoenix::push_back;

            entry_rule = (value_|array_);
            record_rule = (*blank>>(entry_rule % delimiter_))[_val = _2];    
        }
    };

//end of namespace
}
}

