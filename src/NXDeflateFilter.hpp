/*
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
 * Definition of the NXDeflateFilter class.
 *
 * Created on: Feb 16, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __NXDEFLATEFILTER_HPP__
#define __NXDEFLATEFILTER_HPP__

#include "NXFilter.hpp"

namespace pni{
    namespace nx{
            //! \ingroup util_classes
            //! \brief Nexus deflate filter

            //! This class provides an implementation of the simple deflate
            //! filter as it is implemented in zlib. 
            template<typename Imp> class NXDeflateFilter:public NXFilter<Imp>
            {
                public:
                    //================constructors and destructor==============
                    //! default constructor
                    explicit NXDeflateFilter():NXFilter<Imp>()
                    {
                    }

                    //---------------------------------------------------------
                    //! copy constructor
                    NXDeflateFilter(const NXDeflateFilter<Imp> &f)
                        :NXFilter<Imp>(f)
                    {
                    }

                    //---------------------------------------------------------
                    //! move constructor
                    NXDeflateFilter(NXDeflateFilter<Imp> &&f)
                        :NXFilter<Imp>(std::move(f))
                    {
                    }

                    //---------------------------------------------------------
                    //! standard constructor
                    NXDeflateFilter(UInt32 r,bool s)
                        :NXFilter<Imp>(Imp(r,s))
                    {
                    }

                    //---------------------------------------------------------
                    //! destructor
                    ~NXDeflateFilter()
                    {
                    }

                    //=================assignment operators====================
                    //! copy assignment operator
                    NXDeflateFilter<Imp> &
                        operator=(const NXDeflateFilter<Imp> &f)
                    {
                        if(this != &f) NXFilter<Imp>::operator=(f);
                        return *this;
                    }

                    //----------------------------------------------------------
                    //! move assignment operator
                    NXDeflateFilter<Imp> &operator=(NXDeflateFilter<Imp> &&f)
                    {
                        if(this != &f) NXFilter<Imp>::operator=(std::move(f));
                        return *this;
                    }



                    //========filter attribute access methods===================
                    //! set compression rate
                    void compression_rate(UInt32 r)
                    {
                        this->imp().compression_rate(r);
                    }

                    //! get compression rate
                    UInt32 compression_rate() const
                    {
                        return this->imp().compression_rate();
                    }

                    //! set shuffle 
                    void shuffle(bool s)
                    {
                        this->imp().shuffle(s);
                    }

                    //! get shuffle flag
                    bool shuffle() const
                    {
                        return this->imp().shuffle();
                    }

            };




    //end of namespace
    }
}




#endif
