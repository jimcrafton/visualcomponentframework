//OSXPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <errno.h>

using namespace VCF;




String OSXUtils::getErrorString( int errorCode )
{
	String result;

	return result;
}


String OSXUtils::extractStringValueFromCFType( CFTypeRef ref )
{
	String result;
	
	if ( NULL != ref ) {
		CFStringRef resultString = CFStringCreateWithFormat( NULL, NULL, CFSTR("%@"), ref );
		
		if ( NULL != resultString ) {
			
			CFDataRef data = CFStringCreateExternalRepresentation(NULL, 
																  resultString, 
																  CFStringGetSystemEncoding(), 
																  '?');
			
			if (data != NULL) {			
				result.assign( (char*)CFDataGetBytePtr(data), CFDataGetLength(data) );
				
				CFRelease(data);
			}
			
			CFRelease( resultString );
		}	
	}
	
	return result;
}

VCF::ulong32 OSXUtils::translateButtonMask( EventMouseButton button )
{
    VCF::ulong32 result = 0;

    if ( button == kEventMouseButtonPrimary ) {
        result = VCF::mbmLeftButton;
    }
    else if ( button == kEventMouseButtonSecondary ) {
        result = VCF::mbmRightButton;
    }
    else if ( button == kEventMouseButtonTertiary ) {
        result = VCF::mbmMiddleButton;
    }

    return result;
}

VCF::ulong32 OSXUtils::translateKeyMask( UInt32 keyMod )
{
    VCF::ulong32 result = 0;

    if ( keyMod & shiftKey ) {
        result |= VCF::kmShift;
    }

    if ( keyMod & cmdKey ) {
        result |= VCF::kmAlt;
    }

    if ( keyMod & controlKey ) {
        result |= VCF::kmCtrl;
    }
    return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/06/15 15:41:14  ddiego
*minor osx stuff
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/10 20:42:08  ddiego
*osx updates
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


