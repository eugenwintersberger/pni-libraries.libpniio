=============
NeXus support
=============

Most synchrotron radiation facilities have agreed upon a new standard file 
format used by all facilities. Though developing such a common standard 
would cause quite some effort there are several advantages such a 
standard file format would have

* data could be easily exchanged between different laboratories
* authors of analysis software could focus on their real work instead of 
  spending their time in supporting all kinds of file formats.
  
The development of a common file format comprises basically two aspects

* the physical file format - the way how bits and bytes are written to disk 
  and how to read them back (this is also where performance considerations
  have to be taken into account)
* the logical organization of the data an the semantics of keywords.  

At the time of writing these lines, though not without critics, the majority 
of facilities has agreed upon `NeXus`_ file format.

.. _NeXus: http://www.nexusformat.org/


.. toctree::
   :maxdepth: 1
   
   nexus_introduction
   nexus_files
   nexus_groups
   nexus_retrieval