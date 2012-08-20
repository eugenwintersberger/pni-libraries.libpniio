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
#include <pni/utils/Array.hpp>
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
    /*! 
    \ingroup nexus_lowlevel
    \brief base class for all Nexus objects in the library.

    This class provides functionality common to all Nexus objects.  This
    includes methods for obtaining the name and path of an object in the Nexus
    tree, methods to set and get attributes, creation of links to an object.
    Methods for creating links to this objects are also included.
    */
    template<typename Imp> class NXObject {
        private:
            Imp _imp;	//!< implementation object
        protected:
            /*! 
            \brief return read/write reference to implementation

            This method is used only by derived classes and thus not 
            exposed to the public interface.
            \return reference to implementation
            */
            Imp &imp() { return _imp;}
        public:
            typedef NXAttributeIterator<NXObject<Imp>,
                   NXAttribute<MAPTYPE(Imp,AttributeImpl)> > 
                       attr_iterator; //!< attribute iterator type
            //==================constructors and destructors===================
            typedef std::shared_ptr<NXObject<Imp> > 
                shared_ptr; //!< shared poitner type to an NXObject
            //! default constructor
            NXObject(){
            }

            //-----------------------------------------------------------------
            //! copy constructor
            NXObject(const NXObject<Imp> &o):
                _imp(o._imp)
            {
                //here we nothing to do - the default constructor
                //of the implementation object has already been 
                //called
            }

            //-----------------------------------------------------------------
            //! copy constructor from implementation
            NXObject(const Imp &imp):_imp(imp) { }

            //-----------------------------------------------------------------
            //! move constructor 
            NXObject(NXObject<Imp> &&o):_imp(std::move(o._imp)) { }

            //-----------------------------------------------------------------
            //! move constructor from implementation instance
            NXObject(Imp &&imp):_imp(std::move(imp)) { }

            //-----------------------------------------------------------------
            /*! 
            \brief copy constructor 

            Does copy construction from an arbitrary different implementation of
            NXObject<>. This implies that the two implementation instances are
            convertible.
            */
            template<typename PImp> NXObject(const NXObject<PImp> &o):
                _imp(o.imp())
            { }
           
            //-----------------------------------------------------------------
            //! destructor
            virtual ~NXObject()
            {
                _imp.close();
            }

            //============assignment operators=================================
            //! copy assignment operator
            NXObject<Imp> &operator=(const NXObject<Imp> &o)
            {
                if(this == &o) return *this;
                _imp = o._imp;
                return *this;
            }

            //-----------------------------------------------------------------
            //! copy assignment operator for different implementations
            template<typename PImp> NXObject<Imp> &
                operator=(const NXObject<PImp> &o)
            {
                _imp = o.imp();
                return *this;
            }
                    
            //-----------------------------------------------------------------
            //! move assignment operator
            NXObject<Imp> &operator=(NXObject<Imp> &&o)
            {
                if(this == &o) return *this;
                _imp = std::move(o._imp);
                return *this;
            }


            //=============methods managing object names========================
            /*! retrieve objects path

            This method returns the absolute path to this object.
            \return objects absolute path
            */
            String path() const{ return _imp.path(); }

            //-----------------------------------------------------------------
            /*! 
            \brief retrieve objects base path

            Returns the base part of the absolute path of an object. For example
            if the path to an object is /scan_1/detector/data this method will
            return /scan_1/detector.
            \return base part of the absolute path
            */
            String base() const{ return _imp.base(); }

            //-----------------------------------------------------------------
            /*! 
            \brief retrieve an objects name

            Return the name of an object. This the top part of the absolute
            path.  If the path would be /scan_1/detector/data this method would
            return data.
            \return name of the object
            */
            String name() const{ return _imp.name(); }

            //=================attribute management methods====================
            /*! \brief create scalar attribute

            Template method creating a scalar atribute of type T. By default an
            exception is raised if an attribute of same name already exists. If
            ov=true the existing attribute will be overwritten and no exeption
            will be thrown.
            \throws NXAttributeError in case of errors
            \param n name of the attribute
            \param ov overwrite flag
            \return an instance of NXAttribute
            */
            template<typename T> NXAttribute<MAPTYPE(Imp,AttributeImpl)>
                attr(const String &n,bool ov=false) const
            {
                typedef NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
                attr_type attr;

                try
                {
                    attr = attr_type(this->imp().template attr<T>(n,ov));
                }
                catch(...)
                {
                    throw NXAttributeError(EXCEPTION_RECORD,
                            "Error creating attribute ["+n+"] for object"
                            " ["+this->path()+"]!");
                }
                return attr;
            }


            //-----------------------------------------------------------------
            /*! 
            \brief create an array attribute

            Template method creating a multidimensional attribute of type T and
            shape s. By default an exception will be thrown if an attribute of
            same name already exists. If ov=true an existing attribute will be
            overwritten
            \throws NXAttributeError in case of errors
            \param n name of the attribute
            \param s shape of the array
            \param ov overwrite flag
            \return instance of NXAttribute
            */
            template<typename T,typename CTYPE> 
            NXAttribute<MAPTYPE(Imp,AttributeImpl)>
                attr(const String &n, const CTYPE &s,bool ov=true) const
            {
                typedef NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
                attr_type attr;

                try
                {
                    attr = attr_type(this->imp().template attr<T>(n,s,ov));
                }
                catch(...)
                {
                    throw NXAttributeError(EXCEPTION_RECORD,
                            "Cannot create attribute ["+n+"] for object "
                            "["+this->path()+"]!");
                }
                return attr;
            }


            //-----------------------------------------------------------------
            /*! 
            \brief open an existing attribute by name
           
            Opens an existing attribute of name n and returns an instance of
            NXAttribute<> to the callee. An exception will be thrown if the
            attribute does not exist.
            \throws NXAttributeError in case of problems
            \param n name of the attribute
            \return instance of NXAttribute
            */
            NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr(const String &n) const
            {
                typedef NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
                attr_type attr;

                try
                {
                    attr = attr_type(_imp.attr(n));
                }
                catch(...)
                {
                    throw NXAttributeError(EXCEPTION_RECORD,
                            "Cannot open attribute ["+n+"] from object ["
                            +this->path()+"]!");
                }
                return attr;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief open an attribute by index
           
            Opens an existing attribute by its index. If the index exceeds the
            total number of attributes attached to this object an exception will
            be thrown.
            \throws NXAttributeError in case of errors
            \param i index of the attribute
            \return instance of NXAttribute
            */
            NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr(size_t i) const
            {
                typedef NXAttribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
                attr_type attr;

                try
                {
                    attr = attr_type(_imp.attr(i));
                }
                catch(...)
                {
                    std::stringstream istr;
                    istr<<"Cannot open attribute ["<<i<<"] from object [";
                    istr<<this->path()+"]!";
                    throw NXAttributeError(EXCEPTION_RECORD,istr.str());
                }

                return attr;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief delete an attribute

            Deletes an attribute attached to this object.
            \throws NXAttributeError in case of errors
            \param n name of the attribute
            */
            void del_attr(const String &n) const
            {
                try
                {
                    this->imp().del_attr(n);
                }
                catch(...)
                {
                    throw NXAttributeError(EXCEPTION_RECORD,
                            "Error deleting attribute ["+n+"]!");
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief checks for attribute existance

            Checks whether or not an attribute with a particular name exits. If
            it does true is returned otherwise false.
            \throws NXAttributeError in case of errors
            \param n name of the attribute
            \return true if n exists otherwise false
            */
            bool has_attr(const String &n) const
            {
                try
                {
                    return this->imp().has_attr(n);
                }
                catch(...)
                {
                    throw NXAttributeError(EXCEPTION_RECORD,
                            "Error checking for attribute ["+n+"]!");
                }
                return false;
            }

            //-----------------------------------------------------------------
            /*! get number of attributes

            Returns the number of attributes attached to this object.
            \returns number of attributes
            */
            size_t nattr() const { return this->imp().nattr(); }


          
            //==================+misc methods===================================
            //! close the object
            virtual void close() { _imp.close(); }

            //------------------------------------------------------------------
            /*! 
            \brief return implementation object

            Returns a const. reference to the implementation object.
            \return reference to implementation
            */
            const Imp &imp() const{ return _imp; }

            //------------------------------------------------------------------
            /*! 
            \brief checks object validity

            Method returns true if the object is a valid (open) Nexus object. 
            \returns true if valid object, false otherwise
            */
            bool is_valid() const{ return _imp.is_valid(); }

            //------------------------------------------------------------------
            /*! 
            \brief return object type
            
            Return an object identifier. This can be used to distinguish between
            group and field object.
            \return object identifier
            */
            NXObjectType object_type() const { return _imp.nxobject_type(); }

            //-----------------------------------------------------------------
            /*! 
            \brief return access time

            Return the time the object was accessed last as Nexus date-time
            string.
            \return access time as date-time string
            */
            String access_time() const
            {
                return NXDateTime::get_date_time_str(_imp.acc_time());
            }

            //-----------------------------------------------------------------
            /*! \brief return modification time

            Return the time when the object was last modified as a Nexus
            date-time string.
            \return modification time as date-time string
            */
            String modified_time() const
            {
                return NXDateTime::get_date_time_str(_imp.mod_time());
            }
            
            //-----------------------------------------------------------------
            /*! 
            \brief return data change time
            
            Return the time when the data held by the object was last changed as
            a Nexus date-time string (need to verify this). 
            \return change time as date-time string
            */
            String change_time() const
            {
                return NXDateTime::get_date_time_str(_imp.chng_time());
            }
            
            //-----------------------------------------------------------------
            /*! 
            \brief return object creation time

            Return the time when the object was created as Nexus date-time
            string. 
            \return creation time as date-time string
            */
            String create_time() const
            {
                return NXDateTime::get_date_time_str(_imp.birth_time());
            }

            //-----------------------------------------------------------------
            /*! 
            \brief iterator to frist attribute

            Return an iterator to the first attribute attached to the object.
            \return iterator to first attribute
            */
            attr_iterator attr_begin() const { return attr_iterator(*this); }

            //-----------------------------------------------------------------
            /*! 
            \brief iterator to last attribute

            Return an iterator to the last attribute attached to the object.
            \return iterator to last attribute
            */
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

//end of namespace
}
}


#endif /* NXOBJECT_HPP_ */
