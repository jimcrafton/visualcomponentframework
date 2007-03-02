#ifndef _VCF_TRANSPARENTWINDOWPEER_H__
#define _VCF_TRANSPARENTWINDOWPEER_H__
//PopupWindowPeer.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {


class APPLICATIONKIT_API TransparentWindowPeer : public VCF::Interface {
public:
	virtual ~TransparentWindowPeer(){};

	virtual void setAlpha( const double& alphaValue ) = 0;

	virtual double getAlpha() = 0;

	virtual void setAlphaImage( Image* img ) = 0;
};


};



#endif //_VCF_TRANSPARENTWINDOWPEER_H__