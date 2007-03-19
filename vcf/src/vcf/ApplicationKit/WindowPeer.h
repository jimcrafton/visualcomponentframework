#ifndef _VCF_WINDOWPEER_H__
#define _VCF_WINDOWPEER_H__
//WindowPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class Path;


/**
\class WindowPeer WindowPeer.h "vcf/ApplicationKit/WindowPeer.h"  
*/

class APPLICATIONKIT_API WindowPeer : public VCF::Interface {
public:
	virtual ~WindowPeer(){};

	virtual Rect getClientBounds() = 0;

	virtual void  setClientBounds( Rect* bounds ) = 0;

	virtual void close() = 0;

	virtual void setFrameStyle( const FrameStyleType& frameStyle ) = 0;

	virtual void setFrameTopmost( const bool& isTopmost ) = 0;

	virtual bool isMaximized() = 0;

	virtual void setMaximized( const bool maximised ) = 0;

	virtual bool isMinimized() = 0;

	virtual void setMinimized( const bool& minimized ) = 0;

	virtual void restore() = 0;

	virtual void setIconImage( Image* icon ) = 0;
	
	virtual bool isActiveWindow() = 0;

	virtual void setBorderPath( Path* path ) = 0;
};

};


#endif // _VCF_WINDOWPEER_H__

/**
$Id$
*/
