#ifndef _VCF_WIN32TRANSPARENTWINDOWPEER_H__
#define _VCF_WIN32TRANSPARENTWINDOWPEER_H__
//PopupWindowPeer.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {


class APPLICATIONKIT_API Win32TransparentWindowPeer : public Win32Window, public TransparentWindowPeer {
public:

	Win32TransparentWindowPeer( Frame* window );

	virtual ~Win32TransparentWindowPeer();

	virtual void setAlpha( const double& alphaValue );

	virtual double getAlpha();

	virtual void setAlphaImage( Image* img );

	virtual void create( Control* owningControl );

	virtual Win32Object::CreateParams createParams();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);
	virtual void setVisible( const bool& visible );
protected:
	double alpha_;
};


};



#endif //_VCF_WIN32TRANSPARENTWINDOWPEER_H__