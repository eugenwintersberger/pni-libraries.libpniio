===================
Working with groups
===================

.. attention::

   Read the section on groups of *h5cpp* in order to learn how to access 
   and iterate over the children of HDF5 groups. 

NeXus groups (*NXgroup*) are directly mapped onto HDF5 groups. So we can 
use all the algorithms available from *h5cpp* to work with groups. 
However, *libpniio* provides some utility classes which are related to 
the NeXus standard which would make working with groups in a NeXus context 
easier. 

Creating base classes
=====================

The basic elements of a NeXus tree are base classes. Technically, a base
class is an HDF5 groups with a ``NX_class`` attribute attached to it 
 determining the particular base class the group represents. So creating 
 a base class group with *h5cpp* a three step process would have to be 
 taken
 
1. check if the new name for the group complies to the NeXus naming rules
2. create the new group
3. create a string attribute attached to this group storing the name of the 
   particular base class the group should represent. 
   
To make this easier *libpniio* provides the :cpp:class:`BaseClassFactory` 
factory class with a static :cpp:func:`create` member function which 
carries out all these tasks 

.. code-block:: cpp

   hdf5::node::Group entry = nexus::BaseClassFactory::create(root_group,"run_001","NXentry"); 
                                                             
Creating fields
===============

Similar as for base classes *libpniio* provides a factory class to create 
fields: :cpp:class:`nexus::FieldFactory` in order to create HDF5 datasets. 
:cpp:class:`nexus::FieldFactory` provides two static member functions capable 
of creating chunked and contiguous HDF5 datasets. 

To create a simple dataset use 

.. code-block:: cpp

   hdf5::dataspace::Scalar space; 
   auto type = hdf5::datatype::create<int>();
   
   hdf5::node::Dataset number_of_frames = nexus::FieldFactory::create(root_group,"number_of_frames",type,space);

As you may know, such fields cannot be extended and are thus only useful 
for static data. If you want an extensible dataset a chunked layout should 
be chosen. 

.. code-block:: cpp

   auto type = hdf5::datatype::create<uint16>();
   hdf5::dataspace::Simple space{{0,1024,2048},{hdf5::dataspace::Simple::UNLIMITED,1024,2048}};
   hdf5::Dimensions chunk_shape{1,1024,2048};
   
   hdf5::node::Dataset frames = nexus::FieldFactory::create(root_group,"frames",type,space,chunk_shape);

Searching for groups
====================

One of the major tasks when working with NeXus files is to search for 
particular base classes. Some tasks falling into this cathegory would be 

* search for all detectors used during an experiment
* search for all monochromators that where used during an experiment 

For that purpose *libpniio* provides a search function :cpp:func:`search` 
which makes this job particularly easier. 

The fundamental predicate type to look for base classes is 
:cpp:class:`nexus::IsBaseClass`.

Special base class predicates
-----------------------------

For some of the most common base classes there are specialized versions of 
:cpp:class:`nexus::IsBaseClass`. 

+-------------------------------+---------------------------------------+
| predicate                     | description                           |
+===============================+=======================================+
| :cpp:class:`IsTransformation` | returns *true* for *NXtransformation* |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsEntry`          | returns *true* for *NXentry*          |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsSubentry`       | returns *true* for *NXsubentry*       |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsDetector`       | returns *true* for *NXdetector*       |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsInstrument`     | returns *true* for *NXinstrument*     |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsSample`         | returns *true* for *NXsample*         |
+-------------------------------+---------------------------------------+
| :cpp:class:`IsData`           | returns *true* for *NXdata*           |
+-------------------------------+---------------------------------------+




%%%===========================================================================
\subsection{Other group related member functions}

Like files, groups posses an \cpp{is\_valid()} method which allows checking the 
state of a group. Similar to files, default constructed instances of \nxgroup\
are not valid. 
\begin{cppcode}
h5::nxgroup entry; 

if(!entry.is_valid()) std::cerr<<"The entry group is not valid!"<<std::endl;
\end{cppcode}
The getter methods \cpp{name()} and \cpp{filename()} return the name of the
group and the name of the file the group is stored in respectively.
Finally the \cpp{parent()} function returns the parent group of the a group.
In order to use the \cpp{parent()} member function a bit more extra care is 
used. When using the method in a simple way like 
\begin{cppcode}
h5::nxgroup p = other_group.parent();
\end{cppcode}
everything will be fine. However, when we want to use the return value of 
\cpp{parent()} as a temporary we have to do an explicit conversion to 
\cpp{nxgroup} like this
\begin{cppcode}
std::cout<<h5::nxgroup(entry_group.parent())<<std::endl;
\end{cppcode}
The reason for this is that \cpp{parent()} does not really return an 
instance of \cpp{nxgroup} but rather of \cpp{nxobject}. 
But \nxobject\ can be converted to \nxgroup\ safely. The reason 
for this behavior will be explained in detail in Section~\ref{section:nxobject}.

