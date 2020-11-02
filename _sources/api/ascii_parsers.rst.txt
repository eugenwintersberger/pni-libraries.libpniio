=============
ASCII parsers
=============

The basic template for all parsers is :cpp:class:`pni::io::parser`

.. doxygenclass:: pni::io::parser
   :members:
   
   
Parser specializations
======================

.. doxygenclass:: pni::io::parser< pni::core::value >
   :members:
   
.. doxygenclass:: pni::io::parser< pni::core::bool_t >
   :members:
   
.. doxygenclass:: pni::io::parser< pni::core::slice >
   :members:
   
.. doxygenclass:: pni::io::parser< pni::core::string >
   :members: 
   
.. doxygenclass:: pni::io::parser< std::vector< T > >
   :members:
   
.. doxygenclass:: pni::io::parser< std::complex< T > >
   :members: 
   