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

	class XCBWindowPeer : public WindowPeer, public XCBAbstractControl {
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

		virtual void setBorderPath( Path* path ) ;

		////////////////////////////////////////////////////////
		virtual void create( Control* owningControl );

		virtual void destroyControl();

		virtual OSHandleID getHandleID();

		virtual String getText();

		virtual void setText( const String& text );

		virtual void setBounds( Rect* rect );

		virtual bool beginSetBounds( const uint32& numberOfChildren );

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
		static void internal_handleClientMessageEvent(xcb_connection_t &connection, const xcb_client_message_event_t& event);

		static void internal_handleMouseEvents(xcb_connection_t& connection, const xcb_generic_event_t& event);
		static void internal_handleKeyboardEvents(xcb_connection_t &connection, const xcb_generic_event_t& event);

		static void internal_handleConfigureNotifyEvent(xcb_connection_t &connection, const xcb_configure_notify_event_t& event);
		static void internal_handleExposeEvent(xcb_connection_t &connection, const xcb_expose_event_t& event);
		static void internal_handleDestroyNotify(xcb_connection_t &connection, const xcb_destroy_notify_event_t& event);

	private:
		void paint(xcb_connection_t &connection, const xcb_expose_event_t& event );
		void destroyImage(xcb_connection_t &connection);
		void createImage(xcb_connection_t &connection, int width, int height);

	private:
		xcb_drawable_t	      drawable_;
		xcb_gcontext_t       context_;
		xcb_image_t         *image_;
		xcb_shm_segment_info_t shminfo_;
        xcb_atom_t           deleteWindowAtom_;
		Rect 	 	      clientBounds_;

		typedef std::map<uint32, XCBWindowPeer*> XIDWindowPeerMap;
		static XIDWindowPeerMap XIDWindowPeerMap_;
	};
};

#endif //_VCF_XCBCURSORPEER_H__

/**
$Id$
*/

