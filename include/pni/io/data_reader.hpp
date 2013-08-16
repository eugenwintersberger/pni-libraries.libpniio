/*
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
 * DataReader class definition
 *
 * Created on: Apr 23, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 */
#pragma once

#include <memory>
#include <iostream>
#include <fstream>
#include <pni/core/types.hpp>

using namespace pni::core;

namespace pni{
namespace io{

    /*! \ingroup general_io
    \brief base class for data readers

    This is the base class for all data readers. Actually this class only
    manages the name of the file to open for reading.  One cannot instantiate an
    object of this class directly. This is done via the concrete reader classes.
    Thus all constructors are protected making them available only for derived
    classes.
    */
    class data_reader
    {
        private:
            //! name of the file 
            string _fname;           
            //! flag determining how files will be opened
            bool _is_binary;         
            //the stream is accessed via a unique pointer this allows moveing
            //the stream around while benefiting from all advantages of a smart
            //pointer
            //! stream from which to read data
            mutable std::unique_ptr<std::ifstream> _istream;  

            /*! \brief open the stream

            Virtual private method opening the stream. This class provides a
            default implementation for this method. If a different way of
            opening a stream is required this method must be overloaded by child
            classes.
            \throws file_error if opening the file fails
            \throws memory_allocation_error if allocation of a stream object
            fails
            \param fname file name
            \return unique pointer to the input stream
            */
            std::unique_ptr<std::ifstream> 
                _open_stream(const string &fname) const;
        protected:
            /*! \brief get stream

            Return a non-const reference to the stream on the file. This method
            is protected and thus only available to derived classes which can
            use this method to obtain a reference to the stream.
            \return non-const stream reference
            \return reference to the input stream
            */
            std::ifstream &_get_stream() const { return *_istream; } 

            //-----------------------------------------------------------------
            /*! \brief set binary mode

            Set the stream mode to binary. This method is primarily used by 
            default constructors which do not have parameters.
            */
            void _set_binary() { _is_binary = true; }

            //=======================Constructors=============================== 
            //! default constructor
            data_reader();

            //-----------------------------------------------------------------
            /*! 
            \brief standard constructor

            This constructor takes the name of the file from which to reads data
            as its only argument and opens the file. 
            \throws FileError if opening the file fails
            \param fname name of the file
            \param binary if true stream will be opened in binary mode
            */
            explicit data_reader(const string &fname,bool binary=false);
           
            //-----------------------------------------------------------------
            //! move constructor
            data_reader(data_reader &&r);

            //-----------------------------------------------------------------
            //!copy constructor is deleted
            data_reader(const data_reader &r) = delete;
            
            //=======================assignment operator=======================
            //! copy assigment is deleted
            data_reader &operator=(const data_reader &r) = delete;

            //-----------------------------------------------------------------
            //! move assignment
            data_reader &operator=(data_reader &&r);
            
            
            
        public:
            //===============constructor and destructors===================
            //! destructor
            virtual ~data_reader();

            //====================member methods===========================
            /*! \brief get filename

            \return name of the file from which to read data
            */
            pni::core::string filename() const;

            //-------------------------------------------------------------
            /*! \brief set filename

            \param fname name of the file to read data from
            */
            void filename(const string &fname);

            //-------------------------------------------------------------
            //! close the file
            virtual void close();
            
            //-------------------------------------------------------------
            /*! \brief open file

            Opens the file given by filename. 
            \throws FileError in case of errors
            */
            virtual void open();

    };

//end of namespace
}
}
