#ifndef _VCF_OSXCUSTOMCONTROL_H__
#define _VCF_OSXCUSTOMCONTROL_H__
//OSXCustomControl.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF {
	
class OSXCustomControl : public OSXControl {
public:
	OSXCustomControl( Control* control );

	virtual ~OSXCustomControl();

	virtual void create( Control* owningControl );

	virtual void destroyControl();
};
	

};


#endif //_VCF_OSXCUSTOMCONTROL_H__