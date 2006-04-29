#ifndef _VCF_BUTTONPEER_H__
#define _VCF_BUTTONPEER_H__
//ButtonPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {
	
	class Image;
	/**
	\class ButtonPeer ButtonPeer.h "vcf/ApplicationKit/ButtonPeer.h"
	*/
	class ButtonPeer : public VCF::Interface {
	public:	
		virtual Image* getImage() = 0;
		
		virtual void setImage( Image* image ) = 0;
		
		virtual ButtonState getState() = 0;
	};
	
};


#endif // _VCF_BUTTONPEER_H__

/**
$Id$
*/
