/*
 * Declaration of an NXAttribute object
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __NXATTRIBUTEH5IMPLEMENTATION_HPP__
#define __NXATTRIBUTEH5IMPLEMENTATION_HPP__

#include "H5Attribute.hpp"

namespace pni{
    namespace nx{
        namespace h5{

            //! \ingroup nxh5_classes

            //! Implementation of an NXAttribute object. This class is 
            //! a delegate fro H5Attribute. Thus all code is defined 
            //! inline.
            class NXAttributeH5Implementation{
                private:
                    H5Attribute _attribute;                    
                public:
                    //==============constructors and destructors================
                    //! default constructor
                    explicit NXAttributeH5Implementation():
                        _attribute(){}

                    //! copy constructor
                    NXAttributeH5Implementation(const
                            NXAttributeH5Implementation &o):
                        _attribute(o._attribute){}

                    //! move constructor
                    NXAttributeH5Implementation(NXAttributeH5Implementation &&o):
                        _attribute(std::move(o._attribute)){}

                    //! copy constructor from H5Attribute
                    explicit NXAttributeH5Implementation(const H5Attribute &a):
                        _attribute(a){}

                    //! move constructor from H5Attribute
                    explicit NXAttributeH5Implementation(H5Attribute &&a):
                        _attribute(std::move(a)){}
                    
                    //! destructor
                    ~NXAttributeH5Implementation(){
                        _attribute.close();
                    }


                    //==============assignment operators========================
                    NXAttributeH5Implementation &
                        operator=(const NXAttributeH5Implementation &o)
                    {
                        if(this == &o) return *this;

                        _attribute = o._attribute;
                        return *this;
                    }
                    NXAttributeH5Implementation &
                        operator=(NXAttributeH5Implementation &&o)
                    {
                        if(this == &o) return *this;

                        _attribute = std::move(o._attribute);
                        return *this;
                    }


                    //================IO methods================================
                    template<typename T,template<typename> class BT> 
                        void write(const BT<T> buffer) const
                    {
                        _attribute.write(buffer);
                    }
                    //! write from Scalar<T> 
                    template<typename T> void write(const Scalar<T> &o) const
                    {
                        _attribute.write(o);
                    }
                    //! write from Array<T> 
                    template<typename T,template<typename> class BT >
                        void write(const Array<T,BT> &o) const
                    {
                        _attribute.write(o);
                    }

                    template<typename T> void write(const T &value) const
                    {
                        _attribute.write(value);
                    }
                    //! write from String
                    void write(const String &s) const
                    {
                        _attribute.write(s);
                    }

                    //! read to buffer 
                    template<typename T,template<typename> class BT> 
                        void read(BT<T> buffer) const
                    {
                        _attribute.read(buffer);
                    }

                    //! read to Array<T>
                    template<typename T,template<typename> class BT> 
                        void read(Array<T,BT> &a) const
                    {
                        _attribute.read(a);
                    }

                    //! read to Scalar<T>
                    template<typename T> void read(Scalar<T> &s) const
                    {
                        _attribute.read(s);
                    }

                    //! read to plain old data or string
                    template<typename T> void read(T &value) const
                    {
                        _attribute.read(value);
                    }
                    //! read to string
                    
                    //! read without argument
                    template<typename OBJ> OBJ read() const{
                        return _attribute.read<OBJ>();
                    }
                    void read(String &s) const
                    {
                        _attribute.read(s);
                    }

                    //=================properties for object inquery============
                    const Shape &shape() const{
                        return _attribute.shape();
                    }

                    TypeID type_id() const{
                        return _attribute.type_id();
                    }

                    void close()
                    {
                        _attribute.close();
                    }
                


            };


#endif
