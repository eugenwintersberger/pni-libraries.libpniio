#pragma once

#include <pni/utils/Types.hpp>

using namespace pni::utils;

/*!
\brief class describing a program option

Class holds all the information required for a command line option. Each command
line option has at least a long name. The short name, a single letter, can be
left empty. In addition every option is associated with a value the user has to
pass. The only exception from this rule are Bool options. Such options are only
considered as flags without taking any argument.
*/
template<typename T> class config_option
{
    private:
        //! long name of the option
        String _long_name;

        //! short name of the option
        String _short_name;

        //! description (help text)
        String _description;

        //! default value
        T _default_value;

        //! external reference
        const T *_ext_reference;

        //! determin if option has default value
        Bool _has_default;

    public:
        //-----------------------------------------------------------------
        //! default constructor
        config_option();

        /*!
        \brief constructor

        \param lname long name of the option
        \param sname short name (single letter) of the option
        \param description doc string of the option
        \param exref optional external reference
        */
        config_option(const String &lname,const String &sname,const String
                &description,T *exref=nullptr);

        //-----------------------------------------------------------------
        /*!
        \brief constructor
       
        \param lname long name of the option
        \param sname short name (single letter) of the option
        \param description doc string of the option
        \param default_value the default value to use for this option
        \param exref external reference
        */
        config_option(const String &lname,const String &sname,const String
                &description,T default_value,T *exref=nullptr);

        //-----------------------------------------------------------------
        //! destructor
        virtual ~config_option() {}

        //-----------------------------------------------------------------
        //! get long name
        String long_name() const { return _long_name; }

        //-----------------------------------------------------------------
        //! get short name 
        String short_name() const { return _short_name; }

        //-----------------------------------------------------------------
        //! get description
        String description() const { return _description; }

        //-----------------------------------------------------------------
        //! get default value
        T default_value() const { return _default_value; }

        //-----------------------------------------------------------------
        //! get external refernce
        const T *external_reference() const { return _ext_reference; }

        //-----------------------------------------------------------------
        //! check if option has a default value
        Bool has_default() const { return _has_default; }

};

//-----------------------------------------------------------------------------
template<typename T> config_option<T>::config_option():
    _long_name(),
    _short_name(),
    _description(),
    _default_value(),
    _ext_reference(nullptr),
    _has_default(false)
{}

//-----------------------------------------------------------------------------
template<typename T>
config_option<T>::config_option(const String &lname,const String &sname,
                                const String &description,T *exref):
    _long_name(lname),
    _short_name(sname),
    _description(description),
    _default_value(),
    _ext_reference(exref),
    _has_default(false)
{}

//-----------------------------------------------------------------------------
template<typename T>
config_option<T>::config_option(const String &lname,const String &sname,
                                const String &description,T default_value,
                                T *exref):
    _long_name(lname),
    _short_name(sname),
    _description(description),
    _default_value(default_value),
    _ext_reference(exref),
    _has_default(true)
{}
