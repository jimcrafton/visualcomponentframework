#ifndef _VCF_XCBABSTRACTCONTROL_H
#define _VCF_XCBABSTRACTCONTROL_H

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ControlPeer.h"

namespace VCF {

	class XCBAbstractControl : public ControlPeer {
	public:
		virtual ~XCBAbstractControl();
		
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

	protected:
		XCBAbstractControl( Control* control );

		Control* control_;
        Rect 	 bounds_;
	private:
	};
};

#endif //_VCF_XCBABSTRACTCONTROL_H

/**
$Id$
*/

