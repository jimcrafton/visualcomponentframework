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

	protected:
		virtual void createImpl( XCBConnection* connection, XCBSCREEN* screen );

	private:
        XCBATOM deleteWindowAtom_;

	};
};

#endif //_VCF_XCBCURSORPEER_H__

/**
$Id$
*/

