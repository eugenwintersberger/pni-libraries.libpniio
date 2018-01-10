============================
Spreadsheet like ASCII files
============================

Many ASCII formats use a speadsheet like scheme to organize their data, 
basically storing data in rows and columns. Some formats like SPEC allow 
to store multiple runs in a single file (SPEC calls them scans) while others, 
like FIO, store only a single run per file and endcode the run number in the 
file name. 

.. figure:: ../images/data_readers.svg
   :align: center
   :width: 65%
   
   Hierarchy of reader classes in *libpniio*.
   
Spreadsheet readers favor column based over record based access. Not only 
is this the typical way how data is accessed in the field of synchrotron 
research, it has also the advantage that the data type is constant within 
every column and  thus standard containers can be used. 

FIO file support
================

FIO is the old file format used at DESY. Every run (sometimes called scan) is
stored in a single file where the run number is encoded in the name of the file.
A FIO file can be roughly divided into three sections 

* a *comment* section (starting with ``%c``) at the very top of the file 
* a *parameters* section (starting with ``%p``) storing all kinds of meta-data 
  and data not altered during the run in a key-value kind fashion
* a *data* section (starting with ``%d``) with a spreadsheet like layout. 

A comment line in FIO starts with a ``!``. The *data* section itself has two 
parts

* a set of *column descriptors* associating each column with a name and data 
  type
* the data itself. 

The following snippet shows a shortened example for a FIO file.  

.. code-block:: text

   !
   ! Comments 
   %c 
    EXAFS-Scan started at 1-Feb-2003 20:51:31  
    Name: tio2_kronos_0001 from 4750 to 5898.058  
    Offsets (already subtracted):  
    C1 2193 C2 2495 C3 617 C4 0 C6 0 C7 0 C8 0 C9 0 C11 0 C12 0 C13 0  
    C14 0  
   !
   ! Parameter 
   %p 
    EXIT_SL_T = -0.35 
    ... data omitted ...
    SAMPLE = sample 
    IDORIS = 116.04 
   !
   ! Data 
   %d 
    Col 1 TIO2_KRONOS_0001  FLOAT 
    Col 2 TIO2_KRONOS_0001  FLOAT 
    Col 3 TIO2_KRONOS_0001_RING  FLOAT 
    Col 4 TIO2_KRONOS_0001_POS_RIN  FLOAT 
    Col 5 TIO2_KRONOS_0001_POS_EXP  FLOAT 
    Col 6 TIO2_KRONOS_0001_WERT_HHE1  DOUBLE 
    Col 7 TIO2_KRONOS_0001_WERT_HHE2  DOUBLE 
    ... data omitted ...
    Col 23 TIO2_KRONOS_0001_C13  FLOAT 
    Col 24 TIO2_KRONOS_0001_C14  FLOAT 
    Col 25 TIO2_KRONOS_0001_STEPS  FLOAT 
              4750      5.353544      116.1377  -0.008544922  -0.003662109 7.19041552734375e+01 -7.24616992187500e+01 4.75017769741682e+03 0.00000000000000e+00             5             3             0        426446      2017.667     -40.66667             0             1             0      4.666667      3.333333           169           944      727.6667      803.3333       3091011 
              4755      5.343097        116.04  -0.008544922  -0.003662109 7.19314086914062e+01 -7.24616894531250e+01 4.75511986862183e+03 0.00000000000000e+00             5             3             0      426406.3      2038.667     -45.33333             0      6.333333             0      4.666667      3.666667           201           942      695.3333      789.3333       3096532 
              4760      5.328669      116.2354  -0.008544922  -0.003662109 7.19584545898438e+01 -7.24616943359375e+01 4.76003483996449e+03 0.00000000000000e+00             5             3             0        426346          2068     -41.66667             0     0.6666667             0      4.666667      4.666667      148.3333           941           727      804.6667       3102040 
              4765       5.31495      116.1377  -0.008544922  -0.003662109 7.19854394531250e+01 -7.24616918945313e+01 4.76495268584383e+03 0.00000000000000e+00             5             3             0      426298.3      2096.333     -38.66667             0     0.3333333             0      2.333333      2.666667      156.6667           962      722.3333           835       3107535 
              4770      5.302732       116.333  -0.008544922   0.001220703 7.20128271484375e+01 -7.24616845703125e+01 4.76995088467423e+03 0.00000000000000e+00             5             3             0      426277.7          2122     -41.66667             0      3.333333             0             2      7.666667      199.3333      962.6667      739.6667      836.6667       3113017
            
In order to read FIO files use the :cpp:class:`pni::io::fio_reader`. 
Opening a FIO file works as with any other reader 

.. code-block:: cpp

   pni::io::fio_reader reader("run_000001.fio");
   
Accessing parameters
--------------------

Accessing parameters (stored as key value pairs) is done via the 
:cpp:func:`parameter` template member function. Its template parameter determines
the requested data type for the parameter value

.. code-block:: cpp

   pni::io::fio_reader reader("run_0000001.fio");
   
   std::cout<<reader.parameter<pni::core::float32>("IDORIS")<<std::endl;
   
Accessing columns
-----------------

Columns are accessed via the :cpp:func:`column` template member function 
where the template parameter is typically the container type used to 
store the column data

.. code-block:: cpp

   using Float64Column = std::vector<pni::core::float64>;
   
   pni::io::fio_reader reader("run_0000001.fio");
   
   auto column = reader.column<Float64Column>("OMEGA");
   
the column itself is determined by its name which is passed as the sole 
argument to :cpp:func:`column`.




            