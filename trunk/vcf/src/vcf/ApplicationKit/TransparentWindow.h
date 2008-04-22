#ifndef _VCF_TRANSPARENTWINDOW_H__
#define _VCF_TRANSPARENTWINDOW_H__
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


class APPLICATIONKIT_API TransparentWindow : public Frame {
public:
	TransparentWindow( Frame* frame );

	virtual ~TransparentWindow();
	
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
	
	virtual void setBorderPath( Path* path );	

	void setAlpha( const double& alphaValue );

	double getAlpha();

	void setAlphaImage( Image* img );

	virtual void paint( GraphicsContext* context );
protected:
	TransparentWindowPeer* transparentWndPeer_;
	WindowPeer * windowPeer_;
	Image* alphaImage_;

	void onClose( FrameEvent* e );
	void postClose( Event* event );
};


};



#endif //_VCF_TRANSPARENTWINDOW_H__