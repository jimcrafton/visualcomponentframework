/*
 *  OSXCustomControl.cpp
 *  vcfAllProjects
 *
 *  Created by Jim on 6/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */



/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXControl.h"
#include "vcf/ApplicationKit/OSXCustomControl.h"
#include "vcf/ApplicationKit/WindowPeer.h"
#include "vcf/ApplicationKit/OSXLightweightControl.h"
#include "vcf/ApplicationKit/OSXWindow.h"
#include "vcf/ApplicationKit/OSXCursorPeer.h"


namespace VCF {

OSXCustomControl::OSXCustomControl( Control* control ):
	OSXControl(control)
{

}

OSXCustomControl::~OSXCustomControl()
{

}

void OSXCustomControl::create( Control* owningControl )
{
	NSRect r;
	r.origin.x = 0;
	r.origin.y = 0;
	r.size.width = 1;
	r.size.height = 1;	
	view_ = [[VCFControlView alloc] initWithFrame:r];
	
	OSXControl::create( owningControl );
}

void OSXCustomControl::destroyControl()
{
	OSXControl::destroyControl();
}


};