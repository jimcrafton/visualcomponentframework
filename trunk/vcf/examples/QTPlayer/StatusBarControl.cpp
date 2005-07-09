//StatusBarControl.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "StatusBarControl.h"
#include "vcf/ApplicationKit/EtchedBorder.h"

using namespace VCF;



void StatusBarControl::Container::resizeChildren( Control* control )
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
			//we;re at the first control - this is the primary pane
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






StatusBarControl::StatusBarControl():
	VCF::CustomControl(true)
{
	setContainer( new StatusBarControl::Container() );
	Label* primary = new Label();
	primary->setCaption( "" );

	getContainer()->add( primary );
}

void StatusBarControl::addStatusPane( const double& width , const VCF::String& text )
{
	Label* statusPane = new Label();
	if ( width == -1.0 ) {
		statusPane->setWidth( statusPane->getPreferredWidth() );
	}
	else {
		statusPane->setWidth( width );
	}
	getContainer()->add( statusPane );

	statusPane->setCaption( text );

	EtchedBorder* border = new EtchedBorder();
	border->setEdgeStyle( GraphicsContext::etRecessed );
	statusPane->setBorder( border );
	statusPane->setVerticalAlignment( tvaTextCenter );
}

void StatusBarControl::removeStatusPane( VCF::ulong32 index )
{
	Control* child = getContainer()->getControlAtIndex(index+1);
	getContainer()->remove( child );
	removeComponent( child );
}

void StatusBarControl::setStatusText( int index, const VCF::String& text )
{
	if ( -1 == index ) {
		Label* label = (Label*)getContainer()->getControlAtIndex(0);
		label->setCaption( text );
	}
	else {
		Label* label = (Label*)getContainer()->getControlAtIndex(index+1);
		label->setCaption( text );
	}
}

Control* StatusBarControl::getStatusPaneControl( VCF::ulong32 index )
{
	return getContainer()->getControlAtIndex(index+1);
}

void StatusBarControl::paint( GraphicsContext* ctx )
{
	CustomControl::paint( ctx );

	getContainer()->paintChildren( ctx );
}



