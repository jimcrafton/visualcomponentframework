#ifndef _VCF_LABEL_H__
#define _VCF_LABEL_H__
//Label.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{


enum TextVerticalAlignment {
	tvaTextTop=0,
	tvaTextCenter,
	tvaTextBottom
};

static String TextVerticalAlignmentNames[] = { "tvaTextTop", "tvaTextCenter", "tvaTextBottom" };

#define LABEL_CLASSID			"ED88C09F-26AB-11d4-B539-00C04F0196DA"

class APPLICATIONKIT_API Label :  public VCF::CustomControl {
public:


	Label();

	virtual ~Label(){};

    virtual void paint(GraphicsContext * context);

	void setCaption( const String& caption );

	String getCaption();

	virtual void setName( const String& name );

	TextAlignmentType getTextAlignment() {
		return textAlignment_;
	}

	void setTextAlignment( const TextAlignmentType& textAlignment );

	TextVerticalAlignment getVerticalAlignment() {
		return textVerticalAlignment_;
	}

	void setVerticalAlignment( const TextVerticalAlignment& verticalAlignment );

	Control* getFocusControl() {
		return focusControl_;
	}

	void setFocusControl( Control* focusControl );

	bool getWordWrap() {
		return wordWrap_;
	}

	void setWordWrap( const bool& wordWrap );

	virtual void mnemonicActivate();

	virtual double getPreferredHeight();

	virtual double getPreferredWidth();
private:
    String caption_;
	TextAlignmentType textAlignment_;
	TextVerticalAlignment textVerticalAlignment_;
	Control* focusControl_;
	bool wordWrap_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/09/15 02:39:20  ddiego
*fixed a bug in the declaration of the caption member variable that was incorrectly declared as a std::string when it should have been a String. This causing bad display character to show up. Many, many, many thanks to Duff(Eddie) for tracking this down! Also many thanks to Marcello for catching and fixing this in the current dev branch.
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
*Revision 1.14.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.4.4  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.13.4.3  2003/10/07 21:26:05  ddiego
*minor adj to listview to get selected item correctly
*
*Revision 1.13.4.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.13.4.1  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.13  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.1  2003/03/12 03:09:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.2.2  2002/12/27 23:04:31  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.11.2.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.11  2002/11/18 00:46:07  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.10.10.1  2002/09/28 02:37:26  ddiego
*fixed up the radiobox and checkbox, label and header controls to properly
*take advantage of default heights from the UIMetricsManager
*fixed the default height for radioboxes and checkboxes in Win32 so that they are
*10 dialog units high - added the neccessary conversion code from dialog
*units to pixels
*
*Revision 1.10  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/04/27 15:42:38  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.9  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LABEL_H__


