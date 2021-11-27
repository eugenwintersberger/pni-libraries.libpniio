
.. _nexus-api-path: 

==========================
Path classes and functions
==========================

.. _nexus-api-path-class:

The :cpp:class:`pni::io::nexus::Path` class
===========================================

.. doxygenclass:: pni::io::nexus::Path
   :members:
   
.. _nexus-api-pathobject:

Related functions
-----------------

Inquery functions
~~~~~~~~~~~~~~~~~

.. doxygenfunction:: pni::io::nexus::has_file_section

.. doxygenfunction:: pni::io::nexus::has_attribute_section

.. doxygenfunction:: pni::io::nexus::is_absolute

.. doxygenfunction:: pni::io::nexus::is_unique


Modification functions
~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: pni::io::nexus::split_path

.. doxygenfunction:: pni::io::nexus::split_last

.. doxygenfunction:: pni::io::nexus::join

.. doxygenfunction:: pni::io::nexus::make_relative

Comparison
~~~~~~~~~~

.. doxygenfunction:: pni::io::nexus::operator==(const Path &lhs,const Path &rhs)

.. doxygenfunction:: pni::io::nexus::match(const Path &, const Path &)

NeXus path objects
==================

:cpp:class:`pni::io::nexus::PathObject`
---------------------------------------

.. doxygenclass:: pni::io::nexus::PathObject
   :members:
   
:cpp:class:`pni::io::nexus::nexus::PathObjectList`
--------------------------------------------------
   
.. doxygenclass:: pni::io::nexus::PathObjectList
   :members:
   
Related functions
-----------------

.. doxygenfunction:: pni::io::nexus::is_dataset

.. doxygenfunction:: pni::io::nexus::is_group

.. doxygenfunction:: pni::io::nexus::is_attribute

Searching with Paths
====================

.. doxygenfunction:: pni::io::nexus::get_path(const hdf5::attribute::Attribute &)

.. doxygenfunction:: pni::io::nexus::get_path(const hdf5::node::Node &)

.. doxygenfunction:: pni::io::nexus::get_objects


