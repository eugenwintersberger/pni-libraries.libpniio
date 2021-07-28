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

.. doxygenfunction:: pni::operator==(const mdarray<STORAGE,IMAP,IPA>&, const mdarray<STORAGE, IMAP, IPA>&)

.. doxygenfunction:: pni::operator!=(const mdarray<STORAGE,IMAP,IPA>&, const mdarray<STORAGE, IMAP, IPA>&)

.. doxygenfunction:: pni::operator>>(std::istream&, mdarray<STORAGE, IMAP, IPA>&)

.. doxygenfunction:: pni::operator<<(std::ostream&, const mdarray<STORAGE, IMAP, IPA>&)

:cpp:class:`array_view`
=======================

.. doxygenclass:: pni::array_view
   :members:

Operators
---------

.. doxygenfunction:: pni::operator==(const array_view<ATYPE>&, const array_view<ATYPE>&)

.. doxygenfunction:: pni::operator!=(const array_view<ATYPE>&, const array_view<ATYPE>&)

.. doxygenfunction:: pni::operator>>(std::istream&, array_view<ATYPE>&)

.. doxygenfunction:: pni::operator<<(std::ostream&, const array_view<ATYPE>&)


:cpp:class:`scalar`
===================

.. doxygenclass:: pni::scalar
   :members:
   
Operators
---------

.. doxygenfunction:: pni::operator==(const scalar<T>&, const scalar<T>&)

.. doxygenfunction:: pni::operator!=(const scalar<T>&, const scalar<T>&)

.. doxygenfunction:: pni::operator<<(std::ostream&, const scalar<T>&)

.. doxygenfunction:: pni::operator>>(std::istream&, scalar<T>&)
   
:cpp:class:`slice`
==================

.. doxygenclass:: pni::slice
   :members:
   
Functions
---------

.. doxygenfunction:: pni::size(const slice&)

.. doxygenfunction:: pni::span(const slice&)
