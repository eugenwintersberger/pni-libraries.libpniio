//
// (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: May 6, 2013
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <sstream>

#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <algorithm>
#include <iterator>

#include <pni/io/exceptions.hpp>
#include <pni/io/parsers/slice_parser.hpp>
#include <pni/io/parsers/bool_parser.hpp>
#include <pni/io/parsers/value_parser.hpp>
#include <pni/io/parsers/complex_parser.hpp>
#include <pni/io/parsers/parser.hpp>
#include <pni/io/container_io_config.hpp>


namespace pni{
namespace io{

//------------------------------------------------------------------------
//!
//! @brief std::vector parser
//!
//! This parser reads a linear container of data from a string. The data
//! type of the container is assumed to be homogeneous. This means that
//! all elements must match with the parser selected for the element
//! type.
//!
//! In their string representation container data is assumed to be embraced
//! between a start and a stop token. The elements are assumed to be
//! separated by a delimiter token.
//!
//! The container can be any STL compliant container type.
//!
//! @tparam T the value type of the vector
//!
template<typename T>
class parser<std::vector<T>>
{
  public:
    using value_type = T;
  private:
    parser<value_type>  _value_parser;
    container_io_config _config;

  public:
    using result_type = std::vector<value_type>;

    //!
    //! @brief constructor
    //!
    //! With this constructor a container IO configuration can be
    //! passed which determines the value seperator, start and stop symbols.
    //!
    //! @param config reference to the IO configuration
    //!
    parser(const container_io_config &config=container_io_config()):
      _config(config)
    {}

    result_type operator()(const pni::core::string &input) const
    {
      using namespace pni::core;
      auto first = input.begin();
      auto last  = input.end();
      //need to find the start and stop
      if(_config.start_symbol())
      {
        first = std::find(first,last,_config.start_symbol());
        if(first==last)
        {
          std::stringstream ss;
          ss<<"Input: "<<input<<" - has no start symbol!";
          throw parser_error(EXCEPTION_RECORD,ss.str());
        }
        std::advance(first,1);
      }

      if(_config.stop_symbol())
      {
        last = std::find(first,last,_config.stop_symbol());
        if(last==input.end())
        {
          std::stringstream ss;
          ss<<"Input: "<<input<<" - has no stop symbol!";
          throw parser_error(EXCEPTION_RECORD,ss.str());
        }
      }

      string buffer(first,last);
      std::vector<string> elements;
      string sep(1,_config.separator());
      boost::split(elements,buffer, boost::is_any_of(sep),
                   boost::token_compress_on);
      std::transform(elements.begin(),elements.end(),elements.begin(),
                     [](string &value) { boost::trim(value); return value; });
      auto new_end = std::remove_if(elements.begin(),elements.end(),
                                    [](const string &value) { return value.empty(); });

      result_type result;
      std::transform(elements.begin(),new_end,
                     std::back_inserter(result),
                     _value_parser);

      return result;
    }
};

//end of namespace
}
}
