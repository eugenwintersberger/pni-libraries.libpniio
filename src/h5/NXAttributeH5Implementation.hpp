/*
 * Declaration of an NXAttribute object
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
 * Created on: Jan 10, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#ifndef __NXATTRIBUTEH5IMPLEMENTATION_HPP__
#define __NXATTRIBUTEH5IMPLEMENTATION_HPP__

class NXAttributeH5Implementation{
    public:
        hid_t _id;

    public:
        //==============constructors and destructors===========================
        NXAttributeH5Implementation();
        NXAttributeH5Implementation(const NXAttributeH5Implementation &);
        NXAttributeH5Implementation(NXAttributeH5Implementation &&);
        virtual ~NXAttributeH5Implementation();


        //==============assignment operators====================================
        NXAttributeH5Implementation &
            operator=(const NXAttributeH5Implementation&);
        NXAttributeH5Implementation &operator=(NXAttributeH5Implementation &&);


        //=================properties for object inquery========================
        String name() const;
        void   name(const String);
        const Shape &shape() const;








};


#endif
