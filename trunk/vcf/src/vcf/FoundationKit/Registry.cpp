//Registry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

Registry::Registry()
{
	peer_ = NULL;
	peer_ =  SystemToolkit::createRegistryPeer( this );

	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

Registry::~Registry()
{
	delete peer_;
}

void Registry::setRoot( const RegistryKeyType& rootKey )
{
	peer_->setRoot( rootKey );
}

RegistryKeyType Registry::getRoot()
{
	return peer_->getRoot();
}

bool Registry::openKey( const String& keyname, const bool& createIfNonExistant )
{
	return peer_->openKey( keyname, createIfNonExistant );
}

bool Registry::setValue( const String& value, const String& valuename )
{
	return peer_->setValue( value, valuename );
}

bool Registry::setValue( const uint32& value, const String& valuename )
{
	return peer_->setValue( value, valuename );
}

bool Registry::setValue( const bool& value, const String& valuename )
{
	return peer_->setValue( value, valuename );
}

bool Registry::setValue( void* dataBuffer, const uint32& dataBufferSize, const String& valuename )
{
	return peer_->setValue( dataBuffer, dataBufferSize, valuename );
}

String Registry::getStringValue( const String& valuename )
{
	return peer_->getStringValue( valuename );
}

uint32 Registry::getIntValue( const String& valuename )
{
	return peer_->getIntValue( valuename );
}

bool Registry::getBoolValue( const String& valuename )
{
	return peer_->getBoolValue( valuename );
}

void Registry::getDataBufValue( const String& valuename, uint32& dataBufferSize, void** dataBuffer )
{
	peer_->getDataBufValue( valuename, dataBufferSize, dataBuffer );
}

Enumerator<String>* Registry::getKeyNames()
{
	return peer_->getKeyNames();
}

Enumerator<RegistryValueInfo*>* Registry::getValues()
{
	return peer_->getValues();
}

String Registry::getCurrentKey()
{
	return peer_->getCurrentKey();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.10  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.9.2.1  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.9  2003/05/17 20:37:42  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.14.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.14.1  2003/03/12 03:12:49  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.7  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.6  2002/03/18 00:20:44  ddiego
*made changes to foundation kit stuff so that the thread, mutex, semaphore, registry,
*file, filestream, and library class all call the SystemToolkit to create their peer
*instances.
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


