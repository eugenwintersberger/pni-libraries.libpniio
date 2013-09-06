/*
 * cbf_reader_test.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger
 */

//Testing program for the CBF reader

#include<iostream>
#include<typeinfo>
#include<cmath>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkFloatArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkImageViewer2.h>

#include <pni/core/io/CBFReader.hpp>
#include <pni/core/Array.hpp>

using namespace pni::core;
using namespace pni::io;

typedef F32DArray Frame;


void plot_image(const Frame &array)
{
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *window = vtkRenderWindow::New();
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
    vtkImageViewer2 *viewer = vtkImageViewer2::New();

    vtkFloatArray *ia = vtkFloatArray::New();
    ia->SetArray((float *)array.storage().ptr(),array.size(),1);
    vtkImageData *idata = vtkImageData::New();
    idata->GetPointData()->SetScalars(ia);
    idata->SetDimensions(array.shape<shape_t>()[1],array.shape<shape_t>()[0],1);
    idata->SetScalarType(VTK_FLOAT);
    idata->SetSpacing(1.0,1.0,1.0);
    idata->SetOrigin(0,0,0);

    viewer->SetInput(idata);
    viewer->SetZSlice(0);
    viewer->SetupInteractor(interactor);
    viewer->Render();
    interactor->Start();

    //cleanup everything
    renderer->Delete();
    window->Delete();
    interactor->Delete();

}

int main(int argc,char **argv){

    if(argc<2){
        std::cerr<<"Usage: cbf_reader_test <filename>"<<std::endl;
        return -1;
    }

    //get the name of the file to copen
    String file_name(argv[1]);


    CBFReader reader(file_name);
    ImageInfo info = reader.info(0);
    std::cout<<info<<std::endl;

    Frame::storage_type buffer;
    try
    {
        buffer = reader.image<Frame::storage_type>(0);
    }
    catch(IteratorError &error)
    {
        std::cout<<error<<std::endl;
        return -1;
    }
    Frame a(shape_t({info.nx(),info.ny()}),buffer);
    plot_image(a);

    reader.close();

    return 0;
}
