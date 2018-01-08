/*! 
\ingroup nexus_io
\defgroup nxh5_classes HDF5 implementation classes
    HDF5 implementation of the Nexus file format. This module describes the 
    implementation classes which are used to instantiate the low level 
    class templates.

*/

/*! 
\ingroup nxh5_classes
\defgroup nxh5_error_classes HDF5 implementation error classes

Exception classes related to the HDF5 implementation. The classes and functions
provided by this module to not throw exceptions by themselves. 
The rational behind this design decision is rather simple: these functions and
classes are used when higher level objects throw exceptions. If they would do
so by themselves they would might cover the original exception.
*/

