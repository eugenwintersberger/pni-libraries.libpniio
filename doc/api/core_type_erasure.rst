=============
Type erasures
=============

:cpp:class:`pni::value`
============================

.. doxygenclass:: pni::value
   :members:
   
Functions
---------

.. doxygenfunction:: pni::make_value(type_id_t)

.. doxygenfunction:: pni::type_id(const value&)


:cpp:class:`pni::value_ref`
=================================

.. doxygenclass:: pni::value_ref
   :members:
   
Functions
---------

.. doxygenfunction:: pni::to_value(const value_ref&)

:cpp:class:`pni::array`
=============================

.. doxygenclass:: pni::array
   :members:
   
Functions
---------

.. doxygenfunction:: pni::make_array(const ShapeT&)

.. doxygenfunction:: pni::make_array(type_id_t, const ContainerT&)

.. doxygenfunction:: pni::type_id(const array&)
