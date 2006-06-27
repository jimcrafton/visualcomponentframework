#ifndef _VCF_MULTILINETEXTCONTROL_H__
#define _VCF_MULTILINETEXTCONTROL_H__
//MultilineTextControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TEXTCONTROL_H__
#include "vcf/ApplicationKit/TextControl.h"
#endif // _VCF_TEXTCONTROL_H__



#define MULTILINETEXTCONTROL_CLASSID		"5e9c50e2-f9fc-46d8-9439-cf182d212df3"


namespace VCF  {

/**
\class MultilineTextControl MultilineTextControl.h "vcf/ApplicationKit/MultilineTextControl.h"
*Class MultilineTextControl documentation
*/
class APPLICATIONKIT_API MultilineTextControl : public TextControl {
public:

	MultilineTextControl();

	virtual ~MultilineTextControl();

	String getTextForLine( const uint32& lineIndex );

	void scrollToLine( const uint32& lineIndex );

	void scrollToSelection( const bool& _showEndSel = false );

	virtual bool supportsMultiLinedText() {
		return true;
	}

	virtual void gotFocus( FocusEvent* event );
protected:

private:
};


}; //end of namespace VCF


#endif // _VCF_MULTILINETEXTCONTROL_H__

/**
$Id$
*/
