//HTMLBrowserControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//HTMLBrowserControl.h
#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/HTMLBrowserControl.h"
#include "vcf/HTMLKit/HTMLBrowserPeer.h"


using namespace VCF;


HTMLBrowserControl::HTMLBrowserControl():
	browserPeer_(NULL),
	policyState_(0),
	modelChangeState_(0)
{
	browserPeer_ = HTMLToolkit::createHTMLBrowserPeer( this );

	if ( NULL == browserPeer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_ = dynamic_cast<ControlPeer*>(browserPeer_);
	
	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_->create( this );
	setVisible( true );

	policyState_ |= HTMLBrowserControl::hpAllowPopups;
	policyState_ |= HTMLBrowserControl::hpAllowDefaultContextMenu;
	policyState_ |= HTMLBrowserControl::hpUseDefaultAuthenticationUI;
	policyState_ |= HTMLBrowserControl::hpAllowsScrollbars;
	policyState_ |= HTMLBrowserControl::hpAllowsTextSelection;


	addCallback( new ClassProcedure1<Event*,HTMLBrowserControl>(this, &HTMLBrowserControl::inputElementChanged), "HTMLBrowserControl::inputElementChanged" );
	
}

HTMLBrowserControl::~HTMLBrowserControl()
{

}

void HTMLBrowserControl::paint( GraphicsContext* ctx )
{

}

String HTMLBrowserControl::getCurrentURL()
{
	return browserPeer_->getCurrentURL();
}

void HTMLBrowserControl::setCurrentURL( const String& url )
{
	browserPeer_->setCurrentURL( url );
}

void HTMLBrowserControl::goBack()
{
	browserPeer_->goBack();
}

void HTMLBrowserControl::goForward()
{
	browserPeer_->goForward();
}

void HTMLBrowserControl::goHome()
{
	browserPeer_->goHome();
}

void HTMLBrowserControl::refresh()
{
	browserPeer_->refresh();
}

bool HTMLBrowserControl::isLoadingURL()
{
	return browserPeer_->isLoadingURL();
}

void HTMLBrowserControl::stopLoadingURL()
{
	browserPeer_->stopLoadingURL();
}

void HTMLBrowserControl::setFromHTML( const String& html )
{
	browserPeer_->setFromHTML( html );
}

String HTMLBrowserControl::getTitle()
{
	return browserPeer_->getTitle();
}

void HTMLBrowserControl::edit( const bool& val )
{
	browserPeer_->edit( val );
}

void HTMLBrowserControl::copy()
{
	browserPeer_->copy() ;
}

void HTMLBrowserControl::selectAll()
{
	browserPeer_->selectAll() ;
}

void HTMLBrowserControl::setAllowsPopupWindows( const bool& val )
{	
	if ( val ) {
		policyState_ |= HTMLBrowserControl::hpAllowPopups;
	}
	else {
		policyState_ &= ~HTMLBrowserControl::hpAllowPopups;
	}

	browserPeer_->setAllowsPopupWindows( val ) ;
}


void HTMLBrowserControl::setAllowsScrollbars( const bool& val )
{
	if ( val ) {
		policyState_ |= HTMLBrowserControl::hpAllowsScrollbars;
	}
	else {
		policyState_ &= ~HTMLBrowserControl::hpAllowsScrollbars;
	}	

	browserPeer_->setAllowsScrollbars( val ) ;
}


void HTMLBrowserControl::setAllowsTextSelection( const bool& val )
{
	if ( val ) {
		policyState_ |= HTMLBrowserControl::hpAllowsTextSelection;
	}
	else {
		policyState_ &= ~HTMLBrowserControl::hpAllowsTextSelection;
	}

	browserPeer_->setAllowsTextSelection( val ) ;
}


String HTMLBrowserControl::getElementHTMLText( const String& elementName )
{
	return browserPeer_->getElementHTMLText( elementName ) ;
}

void HTMLBrowserControl::setElementHTMLText( const String& elementName, const String& html )
{
	browserPeer_->setElementHTMLText( elementName, html ) ;
}

String HTMLBrowserControl::getElementText( const String& elementName )
{
	return browserPeer_->getElementText( elementName ) ;
}

void HTMLBrowserControl::setElementText( const String& elementName, const String& text )
{
	browserPeer_->setElementText( elementName, text ) ;
}

String HTMLBrowserControl::getActiveElementID()
{
	return browserPeer_->getActiveElementID() ;
}

String HTMLBrowserControl::getElementIDFromPoint( Point* pt )
{
	return browserPeer_->getElementIDFromPoint(pt) ;
}

bool HTMLBrowserControl::setElementClickedEventHandler( const String& elementName, EventHandler* handler )
{
	return browserPeer_->setElementClickedEventHandler( elementName, handler );
}

HTMLDocument HTMLBrowserControl::getDocument()
{	
	return browserPeer_->getDocument();
}	

void HTMLBrowserControl::setKeyForElementName( const String& elementName, const VariantData& key )
{
	elementKeys_[elementName] = key;
	browserPeer_->updateElementForKey( key, elementName );
}

VariantData HTMLBrowserControl::getKeyForElementName( const String& elementName )
{
	VariantData result;

	std::map<String,VariantData>::iterator found = elementKeys_.find( elementName );
	if ( found != elementKeys_.end() ) {	
		result = found->second;
	}

	return result;
}

void HTMLBrowserControl::setKeyForElement( HTMLElement& element, const String& elementName, const VariantData& key )
{
	if ( element.getID() != elementName ) {
		element.setID( elementName );
	}
	setKeyForElementName( key, elementName );
}

void HTMLBrowserControl::onModelChanged( ModelEvent* e )
{
	if ( (NULL != e->key && NULL != e->value) && !(modelChangeState_ & InternalDOMDocumentChanged) ) {
		std::map<String,VariantData>::iterator found = elementKeys_.begin();
		while ( found != elementKeys_.end() ) {
			if ( found->second == *e->key ) {
				browserPeer_->setElementText( found->first, e->value->toString() ) ;
			}
			++found;
		}
	}
}

void HTMLBrowserControl::modelChanged( Model* oldModel, Model* newModel )
{
	CallBack* ev = getCallback( "HTMLBrowserControl::onModelChanged" );
	if ( NULL == ev ) {
		ev = new ClassProcedure1<ModelEvent*,HTMLBrowserControl>( this, &HTMLBrowserControl::onModelChanged, "HTMLBrowserControl::onModelChanged" );
	}

	if ( NULL != oldModel ) {
		oldModel->ModelChanged -= ev;
	}

	if ( NULL != newModel ) {
		newModel->ModelChanged += ev;
	}
}


void HTMLBrowserControl::updateModelFromDOM()
{	
	modelChangeState_ |= InternalDOMDocumentChanged;

	Model* model = this->getViewModel();
	if ( NULL != model ) {
		
		
		std::map<String,VariantData>::iterator it = elementKeys_.begin();
		while ( it != elementKeys_.end() ) {
			model->setValueAsString( browserPeer_->getElementText( it->first ), it->second );
			++it;
		}
	}

	modelChangeState_ &= ~InternalDOMDocumentChanged;
}

void HTMLBrowserControl::updateDOMFromModel()
{
	Model* model = this->getViewModel();
	if ( NULL != model ) {
		
		std::map<String,VariantData>::iterator it = elementKeys_.begin();
		while ( it != elementKeys_.end() ) {
			browserPeer_->setElementText( it->first, model->getValueAsString( it->second ) );
			++it;
		}
	}	
}

bool HTMLBrowserControl::getKeyedElements( std::vector<KeyedHTMLElement>& keyedElements )
{
	std::map<String,VariantData>::iterator it = elementKeys_.begin();
	while ( it != elementKeys_.end() ) {
		keyedElements.push_back( KeyedHTMLElement( it->first, it->second ) );
		++it;
	}
	return !keyedElements.empty();
}

void HTMLBrowserControl::inputElementChanged( Event* e )
{
	HTMLElementEvent* he = (HTMLElementEvent*)e;

	Model* model = this->getViewModel();
	if ( NULL != model ) {
		
		
		std::map<String,VariantData>::iterator it = elementKeys_.begin();
		while ( it != elementKeys_.end() ) {
			if ( he->elementID == it->first ) {
				//modelChangeState_ |= InternalDOMDocumentChanged;
				
				model->setValueAsString( browserPeer_->getElementText( it->first ), it->second );

				//modelChangeState_ &= ~InternalDOMDocumentChanged;
			}
			++it;
		}
	}

	
}

void HTMLBrowserControl::handleEvent( Event* e )
{
	Control::handleEvent(e);

	switch ( e->getType() ){
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)e;
			Component* child = ev->getChildComponent();
			DOMElementComponent* element = dynamic_cast<DOMElementComponent*>(child);

			if ( NULL != element ) {
				element->setBrowser(this);
			}
		}
		break;
	}
}







HTMLDocument DOMDocumentComponent::getDocument()
{
	return HTMLDocument();
}


void DOMDocumentComponent::setBrowser( HTMLBrowserControl* browser )
{

}

void DOMDocumentComponent::handleEvent( Event* e )
{
	Component::handleEvent(e);
}



String DOMElementComponent::getText()
{
	return L"";
}

void DOMElementComponent::setText( const String& val ) 
{

}

void DOMElementComponent::handleEvent( Event* e )
{
	Component::handleEvent(e);

	switch ( e->getType() ){
		case Component::COMPONENT_LOADED : {
			
			if ( NULL != browser_ ) {

			}
		}
		break;

		case HTMLBrowserControl::heURLLoaded : {			
			if ( NULL != browser_ ) {
				browser_->getBrowserPeer()->updateCallbacks( this );
			}
		}
		break;
		
	}
}


void DOMElementComponent::setBrowser( HTMLBrowserControl* browser )
{
	browser_ = browser;
}


/**
$Id$
*/
