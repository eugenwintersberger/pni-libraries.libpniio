.. documentation on data types

==========
Data Types
==========

=========================   ======================  ============================  ===============================
:cpp:enum:`type_class_t`    data type               :cpp:enum:`type_id_t`         description
=========================   ======================  ============================  ===============================
:cpp:enumerator:`INTEGER`   :cpp:type:`uint8`       :cpp:enumerator:`UINT8`       8Bit unsinged integer 
:cpp:enumerator:`INTEGER`   :cpp:type:`int8`        :cpp:enumerator:`INT8`        8Bit signed integer   
:cpp:enumerator:`INTEGER`   :cpp:type:`uint16`      :cpp:enumerator:`UINT16`      16Bit unsigned integer
:cpp:enumerator:`INTEGER`   :cpp:type:`int16`       :cpp:enumerator:`INT16`       16Bit signed integer  
:cpp:enumerator:`INTEGER`   :cpp:type:`uint32`      :cpp:enumerator:`UINT32`      32Bit unsigned integer
:cpp:enumerator:`INTEGER`   :cpp:type:`int32`       :cpp:enumerator:`INT32`       32Bit signed integer  
:cpp:enumerator:`INTEGER`   :cpp:type:`uint64`      :cpp:enumerator:`UINT64`      64Bit unsigned integer
:cpp:enumerator:`INTEGER`   :cpp:type:`int64`       :cpp:enumerator:`INT64`       64Bit signed integer  
:cpp:enumerator:`FLOAT`     :cpp:type:`float32`     :cpp:enumerator:`FLOAT32`     32Bit IEEE floating point type  
:cpp:enumerator:`FLOAT`     :cpp:type:`float64`     :cpp:enumerator:`FLOAT64`     64Bit IEEE floating point type  
:cpp:enumerator:`FLOAT`     :cpp:type:`float128`    :cpp:enumerator:`FLOAT128`    128Bit IEEE floating point type
:cpp:enumerator:`COMPLEX`   :cpp:type:`complex32`   :cpp:enumerator:`COMPLEX32`   32Bit IEEE complex float type   
:cpp:enumerator:`COMPLEX`   :cpp:type:`complex64`   :cpp:enumerator:`COMPLEX64`   64Bit IEEE complex float type   
:cpp:enumerator:`COMPLEX`   :cpp:type:`complex128`  :cpp:enumerator:`COMPLEX128`  128Bit IEEE complex float type 
:cpp:enumerator:`STRING`    :cpp:type:`string`      :cpp:enumerator:`STRING`      string  type  
:cpp:enumerator:`BINARY`    :cpp:type:`binary`      :cpp:enumerator:`BINARY`      binary type  
:cpp:enumerator:`NONE`      :cpp:type:`none`        :cpp:enumerator:`NONE`        none type    
=========================   ======================  ============================  ===============================

An overview of the primitive data types provided by `libpninexus`.

.. ===================================================================================

*libpninexus* provides a set of data types of well defined size and utility
functions related to type management.  The basic header file required to use
*libpninexus* s type facilities is 

.. code-block:: cpp
    
    #include <pni/types.hpp>

The data types provided by *libpninexus* include

* numeric types with all their arithmetic operations
* string types (currently only one member)
* and utility types like :cpp:type:`binary_t`, :cpp:type:`bool_t`, and 
  :cpp:type:`none`.

All this types together are refered to as `primitive types`.  The numeric types
are ensured to have the same size on each platform and architecture supported
by `libpninexus`. They are mostly aliases to the types defined by the C standard
library.  However, the utility types :cpp:type:`binary_t`, :cpp:type:`bool_t`, and
:cpp:type:`none` are unique to `libpninexus` and will be explained in more
detail in the last sections of this chapter.

Every type in `libpninexus` is associated with an ID represented by the
:cpp:enum:`type_id_t` enumeration type. Additionally every type belongs to a
particular type class defined by the :cpp:enum:`type_class_t` enumeration type.
Table~\ref{tab:types:basic_types} gives an overview over the primitive types
provided by `libpninexus` and their corresponding :cpp:enum:`type_id_t` and
:cpp:enum:`type_class_t` values.

Compile time type identification
================================

To obtain the ID or class of a type at compile time use the 
:cpp:class:`type_id_map` or :cpp:class:`type_class_map` type maps. 

.. code-block:: cpp

    #include <pni/types.hpp>

    using namespace pni;

    //determine the type ID for a given type
    type_id_map<float32>::type_id == type_id_t::Float32;

    //obtain the class of a particular type
    type_class_map<float32>::type_class == type_class_t::Float;

For IDs the other way around is also possible with the :cpp:class:`id_type_map`

.. code-block:: cpp

    #include <pni/types.hpp>

    using namespace pni;

    //determine the type for a given ID
    id_type_map<type_id_t::Float32>::type data = ...;


For numeric types there are also some other templates for a more detailed type
classification 

======================================= ==========================================================
template                                description
======================================= ==========================================================
:cpp:member:`is_integer_type<T>::value`  **true** if :cpp:any:`T` is an integer type
:cpp:member:`is_float_type<T>::value`    **true** if :cpp:any:`T` is a floating point type
:cpp:member:`is_complex_type<T>::value`  **true** if :cpp:any:`T` is a complex number
:cpp:member:`is_numeric_type<T>::value`  **true** if :cpp:any:`T` is any of the above types
======================================= ==========================================================



Identifying types at runtime
============================

======================   ========================
data type                string representation 
======================   ========================
:cpp:type:`uint8`        "uint8", "ui8" 
:cpp:type:`int8`         "int8", "i8"  
:cpp:type:`uint16`       "uint16", "ui16" 
:cpp:type:`int16`        "int16", "i16"  
:cpp:type:`uint32`       "uint32", "ui32" 
:cpp:type:`int32`        "int32", "i32"  
:cpp:type:`uint64`       "uint64", "ui64" 
:cpp:type:`int64`        "int64", "i64"  
:cpp:type:`float32`      "float32", "f32"
:cpp:type:`float64`      "float64", "f64"
:cpp:type:`float128`     "float128", "f128"
:cpp:type:`complex32`    "complex32", "c32"
:cpp:type:`complex64`    "complex64", "c64"
:cpp:type:`complex128`   "complex128", "c128"
:cpp:type:`string`       "string", "str"
:cpp:type:`binary`       "binary", "binary"
:cpp:type:`none`         "none" 
======================   ========================

Data types and their string representations.

.. ============================================================================

The recommended way to deal with type information at runtime are the
:cpp:enum:`type_id_t` enumerations.  At some point in time a program might has
to determine the type ID of a variable type or of the element type of a
container.  The basic facility to achieve this is the :cpp:func:`type_id`
function defined in :file:`pni/type_utils.hpp`.  The usage of this
function is rather simple as shown here

.. code-block:: cpp

    #incldue<pni/types.hpp>

    using namespace pni;

    //one could use this with 
    auto data = get_data(...);

    std::cout<<type_id(data)<<std::endl;

The important thing to notice here is that no matter what type the
:cpp:func:`get_data` function returns, :cpp:func:`type_id` will give you the
type ID.  In cases where the type ID is given and a classification of the type
has to be made four functions are provided where each takes a type ID as its
single most argument

==================================  ======================================================
function                            description
==================================  ======================================================
:cpp:func:`is_integer` (type_id_t)  returns true if the type ID refers to an integer type 
:cpp:func:`is_float` (type_id_t)    returns true if the type ID refers to a float type 
:cpp:func:`is_complex` (type_id_t)  returns true if the type ID refers to a complex type 
:cpp:func:`is_numeric` (type_id_t)  returns true if the type ID refers to a numeric type 
==================================  ======================================================

Another important scenario is the situation where a user uses the string
representation to tell a program with which type it should work.  In such a
situation you either want to convert the string representation of a type into a
value of :cpp:enum:`type_id_t` or vica verse. The library provides two
functions for this purpose :cpp:func:`type_id_from_str` which converts the
string representation of a type to a value of :cpp:enum:`type_id_t` and
:cpp:func:`str_from_type_id` which performs the opposite operation.  The usage
of this two guys is again straight forward.

.. code-block:: cpp

    #include <pni/types.hpp>
    #include <pni/type_utils.hpp>

    using namespace pni;

    //get a type id from a string
    string rep = "string";
    type_id_t id = type_id_from_str("str");

    //get a string from a type id
    rep = str_from_type_id(type_id_t::Float32);


.. ===========================================================================

.. _using_binary:

The :cpp:type:`binary` type
===========================

In many cases uninterpreted binary data should be transfered from one location
to the other (a typical example would be to copy the content of one file to
another).
Typically one would use a type alias to something like :cpp:type:`uint8` to
realize such a type. However, this approach has two disadvantages

* as :cpp:type:`uint8` is a numeric type with all arithmetic operators
  available which we do not want for uninterpreted binary data 
* a mere type alias would make :cpp:type:`uint8` and :cpp:type:`binary`
  indistinguishable and thus we could not specialize template classes for 
  each of them.

Consequently :cpp:type:`binary` was implemented as a thin wrapper around an
appropriately sized integer type with all arithmetic operators stripped away.
A short example of how to use binary is the :file:`copy_file.cpp` example in
the :file:`examples` directory of the source distribution of *libpninexus*. 

.. todo:: add here the code of the example file


In lines $8$ and $10$ we include the :file:`pni/types.hpp` header file and
instruct the compiler to use the \texttt{pni} namespace by default. In
line $12$ a vector type with binary elements is defined and an instance of this
type is allocated in line $24$.  In line $27$ data is read from the input file
and stored in the vector. Now, it is clear from here that a vector of type
:cpp:type:`char_t` would have perfectly served the same purpose. The major
difference is that unlike :cpp:type:`char_t` :cpp:type:`binary` has absolutely no
semantics. In practice there is nothing much you can do without it rather than
store it back to another stream as it is done in line $33$.

.. ===========================================================================
.. _using_none:

The :cpp:type:`none` type
=========================

The :cpp:type:`none` type represents the absence of a type. It is a dummy type 
of very limited functionality and is mainly used internally by 
`libpninexus`. One major application of the :cpp:type:`none` type is to do default
construction of type erasures (see :ref:`type_erasures`). 
For all practical purposes this type can be ignored.

.. ===========================================================================
.. _using_bool:

The :cpp:type:`bool_t` type
===========================

Unlike the C programming language C++ provides a native :cpp:type:`bool_t` type.
Unfortunately the C++ standardization committee made some unfortunate decisions
with :cpp:type:`bool_t` and STL containers. :cpp:class:`std::vector` for instance
is in most cases specialized for the standard C++ :cpp:type:`bool_t` type.  In
the most common STL implementation :cpp:class:`std::vector` is considered an
array of individual bits. Meaning that every byte in the vector is storing a
total of *8* :cpp:type:`bool_t` values. Consequently we cannot obtain an address
for a particular bit but only for the byte where it is stored.  Hence
:cpp:class:`std::vector<bool_t>` does not provide the :cpp:func:`data` method
which is required for storage containers used with the :cpp:class:`mdarray`
templates (see :ref:`arrays`). 

To overcome this problem a new boolean type was included in `libpninexus` which
can be converted to :cpp:type:`bool_t` but uses a single byte for each boolean
value and thus can use the :cpp:class:`std::vector` template. So use the
`libpninexus` :cpp:type:`bool_t` type whenever working with `libpninexus`
templates or whenever the address of a container element is required. For all
other purposes the default C++ :cpp:type:`bool_t` type can be used.

.. ===========================================================================

Numeric type conversion
======================= 

`libpninexus` provides facilities for save numeric type conversion. These
functions are not only used internally by the library they are also available to
users.  The conversion policy enforced by `libpninexus` is more strict than that
of standard C++. For instance you cannot convert a negative integer to an
unsigned integer type. The goal of the conversion rules are set up in order to
avoid truncation errors as they would typically occur when using the standard
C++ rules.

The basic rule for conversion between two integer type A and B is as follows

    A value of type :cpp:type:`S` can only be converted to type :cpp:type:`B` 
    if the value does not exceed the numeric range of type :cpp:type:`B`.

A consequence of this rule is that a signed integer can only be converted 
to an unsigned type if its value is larger than 0. This is different 
from the standard C++ rule where the unsigned target type will just overflow. 

The second basic rule which governs `libpninexus` s conversion policy is 
    
    During a conversion no information must be lost!

Hence, conversion from a floating point type to an integer type is prohibited as
it would most likely lead to truncation and thus a loss of information. 
Conversion from a scalar float value to a complex value is allowed (as long as
the first rule applies to the base type of the complex type) but one cannot
convert a complex value to a scalar float type.

Several types cannot be converted to anything than themselves 

* :cpp:type:`bool_t` which can be only the result of a boolean operation.
* :cpp:type:`binary` as this type is considered to be a completely opaque type
  conversion to any other type is prohibited. Furthermore no type can be 
  converted to binary. 
* :cpp:type:`string` conversion to string is done exclusively carried out by 
  formatters provided by the IO library. 

The library distinguishes between two kinds of type conversion
    
unchecked conversion
    the conversion can be done without checking the value

checked conversion 
    the value has to be checked if it fits into the target type.

Table~\ref{tab:types:unchecked_conversions} gives an overview between which
types conversion is possible and whether unchecked or checked conversion will be
used. 

====================== =========  =========  =========  =========  ========= =========  =========  =========  =========  =========  ==========  ===========  ===========  ============
source / target        `uint8`    `uint16`   `uint32`   `uint64`   `int8`    `int16`    `int32`    `int64`    `float32`  `float64`  `float128`  `complex32`  `complex64`  `complex128` 
====================== =========  =========  =========  =========  ========= =========  =========  =========  =========  =========  ==========  ===========  ===========  ============
:cpp:type:`uint8`      unchecked  unchecked  unchecked  unchecked  checked   unchecked  unchecked  unchecked  unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`uint16`     checked    unchecked  unchecked  unchecked  checked   checked    unchecked  unchecked  unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`uint32`     checked    checked    unchecked  unchecked  checked   checked    checked    unchecked  unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`uint64`     checked    checked    checked    unchecked  checked   checked    checked    checked    unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`int8`       checked    checked    checked    checked    unchecked unchecked  unchecked  unchecked  unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`int16`      checked    checked    checked    checked    checked   unchecked  unchecked  unchecked  unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`int32`      checked    checked    checked    checked    checked   checked    unchecked  unchecked  unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`int64`      checked    checked    checked    checked    checked   checked    checked    unchecked  unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`float32`    none       none       none       none       none      none       none       none       unchecked  unchecked  unchecked   unchecked    unchecked    unchecked 
:cpp:type:`float64`    none       none       none       none       none      none       none       none       checked    unchecked  unchecked   checked      unchecked    unchecked 
:cpp:type:`float128`   none       none       none       none       none      none       none       none       checked    checked    unchecked   checked      checked      unchecked 
:cpp:type:`complex32`  none       none       none       none       none      none       none       none       none       none       none        unchecked    unchecked    unchecked 
:cpp:type:`complex64`  none       none       none       none       none      none       none       none       none       none       none        checked      unchecked    unchecked 
:cpp:type:`complex128` none       none       none       none       none      none       none       none       none       none       none        checked      checked      unchecked 
====================== =========  =========  =========  =========  ========= =========  =========  =========  =========  =========  ==========  ===========  ===========  ============

Type matrix showing between which types  conversion is possible. 

The :cpp:func:`convert` function template
-----------------------------------------

At the heart of `libpninexus` s type conversion system is the \cpp{convert}
function template. The declaration of the template looks somehow like this

.. code-block:: cpp

    template<typename SourceT,typename TargetT> TargetT convert(const SourceT &v);

A value of a particular source type (denoted by the template parameter 
:cpp:type:`SourceT`) is passed as an argument to the :cpp:func:`convert` template. The value 
of this argument will then be converted to a value of the target type 
:cpp:type:`TargetT` and returned from the function template. 
This function template throws two exceptions

======================= =========================================================
exception               reason
======================= =========================================================
:cpp:type:`type_error`  in situations where the type conversion is not possible 
:cpp:type:`range_error` where the source value does not fit into the target type
======================= =========================================================

The behavior of this function can best be demonstrated examples. 
.. code-block:: cpp

    auto f = convert<float32>(int32(5)); 

In this example a value of type :cpp:type:`int32` is successfully converted 
to a value of type :cpp:type:`float32`, while

.. code-block:: cpp

    auto f = convert<uint16>(float32(-5)); // throws type_error

leads to :cpp:type:`type_error`. According to the conversion policies mentioned
above a float value cannot be converted to an integer due to truncation issues. 

.. code-block:: cpp

    auto f = convert<uint32>(int32(-3)); //throws range_error

:cpp:type:`range_error` will be thrown as a negative value cannot be converted to an 
unsigned type. A similar situation would be 

.. code-block:: cpp

    auto f = convert<uint8>(int16(10000)); //throws range_error

where :cpp:type:`range_error` would indicate that it is impossible to store a
value of 10000 in an 8-Bit unsigned variable.



