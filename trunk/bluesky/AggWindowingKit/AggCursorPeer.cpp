
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "AggCursorPeer.h"

using namespace VCF;

AggCursorPeer::AggCursorPeer( Cursor* cursor )
{
	
}

OSHandleID AggCursorPeer::getCursorHandleID()
{
	return 0;
}

void AggCursorPeer::createFromImage( Image* cursorImage, Point* hotSpot )
{
	
}

void AggCursorPeer::createSystemCursor( const Cursor::SystemCursorType& systemCursor )
{
	
}

void AggCursorPeer::createFromResourceName( const String& cursorName, OSHandleID instanceHandle )
{
	
}

int32 AggCursorPeer::getCursorID()
{
	
	return 0;
}

void AggCursorPeer::setCursorID( const int32& cursorID )
{
	
}

VCF::Cursor* AggCursorPeer::getCursor()
{	
	return NULL;
}

void AggCursorPeer::setCursor( VCF::Cursor* cursor )
{
	
}

/**
$Id$
*/

