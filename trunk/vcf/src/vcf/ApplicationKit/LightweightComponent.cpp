//LightweightComponent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/LightweightComponent.h"


using namespace VCF;



LightweightComponent::LightweightComponent( Control* component )
{
	component_ = component;
	enabled_ = true;
	focused_ = false;
}

LightweightComponent::~LightweightComponent()
{

}

void LightweightComponent::create( Control* owningControl )
{
	component_ = owningControl;
}

void LightweightComponent::destroyControl()
{

}

OSHandleID LightweightComponent::getHandleID()
{
	OSHandleID result = 0;
	VCF::Control* parent = getHeavyWeightParent();
	if ( NULL != parent ) {
		result = parent->getPeer()->getHandleID();
	}
	return result;
}

VCF::String LightweightComponent::getText()
{
	VCF::String result = "";

	return result;
}

void LightweightComponent::setText( const VCF::String& text )
{

}

void LightweightComponent::setBounds( VCF::Rect* rect )
{
	bounds_.inflate(1,1);

	VCF::Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		parent->repaint( &bounds_ );
	}
	bounds_.setRect( rect->left_, rect->top_, rect->right_, rect->bottom_ );
	VCF::Size sz( bounds_.getWidth(), bounds_.getHeight() );
	VCF::ControlEvent event( component_, sz );
	component_->handleEvent( &event );
}

VCF::Rect LightweightComponent::getBounds()
{
	return bounds_;
}

void LightweightComponent::setVisible( const bool& visible )
{
	bool oldVisible = visible_;
	visible_ = visible;

	if ( visible_ != oldVisible ) {
		Control* parent = this->getHeavyWeightParent();
		if ( NULL != parent ) {
			Container* container = parent->getContainer();
			if ( NULL != container ) {
				container->resizeChildren(NULL);
			}
		}
	}
}

bool LightweightComponent::getVisible()
{
	return visible_;
}

VCF::Control* LightweightComponent::getControl()
{
	return component_;
}

void LightweightComponent::setControl( VCF::Control* component )
{
	component_ = component;
}

void LightweightComponent::setParent( VCF::Control* parent )
{
	Container* container = component_->getContainer();

	int i = 0;

	if ( NULL == parent ) {
		hiddenControls_.clear();
		
		if ( NULL != container ) {
			hiddenControls_.resize( container->getChildCount() );
			Enumerator<Control*>* children = container->getChildren();
			
			while ( children->hasMoreElements() ) {
				Control* child = children->nextElement();

				hiddenControls_[i] = child->getVisible();
				child->setVisible( false );
				i++;
			}
		}
	}
	else {
		if ( !hiddenControls_.empty() ) {

			std::vector<bool>::iterator it = hiddenControls_.begin();
			Enumerator<Control*>* children = container->getChildren();
			
			VCF_ASSERT( hiddenControls_.size() == container->getChildCount() );

			i = 0;
			while ( children->hasMoreElements() ) {
				Control* child = children->nextElement();
				child->setVisible( hiddenControls_[i] );
				i++;
			}

			hiddenControls_.clear();
		}
	}
}

VCF::Control* LightweightComponent::getParent()
{
	return component_->getParent();
}

bool LightweightComponent::isFocused()
{
	return component_ == Control::getCurrentFocusedControl();
}

void LightweightComponent::setFocused()
{
	focused_ = true;
}

bool LightweightComponent::isEnabled()
{
	return enabled_;
}

void LightweightComponent::setEnabled( const bool& enabled )
{
	enabled_ = enabled;
}

void LightweightComponent::setFont( Font* font )
{

}

VCF::Control* LightweightComponent::getHeavyWeightParent()
{
	Control* result = NULL;

	VCF::Control* parent = getParent();
	if ( NULL != parent ){
		bool heavyWeightParent = !parent->isLightWeight();
		result = parent;
		while ( (false == heavyWeightParent) && (parent!=NULL) ){
			parent = result->getParent();
			if ( NULL != parent ){
				heavyWeightParent = !parent->isLightWeight();
				if ( false == heavyWeightParent ){
					result = parent;
					parent = NULL;
				}
			}
		}
	}
	result = parent;
	return result;
}

void LightweightComponent::repaint( Rect* repaintRect, const bool& immediately )
{
	VCF::Control* tmp = NULL;
	VCF::Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		Rect tmpRect;
		if ( NULL == repaintRect ){
			tmpRect = component_->getBounds();
			tmpRect.inflate( 2, 2 );
			repaintRect = &tmpRect;
		}
		if ( immediately ) {
			parent->repaintNow( repaintRect );
		}
		else {
			parent->repaint( repaintRect );
		}
	}
}

void LightweightComponent::keepMouseEvents()
{
	Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		parent->keepMouseEvents();
		Control::setCapturedMouseControl( component_ );
	}
}

void LightweightComponent::releaseMouseEvents()
{
	Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		parent->releaseMouseEvents();
	}
}

void LightweightComponent::setCursor( Cursor* cursor )
{
	Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		parent->getPeer()->setCursor( cursor );
	}
}

bool LightweightComponent::beginSetBounds( const uint32& numberOfChildren )
{
	return true;
}


void LightweightComponent::endSetBounds()
{

}

void LightweightComponent::translateToScreenCoords( Point* pt )
{
	Size offset;
	VCF::Control* parent = getParent();
	if ( NULL != parent ){
		bool lightWeightParent = parent->isLightWeight();
		Rect bounds = this->bounds_;

		offset.width_ += bounds.left_;
		offset.height_ += bounds.top_;

		while ( (lightWeightParent) && (parent!=NULL) ){

			parent = parent->getParent();

			if ( NULL != parent ){
				lightWeightParent = parent->isLightWeight();
				if ( lightWeightParent ){
					bounds = parent->getBounds();

					offset.width_ += bounds.left_;
					offset.height_ += bounds.top_;
				}
				else {
					break;
				}
			}
		}

		if ( NULL != parent ){
			Point tmpPt = *pt;
			tmpPt.x_ += offset.width_;
			tmpPt.y_ += offset.height_;

			parent->translateToScreenCoords( &tmpPt );
			*pt = tmpPt;
		}
	}
}

void LightweightComponent::translateFromScreenCoords( Point* pt )
{
	Size offset;
	VCF::Control* parent = getParent();
	if ( NULL != parent ){
		bool lightWeightParent = parent->isLightWeight();
		Rect bounds = this->bounds_;

		offset.width_ += bounds.left_;
		offset.height_ += bounds.top_;

		while ( (lightWeightParent) && (parent!=NULL) ){
			parent = parent->getParent();

			if ( NULL != parent ){
				lightWeightParent = parent->isLightWeight();
				if ( lightWeightParent ){
					bounds = parent->getBounds();

					offset.width_ += bounds.left_;
					offset.height_ += bounds.top_;
				}
				else {

					break;
				}
			}
		}

		if ( NULL != parent ) {
			Point tmpPt = *pt;
			
			parent->translateFromScreenCoords( &tmpPt );

			tmpPt.x_ -= offset.width_;
			tmpPt.y_ -= offset.height_;

			*pt = tmpPt;		

		}
	}
}

void LightweightComponent::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	graphicsContext->setClippingRect( childClipRect );
}

void LightweightComponent::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	graphicsContext->setClippingRect( oldClipRect );
}


/**
$Id$
*/
