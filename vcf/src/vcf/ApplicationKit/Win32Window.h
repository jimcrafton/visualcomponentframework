#ifndef _VCF_WIN32WINDOW_H__
#define _VCF_WIN32WINDOW_H__
//Win32Window.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/WindowPeer.h"


namespace VCF
{

class Win32Window : public AbstractWin32Component, public WindowPeer
{
public:
	Win32Window();

	Win32Window( Control* component, Control* owner );

	virtual ~Win32Window();

	virtual void create( Control* owningControl );

	virtual void setText( const String& text );

	virtual void setBounds( VCF::Rect* rect );

	virtual void setVisible( const bool& visible );

	virtual void setParent( VCF::Control* parent );

	virtual Rect getClientBounds();

	virtual void  setClientBounds( Rect* bounds );

	virtual Win32Object::CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual void close();

	virtual void setFrameStyle( const FrameStyleType& frameStyle );

	virtual void setFrameTopmost( const bool& isTopmost );

	virtual bool isMaximized();

	virtual void setMaximized( const bool maximised );

	virtual bool isMinimized();

	virtual void setMinimized( const bool& minimized );

	virtual void restore();

	virtual void setIconImage( Image* icon );

	virtual bool isActiveWindow();
protected:
	bool activatesPending_;
	bool internalClose_;
	Control* owner_;

	void handleActivate();
};


};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:59  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.2  2005/06/29 05:15:41  marcelloptr
*fixed some white spaces
*
*Revision 1.3.2.1  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.21.4.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.21  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.20.2.2  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.20.2.1  2003/08/18 19:52:36  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.20  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.19.2.1  2003/05/27 04:45:32  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.19  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.18.2.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.18.2.1  2003/03/12 03:11:37  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.18  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.17.14.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.17  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.16.4.1  2002/04/27 15:52:20  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.16  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32WINDOW_H__


