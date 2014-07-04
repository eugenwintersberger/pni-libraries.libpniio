/*!
\ingroup nexus_io
\defgroup nexus_xml_utilities XML utilities

Creating the structure of a Nexus file can be rather tedious when coded
statically. Additionally such an approach is usually rather inflexible and thus
should be avoided at all. \c libpniio provides utility functions to create
Nexus objects using XML templates. Fortunately, Nexus comes with its own XML
dialect called NXDL which already defines the XML vocabulary necessary to
describie Nexus files with XML. 

Using NXDL makes programs much more flexible and gives users the possibility to
customize the layout of a Nexus file without rewriting code.

Under the hood the XML/NXDL facility provided here is based on
BOOST::property_tree providing a non-validating XML parser.  However, for our
purpose validation is not really required. 
*/

/*!
\ingroup nexus_xml_utilities
\defgroup xml_lowlevel_utils XML low level utilities

*/

/*!
\ingroup nexus_xml_utilities
\defgroup nexus_xml_level2_utils NXDL base class utilities

*/
