/*
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
 * Definition of an HDF5 attribute object.
 *
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once
#include <vector>

#include <pni/utils/Types.hpp>
#include <pni/utils/Array.hpp>
#include <pni/utils/DBuffer.hpp>
#include <pni/utils/IDTypeMap.hpp>

#include "H5NamedObject.hpp"
#include "H5Attribute.hpp"
#include "H5DatatypeFactory.hpp"


namespace pni{
namespace nx{
namespace h5{
                     

    //forward declarations
    template<typename H5ObjectT,typename ItemT> class H5GroupIterator;
    
    /*! 
    \ingroup nxh5_classes
    \brief objects which can hold attributes

    H5AttributeObject is a type which is capable of holding attributes.
    In HDF5 this would be Datasets, Groups, and Files. The class
    provides all the methods responsible for manging attributes.
    */
    class H5AttributeObject:public H5NamedObject
    {
        private:
            /*! create attribute
            
            Creates an attribute of type T. If the ov flag is true
            the method overwrites an existing attribute of same name.
            Otherwise an exception will be thrown.
            \throw H5AttributeError in case of errors
            \param n name of the attribute
            \param ov overwrite flag 
            \param space dataspace to use for the attribute
            \return H5Attribute instance
            */
            template<typename T> H5Attribute __create_attr
                (const String &n, bool ov, const H5Dataspace &space) 
                const;

        protected:
            /*! \brief construction from HDF5 ID
            
            Constructor which allows object construction from an HDF5
            ID. As it is protected it can be only used by derived
            classes.
            \param oid HDF5 of the object
            */ 
            explicit H5AttributeObject(const hid_t &oid);
        public:
            //=================constructors and destructors====================
            //! default constructor
            explicit H5AttributeObject();

            //-----------------------------------------------------------------
            //! copy constructor
            explicit H5AttributeObject(const H5AttributeObject &o);

            //-----------------------------------------------------------------
            //! copy conversion constructor
            H5AttributeObject(const H5Object &o);

            //-----------------------------------------------------------------
            //! move constructor
            explicit H5AttributeObject(H5AttributeObject &&);

            //-----------------------------------------------------------------
            //! move conversion constructor
            H5AttributeObject(H5Object &&o);

            //-----------------------------------------------------------------
            /*! 
            \brief destructor

            Destructor - must be virtual in order to use this class as a base
            class.
            */
            virtual ~H5AttributeObject();

            //==================assignment operators===========================
            //! copy assignment operator
            H5AttributeObject &operator=(const H5AttributeObject &o);

            //-----------------------------------------------------------------
            //! copy conversion assignment operator
            H5AttributeObject &operator=(const H5Object &o);

            //-----------------------------------------------------------------
            //! move assignment operator
            H5AttributeObject &operator=(H5AttributeObject &&o);

            //-----------------------------------------------------------------
            //! move conversion assignment operator
            H5AttributeObject &operator=(H5Object &&o);

            //==============attribute management methods=======================
            /*! \brief create scalar attribute

            Create a scalar attribute of type T. Such an attribute can only take
            a single value of type T. The type T must be provided explicitly in
            the code. The method returns an instance of H5Attribute. If an
            attribute of name n already exists an exception will be thrown
            unless ov in the parameter list of the method is set to true. In
            this case the existing attribute will be overwritten.
            \throws H5AttributeError if attribute exists or in case of errors
            \param n name of the attribute
            \param ov overwrite attribute if true
            \return attribute object
            */
            template<typename T> H5Attribute 
                attr(const String &n,bool ov=false) const;

            //-----------------------------------------------------------------
            /*! \brief create an array attribute

            Create an array attribute of type T and shape s. The type
            must be explicitly given as a template parameter when using
            this method. If an attribute with name n already exists 
            an exception will be thrown unless ov is set to true.
            In the later case the existing attribute will be
            overwritten.
            \throws H5AttributeError if the attribute exists or in case of errors
            \param n name of the attribute
            \param s shape of the array
            \param ov overwrite attribute if true
            \return attribute object
            */
            template<typename T,
                    template<typename ...> class CTYPE,
                    typename ...OTS> 
            H5Attribute 
            attr(const String &n, const CTYPE<OTS...> &s,bool ov=false) const;

            //------------------------------------------------------------------
            /*! \brief open attribute by name
            
            Open an existing attribute and returns it to the callee.  If the
            attribute does not exist or an other error occurs during attribute
            creation H5AttributeError is thrown.
            \throws H5AttributeError if attribute does not exist or creation error
            \param n name of the attribute
            \return attribute object
            */
            H5Attribute attr(const String &n) const;

            //------------------------------------------------------------------
            /*! \brief open attribute by index

            Opens an attribute reference by index i. If i exceeds the number of
            attributes attached to this object an exception will be thrown.
            \throws IndexError if i exceeds 
            \param i index of the attribute
            \returns instance of H5Attribute
            */
            H5Attribute attr(size_t i) const;

            //-----------------------------------------------------------------
            /*! checks for an attributes existence

            Checks if an attribute exists and returns true if it does.
            Otherwise false will be returned.
            \throws H5AttributeError in case of errors
            \param n name of the attribute to check for
            \return true if exists, false otherwise
            */
            bool has_attr(const String &n) const;

            //-----------------------------------------------------------------
            /*! Deletes an attribute

            Deletes an attribute from the object. 
            \throws H5AttributeError in case of errors 
            \param n name of the attribute
            */
            void del_attr(const String &n) const;

            //-----------------------------------------------------------------
            /*! get number of attributes

            Method returns the number of attributes attached to this 
            object.
            \return number of attributes
            */
            size_t nattr() const;

            template<typename H5ObjectT,typename ItemT> friend class
                H5LinkIterator;
    };

    //===================implementation of template methods====================
    template<typename T> H5Attribute
        H5AttributeObject::__create_attr(const String &n,
                bool ov,const H5Dataspace &space) const
    {
        H5Datatype type = H5DatatypeFactory::create_type<T>();

        //what to do if the attribute already exists?
        if(has_attr(n))
        {
            //if the overwrite flag is set the original attribute will be removed
            if(ov) del_attr(n);
            else
            {
                String ss = "Attribute ["+n+"] already exists on "
                        "object ["+name()+"]!";
                throw H5AttributeError(EXCEPTION_RECORD,ss);
            }
        }

        hid_t aid = H5Acreate2(id(),n.c_str(),type.id(),space.id(),
                H5P_DEFAULT,H5P_DEFAULT);
        if(aid < 0)
        {
            H5AttributeError error(EXCEPTION_RECORD,"Cannot create attribute!");
            std::cout<<H5Tget_size(type.id())<<std::endl;
            std::cout<<space.size()<<std::endl;
            throw error;
        }

        H5Attribute a(aid);
        //H5Aclose(aid);
        return a;
    }

    //-------------------------------------------------------------------------
    //implementation of the scalar attribute factory method
    template<typename T> H5Attribute 
        H5AttributeObject::attr(const String &n,bool ov) const
    {
        H5Dataspace space;
        return __create_attr<T>(n,ov,space);   
    }
    

    //-------------------------------------------------------------------------
    //implementation of the array attribute factory method
    template<typename T,template<typename ...> class CTYPE,typename ...OTS> 
        H5Attribute 
        H5AttributeObject::attr(const String &n,const CTYPE<OTS...> &s, bool ov) 
        const
    {
        H5Dataspace space(s);
        return __create_attr<T>(n,ov,space);
    }

        

//end of namespace
}
}
}

