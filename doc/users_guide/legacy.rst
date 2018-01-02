==============
Legacy formats
==============

The term legacy data refers to all non-Nexus file formats.
*libpnicore* distinguishes between tow families of legacy formats 

* ASCII file where the content is entirely stored in human readable ASCII
  characters
* and binary data where the raw binary information is stored in a file.

ASCII data
==========

Lowlevel parser interface
-------------------------

The major job of this interface is to provided save number parsing. It supports 
all primitive data types provided by *libpnicore* along with 
:cpp:class:`std::vector` begin a container of a primitive type.
For a detailed explanation about the low level parsers see
Appendix~\ref{appendix:parsers}. 

At the heart of the parser API is the :cpp:class:`pni::io::parser` class 
template. It takes one template parameter which is the primitive or container 
type to parse. To use the parser API just include :file:`pni/io/parsers.hpp` in 
your source file. 

Parsing primitive scalars
~~~~~~~~~~~~~~~~~~~~~~~~~

A very simple example would be something like this

.. code-block:: cpp

   #include <iostream>
   #include <pni/core/types.hpp>
   #include <pni/io/parsers.hpp>
   
   using namespace pni::core;
   using namespace pni::io;
   
   typedef parser<float64> float64_parser_type;
   
   int main(int argc,char **argv)
   {
       float64_parser_type p;
   
       float64 data = p("1.234");
       std::cout<<data<<std::endl;
   
       return 0;
   }
   
This example should be rather self explaining. 
When used with scalar values the parser template provides only a default 
constructor. No additional information is required to configure the 
parser code. 

Besides primitive types the :cpp:class:`pni::io::parser` template can also be 
used with the :cpp:class:`pni::core::value` type erasure. In this case the 
resulting parser matches either a 

* :cpp:type:`pni::core::int64`
* or a :cpp:type:`pni::core::float64`
* or a :cpp:type:`pni::core::complex64` type.

Again no additional configuration at parser instantiation is required. 
For the ASCII representation of complex numbers see
Appendix~\ref{appendix:parsers}.

Parsing a vector of primitives
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Besides single scalars the :cpp:class:`pni::io::parser` template can also be 
used with :cpp:class:`std::vector` based containers where the element type 
should be one of the primitive types or a value. 
For this purpose a specialization of the :cpp:class:`pni::io::parser` template 
of the form

.. code-block:: cpp

   template<typename T> class parser<std::vector<T>> {...};

is provided. A particularly interesting choice as an element is the 
:cpp:class:`pni::core::value` type erasure as it allows to parse a series of 
inhomogeneous types. The following program

.. code-block:: cpp

   #include <iostream>
   #include <vector>
   #include <pni/core/types.hpp>
   #include <pni/io/parsers.hpp>
   
   using namespace pni::core;
   using namespace pni::io;
   
   typedef std::vector<value> record_type;
   typedef parser<record_type> record_parser;
   
   int main(int argc,char **argv)
   {
       record_parser p;
       record_type data = p("1.234  12 1+I3.4");
       for(auto v: data)
           std::cout<<v.type_id()<<std::endl;
   
       return 0;
   }

would produce this output

.. code-block:: text
   
   FLOAT64
   INT64
   COMPLEX64

When using the default constructor of the :cpp:class:`pni::io::parser` 
template with a container type the individual elements are considered to be 
separated by at least one blank. 
However the vector parser specialization of :cpp:class:`pni::io::parser` 
provides three more additional constructors. 
The first allows to use a custom delimiter symbol

.. code-block:: cpp

   record_parser p(','); // set , as an element delimiter
   record_type data = p("1.234,12 , 1+I3.4");

It is important to not that the delimiter symbol can be surrounded by an
arbitrary number of blanks. 
The second constructor provides the constructor with additional 
start and stop symbols. 

.. code-block:: cpp

   record_parser p('[',']');
   record_type data = p("[1.234 12  1+I3.4]");

However, the elements in the string are now again separated only by blanks. 
Full customization of the parser is provided by the third constructor which
allows the user to provide not only start and stop symbols but also a custom 
delimiter symbol

.. code-block:: cpp

   record_parser p('[',']',';');
   record_type data = p("[1.234;12 ; 1+I3.4]");



Binary data
===========

.. todo::

   Add section about binary data formats

