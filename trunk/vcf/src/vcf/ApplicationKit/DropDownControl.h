#ifndef _VCF_DROPDOWNCONTROL_H__
#define _VCF_DROPDOWNCONTROL_H__
//DropDownControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_LISTCONTROL_H__
#	include "vcf/ApplicationKit/ListControl.h"
#endif // _VCF_LISTCONTROL_H__



#define DROPDOWNCONTROL_CLASSID		"a9122105-8b75-4567-903a-9e1f70cd9a7f"

namespace VCF { 

class DropDownPeer;

/**
\class DropDownControl DropDownControl.h "vcf/ApplicationKit/DropDownControl.h"

*/
class APPLICATIONKIT_API DropDownControl : public ListControl {
public:
	DropDownControl();

	virtual void paint( GraphicsContext* context );

	void setEditText( const String& text );
	
	String getEditText();

	void setDropDownWidth( const double& val );

	double getDropDownWidth();

	void setDropDownCount( const uint32& dropDownCount );

	uint32 getDropDownCount();

	void enableEditBox( const bool& val );

	bool editBoxEnabled();
protected:

	DropDownPeer* dropDownPeer_;
};

};

#endif //_VCF_DROPDOWNCONTROL_H__