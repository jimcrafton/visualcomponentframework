//Cursor.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Cursor.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/VFFInputStream.h"

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
	peer_->setCursorID(cursorID);
}

CursorPeer* Cursor::getPeer()
{
	return peer_;
}

void Cursor::registerConstants()
{
	VFFInputStream::registerComponentConstant( "SCT_DEFAULT", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_CROSSHAIRS", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_SPLIT_VERT", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_SPLIT_HORZ", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_SIZE_HORZ", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_SIZE_VERT", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_SIZE_NE_SW", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_SIZE_NW_SE", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_TEXT", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_HELP", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_NOWAYHOSER", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_WAITING", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_POINTING_HAND", Cursor::getCursorConstants );
	VFFInputStream::registerComponentConstant( "SCT_WAIT", Cursor::getCursorConstants );
}

String Cursor::getCursorConstants( const String& name )
{
	static std::map<String,String> constants;

	if ( constants.empty() ) {
		constants["SCT_DEFAULT"] = StringUtils::toString( (int) Cursor::SCT_DEFAULT );
		constants["SCT_CROSSHAIRS"] = StringUtils::toString( (int) Cursor::SCT_CROSSHAIRS );
		constants["SCT_SPLIT_VERT"] = StringUtils::toString( (int) Cursor::SCT_SPLIT_VERT );
		constants["SCT_SPLIT_HORZ"] = StringUtils::toString( (int) Cursor::SCT_SPLIT_HORZ );
		constants["SCT_SIZE_HORZ"] = StringUtils::toString( (int) Cursor::SCT_SIZE_HORZ );
		constants["SCT_SIZE_VERT"] = StringUtils::toString( (int) Cursor::SCT_SIZE_VERT );
		constants["SCT_SIZE_NE_SW"] = StringUtils::toString( (int) Cursor::SCT_SIZE_NE_SW );
		constants["SCT_SIZE_NW_SE"] = StringUtils::toString( (int) Cursor::SCT_SIZE_NW_SE );
		constants["SCT_TEXT"] = StringUtils::toString( (int) Cursor::SCT_HELP );
		constants["SCT_NOWAYHOSER"] = StringUtils::toString( (int) Cursor::SCT_NOWAYHOSER );
		constants["SCT_WAITING"] = StringUtils::toString( (int) Cursor::SCT_WAITING );
		constants["SCT_POINTING_HAND"] = StringUtils::toString( (int) Cursor::SCT_POINTING_HAND );
		constants["SCT_WAIT"] = StringUtils::toString( (int) Cursor::SCT_WAIT );
	}

	return constants[name];
}

WaitCursor::WaitCursor( Control* control ):
	currentControl_(control),
	prevCursorID_(-1)
{
	if ( NULL == currentControl_ ) {
		currentControl_ = Application::getRunningInstance()->getMainWindow();
	}

	prevCursorID_ = currentControl_->getCursorID();

	currentControl_->setCursorID( Cursor::SCT_WAIT );
}

WaitCursor::~WaitCursor()
{
	if ( NULL != currentControl_ ) {
		currentControl_->setCursorID( prevCursorID_ );
	}
}

/**
$Id$
*/
