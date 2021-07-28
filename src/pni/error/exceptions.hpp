//
// Declaration exception classes and related macros
//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
//
// ===========================================================================
//
// Created on: Apr 19, 2011
//     Author: Eugen Wintersberger
//
//

#pragma once

#include<iostream>
#include<string>
#include<exception>
#include<typeinfo>
#include<list>
#include<boost/current_function.hpp>

#include <pni/types/types.hpp>

#include <pni/windows.hpp>

namespace pni{

//================Macros related to exceptions==================================

//!
//! \ingroup error_classes
//! \brief macro creating an instance of ExceptionRecord
//!
#define EXCEPTION_RECORD\
    pni::exception_record(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION)

//! 
//! \ingroup error_classes
//! \brief forward an exception
//! 
//! This macro can be used to forward an exception caught from another 
//! function. It appends the exception_record of the current function to the 
//! existing exception and throws the exception again. Consider the 
//! following examples
/*!\code
try { value = buffer.at(index); }
EXCEPTION_FORWARD(IndexError)
EXCEPTION_FORWARD(MemoryNotAllocatedError)
\endcode
*/
//! Please note that the MUST NOT BE a semicolon at the end of this macro.
//!
#define EXCEPTION_FORWARD(ETYPE)\
    catch(ETYPE &error)\
    {\
        error.append(EXCEPTION_RECORD);\
        throw error;\
    }

    //========================Exception classes==================================
    //!
    //! \ingroup error_classes
    //! \brief exception record 
    //!
    //! Contains the basic information where an exception has been thrown.  This
    //! information consists of the source file, the line in the file, and the
    //! signature of the function where the error occurred. 
    //! Using the BOOST_CURRENT_FUNCTION macro defined in 
    //! boost/current_function.hpp such a record can easily be constructed with
    /*!
    \code
    exception_record r(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION);
    \endcode
    */
    //!
    class PNINEXUS_EXPORT exception_record
    {
        private:
#ifdef _MSC_VER
#pragma warning(disable: 4251)
#endif
            string _file;     //!< source file where the exception occured
            size_t _line;     //!< line number in the source file
            string _function; //!< function in which the error occured
#ifdef _MSC_VER
#pragma warning(default: 4251)
#endif
        public:
            //===================constructors and destructor===================
            //! no default constructor
            exception_record() = delete;

            //! constructor
            exception_record(const string &file,size_t line,const string &func):
                _file(file),
                _line(line),
                _function(func)
            {}

            //==================public member functions========================
            //! get file name
            const string &file() const { return _file; }
            //! get file line number
            size_t line() const { return _line; }
            //! get function
            const string &function() const { return _function; } 
    };

    //------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief error record output operator
    //!
    PNINEXUS_EXPORT 
    std::ostream & operator<<(std::ostream &o,const exception_record &rec); 

    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief Exceptions base class
    //!
    //! This is the base class for all exceptions used in this library. 
    //!
#ifdef _MSC_VER
#pragma warning(disable:4275)
#endif
    class PNINEXUS_EXPORT exception:public std::exception
    {
        private:
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
            //! name of the exception
            string _name;
            //! description of the error occured
            string _description; 
            //! exception records
            std::list<exception_record> _records;
#ifdef _MSC_VER
#pragma warning(default: 4251)
#endif
        protected:
            //! \brief ouptut method
            //!
            //! Protected method to be used by derived classes for 
            //! implementing exception printing to std::out.
            //!
            //! \param o reference to the ouptput stream
            //! \return output stream
            //!
            std::ostream &print(std::ostream &o) const;
        public:
            //===================public types==================================
            //! const iterator over the error record
            typedef std::list<exception_record>::const_iterator const_iterator;
            //===================constructors and destructor===================
            //! default constructor
            exception();

            //-----------------------------------------------------------------
            //!
            //! \brief constructor 
            //!
            //! \param n name of the exception
            //!
            exception(const string &n);

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor 
            //!
            //! \param n name of the exception
            //! \param rec Exception record of the initial location where the 
            //! error occured
            //!
            exception(const string &n, const exception_record &rec);

            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param n name of the exception
            //! \param rec exception record describing the location of the 
            //! first occurrence  of the error
            //! \param d description of the exception
            //!
            exception(const string &n, const exception_record &rec, 
                      const string &d);

            //-----------------------------------------------------------------
            //! virtual destructor
            virtual ~exception() throw() { }

            //===================public member functions=======================
            //! 
            //! \brief set the exception name
            //! \param name exception name
            //!
            void name(const std::string &name) { _name = name; }

            //-----------------------------------------------------------------
            //!
            //! \brief get the exceptions name
            //!
            //! \return reference to the string object holding the name
            //!
            const string &name() const { return _name; }

            //-----------------------------------------------------------------
            //!
            //! \brief add a new issuer
            //!
            //! Use this method to add a new issuer in the case that the 
            //! exception is re-thrown by an other function or class method.
            /*!
            \code
            ...
            catch(exception &error)
            {
                error.append(EXCEPTION_RECORD);
                throw error;
            }
            \endcode
            */
            //! With this a particular exception can be traced througout the 
            //! entire code.
            //! 
            //! \param n exception_record to append 
            //!
            void append(const exception_record &n) { _records.push_back(n); }
            void push_back(const exception_record &n) { _records.push_back(n); }

            //-----------------------------------------------------------------
            //!
            //! \brief set exception desccription
            //!
            //! \param desc description of the exception
            //!
            void description(const std::string &desc) { _description = desc; }

            //-----------------------------------------------------------------
            //!
            //! \brief get the exceptions description
            //!
            //! \return reference to the string object with the exceptions 
            //! description
            //!
            const string &description() const { return _description; }

            //-----------------------------------------------------------------
            //!
            //! \brief get number of record
            //!
            //! Returns the number of records associated with this exception.
            //!
            //! \return number of records
            size_t size() const { return _records.size(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief get iterator to first error record
            //!
            //! Return get a const iterator to the first error record in the 
            //! class.
            //! 
            //! \return iterator to first exception record
            //!
            const_iterator begin() const { return _records.begin(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get iterator to the last error record
            //!
            //! Return a const iterator pointing to the last+1 element in the 
            //! exception record list. 
            //! 
            //! \return iterator to last+1 exception record
            //!            
            const_iterator end() const { return _records.end(); }

            //-----------------------------------------------------------------
            //! output operator for exceptions
            friend PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &, const exception &);
            
    };
#ifdef _MSC_VER
#pragma warning(default:4275)
#endif

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief memory allocation error
    //! 
    //! This exception is typically raised when allocation of memory on the 
    //! heap fails. In other words when a call to new leads to a nullptr.
    //!
    class PNINEXUS_EXPORT memory_allocation_error: public exception 
    {
        public:
            //! default constructor
            memory_allocation_error() : exception("memory_allocation_error") 
            { }

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial issuer
            //! \param d description of the exception
            //!
            explicit memory_allocation_error(const exception_record &i, 
                                             const string &d):
                exception("memory_allocation_eror", i, d) 
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~memory_allocation_error() throw() { } 

            //-----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const memory_allocation_error &e);
    };

    //-------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief memory not allocated error
    //! 
    //! This exception is usually thrown if one tries to access not allocated 
    //! memory.
    //!
    class PNINEXUS_EXPORT memory_not_allocated_error: public exception
    {
        public:
            //! default constructor
            memory_not_allocated_error(): 
                exception("memory_not_allocated_error") 
            {}

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!  
            //! \param i ExceptionRecord of the initial location where the 
            //! error occurred 
            //! \param d description of the error
            //!
            explicit memory_not_allocated_error(const exception_record &i,
                                                const string &d):
                exception("memory_not_allocated_error",i,d) 
            {}

            //----------------------------------------------------------------
            //! destructor
            ~memory_not_allocated_error() throw() {}

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &o,const
                    memory_not_allocated_error &e);
    };


    //-------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief Shape mismatch error
    //!
    //! Raised in cases where the Shape objects of two objects are not equal.
    //!
    class PNINEXUS_EXPORT shape_mismatch_error: public exception 
    {
        public:
            //! default constructor
            shape_mismatch_error() : 
                exception("shape_mismatch_error") 
            { }

            //----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d description of the exception
            //!
            explicit shape_mismatch_error(const exception_record &i, 
                                           const string &d) :
                exception("shape_mismatch_error",i,d) 
            { }

            //----------------------------------------------------------------
            //! destructor
            ~shape_mismatch_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const shape_mismatch_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief Size mismatch error
    //!
    //! This exception will be raised in cases where buffer sizes do not meet 
    //! the requirements.
    //!
    class PNINEXUS_EXPORT size_mismatch_error: public exception 
    {
        public:
            //! default constructor
            size_mismatch_error() : exception("size_mismatch_error") 
            { }

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d description of the exception
            //!
            explicit size_mismatch_error(const exception_record &i, 
                                         const string &d) :
                exception("size_mismatch_error", i,d) 
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~size_mismatch_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const size_mismatch_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief index error
    //!
    //! Raised if the index passed to a [] operator exceeds the size of the
    //! container it belongs to.
    //!
    class PNINEXUS_EXPORT index_error: public exception 
    {
        public:
            //! default constructor
            index_error() : exception("index_error") 
            { }

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d description of the exception
            //!
            explicit index_error(const exception_record &i, const string &d) :
                exception("index_error", i, d) 
            { }
           
            //-----------------------------------------------------------------
            //! destructor
            ~index_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const index_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief key error
    //!
    //! Raised in cases where a problem with the key of a hash map occurs.
    //!
    class PNINEXUS_EXPORT key_error: public exception
    {
        public:
            //! default constructor
            key_error():exception("key_error"){}

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i ExceptionRecord of the initial occurrence of the 
            //! error
            //! \param d description of the error
            //!
            explicit key_error(const exception_record &i,const string &d):
                exception("key_error",i,d)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~key_error() throw() {}

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const key_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief file IO fails
    //!
    //! Raised typically in cases of problems with files.
    //!
    class PNINEXUS_EXPORT file_error: public exception 
    {
        public:
            //! default constructor
            file_error() : exception("file_error") { }

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d description of the exception
            //!
            explicit file_error(const exception_record &i, const string &d) :
                exception("file_error", i, d) 
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~file_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const file_error &e);

    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief data type error
    //!
    //! This exception is raised in cases of errors concerning data types.
    //!
    class PNINEXUS_EXPORT type_error: public exception 
    {
        public:
            //! default constructor
            type_error() : exception("type_error") { }
           
            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d error description as String
            //!
            explicit type_error(const exception_record &i, const string &d):
                exception("type_error", i, d) 
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~type_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const type_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief data value error
    //!
    //! This exception is raised in cases where a particular variable takes 
    //! an inappropriate value.
    //!
    class PNINEXUS_EXPORT value_error: public exception 
    {
        public:
            //! default constructor
            value_error() : exception("value_error") { }
           
            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d error description as String
            //!
            explicit value_error(const exception_record &i, const string &d):
                exception("value_error", i, d) 
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~value_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const value_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief data range error
    //!
    //! This exception is raised in cases where data values exceed the range
    //! spanned by their data type.
    //!
    class PNINEXUS_EXPORT range_error: public exception 
    {
        public:
            //! default constructor
            range_error(): exception("range_error"){ }

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! Constructor setting source and description of the error
            //! \param i error issuer as string
            //! \param d error description as string
            //!
            explicit range_error(const exception_record &i,const string &d):
                exception("range_error",i,d)
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~range_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const range_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief not implemented exception
    //!
    //! This exception can be used to mark methods of abstract or base classes
    //! as not implemented. Such an approach can be quite useful for debugging
    //! and development.
    //!
    class PNINEXUS_EXPORT not_implemented_error:public exception
    {
        public:
            //! default construtor
            not_implemented_error(): 
                exception("not_implemented_error")
            { }
            
            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d error description
            //!
            explicit not_implemented_error(const exception_record &i,
                                           const string &d):
                exception("not_implemented_error",i,d)
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~not_implemented_error() throw() { }

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const not_implemented_error &e);
    };


    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief iterator error
    //!
    //! Exception thrown in case of iterator errors.
    //!
    class PNINEXUS_EXPORT iterator_error:public exception
    {
        public:
            //! default constructor
            iterator_error():exception("iterator_error"){ }

            //-----------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! Constructor setting the issuer and description of the error.
            //! \param i exception_record of the initial occurrence of the 
            //! error
            //! \param d error description
            //!
            explicit iterator_error(const exception_record &i,const string &d):
                exception("iterator_error",i,d)
            { }

            //-----------------------------------------------------------------
            //! destructor
            ~iterator_error() throw() { }

            //-----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const iterator_error &e);
    };
    

    //-------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief command line argument error
    //!
    //! Thrown in cases where a command line argument (do not confuse this 
    //! with an option has an inapropriate value or is missing).
    //!
    class PNINEXUS_EXPORT cli_argument_error:public exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_argument_error():exception("cli_argument_error"){}

            //------------------------------------------------------------------
            //! 
            //! \brief constructor
            //!
            //! \param r exception record
            //! \param d description
            //!
            cli_argument_error(const exception_record &r,const string &d):
                exception("cli_argument_error",r,d)
            {}
            
            //------------------------------------------------------------------
            //! destructor
            ~cli_argument_error() throw() {}

            //------------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
                operator<<(std::ostream &o,const cli_argument_error &e);
    };

    //--------------------------------------------------------------------------
    //! 
    //! \ingroup error_classes
    //! \brief command line option error
    //!
    //! Exception thrown in cases where a command line option is missing or 
    //! has an inapropriate value.
    //!
    class PNINEXUS_EXPORT cli_option_error:public exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_option_error():exception("cli_option_error"){}

            //------------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param r exception record
            //! \param d description
            //!
            cli_option_error(const exception_record &r,const string &d):
                exception("cli_option_error",r,d)
            {}

            //------------------------------------------------------------------
            ~cli_option_error() throw() {}

            //------------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
            operator<<(std::ostream &o,const cli_option_error &e);
    };

    //--------------------------------------------------------------------------
    //!
    //! \ingroup error_classes
    //! \brief general CLI error
    //!
    //! Thrown in case of a general CLI error not related to arguments or 
    //! options.
    //!
    class PNINEXUS_EXPORT cli_error:public exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_error():exception("cli_error"){}
            
            //------------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param r exception record
            //! \param d description
            //!
            cli_error(const exception_record &r,const string &d):
                exception("cli_error",r,d)
            {}

            //------------------------------------------------------------------
            //! destructor
            ~cli_error() throw() {}

            //------------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &operator<<(std::ostream &o,const cli_error &e);
    };

    //--------------------------------------------------------------------------
    //!
    //! \ingroup errror_classes
    //! \brief help request
    //!
    //! This is exception is not intended to manage an error at all. It is 
    //! thrown in the case that a user makes a help request from the CLI.
    //!
    class PNINEXUS_EXPORT cli_help_request:public exception
    {
        public:
            //------------------------------------------------------------------
            //! default constructor
            cli_help_request():exception("cli_help_request"){}
            
            //------------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! \param r exception record
            //! \param d description
            //!
            cli_help_request(const exception_record &r,const string &d):
                exception("cli_help_request",r,d)
            {}

            //------------------------------------------------------------------
            //! destructor
            ~cli_help_request() throw() {}

            //----------------------------------------------------------------
            //! output operator
            friend PNINEXUS_EXPORT std::ostream &
            operator<<(std::ostream &o,const cli_help_request &e);
    };
}
