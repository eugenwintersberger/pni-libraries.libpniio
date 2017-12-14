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
// Created on: Dec 12, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/core/types.hpp>
#include <pni/core/type_erasures.hpp>
#include <pni/core/type_erasures/array.hpp>
#include <pni/core/arrays/mdarray.hpp>
#include <pni/io/nexus/datatype_factory.hpp>


//
// header file contains traits used to write data to HDF5 from an array
// type erasure
//
namespace hdf5 {
namespace datatype {

template<> class TypeTrait<pni::core::array>
{
  public:
    using TypeClass = Datatype;

    static TypeClass create(const pni::core::array &v)
    {
      return pni::io::nexus::DatatypeFactory::create(v.type_id());
    }
};

template<
         typename STORAGE,
         typename IMAP,
         typename IPA
        >
class TypeTrait<pni::core::mdarray<STORAGE,IMAP,IPA>>
{
  public:
    using Type = pni::core::mdarray<STORAGE,IMAP,IPA>;
    using TypeClass = typename TypeTrait<typename Type::value_type>::TypeClass;

    static TypeClass create(const  Type &v = Type())
    {
      return TypeTrait<typename Type::value_type>::create();
    }
};



} // namespace datatype
} // namespace hdf5

namespace hdf5 {
namespace dataspace {

template<> class TypeTrait<pni::core::array>
{
  public:
    using DataspaceType = Simple;

    static DataspaceType create(const pni::core::array &a)
    {
      auto shape = a.shape<hdf5::Dimensions>();
      return Simple(shape);
    }

    static void *ptr(pni::core::array &a)
    {
      return a.data();
    }

    static const void *cptr(const pni::core::array &a)
    {
      return a.data();
    }
};


template<
         typename STORAGE,
         typename IMAP,
         typename IPA
        >
class TypeTrait<pni::core::mdarray<STORAGE,IMAP,IPA>>
{
  public:
    using ArrayType = pni::core::mdarray<STORAGE,IMAP,IPA>;
    using DataspaceType = Simple;

    static DataspaceType create(const ArrayType &a)
    {
      return Simple(a.template shape<hdf5::Dimensions>());
    }

    static void *ptr(ArrayType &a)
    {
      return reinterpret_cast<void*>(a.data());
    }

    static const void*cptr(const ArrayType &a)
    {
      return reinterpret_cast<const void*>(a.data());
    }
};


} // namespace dataspace
} // namespace hdf5

namespace hdf5 {

template<>
class VarLengthStringTrait<pni::core::dynamic_array<std::string>>
{
  public:
    using BufferType = VarLengthStringBuffer<char>;
    using DataType   = pni::core::dynamic_array<std::string>;

    static BufferType to_buffer(const DataType &data)
    {
      BufferType buffer;
      std::transform(data.begin(),data.end(),std::back_inserter(buffer),
                     [](const std::string &str)
                     {
                      return const_cast<char*>(str.c_str());
                     });
      return buffer;
    }

    static void from_buffer(const BufferType &buffer,DataType &data)
    {
      std::transform(buffer.begin(),buffer.end(),data.begin(),
                     [](const char *ptr)
                     {
                       return std::string(ptr,std::strlen(ptr));
                     });
    }

};


} // namespace hdf 5

