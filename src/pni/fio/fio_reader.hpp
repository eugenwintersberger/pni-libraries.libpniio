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
//============================================================================
//
// Created on: Apr 30, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <boost/regex.hpp>
#include <boost/current_function.hpp>
#include <boost/lexical_cast.hpp>

#include <pni/arrays.hpp>
#include <pni/spreadsheet_reader.hpp>
#include <pni/windows.hpp>

namespace pni{
   
    /*! \ingroup ascii_io
    \brief FIO data reader

    FIO files are written by ONLINE a data acquisition and experiment control
    software used at DESY. FIO files are basically ACII files where data is
    stored in columns. Thus such files correspond to the family of spreadsheet
    style files. 
    */
    class PNINEXUS_EXPORT fio_reader:public spreadsheet_reader
    {
        private:
#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif
    	    using parameter_map_type = std::map<pni::string,pni::string>;
    	    using column_type = std::vector<pni::string>;
    	    using column_map_type = std::map<pni::string,column_type>;
            //! parameter stream positions
            std::map<pni::string,pni::string> _param_map;
            //! column data
            std::map<pni::string,std::vector<pni::string>> _columns;
#ifdef _MSC_VER
#pragma warning(default:4251)
#endif

            //====================private member methods=======================
            /*! 
            \brief initial file parseing

            This private method runs through the entire file once and calles 
            the appropriate parses. 
            \param stream input stream from which to read data
            */
            void _parse_file(std::ifstream &stream);

            //-----------------------------------------------------------------
            /*! 
            \brief parse parameter section

            Method parses the parameter section of a file. It sets up the
            _param_map member variable. 
            \param stream input stream from which to read data
            */
            void _parse_parameters(std::ifstream &stream);

            //-----------------------------------------------------------------
            /*! 
            \brief parse the data section

            Private function which execudes parser code for the data section of
            the FIO file. It collects all the information about columns present
            in the file.
            \param stream input stream from which to read data
            */
            void _parse_data(std::ifstream &stream);

            //-----------------------------------------------------------------
            /*! 
            \brief type id from type string 

            Method converts a FIO type string to a TypeID as provided by
            libpninexus.
            \param tstr type string
            \return TypeID 
            */
            static pni::type_id_t _typestr2id(const pni::string &tstr);
          
            //------------------------------------------------------------------
            /*! 
            \brief read data line

            Reads a data line and splits the line into its cells. The method
            returns a vector of Strings where each elements corresponds to a
            particular cell. 
            \param line input line
            \return vector with cell content as strings
            */
            static std::vector<pni::string> _read_data_line(const pni::string &line);

            //-----------------------------------------------------------------
            /*! 
            \brief read parameter data

            This template is used internally to extract parameter data from the
            input stream and store the result in a variable of type T. 
            \param stream input stream
            \param value where to store data
            */
            template<typename T>
                void _get_parameter_data(std::ifstream &stream,T &value) const;

            //------------------------------------------------------------------
            /*! 
            \brief read string parameter

            Overloaded version of the _get_parameter_data template method to
            handle string data. 
            \param stream input stream
            \param value string value where to store parameter data
            */
            void _get_parameter_data(std::ifstream &stream,pni::string &value) const;

            //-------------------------------------------------------------------
            /*! 
            \brief read column data

            Private template method to read column data and store it to an array
            object. If EOF is reached before all data was read an exception will
            be thrown.
            \throw file_error if EOF is reached before end of data
            \param index index of the column in the file
            \param array instance of the Array template where to store the data
            */
            template<typename ContainerT> 
                void _read_column(size_t index,ContainerT &array) const;

        public:
            //==============constructor and destructor=========================
            //! default constructor
            fio_reader();

            //! copy construction is deleted
            fio_reader(const fio_reader &r) = delete;

            //! move constructor
            fio_reader(fio_reader &&r) = default;

            //! standard constructor
            fio_reader(const pni::string &n);

            //! destructor
            ~fio_reader();

            //===================assignment operators==========================
            //! copy assignment is deleted
            fio_reader &operator=(const fio_reader &r) = delete;

            //! move assignemnt operator
            fio_reader &operator=(fio_reader &&r) = default;

            //=================public member methods===========================
            /*! 
            \brief get number of parameters

            Return the number of parameters stored in the file.
            \return number of parameters
            */
            size_t nparameters() const;

            //-----------------------------------------------------------------
            /*! 
            \brief get parameter names

            Returns a vector of Strings holding the parameter names stored in
            the file.
            \return parameter names
            */
            std::vector<std::string> parameter_names() const;

            //-----------------------------------------------------------------
            /*! 
            \brief get parameter by name

            Return the value of a parameter stored in the FIO file by name. 
            \throws key_errror if parameter name does not exist
            \param name parameter name
            \return parameter value as type T
            */
            template<typename T> 
            T parameter(const std::string &name) const;
           
            //-----------------------------------------------------------------
            /*! 
            \brief get single column

            Returns a single column and stores the data into an array object.
            If the column name does not exist an exception is thrown.
            \throws key_error if column does not exist
            \throws file_error if EOF is reached before end of data
            \param n name of the column
            \return instance of ArrayT holding the data.
            */
            template<typename ContainerT> 
            ContainerT column(const std::string &n) const;

            //-----------------------------------------------------------------
            /*! 
            \brief read single column

            Read a single column and stores the result in an appropriate
            container. The method assumes that the container is of appropriate
            size and shape. 
            \throws key_error if the requested column does not exist
            \throws file_error in any other case of error
            \tparam ContainerT container type
            \param n name of the column
            \param c instance of ContainerT that will in the end contain the data
            */
            template<typename ContainerT> 
                void column(const std::string &n,ContainerT &c) const;

    };
    
    //==========implementation of private template methods=====================
    template<typename T> 
        void fio_reader::_get_parameter_data(std::ifstream &stream,T &value) const
    {
        stream>>value;
    }

    //======================template implementation============================
    template<typename T> 
    T fio_reader::parameter(const std::string &name) const
    {
        return boost::lexical_cast<T>(_param_map.at(name));
    }

    //-------------------------------------------------------------------------
    template<typename ContainerT> 
        void fio_reader::column(const std::string &n,ContainerT &c) const
    {
        using namespace pni;
        using value_type = typename ContainerT::value_type;

        try
        {
            const column_type &column  = _columns.at(n);

            size_t index=0;
            for(auto value: column)
            	c[index++] = boost::lexical_cast<value_type>(value);
        }
        catch(key_error &error)
        {
            //append a new issuer to the exception
            error.append(EXCEPTION_RECORD);
            throw error;
        }
    }


    //-------------------------------------------------------------------------
    template<typename ContainerT> 
    ContainerT fio_reader::column(const std::string &n) const
    {
        //create the container 
        //allocate a new array
        std::vector<size_t> s{this->nrecords()};
        ContainerT data(this->nrecords());

        this->column(n,data);

        return data;
    }


//end of namespace
}
