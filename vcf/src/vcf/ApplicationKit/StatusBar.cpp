//StatusBar.cpp

/*
Copyright 2000-2004 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/StatusBar.h"
#include "vcf/ApplicationKit/EtchedBorder.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


void StatusBar::Container::resizeChildren( Control* control )
{
	if ( NULL == controlContainer_ ) {
		return;
	}
	
	Rect bounds = controlContainer_->getClientBounds();
	Rect rect ( bounds.left_ + leftBorderWidth_, 
		bounds.top_ + topBorderHeight_, 
		bounds.right_ - rightBorderWidth_, 
		bounds.bottom_ - bottomBorderHeight_ );

	double spacer = 2.0;

	double currentRight = bounds.right_ - spacer;
	

	std::vector< Control* >::reverse_iterator it = controls_.rbegin();
	int index = 0;
	double childWidth = 0;
	Rect childRect;
	while ( it != controls_.rend() ) {
		Control* child = *it;
		childRect = child->getBounds();

		childWidth = childRect.getWidth();

		childRect.top_ = bounds.top_;
		childRect.bottom_ = bounds.bottom_;

		if ( index == controls_.size()-1 ) {
			//we're at the first control - this is the primary pane
			childRect.left_ = bounds.left_;
			childRect.right_ = currentRight;
		}
		else {
			childRect.left_ = currentRight - childWidth;
			childRect.right_ = childRect.left_ + childWidth;
		}
		child->setBounds( &childRect );

		currentRight -= (childWidth + spacer);
		index ++;
		it ++;
	}
}






StatusBar::StatusBar():
	VCF::CustomControl(true)
{
	setContainer( new StatusBar::Container() );
	Label* primary = new Label();
	primary->setCaption( "" );

	getContainer()->add( primary );

	setAlignment( AlignBottom );

	setHeight( UIToolkit::getUIMetricValue(UIMetricsManager::mtInformationalControlHeight) );
}

void StatusBar::addStatusPane( const double& width , const VCF::String& text )
{
	insertStatusPaneWithWidth( getContainer()->getChildCount(), text, width );
}

void StatusBar::insertStatusPaneWithWidth( const uint32& index, const String& text, const double& width )
{
	Label* statusPane = new Label();
	if ( width == -1.0 ) {
		statusPane->setWidth( statusPane->getPreferredWidth() );
	}
	else {
		statusPane->setWidth( width );
	}
	getContainer()->insertAtIndex( statusPane, statusPane->getAlignment(), index );

	statusPane->setCaption( text );

	EtchedBorder* border = new EtchedBorder();
	border->setEdgeStyle( GraphicsContext::etRecessed );
	statusPane->setBorder( border );
	statusPane->setVerticalAlignment( tvaTextCenter );
}

void StatusBar::insertStatusPane( const uint32& index, const String& text )
{
	insertStatusPaneWithWidth( index, text, -1 );
}

void StatusBar::removeStatusPane( const uint32& index )
{
	Control* child = getContainer()->getControlAtIndex(index+1);
	getContainer()->remove( child );
	removeComponent( child );
}

uint32 StatusBar::getStatusPaneCount()
{
	return getContainer()->getChildCount()-1;
}

String StatusBar::getStatusText()
{
	Label* label = (Label*)getContainer()->getControlAtIndex(0);
	return label->getCaption();
}
	
void StatusBar::setStatusText( const String& val )
{
	Label* label = (Label*)getContainer()->getControlAtIndex(0);
	label->setCaption( val );
}

String StatusBar::getStatusPaneText( const uint32& index )
{
	String result;

	if ( PrimaryPane == index ) {
		Label* label = (Label*)getContainer()->getControlAtIndex(0);
		result = label->getCaption();
	}
	else {
		Label* label = (Label*)getContainer()->getControlAtIndex(index+1);
		result = label->getCaption();
	}

	return result;
}

void StatusBar::setStatusPaneText( const uint32& index, const String& val, bool addMissingValues )
{
	size_t missing = (index+1) - getContainer()->getChildCount();

	if ( addMissingValues ) {
		if ( missing > 0 ) {
			for (int i=0;i<missing;i++ ) {
				addStatusPane();
			}			
		}
	}

	Label* label = (Label*)getContainer()->getControlAtIndex(index);
	label->setCaption( val );
}
/*
void StatusBar::setStatusText( const uint32& index, const VCF::String& text )
{
	if ( PrimaryPane == index ) {
		Label* label = (Label*)getContainer()->getControlAtIndex(0);
		label->setCaption( text );
	}
	else {
		Label* label = (Label*)getContainer()->getControlAtIndex(index+1);
		label->setCaption( text );
	}
}
*/

Control* StatusBar::getStatusPaneControl( const uint32& index )
{
	return getContainer()->getControlAtIndex(index+1);
}

void StatusBar::paint( GraphicsContext* ctx )
{
	//CustomControl::paint( ctx );

	Rect innerBounds = getClientBounds( true );

	BackgroundState bkg;
	bkg.setEnabled( isEnabled() );
	bkg.setActive( isActive() );
	bkg.colorType_ = SYSCOLOR_FACE;	
			
	ctx->drawThemeBackground( &innerBounds, bkg );

	getContainer()->paintChildren( ctx );
}


/**
$Id$
*/



