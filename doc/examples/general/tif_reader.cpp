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

#include <pni/utils/Array.hpp>
#include <pni/utils/io/TIFFReader.hpp>

using namespace pni::utils;

typedef F32DArray Frame;

void plot_image(const Frame &array)
{
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindow *window = vtkRenderWindow::New();
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
    vtkImageViewer2 *viewer = vtkImageViewer2::New();

    vtkFloatArray *ia = vtkFloatArray::New();
    ia->SetArray((Float32 *)array.storage().ptr(),array.size(),1);
    vtkImageData *idata = vtkImageData::New();
    idata->GetPointData()->SetScalars(ia);
    idata->SetDimensions(array.shape()[1],array.shape()[0],1);
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

using namespace pni::io;

int main(int argc,char **argv){

    if(argc<2){
        std::cerr<<"usage: tif_reader_test <filename>"<<std::endl;
    	return -1;
    }

    //open file for reading
    String filename(argv[1]);
    TIFFReader reader(filename);

    std::cout<<"number of images: "<<reader.nimages()<<std::endl;
    std::cout<<reader<<std::endl;
    std::cout<<reader.info(0)<<std::endl;
    
    
    auto buffer = reader.image<Frame::storage_type>(0);
    Frame array(shape_t({reader.info(0).nx(),reader.info(0).ny()}),
                       buffer);
    //close the reader object when we are done
    plot_image(array);

    return 0;
}
