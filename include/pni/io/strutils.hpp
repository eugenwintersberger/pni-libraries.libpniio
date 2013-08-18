/*
 * strutils.hpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eugen
 */

#pragma once
//! strips a string

//! function strips leading and trailing signs from a string object
//! \param s string to strip
//! \param begrem string with signs to remove from the beginning
//! \param endrem string with signs to remove from the end of the string
//! \return new string with stripped content
std::string strip(std::string &s,const char *begrem="\n ",const char *endrem=" \n");

//! split into key value pairs

//! Function splits a string into a "key"/"value" pair according to a delimiter symbol.
//! \param s string to split
//! \param del delimiter string
//! \param key reference to the key
//! \param value reference to the value portion of the original string
int get_key_value(std::string &s,const char *del,std::string &key,std::string &value);

