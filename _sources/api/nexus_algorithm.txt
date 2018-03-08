.. _nexus-api-algorithms:

==========
Algorithms
==========

*libpniio*'s provides an extensive set algorithms related to NeXus. In 
particulare related to searching for particular base classes. 


.. _nexus-api-containers:

Containers
==========

.. doxygenclass:: pni::io::nexus::GroupList
   :members:
   
.. doxygenclass:: pni::io::nexus::DatasetList
   :members:
   
.. doxygenclass:: pni::io::nexus::NodeList
   :members:
   
.. doxygenclass:: pni::io::nexus::AttributeList
   :members: 

.. _nexus-api-predicates:

Predicates
==========

.. doxygenclass:: pni::io::nexus::NodePredicate
   :members:
   
.. doxygenclass:: pni::io::nexus::IsBaseClass
   :members:
   
.. doxygenclass:: pni::io::nexus::IsData
   :members:
   
.. doxygenclass:: pni::io::nexus::IsDetector
   :members:
   
.. doxygenclass:: pni::io::nexus::IsEntry
   :members:
   
.. doxygenclass:: pni::io::nexus::IsInstrument
   :members:
   
.. doxygenclass:: pni::io::nexus::IsSample
   :members:
   
.. doxygenclass:: pni::io::nexus::IsSubentry
   :members:
   
.. doxygenclass:: pni::io::nexus::IsTransformation
   :members:
   
.. doxygenclass:: pni::io::nexus::IsValidNeXusName
   :members:
   
.. _nexus-api-searching:
   
Searching
=========

There is a single search function which, in connection with the above 
predicates can be used to retrieve any node from a NeXus tree.

.. doxygenfunction:: pni::io::nexus::search

Utilities
=========

.. doxygenfunction:: pni::io::nexus::get_type_id(const hdf5::attribute::Attribute &)

.. doxygenfunction:: pni::io::nexus::get_type_id(const hdf5::node::Dataset &)

.. doxygenfunction:: pni::io::nexus::get_dimensions(const hdf5::attribute::Attribute &)

.. doxygenfunction:: pni::io::nexus::get_dimensions(const hdf5::node::Dataset &)

