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
	handleID_(0)
{

}

OSXApplicationPeer::~OSXApplicationPeer()
{

}


bool OSXApplicationPeer::initApp()
{
	bool result = true;

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
		result += val;//OSXUtils::extractStringValueFromCFType( val );
	}
	
	return result;
}

long OSXApplicationPeer::getHandleID()
{
	return handleID_;
}

void OSXApplicationPeer::setHandleID( const long& handleID )
{
	handleID_ = handleID;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/15 05:41:27  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/06 02:56:35  ddiego
*checking in OSX updates
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:44  ddiego
*initial OSX ApplicationKit port checkin
*
*/


