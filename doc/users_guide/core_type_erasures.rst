.. _type_erasures:

=============
Type erasures
=============

Templates are powerful tools as they allow the compiler to perform all kinds of
optimizations.In addition they help to avoid virtual functions in classes and
thus increase performance by avoiding call indirection through the virtual
functions table. However, there are two major obstacles with templates

* template expansion virtually always leas to code generation and this could lead to large 
binaries which might be a problem on small hardware architectures
* template libraries and the applications which are using them are harder to maintain. 

The last point may requires a bit of explanation. The reason why system
administrators are not very happy with programs based on template libraries is
that the latter ones are distributed as source code. 
Consequently whenever a bug is fixed in the library all programs depending 
on the code required recompilation. For programs using binary libraries only the
library has to be updated. This is obviously much easier than recompiling 
all the programs depending on a library. 

A reasonable solution for this problem is the use of type erasures. 
*libpninexus* provides three different type erasures

+------------------------+---------------------------------------------------+
| class                  | description                                       |
+========================+===================================================+
| :cpp:class:`value`     | stores a single scalar value of a POD type        |
+------------------------+---------------------------------------------------+
| :cpp:class:`value_ref` | stores the reference to an instance of a POD type |
+------------------------+---------------------------------------------------+
| :cpp:class:`array`     | stores a multidimensional array type              |
+------------------------+---------------------------------------------------+

To use type erasures include the :file:`/pni/type_erasures.hpp` at the 
top of your source file.

The :cpp:class:`value` type erasures
====================================

Construction
------------

The :cpp:class:`value` type erasure stores the value of a single primitive type. 
Whenever an instance of :cpp:class:`value` is constructed memory is allocated 
large enough to store the value of a particular type. 

:cpp:class:`value` provides a default constructor. The instance produced by the 
default constructor holds a value of type :cpp:class:`none`. 

.. code-block:: cpp

   value v;
   std::cout<<v.type_id()<<std::endl; //output NONE

Though there is not too much one can do with such a type it has the nice 
advantage that one can default construct an instance of type :cpp:class:`value`.
In addition a copy and a move constructor is provided. All these constructors
are implicit. 

The more interesting constructors are explicit. An instance of :cpp:class:`value` 
can be constructed either from a variable from a particular type or from a
literal as shown in this next example

.. code-block:: cpp

   //explicit construction from a variable
   int32 n = 1000;
   value v1(n);     
   std::cout<<v1.type_id()<<std::endl; //output INT32
   
   //explicit construction from a literal
   value v2(3.4212); 
   std::cout<<v2.type_id()<<std::endl; //output FLOAT64
   
   //copy construction
   value v3 = v1;

As mentioned earlier in this section, whenever an instance of :cpp:class:`value` 
is constructed, memory is allocated to store the quantity that should be 
hidden in the type erasure. The default constructor would allocate memory for a 
:cpp:class:`none` type with which one can do nothing useful. 
A typical application for type erasures would be to store primitive values 
of different type in a container and we would like to make the decision 
which type to use at runtime. 
For this purpose one could define a vector type like this

.. code-block:: cpp

   using value_vector =  std::vector<value>; 

However, how would one initialize an instance of this vector? It would not make
too much sense to use the default constructor (as we cannot pass type
information). The solution to this problem is the :cpp:func:`make_value` function
which comes in two flavors. The first, as shown in the next code snippet, takes
a type ID as a single argument and returns an instance of :cpp:class:`value` of the 
requested type.

.. code-block:: cpp

   std::vector<type_id_t>  ids = get_ids();
   value_vector values; 
   
   for(auto id: ids)
       values.push_back(make_value(id));

In addition there is a function template which serves the same purpose

.. code-block:: cpp

   value v = make_value<uint32>();

Here the type is determined by the template parameter of the function template.

Assignment
----------

Copy and move assignment are provided by the :cpp:class:`value` between two of its
instances. In both situations the type of the :cpp:class:`value` instance on the 
left handside of the operator changes (this is obvious). 
Move and copy assignment have the expected semantics. 

The more interesting situation appears with assigning new values to an instance
of :cpp:class:`value`. As memory is only allocated during creation (or copy
assignment) assigning a new value does not create a new instance of
:cpp:class:`value` but rather tries to perform a type conversion between the 
instance of :cpp:class:`value` on the LHS of the operator and the value on the LHS. 

.. code-block:: cpp
   
   value v = make_value<float32>(); //creates a value for a float32 value
   
   v = uint16(5); //converts uint16 value to a float32 value

The type conversion follows the same rules as described in the section about 
type conversion earlier in this manual (in fact it uses this functionality). 
Consequently 

.. code-block:: cpp

   value v = make_value<float64>(); 
   
   v = complex32(3,4); //throws type_error 
   
will throw a :cpp:class:`type_error` exception as a complex number cannot be 
converted to a single float value.

Retrieving data
---------------

Retrieving data from an instance of :cpp:class:`value` is done via the :cpp:func:`as` 
template method like this

.. code-block:: cpp

   value v = ....;
   
   auto data = v.as<uint8>();

The template parameter of :cpp:func:`as` determines the data type as which the data
should be retrieved. Like for value assignment the method performs a type
conversion if necessary and throws :cpp:class:`type_error` or :cpp:class:`range_error` 
exceptions if the conversion is not possible or the numeric range of the
requested type is too small.

Information about the type of the data stored in the:cpp:class:`value` instance 
can be obtained by means of the :cpp:class:`type_id` method. 

.. code-block:: cpp

   value v = ...;
   v.type_id();


The :cpp:class:`value_ref` type erasure
=======================================

The :cpp:class:`value` type encapsulates data of an arbitrary type and has full 
ownership of the data. Sometimes it is more feasible to only store a reference 
to an already existing data item of a primitive type. If the reference 
should be copyable the default approach towards this problem would be to use
:cpp:class:`std::reference_wrapper`. Unfortunately, this template includes the 
full type information -- which is what we want to get rid of when using 
a type erasure. 
*libpninexus* for this purpose provides the :cpp:class:`value_ref` erasure. It stores 
a reference to an existing data item and hides all the type information. 
Though :cpp:class:`value_ref` behaves quite similar to :cpp:class:`value` there are some 
subtle differences originating from its nature as a reference type. Thus it
is highly recommended to read this section carefully if you are planing to 
use :cpp:class:`value_ref`.

Construction
------------

Like :cpp:class:`value`, :cpp:class:`value_ref` is default constructible

.. code-block:: cpp

   value_ref vref;

allowing it to be used in STL containers. However, unlike :cpp:class:`value` the default 
constructed reference points to nowhere. Every access to any of
:cpp:class:`value_ref`'s methods will throw :cpp:class:`memory_not_allocated_error` 
for a default constructed instance of :cpp:class:`value_ref`. The preferred way of 
how to initialize :cpp:class:`value_ref` is by passing an instance of 
:cpp:class:`std::reference_wrapper` to it 

.. code-block:: cpp

   float64 data;
   value_ref data_ref(std::ref(data));

In addition :cpp:class:`value_ref` is copy constructible. 

Assignment
----------

The most difficult operation with :cpp:class:`value_ref` is assignment. It really
depends on the right handside of the assignment operator what happens. 
One can do copy assignment

.. code-block:: cpp

   float32 temperature; 
   uint32  counter;
   value_ref v1(std::ref(temperature)); //reference to temperature
   value_ref v2(std::ref(counter));     //reference to counter
   
   v1 = v2; //now v1 is a reference to counter too

which has the same semantics as the copy assignment for
:cpp:class:`std::reference_wrapper` where the reference is copied. 

Another possibility is to assign the value of a primitive type to an 
instance of :cpp:class:`value_ref`. In this case two things are taking place

* the value is converted to the type of the data item the instance of :cpp:class:`value_ref` references
* the converted value is assigned to the referenced data item

Consider this example

.. code-block:: cpp

   float32 temperature;
   value_ref temp_ref(std::ref(temperature));
   
   temp_ref = uint16(12);

In this example the value 12 of type :cpp:type:`uint16` is first converted to 
a :cpp:type:`float32` value. This new float value is then assigned to the variable 
:cpp:var:`temperature`. As always with type conversions exceptions will be 
thrown if the conversion fails.

One can also change the variable an instance of :cpp:class:`value_ref` references 
with

.. code-block:: cpp

   value_ref ref = ....;    //reference to some data item
   complex64 refractive_index = ...;
   
   //now reference points to refractive_index
   ref = std::ref(refractive_index);  

Finally a value from a :cpp:class:`value` instance can be assigned with

.. code-block:: cpp

   value v = int32(100);
   value_ref ref = ....;
   
   ref = v;

in which case type conversion from the internal type of :cpp:var:`v` to the internal 
type of :cpp:var:`ref` occurs. Exceptions are thrown if the type conversion fails.

Retrieving data
---------------

Data retrieval for :cpp:class:`value_ref` works exactly the same way as for
:cpp:class:`value`. The type provides a template method :cpp:func:`as` which can be 
used to get a copy of the data stored in the item referenced as an instance 
of a type determined by the template parameter. 

.. code-block:: cpp

   value_ref ref = ....;
   
   auto data = ref.as<uint32>();

Again, type conversion takes place from the original type of the referenced 
data item to the type requested by the user via the template parameter. 
Finally, as :cpp:class:`value`, :cpp:class:`value_ref` provides a 
:cpp:func:`type_id` member 
function which returns the type ID of the referenced data item.



Type erasures for arrays
========================

As *libpninexus* provides a virtually indefinite number of array types via its
:cpp:class:`mdarray` template the :cpp:class:`array` type erasure is maybe one of the most
important ones. Like the :cpp:class:`value` type erasure it will take over full
ownership of the array stored in it.

A good introduction into the :cpp:class:`array` type erasure is this particular version
of the array inquiry  example from the previous chapter on arrays. 

.. literalinclude:: ../examples/core/type_erasure3.cpp
   :language: cpp
   :lines: 25-62
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure3.cpp` for full code
   

In the previous version, where :cpp:func:`show_info` was a template function a new
version of :cpp:func:`show_info` would have been created for each of the three array
types used in this example. By using the type erasure only a single version of
:cpp:func:`show_info` is required which reduces the total code size of the binary.

The current implementation of :cpp:class:`array` is rather limited in comparison 
to the :cpp:class:`mdarray` template. Multidimensional access is not provided and only
forward iteration is implemented. In addition there is now :cpp:class:`array_ref` 
type erasure which only keeps a reference to an instance of :cpp:class:`mdarray`. 

The iterators themselves have a subtle speciality. They do not provide a
:cpp:func:`->` operator. This has a rather simple reason. While all other interators
return a pointer to a particular data element in a container the :cpp:class:`array`
iterators cannot do this (they do no hold any type information). Instead they
return an instance of :cpp:class:`value` for constant or :cpp:class:`value_ref` for
read/write iterators. In order to keep the semantics of the :cpp:func:`->` operator we
would have to return :cpp:type:`*value` or :cpp:type:`*value_ref` from the :cpp:func:`->`
operator. However, this is not possible as these objects are just temporaries
and would be destroyed once the operator function has returned. 
However, this is only a small inconvenience as it has no influence on the 
STL compliance of the iterator. 
One can still use the *for-each* construction

.. code-block:: cpp

   array a(...);
   
   for(auto x: a)
       std::cout<<s<<std::endl;

and all STL algorithms with a :cpp:class:`array` type erasure.

An example: reading tabular ASCII data
======================================

In this final section a typical use-case for a type erasure will be discussed. 
One problem that regularly pops up is to read tabular ASCII data. 
For this example a very simple file format has been used. The file
:file:`record.dat`
has the following content

.. literalinclude:: ../examples/core/record.dat
   :language: text

While the elements of the first two columns are integer and float respectively,
the third column holds complex numbers. The task is simple: read the values from
the file without losing information. This means that we do not want to truncate
values (for instance float to integer) or do inappropriate type conversions (for
instance convert everything to the complex type) which may add rounding errors. 

There are several ways how to approach this problem. The most straight forward
one would be to create a :cpp:type:`struct` with an integer, a float, and a complex
element. However, this approach is rather static. If a column will be added or
removed or only the order of the columns is changed we have to alter the code. 

In this example a different path has been taken. Each individual line is
represented by a record type which consists of a vector whose elements are
instances of the :cpp:class:`value` type erasure.

.. literalinclude:: ../examples/core/type_erasure_record.cpp
   :language: cpp
   :lines: 26-42
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure_record.cpp` for full code
   
The entire table is again a vector with :cpp:type:`record_type` as element type.
In addition we have defined a special type to store complex numbers
(:cpp:type:`complex_type`).

Defining the parsers
--------------------

One of the key elements for this example is to use the *boost::spirit*
parser framework. We define three parsers

* one for the :cpp:type:`complex_type`
* one for a value which can parser integer, double, and complex numbers
* and one for the entire record.

The *boost::spirit* framwork is indeed rather complex and requires a deep
understanding of some of the additional boost libraries like *fusion* and
*phoenix*. However, as we will see, it is worth to become familiar with them
as will be shown here.

In this next snippet the definition of the complex number parser is shown. 

.. literalinclude:: ../examples/core/type_erasure_record.cpp
   :language: cpp
   :lines: 46-62
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure_record.cpp` for full code

We assume complex numbers to be stored as tuples of the form *(real
part,imaginary part)*. As we can see in the above example the complex type is
assembled from the two double values matched in the rule. The next parser
required is the value parser. This parser matches either an integer, a double,
or a complex value. It is a good example how to reuse already existing 
parser in *boost::spirit*. 

.. literalinclude:: ../examples/core/type_erasure_record.cpp
   :language: cpp
   :lines: 67-93
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure_record.cpp` for full code


Finally we need a parser for the entire record. This is rather simple as
*boost::spirit* provides a special syntax for parsers who store their
results in containers.

.. literalinclude:: ../examples/core/type_erasure_record.cpp
   :language: cpp
   :lines: 98-111
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure_record.cpp` for full code

The main program
----------------

The main program is rather simple 

.. literalinclude:: ../examples/core/type_erasure_record.cpp
   :language: cpp
   :lines: 195-203
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure_record.cpp` for full code

Not all the code will be explained as it is only those parts which are of
interest for the :cpp:class:`value` type erasure.
The program can be divided into two parts:

* reading the data (in line 132) 
* and writing it back to standard output (in line 148)

As the latter one is rather trivial we will only consider the reading part in
this document. The output of the main function is 

.. code-block:: text

   INT32
   FLOAT64
   COMPLEX32
   11      -123.23 (-1,0.23)
   13      -12.343 (12.23,-0.2)
   16      134.12  (1.23,-12.23)


The reading sequence
--------------------

The entry point for the read sequence is the :cpp:func:`read_table` function.

.. literalinclude:: ../examples/core/type_erasure_record.cpp
   :language: cpp
   :lines: 132-145
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure_record.cpp` for full code


The logic of this function is rather straight forward. Individual lines are
written from the input stream until *EOF* and passed on to the
:cpp:func:`parse_record` function which returns an instance of :cpp:type:`record_type`. 
Each record is appended to the table. 

The :cpp:func:`parse_record` function is where all the magic happens

.. literalinclude:: ../examples/core/type_erasure_record.cpp
   :language: cpp
   :lines: 116-127
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/type_erasure_record.cpp` for full code

The definition of this function pretty much demonstrates the power of the
*boost::spirit* library. All the nasty parsing work is done by the code 
provided by *boost::spirit*. The only thing left to do is provide iterators
to the beginning and end of the line.


