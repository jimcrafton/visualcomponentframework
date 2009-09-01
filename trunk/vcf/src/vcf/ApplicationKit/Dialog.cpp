//Dialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DialogPeer.h"
#include "vcf/ApplicationKit/WindowPeer.h"

using namespace VCF;



Dialog::Dialog( Control* owner )
{
	owner_ = owner;

	modal_ = Dialog::msNonModal;

	previousFocusedControl_ = Control::currentFocusedControl;

	returnValue_ = UIToolkit::mrNone;
	
	if ( NULL == owner_ ) {
		owner_ = UIToolkit::getUIPolicyManager()->getOwnerForDialog();
	}

	dialogPeer_ = UIToolkit::createDialogPeer( owner_, this );

	peer_ = dynamic_cast<ControlPeer*>(dialogPeer_);


	windowPeer_ = dynamic_cast<WindowPeer*>(dialogPeer_);

	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_->create( this );

	peer_->setControl( this );

	setFrameStyle( fstFixed );

	//add a close handler to get notified of the closing window
	FrameClose += new ClassProcedure1<Event*,Dialog>( this, &Dialog::onDialogClose, "Dialog::onDialogClose" );


	StandardContainer* container = (StandardContainer*)this->getContainer();
	container->setBorderWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) );
}


Dialog::~Dialog()
{

}

void Dialog::onDialogClose( Event* event )
{
	if ( isModal() ) {
		DialogEvent e(this,Dialog::deModalFinished);
		e.setModalResult( getModalReturnValue() );
		ModalFinished(&e);
	}
	else if ( isSheetModal() ) {
		DialogEvent e(this,Dialog::deSheetModalFinished);
		e.setModalResult( getModalReturnValue() );
		SheetModalFinished(&e);
	}
	else if ( !isModal() ) {
		EventHandler* ev = new ClassProcedure1<Event*,Dialog>( this, &Dialog::onPostClose );
		UIToolkit::postEvent( ev, new Event( event->getSource() ) );
	}
}

void Dialog::onPostClose( Event* e )
{
	free();
}

void Dialog::paint(GraphicsContext * context)
{
	Frame::paint( context );
}

void Dialog::setCaption( const String& caption )
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}	

	caption_ = caption;

	String text = caption_;
	
	if ( getUseLocaleStrings() ) {
		text = System::getCurrentThreadLocale()->translate( text );
	}

	peer_->setText( text );
}

Rect Dialog::getClientBounds(const bool& includeBorder)
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	return windowPeer_->getClientBounds();
}

void  Dialog::setClientBounds( Rect* bounds )
{
	if ( NULL == dialogPeer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}
	windowPeer_->setClientBounds( bounds );
}

/*
void Dialog::resizeChildren()
{
	Rect* bounds = getClientBounds();
	Rect rect( 0.0, 0.0, bounds->getWidth(), bounds->getHeight() );

	resizeChildrenUsingBounds( &rect );
}
*/

class ControlHolder : public ObjectWithCallbacks {
public:
	ControlHolder(): control_(NULL) {

	}

	ControlHolder( Control* control ): control_(control) {
		updateEventHandler();
	}

	ControlHolder( const ControlHolder& rhs ) {
		*this = rhs;
	}

	virtual ~ControlHolder() {
		if ( NULL != control_ ) {
			CallBack* cb = getCallback( "onDestroy" );
			if ( NULL != cb ) {
				control_->ComponentDestroyed -= cb;
			}
		}
	}

	ControlHolder& operator=( const ControlHolder& rhs ) {
		control_ = rhs.control_;
		updateEventHandler();
		return *this;
	}

	ControlHolder& operator=( Control* rhs ) {
		control_ = rhs;
		updateEventHandler();
		return *this;
	}

	operator Control* () {
		return control_;
	}

	void onDestroy( VCF::ComponentEvent* e ) {
		control_ = NULL;
	}

	Control* operator ->() {
		return control_;
	}
protected:
	void updateEventHandler() {
		if ( NULL != control_ ) {
			CallBack* ev = getCallback( "onDestroy" );
			if ( NULL == ev ) {
				ev = new ClassProcedure1<ComponentEvent*,ControlHolder>(this, &ControlHolder::onDestroy, "onDestroy" );
			}
			control_->ComponentDestroyed += ev;
		}
	}
	Control* control_;
};


void Dialog::showSheetModal()
{
	if ( NULL == owner_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("No owner window specified! Invalid use of the Dialog::showSheetModal method!") );
	}
	
	showWithModalState( Dialog::msSheetModal );
	
	owner_->setEnabled( false );	
}	

UIToolkit::ModalReturnType Dialog::showModal(bool autoDestroy)
{
	UIToolkit::ModalReturnType result = UIToolkit::mrNone;

	ControlHolder prevFocusedControl = previousFocusedControl_;

	Control* owningControl = owner_;

	if ( NULL != owner_ ) {

		owningControl->setEnabled( false );
	}

	showWithModalState( Dialog::msAppModal );
	
	result = UIToolkit::runModalEventLoopFor( this );
	if ( result == UIToolkit::mrTrue ) {
		result = getModalReturnValue();
	}

	if ( prevFocusedControl != NULL ) {
		prevFocusedControl->setFocused();
	}
	else if ( NULL != Control::getCurrentFocusedControl() ) {
		Control::getCurrentFocusedControl()->setFocused();
	}

	//kill off the internal contained compoennts and controls
	if ( autoDestroy ) {
		destroy();
	}

	previousFocusedControl_ = prevFocusedControl;

	return result;
}

void Dialog::show()
{
	showWithModalState( Dialog::msNonModal );
}

void Dialog::showWithModalState( ModalState state )
{
	modal_ = state;
	
	Rect adjustedBounds = UIToolkit::getUIPolicyManager()->adjustInitialDialogBounds( this );

	if ( (!(adjustedBounds == getBounds())) && (!adjustedBounds.isEmpty()) && (!adjustedBounds.isNull()) ) {
		setBounds( &adjustedBounds );
	}
	
	//force a resize here because the actual width/height may not change and therefore
	//we won't get a size event to be fired.
	resizeChildren(NULL);

	peer_->setVisible(true);
}

void Dialog::showMessage( const String& message )
{
	String captionText;
	Application* app = Application::getRunningInstance();
	if ( NULL != app ) {
		captionText = app->getName();
	}

	Dialog::showMessage( message, captionText );
}

void Dialog::showMessage( const String& message, const String& caption )
{
	DialogPeer* dialogPeer = UIToolkit::createDialogPeer();// owner, this );
	if ( NULL != dialogPeer ){
		String captionText = caption;
		
		if ( captionText.empty() ) {
			Application* app = Application::getRunningInstance();
			if ( NULL != app ) {
				captionText = app->getName();
			}
		}
		
		captionText = System::getCurrentThreadLocale()->translate( captionText );
		
		String msgText = message;
			
		msgText = System::getCurrentThreadLocale()->translate( msgText );

		dialogPeer->showMessage( msgText, captionText );
	}

	delete dialogPeer;
	dialogPeer = NULL;
}

UIToolkit::ModalReturnType Dialog::showMessage( const String& message, const String& caption,
														const int32& messageButtons,
														const MessageStyle& messageStyle )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrOK;

	DialogPeer* dialogPeer = UIToolkit::createDialogPeer();// owner, this );
	if ( NULL != dialogPeer ){
		String captionText = caption;			
		captionText = System::getCurrentThreadLocale()->translate( captionText );

		String msgText = message;			
		msgText = System::getCurrentThreadLocale()->translate( msgText );

		result = dialogPeer->showMessage( msgText, captionText, messageButtons, messageStyle );
	}

	delete dialogPeer;
	dialogPeer = NULL;

	return result;
}

void Dialog::close()
{
	windowPeer_->close();
}

void Dialog::setFrameStyle( const FrameStyleType& frameStyle )
{
	frameStyle_ = frameStyle;

	if ( !(Component::csDesigning & getComponentState()) ){
		windowPeer_->setFrameStyle( frameStyle_ );
	}

}

void Dialog::setIconImage( Image* icon )
{
	windowPeer_->setIconImage( icon );
}

Image* Dialog::getIconImage()
{
	return NULL;
}

void Dialog::keyDown( KeyboardEvent* e )
{
	if ( vkEscape == e->virtualKeyCode ) {
		e->setConsumed(true);
		returnValue_ = UIToolkit::mrCancel;
		close();
	}
}

bool Dialog::isActiveFrame()
{
	return windowPeer_->isActiveWindow();
}

/*
void Dialog::onModalClose( WindowEvent* e )
{
	Application::getRunningInstance()->getMainWindow()->setEnabled( true );
}
*/


/**
$Id$
*/
