=========================================
Problems with links in the current design
=========================================

Problems showed up recently
===========================

Several problems when dealing with links shown up recently which are all
closely related to a single problem.

The first issue was reported by Jan Kotanski. This problem concerns chains of
links. In particular when creating a soft-link to a field which is by itself an
external link.




The parent issue
================

.. Figure:: parent_problem.png
   :width: 50%

   Sketch of the parent problem. The target node could be reached via two
   different paths. This makes it virtually impossible to decide what would be 
   the parent object of the target.

The major problem is the fact that it is virtually impossible to obtain a
unique parent for a particular object. The sketch above shows the basic
problematic situation. The target object could be reached via two different
paths. What would be the parent object. The one connected via edge `2` or that 
via `5`. This might be the reason why the HDF5 library does not provide an API
function to retrieve the parent of a particular object as there is no unique
parent.

Another problem is how we retrieve the parent of a particular object in
``libpniio``. 

* get the ID of the file an object belongs to
* get the path of the object and extract the path of the parent from it
* use the file ID and the parent path to retrieve the parent

In particular the second step causes troubles. The API function to retrieve an
objects path is ``H5Iget_name`` which typically tries to return the path used
to open the object. If the object is accessed via a symbolic link one would get
the path described by the symbolic link and not the path to the hard link. 

One is maybe tempted to consider hard-links as unique for every object. 
Unfortunately this is not true: several hard-links can address the same object
within a file.


Possible solutions
==================
