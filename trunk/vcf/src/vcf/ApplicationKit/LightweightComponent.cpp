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

long LightweightComponent::getHandleID()
{
	long result = -1;
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

void LightweightComponent::repaint( Rect* repaintRect )
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

bool LightweightComponent::beginSetBounds( const ulong32& numberOfChildren )
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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.17  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.2.4  2003/10/12 06:34:29  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.16.2.3  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.16.2.2  2003/08/19 04:43:56  ddiego
*further code to support lightweight container implementation. Not quite
*finished
*
*Revision 1.16.2.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.16  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.15.2.1  2003/05/27 04:45:33  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.15  2003/05/17 20:37:33  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.2  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.14.2.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:48  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.14.1  2003/01/08 00:19:51  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.13  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/04/27 15:52:24  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.12.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.12  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.11  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


