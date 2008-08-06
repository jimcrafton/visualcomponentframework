#ifndef _VCF_OSXPOPUPWINDOW_H__
#define _VCF_OSXPOPUPWINDOW_H__
/*
 Copyright 2000-3004 The VCF Project.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */




namespace VCF {
	
	
	class OSXPopupWindow : public OSXWindow, public PopupWindowPeer {
	public:
		OSXPopupWindow( Frame* frame, Window* owner );
		
		virtual ~OSXPopupWindow();
		
		virtual void create( Control* owningControl );
		
		virtual void setBorder( Border* border );
		
		virtual void setText( const String& text );
		
		virtual void setBounds( Rect* rect );
		
		virtual void setVisible( const bool& visible );
		
		virtual void  setClientBounds( Rect* bounds );
		
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
		
		virtual void showModal();
		
		virtual void showAsSheet( Window* owningWindow );
		
		virtual void show();	
		
		void closePopup();
	};
	
}	

#endif //_VCF_OSXPOPUPWINDOW_H__