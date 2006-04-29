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


#endif // _VCF_WIN32CONTROLCONTEXT_H__

/**
$Id$
*/
