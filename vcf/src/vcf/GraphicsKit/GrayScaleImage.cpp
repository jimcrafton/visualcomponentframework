//GrayScaleImage.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GrayScaleImage.h"


using namespace VCF;

GrayScaleImage::GrayScaleImage( const bool& needsMemAlloc ):
	AbstractImage(needsMemAlloc)
{

}

GrayScaleImage::~GrayScaleImage()
{

}

void GrayScaleImage::setSize( const uint32 & width, const uint32 & height )
{
	AbstractImage::setSize( width, height );
}


/**
$Id$
*/
