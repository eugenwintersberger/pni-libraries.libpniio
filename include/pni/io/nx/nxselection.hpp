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
// Created on: Nov 14, 2012
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once

#include <vector>
#include <pni/core/arrays.hpp>
#include <pni/core/type_erasures.hpp>


namespace pni{
namespace io{
namespace nx{

    using namespace pni::core;
    //need this here to avoid name collisions with tango headers.
    using pni::core::array;
    using pni::core::string;
    using pni::core::exception;

    /*!
    \ingroup nexus_lowlevel
    \brief selection template

    This template implements a selection applied to a particular field. It acts
    as a kind of guard object holding a reference to the field onto which the
    selection should be applied. It can be also considered as a kind of delegate
    which provides virtually the same interface as nxfield. However, whenever a
    method is called the selection is applied before the original field method
    is called. 
    */
    template<typename FTYPE> class nxselection
    {
        private:
            //! the current selection as vector of slices
            std::vector<slice>  _selection;

            FTYPE &_field; //!< reference to the original field

            /*!
            \brief applies the current selection 

            Applies the current selection to the data field. This method is
            called ususally everytime before a particular request to the wrapped
            field is made.
            */
            void apply_selection() const
            {
                _field.apply_selection(_selection);
            }

            //-----------------------------------------------------------------
            /*!
            \brief reset selection

            Remove the selection from the wrapped field. This is typically
            called after the request to the wrapped field.
            */
            void reset_selection() const
            {
                _field.reset_selection();
            }
        public:
            //=================public types====================================
            //! container type holding the selection
            typedef std::vector<slice> selection_type;
            //=============constructors and destructor=========================
            //! default constructor
            nxselection(selection_type &&sel,FTYPE &field):
                _selection(std::move(sel)),
                _field(field)
            {}

            //! default constructor
            nxselection(const selection_type &sel,FTYPE &field):
                _selection(sel),
                _field(field)
            {}
            //-----------------------------------------------------------------
            //! copy constructor
            nxselection(const nxselection<FTYPE> &sel):
                _selection(sel._selection),
                _field(sel._field)
            {}

            //-----------------------------------------------------------------
            //! destructor
            ~nxselection()  
            {
                //need to remove all eventual selections in case that something 
                //goes wrong and the selection gets destroyed
                reset_selection();
            }

            //=================assignment operators============================
            //! copy assignemnt operator
            nxselection<FTYPE> &operator=(const nxselection<FTYPE> &sel)
            {
                if(this == &sel) return *this;
                _selection = sel._selection;
                _field = sel._field;
                return *this;
            }

            //====================public member functions======================
            //! get size
            size_t size() const
            {   
                this->apply_selection();
                size_t s = this->_field.size();
                //release selection
                this->reset_selection();

                return s;
            }

            //-----------------------------------------------------------------
            //! get shape
            template<typename CTYPE> CTYPE shape() const
            {
                this->apply_selection();
                auto s = this->_field.shape<CTYPE>();
                this->reset_selection();
                return s;
            }

            //-----------------------------------------------------------------
            //! get type id
            type_id_t type_id() const
            {
                return _field.type_id();
            }

            //-----------------------------------------------------------------
            //! get the rank
            size_t rank() const
            {
                this->apply_selection();
                size_t r = this->_field.rank();
                this->reset_selection();
                return r;
            }

            //-----------------------------------------------------------------
            //! read data
            template<typename DTYPE> void read(DTYPE &data) const
            {
                this->apply_selection();
                this->_field.read(data);
                this->reset_selection();
            }
           
            //-----------------------------------------------------------------
            //! read data to pointer
            template<typename T> void read(T *data) const
            {
                this->apply_selection();
                this->_field.read(data);
                this->reset_selection();
            }


            //-----------------------------------------------------------------
            //! write data
            template<typename DTYPE> void write(const DTYPE &data) const
            {
                static_assert(!std::is_pointer<DTYPE>::value,"no pointer");
                this->apply_selection();
                this->_field.write(data);
                this->reset_selection();
            }

            //----------------------------------------------------------------
            //! write data from pointer
            template<typename T> void write(const T *data) const
            {
                this->apply_selection();
                this->_field.write(data);
                this->reset_selection();
            }

    };


//end of namespace
}
}
}
