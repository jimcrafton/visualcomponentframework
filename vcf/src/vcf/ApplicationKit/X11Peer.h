#ifndef _VCF_X11PEER_H__
#define _VCF_X11PEER_H__
//X11Peer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
This is used help qualify any naming conflict between
X11 typedefs and VCF class names
*/
namespace xLib {
	typedef Window Window;
	typedef Font Font;
	typedef Cursor Cursor;
};


#endif // _VCF_X11PEER_H__

/**
$Id$
*/
