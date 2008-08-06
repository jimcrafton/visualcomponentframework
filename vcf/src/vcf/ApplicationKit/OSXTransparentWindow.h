#ifndef _VCF_OSXTRANSPARENTWINDOW_H__
#define _VCF_OSXTRANSPARENTWINDOW_H__
/*
 Copyright 2000-3004 The VCF Project.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */



namespace VCF {
	
	
	class OSXTransparentWindow : public OSXWindow, public TransparentWindowPeer {
	public:
		
		OSXTransparentWindow( Frame* window );
		
		virtual ~OSXTransparentWindow();
		
		virtual void setAlpha( const double& alphaValue );
		
		virtual double getAlpha();
		
		virtual void setAlphaImage( Image* img );
		
		virtual void create( Control* owningControl );
				
		virtual void setVisible( const bool& visible );
	protected:
		
	};
	
	
};


#endif //_VCF_OSXTRANSPARENTWINDOW_H__