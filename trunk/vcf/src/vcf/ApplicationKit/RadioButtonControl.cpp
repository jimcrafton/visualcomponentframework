//RadioButtonControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/RadioButtonControl.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


RadioButtonControl::RadioButtonControl()
{
	setVisible( true );

	useFixedRadioButtonSize_ = true;

	groupID_ = 0;

	fixedRadioButtonHeight_ = UIToolkit::getUIMetricSize( UIMetricsManager::mtRadioBoxBtnSize ).height_;
}

RadioButtonControl::~RadioButtonControl()
{

}

double RadioButtonControl::getPreferredHeight()
{
	return UIToolkit::getUIMetricValue( UIMetricsManager::mtRadioBoxHeight );
}

double RadioButtonControl::getPreferredWidth()
{
	return 100;
}

void RadioButtonControl::paint( GraphicsContext* context )
{
	ToggledButton::paint( context );

	Rect r( 0.0, 0.0, getWidth(), getHeight() );

	Rect radioBtnRect = r;

	if ( true == useFixedRadioButtonSize_ ) {

		radioBtnRect.top_ = maxVal<double>( 0.0, r.top_ + (r.getHeight() / 2.0 - fixedRadioButtonHeight_/2.0));

		radioBtnRect.bottom_ = minVal<double>( r.bottom_, radioBtnRect.top_ + fixedRadioButtonHeight_ );
	}
	else {
		radioBtnRect.inflate( -3.0, -3.0 );
	}

	//radioBtnRect.left_ += 3.0;

	//radioBtnRect.right_ = radioBtnRect.left_ + radioBtnRect.getHeight();

	//r.left_ = radioBtnRect.right_;

	ButtonState state;
	state.setActive( isActive() );
	state.setEnabled( isEnabled() );
	state.setToggled( checked_ );
	state.setFocused( isFocused() );
	state.buttonCaption_ = caption_;
	if ( getUseLocaleStrings() ) {
		state.buttonCaption_ = System::getCurrentThreadLocale()->translate( caption_ );
	}

	context->drawThemeRadioButtonRect( &radioBtnRect, state );
}


void RadioButtonControl::setFixedRadioButtonHeight( const double& fixedRadioButtonHeight )
{
	fixedRadioButtonHeight_ = minVal<>( fixedRadioButtonHeight, getHeight() );
	repaint();
}

void RadioButtonControl::setUseFixedRadioButtonSize( const bool& fixedRadioButtonSize )
{
	useFixedRadioButtonSize_ = fixedRadioButtonSize;
	repaint();
}

void RadioButtonControl::setGroupID( const int32& groupID )
{
	groupID_ = groupID;
}

void RadioButtonControl::setChecked( const bool& checked )
{
	Control* parent = getParent();
	if ( NULL != parent ) {
		Container* container = parent->getContainer();
		if ( NULL != container ) {
			Enumerator<Control*>* children = container->getChildren();

			while ( (children->hasMoreElements()) ) {
				Control* child = children->nextElement();
				RadioButtonControl* radioControl = dynamic_cast<RadioButtonControl*>( child );
				if ( NULL != radioControl ) {
					if ( (radioControl != this) && (radioControl->getGroupID() == groupID_) ) {
						radioControl->internal_setChecked( false );
					}
				}
			}

			if ( checked ) {
				ToggledButton::setChecked( checked  );
			}
		}
		else {
			//Ooh this is very bad !!
			throw BadComponentStateException();
		}
	}
	else {
		ToggledButton::setChecked( checked  );
	}
}

RadioButtonControl* RadioButtonControl::getSelectedRadioButtonFromGroup()
{
	RadioButtonControl* result = NULL;
	Container* parent = getParent()->getContainer();
	if ( NULL != parent ) {
		Enumerator<Control*>* children = parent->getChildren();
		while ( true == children->hasMoreElements() ) {
			Control* child = children->nextElement();
			RadioButtonControl* radioControl = dynamic_cast<RadioButtonControl*>( child );
			if ( NULL != radioControl ) {
				if ( (radioControl->getGroupID() == groupID_) && (true == radioControl->isChecked()) ) {
					result = radioControl;
					break;
				}
			}
		}
	}
	else {
		//Ooh this is very bad !!
		throw BadComponentStateException();
	}

	return result;
}

bool RadioButtonControl::generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )
{
	String lcPropName = StringUtils::lowerCase(fullPropertyName);
	if ( lcPropName == CONTROL_HEIGHT ) {
		if ( getHeight() == UIToolkit::getUIMetricValue( UIMetricsManager::mtRadioBoxHeight ) ) {
			strValue = CC_RADIOBOXHEIGHT;
			return true;
		}
	}

	return Control::generatePropertyValue( fullPropertyName, property, value, strValue );
}

/**
$Id$
*/
