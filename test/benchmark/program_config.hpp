/*
 * ProgramConfig.hpp
 *
 *  Created on: May 31, 2011
 *      Author: eugen
 */

#pragma once

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>
#include <pni/utils/Types.hpp>
#include <pni/utils/Exceptions.hpp>
#include "exceptions.hpp"
#include "config_option.hpp"
#include "config_argument.hpp"

//set an abriviation for the namespace
namespace popts = boost::program_options;
using namespace pni::utils;

/*!
\brief a general facility for program configuration

Class provides the base for all program configuration. It provides all the
options common to all programs. It bundles all the components requird by a
command line parser.
*/
class program_config 
{
    private:
        //! stores the program options
        popts::variables_map _vmap;

        //! options visible in the help
        popts::options_description _visible_opts;

        //! options hidden in the help output
        popts::options_description _hidden_opts;

        //! positional arguments description
        popts::positional_options_description _oargs;
    protected:
        /*!
        \brief print options

        Append options string representation to an output stream. Only the
        visible options are appended to the output stream.
        \param o reference to the output stream
        \return reference to output stream
        */
        std::ostream &print(std::ostream &o) const;
    public:
        //===================constructors and destructor=======================
        //! default constructor
        program_config();

        //! copy constructor - deleted
        program_config(const program_config &c) = delete;

        //---------------------------------------------------------------------
        //! destructor
        ~program_config() {}


        //=====================public member functions========================= 
        /*!
        \brief run the parser

        Run the command line parser.
        */
        void parse(int argc,char **argv);

        //---------------------------------------------------------------------
        /*!
        \brief check if option is there

        Return true if a particular option has been passed by the user.
        If the option is present true is returned otherwise false.
        \param name long name of the option
        \return true if option exists
        */
        bool has_option(const String &name) const;

        //---------------------------------------------------------------------
        /*! 
        \brief return the value of an option

        Template method returning the value of an option as instance of type T.
        If the option was created with a default value this value will be
        returned. If the option was created without default value an exception
        will be thrown.
        \tparam T return type of the method
        \throws MissingCommandLineOption if option is not present and has no
        default value
        \param name long name of the option
        \return value of the option as instance of type T
        */
        template<typename T> T value(const String &name) const
        {
            if(has_option(name)) return _vmap[name].as<T>();
            throw cli_option_error(EXCEPTION_RECORD,
                    "Program option ["+name+"] not passed or "
                    "inappropriate value!");
        }

        //---------------------------------------------------------------------
        /*!
        \brief add a program option


        */
        template<typename T>
        void add_option(const config_option<T> &opt,bool visible=true)
        {
            typedef boost::shared_ptr<popts::option_description> option_sptr;
            //assemble the name of the option
            String oname = opt.long_name();

            if(!opt.short_name().empty())
                oname += ","+opt.short_name();

            //assemble the sematnic value
            auto value =
                popts::value<T>(const_cast<T*>(opt.external_reference()));
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

        //---------------------------------------------------------------------
        void add_option(const config_option<Bool> &opt,bool visible=true);

        template<typename T> void add_argument(const config_argument<T> &arg)
        {
            typedef boost::shared_ptr<popts::option_description> option_sptr;
            //assemble the name of the option
            String oname = arg.long_name();

            //assemble the sematnic value
            auto value =
                popts::value<T>(const_cast<T*>(arg.external_reference()));

            option_sptr option_ptr (new popts::option_description(oname.c_str(),
                                    value,arg.description().c_str()));

            //finally we cann add the option
            _hidden_opts.add(option_ptr);

            _oargs.add(arg.long_name().c_str(),arg.position());
        }


        friend std::ostream &operator<<(std::ostream &o,const program_config &c);

};
