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
// Created on: Nov 4, 2014
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
#pragma once


namespace pni{
namespace io{
namespace nx{
namespace h5{

    //forward declaration
    class selection;

    //!
    //! \ingroup nxh5_classes
    //! \brief selection guard
    //! 
    //! Selections are applied to a field only immediately before writing 
    //! or reading the data. This guard ensures that the seleciton will be 
    //! removed in every case.
    //!
    //! \tparam STYPE dataspace type
    //!
    template<typename STYPE> class selection_guard
    {
        private:
            //! reference to the dataspace to which to apply the selection
            const STYPE &_space_ref;
            //! flag to decide whether or not to apply the selection
            bool         _apply;
        public:
            //----------------------------------------------------------------
            //!
            //! \brief constructor
            //! 
            //! This constructor applies the selection to a particular 
            //! dataspace.
            //!
            //! \param s reference to the selection
            //! \param space reference to the dataspace
            //! \param apply flag to check if the selection should be applied
            //!
            selection_guard(const selection &s,const STYPE &space,bool apply):
                _space_ref(space),
                _apply(apply)
            {
                if(_apply) _space_ref.apply_selection(s);
            }

            //----------------------------------------------------------------
            ~selection_guard()
            {
                if(_apply) _space_ref.reset_selection();
            }
    };


//end of namespace
}
}
}
}
