#ifndef _VCF_POPUPWINDOWPEER_H__
#define _VCF_POPUPWINDOWPEER_H__
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


class APPLICATIONKIT_API PopupWindowPeer : public VCF::Interface {
public:
	virtual ~PopupWindowPeer(){};

	virtual void showModal() = 0;

	virtual void showAsSheet( Window* owningWindow ) = 0;

	virtual void show() = 0;
};


};



#endif //_VCF_POPUPWINDOWPEER_H__