#ifndef _VCF_SPLITTER_H__
#define _VCF_SPLITTER_H__
//Splitter.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define SPLITTER_CLASSID		"e06c4170-04d7-4ba5-84ff-d1718d7b2a9d"


namespace VCF  {

/**
\class Splitter Splitter.h "vcf/ApplicationKit/Splitter.h"
*Class Splitter documentation
*/
class APPLICATIONKIT_API Splitter : public CustomControl {
public:

	Splitter( const AlignmentType& alignment = AlignLeft );
	virtual ~Splitter();

	void init();

	virtual void mouseDown( MouseEvent* e );

	virtual void mouseMove( MouseEvent* e );

	virtual void mouseUp( MouseEvent* e );

	virtual void mouseDblClick( MouseEvent* e );

	virtual void paint( GraphicsContext* ctx );

	bool getDblClickEnabled() {
		return dblClickEnabled_;
	}
	void setDblClickEnabled( const bool& dblClickEnabled ) {
		dblClickEnabled_ = dblClickEnabled;
	}

	void setAlignment( const AlignmentType& alignment );

	void setMinimumWidth( const double& _minimumWidth );
	double getMinimumWidth();

	virtual double getPreferredHeight();
	virtual double getPreferredWidth();

protected:
	/**
	this is the function doing the real job
	*/
	void updateAttachedControl( Point& pt, const bool& shiftAll = false );

	/**
	this is the function doing the real job when double clicking with the mouse
	*/
	void updateAttachedControlJump( Point& pt, const bool& shiftAll = false );

protected:
	Control* attachedControl_;
	Point dragPoint_;
	Light3DBorder bdr_;
	Control* attachedControlAlt_;
	Control* outmostControl_;
	double deltaRestore_;
	double deltaRestoreAlt_;
	double minimumWidth_;
	bool dblClickEnabled_;

private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/06/28 20:14:11  marcelloptr
*first step to remove flickering when dragging a splitter
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.5  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.9.4.4  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9.4.3  2003/09/06 19:45:45  ddiego
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
*Revision 1.9.4.2  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.9.4.1  2003/08/26 21:41:30  ddiego
*miscellanesous stuff, minor bugs
*
*Revision 1.9  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.16.1  2003/03/12 03:09:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.7  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SPLITTER_H__


