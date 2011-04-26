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
	uint32 index=0;
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
	uint32 index=0;
	while ( it != controls_.end() ){
		Control* child = *it;

		if ( (child->getAlignment() == alignment) && (child->getVisible()) && !child->isIgnoredForLayout() ){
			uint32 insertIndex = 0;
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
			int32 anchorType = child->getAnchor();

			Rect anchorBounds = child->getBounds();
			double h = anchorBounds.getHeight();
			double w = anchorBounds.getWidth();

			float* anchorDeltas = child->getAnchorDeltas();

			if ( (anchorType & AnchorRight) != 0 ) {

				//the right can't go negative here anymore
				//which prevents us from seeing a weird "mirror"
				//effect when resizing the parent 

				anchorBounds.right_ = maxVal<>(0.0,tmpBounds.getWidth() - anchorDeltas[Control::ANCHOR_DRIGHT]);

				anchorBounds.left_ = anchorBounds.right_ - w;
			}

			if ( (anchorType & AnchorLeft) != 0 ) {
				anchorBounds.left_ = anchorDeltas[Control::ANCHOR_DLEFT];
			}

			if ( (anchorType & AnchorBottom) != 0 ) {
				//the bottom can't go negative here anymore
				//which prevents us from seeing a weird "mirror"
				//effect when resizing the parent 
				anchorBounds.bottom_ = maxVal<>( 0.0, tmpBounds.getHeight() - anchorDeltas[Control::ANCHOR_DBOTTOM] );

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
	uint32 index=0;
	while ( it != controls_.end() ){
		Control* child = *it;

		if ( (child->getAlignment() == alignment) && (child->getVisible()) && !child->isIgnoredForLayout() ){
			uint32 insertIndex = 0;
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

double StandardContainer::getBorderWidth()
{
	double result = -1;

	result = (bottomBorderHeight_ +
						rightBorderWidth_ +
						topBorderHeight_ +
						leftBorderWidth_ ) / 4.0;

	if ( (result != bottomBorderHeight_) ||
			(result != rightBorderWidth_) ||
			(result != topBorderHeight_) || (result != leftBorderWidth_) ) {
		result = -1;
	}

	return result;
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

bool StandardContainer::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTAINER_BOTTOMHEIGHT ) {
		if ( bottomBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) ) {
			strValue = CC_WINDOW_BORDER;
			return true;
		}
		else if ( bottomBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) ) {
			strValue = CC_CONTAINER_BORDER;
			return true;
		}
		else if ( bottomBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing ) ) {
			strValue = CC_CONTROL_VSPACE;
			return true;
		}
		else if ( bottomBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlTopSpacer ) ) {
			strValue = CC_INFO_TOPSPACE;
			return true;
		}
		else if ( bottomBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlBottomSpacer ) ) {
			strValue = CC_INFO_BOTTOMSPACE;
			return true;
		}		
	}
	else if ( lcPropName == CONTAINER_TOPHEIGHT ) {
		if ( topBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) ) {
			strValue = CC_WINDOW_BORDER;
			return true;
		}
		else if ( topBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) ) {
			strValue = CC_CONTAINER_BORDER;
			return true;
		}
		else if ( topBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing ) ) {
			strValue = CC_CONTROL_VSPACE;
			return true;
		}
		else if ( topBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlTopSpacer ) ) {
			strValue = CC_INFO_TOPSPACE;
			return true;
		}
		else if ( topBorderHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlBottomSpacer ) ) {
			strValue = CC_INFO_BOTTOMSPACE;
			return true;
		}		
	}
	else if ( lcPropName == CONTAINER_LEFTWIDTH ) {
		if ( leftBorderWidth_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) ) {
			strValue = CC_WINDOW_BORDER;
			return true;
		}
		else if ( leftBorderWidth_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) ) {
			strValue = CC_CONTAINER_BORDER;
			return true;
		}
		else if ( leftBorderWidth_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) ) {
			strValue = CC_CONTROL_HSPACE;
			return true;
		}		
	}
	else if ( lcPropName == CONTAINER_RIGHTWIDTH ) {
		if ( rightBorderWidth_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) ) {
			strValue = CC_WINDOW_BORDER;
			return true;
		}
		else if ( rightBorderWidth_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) ) {
			strValue = CC_CONTAINER_BORDER;
			return true;
		}
		else if ( rightBorderWidth_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) ) {
			strValue = CC_CONTROL_HSPACE;
			return true;
		}		
	}

	return Component::generatePropertyValue( fullPropertyName, property, value, strValue );
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
$Id$
*/
