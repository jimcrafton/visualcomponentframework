//Containers.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractContainer.h"
#include "vcf/ApplicationKit/Containers.h"

using namespace VCF;


StandardContainer::StandardContainer():
	bottomBorderHeight_(0.0),
	topBorderHeight_(0.0),
	rightBorderWidth_(0.0),
	leftBorderWidth_(0.0)
{

}

StandardContainer::StandardContainer( Component* owner ):
	AbstractContainer(owner),
	bottomBorderHeight_(0.0),
	topBorderHeight_(0.0),
	rightBorderWidth_(0.0),
	leftBorderWidth_(0.0)
{

}

void StandardContainer::resizeChildren( Control* control )
{
	Rect bounds = controlContainer_->getClientBounds();
	if ( bounds.isEmpty() ) {
		//return;
	}

	bounds.left_ += leftBorderWidth_;
	bounds.top_ += topBorderHeight_;
	bounds.right_ -= rightBorderWidth_;
	bounds.bottom_ -= bottomBorderHeight_;

	bool controlJustAdded = false;
	if ( NULL != control ) {
		std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );

		controlJustAdded = ( found == controls_.end() );
	}

	bool needAnchorWork = anchorWork() ||
		(controlJustAdded && (control->getAlignment() == AlignNone) && (control->getAnchor() != 0));

	bool needAlignWork = alignWork()||
		(controlJustAdded && (control->getAlignment() != AlignNone));


	if ( (true == needAnchorWork) || (true == needAlignWork) ) {
		controlContainer_->getPeer()->beginSetBounds( controls_.size() );
	}

	if ( true == needAlignWork ){

		alignFixed( control, controlJustAdded, AlignTop, &bounds );
		alignFixed( control, controlJustAdded, AlignBottom, &bounds );
		alignFixed( control, controlJustAdded, AlignLeft, &bounds );
		alignFixed( control, controlJustAdded, AlignRight, &bounds );
		alignFixed( control, controlJustAdded, AlignClient, &bounds );
	}

	if ( true == needAnchorWork ) {
		doAnchors( control, controlJustAdded, &bounds );
	}

	if ( (true == needAnchorWork) || (true == needAlignWork) ) {
		controlContainer_->getPeer()->endSetBounds();
	}

}

void StandardContainer::alignFixed( Control* initialControl, const bool& controlJustAdded, const AlignmentType& alignment, Rect* rect )
{
	std::vector< Control* > alignmentList;

	std::vector< Control* >::iterator it = controls_.begin();
	ulong32 index=0;
	while ( it != controls_.end() ){
		Control* child = *it;

		if ( (child->getAlignment() == alignment) && (child->getVisible()) && !child->isIgnoredForLayout() ){
			alignmentList.push_back( child );
		}

		it ++;
	}

	if ( NULL != initialControl ) {
		if ( (initialControl->getVisible()) && (initialControl->getAlignment() == alignment) && !initialControl->isIgnoredForLayout() ) {
			alignmentList.push_back( initialControl );
		}
	}

	if ( (alignment == AlignBottom) || (alignment == AlignRight) ) {
		std::reverse( alignmentList.begin(), alignmentList.end() );
	}

	it = alignmentList.begin();
	while ( it != alignmentList.end() ) {
		doPosition( *it, alignment, rect );
		it ++;
	}
}






bool StandardContainer::insertBefore( Control* initialControl, const bool& controlJustAdded,
									 Control* c1, Control* c2, const AlignmentType& alignment, Rect* bounds )
{
	bool result = false;
	Rect bounds1;
	Rect bounds2;
	if ( (NULL != c1) && (NULL != c2) ){
		bounds1 = c1->getBounds();
		bounds2 = c2->getBounds();

		if ( controlJustAdded ) {
			//first time through
			//adjust the bounds if neccessary by the difference from 0 to bounds->topleft
			if ( initialControl == c1 ) {
				bounds1.offset( bounds->left_, bounds->top_ );
			}
			else if ( initialControl == c2 ) {
				bounds2.offset( bounds->left_, bounds->top_ );
			}
		}
		switch ( alignment ){
			case AlignTop:{
				result = bounds1.top_ < bounds2.top_;
			}
			break;

			case AlignBottom:{
				//this ->> (bounds1.top_ /*+ bounds1.getHeight()*/)
				//is wrong - commented out to fix [ 532623 ] alignment problem & [ 525214 ] alignment loss after resize JEC 20-03-2002

				result = (bounds1.top_ + bounds1.getHeight()) > (bounds2.top_ + bounds2.getHeight());
			}
			break;

			case AlignLeft:{
				result = bounds1.left_ < bounds2.left_;
			}
			break;

			case AlignRight:{
				//this ->> (bounds1.top_ /*+ bounds1.getHeight()*/)
				//is wrong - commented out to fix [ 532623 ] alignment problem & [ 525214 ] alignment loss after resize JEC 20-03-2002

				result = (bounds1.left_ + bounds1.getWidth()) > (bounds2.left_ + bounds2.getWidth());
			}
			break;
		}
	}
	return result;
}

/**
*the rect parameter is the available bounds for the parent control that is being adjusted
*as each of the child controls repositions itself
*/
void StandardContainer::doPosition( Control* component, const AlignmentType& alignment, Rect* rect )
{
	Rect componentBounds = component->getBounds();
	double w = componentBounds.getWidth();
	double h = componentBounds.getHeight();

	switch ( alignment ){
		case AlignLeft:{
			rect->left_ = rect->left_ + w;//minVal<>( rect->left_ + w,  rect->right_ );
		}
		break;

		case AlignTop:{
			rect->top_ = rect->top_ + h;//minVal<>( rect->bottom_, rect->top_ + h );
		}
		break;

		case AlignRight:{
			rect->right_ = rect->right_ - w;//maxVal<>(rect->left_, rect->right_ - w);//VCF::maxVal<double>( rect->right_ - w, rect->left_ );
		}
		break;

		case AlignBottom:{

			rect->bottom_ = rect->bottom_- h;//maxVal<>( rect->bottom_- h, rect->top_);//VCF::maxVal<double>( rect->bottom_ - h, rect->top_ );
		}
		break;
	}

	switch ( alignment ){
		case AlignLeft:{
			componentBounds.left_ = rect->left_ - w;//VCF::maxVal<double>( 0.0, rect->left_ - w );
			componentBounds.top_ = rect->top_;
			componentBounds.right_ = componentBounds.left_ + w;
			componentBounds.bottom_ = componentBounds.top_;
			if ( (rect->bottom_ - rect->top_) >= 0 ) {
				componentBounds.bottom_ += rect->bottom_ - rect->top_;
			}
			else {
				componentBounds.bottom_ += h;
			}

			component->setBounds( &componentBounds );
		}
		break;

		case AlignTop:{
			componentBounds.left_ = rect->left_;
			componentBounds.top_ = rect->top_ - h;//VCF::maxVal<double>( 0.0, rect->top_ - h );
			componentBounds.right_ = componentBounds.left_;
			if ( (rect->right_ - rect->left_) >= 0 ) {
				componentBounds.right_ += (rect->right_ - rect->left_);
			}
			else {
				componentBounds.right_ += w;
			}

			componentBounds.bottom_ = componentBounds.top_ + h;

			component->setBounds( &componentBounds );
		}
		break;

		case AlignRight:{
			componentBounds.left_ = rect->right_;
			componentBounds.top_ = rect->top_;
			componentBounds.right_ = rect->right_ + w;
			componentBounds.bottom_ = componentBounds.top_;

			componentBounds.bottom_ = componentBounds.top_;
			if ( (rect->bottom_ - rect->top_) >= 0 ) {
				componentBounds.bottom_ += rect->bottom_ - rect->top_;
			}
			else {
				componentBounds.bottom_ += h;
			}

			component->setBounds( &componentBounds );
		}
		break;

		case AlignBottom:{
			componentBounds.left_ = rect->left_;
			componentBounds.top_ = rect->bottom_;
			componentBounds.right_ = componentBounds.left_;
			if ( (rect->right_ - rect->left_) >= 0 ) {
				componentBounds.right_ += (rect->right_ - rect->left_);
			}
			else {
				componentBounds.right_ += w;
			}

			componentBounds.bottom_ = componentBounds.top_ + h;

			component->setBounds( &componentBounds );
		}
		break;

		case AlignClient:{
			Rect clientBounds;
			clientBounds.setRect( maxVal<>(0.0,rect->left_),maxVal<>(0.0,rect->top_),
									maxVal<>(0.0,rect->right_),maxVal<>(0.0,rect->bottom_) );

			component->setBounds( &clientBounds );

		}
		break;
	}
}

void StandardContainer::doAlign( Control* initialControl, const bool& controlJustAdded,
									const AlignmentType& alignment, Rect* rect )
{
	std::vector< Control* > alignmentList;

	if ( NULL != initialControl ) {
		if ( (initialControl->getVisible()) && (initialControl->getAlignment() == alignment) && !initialControl->isIgnoredForLayout() ) {
			alignmentList.push_back( initialControl );
		}
	}

	std::vector< Control* >::iterator it = controls_.begin();
	ulong32 index=0;
	while ( it != controls_.end() ){
		Control* child = *it;

		if ( (child->getAlignment() == alignment) && (child->getVisible()) && !child->isIgnoredForLayout() ){
			ulong32 insertIndex = 0;
			if ( NULL != initialControl && initialControl == child ) {
				it ++;
				index ++;
				continue;
			}
			while ( (insertIndex < alignmentList.size()) &&
					!insertBefore( initialControl, controlJustAdded, child,
									alignmentList[insertIndex], alignment, rect ) ){


				insertIndex++;

			}

			alignmentList.insert( alignmentList.begin() + insertIndex, child );
		}

		it ++;
		index ++;
	}


	it = alignmentList.begin();
	while ( it != alignmentList.end() ) {
		doPosition( *it, alignment, rect );
		it ++;
	}
}

bool StandardContainer::alignWork()
{
	bool result = false;

	std::vector<Control*>::iterator it = controls_.begin();

	while ( it != controls_.end() ) {
		if ( (*it)->getAlignment() != AlignNone && !(*it)->isIgnoredForLayout() ){
			result = true;
			break;
		}
		it ++;
	}
	return result;
}

bool StandardContainer::anchorWork()
{
	bool result = false;

	std::vector<Control*>::iterator it = controls_.begin();
	while ( it != controls_.end() ) {
		if ( AnchorNone != (*it)->getAnchor() && !(*it)->isIgnoredForLayout() ) {
			result = true;
			break;
		}
		it ++;
	}

	return result;
}

void StandardContainer::doAnchors( Control* initialControl, const bool& controlJustAdded, Rect* bounds )
{
	Rect tmpBounds = controlContainer_->getClientBounds();

	std::vector<Control*>::iterator it = controls_.begin();
	while ( it != controls_.end() ) {
		Control* child = *it;

		if ( child->isIgnoredForLayout() ) {
			it ++;
			continue;
		}

		if ( AnchorNone != child->getAnchor() ) {
			long anchorType = child->getAnchor();

			Rect anchorBounds = child->getBounds();
			double h = anchorBounds.getHeight();
			double w = anchorBounds.getWidth();

			float* anchorDeltas = child->getAnchorDeltas();

			if ( (anchorType & AnchorRight) != 0 ) {
				if ( anchorBounds.left_ < tmpBounds.right_ ) {
					anchorBounds.right_ = tmpBounds.getWidth() - anchorDeltas[Control::ANCHOR_DRIGHT];
				}
				else {
					anchorBounds.right_ = tmpBounds.getWidth() - anchorDeltas[Control::ANCHOR_DRIGHT];
				}

				anchorBounds.left_ = anchorBounds.right_ - w;
			}

			if ( (anchorType & AnchorLeft) != 0 ) {
				anchorBounds.left_ = anchorDeltas[Control::ANCHOR_DLEFT];
			}

			if ( (anchorType & AnchorBottom) != 0 ) {
				if ( anchorBounds.top_ < tmpBounds.bottom_ ) {
					anchorBounds.bottom_ = tmpBounds.getHeight() - anchorDeltas[Control::ANCHOR_DBOTTOM];
				}
				else {
					anchorBounds.bottom_ = tmpBounds.getHeight() - anchorDeltas[Control::ANCHOR_DBOTTOM];
				}

				anchorBounds.top_ = anchorBounds.bottom_ - h;
			}

			if ( (anchorType & AnchorTop) != 0 ) {
				anchorBounds.top_ = anchorDeltas[Control::ANCHOR_DTOP];
			}

			child->setBounds( &anchorBounds, false );
		}
		it ++;
	}
}

void StandardContainer::calcAlignmentList( const AlignmentType& alignment, std::vector< Control* >& alignmentList )
{
	//std::vector< Control* > alignmentList;
	Control* initialControl = NULL;
	const bool controlJustAdded = false;
	Rect* rect = NULL;

	alignmentList.clear();

	if ( NULL != initialControl ) {
		if ( (initialControl->getVisible()) && (initialControl->getAlignment() == alignment) && !initialControl->isIgnoredForLayout() ) {
			alignmentList.push_back( initialControl );
		}
	}

	std::vector< Control* >::iterator it = controls_.begin();
	ulong32 index=0;
	while ( it != controls_.end() ){
		Control* child = *it;

		if ( (child->getAlignment() == alignment) && (child->getVisible()) && !child->isIgnoredForLayout() ){
			ulong32 insertIndex = 0;
			if ( NULL != initialControl && initialControl == child ) {
				it ++;
				index ++;
				continue;
			}
			while ( (insertIndex < alignmentList.size()) &&
					!insertBefore( initialControl, controlJustAdded, child,
									alignmentList[insertIndex], alignment, rect ) ){


				insertIndex++;

			}

			alignmentList.insert( alignmentList.begin() + insertIndex, child );
		}

		it ++;
		index ++;
	}
}

Control* StandardContainer::getControlWithAlignment( const AlignmentType& alignment, const bool& first/*=true*/ )
{
	Control* control = NULL;

	std::vector<Control*>::iterator it = controls_.begin();

	while ( it != controls_.end() ) {
		if ( (*it)->getAlignment() == alignment ){
			control = (*it);
			if ( first ) {
				break;
			}
		}
		it ++;
	}

	return control;
}

Control* StandardContainer::getControlInAlignmentList( const AlignmentType& alignment, const bool& first/*=true*/ )
{
	Control* control = NULL;
	control = getControlWithAlignment( AlignClient, first );
	if ( NULL == control ) {
		std::vector< Control* > alignmentList;
		calcAlignmentList( alignment, alignmentList );
		if ( 0 != alignmentList.size() ) {
			if ( first ) {
				control = alignmentList[0];
			}
			else {
				control = alignmentList[alignmentList.size()-1];
			}
		}
	}

	return control;

}

void StandardContainer::setBottomBorderHeight( const double& bottomBorderHeight )
{
	bottomBorderHeight_ = bottomBorderHeight;
	if ( NULL != controlContainer_ ) {
		resizeChildren(NULL);
	}
}

void StandardContainer::setTopBorderHeight( const double& topBorderHeight )
{
	topBorderHeight_ = topBorderHeight;
	if ( NULL != controlContainer_ ) {
		resizeChildren(NULL);
	}
}

void StandardContainer::setRightBorderWidth( const double& rightBorderWidth )
{
	rightBorderWidth_ = rightBorderWidth;
	if ( NULL != controlContainer_ ) {
		resizeChildren(NULL);
	}
}

void StandardContainer::setLeftBorderWidth( const double& leftBorderWidth )
{
	leftBorderWidth_ = leftBorderWidth;
	if ( NULL != controlContainer_ ) {
		resizeChildren(NULL);
	}
}

void StandardContainer::setBorderWidth ( const double& borderWidth )
{
	leftBorderWidth_ = borderWidth;
	topBorderHeight_ = borderWidth;
	rightBorderWidth_ = borderWidth;
	bottomBorderHeight_ = borderWidth;
	if ( NULL != controlContainer_ ) {
		resizeChildren(NULL);
	}
}











/**
DesignTimeContainer class impl
*/
void DesignTimeContainer::resizeChildren( Control* control )
{
	//if ( controlContainer_->getVisible() ) {
		Rect bounds = controlContainer_->getClientBounds();
		if ( bounds.isEmpty() ) {
			//return;
		}

		Rect rect ( bounds.left_ + leftBorderWidth_,
						bounds.top_ + topBorderHeight_,
						bounds.right_ - rightBorderWidth_,
						bounds.bottom_ - bottomBorderHeight_ );



		resizeChildrenUsingBounds( control, &rect );
	//}
}

void DesignTimeContainer::resizeChildrenUsingBounds( Control* control, Rect* bounds )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG_2(INVALID_POINTER_ERROR));
	};

	bool controlJustAdded = false;

	if ( NULL != control ) {
		std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );

		controlJustAdded = ( found == controls_.end() );
	}

	bool needAnchorWork = anchorWork() ||
		(controlJustAdded && (control->getAlignment() == AlignNone) && (control->getAnchor() != 0));

	bool needAlignWork = alignWork()||
		(controlJustAdded && (control->getAlignment() != AlignNone));


	if ( (true == needAnchorWork) || (true == needAlignWork) ) {
		controlContainer_->getPeer()->beginSetBounds( controls_.size() );
	}

	if ( true == needAlignWork ){

		doAlign( control, controlJustAdded, AlignTop, bounds );
		doAlign( control, controlJustAdded, AlignBottom, bounds );
		doAlign( control, controlJustAdded, AlignLeft, bounds );
		doAlign( control, controlJustAdded, AlignRight, bounds );
		doAlign( control, controlJustAdded, AlignClient, bounds );
	}

	if ( true == needAnchorWork ) {
		doAnchors( control, controlJustAdded, bounds );
	}

	if ( (true == needAnchorWork) || (true == needAlignWork) ) {
		controlContainer_->getPeer()->endSetBounds();
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.3  2006/03/16 05:51:53  ddiego
*fixed glitch in achor sizing code, per fraggles req.
*
*Revision 1.3.2.2  2005/08/15 03:10:51  ddiego
*minor updates to vff in out streaming.
*
*Revision 1.3.2.1  2005/07/29 03:04:25  ddiego
*rolled back a few conatainer changes.
*
*Revision 1.3  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/06/25 22:47:20  marcelloptr
*[bugfix 1227549] HorizontalLayoutContainer set the heights in the wrong rows.
*AbstractContainer::add() needs to resizeChildren *after* the child control has been added.
*
*Revision 1.2.4.2  2005/03/20 04:29:21  ddiego
*added ability to set image lists for list box control.
*
*Revision 1.2.4.1  2005/03/06 22:50:58  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/08 15:08:05  ddiego
*made the change to the StandardContainer name - the
*old StandardContainer is now called DesignTimeContainer and
*the old FixedStandardContainer is now renamed to StandardContainer.
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/24 02:14:06  ddiego
*fixed incorrect calculation of anchor bounds in certain cases
*
*Revision 1.2  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.10  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.1.2.9  2003/12/01 21:58:25  marcelloptr
*minor fixes
*
*Revision 1.1.2.8  2003/10/15 04:01:29  ddiego
*added some more support for persisting the dependency info
*
*Revision 1.1.2.7  2003/10/14 04:31:07  ddiego
*some more adjustments to hack on getting the alignments to wrok better
*
*Revision 1.1.2.6  2003/10/13 21:27:57  ddiego
*fiddles with the containers a bit - didn't fix anything :(
*
*Revision 1.1.2.5  2003/10/12 19:38:35  ddiego
*added a fix in the combbox control due to changes in the container
*layout
*fixed a glitch in the StandardContainer::resizeChildrenUsingBounds
*method os that it correctly checks the passed in control for alignment
*or anchor  changes if neccessary
*
*Revision 1.1.2.4  2003/10/12 06:34:13  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.1.2.3  2003/08/20 19:05:20  ddiego
*some minor changes to container logic
*
*Revision 1.1.2.2  2003/08/19 04:43:40  ddiego
*further code to support lightweight container implementation. Not quite
*finished
*
*Revision 1.1.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*/


