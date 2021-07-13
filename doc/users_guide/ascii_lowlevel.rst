=============================
The low-level ASCII interface
=============================

At the very bottom of the ASCII IO interface are 

* *parsers* reading ASCII data from a stream
* and *formatters* which can be used to write ASCII data to a stream

Parsers
=======

The major job of this interface is to provided save number parsing. It supports 
all primitive data types provided by *libpnicore* along with instances of 
:cpp:class:`std::vector` of such types.

At the heart of the parser API is the :cpp:class:`pni::io::parser` class 
template. It takes one template parameter which is the primitive or container 
type to parse. To use the parser API just include :file:`pni/parsers.hpp` in 
your source file. 

Parsing primitive scalars
~~~~~~~~~~~~~~~~~~~~~~~~~

A very simple example would be something like this

.. code-block:: cpp

   #include <iostream>
   #include <pni/core/types.hpp>
   #include <pni/parsers.hpp>
   
   using namespace pni::core;
   
   using Float64Parser = pni::io::parser<float64>;
   
   int main(int argc,char **argv)
   {
       Float64Parser p;
   
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
   #include <pni/parsers.hpp>
   
   using namespace pni::core;
   
   using Record       = std::vector<value>;
   using RecordParser = pni::io::parser<Record>;
   
   int main(int argc,char **argv)
   {
       RecordParser p;
       Record record = p("1.234  12 1+I3.4");
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
separated by at least one blank. There are three more constructors 
allowing you to customize the behavior for the container parser. 

The first allows to use a custom delimiter symbol

.. code-block:: cpp

   RecordParser parser(','); // set , as an element delimiter
   Record data = parser("1.234,12 , 1+I3.4");

It is important to note that the delimiter symbol can be surrounded by an
arbitrary number of blanks. 
The second constructor provides the constructor with additional 
start and stop symbols. 

.. code-block:: cpp

   RecordParser parser('[',']');
   Record data = parser("[1.234 12  1+I3.4]");

However, the elements in the string are now again separated only by blanks. 
Full customization of the parser is provided by the third constructor which
allows the user to provide not only start and stop symbols but also a custom 
delimiter symbol

.. code-block:: cpp

   RecordParser parser('[',']',';');
   Record data = parser("[1.234;12 ; 1+I3.4]");
   
Formatters
==========

Formatters perform literally the inverse operation of parsers. They write 
data to a stream. Like for parsers the major concern here was to write 
numeric data without loss of precision to a stream. 

.. note::

   It is a common error when writing numbers in ASCII format to use the 
   wrong precision. In the best case only  0 are written which is usually 
   recognized rather early during software development. However, also truncations
   and thus loss of precision can occur which sometimes can lead to hard 
   to recognize and thus difficult to debug bugs. 
   
   Thus, the formatter functions provided by *libpniio* usually write numeric
   data with the maximum precision to avoid such issues. 
   
Formatters are currently implemented as functions returning a string 
with the formatted output. You can use 
them after including :file:`pni/formatters.hpp` in your source code. 

For scalar data their usage is rather simple 

.. code-block:: cpp

   uint8 number = ...;
   std::cout<<pni::io::format(number)<<std::endl; 
   
The format function takes care that the number if converted to a string 
without loss of precision. 

As for parsers, there are also overloaded formatters for containers like 
:cpp:class:`std::vector`. In this case the :cpp:func:`format` function 
takes an optional second argument which is a reference to 
:cpp:class:`pni::io::container_io_config`. This class controls how such 
container data is written to disk. 
Taking the record example from the above parser section we could do 
something like this 

.. code-block:: cpp

   //using a ; as a separator between record elements 
   pni::io::container_io_config config(';'); 
   
   Record record = ...;
   std::cout<<pni::io::format(record,config)<<std::endl;
   
 

