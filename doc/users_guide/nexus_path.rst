===========================================
NeXus path's: :cpp:class:`pni::nexus::Path`
===========================================

Until now we discussed only the basic properties of a NeXus path. 
As these paths are rather powerful tools this chapter is entirely dedicated 
to such paths.   

The structure of a Nexus path
=============================

In comparison to a plain HDF5 path the NeXus path as provided by *libpniio* 
has to additional features

* it includes the name of the file and thus could be used by command line 
  programs to entirely determine the location of an object
* it is able to address attributes (:cpp:class:`hdf5::Path` can only address
  node objects within a file). 
  
To describe the anatomy of a NeXus path in *libpniio* we consider the following
example 

   ``/home/user/data/experiment.nxs://run_001:NXentry/:NXinstrument/:NXdetector/data@units``

where we can identify all three sections comprising a *libpniio* NeXus path

* *file section* - ``/home/user/data/experiment.nxs:/``
* *node section* - ``/run_001:NXentry/:NXinstrument/:NXdetector/data``
* *attribute section* - ``units``

In more detail these three sections describe 

+---------------------+-----------------------------------------------------+
| Section             | Description                                         |
+=====================+=====================================================+
| *file section*      | which references the NeXus-file on the file system. |
|                     | It must thus be a valid file system path on the     |
|                     | operating system platform in use.                   |
+---------------------+-----------------------------------------------------+
| *node section*      | describing the location of an node within the file  |
+---------------------+-----------------------------------------------------+
| *attribute section* | referencing an attribute attached to the object     |
|                     | pointed to by the residual path. The attribute is   |
|                     | identified by its name.                             |
+---------------------+-----------------------------------------------------+

The *file-* and the *node-section* are separated by ``:/`` and the *node-* and 
the *attribute-section* are separated by a ``@`` symbol.
Each element in the *node-section* of the path consists of two path 

* the nodes link name 
* and an optional base class type 

separated by a semicolon. The base class type part only makes sense if a 
group should be referenced as individual fields (or datasets in HDF5 
terminology) are not associated with a base class type. 
There are three permitted forms how a node element could look like 

+----------------+------------------------------------------------------+-+
| node element   | description                                          | |
+================+======================================================+=+
| ``name:class`` | this would be the full description of a base class   | |
|                | including the name of the link to the group as well  | |
|                | as the base class type it belongs to.                | |
+----------------+------------------------------------------------------+-+
| ``name``       | only the name of the link. Something like this could | |
|                | be used for both: groups and fields.                 | |
+----------------+------------------------------------------------------+-+
| ``:class``     | references a group by the base class type it belongs | |
|                | to.                                                  | |
+----------------+------------------------------------------------------+-+

A path is considered as *absolute* if its *node section* starts at the root
group of the file. This is always  the case if 

* the *file section* of the path is not empty (if we give a file the 
  *node section* has to start at the root node and thus must be absolute)
* or, if no *file section* is given, the *object section* starts with a 
  leading ``/``.

The latter condition is equivalent to the convention used for Unix file system
paths while the former requires some explanation. 


Equality and matching of paths
==============================

Equality
--------

The equality of two NeXus paths is rather trivial: two paths can be considered 
equal if all of their elements are equal. 


Matching
--------

Two paths are considered as *matching* if they are not equal but capable of 
referencing the same object within a single file.  
To illustrate this situation consider the following three paths 

#. *a = /entry/instrument/detector/data*
#. *b = /entry:NXentry/instrument:NXinstrument/detector:NXdetector/data*
#. *c = /:NXentry/:NXinstrument/:NXdetector/data*

each being perfectly well defined NeXus paths referencing the data field in 
a detector group. 
It is obvious for path :cpp:var:`a` and :cpp:var:`b` that they reference the 
same object. The same is true for the paths :cpp:var:`b` and :cpp:var:`c`. 
Surprisingly, :cpp:var:`a` and :cpp:var:`c` do not match. As :cpp:var:`a` does 
not provide any type information for each of its nodes we cannot be sure that 
it references the same object as :cpp:var:`c`. Being more specific: none of 
the groups in :cpp:var:`a` has to be a NeXus group at all. 
We get the rough idea that the property of two path of *matching* each other 
has something to do with the number of elements they have common.

In order to derive a reasonable set of rules determining whether or not two 
paths are matching we start with deriving rules to deciding under which 
conditions the *node*-elements of the *node section* of a path are matching. 

The first rule covers the trivial case of equality 
 
.. note::

    Two node elements *a* and *b* are considered as *matching* if they are 
    equal in the above case: *a=b*. 

For instance, let *a=entry:NXentry* and *b=entry:NXentry* it is obvious that 
they are referencing the same node as they are equal in the above sense.

Furthermore, we can propose a second rule

.. note::

    Two node elements *a* and *b* can be considered *matching* if their class 
    component is equal and only one of them has the name attribute set. 

This would be the case if *a=:NXentry* and *b=entry:NXentry*. This is somehow 
logical if we consider that *a* is just a more general version of *b*. However, 
it is crucial that only one of them has a non empty name attribute. Otherwise 
this rule would violate rule one.

Now as we have derived two rules for matching node elements we can generalize 
a single rule for paths 

.. note::

   Two paths *a* and *b* are considered matching if 
   
   * they are of equal size
   * all of their node elements match
   * and, if available, they reference the same attribute.


The :cpp:class:`pni::io::nexus::Path` type
==========================================

In C++ a NeXus-path is represented by an instance of 
:cpp:class:`pni::io::nexus::Path`. 
:cpp:class:`pni::io::nexus::Path` is an
iterable over the elements of the *object section* of a NeXus-path.  
The optional *file-* and *attribute-section* can be accessed via getter and 
setter methods like this

.. code-block:: cpp

   nexus::Path path = ...;
   path.filename("/data/run/detector.nxs"); //set file section
   std::cout<<path.filename()<<std::endl;   //retrieve file section


and analogously for the *attribute section*

.. code-block:: cpp

   nexus::Path path = ...;
   path.attribute("units");              //set attribute section
   std::cout<<path.units()<<std::endl;   //retrieve attribute section

The elements of the *object section* are stored as instances of 
:cpp:type:`nexus::Path::Element` which is in fact a type alias for a 
:cpp:class:`std::pair` where the first element of the pair stores the
name of the element and the second its class (if available). 
Technically, :cpp:class:`nexus::Path` is a thin wrapper around a list of such
:cpp:class:`nexus::Path::Element` (although not all the list functionality 
is exported). Consult the API documentation for a detailed description of 
:cpp:class:`nexus::Path`'s interface.

Path construction
-----------------

Though the :cpp:class:`nexus::Path` type has a constructor one would 
typically construct a path from a string using the 
:cpp:func:`nexus::Path::from_string` static member method

.. code-block:: cpp

   nexus::Path path = nexus::Path::from_string("/:NXentry/:NXinstrument/pilatus");

:cpp:func:`nexus::Path::from_string` has also a static counterpart method 
:cpp:func:`nexus::Path::to_string` which converts a path instance to its 
string representation.

.. code-block:: cpp

   nexus::Path path = ....;
   std::cout<<nexus::Path::to_string(path)<<std::endl;


Path iteration
--------------

:cpp:class:`nexus::Path` provides an STL compliant iterator interface which 
allows easy iteration over all elements in the *object section* of the path. 
Consider the following example

.. code-block:: cpp

   nexus::Path p = nexus::Path::from_string("/:NXentry/:NXinstrument/pilatus/data");

   for(auto e:p)
      std::cout<<"name: "<<e.first<<"\t type:"<<e.second<<std::endl;

which would yield the output

.. code-block:: text

   name: /       type: NXroot
   name:         type: NXentry
   name:         type: NXinstrument
   name: pilatus type: 
   name: data    type: 

As we can see from the above example: the first member of the
:cpp:class:`nexus::Path::Element` stored in the object section list is the 
name of an object while the second is its type. In the case of a field 
only the first (name) element will be set (a field does not have a 
particular type). 
The number of elements in the *object section* of :cpp:class:`nexus::Path` can 
be obtained via the :cpp:func:`nexus::Path::size` member function (which is 
the same as for any other STL container).

Push and pop on object
----------------------

Elements of the *object section* of the path can be added using the 
:cpp:func:`push_back` and :cpp:func:`push_front` member functions. 

.. code-block:: cpp

   nexus::Path p = nexus::Path::from_string(":NXinstrument");
   std::cout<<p<<std::endl; // output: :NXinstrument

   p.push_back(object_element("","NXdetector"));
   std::cout<<p<<std::endl; // output: :NXinstrument/:NXdetector

   p.push_front(object_element("","NXentry"));
   std::cout<<p<<std::endl; // output: :NXentry/:NXinstrument/:NXdetector

Like other STL containers :cpp:class:`nexus::Path` also provides the 
:cpp:func:`front`, :cpp:func:`back`, :cpp:func:`pop_front`, and 
:cpp:func:`pop_back` member functions which have the standard STL behavior. 

.. code-block:: cpp

   nexus::Path p = nexus::Path::from_string(":NXentry/:NXinstrument/:NXdetector");
   
   //get front and back elements from the object section
   nexus::Path::Element entry = p.front();
   nexus::Path::Element detector = p.back();
   
   std::cout<<p<<std::endl; // output: :NXentry/:NXinstrument/:NXdetector
   
   //remove front and back objects from the object section
   p.pop_front();
   p.pop_back();
   
   std::cout<<p<<std::endl; // output: :NXinstrument

:cpp:class:`pni::io::nexus::Path` and :cpp:class:`hdf5::Path`
-------------------------------------------------------------

In many cases we may want to construct an HDF5 path from a NeXus path an 
vica verse. Now, converting from an HDF5 path to a NeXus path is always 
easy as an HDF5 path is also a valid NeXus path (despite the fact that an 
HDF5 path cannot address attributes and contains no file information). 
For this purpose :cpp:class:`pni::io::nexus::Path` has an implicit 
conversion constructor for an HDF5 path.

.. code-block:: cpp

   hdf5::Path hdf5_path = ...;
   pni::io::nexus::Path nexus_path = hdf5_path; 
   
The other direction is also possible but only under certain conditions. 
Unlike a NeXus path an HDF5 path contains only of link names. So conversion from 
a NeXus path to an HDF5 path is only possible under the following 
restrictions 

* the NeXus path has all the link names set in its *node section* 
* the NeXus path does not reference an attribute (an HDF5 path cannot do that)
* the NeXus path has an empty *file section* - we cannot reference a file 
  with an HDF5 path. 
  
:cpp:class:`pni::io::nexus::Path` has an implicit conversion operator to 
an :cpp:class:`hdf5::Path`. Thus we could use for instance a NeXus path 
in situations where an HDF5 path is expected 

.. code-block:: cpp

   nexus::Path path=nexus::Path::from_string("/entry:NXentry/instrument/detector:NXdetector");
   
   hdf5::node::Group detector = hdf5::node::get_node(root_group,path);


Utility functions
=================

Element utilities
-----------------

There are a couple of utility functions available to work with the elements 
stored in the *object section* of the path.
One important function is the :cpp:func:`object_element` function which 
creates a single element for the *object section* of a path. This is 
particularly useful in connection with the :cpp:func:`push_back` and 
:cpp:func:`push_front` member functions of :cpp:class:`nexus::Path`. 
If for instance one wants to append a detector group to the object section
we could use

.. code-block:: cpp

   nexus::Path p = ...;
   p.push_back(object_element("detector","NXdector"));

:cpp:func:`object_element` takes two arguments: the first is the name of the 
object while the second its type (only relevant for groups). If both are empty 
strings and exception will be thrown.

Furthermore there are some functions for querying the basic properties of an 
element instance. Each of these functions returns a boolean value and takes
an instance of :cpp:type:`nexus::Path::Element` as its only argument.

+-----------------------------+--------------------------------------------+
| utiltiy function            | description                                |
+=============================+============================================+
| :cpp:func:`is_root_element` | returns true if the element references the |
|                             | root group with name ``/`` and type        |
|                             | ``NXroot``                                 |
+-----------------------------+--------------------------------------------+
| :cpp:func:`is_complete`     | return true if the element has a non-empty |
|                             | name and type                              |
+-----------------------------+--------------------------------------------+
| :cpp:func:`has_name`        | return true if the element has a non-empty |
|                             | name                                       |
+-----------------------------+--------------------------------------------+
| :cpp:func:`has_class`       | return true if the element has a non-empty |
|                             | type                                       |
+-----------------------------+--------------------------------------------+



:cpp:class:`pni::io::nexus::Path` utilities
-------------------------------------------

Three inquiry functions exist for :cpp:class:`nexus::Path`. Each of them 
returns a boolean and takes as their single argument a reference to an 
instance of :cpp:class:`nexus::Path`

+-----------------------------------+--------------------------------------+
| utility function                  | description                          |
+===================================+======================================+
| :cpp:func:`is_absolute`           | returns *true* if the path is an     |
|                                   | absolute path                        |
+-----------------------------------+--------------------------------------+
| :cpp:func:`has_file_section`      | returns *true* if the path has a     |
|                                   | non-empty file section               |
+-----------------------------------+--------------------------------------+
| :cpp:func:`has_attribute_section` | returns *true* if the path has a     |
|                                   | non-empty attribute section          |
+-----------------------------------+--------------------------------------+
| :cpp:func:`is_empty               | returns *true* if a path has neither |
|                                   | a *file section*, an                 |
|                                   | *attribute section*, and an          |
|                                   | *object section*. This situation     |
|                                   | would be equivalent to a default     |
|                                   | constructed path object.             |
+-----------------------------------+--------------------------------------+

The :cpp:func:`split_path` function divides an :cpp:class:`nexus::Path` into 
two partial paths at a user defined position. 

.. code-block:: cpp

   std::string s = "test.nxs://:NXentry/:NXinstrument/detector@NX_class";
   nexus::Path p = nexus::Path::from_string(s);
   nexus::Path instrument_path,detector_path;
   split_path(p,3,instrument_path,detector_path);
   
   // output: test.nxs://:NXentry/:NXinstrument
   std::cout<<instrument_path<<std::endl; 
   // output: detector@NX_class
   std::cout<<detector_path<<std::endl;   

The second argument to :cpp:func:`split_path` is the position where to 
perform the split. It is the index of the first element for the second path.
To chop of the *file section* from a path one could use the following code

.. code-block:: cpp

   std::string s = "test.nxs://:NXentry/:NXinstrument/detector@NX_class";
   nexus::Path p = nexus::Path::from_string(s);
   nexus::Path instrument_path,detector_path;
   split_path(p,0,instrument_path,detector_path);
   
   // output: test.nxs
   std::cout<<instrument_path<<std::endl;
   // output: /:NXentry/:NXinstrument/detector@NX_class
   std::cout<<detector_path<<std::endl;   

Two paths can be joined using the :cpp:func:`join` function. 

.. code-block:: cpp

   nexus::Path a = nexus::Path::from_string("file.nxs://:NXentry/:NXinstrument");
   nexus::Path b = nexus::Path::from_string("pilatus300k:NXdetector/data");
   nexus::Path c = join(a,b);
   std::cout<<c<<std::endl;
   
   //would output
   //file.nxs://:NXentry/:NXinstrument/pilatus300k:NXdetector/data"

There are several restrictions to the two path arguments :cpp:var:`a` and 
:cpp:var:`b` passed to the :cpp:func:`join` function

* :cpp:var:`a` must not have an *attribute section*
* :cpp:var:`b` must not have a *file section*
* :cpp:var:`b` must not be an absolute path.

If any of these restrictions are violated :cpp:func:`join` throws
:cpp:type:`value_error`. There are additional special conditions which should be
taken into account and where the above rules do not apply

+--------------------------------------+-------------------------------+
| input state                          | result                        |
+======================================+===============================+
| :cpp:var:`a` empty, :cpp:var:`b` not | return :cpp:var:`b` unchanged |
+--------------------------------------+-------------------------------+
| :cpp:var:`b` empty, :cpp:var:`a` not | return :cpp:var:`a` unchanged |
+--------------------------------------+-------------------------------+
| :cpp:var:`a` and :cpp:var:`b` empty  | return an empty path object   |
+--------------------------------------+-------------------------------+



The grammar of a NeXus path
===========================

Lets first have a look on the grammar of a Nexus path in
EBNF\footnote{EBNF=Extended Backus Naur Form}

.. productionlist:: path
   file_path : {all characters allowed by the plattform to describe a path}
   valid_char  : "_" | "a-z" | "A-Z" | "0-9";
   whitespace  : " " | "\n" | "\r";
   class_seperator  : ":";
   object_seperator : "/";
   nexus_id    : valid_char,{valid_char}; 
   nexus_name  : nexus_id,(class_seperator|group_separtor|whitespace);
   nexus_group : group_seperator,nexus_id,[group_seperator|whitespace];
   object_id   : nexus_name | nexus_name,nexus_group | nexus_group   
   object_path : ["/"],object_id,{"/",object_id};
   nexus_path  : [file_path,"://"],object_path,["@",nexus_attr];


The ``file_path`` is platform dependent which makes it difficult to determine
which characters would be allowed in a path. Thus we leave this open to and
separate the file path from everything else by a ``://`` string terminal.
``nexus_id`` describes a repetition of a set of characters allowed in Nexus
names (for groups, fields, attributes, and classes). It is much more restrictive
as for the filename.
