//ClassRegistryEntry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ClassRegistryEntry.h


#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;

using namespace VCFRemote;

ClassRegistryEntry::ClassRegistryEntry()
{
	classID_ = "";
	userID_ = "";
	localServerPath_ = "";
	inProcess_ = false;
	isRemote_ = false;
	remoteServerPath_ = "";
}

ClassRegistryEntry::ClassRegistryEntry( const VCF::String& classID,
		                const VCF::String& userID,
						const VCF::String& localServerPath,
						const bool& inProcess,
						const bool& remote,
						const VCF::String& remoteServerPath )
{
	classID_ = classID;
	userID_ = userID;
	localServerPath_ = localServerPath;
	inProcess_ = inProcess;
	isRemote_ = remote;
	remoteServerPath_ = remoteServerPath;
}

ClassRegistryEntry::~ClassRegistryEntry()
{

}

void ClassRegistryEntry::saveToStream( OutputStream * stream )
{
	stream->write( classID_ );
	stream->write( userID_ );
	stream->write( localServerPath_ );
	stream->write( inProcess_ );
	stream->write( isRemote_ );
	stream->write( remoteServerPath_ );
}

void ClassRegistryEntry::loadFromStream( InputStream * stream )
{
	stream->read( classID_ );
	stream->read( userID_ );
	stream->read( localServerPath_ );
	stream->read( inProcess_ );
	stream->read( isRemote_ );
	stream->read( remoteServerPath_ );
}

VCF::String ClassRegistryEntry::toString()
{
	return "classID = " + classID_ + "\nLocal Server Path = " + localServerPath_;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.6  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.2.1  2003/03/12 03:13:32  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.1  2003/01/08 00:20:03  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.3  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


