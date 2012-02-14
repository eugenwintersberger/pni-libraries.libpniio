/*
 * Declaration of Nexus specific exceptions
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
 * Declaration of Nexus specific exceptions
 *
 * Created on: Aug 5, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef NXEXCEPTIONS_HPP_
#define NXEXCEPTIONS_HPP_

#include <iostream>
#include <pni/utils/Exceptions.hpp>

using namespace pni::utils;

namespace pni{
    namespace nx{

        //! \ingroup error_classes
        //! \brief field exception

        //! Raised if an error occured in one of the NXField methods.
        class NXFieldError:public Exception{
            public:
                //! default constructor
                explicit NXFieldError();
                //! constructor
                explicit NXFieldError(const String &i,const String &d);
                //! destructor
                ~NXFieldError() throw();
                
                //! output operator
                friend std::ostream &operator<<(std::ostream &o,
                                                const NXFieldError &e);
        };

        //---------------------------------------------------------------------
        //! \ingroup error_classes
        //! \brief Attribute Error

        //! Raised in cases where reading or writing an attribute failed.
        class NXAttributeError:public Exception{
            public:
                //! default constructor
                explicit NXAttributeError();
                //! constructor
                explicit NXAttributeError(const String &i,const String &d);
                //! destructor
                ~NXAttributeError() throw();
                
                //! output operator
                friend std::ostream &operator<<(std::ostream &o,
                                                const NXAttributeError &e);
        };

        //----------------------------------------------------------------------
        //! \ingroup error_classes
        //! \brief Group Error

        //! Error in case of group operations.
        class NXGroupError:public Exception{
            public:
                //! default constructor
                explicit NXGroupError();
                //! constructor
                explicit NXGroupError(const String &i,const String &d);
                //! destructor
                ~NXGroupError() throw();
                //! output operator
                friend std::ostream &operator<<(std::ostream &o,
                                                const NXGroupError &e);
        };

        //----------------------------------------------------------------------
        //! \ingroup error_classes
        //! \brief File Error

        //! File exception class.
        class NXFileError:public Exception {
            public:
                //! default constructor
                explicit NXFileError():Exception("NXFileError")
                {}

                //! constructor
                explicit NXFileError(const String &i,const String &d)
                    :Exception("NXFileError",i,d)
                {}

                //! destructor
                ~NXFileError() throw() 
                {}

                //! output operator
                friend std::ostream &operator<<(std::ostream &o,
                                                const NXFileError &e){
                    return e.print(o);
                }
        };

        //----------------------------------------------------------------------
        //! \ingroup error_classes
        //! \brief Selection Error

        //! Selection exception class.
        class NXSelectionError:public Exception {
            public:
                //! default constructor
                explicit NXSelectionError():Exception("NXFileError")
                {}

                //! constructor
                explicit NXSelectionError(const String &i,const String &d)
                    :Exception("NXFileError",i,d)
                {}

                //! destructor
                ~NXSelectionError() throw() 
                {}

                //! output operator
                friend std::ostream &operator<<(std::ostream &o,
                                                const NXSelectionError &e){
                    return e.print(o);
                }
        };


//end of namespace
    }
}


#endif /* NXEXCEPTIONS_HPP_ */
