//
// (c) Copyright 2017 DESY
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jun 8, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/parsers/parser.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>

namespace pni{

//!
//! @brief parser specialization for bool values
//!
//! This specialization of the parser template reads boolean values from a
//! string. The parser uses regular expressions to distinguish between
//! strings representing *true* and *false*.
//!
//! When instantiated using the default constructor
//!
//! * `TRUE`, `true` and `True` are interpreted as *true*
//! * and `FALSE`, `false` and `False` as *false*.
//!
template<>
class PNINEXUS_EXPORT parser<pni::bool_t>
{
  private:
    boost::regex _true_regex;
    boost::regex _false_regex;
  public:
    using result_type = bool;

    //!
    //! @brief default constructor
    //!
    //! With the default constructor the following regular expressions are
    //! used to distinguish between true and false
    //!
    //! * for *true* - `^T(rue|RUE)|true|1$`
    //! * for *false* - `^F(alse|ALSE)|false|0$`
    //!
    explicit parser();

    //!
    //! @brief constructor
    //!
    //! With this constructor the regular expressions used for *true* and
    //! *false* values can be customized.
    //!
    //! @param true_regex regular expression evaluating to true
    //! @param false_regex regular expression evaluating to false
    //!
    explicit parser(const pni::string &true_regex,
                    const pni::string &false_regex);

    result_type operator()(const pni::string &input) const;

};

//!
//! @brief parser specialization for bool values
//!
//! This specialization of the parser template reads boolean values from a
//! string. The parser uses regular expressions to distinguish between
//! strings representing *true* and *false*.
//!
//! When instantiated using the default constructor
//!
//! * `TRUE`, `true` and `True` are interpreted as *true*
//! * and `FALSE`, `false` and `False` as *false*.
//!
template<>
class PNINEXUS_EXPORT parser<hdf5::datatype::EBool>
{
  private:
    boost::regex _true_regex;
    boost::regex _false_regex;
  public:
    using result_type = hdf5::datatype::EBool;

    //!
    //! @brief default constructor
    //!
    //! With the default constructor the following regular expressions are
    //! used to distinguish between true and false
    //!
    //! * for *true* - `^T(rue|RUE)|true|1$`
    //! * for *false* - `^F(alse|ALSE)|false|0$`
    //!
    explicit parser();

    //!
    //! @brief constructor
    //!
    //! With this constructor the regular expressions used for *true* and
    //! *false* values can be customized.
    //!
    //! @param true_regex regular expression evaluating to true
    //! @param false_regex regular expression evaluating to false
    //!
    explicit parser(const pni::string &true_regex,
                    const pni::string &false_regex);

    result_type operator()(const pni::string &input) const;

};

}
