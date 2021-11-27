==============================
Data types and type management
==============================


:cpp:enum:`pni::type_id_t`
================================

.. doxygenenum:: pni::type_id_t

Operators
---------

.. doxygenfunction:: operator<<(std::ostream&,const type_id_t&)

Predicates
----------

.. doxygenfunction:: is_numeric(type_id_t)

.. doxygenfunction:: is_integer(type_id_t)

.. doxygenfunction:: is_complex(type_id_t)

.. doxygenfunction:: is_float(type_id_t)

.. doxygenfunction:: is_checked_convertible(type_id_t,type_id_t)

.. doxygenfunction:: is_unchecked_convertible(type_id_t,type_id_t)

.. doxygenfunction:: is_convertible(type_id_t,type_id_t)


Utility functions
-----------------

.. doxygenfunction:: type_id_from_str(const string&)

.. doxygenfunction:: str_from_type_id(type_id_t)

.. doxygenfunction:: type_id(const T&)
   

:cpp:enum:`pni::type_class_t`
===================================

.. doxygenenum:: pni::type_class_t


:cpp:class:`pni::bool_t`
=============================

.. doxygenclass:: pni::bool_t
   :members:
   
   
:cpp:class:`pni::none`
============================

.. doxygenstruct:: pni::none
   :members:
   
Operators
---------

.. doxygenfunction:: operator<<(std::ostream&,const none&)

.. doxygenfunction:: operator>>(std::istream&,none&)

.. doxygenfunction:: operator==(const none&,const none&)

.. doxygenfunction:: operator!=(const none&,const none&)
   
   
:cpp:class:`pni::binary_t`
================================

.. doxygenclass:: pni::binary_t
   :members:
   
.. doxygenfunction:: pni::operator<<(std::ostream&, const binary_t<NTYPE>&)



