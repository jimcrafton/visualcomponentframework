//GTKDesktop.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKDesktop.h"

using namespace VCF;

GTKDesktop::GTKDesktop( Desktop* desktop )
{
}

GTKDesktop::~GTKDesktop()
{
}


void GTKDesktop::desktopBeginPainting( Rect* clippingRect )
{
}

/**
*called after finished painting on the desktop
*allows for native Windowing system cleanup to happen
*/
void GTKDesktop::desktopEndPainting()
{
}

bool GTKDesktop::desktopSupportsVirtualDirectories()
{
	bool result = false;

	return result;
}

bool GTKDesktop::desktopHasFileSystemDirectory()
{
	bool result = false;

	return result;
}

String GTKDesktop::desktopGetDirectory()
{
	return "";
}

OSHandleID GTKDesktop::desktopGetHandleID()
{
	return gdk_get_default_root_window();
}

OSHandleID GTKDesktop::desktopGetGraphicsContextHandleID()
{
	return desktopGetHandleID();
}

void GTKDesktop::desktopSetDesktop( Desktop* desktop )
{
}

ulong32 GTKDesktop::desktopGetWidth()
{
	return gdk_screen_get_width( gdk_screen_get_default() );
}

ulong32 GTKDesktop::desktopGetHeight()
{

	return gdk_screen_get_height( gdk_screen_get_default() );
}


Rect GTKDesktop::desktopGetUsableBounds()
{
	Rect result;

	result.left_ = 0.0;
	result.top_ = 0.0;

	result.right_ = desktopGetWidth();
	result.bottom_ = desktopGetHeight();

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/05/17 20:37:32  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.2.1  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*/


