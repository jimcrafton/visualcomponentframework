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
								const bool& isMnemonic )
{
	associatedControl_ = associatedControl;
	keyCode_ = keyCode;
	modifierMask_ = modifierMask;
	eventHandler_ = eventHandler;
	isMnemonic_ = isMnemonic;
}

AcceleratorKey::~AcceleratorKey()
{

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


/**
*CVS Log info
*$Log$
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


