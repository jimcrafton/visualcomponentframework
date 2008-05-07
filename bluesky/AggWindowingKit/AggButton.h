
#ifndef _VCF_XCBBUTTON_H
#define _VCF_XCBBUTTON_H

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifndef _VCF_DRAWUISTATE_H__
#	include "vcf/GraphicsKit/DrawUIState.h"
#endif // _VCF_DRAWUISTATE_H__

#ifndef _VCF_BUTTONPEER_H__
#	include "vcf/ApplicationKit/ButtonPeer.h"
#endif // _VCF_BUTTONPEER_H__




namespace VCF {

    class CommandButton;

	class AggButton : public AggAbstractControl, public ButtonPeer {
	public:
        AggButton( CommandButton* button );

        virtual ~AggButton();


        virtual Image* getImage();

		virtual void setImage( Image* image );

		virtual ButtonState getState();

        //virtual void paintPeer( xcb_connection_t &connection, const xcb_expose_event_t& event, GraphicsContext* sharedCtx );
    protected:
        //virtual void handleMouseEvents(xcb_connection_t &connection, const xcb_generic_event_t& event);

		ButtonState btnState_;
		Image* btnImage_;
	};
};

#endif //_VCF_XCBBUTTON_H

/**
$Id$
*/

