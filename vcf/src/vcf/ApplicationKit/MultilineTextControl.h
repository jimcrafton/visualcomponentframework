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

	String getTextForLine( const ulong32& lineIndex );

	void scrollToLine( const ulong32& lineIndex );

	void scrollToSelection( const bool& _showEndSel = false );

	virtual bool supportsMultiLinedText() {
		return true;
	}

	virtual void gotFocus( FocusEvent* event );
protected:

private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.4.2  2006/03/21 00:57:35  ddiego
*fixed bug in table control - problem was really with casting a
*model to a table model, and having the pointer value not be right. Needed
*to use dynamic_cast() to fix it. Curiously this problem was not flagegd in
*debug at all.
*
*Revision 1.3.4.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/03 22:47:33  ddiego
*fixed a text model bug that incorectly handled deleting chars.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.20.3  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.7.20.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7.20.1  2003/08/12 20:30:32  marcelloptr
*improvement: multiline editor - scrollToSelection
*
*Revision 1.7  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/04/27 15:42:44  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_MULTILINETEXTCONTROL_H__


