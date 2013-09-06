#include<iostream>
#include<pni/core/types.hpp>
#include<pni/core/value.hpp>
#include<pni/core/array.hpp>
#include<vector>

#include <boost/variant.hpp>

#include <pni/core/config/configuration.hpp>
#include <pni/core/config/config_parser.hpp>


#include "array_parser.hpp"

using namespace pni::core;

class data2string :public  boost::static_visitor<string>
{
    public:
        string operator()(const value &data) const
        {
            std::stringstream s;
            s<<data;
            return s.str();
        }

        string operator()(const array &data) const
        {
            std::stringstream s;
            s<<data;
            return s.str();
        }

};




int main(int argc,char **argv)
{
    typedef string::const_iterator iterator_t;
    typedef record_parser<iterator_t> record_parser_t;
    configuration config;
    config.add_option(config_option<char>("column-sep","c","column separator",
                      ' '));
    config.add_option(config_option<char>("array-sep","d","array separator",
                      ' '));
    config.add_option(config_option<char>("array-start","s",
                "array start symbol",'['));
    config.add_option(config_option<char>("array-end","e",
                "array end symbol",']'));
    config.add_argument(config_argument<string>("record",-1));

    //parse the configuration
    parse(config,cliargs2vector(argc,argv));

    //setup input
    string input;
    if(config.has_option("record"))
        input = config.value<string>("record");
    else
    {
        std::cerr<<"you have to enter a recrod!"<<std::endl;
        return -1;
    }

    //setup the parser
    record_parser_t parser(config.value<char>("column-sep"),
                           config.value<char>("array-start"),
                           config.value<char>("array-end"),
                           config.value<char>("array-sep"));
    
    std::cout<<"input was: "<<input<<std::endl;
    record_t record;
    iterator_t start = input.begin();
    iterator_t end   = input.end();
    boost::spirit::qi::parse(start,end,parser,record);
    std::cout<<"number of elements: "<<record.size()<<std::endl;
    for(auto entry: record)
        std::cout<<boost::apply_visitor(data2string(),entry)<<std::endl;

    return 0;
}
