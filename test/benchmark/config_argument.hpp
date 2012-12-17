#pragma once

#include <pni/utils/Types.hpp>
#include "config_option.hpp"

using namespace pni::utils;

/*!
\brief class describing a program argument

Class holds all the information required for a command line arguments.
Arguments have at least a long name which can later be used to identify the
argument in the program configuration. However, this name never shows up in the
help list.

Command line arguments are identified by there position in the total argument
list. If this position is -1 then all the values from a current starting
position to the end of the argument list belong to this argument.
*/
template<typename T> class config_argument:public config_option<T>
{
    private:
        //! position of the argument in the argument list
        int _position;

    public:
        //-----------------------------------------------------------------
        //! default constructor
        config_argument();

        /*!
        \brief constructor

        \param lname long name of the option
        \param pos position of the argument
        \param exref optional external reference
        */
        config_argument(const String &lname,int pos,T *exref=nullptr);

        //-----------------------------------------------------------------
        /*!
        \brief constructor
       
        \param lname long name of the option
        \param pos position of the argument
        \param default_value the default value to use for this option
        \param exref external reference
        */
        config_argument(const String &lname,int pos,T default_value,
                       T *exref=nullptr);

        //-----------------------------------------------------------------
        //! destructor
        ~config_argument() {}

        //-----------------------------------------------------------------
        //! get short name 
        int position() const { return _position; }
};

//-----------------------------------------------------------------------------
template<typename T> config_argument<T>::config_argument():
    config_option<T>(),
    _position(0)
{}

//-----------------------------------------------------------------------------
template<typename T>
config_argument<T>::config_argument(const String &lname,int pos,T *exref):
    config_option<T>(lname,"","",exref),
    _position(pos)
{}

//-----------------------------------------------------------------------------
template<typename T>
config_argument<T>::config_argument(const String &lname,int pos,
                                    T default_value, T *exref):
    config_option<T>(lname,"","",default_value,exref),
    _position(pos)
{}

