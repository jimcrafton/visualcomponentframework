
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/SystemTrayPeer.h"
#include "vcf/ApplicationKit/SystemTray.h"




using namespace VCF;



SystemTray::SystemTray():
	Component(),
	popupMenu_(NULL),
	peer_(NULL)
{
	peer_ = UIToolkit::createSystemTrayPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2(L"Unable to create instance of a System Tray Peer.") );
	}
}

SystemTray::SystemTray( Component* owner ):
	Component( owner ),
	popupMenu_(NULL),
	peer_(NULL)
{
	peer_ = UIToolkit::createSystemTrayPeer();
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2(L"Unable to create instance of a System Tray Peer.") );
	}
}

void SystemTray::destroy()
{
	removeFromTray();

	delete peer_;
	peer_ = NULL;
}

void SystemTray::setIconImage( Image* image )
{
	peer_->setIconImage( image );
}

void SystemTray::setPopupMenu( PopupMenu* popupMenu )
{
	peer_->setPopupMenu( popupMenu );
}

void SystemTray::setTooltipText( const String& tooltipText )
{
	String text = tooltipText;

	if ( getUseLocaleStrings() ) {
		text = System::getCurrentThreadLocale()->translate( text );
	}
	peer_->setTooltipText( text );
}

void SystemTray::addToTray()
{
	peer_->addToTray();

	Event e( this,SystemTray::stAddedToTray );
	TrayIconChanged.fireEvent( &e );
}

void SystemTray::removeFromTray()
{
	peer_->removeFromTray();

	Event e( this,SystemTray::stRemovedFromTray );
	TrayIconChanged.fireEvent( &e );
}

void SystemTray::showInTray()
{
	peer_->showInTray();
	Event e( this,SystemTray::stShown );
	TrayIconChanged.fireEvent( &e );
}

void SystemTray::hideFromTray()
{
	peer_->hideFromTray();
	Event e( this,SystemTray::stHidden );
	TrayIconChanged.fireEvent( &e );
}

