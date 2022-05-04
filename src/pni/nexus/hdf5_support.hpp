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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 12, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <pni/types.hpp>
#include <pni/type_erasures.hpp>
#include <pni/type_erasures/array.hpp>
#include <pni/arrays/mdarray.hpp>
#include <pni/nexus/datatype_factory.hpp>


//
// header file contains traits used to write data to HDF5 from an array
// type erasure
//
namespace hdf5 {
namespace datatype {

template<> class TypeTrait<pni::array>
{
  public:
    using TypeClass = datatype::Datatype;

    static TypeClass create(const pni::array &v)
    {
      return pni::nexus::DatatypeFactory::create(v.type_id());
    }

    const static Datatype  & get(const pni::array & ) {
      const static Datatype & cref_ = Datatype{};
      return cref_;
    }

};

template<
         typename StorageT,
         typename IndexMapT,
         typename InplaceArithmeticT
        >
class TypeTrait<pni::mdarray<StorageT,IndexMapT,InplaceArithmeticT>>
{
  public:
    using Type = pni::mdarray<StorageT,IndexMapT,InplaceArithmeticT>;
    using TypeClass = typename TypeTrait<typename Type::value_type>::TypeClass;

    static TypeClass create(const  Type & = Type())
    {
      return TypeTrait<typename Type::value_type>::create();
    }

    const static Datatype & get(const Type & = Type()) {
      const static Datatype & cref_ = Datatype();
      return cref_;
    }
};



} // namespace datatype
} // namespace hdf5

namespace hdf5 {
namespace dataspace {

template<> class TypeTrait<pni::array>
{
  public:
    using DataspaceType = Simple;

    static DataspaceType create(const pni::array &a)
    {
      auto shape = a.shape<hdf5::Dimensions>();
      return Simple(shape);
    }

    static void *ptr(pni::array &a)
    {
      return a.data();
    }

    static const void *cptr(const pni::array &a)
    {
      return a.data();
    }
  const static Dataspace & get(const pni::array &, hdf5::dataspace::DataspacePool &) {
      const static Dataspace & cref_ = Dataspace();
      return cref_;
    }
};


template<
         typename StorageT,
         typename IndexMapT,
         typename InplaceArithmeticT
        >
class TypeTrait<pni::mdarray<StorageT,IndexMapT,InplaceArithmeticT>>
{
  public:
    using ArrayType = pni::mdarray<StorageT,IndexMapT,InplaceArithmeticT>;
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

    const static Dataspace & get(const ArrayType &, hdf5::dataspace::DataspacePool &) {
    const static Dataspace & cref_ = Dataspace();
    return cref_;
  }

};


} // namespace dataspace
} // namespace hdf5

namespace hdf5 {

template<>
class VarLengthStringTrait<pni::dynamic_array<std::string>>
{
  public:
    using BufferType = VarLengthStringBuffer<char>;
    using DataType   = pni::dynamic_array<std::string>;

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

