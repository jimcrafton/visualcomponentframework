#ifndef _VCF_POPUPWINDOW_H__
#define _VCF_POPUPWINDOW_H__
//PopupWindow.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

class PopupWindowPeer;


class APPLICATIONKIT_API PopupWindow : public Frame {
public:
	PopupWindow();

	virtual ~PopupWindow();

	void showModal();

	void showAsSheet( Window* owningWindow );

	void show();
protected:
	PopupWindowPeer * popupPeer_;
	WindowPeer * windowPeer_;
};


};



#endif //_VCF_POPUPWINDOW_H__