//Cursor.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Cursor.h

#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

Cursor::Cursor( const SystemCursorType& systemCursor )
{
	peer_ = UIToolkit::createCursorPeer( this );

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL cursor peer - this is probably not implemented yet") );
	}

	peer_->createSystemCursor( systemCursor );
	CursorManager::getCursorManager()->registerCursor( this );
}

Cursor::Cursor( Image* cursorImage, Point* hotSpot )
{
	peer_ = UIToolkit::createCursorPeer( this );

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL cursor peer - this is probably not implemented yet") );
	}

	peer_->createFromImage( cursorImage, hotSpot );
	CursorManager::getCursorManager()->registerCursor( this );
}

Cursor::Cursor( const String& cursorName, AbstractApplication* application )
{
	peer_ = UIToolkit::createCursorPeer( this );

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL cursor peer - this is probably not implemented yet") );
	}

	if ( NULL == application ) {
		peer_->createFromResourceName( cursorName );
	}
	else {
		peer_->createFromResourceName( cursorName, application->getPeer()->getHandleID() );
	}

	CursorManager::getCursorManager()->registerCursor( this );
}

Cursor::~Cursor()
{
	delete peer_;
}

int32 Cursor::getCursorID()
{
	return peer_->getCursorID();
}

void Cursor::setCursorFromID( const int32& cursorID )
{

}

CursorPeer* Cursor::getPeer()
{
	return peer_;
}


/**
$Id$
*/
