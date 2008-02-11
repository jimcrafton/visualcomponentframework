#ifndef _VCF_GRAPHICSKIT_H__
#define _VCF_GRAPHICSKIT_H__
//GraphicsKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/FoundationKit.h"

#include "vcf/GraphicsKit/GraphicsKitSelectLib.h"

#include "vcf/GraphicsKit/Point.h"
#include "vcf/GraphicsKit/Size.h"
#include "vcf/GraphicsKit/Rect.h"

#include "vcf/GraphicsKit/Color.h"

#include "vcf/GraphicsKit/ImageEvent.h"
#include "vcf/GraphicsKit/Image.h"

#include "vcf/GraphicsKit/GraphicsToolKit.h"
#include "vcf/GraphicsKit/Pixels.h"

#include "vcf/GraphicsKit/NoGraphicsToolkitFoundException.h"

#include "vcf/GraphicsKit/Stroke.h"
#include "vcf/GraphicsKit/Fill.h"
#include "vcf/GraphicsKit/Matrix2D.h"
#include "vcf/GraphicsKit/ContextPeer.h"
#include "vcf/GraphicsKit/GraphicsContext.h"

#include "vcf/GraphicsKit/ImageLoader.h"
#include "vcf/GraphicsKit/Path.h"
#include "vcf/GraphicsKit/BezierCurve.h"
#include "vcf/GraphicsKit/Ellipse.h"
#include "vcf/GraphicsKit/Circle.h"
#include "vcf/GraphicsKit/Font.h"
#include "vcf/GraphicsKit/FontPeer.h"

#include "vcf/GraphicsKit/PrintContext.h"
#include "vcf/GraphicsKit/Printable.h"
#include "vcf/GraphicsKit/InvalidImage.h"
#include "vcf/GraphicsKit/ImageLoaderException.h"
#include "vcf/GraphicsKit/AbstractImage.h"

#include "vcf/GraphicsKit/BasicFill.h"
#include "vcf/GraphicsKit/BasicStroke.h"
#include "vcf/GraphicsKit/ContextPeer.h"

//graphics resources
#include "vcf/GraphicsKit/GraphicsResourceBundle.h"

//printing
#include "vcf/GraphicsKit/PrintEvent.h"
#include "vcf/GraphicsKit/PrintSession.h"



/**
\class GraphicsKit GraphicsKit.h "vcf/GraphicsKit/GraphicsKit.h"
*initializes the graphics Kit runtime.
*This includes registering the basic classes in the runtime system
*This MUST be called first off, after the initFoundationKit, in the main() function of the app
*/
namespace VCF
{
	class GRAPHICSKIT_API GraphicsKit
	{
	public:
		/**
		*Initialization takes place here, plus creating the various
		*system resources and peer instances
		*/
		static void init( int argc, char** argv );

		/**
		*Frees up any resource allocated in init();
		*/
		static void terminate();
	};
}; // end of namespace


#endif // _VCF_GRAPHICSKIT_H__

/**
$Id$
*/
