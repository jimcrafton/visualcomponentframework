//Resource.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"


using namespace VCF;

Resource::Resource( void* data, const uint32& size, const String& name )
{
	data_ = new char[size];
	memset( data_, 0, size*sizeof(char) );
	memcpy( data_, data, size*sizeof(char) );
	size_ = size;
	name_ = name;
}

Resource::~Resource()
{
	delete data_;
}

void* Resource::getData()
{
	return data_;
}

String Resource::getName()
{
	return name_;
}

void Resource::setName( const String& name )
{
	name_ = name;
}

uint32 Resource::getDataSize()
{
	return size_;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.2.1  2005/04/09 17:21:32  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.7  2003/05/17 20:37:42  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/12 03:12:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2003/01/08 00:19:55  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


