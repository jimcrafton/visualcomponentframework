#ifndef _VCF_POPUPWINDOW_H__
#define _VCF_POPUPWINDOW_H__
//PopupWindow.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

class PopupWindowPeer;


class APPLICATIONKIT_API PopupWindow : public Frame {
public:
	PopupWindow( Window* owningWindow );

	virtual ~PopupWindow();

	void showModal();

	void showAsSheet( Window* owningWindow );

	void show();

	bool isModal() {
		return modal_;
	}

	virtual void  setClientBounds( Rect* bounds );
	virtual void close();
	virtual void setFrameStyle( const FrameStyleType& frameStyle ){};

	virtual bool allowsActivation() {
		return false;
	}

	virtual void setIconImage( Image* icon ){}

	virtual Image* getIconImage(){
		return NULL;
	}

	virtual bool isActiveFrame() {
		return false;
	}


	virtual void paint( GraphicsContext * context );

	virtual void mouseDown( MouseEvent* event );

	virtual void setBorderPath( Path* path );
protected:
	PopupWindowPeer * popupPeer_;
	WindowPeer * windowPeer_;
	bool modal_;
	Window* owningWindow_;

	void onClose( FrameEvent* e );
	void postClose( Event* event );
};


};



#endif //_VCF_POPUPWINDOW_H__