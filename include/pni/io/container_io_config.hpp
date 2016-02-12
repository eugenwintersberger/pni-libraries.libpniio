//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Apr 28, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include "windows.hpp"

namespace pni{
namespace io{
    
    //!
    //! \ingroup ascii_io
    //! \brief container IO configuration
    //!
    //! This type stores the parameters required to read and write container
    //! data. 
    //! 
    //! * the start symbol (typically an opening bracket `[`)
    //! * the stop symbol (typically a closing praket `]`)
    //! * and the seperator (can be a whitespace, comma, etc)
    //! 
    //! Instances of this type are used for instance by the formatter<T>
    //! template when used with container types. Instances of this class 
    //! are only configuratble during construction. After its construction
    //! only read only access to its members is possible.
    //! 
    //! The usage is rather simple. Configuration is done vai the constructor:
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! //use a semicolon as a seperator for the container elements
    //! container_io_config config_1(';');
    //!
    //! //use { and } to embrace the container elements
    //! container_io_config config_2('{','}');
    //!
    //! //use { and } to embrace the container elements and a colon as a
    //! //seperator
    //! container_io_config config_3('{','}',':');
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //!
    //! Once an instance of `container_io_config` is created its elements 
    //! can be accessed 
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
    //! config_1.separator();
    //! config_1.start_symbol();
    //! config_1.stop_symbol();
    //! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //!
    class PNIIO_EXPORT container_io_config
    {
        private:
            //! start symbol
            char _start;
            //! stop symbol
            char _stop;
            //! seperator symbol
            char _sep;
        public:
            //! 
            //! \brief default constructor
            //! 
            //! By default the start, and stop symbol are empty and the 
            //! seperator symbol is a single blank.
            //! 
            container_io_config();
            
            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! This destructor allows the determine the seperator symbol. 
            //! The start and stop symbol remain empty. 
            //!
            //! \param seperator the symbol which should be used to seperate 
            //!                  the container elements
            //!
            container_io_config(char seperator);
            
            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //!
            //! A constructor where the user can set the start and stop symbol.
            //! The seperator symbol remains a single blank.
            //!
            //! \param start symbol initiating the sequence
            //! \param stop  symbol terminating the sequence 
            //!
            container_io_config(char start,char stop);
            
            //-----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! Constructor where all aspects of container IO can be 
            //! determined by the user.
            //!
            //! \param start symbol initiating the sequence
            //! \param stop  symbol terminating the sequence
            //! \param seperator the element seperator symbol 
            //! 
            container_io_config(char start,char stop,char seperator);
            
            //-----------------------------------------------------------------
            //! 
            //! \brief get separator symbol
            //! \return the separator symbol of the current configuration 
            //!         instance 
            //! 
            char separator() const;
            
            //-----------------------------------------------------------------
            //!
            //! \brief get start symbol
            //! \return the start symbol of the current configuration instance
            //! 
            char start_symbol() const;
            
            //-----------------------------------------------------------------
            //!
            //! \brief get stop symbol
            //! \return the stop symbol of the current configuration instance
            //!
            char stop_symbol() const;            
    };
 
//end of namespace 
}
}

