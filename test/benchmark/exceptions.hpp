/*
 * Exceptions.hpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */
#pragma once
#include<pni/utils/Types.hpp>
#include<pni/utils/Exceptions.hpp>

using namespace pni::utils;

/*!
\brief command line argument error

Thrown in cases where a command line argument (do not confuse this with an
option has an inapropriate value or is missing).
*/
class cli_argument_error:public Exception
{
    public:
        //---------------------------------------------------------------------
        //! default constructor
        cli_argument_error():Exception("CLIArgumentError"){}

        //---------------------------------------------------------------------
        /*! 
        \brief constructor

        \param r exception record
        \param d description
        */
        cli_argument_error(const ExceptionRecord &r,const String &d):
            Exception("CLIArgumentError",r,d)
        {}
        
        //---------------------------------------------------------------------
        //! destructor
        ~cli_argument_error() throw() {}

        //---------------------------------------------------------------------
        //! output operator
        friend std::ostream &operator<<(std::ostream &o,const cli_argument_error &e);
};

//-----------------------------------------------------------------------------
/*! 
\brief command line option error

Exception thrown in cases where a command line option is missing or has an
inapropriate value.
*/
class cli_option_error:public Exception
{
    public:
        //---------------------------------------------------------------------
        //! default constructor
        cli_option_error():Exception("CLIOptionError"){}

        //---------------------------------------------------------------------
        /*!
        \brief constructor

        \param r exception record
        \param d description
        */
        cli_option_error(const ExceptionRecord &r,const String &d):
            Exception("CLIOptionError",r,d)
        {}

        //---------------------------------------------------------------------
        ~cli_option_error() throw() {}

        //---------------------------------------------------------------------
        //! output operator
        friend std::ostream &operator<<(std::ostream &o,const cli_option_error &e);
};

//-----------------------------------------------------------------------------
/*!
\brief general CLI error

Thrown in case of a general CLI error not related to arguments or options.
*/
class cli_error:public Exception
{
    public:
        //---------------------------------------------------------------------
        //! default constructor
        cli_error():Exception("CLIError"){}
        
        //---------------------------------------------------------------------
        /*!
        \brief constructor

        \param r exception record
        \param d description
        */
        cli_error(const ExceptionRecord &r,const String &d):
            Exception("CLIError",r,d)
        {}

        //---------------------------------------------------------------------
        //! destructor
        ~cli_error() throw() {}

        //---------------------------------------------------------------------
        //! output operator
        friend std::ostream &operator<<(std::ostream &o,const cli_error &e);
};

//-----------------------------------------------------------------------------
/*!
\brief help request

This is exception is not intended to manage an error at all. It is thrown in the
case that a user makes a help request from the CLI.
*/
class cli_help_request:public Exception
{
    public:
        //---------------------------------------------------------------------
        //! default constructor
        cli_help_request():Exception("CLIHelpRequest"){}
        
        //---------------------------------------------------------------------
        /*!
        \brief constructor

        \param r exception record
        \param d description
        */
        cli_help_request(const ExceptionRecord &r,const String &d):
            Exception("CLIHelpRequest",r,d)
        {}

        //---------------------------------------------------------------------
        //! destructor
        ~cli_help_request() throw() {}

        //! output operator
        friend std::ostream &operator<<(std::ostream &o,const cli_help_request &e);
};
