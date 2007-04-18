//AcceleratorKey.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//AcceleratorKey.h

#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;



AcceleratorKey::AcceleratorKey( Object* object, AcceleratorObjectType type,
								const VirtualKeyCode& keyCode,
								const uint32& modifierMask, EventHandler* eventHandler,
								const bool& isMnemonic ):
	keyCode_(keyCode),
	modifierMask_(modifierMask),
	associatedControl_(NULL),
	associatedMenuItem_(NULL),
	associatedObject_(NULL),
	eventHandler_(eventHandler),
	isMnemonic_(isMnemonic),
	enabled_(true)
{
	switch ( type ) {
		case AcceleratorKey::aotObject : {
			associatedObject_ = object;
		}
		break;

		case AcceleratorKey::aotControl : {
			associatedControl_ = object;
		}
		break;

		case AcceleratorKey::aotMenuItem : {
			associatedMenuItem_ = object;
		}
		break;
	}
}


AcceleratorKey::~AcceleratorKey()
{

}

AcceleratorKey::AcceleratorKey( const AcceleratorKey& rhs ):
	keyCode_((VirtualKeyCode)0),
	modifierMask_(0),
	associatedControl_(NULL),
	associatedMenuItem_(NULL),
	associatedObject_(NULL),
	eventHandler_(NULL),
	isMnemonic_(false),
	enabled_(true)
{
	keyCode_ = rhs.keyCode_;
	modifierMask_ = rhs.modifierMask_;
	associatedControl_ = rhs.associatedControl_;
	associatedMenuItem_ = rhs.associatedMenuItem_;
	associatedObject_ = rhs.associatedObject_;
	eventHandler_ = rhs.eventHandler_;
	isMnemonic_ = rhs.isMnemonic_;
	enabled_ = rhs.enabled_;
}

bool AcceleratorKey::hasShiftKey()
{
	return ((modifierMask_ & kmShift) != 0);
}

bool AcceleratorKey::hasCtrlKey()
{
	return ((modifierMask_ & kmCtrl) != 0);
}

bool AcceleratorKey::hasAltKey()
{
	return ((modifierMask_ & kmAlt) != 0);
}

void AcceleratorKey::invoke( Event* event )
{
	if ( NULL == eventHandler_ ) {
		if ( NULL != this->associatedControl_ ) {
			StringUtils::trace( "WARNING! This used to set focus to the associated control - this is currently commented out - does it break anything????\n" );
			//associatedControl_->setFocused();
		}
	}
	else {
		eventHandler_->invoke( event );
	}
}

Object* AcceleratorKey::clone( bool deep )
{
	
	return new AcceleratorKey(*this);
}

void AcceleratorKey::setEnabled( const bool& val )
{
	enabled_ = val;
	std::vector<AcceleratorKey*> matchingAccelerators;
//	if ( UIToolkit::findMatchingAccelerators( this, matchingAccelerators ) ) {
//		std::vector<AcceleratorKey*>::iterator it = matchingAccelerators.begin();
//		while ( it != matchingAccelerators.end() ) {
//			(*it)->enabled_ = enabled_;
//			it ++;
//		}
//	}

}


/**
$Id$
*/
