//
// (c) Copyright 2017 DESY
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 6, 2017
//
#pragma once

#include <string>
#include <iostream>
#include <boost/regex.hpp>

namespace pni {
namespace io {
namespace nexus {

//!
//! \brief a 3 number version class
//!
//! Describes a version number.
//!
class Version
{
  public:
    //!
    //! @brief the number type used to represent version numbers
    using NumberType = unsigned long;
  private:
    NumberType major_;
    NumberType minor_;
    NumberType patch_;

    static NumberType get_number_from_part(const boost::smatch &match,
                                           const std::string &part_name);
  public:
    //!
    //! \brief default constructor
    //!
    //! Set all three version numbers to 0
    //!
    Version() noexcept;

    //!
    //! @brief constructor
    //! @param major the major version number
    //! @param minor the minor version number
    //! @param patch the patch version number
    //!
    Version(NumberType major, NumberType minor, NumberType patch) noexcept;

    //!
    //! @brief copy constructor
    //!
    //! We can use the compiler provided default implementation here as all
    //! members are trivially copyable.
    //!
    Version(const Version &) = default;

    //!
    //! @brief return the major version number
    //!
    NumberType major() const noexcept;

    //!
    //! @brief return the minor version number
    //!
    NumberType minor() const noexcept;

    //!
    //! @brief return the patch version number
    //!
    NumberType patch() const noexcept;

    //!
    //! @brief read version from a string
    //!
    //! The string must be formated as <MAJOR>.<MINOR>.<PATCH>. Otherwise
    //! a runtime exception will be thrown. Incomplete version numbers are
    //! permited starting from <MAJOR> downards. Non-existing elements of
    //! the version are assumed to be 0.
    //!
    //! @throws std::runtime_error in the case of a malformed input string
    //!
    //! @param str the string with the version number
    //! @return a new instance of Version
    //!
    static Version from_string(const std::string &str);

    //!
    //! @brief convert a Version to a string
    //!
    //! The result is a string with the format <MAJOR>.<MINOR>.<PATCH>.
    //! @param version reference to a instance of Version
    //! @return a new instance of std::string
    //!
    static std::string to_string(const Version &version);
};

//!
//! @brief output stream operator
//!
//! Writes an instance of Version to a std::ostream. The output format is the
//! same as for Version::to_string.
//!
//! @param stream   the stream where to write the version
//! @param version  reference to the Version to write
//! @return modified version of std::ostream
//! @sa Version::to_string
//!
std::ostream &operator<<(std::ostream &stream,const Version &version);

//!
//! @brief input stream operator
//!
//! Read an instance of Version from a stream. The input format expected
//! is the same as for Version::from_string.
//!
//! @param stream   reference to the stream from which to read the Version
//! @param version  reference to the version to which to read
//! @return modified input stream
//! @sa Version::from_string
//!
std::istream &operator>>(std::istream &stream,Version &version);

//!
//! @brief checks two version for equality
//!
//! Two version are considered equal if all of their parts are equal.
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//! @return true if versions are equal, false otherwise
//!
bool operator==(const Version &lhs,const Version &rhs);

//!
//! @brief checks if two versions are not equal
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//! @return true if versions are not equal, false otherwise
//!
bool operator!=(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is smaller or equal to the right
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
bool operator<=(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is strictly small than the right
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
bool operator<(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is bigger or equal than the right
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
bool operator>=(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is strictly bigger than the right
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
bool operator>(const Version &lhs,const Version &rhs);




} // namespace nexus
} // namespace io
} // namespace pni
