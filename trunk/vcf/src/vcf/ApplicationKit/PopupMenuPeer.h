#ifndef _VCF_POPUPMENUPEER_H__
#define _VCF_POPUPMENUPEER_H__
//PopupMenuPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Control;

class Point;

class PopupMenuPeer {
public:
	virtual ~PopupMenuPeer(){};

	/**
	*sets the Control the menu bar is attached to
	*/
	virtual void setControl( Control* control ) = 0;

	virtual MenuItem* popup( Point* pt ) = 0;
};

}; //end of namespace VCF


#endif // _VCF_POPUPMENUPEER_H__

/**
$Id$
*/
