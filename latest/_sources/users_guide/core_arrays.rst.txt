.. _arrays:

=======================
Multidimensional arrays
=======================

C++ has no multidimensional array type (MDA) in its standard library. 
However, MDAs are crucial for the developmemt of scientific applications.
One of the reasons for the continuing success of languages like Fortran or Python
is their excellent support for MDAs\footnote{For Python arrays are introduced by
the \texttt{numpy} package.}. The lack of an MDA type in C++
was indeed the spark that initiated the developement of \libpninexus.  Before
discussing `libpninexus` s array facilities some terminology should be defined: 


element type (ET)   
    referes to the data type of the individual elements stored in an MDA. For
    MDAs this will typically be a numeric type like an integer or a floating
    point number.

rank :math:`r`
    denotes the number of dimensions of an MDA 

shape :math:`\mathbf{s}`
    is a vector of dimension :math:`r` whose elements are the
    number of elements along each dimension. The elements of :math:`\mathbf{s}` are
    denoted as :math:`s_i` with :math:`i=0,\dots,r-1` 

The hart of `libpninexus` s MDA support is the :cpp:class:`mdarray` template.
:cpp:class:`mdarray` is extremely powerfull. Thus, using :cpp:class:`mdarray`
directly to define array types is not for the faint harted.  To simplify the
usage of multidimensional arrays the library provides three templates derived
form :cpp:class:`mdarray` which are easy to use.  

+-------------------------------+------------------------------------+-+
| template alias                | description                        | |
+===============================+====================================+=+
| *static_array<T,size_t ...N>* | a static arrays whose shape, rank, | |
|                               | and element type are fixed at      | |
|                               | compile time.                      | |
+-------------------------------+------------------------------------+-+
| *fixed_dim_array<T,R>*        | element type and rank are fixed at | |
|                               | compile time but the shape can be  | |
|                               | changed at runtime.                | |
+-------------------------------+------------------------------------+-+
| *dynamic_array<T>*            | a fully dynamic array type where   | |
|                               | only the element type must be      | |
|                               | known at compile time. The rank    | |
|                               | as well as the shape can be        | |
|                               | altered at runtime                 | |
+-------------------------------+------------------------------------+-+


These types are all defined in :file:`pni/arrays.hpp`.
In addition to this two basic templates there are several utility classes and
templates like

+---------------------------+------------------------------------+-+
| template                  | functionality                      | |
+===========================+====================================+=+
| :cpp:class:`arrayview`    | this template provides a view on a | |
|                           | particular part of an array        | |
+---------------------------+------------------------------------+-+
| :cpp:class:`arrayerasure` | type erasure for an array          | |
+---------------------------+------------------------------------+-+


All array types derived from :cpp:class:`mdarray` provide the following features

* unary and binary arithmetics if the element type is a numeric type.
* slicing to extract only a part of a large array
* simple access to data elements using variadic operators.
* all array types are full STL compliant containers and thus can be used
  along with STL algorithms.

.. ============================================================================

Array construction and inquery
==============================
    
Constructing arrays is rather simple by means of the :cpp:func:`create` function
provided by the array templates. As shown in :file:`array_create.cpp` 

.. literalinclude:: ../examples/core/array_create.cpp
   :language: cpp
   :linenos:
   :lineno-match:
   :lines: 28-50
   :caption: see :file:`examples/core/array_create.cpp`
   
   
In line 35 a concrete array type is defined from the :cpp:class:`dynamic_array`
utility template.
The :cpp:func:`create` function comes in three flavors as shown in the previous
example

+------+----------------------------------------------------------------+
| line | description                                                    |
+======+================================================================+
| 40   | Only the shape is passed as an argument. The storage container |
|      | is allocated automatically by the constructor.                 |
+------+----------------------------------------------------------------+
| 43   | The storage container with initial data is passed as a second  |
|      | argument to :cpp:func:`create` along with the shape of the     |
|      | array.                                                         |
+------+----------------------------------------------------------------+
| 47   | shape as well as initial data are provided via                 |
|      | initializer lists.                                             |
+------+----------------------------------------------------------------+

After an array has been created we may want to retrieve some of its basic
properties. In the next example we do exactly this 

.. literalinclude:: ../examples/core/array_inquery.cpp
   :language: cpp
   :lines: 28-56
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_inquery.cpp` for full code

The important part is the implementation of the :cpp:func:`show_info` function
template starting at line 37. The function template :cpp:func:`type_id` is used in
line 40 to retrieve the type ID of the arrays element type. :cpp:func:`rank` in line
41 returns the number of dimension and :cpp:func:`size` in line 46 the total
number of elements stored in the array. 
The :cpp:func:`shape` template function in line 43 returns the number of elements
along each dimension stored in a user provided container type.

The content of arrays can be copied to and from containers using the standard 
:cpp:func:`std::copy` template function from the STL. In addition a version of the
assignment operator is provided which allows assignment of values from an
initializer list. This is particularly useful for static arrays which basically
do not require construction. 

.. code-block:: cpp

   using static_array_type = ....; 

   static_array_type a;
   a = {1,2,3,4,5};



Linear access to data
=====================

As already mentioned in the first section of this chapter, the array types
provided by *libpninexus* are fully STL compliant containers. They provided all
the iterators required by the STL. 
Before we have a look on STL lets first investigate how to simply access data
elements in an array

.. literalinclude:: ../examples/core/array_linear_access.cpp
   :language: cpp
   :lines: 28-60
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_linear_access.cpp` for full code


For all array types the new C++ *for-each* construction can be used as shown
in lines 47 and 57. Unchecked access (no index bounds are checked) is
provided via the *[]* operator as demonstrated in line 50 (use :cpp:func:`at`
for checked access).
Some of the operations in this example can be done much more efficient with STL
algorithms as demonstrated in the next example

.. literalinclude:: ../examples/core/array_stl.cpp
   :language: cpp
   :lines: 28-59
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_stl.cpp` for full code

In line 42 :cpp:func:`std::fill` is used to initialize the array to 0 and 
:cpp:func:`std::generate` in line 48 fills it with random numbers using a lambda
expression . The rest of the example should be trivial (if not, please lookup a
good C++ STL reference).


Multidimensional access
=======================

Though being an important feature, linear access to multidimensional arrays is
not always useful. In particular the last example where we pretended to work on
image data implementing algorithms would be rather tedious if we would have had
only linear access. It is natural for such objects to think in pixel coordinates
*(i,j)* rather than the linear offset in memory. 
*libpninexus* provides easy multidimensional access to the data stored in an
array. The next example shows how to use this feature to work only on a small
region of the image data as defined in the last example

.. literalinclude:: ../examples/core/array_multiindex.cpp
   :language: cpp
   :lines: 28-69
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_multiindex.cpp` for full code


The interesting part here are lines 59 and 60. You can pass the
multidimensional indexes either as a variadic argument list to the  *()*
operator of the array type (as in line 59) or you can use a container like 
in line 60. The former approach might look a bit more familiar, however, in
some cases when decisions have to made at runtime the container approach might
fits better. However, passing containers reduces access performance
approximately by a factor of 2. Thus, as a rule of thumb you should always use
the variadic form when you know the number of dimensions the array has and
containers only in those cases where this information is only available at
runtime.


Array views and slicing
=======================

In the previous example multiindex access was used to do work on only a small
part of the image data. *libpninexus* provides view types for arrays which would
make these operations easier. Views are created by passing instances of 
:cpp:class:`slice` to the *()* operator of an array type. Slices in *libpninexus* work
pretty much the same as in python. Lets have a look on the following example

.. literalinclude:: ../examples/core/array_view.cpp
   :language: cpp
   :lines: 28-63
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_view.cpp` for full code

The view is created in line 53 where the slices are passed instead of integer
indices to the *()* operator. A slice selects an entire index range along a
dimension. The first argument to the :cpp:class:`slice` constructor is the starting
index and the last the stop index of the range. The stop index is not included
(just as it is the case with Python slices). If the *()* operator of an
array is called with any of its arguments being a slice a view object is
returned instead of a single value or reference to a single value. 
View objects are pretty much like arrays themselves. However, they do not hold
data by themselves but only a reference to the original array. 
Like arrays they are fully STL compliant containers and thus can be used with
STL algorithms as shown in lines 54 and 56. 

View types can be copied and moved and thus can be stored in STL containers as
shown in the next example

.. literalinclude:: ../examples/core/array_view_container.cpp
   :language: cpp
   :lines: 28-73
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_view_container.cpp` for full code 


Here we apply the algorithms from the previous example not to a single but to
several selections in the image. As shown in lines 55 to 57 we can safely
store views in a container and later iterate over it.

In general views make algorithm development much easier as we have to develop
algorithms only for entire arrays. If it should be applied to only a part of an
array we can use a view and pass it to the algorithm. As views expose the same
interface as an array the algorithm should work on views too.

Arithmetic expressions
======================

Array and view types fully support the common arithmetic
operators *+*, *\**, */*, and *-* in their binary and unary
forms. The binary versions are implemented as expression templates avoiding the
allocation of unnecessary temporary and giving the compiler more possibilities
to optimize the code. 
Views, arrays and scalars can be mixed within all arithmetic expressions. 
There is nothing magical with expression templates as they work entirely
transparent to the user. Just use the arithmetic expressions as you are used to

.. literalinclude:: ../examples/core/array_arithmetic1.cpp
   :language: cpp
   :lines: 28-50
   :linenos: 
   :lineno-match:
   :caption: see :file:`examples/core/array_arithmetic1.cpp`


The important line here is 47 where arrays and scalars are mixed in an
arithmetic expression.
One can also mix arrays, selections, and scalars as the next examples 
shows

.. literalinclude:: ../examples/core/array_arithmetic2.cpp
   :language: cpp
   :lines: 28-58
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_arithmetic2.cpp` for full code

In line 53 a single image frame is selected from a stack of images and used in
line 54 in an arithmetic expression. In fact, what we are doing here is,
we are writing the corrected data back on the stack since :cpp:var:`curr_frame` is
just a view on the particular image in the stack.


Example: matrix-vector and matrix-matrix multiplication
=======================================================
In the last example matrix vector multiplications are treated. The full code can
be viewed in :file:`array_arithmetic3.cpp` in the source distribution. But lets
first start with the header

.. literalinclude:: ../examples/core/array_arithmetic3.cpp
   :language: cpp
   :lines: 28-139
   :linenos:
   :lineno-match:
   :caption: see :file:`examples/core/array_arithmetic3.cpp` for full code

Besides including all required header files matrix and vector templates are 
defined in lines 37 and 38 using the new C++11 template aliasing.

Matrix vector multiplication
----------------------------

The implementation of the matrix vector multiplication is shown in the next
block. 

.. math::

    \mathbf{r} = A\mathbf{v} \mbox{ or } r_j = A_{j,i}v_i

with :math:`\mathbf{A}` denoting a :math:`N\times N` matrix and 
:math:`\mathbf{r}` and :math:`\mathbf{v}` are
:math:`N`-dimensional vectors. In all formulas Einsteins sum convention is used.

.. literalinclude:: ../examples/core/array_arithmetic3.cpp
   :language: cpp
   :lines: 66-78
   :linenos:
   :lineno-match:

In line 74 we select the :math:`i`-th row of the matrix and compute the inner
product of the row vector and the input vector in line 75. 

Vector matrix multiplication
----------------------------

The vector matrix multiplication

.. math::

    \mathbf{r} = \mathbf{v}A\mbox{ or } r_i = v_j A_{j,i}

is computed analogously

.. literalinclude:: ../examples/core/array_arithmetic3.cpp
   :language: cpp
   :lines: 82-94
   :linenos:
   :lineno-match:
 
despite the fact that we are choosing the appropriate column instead of a row in 
line 90. 

Matrix matrix multiplication
----------------------------

Finally we need an implementation for the matrix - matrix
multiplication

.. math::

   C = AB \mbox{ or } C_{i,j} = A_{i,k}B_{k,j}


.. literalinclude:: ../examples/core/array_arithmetic3.cpp
   :language: cpp
   :lines: 98-114
   :linenos:
   :lineno-match:

The rows and columns are selected in lines 107 and 108 respectively. 
Line 109 finally computes the inner product of the row and column vector.

Putting it all together: the main function
------------------------------------------

Finally the main program shows a simple application of these template functions. 

.. literalinclude:: ../examples/core/array_arithmetic3.cpp
   :language: cpp
   :lines: 123-139
   :linenos:
   :lineno-match:

It is important to understand that the appropriate function is determined by the
types of the arguments (vector or matrix). This is a rather nice example of how
to use the typing system of C++ to add meaning to objects.

The output of the program is

.. code-block:: bash

   >./array_arithmetic3
   m1 = 
   | 1 2 3 |   
   | 4 5 6 |
   | 7 8 9 |

   m2 = 
   | 9 8 7 |
   | 6 5 4 |
   | 3 2 1 |
   
   v  = 
   | 1 |
   | 2 |
   | 3 |
   
   m1.v = 
   | 14 |
   | 32 |
   | 50 |
   
   v.m1 = 
   | 30 |
   | 36 |
   | 42 |
   
   m1.m2 = 
   | 30 24 18 |
   | 84 69 54 |
   | 138 114 90 |

