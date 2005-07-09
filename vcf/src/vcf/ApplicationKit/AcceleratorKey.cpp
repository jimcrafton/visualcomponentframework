//AcceleratorKey.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//AcceleratorKey.h

#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;



AcceleratorKey::AcceleratorKey( Control* associatedControl, const VirtualKeyCode& keyCode,
								const ulong32& modifierMask, EventHandler* eventHandler,
								const bool& isMnemonic ):
	keyCode_(keyCode),
	modifierMask_(modifierMask),
	associatedControl_(associatedControl),
	associatedMenuItem_(NULL),
	associatedObject_(NULL),
	eventHandler_(eventHandler),
	isMnemonic_(isMnemonic),
	enabled_(true)
{
	
}

AcceleratorKey::AcceleratorKey( MenuItem* associatedMenuItem, const VirtualKeyCode& keyCode,
					const ulong32& modifierMask, EventHandler* eventHandler,
					const bool& isMnemonic ):
	keyCode_(keyCode),
	modifierMask_(modifierMask),
	associatedControl_(NULL),
	associatedMenuItem_(associatedMenuItem),
	associatedObject_(NULL),
	eventHandler_(eventHandler),
	isMnemonic_(isMnemonic),
	enabled_(true)
{
	
}

AcceleratorKey::AcceleratorKey( Object* associatedObject, const VirtualKeyCode& keyCode,
					const ulong32& modifierMask, EventHandler* eventHandler,
					const bool& isMnemonic ):
	keyCode_(keyCode),
	modifierMask_(modifierMask),
	associatedControl_(NULL),
	associatedMenuItem_(NULL),
	associatedObject_(associatedObject),
	eventHandler_(eventHandler),
	isMnemonic_(isMnemonic),
	enabled_(true)
{
	
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
			associatedControl_->setFocused();
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
	if ( UIToolkit::findMatchingAccelerators( this, matchingAccelerators ) ) {
		std::vector<AcceleratorKey*>::iterator it = matchingAccelerators.begin();
		while ( it != matchingAccelerators.end() ) {
			(*it)->enabled_ = enabled_;
			it ++;
		}
	}

}

/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2.4.1  2005/03/14 04:17:22  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.6  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.3  2003/04/17 04:29:52  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.5.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.2.1  2003/03/12 03:12:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.1  2003/01/08 00:19:57  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.3  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


