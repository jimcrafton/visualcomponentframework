
//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/FoundationKit/FoundationKitPrivate.h>
#include <vcf/FoundationKit/RunLoopSource.h>
#include <vcf/FoundationKit/Win32RunLoopSourcePeer.h>

using namespace VCF;

Win32RunLoopSourcePeer::Win32RunLoopSourcePeer( RunLoopSource* source )
    : source_( CreateEvent(NULL, TRUE, FALSE, NULL) )
    , owner_( source )
{
}

Win32RunLoopSourcePeer::~Win32RunLoopSourcePeer()
{
	::CloseHandle( source_ );
}

void Win32RunLoopSourcePeer::fire()
{
    ::SetEvent( source_ );
}

/**
$Id:$
*/

