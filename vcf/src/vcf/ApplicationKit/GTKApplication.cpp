//GTKApplication.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKApplication.h"


using namespace VCF;

GTKApplication::GTKApplication() :
		app_( NULL ),
		handleID_( 0 )
{
}

GTKApplication::~GTKApplication()
{
}


bool GTKApplication::initApp()
{
	bool result = true;

	//initialize GTK!
	//note! gtk_init is called in GraphicsKit::init() now


	gdk_event_handler_set( GTKUIToolkit::internal_gdkEventHandler,
	                       ( gpointer ) UIToolkit::internal_getDefaultUIToolkit(), NULL );

	//g_idle_add( GTKUIToolkit::internal_gdkIdleHandler, (gpointer)UIToolkit::getDefaultUIToolkit() );


	return result;
}

void GTKApplication::terminateApp()
{
}


void GTKApplication::setApplication( VCF::AbstractApplication* application )
{
	app_ = application;
}

ResourceBundle* GTKApplication::getResourceBundle()
{
	return NULL;
}

String GTKApplication::getFileName()
{
	String result;

	return result;
}

OSHandleID GTKApplication::getHandleID()
{
	return reinterpret_cast<OSHandleID>( handleID_ );
}

void GTKApplication::setHandleID( OSHandleID handleID )
{
	handleID_ = reinterpret_cast<long>( handleID );
}


/**
$Id$
*/
