/*
 * Declaration of Nexus object template.
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
 * Definition of the NXAttribute class.
 *
 * Created on: Feb 11, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __NXATTRIBUTE_HPP__
#define __NXATTRIBUTE_HPP__

#include "NXExceptions.hpp"

namespace pni{
    namespace nx{
       
        //! \ingroup nexus_lowlevel
        //! \brief attribute object

        //! NXAttribute represents an attribute which is attached to one 
        //! of the Nexus objects. Objects of this type can be used to 
        //! read and write attribute data from and to an object.
        template<typename Imp> class NXAttribute{
            private:
                Imp _imp;  //!< implementation of the attribute object
            public:
                //==========constructors and destructors=======================
                //! default constructor
                explicit NXAttribute():_imp(){}

                //-------------------------------------------------------------
                //! copy constructor
                NXAttribute(const NXAttribute<Imp> &a):
                    _imp(a._imp)
                {
                }

                //-------------------------------------------------------------
                //! move constructor
                NXAttribute(NXAttribute<Imp> &&a):
                    _imp(std::move(a._imp))
                {
                }

                //-------------------------------------------------------------
                //! copy constructor from implementation
                explicit NXAttribute(const Imp &i):
                    _imp(i)
                {
                }

                //-------------------------------------------------------------
                //! move constructor from implementation
                explicit NXAttribute(Imp &&i):
                    _imp(std::move(i))
                {
                }

                //-------------------------------------------------------------
                //!destructor
                ~NXAttribute(){
                    _imp.close();
                }

                //=========assignment operators=================================
                //! copy assignment operator
                NXAttribute<Imp> &operator=(const NXAttribute<Imp> &a)
                {
                    if(this == &a) return *this;

                    _imp = a._imp;
                    return *this;
                }

                //--------------------------------------------------------------
                //! move assignment operator
                NXAttribute<Imp> &operator=(NXAttribute<Imp> &&a)
                {
                    if(this == &a) return *this;
                    _imp = std::move(a._imp);
                    return *this;
                }

                //================IO methods====================================
                //! write from a buffer

                //! Write attribute data from a buffer object. The method 
                //! throws a
                template<typename T,template<typename> class BT> 
                    void write(const BT<T> buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void write(const BT<T> buffer) const"
                            "_imp.write(buffer);");

                    if(!buffer.is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,
                                "Buffer not allocated!");
                        EXCEPTION_THROW();
                    }
                    _imp.write(buffer);
                }

                //--------------------------------------------------------------
                //! write from Scalar<T> 
                template<typename T> void write(const Scalar<T> &o) const
                {
                    _imp.write(o);
                }

                //--------------------------------------------------------------
                //! write from Array<T> 
                template<typename T,template<typename> class BT >
                    void write(const Array<T,BT> &o) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT > void write(const Array<T,BT> &o) const");

                    if(!o.buffer().is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,
                                "Array not allocated!");
                        EXCEPTION_THROW();
                    }
                    _imp.write(o);
                }

                //--------------------------------------------------------------
                //! write single primitive value
                template<typename T> void write(const T &value) const
                {
                    _imp.write(value);
                }

                //--------------------------------------------------------------
                //! write from String
                void write(const String &s) const
                {
                    _imp.write(s);
                }

                //--------------------------------------------------------------
                //! read to buffer 
                template<typename T,template<typename> class BT> 
                    void read(BT<T> buffer) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void read(BT<T> buffer) const");
                    if(!buffer.is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,
                                "Buffer not allocated!");
                        EXCEPTION_THROW();
                    }
                    _imp.read(buffer);
                }

                //--------------------------------------------------------------
                //! read to Array<T>
                template<typename T,template<typename> class BT> 
                    void read(Array<T,BT> &a) const
                {
                    EXCEPTION_SETUP("template<typename T,template<typename> "
                            "class BT> void read(Array<T,BT> &a) const");

                    if(!a.buffer().is_allocated()){
                        EXCEPTION_INIT(MemoryAccessError,
                                "Array not allocated!");
                        EXCEPTION_THROW();
                    }
                    _imp.read(a);
                }

                //--------------------------------------------------------------
                //! read to Scalar<T>
                template<typename T> void read(Scalar<T> &s) const
                {
                    _imp.read(s);
                }

                //--------------------------------------------------------------
                //! read to plain old data or string
                template<typename T> void read(T &value) const
                {
                    _imp.read(value);
                }

                //--------------------------------------------------------------
                //! read to string
                void read(String &s) const
                {
                    _imp.read(s);
                } 
               
                //--------------------------------------------------------------
                //! read without argument
                template<typename OBJ> OBJ read() const
                {
                    return _imp.read<OBJ>();
                }

                //============simple maintenance methods========================
                //! obtain attribute shape
                Shape shape() const
                {
                    return _imp.shape();
                }

                //--------------------------------------------------------------
                //! obtain type id

                //! Returns the type ID of the data stored in the attribute.
                TypeID type_id() const
                {
                    return _imp.type_id();
                }

                //--------------------------------------------------------------
                //! close attribute
                void close()
                {
                    _imp.close();
                }

                //---------------------------------------------------------------
                String name() const
                {
                    return _imp.name();
                }

        };

    }
}

#endif
