#ifndef _VCF_WIN32PEER_H__
#define _VCF_WIN32PEER_H__
//Win32Peer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
*Main header for implementation object that Win32 headers
*/


#define VCF_MESSAGE				WM_APP	+ 100



namespace VCFWin32 {

/**
*what follows are a set of standard utility functions for Win32
*/
class FOUNDATIONKIT_API Win32Utils {
public:
	static void trace( const VCF::String& text );

	static WORD	getWin32LangID( VCF::Locale* locale );

	static VCF::String getErrorString( const DWORD& errorCode );

	static VCF::uint32 convertCharToVKCode( VCF::VCFChar ch );
};


};


#endif // _VCF_WIN32PEER_H__

/**
$Id$
*/
