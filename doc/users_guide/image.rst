=========================
Reading binary image data
=========================

The image model
===============

The image model used by *libpniio* is rather simple. We assume that an image 
is a regular 2 dimensional array with *nx* elements along the first dimension
and *ny* elements along the second dimension. 
In general the x-direction is the slow direction and the y-direction the 
fast one. This means typically that *nx* is typically associated with the 
number of rows or strips of an image and *ny* with the number of pixels 
per strip or row. 

The elements on the images grid are pixels. Every pixel is again 
subdivided in a set of *channels*. For instance an RGB image would have a 
*red-*, *green-* and *blue-channel*. Additionally a file can store 
multiple images (for instance TIFF). The interface takes care about this. 

The base class for all image readers is :cpp:class:`image_reader`. In addition
there are two additional classes providing basic image meta-data

* :cpp:class:`image_info` - with general information about an image (number of 
  pixels along each dimension, total number of bits per pixel)
* and :cpp:class:`image_channel_info` - providing information about the 
  individual channels stored in each image. 

Image reader
============

Currently there are two classes implementing the :cpp:class:`image_reader` 
interface:

* :cpp:class:`pni::io::tiff_reader` for reading TIFF files 
* and :cpp:class:`pni::io::cbf_reader` to read CBF files. 

As both have a similar interface only the CBF reader will be discussed 
here. 

In order to use the CBF reader you have to include 
:file:`pni/cbf/cbf_reader.hpp` in your source file (for the TIFF reader 
use :file:`pni/tiff/tiff_reader.hpp`). 

.. code-block:: cpp

   #include <pni/cbf/cbf_reader.hpp>
   #include <pni/image_info.hpp>
   
   pni::io::cbf_reader reader("image_00001.cbf");
   
We can check whether there are several images in the file and have a 
look on their basic structure with 

.. code-block:: cpp

   for(size_t index=0;index<reader.nimages();index++)
      std::cout<<reader.info(index)<<std::endl; 
      
To read data we could use 

.. code-block:: cpp

   using Frame = std::vector<pni::core::float32>;
   
   //read the first channel from the first image in the file
   auto frame = reader.image<Frame>(0,0);

   