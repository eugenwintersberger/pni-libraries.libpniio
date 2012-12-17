/*
 * ProgramConfig.cpp
 *
 *  Created on: May 31, 2011
 *      Author: eugen
 */

#include<string>
#include<vector>
#include<cstdio>
#include<cstdlib>

#include "program_config.hpp"

//-----------------------------------------------------------------------------
std::ostream &program_config::print(std::ostream &o) const
{
    return o<<_visible_opts;
}

//-----------------------------------------------------------------------------
program_config::program_config():
    _vmap(popts::variables_map()),
    _visible_opts(popts::options_description()),
    _hidden_opts(popts::options_description()),
    _oargs(popts::positional_options_description())
{
    //set command line options
    _visible_opts.add_options()
            ("help,h","print help message")
            ;
}


//----------------------------------------------------------------------------
void program_config::parse(int argc,char **argv)
{
    //merging hidden and visible options to a single option description
    popts::options_description total_opts;
    total_opts.add(_visible_opts);
    total_opts.add(_hidden_opts);

    //run the parser
    popts::store(popts::command_line_parser(argc,argv).
                 options(total_opts).
                 positional(_oargs).run(),
                 _vmap);

    //notify the variable map that we are done
    popts::notify(_vmap);
    
    if(has_option("help"))
        throw cli_help_request(EXCEPTION_RECORD,"help was requested!");
}

//-----------------------------------------------------------------------------
bool program_config::has_option(const String &name) const
{
    if(_vmap.count(name)) return true;
    return false;
}

//-----------------------------------------------------------------------------
void program_config::add_option(const config_option<Bool> &opt,bool visible)
{
    typedef boost::shared_ptr<popts::option_description> option_sptr;
    //assemble the name of the option
    String oname = opt.long_name();

    if(!opt.short_name().empty())
        oname += ","+opt.short_name();

    //assemble the sematnic value
    auto value =
        popts::bool_switch(const_cast<bool*>(opt.external_reference()));
    if(opt.has_default())
        value->default_value(opt.default_value());

    option_sptr option_ptr (new popts::option_description(oname.c_str(),
                            value,opt.description().c_str()));

    //finally we cann add the option
    if(visible)
        _visible_opts.add(option_ptr);
    else
        _hidden_opts.add(option_ptr);
}

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const program_config &c)
{
    return c.print(o);
}


