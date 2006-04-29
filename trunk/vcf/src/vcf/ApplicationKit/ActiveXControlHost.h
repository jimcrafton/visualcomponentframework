#ifndef _VCF_ACTIVEXCONTROLHOST_H__
#define _VCF_ACTIVEXCONTROLHOST_H__
//ActiveXControlHost.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/CustomControl.h"

namespace VCF
{

/**
 * This is a control that can host other ActiveX controls. This will have to implement whatever
 *functionality is neccesary on an ActiveX site container.
 *
 *@version 1.0
 *@author Jim Crafton
 */
class ActiveXControlHost :  public VCF::CustomControl{
public:
	virtual ~ActiveXControlHost(){};
};

};


#endif // _VCF_ACTIVEXCONTROLHOST_H__

/**
$Id$
*/
