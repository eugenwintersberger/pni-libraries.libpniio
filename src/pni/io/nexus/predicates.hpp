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
// Created on: Dec 7, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/io/windows.hpp>
#include <boost/regex.hpp>

namespace pni {
namespace io {
namespace nexus {

//!
//! @brief abstract predicate interface for nodes
//!
//! This is the base class for all predicates related to HDF5 Node instances.
//!
class PNIIO_EXPORT NodePredicate
{
  public:
    //!
    //! @brief virtual destructor
    //!
    //! Required for inheritances
    //!
    virtual ~NodePredicate();

    //!
    //! @brief predicate operator
    //!
    //! Every specialization of this class has to implement this
    //! function.
    //!
    //! @param node reference to the node of interest
    //! @return true of the node matches the predicate, false otherwise
    //!
    virtual bool operator()(const hdf5::node::Node &node) const = 0;
};

//!
//! @brief predicate to search for base classes
//!
//! This predicate can be used in two particular ways
//! \li to search for any base class (when default constructed)
//! \li to search for a specific base class when constructed with a class name
//!
//! //! \code
//! using GroupList = std::list<hdf5::node::Group>;
//!
//! GroupList detectors;
//! hdf5::node::Group entry = ...;
//!
//! std::copy_if(node::RecursiveNodeIterator::begin(entry),
//!              node::RecursiveNodeIterator::end(entry),
//!              std::back_inserter(detectors),
//!              IsBaseClass("NXdetector"));
//! \endcode
//!
class PNIIO_EXPORT IsBaseClass : public NodePredicate
{
  private:
    std::string class_name_;
  public:
    //!
    //! @brief default constructor
    //!
    //! We use the compiler provided default implementation. When instantiated
    //! with the default constructor this predicate will match every base
    //! class.
    //!
    IsBaseClass() = default;

    //!
    //! @brief constructor
    //!
    //! A predicate instantiated with this constructor searches for a
    //! particular type of base class. The type is determined by the
    //! name argument of the constructor.
    //!
    //! @param name the name of the base class to match
    //!
    explicit IsBaseClass(const std::string &name);

    //!
    //! @brief copy constructor
    //!
    //! We use the compiler provided default implementation here.
    //!
    IsBaseClass(const IsBaseClass &) = default;

    //!
    //! @brief virtual destructor
    //!
    //! Required for inheritance.
    //!
    virtual ~IsBaseClass();

    //!
    //! @brief function call operator
    //!
    //! Returns true if the node matches the predicate, false otherwise.
    //! @param node reference to the node to check
    //!
    virtual bool operator()(const hdf5::node::Node &node) const;
};

//!
//! @brief matches an NXtransformations
//!
//! Child class of IsBaseClass that matches an NXtransformation.
//!
class PNIIO_EXPORT IsTransformation : public IsBaseClass
{
  public:
    IsTransformation();
    IsTransformation(const IsTransformation &) = default;

};

//!
//! @brief matches NXentry
//!
//! Child class of IsBaseClass that matches an NXentry
//!
class PNIIO_EXPORT IsEntry : public IsBaseClass
{
  public:
    IsEntry();
    IsEntry(const IsEntry &) = default;
};

//!
//! @brief matches NXsubentry
//!
//! Child class of IsBaseClass that matches NXsubentry
//!
class PNIIO_EXPORT IsSubentry : public IsBaseClass
{
  public:
    IsSubentry();
    IsSubentry(const IsSubentry &) = default;
};

//!
//! @brief matches NXdetector
//!
//! Child class of IsBaseClass that matches NXdetector
//!
class PNIIO_EXPORT IsDetector : public IsBaseClass
{
  public:
    IsDetector();
    IsDetector(const IsDetector &) = default;
};

//!
//! @brief matches NXinstrument
//!
//! Child class of IsBaseClass that matches NXinstrument
//!
class PNIIO_EXPORT IsInstrument : public IsBaseClass
{
  public:
    IsInstrument();
    IsInstrument(const IsInstrument &) = default;
};

//!
//! @brief matches NXsample
//!
//! Child class of IsBaseClass that matches NXsample
//!
class PNIIO_EXPORT IsSample : public IsBaseClass
{
  public:
    IsSample();
    IsSample(const IsSample &) = default;
};

//!
//! @brief matches NXdata
//!
//! Child class of IsBaseClass that matches NXdata
//!
class PNIIO_EXPORT IsData : public IsBaseClass
{
  public:
    IsData();
    IsData(const IsData &) = default;
};

//!
//! @brief predicate checking a NeXus name
//!
//! This predicate is checking a string if it is a valid NeXus name.
//! The regular expression used for this check is given
//! <a href="http://download.nexusformat.org/doc/html/datarules.html?highlight=valid%20name">
//! here</a>.
//!
class PNIIO_EXPORT IsValidNeXusName
{
  private:
    boost::regex name_regex_;
  public:
    IsValidNeXusName();

    bool operator()(const std::string &name) const;
};


} // namespace nexus
} // namespace io
} // namespace pni
