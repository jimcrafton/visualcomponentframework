#ifndef _VCF_GTKCONTROL_H__
#define _VCF_GTKCONTROL_H__
//GTKControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#ifndef _VCF_ABSTRACTGTKCONTROL_H__
#	include "vcf/ApplicationKit/AbstractGTKControl.h"
#endif // _VCF_ABSTRACTGTKCONTROL_H__

namespace VCF {

/**

*/
class GTKControl : public AbstractGTKControl {
public:

	GTKControl( Control* control );

	virtual ~GTKControl();

	virtual void create( Control* owningControl );

	virtual void setBorder( Border* border );

protected:

};

}


#endif // _VCF_GTKCONTROL_H__

/**
$Id$
*/
