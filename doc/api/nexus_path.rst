
.. _nexus-api-path: 

==========================
Path classes and functions
==========================

.. _nexus-api-path-class:

The :cpp:class:`pni::nexus::Path` class
===========================================

.. doxygenclass:: pni::nexus::Path
   :members:
   
.. _nexus-api-pathobject:

Related functions
-----------------

Inquery functions
~~~~~~~~~~~~~~~~~

.. doxygenfunction:: pni::nexus::has_file_section

.. doxygenfunction:: pni::nexus::has_attribute_section

.. doxygenfunction:: pni::nexus::is_absolute

.. doxygenfunction:: pni::nexus::is_unique


Modification functions
~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: pni::nexus::split_path

.. doxygenfunction:: pni::nexus::split_last

.. doxygenfunction:: pni::nexus::join

.. doxygenfunction:: pni::nexus::make_relative

Comparison
~~~~~~~~~~

.. doxygenfunction:: pni::nexus::operator==(const Path&,const Path&)

.. doxygenfunction:: pni::nexus::match(const Path&,const Path&)

NeXus path objects
==================

:cpp:class:`pni::nexus::PathObject`
-----------------------------------

.. doxygenclass:: pni::nexus::PathObject
   :members:
   
:cpp:class:`pni::nexus::PathObjectList`
---------------------------------------
   
.. doxygenclass:: pni::nexus::PathObjectList
   :members:
   
Related functions
-----------------

.. doxygenfunction:: pni::nexus::is_dataset

.. doxygenfunction:: pni::nexus::is_group

.. doxygenfunction:: pni::nexus::is_attribute

Searching with Paths
====================

.. doxygenfunction:: pni::nexus::get_path(const hdf5::attribute::Attribute&)

.. doxygenfunction:: pni::nexus::get_path(const hdf5::node::Node&)

.. doxygenfunction:: pni::nexus::get_objects(const hdf5::node::Group &, const Path &)

.. doxygenfunction:: pni::nexus::get_objects(const hdf5::node::Group &, const std::string &)

.. doxygenfunction:: pni::nexus::get_objects(const hdf5::node::Group &, const char *)


