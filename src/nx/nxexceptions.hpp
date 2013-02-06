/*
 * Declaration of Nexus specific exceptions
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
 * Declaration of Nexus specific exceptions
 *
 * Created on: Aug 5, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <iostream>
#include <pni/core/exceptions.hpp>

using namespace pni::core;

namespace pni{
namespace io{
namespace nx{

    /*! 
    \ingroup error_classes
    \brief field exception

    Raised if an error occured in one of the NXField methods.
    */
    class nxfield_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxfield_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit nxfield_error(const exception_record &i,const string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~nxfield_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxfield_error &e);
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Attribute Error

    Raised in cases where reading or writing an attribute failed.
    */
    class nxattribute_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxattribute_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit nxattribute_error(const exception_record &i,const string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~nxattribute_error() throw();
           
            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxattribute_error &e);
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Group Error

    Error in case of group operations.
    */
    class nxgroup_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxgroup_error();

            //-----------------------------------------------------------------
            //! constructor
            explicit nxgroup_error(const exception_record &i,const string &d);

            //-----------------------------------------------------------------
            //! destructor
            ~nxgroup_error() throw();

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxgroup_error &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief File Error

    File exception class.
    */
    class nxfile_error:public exception 
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxfile_error():exception("nxfile_error") {}

            //-----------------------------------------------------------------
            //! constructor
            explicit nxfile_error(const exception_record &i,const string &d)
                :exception("nxfile_error",i,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~nxfile_error() throw() 
            {}

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxfile_error &e)
            {
                return e.print(o);
            }
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Selection Error

    Selection exception class.
    */
    class nxselection_error:public exception 
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxselection_error():exception("nxselection_error")
            {}

            //-----------------------------------------------------------------
            //! constructor
            explicit nxselection_error(const exception_record &i,const string &d)
                :exception("nxselection_error",i,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~nxselection_error() throw() 
            {}

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxselection_error &e)
            {
                return e.print(o);
            }
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Filter Error

    Filter exception class.
    */
    class nxfilter_error:public exception 
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxfilter_error():exception("nxfilter_error")
            {}

            //-----------------------------------------------------------------
            //! constructor
            explicit nxfilter_error(const exception_record &i,const string &d)
                :exception("nxfilter_error",i,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~nxfilter_error() throw() 
            {}

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxfilter_error &e){
                return e.print(o);
            }
    };

    //-------------------------------------------------------------------------
    /*!
    \brief error_classes
    \brief link error

    Exception thrown in case of link related errors.
    */
    class nxlink_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxlink_error():exception("nxlink_error")
            {}

            //-----------------------------------------------------------------
            //! constructor
            explicit nxlink_error(const exceptoin_record &i,const String &d)
                :exception("nxlink_error",i,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~nxlink_error() throw()
            {}

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxlink_error &e)
            {
                return e.print(o);
            }
    };

    //-------------------------------------------------------------------------
    /*!
    \brief error_classes
    \brief backend error

    Exception thrown in case of a general backend error.
    */
    class nxbackend_error:public exception
    {
        public:
            //-----------------------------------------------------------------
            //! default constructor
            explicit nxbackend_error():exception("nxbackend_error")
            {}

            //-----------------------------------------------------------------
            //! constructor
            explicit nxbackend_error(const exceptoin_record &i,const String &d)
                :exception("nxbackend_error",i,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~nxbackend_error() throw()
            {}

            //-----------------------------------------------------------------
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const nxbackend_error &e)
            {
                return e.print(o);
            }
    };




//end of namespace
}
}
}
