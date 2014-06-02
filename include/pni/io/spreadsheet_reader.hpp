//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpniio.
//
// libpniio is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpniio is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpniio.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Apr 30, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <vector>
#include <boost/current_function.hpp>
#include <pni/core/types.hpp>
#include <pni/core/error.hpp>
#include "data_reader.hpp"
#include "column_info.hpp"

namespace pni{
namespace io{

    //!
    //! \ingroup ascii_io
    //! \brief base class for spreadsheet reader
    //!
    //! This class is the basement for all readers dealing with spreadsheet 
    //! like data files. Most of the ASCII formats written following this 
    //! storage convention. 
    //!
    class spreadsheet_reader:public data_reader
    {
        private:
            std::vector<column_info> _columns_info; //!< column information
            size_t _nrec;    //!< number of records in the sheet

        protected:
            //============constructors and destructor==========================
            //! default constructor
            spreadsheet_reader();

            //! copy constructor is deleted
            spreadsheet_reader(const spreadsheet_reader &) = delete;

            //! move constructor
            spreadsheet_reader(spreadsheet_reader &&o);

            //! standard constructor
            spreadsheet_reader(const string &n);

            //==================protected member functions======================
            //!
            //! \brief append a column
            //!
            //! Protected method used by child classes to add a new column to 
            //! the reader.
            //!
            //! \param i column info to add
            //!
            virtual void _append_column(const column_info &i)
            {
                _columns_info.push_back(i);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get column information
            //!
            //! Protected method used by child classes to retriev the info 
            //! object for column i in the file.
            //!
            //! \param i index of the column in the file
            //! \return ColumnInfo instance for this column
            //!
            virtual column_info _get_column(size_t i) const
            {
                return _columns_info.at(i);
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get column information 
            //!
            //! Protected method used by child classes to obtain column 
            //! information by using the name of the column. 
            //!
            //! \throws key_error if the name of the column does not exist
            //! \param n name of the column
            //! \return column_info instance for this column
            //!
            virtual column_info _get_column(const string &n) const
            {
                size_t i=0;
                for(auto c: _columns_info)
                {
                    if(c.name() == n)
                        return _get_column(i); 

                    //increment column counter
                    i++;
                }
               
                throw key_error(EXCEPTION_RECORD,"Column ["+n+"] not found!");

                return column_info(); //just to get rid of compiler warning
            }

            //-----------------------------------------------------------------
            //!
            //! \brief set number of records
            //!
            //! Child classes can use this method to set the number of 
            //! records in the spreadsheet. 
            //!
            //! \param n number of records
            //!
            void _nrecords(size_t n) { _nrec = n; }


        public:
            //========================public type==============================
            //! iterator type
            typedef std::vector<column_info>::iterator iterator;
            //! const iterator type
            typedef std::vector<column_info>::const_iterator const_iterator; 
            //=======================destructor================================
            //! destructor
            virtual ~spreadsheet_reader();

            //===================assignment operators==========================
            //! copy assignment operator is deleted
            spreadsheet_reader &operator=(const spreadsheet_reader &) = delete;

            //-----------------------------------------------------------------
            //! move assignment operator
            spreadsheet_reader &operator=(spreadsheet_reader &&r);

            //===============public memeber methods============================
            //!
            //! \brief get column number 
            //!
            //! Returns the number of columns. 
            //! \return number of columns
            //!
            size_t ncolumns() const
            {
                return _columns_info.size();
            }

            //-----------------------------------------------------------------
            //!
            //! \brief get record number
            //!
            //! Return the number of records in the spreadsheet.
            //! \return number of records
            //!
            size_t nrecords() const { return _nrec; }

            //-----------------------------------------------------------------
            //!
            //! \brief get iterator to first column
            //!
            //! Return an iterator pointing to the first column in the file.
            //! \return iterator
            //!
            iterator begin() { return _columns_info.begin(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get const first iterator
            //!
            //! Return a const iterator to the first column in the file.
            //! \return const iterator
            //!
            const_iterator begin() const { return _columns_info.begin(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get last iterator
            //!
            //! Return an iterator to the last column in the file.
            //! \return iterator
            //!
            iterator end() { return _columns_info.end(); }

            //-----------------------------------------------------------------
            //!
            //! \brief get const last iterator
            //!
            //! Returns a const iterator to the last column in the file.
            //!
            //! \return const iterator
            //!
            const_iterator end() const { return _columns_info.end(); }

            //-----------------------------------------------------------------
            //! 
            //! \brief checks if a particular column exists
            //!
            //! Returns true if the spreadsheet contains a column of the 
            //! requested name and false otherwise.
            //!
            //! \param name of the column
            //! \return true if column exists, false otherwise
            //!
            bool has_column(const string &name) const;

            //-----------------------------------------------------------------
            //! 
            //! \brief get column index 
            //!
            //! Get the index of a particular column.
            //! \throws key_error if the column does not exist
            //! \param name name of the column
            //! \return numeric index 
            //!
            size_t column_index(const string &name) const;

    };


//end of namespace
}
}

