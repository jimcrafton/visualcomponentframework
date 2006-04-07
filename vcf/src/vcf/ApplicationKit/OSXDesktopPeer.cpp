//OSXDesktopPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXDesktopPeer.h"

using namespace VCF;

OSXDesktopPeer::OSXDesktopPeer( Desktop* desktop )
{

}

OSXDesktopPeer::~OSXDesktopPeer()
{

}


void OSXDesktopPeer::desktopBeginPainting( Rect* clippingRect )
{

}

/**
*called after finished painting on the desktop
*allows for native Windowing system cleanup to happen
*/
void OSXDesktopPeer::desktopEndPainting()
{

}

bool OSXDesktopPeer::desktopSupportsVirtualDirectories()
{
	bool result = false;

	return result;
}

bool OSXDesktopPeer::desktopHasFileSystemDirectory()
{
	bool result = true;

	return result;
}

String OSXDesktopPeer::desktopGetDirectory()
{
    String result;
    FSRef desktopFolder;
    if ( noErr == FSFindFolder( kUserDomain, kDesktopFolderType, kDontCreateFolder, &desktopFolder ) ) {
        char tmp[256];
        FSRefMakePath( &desktopFolder, (UInt8*)tmp, sizeof(tmp)-1 );
        result = tmp;
    }
    else {

    }

	return result;
}

OSHandleID OSXDesktopPeer::desktopGetHandleID()
{
	OSHandleID result = 0;


	return result;
}

OSHandleID OSXDesktopPeer::desktopGetGraphicsContextHandleID()
{

	return desktopGetHandleID();
}

void OSXDesktopPeer::desktopSetDesktop( Desktop* desktop )
{

}

ulong32 OSXDesktopPeer::desktopGetWidth()
{
	return CGDisplayPixelsWide( CGMainDisplayID() );
}

ulong32 OSXDesktopPeer::desktopGetHeight()
{

	return CGDisplayPixelsHigh( CGMainDisplayID() );
}


VCF::Rect OSXDesktopPeer::desktopGetUsableBounds()
{
	VCF::Rect result;

	result.left_ = 0.0;
	result.top_ = GetMBarHeight();

	result.right_ = desktopGetWidth();
	result.bottom_ = desktopGetHeight();

	return result;
}

VCF::Point OSXDesktopPeer::getCurrentMousePosition()
{
	VCF::Point result;
	::Point pt;
	GetMouse( &pt );
	result.x_ = pt.h;
	result.y_ = pt.v;
	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2006/02/19 02:07:46  ddiego
*mac osx update.
*
*Revision 1.4.2.1  2005/11/27 23:55:44  ddiego
*more osx updates.
*
*Revision 1.4  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.2.4.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
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
*Revision 1.2  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:44  ddiego
*initial OSX ApplicationKit port checkin
*
*/


