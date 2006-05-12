//GraphicsKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"

#include "vcf/FoundationKit/RTTIMacros.h"

#include "vcf/GraphicsKit/GraphicsKitRTTI.inl"

using namespace VCF;


//put global C++ objects here

GraphicsToolkit* GraphicsToolkit::graphicsToolkitInstance = NULL;




void GraphicsKit::init( int argc, char** argv )
{
	FoundationKit::init( argc, argv );

	REGISTER_CLASSINFO_EXTERNAL( Rect );
//	REGISTER_CLASSINFO_EXTERNAL( ImageBits );
	REGISTER_CLASSINFO_EXTERNAL( Color );
	REGISTER_CLASSINFO_EXTERNAL( Font );

	GraphicsToolkit::initGraphicsToolkit();
}


void GraphicsKit::terminate()
{
	GraphicsToolkit::terminate();

	FoundationKit::terminate();
}


/**
$Id$
*/
