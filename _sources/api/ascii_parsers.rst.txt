=============
ASCII parsers
=============

The basic template for all parsers is :cpp:class:`pni::parser`

.. doxygenclass:: pni::parser
   :members:
   
   
Parser specializations
======================

.. doxygenclass:: pni::parser< pni::value >
   :members:
   
.. doxygenclass:: pni::parser< pni::bool_t >
   :members:
   
.. doxygenclass:: pni::parser< pni::slice >
   :members:
   
.. doxygenclass:: pni::parser< pni::string >
   :members: 
   
.. doxygenclass:: pni::parser< std::vector< T > >
   :members:
   
.. doxygenclass:: pni::parser< std::complex< T > >
   :members: 
   