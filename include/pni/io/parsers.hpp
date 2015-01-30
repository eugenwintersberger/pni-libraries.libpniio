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
// Created on: Jan 21, 2015
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once


//----------------------------------------------------------------------------
// header files providing the rules for parsing objects
//----------------------------------------------------------------------------
#include "parsers/spirit_rules.hpp"
#include "parsers/complex_rule.hpp"
#include "parsers/delimiter_rule.hpp"
#include "parsers/get_rule_type.hpp"
#include "parsers/sequence_rule.hpp"
#include "parsers/value_rule.hpp"
#include "parsers/slice_rule.hpp"

//----------------------------------------------------------------------------
// header files providing parser classes
//----------------------------------------------------------------------------
#include "parsers/parser.hpp"
#include "parsers/string_parser.hpp"
#include "parsers/vector_parser.hpp"
