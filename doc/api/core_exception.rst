==========
Exceptions
==========

:cpp:class:`pni::exception_record`
==================================

.. doxygenclass:: pni::exception_record
   :members:
   
.. doxygenfunction:: operator<<(std::ostream&,const exception_record&)
   
:cpp:class:`pni::exception`
===========================

.. doxygenclass:: pni::exception
   :members:


Exception classes
-----------------

These classes have the same interface as :cpp:class:`pni::exception` but 
denote different failure situations.

.. doxygenclass:: pni::memory_allocation_error
   
.. doxygenclass:: pni::memory_not_allocated_error

.. doxygenclass:: pni::shape_mismatch_error

.. doxygenclass:: pni::size_mismatch_error

.. doxygenclass:: pni::index_error

.. doxygenclass:: pni::key_error

.. doxygenclass:: pni::file_error

.. doxygenclass:: pni::type_error

.. doxygenclass:: pni::value_error

.. doxygenclass:: pni::range_error

.. doxygenclass:: pni::not_implemented_error

.. doxygenclass:: pni::iterator_error

.. doxygenclass:: pni::cli_argument_error

.. doxygenclass:: pni::cli_option_error

.. doxygenclass:: pni::cli_error


Macros
======

.. doxygendefine:: EXCEPTION_RECORD

.. doxygendefine:: EXCEPTION_FORWARD


Utility functions
=================

.. doxygenfunction:: check_equal_size(const ContainerAT&, const ContainerBT&)

.. doxygenfunction:: check_equal_size(const ContainerAT&, const ContainerBT&, const exception_record&)
