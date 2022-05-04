.. _mdarrays:

==========================
Multidimensional array API
==========================

:cpp:class:`mdarray`
====================

.. doxygenclass:: pni::mdarray
   :members:

Operators
---------

.. doxygenfunction:: pni::operator==(const mdarray<StorageT,IndexMapT,InplaceArithmeticT>&, const mdarray<StorageT, IndexMapT, InplaceArithmeticT>&)

.. doxygenfunction:: pni::operator!=(const mdarray<StorageT,IndexMapT,InplaceArithmeticT>&, const mdarray<StorageT, IndexMapT, InplaceArithmeticT>&)

.. doxygenfunction:: pni::operator>>(std::istream&, mdarray<StorageT, IndexMapT, InplaceArithmeticT>&)

.. doxygenfunction:: pni::operator<<(std::ostream&, const mdarray<StorageT, IndexMapT, InplaceArithmeticT>&)

:cpp:class:`array_view`
=======================

.. doxygenclass:: pni::array_view
   :members:

Operators
---------

.. doxygenfunction:: pni::operator==(const array_view<ArrayT>&, const array_view<ArrayT>&)

.. doxygenfunction:: pni::operator!=(const array_view<ArrayT>&, const array_view<ArrayT>&)

.. doxygenfunction:: pni::operator>>(std::istream&, array_view<ArrayT>&)

.. doxygenfunction:: pni::operator<<(std::ostream&, const array_view<ArrayT>&)


:cpp:class:`scalar`
===================

.. doxygenclass:: pni::scalar
   :members:
   
Operators
---------

.. doxygenfunction:: pni::operator==(const scalar<ElementT>&, const scalar<ElementT>&)

.. doxygenfunction:: pni::operator!=(const scalar<ElementT>&, const scalar<ElementT>&)

.. doxygenfunction:: pni::operator<<(std::ostream&, const scalar<ElementT>&)

.. doxygenfunction:: pni::operator>>(std::istream&, scalar<ElementT>&)
   
:cpp:class:`slice`
==================

.. doxygenclass:: pni::slice
   :members:
   
Functions
---------

.. doxygenfunction:: pni::size(const slice&)

.. doxygenfunction:: pni::span(const slice&)
