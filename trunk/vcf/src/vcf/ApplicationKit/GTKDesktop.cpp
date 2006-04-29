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
$Id$
*/
