//AbstractContainer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractContainer.h"
#include <algorithm>

using namespace VCF;



AbstractContainer::AbstractContainer():
	controlContainer_(NULL),
	currentTabControlIndex_(0),
	controlHandler_(NULL),
	mouseHandler_(NULL)
{
	init();
}

AbstractContainer::AbstractContainer( Component* owner ):
	Container(owner),
	controlContainer_(NULL),
	currentTabControlIndex_(0),
	controlHandler_(NULL),
	mouseHandler_(NULL)
{
	init();
}

AbstractContainer::~AbstractContainer()
{
	if ( NULL != controlContainer_ ){
		controlContainer_->ControlSized -= controlHandler_;

		controlContainer_->MouseDoubleClicked -= mouseHandler_;
		controlContainer_->MouseClicked -= mouseHandler_;
		controlContainer_->MouseMove -= mouseHandler_;
		controlContainer_->MouseUp -= mouseHandler_;
		controlContainer_->MouseDown -= mouseHandler_;
		controlContainer_->MouseLeave -= mouseHandler_;
		controlContainer_->MouseEnter -= mouseHandler_;
	}

	controls_.clear();
}

void AbstractContainer::containerResized( ControlEvent* event )
{
	resizeChildren( NULL );
}

/**
*Translate points to screen coords
*Translate points back to client coords
*for each child, pass the event to it's process mouse event
*/
void AbstractContainer::onMouseEvent( MouseEvent* event )
{
	Control* previousMouseEnteredChild = Control::getPreviousMouseOverControl();
	Point tmp(0.0,0.0);
	tmp = *event->getPoint();
	//check for scollable to get rid of it's offsets
	Scrollable* scrollable = getContainerControl()->getScrollable();
	if ( NULL != scrollable ) {
		tmp.x_ -= scrollable->getHorizontalPosition();
		tmp.y_ -= scrollable->getVerticalPosition();
	}


	Rect childBounds;


	Control* capturedControl = Control::getCapturedMouseControl();
	if ( NULL != capturedControl ){
		Control* container = getContainerControl();

		Control* parent = capturedControl->getParent();
		if ( parent == container ){ //then the captured control is a child of this container so keep sedning it the messages
			childBounds = capturedControl->getBounds();
			//if ( true == childBounds->containsPt( &tmp ) ){
				capturedControl->translateToLocal( &tmp );
				MouseEvent localEvent( capturedControl, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
				capturedControl->handleEvent( &localEvent );
				event->setConsumed(true);//localEvent.isConsumed());
			//}
		}
	}
	else {
		std::vector<Control*>::reverse_iterator it = controls_.rbegin();

		while ( it != controls_.rend() ){
			Control* child = *it;

			if ( NULL == child ) {
				throw RuntimeException (MAKE_ERROR_MSG_2(INVALID_POINTER_ERROR)) ;
			}


			childBounds = child->getBounds();
			if ( Control::MOUSE_LEAVE == event->getType() ) {
				if ( (false == childBounds.containsPt( &tmp )) && (child->isLightWeight() && child->getVisible()) ){
					if ( (NULL != previousMouseEnteredChild) && (previousMouseEnteredChild == child) ) {
						//if ( child->isLightWeight() ){
						child->translateToLocal( &tmp );
						MouseEvent localEvent( child, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
						child->handleEvent( &localEvent );

						event->setConsumed(true);//localEvent.isConsumed());
						break;
					}
				}
			}
			else if ( Control::MOUSE_ENTERED == event->getType() ) {
				Rect tmpRect = child->getBounds();
				tmpRect.inflate( 2, 2 );
				if ( (tmpRect.containsPt( &tmp )) && (child->isLightWeight() && child->getVisible()) ){
					Control::setPreviousMouseOverControl( child );
					child->translateToLocal( &tmp );
					MouseEvent localEvent( child, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
					child->handleEvent( &localEvent );

					event->setConsumed(true);//localEvent.isConsumed());
					break;
				}
			}
			else {
				if ( (true == childBounds.containsPt( &tmp )) && (child->isLightWeight() && child->getVisible()) ){
					child->translateToLocal( &tmp );
					if ( Control::MOUSE_MOVE == event->getType() ) {
						if ( child != previousMouseEnteredChild ) {
							if ( NULL != previousMouseEnteredChild ) {
								Point tmp2 = *event->getPoint();
								previousMouseEnteredChild->translateToLocal( &tmp2 );
								MouseEvent localEvent( previousMouseEnteredChild, Control::MOUSE_LEAVE, event->getButtonMask(), event->getKeyMask(), &tmp2 );
								previousMouseEnteredChild->handleEvent( &localEvent );
							}
							Control::setPreviousMouseOverControl( child );
							previousMouseEnteredChild = Control::getPreviousMouseOverControl();
							if ( NULL != previousMouseEnteredChild ) {
								Point tmp2 = *event->getPoint();
								child->translateToLocal( &tmp2 );
								MouseEvent localEvent( child, Control::MOUSE_ENTERED, event->getButtonMask(), event->getKeyMask(), &tmp2 );
								child->handleEvent( &localEvent );
							}
						}
					}


					if ( event->getType() != Control::MOUSE_CLICK ) {
						MouseEvent localEvent( child, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
						child->handleEvent( &localEvent );
						event->setConsumed(true);//localEvent.isConsumed());
					}
					break;
				}
				else if ( (Control::MOUSE_MOVE == event->getType()) && (child == previousMouseEnteredChild) ) {
					Point tmp2 = *event->getPoint();
					previousMouseEnteredChild->translateToLocal( &tmp2 );
					MouseEvent localEvent( previousMouseEnteredChild, Control::MOUSE_LEAVE, event->getButtonMask(), event->getKeyMask(), &tmp2 );
					previousMouseEnteredChild->handleEvent( &localEvent );
					Control::setPreviousMouseOverControl( NULL );
				}
			}

			it ++;
		}
	}
}




void AbstractContainer::init()
{
	currentTabControlIndex_ = 0;


	controlHandler_ =
		new ControlEventHandler<AbstractContainer>( this, &AbstractContainer::containerResized,
													"AbstractContainer::containerResized");

	mouseHandler_ =
		new MouseEventHandler<AbstractContainer>( this,&AbstractContainer::onMouseEvent,
													"AbstractContainer::onMouseEvent");

	controlContainer_ = NULL;
	controlsContainer_.initContainer( controls_ );
}

void AbstractContainer::add( Control * child )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	//verify we don't already have this control
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}

		child->setParent( controlContainer_ );		

		child->setTabOrder( controls_.size() );
		resizeChildren( child );

		controls_.push_back( child );
	}
}

void AbstractContainer::add( Control * child, const AlignmentType& alignment )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}

		child->setParent( controlContainer_ );
		child->setAlignment( alignment );

		child->setTabOrder( controls_.size() );
		resizeChildren( child );

		controls_.push_back( child );
	}
}

void AbstractContainer::remove( Control* child )
{
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );
	if ( found != controls_.end() ){
		controls_.erase( found );

		child->setParent( NULL );

		resizeChildren(NULL);

		std::map<long,Control*>::iterator it = tabOrderMap_.begin();
		while ( it != tabOrderMap_.end() ) {
			if ( child == it->second ) {
				tabOrderMap_.erase( it );
				break;
			}
			it ++;
		}
	}
}

void AbstractContainer::clear()
{
	controls_.clear();
	tabOrderMap_.clear();
	resizeChildren(NULL);
}


void AbstractContainer::paintChildren( GraphicsContext* context )
{
	Enumerator<Control*>* children = controlsContainer_.getEnumerator();
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};

	double originX = 0.0;
	double originY = 0.0;

	Scrollable* scrollable = controlContainer_->getScrollable();

	Rect oldClipRect = context->getClippingRect();
	Rect mainBounds;
	if ( controlContainer_->getParent() ) {
		mainBounds = controlContainer_->getBounds();
		mainBounds.offset( -controlContainer_->getLeft(), -controlContainer_->getTop() );
	}
	else {
		mainBounds = controlContainer_->getClientBounds();
	}

	if ( oldClipRect.isNull() || oldClipRect.isEmpty() ) {
		oldClipRect.setRect( 0, 0, mainBounds.getWidth(), mainBounds.getHeight() );
	}

	Rect childClipRect;
	Rect bounds;

	Control* heavyWeightParent  = controlContainer_;
	if ( NULL != heavyWeightParent ) {
		
	}
	
	while ( true == children->hasMoreElements() ){
		Control* child = children->nextElement();
		VCF_ASSERT( NULL != child );

		if ( child->isLightWeight() && child->getVisible() ){
			
			bounds = child->getBounds();
			

			childClipRect.left_ = maxVal<>(bounds.left_,mainBounds.left_);
			childClipRect.top_ = maxVal<>(bounds.top_,mainBounds.top_);
			childClipRect.right_ = minVal<>(bounds.right_,mainBounds.right_);
			childClipRect.bottom_ = minVal<>(bounds.bottom_,mainBounds.bottom_);
								
			childClipRect.offset( -bounds.left_, -bounds.top_ );

			Point oldOrigin = context->getOrigin();
			originX = bounds.left_ + oldOrigin.x_;
			originY = bounds.top_ + oldOrigin.y_;
			if ( NULL != scrollable ) {
				originX += 	scrollable->getHorizontalPosition();
				originY += 	scrollable->getVerticalPosition();
			}


			context->setOrigin( originX, originY );

			
			//do this to prevent matrix changes from
			//screwing up the state for the child control
			Matrix2D xfrm;
			int gcs = context->saveState();
			context->setCurrentTransform( xfrm );
									
			controlContainer_->preChildPaint( context , child, &childClipRect );
			//context->setClippingRect( &childClipRect );

			child->paintBorder( context );

			child->paint( context );

			context->restoreState( gcs );


			context->setOrigin( oldOrigin.x_, oldOrigin.y_ );
			
			controlContainer_->postChildPaint( context , child, &oldClipRect );
			//context->setClippingRect( &oldClipRect );
		}
	}
}

Enumerator<Control*>* AbstractContainer::getChildren()
{
	return controlsContainer_.getEnumerator();
}

unsigned long AbstractContainer::getChildCount()
{
	return controls_.size();
}


Control* AbstractContainer::findControl( const String& controlName )
{
	Control* result = NULL;
	//this is very slow !! for the moment !
	std::vector<Control*>::iterator it = controls_.begin();
	bool notFound = true;
	while ( it != controls_.end() ){
		Control* child = *it;
		if ( controlName == child->getName() ){
			result = child;
			break;
		}
		it ++;
	}

	return result;
}

void AbstractContainer::updateTabOrder( Control* child, ulong32& newTabOrder )
{
	long currentTabOrder = child->getTabOrder();
	if ( newTabOrder >= 0 ) {

		if ( newTabOrder > tabOrderMap_.size() ) {
			newTabOrder = tabOrderMap_.size() - 1;
		}
		else if ( newTabOrder < 0 ) {
			newTabOrder = 0;
		}
		std::map<long,Control*>::iterator found = tabOrderMap_.find( currentTabOrder );
		if ( found != tabOrderMap_.end() ) {
			tabOrderMap_.erase( found );
		}

		tabOrderMap_[newTabOrder] = child;
	}
}

void AbstractContainer::getTabList( std::vector<Control*>& tabList )
{
	std::map<long,Control*>::iterator it = tabOrderMap_.begin();
	while ( it != tabOrderMap_.end() ) {
		Control::buildTabList( it->second, tabList );
		it ++;
	}
}


Control* AbstractContainer::getControlAtIndex( const ulong32& index )
{
	Control* result = NULL;

	if ( index < controls_.size() ) {
		std::vector<Control*>::iterator found = controls_.begin() + index;
		if ( found != controls_.end() ) {
			result = *found;
		}
	}

	return result;
}

long AbstractContainer::getControlIndex( Control* control )
{
	long result = -1;

	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );
	if ( found != controls_.end() ) {
		result = found - controls_.begin();
	}

	return result;
}

void AbstractContainer::insertBeforeControl( Control * child, const AlignmentType& alignment, Control* beforeControl )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	std::vector<Control*>::iterator insertAt = std::find( controls_.begin(), controls_.end(), beforeControl );

	//the control is not present
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}
	}
	else { // OK we already have this child so remove it first before changing it's position in the list
		controls_.erase( found );
	}



	child->setParent( controlContainer_ );
	child->setAlignment( alignment );
	child->setTabOrder( controls_.size()/*-1*/ );

	resizeChildren( child );

	if ( insertAt != controls_.end() ) {
		controls_.insert( insertAt, child );
	}
	else {
		controls_.insert( controls_.begin(), child );
	}
}

void AbstractContainer::insertAtIndex( Control * child, const AlignmentType& alignment, const ulong32& index )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	std::vector<Control*>::iterator insertAt = controls_.begin() + index;

	//the control is not present
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}
	}
	else { // OK we already have this child so remove it first before changing it's position in the list
		controls_.erase( found );
	}



	child->setParent( controlContainer_ );
	child->setAlignment( alignment );
	child->setTabOrder( controls_.size()/*-1*/ );

	resizeChildren( child );

	if ( insertAt != controls_.end() ) {
		controls_.insert( insertAt, child );
	}
	else {
		controls_.push_back( child );
	}
}

void AbstractContainer::sendControlToFront( Control* child )
{
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	if ( found != controls_.end() ) {
		controls_.erase( found );
		controls_.insert( controls_.begin(), child );
		resizeChildren(NULL);
	}
	else {
		throw NoSuchElementException();
	}
}

void AbstractContainer::sendControlToBack( Control* child )
{
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	if ( found != controls_.end() ) {
		controls_.erase( found );
		controls_.push_back( child );
		resizeChildren(NULL);
	}
	else {
		throw NoSuchElementException();
	}
}

void AbstractContainer::setContainerControl( Control* control )
{
	if ( NULL != controlContainer_ ){
		controlContainer_->ControlSized -= controlHandler_;

		controlContainer_->MouseDoubleClicked -= mouseHandler_;
		controlContainer_->MouseClicked.removeHandler( mouseHandler_ );
		controlContainer_->MouseMove.removeHandler( mouseHandler_ );
		controlContainer_->MouseUp.removeHandler( mouseHandler_ );
		controlContainer_->MouseDown.removeHandler( mouseHandler_ );
		controlContainer_->MouseLeave.removeHandler( mouseHandler_ );
		controlContainer_->MouseEnter.removeHandler( mouseHandler_ );
	}
	controlContainer_ = control;
	controlContainer_->ControlSized.addHandler( controlHandler_ );

	controlContainer_->MouseDoubleClicked.addHandler( mouseHandler_ );
	controlContainer_->MouseClicked.addHandler( mouseHandler_ );
	controlContainer_->MouseMove.addHandler( mouseHandler_ );
	controlContainer_->MouseUp.addHandler( mouseHandler_ );
	controlContainer_->MouseDown.addHandler( mouseHandler_ );
	controlContainer_->MouseLeave.addHandler( mouseHandler_ );
	controlContainer_->MouseEnter.addHandler( mouseHandler_ );
}


/**
$Id$
*/
