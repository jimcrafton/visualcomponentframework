
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBCursorPeer.h"

using namespace VCF;

XCBCursorPeer::XCBCursorPeer( Cursor* cursor )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

OSHandleID XCBCursorPeer::getCursorHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

void XCBCursorPeer::createFromImage( Image* cursorImage, Point* hotSpot )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBCursorPeer::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBCursorPeer::createFromResourceName( const String& cursorName, OSHandleID instanceHandle )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

long XCBCursorPeer::getCursorID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

void XCBCursorPeer::setCursorID( const long& cursorID )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

VCF::Cursor* XCBCursorPeer::getCursor()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

void XCBCursorPeer::setCursor( VCF::Cursor* cursor )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

/**
$Id$
*/

