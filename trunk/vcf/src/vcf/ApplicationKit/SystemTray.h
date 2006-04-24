#ifndef _SYSTEMTRAY_H__
#define _SYSTEMTRAY_H__




#define SYSTEMTRAY_CLASSID		"d32f1b1a-5b08-4796-ad35-5284d5e30aaa"


namespace VCF {

	class SystemTrayPeer;

	/**
	\class SystemTray SystemTray.h "vcf/ApplicationKit/SystemTray.h"
	The SystemTray component provides a simple wrapper around system 
	tray functionality. On Win32 the system tray is the rectangular
	area on the lower right side of the Start bar. It contains 
	various icons that represent some program. You can control the 
	image used for your icon, as well as the tooltip associated with it.
	You can also add a popup menu that is associated with clicking on the
	icon.
	@delegates	
		@del SystemTray::TrayIconChanged
	*/
	class APPLICATIONKIT_API SystemTray : public Component {
	public:


		SystemTray();

		SystemTray( Component* owner );


		enum SysTrayEvents{
			stHidden = 20031,
			stShown,
			stRemovedFromTray,
			stAddedToTray
		};
		
		/**
		@delegate TrayIconChanged
		@event Event
		@eventtype SystemTray::stHidden
		@eventtype SystemTray::stShown
		@eventtype SystemTray::stRemovedFromTray
		@eventtype SystemTray::stAddedToTray
		*/
		DELEGATE(TrayIconChanged);

		/**
		Sets the icon image for the system tray. 
		*/
		void setIconImage( Image* image );

		void setPopupMenu( PopupMenu* popupMenu );

		PopupMenu* getPopupMenu() {
			return popupMenu_;
		}

		void setTooltipText( const String& tooltipText );
	
		String getTooltipText() {
			return tooltipText_;
		}

		void addToTray();

		void removeFromTray();

		void showInTray();

		void hideFromTray();

	protected:

		virtual void destroy();

		String tooltipText_;
		PopupMenu* popupMenu_;
		SystemTrayPeer* peer_;
	};

};

#endif //_SYSTEMTRAY_H__



