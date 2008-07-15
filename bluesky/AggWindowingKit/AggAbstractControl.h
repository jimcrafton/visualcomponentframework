#ifndef _VCF_AggAbstractControl_H
#define _VCF_AggAbstractControl_H

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ControlPeer.h"

namespace VCF {
	class AggWindowPeer;

    class AggAbstractControl;
    typedef std::vector<AggAbstractControl*> AggControlArray;


	class AggAbstractControl : public ControlPeer {
	public:
		virtual ~AggAbstractControl();

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

        AggWindowPeer* getOwnerWindow() {
            return owningWindow_;
        }

        void setOwnerWindow( AggWindowPeer* val ) {
            owningWindow_ = val;
        }

        bool mouseEventsCaptured() {
            return mouseEventsCaptured_;
        }

        AggControlArray getXCBChildControls() {
            return childControls_;
        }

        void paintChildren( GraphicsContext* sharedCtx );

		virtual void paintPeer( GraphicsContext* sharedCtx );

		virtual void paintPeerControl( GraphicsContext* sharedCtx );

		//virtual void handleMouseEvents(xcb_connection_t &connection, const xcb_generic_event_t& event);
		
	protected:
		AggAbstractControl( Control* control );

		Control* control_;
        Rect 	 bounds_;
        AggWindowPeer* owningWindow_;
        bool enabled_;
        bool visible_;
        bool focused_;
        AggAbstractControl* parent_;
        bool mouseEventsCaptured_;

        AggControlArray childControls_;


        void addChild( AggAbstractControl* child );
        void removeChild( AggAbstractControl* child );

		AggAbstractControl* findControlForMouseEvent( Point pt );
	private:
	};
};

#endif //_VCF_AggAbstractControl_H

/**
$Id$
*/

