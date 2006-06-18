#ifndef _VCF_XCBWINDOWPEER_H__
#define _VCF_XCBWINDOWPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/WindowPeer.h"
#include "vcf/ApplicationKit/XCBAbstractControl.h"

namespace VCF {

	class XCBWindowPeer : public WindowPeer, public ControlPeer {
	public:
        XCBWindowPeer( Control* component, Control* owner );

		virtual Rect getClientBounds();

		virtual void setClientBounds( Rect* bounds );

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

		////////////////////////////////////////////////////////
		virtual void create( Control* owningControl );

		virtual void destroyControl();

		virtual OSHandleID getHandleID();

		virtual String getText();

		virtual void setText( const String& text );

		virtual void setBounds( Rect* rect );

		virtual bool beginSetBounds( const ulong32& numberOfChildren );

		virtual void endSetBounds();

		virtual Rect getBounds();

		virtual void setVisible( const bool& visible );

		virtual bool getVisible();

		virtual Control* getControl();

		virtual void setControl( Control* component );

		virtual void setCursor( Cursor* cursor );

		virtual void setParent( Control* parent );

		virtual Control* getParent();

		virtual bool isFocused();

		virtual void setFocused();

		virtual bool isEnabled();

		virtual void setEnabled( const bool& enabled );

		virtual void setFont( Font* font );

		virtual void repaint( Rect* repaintRect, const bool& immediately );

		virtual void keepMouseEvents();

		virtual void releaseMouseEvents();

		virtual void translateToScreenCoords( Point* pt );

		virtual void translateFromScreenCoords( Point* pt );

		virtual void setBorder( Border* border );

		virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );

		virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );

		/////////////////////////////////////////////////////////////////////
		static void internal_handleClientMessageEvent(const XCBClientMessageEvent& event);
		static void internal_handleConfigureNotifyEvent(const XCBConfigureNotifyEvent& event);
		static void internal_handleExposeEvent(const XCBExposeEvent& event);
		static void internal_handleDestroyNotify(const XCBDestroyNotifyEvent& event);

	private:
		void paint();

	private:
		XCBDRAWABLE	drawable_;
		XCBGCONTEXT context_;
        XCBATOM     deleteWindowAtom_;
		Rect 	 	clientBounds_;
		Control*    control_;

		typedef std::map<CARD32, XCBWindowPeer*> XIDWindowPeerMap;
		static XIDWindowPeerMap XIDWindowPeerMap_;
	};
};

#endif //_VCF_XCBCURSORPEER_H__

/**
$Id$
*/

