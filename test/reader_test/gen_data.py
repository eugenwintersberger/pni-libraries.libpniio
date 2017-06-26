#!/bin/env python

from PIL import Image
import tifffile
import numpy 


dui8 = numpy.array([[1,2,3,4],[2,4,6,8]],dtype="uint8")
di8  = numpy.array([[-1,2,-3,4],[2,-4,6,-8]],dtype="int8")

di32 = numpy.array([[-100,200,-300,400],[200,-400,600,-800]],dtype="int32")
dui32 = numpy.array([[100,200,300,400],[200,400,600,800]],dtype="uint32")

#----------------------write the image data--------------------------------
Image.fromarray(dui8).save('iui8.tiff','TIFF')
Image.fromarray(di8).save('ii8.tiff','TIFF')

Image.fromarray(di32).save('ii32.tiff','TIFF')
tifffile.imsave('ui32.tiff',dui32)
