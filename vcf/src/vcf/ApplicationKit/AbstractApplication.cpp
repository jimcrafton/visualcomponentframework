//AbstractApplication.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//AbstractApplication.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationPeer.h"
#include "vcf/FoundationKit/VFFInputStream.h"
#include "vcf/FoundationKit/VFFOutputStream.h"

using namespace VCF;

AbstractApplication::AbstractApplication():
	applicationPeer_(NULL)
{

}

AbstractApplication::~AbstractApplication()
{

}

ApplicationPeer* AbstractApplication::getPeer()
{
	return applicationPeer_;
}

GraphicsResourceBundle* AbstractApplication::getResourceBundle()
{
	return GraphicsToolkit::getResourceBundle();
}

String AbstractApplication::getFileName()
{
	return applicationPeer_->getFileName();
}

Window* AbstractApplication::createWindow( Class* windowClass )
{
	Window* result = NULL;

	result = Frame::createWindow( windowClass, getResourceBundle() );

	return result;
}

Dialog* AbstractApplication::createDialog( Class* dialogClass )
{
	Dialog* result = NULL;

	result = Frame::createDialog( dialogClass, getResourceBundle() );

	return result;
}

void AbstractApplication::loadWindow( Window* window )
{
	Component::initComponent( window, window->getClass(), classid(VCF::Window), getResourceBundle() );
}

void AbstractApplication::loadDialog( Dialog* dialog )
{
	Component::initComponent( dialog, dialog->getClass(), classid(VCF::Dialog), getResourceBundle() );
}


void AbstractApplication::idleTime()
{

}

void AbstractApplication::postEvent( EventHandler* eventHandler, Event* event, const bool& deleteHandler )
{
	UIToolkit::postEvent( eventHandler, event, deleteHandler );
}

AcceleratorKey* AbstractApplication::getAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src )
{
	return UIToolkit::getAccelerator( keyCode, modifierMask, src );
}

void AbstractApplication::addAcceleratorKey( const VirtualKeyCode& keyCode, const uint32& modifierMask, EventProcedure* eventHandler )
{
	if ( NULL == eventHandler ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2("The Event handler passed in is NULL!") );
	}

	AcceleratorKey* accelerator = new AcceleratorKey( this, keyCode, modifierMask, eventHandler );
	addAcceleratorKey( accelerator );
}

void AbstractApplication::addAcceleratorKey( AcceleratorKey* accelerator )
{
	UIToolkit::registerAccelerator( accelerator );
}

void AbstractApplication::setName( const String& name )
{
	applicationName_ = name;
}


/**
$Id$
*/
