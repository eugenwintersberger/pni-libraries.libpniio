====================================
A general introduction to *libpniio*
====================================


*libpniio* is the IO library within the PNI library stack. More precisely it is
responsible for file IO. Although several legacy formats are supported the
library mainly deals with Nexus files providing functions and objects to deal
with these kind of files. 

Chapter :ref:`Legacy Formats <legacy_formats>` gives an overview over the supported legacy
formats and how to access data. It is important to note that the legacy support
is mainly for reading data. The reason for this is that newly created data
should be written as Nexus files. 

Chapter :ref:`Using the library <nexus_quickstart>` gives a quick overview over Nexus and
provides a kind of quick start tutorial how to use the library. 
In the ongoing chapters present more detailed information about how to work with
Nexus files with \libpniio.



