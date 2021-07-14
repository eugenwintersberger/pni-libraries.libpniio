.. _nexus-api-algorithms:

==========
Algorithms
==========

*libpninexus*'s provides an extensive set algorithms related to NeXus. In 
particulare related to searching for particular base classes. 


.. _nexus-api-containers:

Containers
==========

.. doxygenclass:: pni::nexus::GroupList
   :members:
   
.. doxygenclass:: pni::nexus::DatasetList
   :members:
   
.. doxygenclass:: pni::nexus::NodeList
   :members:
   
.. doxygenclass:: pni::nexus::AttributeList
   :members: 

.. _nexus-api-predicates:

Predicates
==========

.. doxygenclass:: pni::nexus::NodePredicate
   :members:
   
.. doxygenclass:: pni::nexus::IsBaseClass
   :members:
   
.. doxygenclass:: pni::nexus::IsData
   :members:
   
.. doxygenclass:: pni::nexus::IsDetector
   :members:
   
.. doxygenclass:: pni::nexus::IsEntry
   :members:
   
.. doxygenclass:: pni::nexus::IsInstrument
   :members:
   
.. doxygenclass:: pni::nexus::IsSample
   :members:
   
.. doxygenclass:: pni::nexus::IsSubentry
   :members:
   
.. doxygenclass:: pni::nexus::IsTransformation
   :members:
   
.. doxygenclass:: pni::nexus::IsValidNeXusName
   :members:
   
.. _nexus-api-searching:
   
Searching
=========

There is a single search function which, in connection with the above 
predicates can be used to retrieve any node from a NeXus tree.

.. doxygenfunction:: pni::nexus::search

Utilities
=========

.. doxygenfunction:: pni::nexus::get_type_id(const hdf5::attribute::Attribute &)

.. doxygenfunction:: pni::nexus::get_type_id(const hdf5::node::Dataset &)

.. doxygenfunction:: pni::nexus::get_dimensions(const hdf5::attribute::Attribute &)

.. doxygenfunction:: pni::nexus::get_dimensions(const hdf5::node::Dataset &)

