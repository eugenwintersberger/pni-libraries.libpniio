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
    class NXFieldError:public exception
    {
        public:
            //! default constructor
            explicit NXFieldError();
            //! constructor
            explicit NXFieldError(const exception_record &i,const string &d);
            //! destructor
            ~NXFieldError() throw();
            
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const NXFieldError &e);
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Attribute Error

    Raised in cases where reading or writing an attribute failed.
    */
    class NXAttributeError:public exception
    {
        public:
            //! default constructor
            explicit NXAttributeError();
            //! constructor
            explicit NXAttributeError(const exception_record &i,const string &d);
            //! destructor
            ~NXAttributeError() throw();
            
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const NXAttributeError &e);
    };

    //-------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief Group Error

    Error in case of group operations.
    */
    class NXGroupError:public exception
    {
        public:
            //! default constructor
            explicit NXGroupError();
            //! constructor
            explicit NXGroupError(const exception_record &i,const string &d);
            //! destructor
            ~NXGroupError() throw();
            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const NXGroupError &e);
    };

    //--------------------------------------------------------------------------
    /*! 
    \ingroup error_classes
    \brief File Error

    File exception class.
    */
    class NXFileError:public exception 
    {
        public:
            //! default constructor
            explicit NXFileError():exception("NXFileError") {}

            //! constructor
            explicit NXFileError(const exception_record &i,const string &d)
                :exception("NXFileError",i,d)
            {}

            //! destructor
            ~NXFileError() throw() 
            {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const NXFileError &e)
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
    class NXSelectionError:public exception 
    {
        public:
            //! default constructor
            explicit NXSelectionError():exception("NXFilterError")
            {}

            //! constructor
            explicit NXSelectionError(const exception_record &i,const string &d)
                :exception("NXFilterError",i,d)
            {}

            //! destructor
            ~NXSelectionError() throw() 
            {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const NXSelectionError &e)
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
    class NXFilterError:public exception 
    {
        public:
            //! default constructor
            explicit NXFilterError():exception("NXFilterError")
            {}

            //! constructor
            explicit NXFilterError(const exception_record &i,const string &d)
                :exception("NXFilterError",i,d)
            {}

            //! destructor
            ~NXFilterError() throw() 
            {}

            //! output operator
            friend std::ostream &operator<<(std::ostream &o,
                                            const NXFilterError &e){
                return e.print(o);
            }
    };


//end of namespace
}
}
}
