#ifndef _VCF_SYSTEMTRAYPEER_H__
#define _VCF_SYSTEMTRAYPEER_H__
//ControlPeer.h

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
class PopupMenu;

	class SystemTrayPeer : public VCF::Interface {
	public:

		virtual void setIconImage( Image* image ) = 0;

		virtual void setPopupMenu( PopupMenu* popupMenu ) = 0;

		virtual void setTooltipText( const String& tooltipText ) = 0;
	
		virtual void addToTray() = 0;

		virtual void removeFromTray() = 0;

		virtual void showInTray() = 0;

		virtual void hideFromTray() = 0;
	};

};




#endif //_VCF_SYSTEMTRAYPEER_H__
