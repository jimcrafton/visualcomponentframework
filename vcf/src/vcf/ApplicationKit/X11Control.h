#ifndef _VCF_X11CONTROL_H__
#define _VCF_X11CONTROL_H__
//X11Control.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_ABSTRACTX11CONTROL_H__
#	include "vcf/ApplicationKit/AbstractX11Control.h"
#endif // _VCF_ABSTRACTX11CONTROL_H__



/**
For unusual looking typedefs please see the vcf/ApplicationKit/X11Peer.h
*/

namespace VCF {


/**

*/
class X11Control : public Object, public AbstractX11Control {
public:

	X11Control( Control* control );

	virtual ~X11Control();

protected:

};



};


#endif // _VCF_X11CONTROL_H__

/**
$Id$
*/
