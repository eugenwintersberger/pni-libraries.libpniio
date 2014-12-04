//
// (c) Copyright 2014 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
// Created on: Dec 4, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/core/types.hpp>
#include "../../parsers/array_parser.hpp"

#include <boost/algorithm/string/trim.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include "default.hpp"

namespace pni{
namespace io{
namespace nx{
namespace xml{

    using namespace pni::core;

    //!
    //! \ingroup xml_classes
    //! \brief XML data decoder
    //! 
    //! This is the decoder class used to parse the data stored in an XML 
    //! tag or attribute and return it as an instance of the requested type
    //! This default implementation can be used for scalar numeric data. 
    //! 
    //! \tparam T requested numeric type 
    //!
    template<typename T> class decoder
    {
        public:
            //!
            //! \brief read an XML attribute from a node
            //!
            //! Reads an attribute from an XML node and returns it as a value of
            //! type T.  If the attribute string cannot be converted to T or the
            //! node does not posses this attribute an exception will be thrown. 
            //! 
            //! \throws parser_error in case of errors
            //! \throws range_error if the attributes value does not fit in the 
            //! range of T 
            //! 
            //! \param n node instancen
            //! \param a name of the attribute
            //! \return attribute value as instance of T
            //!
            T decode(const string &data) const;
    };

    //------------------------------------------------------------------------
    // implementation of the default decode function
    //------------------------------------------------------------------------
    template<typename T> T decoder<T>::decode(const string &data) const
    {

        typedef typename mpl::at<max_type_map,T>::type safe_type;
        typedef boost::numeric::converter<T,safe_type> safe_to_T;

        string input_string(data);
        boost::algorithm::trim(input_string);

        if(std::is_unsigned<T>::value && input_string[0]=='-')
            throw range_error(EXCEPTION_RECORD,
                    "Try to parse a negative value to an unsigned type!");

        T value;
        try
        {
            safe_type buffer;
            std::stringstream ss(data);
            ss>>buffer;
            value = safe_to_T::convert(buffer);
        }
        catch(boost::numeric::positive_overflow &error)
        {
            throw pni::core::range_error(EXCEPTION_RECORD,
                    "Attribute value to large for requested type!");
        }
        catch(boost::numeric::negative_overflow &error)
        {
            throw pni::core::range_error(EXCEPTION_RECORD,
                    "Attribute value to small for requested type!");
        }
        catch(...)
        {
            throw pni::io::parser_error(EXCEPTION_RECORD,
                    "Unknown error during parsing !");
        }

        return value;
    }

    typedef decoder<size_t> size_t_decoder_type;


    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief specialized decoder for string data
    //!
    template<> class decoder<string>
    {
        public:
            //!
            //! \brief get XML data as string
            //!
            //! \throws parser_error in case of errors
            //!
            //! \param data the input data
            //! \return stored data as a string
            //!
            string decode(const string &data) const;
    };
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief specialized decoder for bool data
    //! 
    //! A specialization of the decoder template for bool values.
    //! Boolean values can be encoded as "1"/"0", "true/false", or 
    //! "True/False". 
    template<> class decoder<bool>
    {
        public:
            //!
            //! \brief decode a bool value
            //!
            //! \throws parser_error in case of errors
            //! \throws value_error if the attribute value is not a valid
            //! bool represenation
            //! 
            //! \param data the input data as string
            //! \return return decoded bool value
            //!
            bool decode(const string &data) const;
    };
    
    //------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief specialized decoder for bool_t data
    //! 
    //! A specialization of the decoder template for bool values.
    //! Boolean values can be encoded as "1"/"0", "true/false", or 
    //! "True/False". 
    template<> class decoder<bool_t>
    {
        public:
            //!
            //! \brief decode bool_t values
            //!
            //! \throws parser_error in case of errors
            //! \throws value_error if the attribute value is not a valid
            //! bool represenation
            //! 
            //! \param data input data as string
            //! \return return the decoded bool_t value
            //!
            bool_t decode(const string &data) const;
    };


    //-------------------------------------------------------------------------
    //!
    //! \ingroup xml_classes
    //! \brief decoder for array data
    //!
    //! Provide several static methods to read array data from an attribute. 
    //!
    template<> class decoder<array>
    {
        private:
            //! iterator type for parsing array data
            typedef string::const_iterator iterator_t;
            //! parser type 
            typedef pni::io::array_parser<iterator_t> array_parser_t;

            array_parser_t _parser;

        public:
            explicit decoder(char sep);
            explicit decoder(char start,char stop,char sep);
            
            array decode(const string &data) const;
    };


//end of namespace
}
}
}
}
