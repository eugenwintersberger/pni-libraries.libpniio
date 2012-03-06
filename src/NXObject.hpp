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
 * Declaration of Nexus object template.
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXOBJECT_HPP_
#define NXOBJECT_HPP_

#include <memory>
#include <iostream>

#include <pni/utils/Types.hpp>
#include <pni/utils/ArrayObject.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/ScalarObject.hpp>
#include <pni/utils/Scalar.hpp>

#include "NXImpMap.hpp"
#include "NXImpCodeMap.hpp"
#include "NXAttribute.hpp"
#include "NXObjectType.hpp"
#include "NXDateTime.hpp"
#include "NXAttributeIterator.hpp"

using namespace pni::utils;

//selects a particular implementation depending on an other 
//implementation
#define MAPTYPE(type,implname)\
    typename NXImpMap<NXImpCodeMap<type>::icode>::implname

//creates a type with a particular implementation using 
//depending on a particular implementation type.
#define OBJTYPE(nxname,type,implname)\
    (nxname)<MAPTYPE(type,implname) >



namespace pni{
    namespace nx{
        //! \ingroup nexus_lowlevel
        //! \brief base class for all Nexus objects in the library.

        //! This class provides functionality common to all Nexus objects.
        //! This includes methods for obtaining the name and path of an object
        //! in the Nexus tree, methods to set and get attributes, creation of
        //! links to an object. Methods for creating links to this objects are
        //! also included.
        template<typename Imp> class NXObject {
            private:
                Imp _imp;	//!< implementation object
            protected:
                Imp &imp() { return _imp;}
            public:
                typedef NXAttributeIterator<NXObject<Imp>,
                       NXAttribute<MAPTYPE(Imp,AttributeImpl)> > attr_iterator;
                //==================constructors and destructors================
                typedef std::shared_ptr<NXObject<Imp> > sptr;
                //! default constructor
                NXObject(){
                }

                //--------------------------------------------------------------
                //! copy constructor
                NXObject(const NXObject<Imp> &o):
                    _imp(o._imp)
                {
                    //here we nothing to do - the default constructor
                    //of the implementation object has already been 
                    //called
                }

                //--------------------------------------------------------------
                //! copy constructor from implementation
                NXObject(const Imp &imp):_imp(imp)
                {
                }

                //--------------------------------------------------------------
                //! move constructor 
                NXObject(NXObject<Imp> &&o):_imp(std::move(o._imp))
                {
                }

                //--------------------------------------------------------------
                NXObject(Imp &&imp):_imp(std::move(imp))
                {
                }

                //-------------------------------------------------------------
                
                template<typename PImp> NXObject(const NXObject<PImp> &o):
                    _imp(o.imp())
                {
                }
                /*
                //-------------------------------------------------------------
                //! move constructor from implementation
                template<typename PImp> NXObject(PImp &&imp):
                    _imp(std::move(imp))
                {

                }*/
               
                //-------------------------------------------------------------
                //! destructor
                virtual ~NXObject(){
                    _imp.close();
                }

                //============assignment operators==============================
                NXObject<Imp> &operator=(const NXObject<Imp> &o)
                {
                    if(this == &o) return *this;
                    _imp = o._imp;
                    return *this;
                }

                //--------------------------------------------------------------
                //! copy assignment operator
                template<typename PImp> NXObject<Imp> &
                    operator=(const NXObject<PImp> &o)
                {
                    _imp = o.imp();
                    return *this;
                }
                        
                //--------------------------------------------------------------
                NXObject<Imp> &operator=(NXObject<Imp> &&o)
                {
                    if(this == &o) return *this;
                    _imp = std::move(o._imp);
                    return *this;
                }


                //=========methods managing object names========================
                //! retrieve objects path

                //! This method returns the absolute path to this object.
                //! \return objects absolute path
                String path() const{
                    return _imp.path();
                }

                //! retrieve objects base path

                //! Returns the base part of the absolute path of an object. For example
                //! if the path to an object is /scan_1/detector/data this method
                //! will return /scan_1/detector.
                //! \return base part of the absolute path
                String base() const{
                    return _imp.base();
                }

                //! retrieve an objects name

                //! Return the name of an object. This the top part of the absolute path.
                //! If the path would be /scan_1/detector/data this method would
                //! return data.
                //! \return name of the object
                String name() const{
                    return _imp.name();
                }

                //===========attribute management methods==================
                //! create scalar attribute

                //! Create a scalar attribute. This method acts as a 
                //! factory method for an attribute object.
                //! \param n name of the attribute
                //! \param tid ID of the data-type
                //! \return attribute object
                template<typename T> NXAttribute<MAPTYPE(Imp,AttributeImpl)>
                    attr(const String &n,bool ov=false) const
                {
                    return NXAttribute<MAPTYPE(Imp,AttributeImpl)>
                        (this->imp().attr<T>(n,ov));
                }


                //--------------------------------------------------------------
                //! create an array attribute

                //! Create an array attribute. This method acts as a 
                //! factory method for an attribute object.
                //! \param n name of the attribute
                //! \param tid ID of the data-type
                //! \param s shape of the array
                //! \return attribute object
                template<typename T> NXAttribute<MAPTYPE(Imp,AttributeImpl)>
                    attr(const String &n, const Shape &s,bool ov=true) const
                {
                    return NXAttribute<MAPTYPE(Imp,AttributeImpl)>
                        (this->imp().attr<T>(n,s,ov));
                }


                //--------------------------------------------------------------
                //! open an attribute by name
                
                //! Open an existing attribute and returns it to the 
                //! callee. 
                //! \param n name of the attribute
                //! \return attribute object
                NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr(const String &n) const
                {
                    return NXAttribute<MAPTYPE(Imp,AttributeImpl)>(_imp.attr(n));
                }

                //--------------------------------------------------------------
                //! open an attribute by index
                
                //! Open an existing attribute and returns it to the 
                //! callee. 
                //! \param n name of the attribute
                //! \return attribute object
                NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr(size_t i) const
                {
                    return NXAttribute<MAPTYPE(Imp,AttributeImpl)>(_imp.attr(i));
                }

                //-------------------------------------------------------------
                //! delete an attribute

                //! Deletes an attribute attached to this object.
                //! \throws NXAttributeError in case of errors
                //! \param n name of the attribute
                void del_attr(const String &n) const
                {
                    EXCEPTION_SETUP("void del_attr(const String &n) const");
                    try{
                        this->imp().del_attr(n);
                    }catch(...){
                        EXCEPTION_INIT(NXAttributeError,
                                "Error deleting attribute ["+n+"]!");
                        EXCEPTION_THROW();
                    }
                }

                //-------------------------------------------------------------
                //! checks for attribute existance

                //! Checks whether or not an attribute with a particular name
                //! exits. If it does true is returned otherwise false.
                //! \throws NXAttributeError in case of errors
                //! \param n name of the attribute
                //! \return true if n exists otherwise false
                bool has_attr(const String &n) const
                {
                    EXCEPTION_SETUP("bool has_attr(const String &n) const");

                    try{
                        return this->imp().has_attr(n);
                    }catch(...){
                        EXCEPTION_INIT(NXAttributeError,
                                "Error checking for attribute ["+n+"]!");
                        EXCEPTION_THROW();
                    }
                    return false;
                }

                //------------------------------------------------------------
                //! get number of attributes

                //! Returns the number of attributes attached to this 
                //! object.
                //! \returns number of attributes
                size_t nattr() const
                {
                    return this->imp().nattr();
                }


              
                //=============misc methods===================================
                //! close the object
                virtual void close()
                {
                    _imp.close();
                }

                //--------------------------------------------------------------
                const Imp &imp() const{
                    return _imp;
                }

                //--------------------------------------------------------------
                bool is_valid() const{
                    return _imp.is_valid();
                }

                //--------------------------------------------------------------
                NXObjectType object_type() const
                {
                    return _imp.nxobject_type();
                }

                //-------------------------------------------------------------
                String access_time() const
                {
                    return NXDateTime::getDateTimeStr(_imp.acc_time());
                }

                //-------------------------------------------------------------
                String modified_time() const
                {
                    return NXDateTime::getDateTimeStr(_imp.mod_time());
                }
                
                //-------------------------------------------------------------
                String change_time() const
                {
                    return NXDateTime::getDateTimeStr(_imp.chng_time());
                }
                
                //-------------------------------------------------------------
                String create_time() const
                {
                    return NXDateTime::getDateTimeStr(_imp.birth_time());
                }

                //-------------------------------------------------------------
                attr_iterator attr_begin() const
                {
                    return attr_iterator(*this);
                }

                //-------------------------------------------------------------
                attr_iterator attr_end() const
                {
                    return attr_iterator(*this,this->nattr());
                }

        };

        //=============comparison operators====================================
        template<typename ImpA,typename ImpB>
            bool operator==(const NXObject<ImpA> &a,const NXObject<ImpB> &b)
        {
            if(a.imp() == b.imp()) return true;
            return false;
        }

        template<typename ImpA,typename ImpB>
            bool operator!=(const NXObject<ImpA> &a,const NXObject<ImpB> &b)
        {
            if(a == b) return false;
            return true;
        }
    }
}


#endif /* NXOBJECT_HPP_ */
