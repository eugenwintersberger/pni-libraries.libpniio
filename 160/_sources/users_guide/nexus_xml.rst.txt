===========
XML support
===========

NeXus files can grow quite complex it would be rather tedious to express
the structure of such a file entirely in code. 
*libpninexus* provides a way to create NeXus structures from XML. Like HDF5, 
XML structures data in a tree like hierarchy, making it the perfekt ASCII 
representation for a NeXus file. 

Generating objects
==================

The XML content can come from two sources 

* a file 
* or from a string. 

Using the XML interface is rather simple. Consider that we have the structure
of the file expressed as XML and stored in a file :file:`file_structure.xml`
using this is simply  

.. code-block:: cpp

   hdf5::node::Group root_group = file.root(); 
   
   nexus::xml::create_from_file(root_group,"file_structure.xml");
   
Alternatively you could use XML content from a string 

.. code-block:: cpp

   hdf5::node::Group instrument = hdf5::node::get_node(root_group,"/entry/instrument");
   
   std::string detector_struct = create_detector_structure();
   nexus::xml::create_from_string(instrument,detector_struct); 

As can be seen from this example the XML data must not contain the entire 
file structure. Instead it would be possible to provide separate XML files 
with different components of the file. 
Consider here for instance the following files 

+-------------------------+-----------------------------+
| file                    | content description         |
+=========================+=============================+
| :file:`basic_file.xml`  | the basic file structure    |
+-------------------------+-----------------------------+
| :file:`detector_1d.xml` | structure for a 1d detector |
+-------------------------+-----------------------------+
| :file:`detector_2d.xml` | structure for a 2d detector |
+-------------------------+-----------------------------+
   
Code which uses this setup could look like this

.. code-block:: cpp

   hdf5::file::File file = ... ;
   hdf5::node::Group root_group = file.root(); 
   
   nexus::xml::create_from_file(root_group,"basic_file.xml");
   hdf5::node::Group instrument = hdf5::node::get_node(root_group,"/entry/instrument");
   
   switch(detector_setup)
   {
      case DetectorType::LINEAR:
         nexus::xml::create_from_file(instrument,"detector_1d.xml");
         break;
      case DetectorType::AREA:
         nexus::xml::create_from_file(instrument,"detector_2d.xml");
   }
   


It should be mentioned that currently *libpninexus* does not use a validating 
parser which makes error detection rather difficult. 


NeXus XML tags
==============

.. attention:: 

   Currently the entire content is described in the NeXus serialization 
   documentation. Either need a link here or we have to provide a 
   copy in this documentation. 

