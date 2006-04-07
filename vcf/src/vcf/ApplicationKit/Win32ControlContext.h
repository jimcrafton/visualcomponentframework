#ifndef _VCF_WIN32CONTROLCONTEXT_H__
#define _VCF_WIN32CONTROLCONTEXT_H__
//Win32ControlContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class ControlPeer;

class ControlGraphicsContext;

class Control;


/**
* implementation of the peer for Win32 of the GraphicsContext
* 
* To paint inside a mouse move event it is necessary to use the HDC (device 
* context handle) given by ::getDC( hwnd ) where hwnd is the HWND of the control.
* 
* To paint inside a WM_PAINT message it is necessary to use the HDC 
* given by the system with the message itself.
* 
* We CANNOT count on the HDC that we get from WM_PAINT being the same 
* as the HDC we get from GetDC.
* 
* All of this is done automatically by checkHandle()/releaseHandle() members 
* of this class, that by doing:
* \code
* HDC dc = (HDC) getContext()->getPeer()->getContextID();
* \endcode
* make us confident that we alwyas have the HDC we need.
* 
* During a paint operation it is necessary to use the HDC 
* given by the system with the message itself, so before the paint
* it is necessary to modify the instance of this class so
* that getOwningControl() returns NULL and then checkHandle()
* and releaseHandle() become no-op functions.
*
*@see AbstractWin32Component::doControlPaint
*/
class Win32ControlContext : public  Win32Context{
public:

	Win32ControlContext( ControlPeer* controlPeer );

	virtual ~Win32ControlContext();

	/**
	* sets the Graphics context to be currently used 
	* for Graphics operations.
	*/
	virtual void setContext( GraphicsContext* context );

	/**
	* gets the control to which is associated the Graphics 
	* context to be currently used for Graphics operations.
	*@return Control*, the control owning the Graphics context.
	*/
	Control* getOwningControl();

	/**
	* make sure we always have the HDC ( device context handle ) we need.
	* If the owningControl of the Graphics context is not NULL,
	* it gets the device context from its HWND.
	* It hte control is lightWeight it is also necessary to set 
	* the viewport correctly and this too is done here.
	* @see releaseHandle()
	*/
	virtual void checkHandle();

	/**
	* Does the opposite operation of checkHandle(), i.e. restores
	* the previous HDC if it has been changed by checkHandle().
	* @see checkHandle()
	*/
	virtual void releaseHandle();

protected:
	/**
	* the Graphics Context associated to the control 
	* that is owning the Graphics Context we need.
	* When doing any Graphics operation the suited HDC 
	* changes according to the operation to perform.
	* If the Graphics operation needs to be extracted 
	* from the HWND of a control, then the owningControl
	* of this Graphics Context is not NULL and we need
	* to get the HDC from it.
	*/
	ControlGraphicsContext* owningControlCtx_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.4.1  2006/03/18 22:17:42  ddiego
*removed par tag for doxygen comments as its not needed and
*screws up the doc formatting.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/07 19:32:19  marcelloptr
*more documentation
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/12 03:11:11  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.20.1  2003/01/08 00:19:46  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32CONTROLCONTEXT_H__


