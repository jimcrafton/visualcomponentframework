//OSXApplicationPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXApplicationPeer.h"


using namespace VCF;

OSXApplicationPeer::OSXApplicationPeer():
	app_(NULL),
	appInstance_(0)
{

}

OSXApplicationPeer::~OSXApplicationPeer()
{

}


bool OSXApplicationPeer::initApp()
{
	bool result = true;
	appInstance_ = [NSApplication sharedApplication];
	NSAutoreleasePool * Pool = [[NSAutoreleasePool alloc] init];
	
	return result;
}

void OSXApplicationPeer::terminateApp()
{

}


void OSXApplicationPeer::setApplication( VCF::AbstractApplication* application )
{
	app_ = application;
}

ResourceBundle* OSXApplicationPeer::getResourceBundle()
{
	return NULL;
}

String OSXApplicationPeer::getFileName()
{
	String result;
	
	CFRefObject<CFBundleRef> bundle = CFBundleGetMainBundle();
	CFTextString val;
	val = (CFStringRef)CFBundleGetValueForInfoDictionaryKey( bundle, kCFBundleExecutableKey );
	
	CFRefObject<CFURLRef> url = CFBundleCopyBundleURL( bundle );
	char buf[256];
	if ( CFURLGetFileSystemRepresentation( url, true, (UInt8*)buf, sizeof(buf) ) ) {
		result = buf;
		result += "/Contents/MacOS/";
		result += val.c_str();//OSXUtils::extractStringValueFromCFType( val );
	}
	
	return result;
}

OSHandleID OSXApplicationPeer::getHandleID()
{
	return (OSHandleID)appInstance_;
}

void OSXApplicationPeer::setHandleID( OSHandleID handleID )
{
	appInstance_ = (NSApplication*) handleID;
}


/**
$Id$
*/
