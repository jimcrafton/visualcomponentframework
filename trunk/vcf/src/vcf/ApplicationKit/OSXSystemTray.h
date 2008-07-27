#ifndef _VCF_OSXSYSTEMTRAYPEER_H__
#define _VCF_OSXSYSTEMTRAYPEER_H__
//ControlPeer.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF {

	class OSXSystemTray : public SystemTrayPeer {
	public:
		OSXSystemTray();

		virtual ~OSXSystemTray();

		virtual void setIconImage( Image* image );

		virtual void setPopupMenu( PopupMenu* popupMenu );

		virtual void setTooltipText( const String& tooltipText );
	
		virtual void addToTray();

		virtual void removeFromTray();

		virtual void showInTray();

		virtual void hideFromTray();

	protected:
		
	};
}


#endif //_VCF_OSXSYSTEMTRAYPEER_H__

/**
$Id: OSXSystemTray.h 2657 2006-04-29 06:30:28Z kdmix $
*/
