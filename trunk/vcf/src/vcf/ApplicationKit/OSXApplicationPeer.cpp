//OSXApplicationPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXApplicationPeer.h"


@interface VCFAppDelegate : NSObject
{

}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
@end

@implementation VCFAppDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return NO;
}


- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
	printf( "applicationShouldTerminate called!\n" );
	
	VCF::Application* app = VCF::Application::getRunningInstance();
	
	app->internal_terminate();
	
	VCF::ApplicationPeer* appPeer = app->getPeer();
	delete appPeer;
	
	app->free();
	VCF::ApplicationKit::terminate();
	
	return NSTerminateNow;
}

@end



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
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];	
	
	VCFAppDelegate* appDelegate = [[VCFAppDelegate alloc] init];
	[appInstance_ setDelegate: appDelegate];
	
	
	return result;	
}

void OSXApplicationPeer::terminateApp()
{
	//appInstance_->free();

	
	NSApplication* app = [NSApplication sharedApplication];
	[app terminate: app];		
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
