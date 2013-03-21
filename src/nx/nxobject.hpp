/*
 * Declaration of Nexus object template.
 *
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpniio.
 *
 * libpniio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpniio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Declaration of Nexus object template.
 *
 * Created on: Jul 1, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#pragma once

#include <memory>
#include <iostream>

#include <pni/core/types.hpp>
#include <pni/core/arrays.hpp>
#include <pni/core/scalar.hpp>

#include "nximp_map.hpp"
#include "nximp_code_map.hpp"
#include "nxattribute.hpp"
#include "nxobject_type.hpp"
#include "nxdate_time.hpp"
#include "nxattribute_iterator.hpp"

using namespace pni::core;

//selects a particular implementation depending on an other 
//implementation
#define MAPTYPE(type,implname)\
    typename nximp_map<nximp_code_map<type>::icode>::implname

//creates a type with a particular implementation using 
//depending on a particular implementation type.
#define OBJTYPE(nxname,type,implname)\
    (nxname)<MAPTYPE(type,implname) >

namespace pni{
namespace io{
namespace nx{
    //need this here to avoid name collisions with tango headers
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;
    /*! 
    \ingroup nexus_lowlevel
    \brief base class for all Nexus objects in the library.

    This class provides functionality common to all Nexus objects.  This
    includes methods for obtaining the name and path of an object in the Nexus
    tree, methods to set and get attributes, creation of links to an object.
    Methods for creating links to this objects are also included.
    */
    template<typename Imp> class nxobject 
    {
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
            //=====================public types================================
            //! shared poitner type to an NXObject
            typedef std::shared_ptr<nxobject<Imp> > shared_ptr; 

            //! attribute iterator type
            typedef nxattribute_iterator<nxobject<Imp>,
                   nxattribute<MAPTYPE(Imp,AttributeImpl)> > 
                       attr_iterator; //!< attribute iterator type
            //==================constructors and destructors===================
            //! default constructor
            nxobject(){ }

            //-----------------------------------------------------------------
            //! copy constructor
            nxobject(const nxobject<Imp> &o):_imp(o._imp)
            {
                //here we nothing to do - the default constructor
                //of the implementation object has already been 
                //called
            }

            //-----------------------------------------------------------------
            //! copy constructor from implementation
            nxobject(const Imp &imp):_imp(imp) { }

            //-----------------------------------------------------------------
            //! move constructor 
            nxobject(nxobject<Imp> &&o):_imp(std::move(o._imp)) { }

            //-----------------------------------------------------------------
            //! move constructor from implementation instance
            nxobject(Imp &&imp):_imp(std::move(imp)) { }

            //-----------------------------------------------------------------
            /*! 
            \brief copy constructor 

            Does copy construction from an arbitrary different implementation of
            nxobject<>. This implies that the two implementation instances are
            convertible.
            \tparam PImp implementation type of the original nxobject instance
            \param o original instance of the object
            */
            template<typename PImp> nxobject(const nxobject<PImp> &o):
                _imp(o.imp())
            { }
           
            //-----------------------------------------------------------------
            //! destructor
            virtual ~nxobject() { }

            //============assignment operators=================================
            //! copy assignment operator
            nxobject<Imp> &operator=(const nxobject<Imp> &o)
            {
                if(this == &o) return *this;
                this->_imp = o._imp;
                return *this;
            }

            //-----------------------------------------------------------------
            //! copy assignment operator for different implementations
            template<typename PImp> nxobject<Imp> &
                operator=(const nxobject<PImp> &o)
            {
                this->_imp = o.imp();
                return *this;
            }
                    
            //-----------------------------------------------------------------
            //! move assignment operator
            nxobject<Imp> &operator=(nxobject<Imp> &&o)
            {
                if(this == &o) return *this;
                this->_imp = std::move(o._imp);
                return *this;
            }


            //=============methods managing object names========================
            /*! 
            \brief retrieve objects path

            This method returns the absolute path to this object.
            \return objects absolute path
            */
            string path() const{ return _imp.path(); }

            //-----------------------------------------------------------------
            /*! 
            \brief retrieve objects base path

            Returns the base part of the absolute path of an object. For example
            if the path to an object is /scan_1/detector/data this method will
            return /scan_1/detector.
            \return base part of the absolute path
            */
            string base() const{ return _imp.base(); }

            //-----------------------------------------------------------------
            /*! 
            \brief retrieve an objects name

            Return the name of an object. This the top part of the absolute
            path.  If the path would be /scan_1/detector/data this method would
            return data.
            \return name of the object
            */
            string name() const{ return _imp.name(); }

            //=================attribute management methods====================
            /*! \brief create scalar attribute

            Template method creating a scalar atribute of type T. By default an
            exception is raised if an attribute of same name already exists. If
            ov=true the existing attribute will be overwritten and no exeption
            will be thrown.
            \throws nxattribute_error in case of attribute related errors
            \throws nxbackend_error in case of any other error
            \param n name of the attribute
            \param ov overwrite flag
            \return an instance of nxattribute
            */
            template<typename T> nxattribute<MAPTYPE(Imp,AttributeImpl)>
                attr(const string &n,bool ov=false) const
            {
                typedef nxattribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
                attr_type attr;

                try
                {
                    attr = attr_type(this->imp().template attr<T>(n,ov));
                }
                catch(nxattribute_error &error)
                {
                    error.append(EXCEPTION_RECORD);
                    throw error;
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
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
            \throws nxattribute_error in case of errors
            \param n name of the attribute
            \param s shape of the array
            \param ov overwrite flag
            \return instance of nxattribute
            */
            template<typename T,typename CTYPE> 
            nxattribute<MAPTYPE(Imp,AttributeImpl)>
                attr(const string &n, const CTYPE &s,bool ov=true) const
            {
                typedef nxattribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
                attr_type attr;

                try
                {
                    attr = attr_type(this->imp().template attr<T>(n,s,ov));
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Cannot create attribute ["+n+"] for object "
                            "["+this->path()+"]!");
                }
                return attr;
            }


            //-----------------------------------------------------------------
            /*! 
            \brief open an existing attribute by name
           
            Opens an existing attribute of name n and returns an instance of
            nxattribute<> to the callee. An exception will be thrown if the
            attribute does not exist.
            \throws nxattribute_error in case of problems
            \param n name of the attribute
            \return instance of nxattribute
            */
            nxattribute<MAPTYPE(Imp,AttributeImpl)> attr(const string &n) const
            {
                typedef nxattribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
                attr_type attr;

                try
                {
                    attr = attr_type(_imp.attr(n));
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
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
            \throws nxattribute_error in case of errors
            \param i index of the attribute
            \return instance of nxattribute
            */
            nxattribute<MAPTYPE(Imp,AttributeImpl)> attr(size_t i) const
            {
                typedef nxattribute<MAPTYPE(Imp,AttributeImpl)> attr_type;
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
                    throw nxattribute_error(EXCEPTION_RECORD,istr.str());
                }

                return attr;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief delete an attribute

            Deletes an attribute attached to this object.
            \throws nxattribute_error in case of errors
            \param n name of the attribute
            */
            void del_attr(const string &n) const
            {
                try
                {
                    this->imp().del_attr(n);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error deleting attribute ["+n+"]!");
                }
            }

            //-----------------------------------------------------------------
            /*! 
            \brief checks for attribute existance

            Checks whether or not an attribute with a particular name exits. If
            it does true is returned otherwise false.
            \throws nxattribute_error in case of errors
            \param n name of the attribute
            \return true if n exists otherwise false
            */
            bool has_attr(const string &n) const
            {
                try
                {
                    return this->imp().has_attr(n);
                }
                catch(...)
                {
                    throw nxattribute_error(EXCEPTION_RECORD,
                            "Error checking for attribute ["+n+"]!");
                }
                return false;
            }

            //-----------------------------------------------------------------
            /*! 
            \brief get number of attributes

            Returns the number of attributes attached to this object.
            \return number of attributes
            */
            size_t nattr() const { return this->imp().nattr(); }
          
            //==================+misc methods===================================
            //! close the object
            virtual void close() { this->_imp.close(); }

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
            nxobject_type object_type() const { return _imp.nxobject_type(); }

            //-----------------------------------------------------------------
            /*! 
            \brief return access time

            Return the time the object was accessed last as Nexus date-time
            string.
            \return access time as date-time string
            */
            string access_time() const
            {
                return nxdate_time::get_date_time_str(_imp.acc_time());
            }

            //-----------------------------------------------------------------
            /*! \brief return modification time

            Return the time when the object was last modified as a Nexus
            date-time string.
            \return modification time as date-time string
            */
            string modified_time() const
            {
                return nxdate_time::get_date_time_str(_imp.mod_time());
            }
            
            //-----------------------------------------------------------------
            /*! 
            \brief return data change time
            
            Return the time when the data held by the object was last changed as
            a Nexus date-time string (need to verify this). 
            \return change time as date-time string
            */
            string change_time() const
            {
                return nxdate_time::get_date_time_str(_imp.chng_time());
            }
            
            //-----------------------------------------------------------------
            /*! 
            \brief return object creation time

            Return the time when the object was created as Nexus date-time
            string. 
            \return creation time as date-time string
            */
            string create_time() const
            {
                return nxdate_time::get_date_time_str(_imp.birth_time());
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
        bool operator==(const nxobject<ImpA> &a,const nxobject<ImpB> &b)
    {
        if(a.imp() == b.imp()) return true;
        return false;
    }

    template<typename ImpA,typename ImpB>
        bool operator!=(const nxobject<ImpA> &a,const nxobject<ImpB> &b)
    {
        if(a == b) return false;
        return true;
    }

//end of namespace
}
}
}
