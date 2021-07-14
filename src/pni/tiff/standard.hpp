//
// (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of libpninexus.
//
// libpninexus is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// libpninexus is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libpninexus.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Created on: Jun 17, 2011
//     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//
//
#pragma once

#include <map>
#include <pni/types.hpp>

namespace pni{
namespace io{
namespace tiff{

    //-------------------------------------------------------------------------    
    std::map<pni::uint16,pni::string> tiff_tag_name_map = 
    {
        {254,"NewSubfileType"},
        {255,"SubfileType"},
        {256,"ImageWidth"},
        {257,"ImageLength"},
        {258,"BitsPerSample"},
        {259,"Compression"},
        {262,"PhotometricInterpretation"},
        {263,"Threshholding"},
        {264,"CellWidth"},
        {265,"CellLength"},
        {266,"FillOrder"},
        {269,"DocumentName"},
        {270,"ImageDescription"},
        {271,"Make"},
        {272,"Model"},
        {273,"StripOffsets"},
        {274,"Orientation"},
        {277,"SamplesPerPixel"},
        {278,"RowsPerStrip"},
        {279,"StripByteCounts"},
        {280,"MinSampleValue"},
        {281,"MaxSampleValue"},
        {282,"XResolution"},
        {283,"YResolution"},
        {284,"PlanarConfiguration"},
        {285,"PageName"},
        {286,"XPosition"},
        {287,"YPosition"},
        {288,"FreeOffsets"},
        {289,"FreeByteCounts"},
        {290,"GrayResponseUnit"},
        {291,"GrayResponseCurve"},
        {292,"T4Options"},
        {293,"T6Options"},
        {296,"ResolutionUnit"},
        {297,"PageNumber"},
        {301,"TransferFunction"},
        {305,"Software"},
        {306,"DateTime"},
        {315,"Artist"},
        {316,"HostComputer"},
        {317,"Predictor"},
        {318,"WhitePoint"},
        {319,"PrimaryChromaticities"},
        {320,"ColorMap"},
        {321,"HalftoneHints"},
        {322,"TileWidth"},
        {323,"TileLength"},
        {324,"TileOffsets"},
        {325,"TileByteCounts"},
        {332,"InkSet"},
        {333,"InkNames"},
        {334,"NumberOfInks"},
        {336,"DotRange"},
        {337,"TargetPrinter"},
        {338,"ExtraSamples"},
        {339,"SampleFormat"},
        {340,"SMinSampleValue"},
        {341,"SMaxSampleValue"},
        {342,"TransferRange"},
        {512,"JPEGProc"},
        {513,"JPEGInterchangeFormat"},
        {514,"JPEGInterchangeFormatLength"},
        {515,"JPEGRestartLevel"},
        {517,"JPEGLosslessPredictors"},
        {518,"JPEGPointTransforms"},
        {519,"JPEGQTables"},
        {520,"JPEGDCTables"},
        {521,"JPEGACTables"},
        {529,"YCbCrCoefficients"},
        {530,"YCbCrSubSampling"},
        {531,"YCbCrPositioning"},
        {532,"ReferenceBlackWhite"},
        {33432,"Copyright"} };

    //-------------------------------------------------------------------------
    std::map<pni::uint16,pni::string> tiff_compression_tag_map = 
    {
        {1,"Uncompressed"}, {2,"CCITT 1D"},
        {3,"Group 3 Fax"}, {4,"Group 4 Fax"},
        {5,"LZW"}, {6,"JPEG"}, {32773,"PackBits"}
    };

    //-------------------------------------------------------------------------
    std::map<pni::uint16,pni::string> tiff_photo_tag_map= 
    {
        {0,"WhiteIsZero"}, {1,"BlackIsZero"},
        {2,"RGB"}, {3,"RGB Palette"},
        {4,"Transparency mask"}, {5,"CMYK"},
        {6,"YCbCr"}, {8,"CIELab"}
    };

    //end of namespace
}
}
}
