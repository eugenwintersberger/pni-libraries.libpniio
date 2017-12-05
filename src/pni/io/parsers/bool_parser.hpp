//
// (c) Copyright 2017 DESY
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
// Created on: Jun 8, 2017
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <pni/io/parsers/parser.hpp>

namespace pni{
namespace io{

    template<>
    class PNIIO_EXPORT parser<pni::core::bool_t>
    {
    private:
        boost::regex _true_regex;
        boost::regex _false_regex;
    public:
        using result_type = bool;

        explicit parser();

        explicit parser(const pni::core::string &true_regex,
                        const pni::core::string &false_regex);

        result_type operator()(const pni::core::string &input) const;

    };

}
}
