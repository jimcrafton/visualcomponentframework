//GTKControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKControl.h"
#include "vcf/ApplicationKit/GTKUIToolkit.h"

using namespace VCF;


GTKControl::GTKControl( Control* control )
{
	control_ = control;


}

GTKControl::~GTKControl()
{
}



void GTKControl::create( Control* owningControl )
{
	GTKGraphicsToolkit * grafToolkit = ( GTKGraphicsToolkit* ) GraphicsToolkit::internal_getDefaultGraphicsToolkit();
	GTKUIToolkit* toolkit = ( GTKUIToolkit* ) UIToolkit::internal_getDefaultUIToolkit();

	wndHandle_ = AbstractGTKControl::Container::create( NULL, this );	//gtk_layout_new( NULL, NULL );

	//

	if ( NULL == wndHandle_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "gtk_layout_new() failed" ) );
	}

	gtk_container_add( GTK_CONTAINER( toolkit->getDefaultParent() ), wndHandle_ );

	AbstractGTKControl::registerGTKControl( this );


}

void GTKControl::setBorder( Border* border )
{}


/**
$Id$
*/
