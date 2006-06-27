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

uint32 OSXDesktopPeer::desktopGetWidth()
{
	return CGDisplayPixelsWide( CGMainDisplayID() );
}

uint32 OSXDesktopPeer::desktopGetHeight()
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
$Id$
*/
