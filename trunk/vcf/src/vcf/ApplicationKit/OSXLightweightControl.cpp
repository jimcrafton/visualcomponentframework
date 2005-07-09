//OSXLightweightControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/OSXLightweightControl.h"


using namespace VCF;

OSXLightweightControl::OSXLightweightControl( Control* component )
{
	component_ = component;
	enabled_ = true;
	focused_ = false;
}

OSXLightweightControl::~OSXLightweightControl()
{

}

void OSXLightweightControl::create( Control* owningControl )
{
	component_ = owningControl;
}

void OSXLightweightControl::destroyControl()
{

}

OSHandleID OSXLightweightControl::getHandleID()
{
	OSHandleID result = NULL;

	VCF::Control* parent = getHeavyWeightParent();
	if ( NULL != parent ) {
		result = parent->getPeer()->getHandleID();
	}
	return result;
}

VCF::String OSXLightweightControl::getText()
{
	VCF::String result = "";

	return result;
}

void OSXLightweightControl::setText( const VCF::String& text )
{

}

void OSXLightweightControl::setBounds( VCF::Rect* rect )
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

VCF::Rect OSXLightweightControl::getBounds()
{
	return bounds_;
}

void OSXLightweightControl::setVisible( const bool& visible )
{
	bool oldVisible = visible_;
	visible_ = visible;

	if ( visible_ != oldVisible ) {
		Control* parent = getHeavyWeightParent();
		if ( NULL != parent ) {
			Container* container = parent->getContainer();
			if ( NULL != container ) {
				container->resizeChildren(NULL);
			}
		}
	}
}

bool OSXLightweightControl::getVisible()
{
	return visible_;
}

VCF::Control* OSXLightweightControl::getControl()
{
	return component_;
}

void OSXLightweightControl::setControl( VCF::Control* component )
{
	component_ = component;
}

void OSXLightweightControl::setParent( VCF::Control* parent )
{

}

VCF::Control* OSXLightweightControl::getParent()
{
	return component_->getParent();
}

bool OSXLightweightControl::isFocused()
{
	return component_ == Control::getCurrentFocusedControl();
}

void OSXLightweightControl::setFocused()
{
	focused_ = true;
}

bool OSXLightweightControl::isEnabled()
{
	return enabled_;
}

void OSXLightweightControl::setEnabled( const bool& enabled )
{
	enabled_ = enabled;
}

void OSXLightweightControl::setFont( Font* font )
{

}

VCF::Control* OSXLightweightControl::getHeavyWeightParent()
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

void OSXLightweightControl::repaint( Rect* repaintRect )
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
		parent->repaint( repaintRect );
	}
}

void OSXLightweightControl::keepMouseEvents()
{
	Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		parent->keepMouseEvents();
		Control::setCapturedMouseControl( component_ );
	}
}

void OSXLightweightControl::releaseMouseEvents()
{
	Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		parent->releaseMouseEvents();
	}
}

void OSXLightweightControl::setCursor( Cursor* cursor )
{
	Control* parent = getHeavyWeightParent();
	if ( NULL != parent ){
		parent->getPeer()->setCursor( cursor );
	}
}

bool OSXLightweightControl::beginSetBounds( const ulong32& numberOfChildren )
{
	return true;
}


void OSXLightweightControl::endSetBounds()
{

}

void OSXLightweightControl::translateToScreenCoords( Point* pt )
{
	Size offset;
	VCF::Control* parent = getParent();
	if ( NULL != parent ){
		bool lightWeightParent = parent->isLightWeight();
		Rect bounds = bounds_;

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

void OSXLightweightControl::translateFromScreenCoords( Point* pt )
{
	Size offset;
	VCF::Control* parent = getParent();
	if ( NULL != parent ){
		bool lightWeightParent = parent->isLightWeight();
		Rect bounds = bounds_;

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


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3.2.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
*
*Revision 1.3  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/18 03:10:30  ddiego
*osx updates - add initial command button support, fixed rpoblem in mouse handling, and added dialog support.
*
*Revision 1.2  2004/08/07 17:15:07  ddiego
*added missing osx files and projects
*
*Revision 1.1.4.1  2004/08/07 16:32:50  ddiego
*added missing files
*
*Revision 1.1.2.1  2004/07/06 03:34:56  ddiego
*added new files for osx update, and added new
*project template files for creating VCF based projects with XCode.
*
*/


