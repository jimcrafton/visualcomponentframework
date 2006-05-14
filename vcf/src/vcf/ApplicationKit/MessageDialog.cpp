//MessageDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/MessageDialog.h"
#include "vcf/ApplicationKit/CommandButton.h"
#include "vcf/ApplicationKit/PushButton.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/ImageControl.h"

using namespace VCF;


MessageDialog::MessageDialog():
	showTitle_(false),
	style_(Dialog::msDefault),
	applicationIcon_(NULL)
{
	UIMetricsManager* metricMgr = UIToolkit::getUIMetricsManager();

	setWidth( 415 );

	imagePane_ = new Panel();
	imagePane_->setBorder( NULL );

	labelsPane_ = new Panel();
	labelsPane_->setBorder( NULL );

	commandPane_ = new Panel();
	commandPane_->setBorder( NULL );

	commandPane_->setHeight( UIToolkit::getUIMetricValue( UIMetricsManager::mtButtonHeight ) +
								(UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) * 2.0 ) );

	commandPane_->setBorderSize( UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) );

	add( commandPane_, AlignBottom );

	const Image* img = UIToolkit::getStandardInformationImage();

	imagePane_->setWidth( 64 );
	add( imagePane_, AlignLeft );

	add( labelsPane_, AlignClient );



	messageLabel_ = new Label();
	messageLabel_->setWordWrap( true );

	double messageHeight = 0.0;
	Font font = metricMgr->getDefaultFontFor( UIMetricsManager::ftMessageFont );

	messageLabel_->setFont( &font );

	double x = UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing );
	double y = UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing );

	messageHeight = messageLabel_->getPreferredHeight() * 2.0 +
					UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing ) +
					UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlTopSpacer ) +
					UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlBottomSpacer );

	font = metricMgr->getDefaultFontFor( UIMetricsManager::ftToolTipFont );

	double w = labelsPane_->getWidth() - (UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) *2) ;

	messageLabel_->setBounds(x, y, w, messageLabel_->getPreferredHeight()*2.0 );

	labelsPane_->add( messageLabel_ );

	y =  messageLabel_->getBottom() +
				UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlTopSpacer );

	infoLabel_ = new Label();

	infoLabel_->setFont( &font );

	infoLabel_->setBounds( x, y, w, infoLabel_->getPreferredHeight() * 2.0 );

	infoLabel_->setVerticalAlignment( tvaTextCenter );
	infoLabel_->setWordWrap( true );

	labelsPane_->add( infoLabel_ );


	Rect clientR = getClientBounds();

	setHeight( 25 + (commandPane_->getHeight() + infoLabel_->getBottom()) );


	Image* image = const_cast<Image*>( UIToolkit::getStandardInformationImage() );

	applicationIcon_ = GraphicsToolkit::createImage( image->getWidth(), image->getHeight() );



	ColorPixels pix(applicationIcon_);	
	SysPixelType* bits = pix;

	memcpy( applicationIcon_->getData(), image->getData(), 
			image->getHeight() * image->getWidth() * image->getType() );

	applicationIcon_->setTransparencyColor( &Color(0.0,1.0,0.0) );
	applicationIcon_->setIsTransparent( true );

	ImageControl* ic = new ImageControl();

	x = imagePane_->getWidth() / 2.0 - applicationIcon_->getWidth() / 2.0;
	y = imagePane_->getHeight() / 2.0 - applicationIcon_->getHeight() / 2.0;


	ic->setBounds( x, y, applicationIcon_->getWidth(), applicationIcon_->getHeight() );

	imagePane_->add( ic, AlignClient );
	ic->setImage( applicationIcon_ );
	ic->setTransparent( true );
}

MessageDialog::~MessageDialog()
{

}

UIToolkit::ModalReturnType MessageDialog::showModal()
{
	verifyUIState();
	return Dialog::showModal();
}

void MessageDialog::show()
{
	verifyUIState();
	Dialog::show();
}

void MessageDialog::addActionButton( const String& caption, const UIToolkit::ModalReturnType returnVal, const bool& defaultButton )
{
	CommandButton* newButton = new CommandButton();

	newButton->setCaption( caption );
	//////////////////////////////////////////////////////////
	//TODO::: switch the types for the CommandButton::setCommandType()  -
	//it should take the same type (UIToolkit::ModalReturnType) and adjust
	//accordingly
	//////////////////////////////////////////////////////////
	switch ( returnVal ) {
		case UIToolkit::mrNone: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrOK: {
			newButton->setCommandType(BC_OK);
		}
		break;

		case UIToolkit::mrCancel: {
			newButton->setCommandType(BC_CANCEL);
		}
		break;

		case UIToolkit::mrYes: {
			newButton->setCommandType(BC_YES);
		}
		break;

		case UIToolkit::mrNo: {
			newButton->setCommandType(BC_NO);
		}
		break;

		case UIToolkit::mrRetry: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrIgnore: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrHelp: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrAbort: {
			newButton->setCommandType(BC_NONE);
		}
		break;
	}


	//set dimensions
	newButton->setHeight( newButton->getPreferredHeight() );
	newButton->setWidth( newButton->getPreferredWidth() );

	//this is a REALLY lame way to do this - need to
	//add some sort of vertical/horizontal  spacing rules for alignment layout
	Label* l = new Label();
	l->setCaption("");
	UIMetricsManager* metricMgr = UIToolkit::getUIMetricsManager();
	l->setWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );
	l->setHeight( newButton->getHeight() );


	commandPane_->add( newButton, AlignRight );
	commandPane_->add( l, AlignRight );

	if ( defaultButton ) {
		newButton->setDefault( true );
		newButton->setFocused();
	}

	buttons_.push_back( newButton );
}

PushButton* MessageDialog::addPushButton( const String& caption, const UIToolkit::ModalReturnType returnVal, const bool& defaultButton )
{
	PushButton* newButton = new PushButton();

	newButton->setCaption( caption );
	//////////////////////////////////////////////////////////
	//TODO::: switch the types for the CommandButton::setCommandType()  -
	//it should take the same type (UIToolkit::ModalReturnType) and adjust
	//accordingly
	//////////////////////////////////////////////////////////
	switch ( returnVal ) {
		case UIToolkit::mrNone: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrOK: {
			newButton->setCommandType(BC_OK);
		}
		break;

		case UIToolkit::mrCancel: {
			newButton->setCommandType(BC_CANCEL);
		}
		break;

		case UIToolkit::mrYes: {
			newButton->setCommandType(BC_YES);
		}
		break;

		case UIToolkit::mrNo: {
			newButton->setCommandType(BC_NO);
		}
		break;

		case UIToolkit::mrRetry: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrIgnore: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrHelp: {
			newButton->setCommandType(BC_NONE);
		}
		break;

		case UIToolkit::mrAbort: {
			newButton->setCommandType(BC_NONE);
		}
		break;
	}


	//set dimensions
	newButton->setHeight( newButton->getPreferredHeight() );
	newButton->setWidth( newButton->getPreferredWidth() );

	//this is a REALLY lame way to do this - need to
	//add some sort of vertical/horizontal  spacing rules for alignment layout
	if ( 0 == commandPane_->getChildCount() ) {
		Label* l = new Label();
		l->setCaption("");
		UIMetricsManager* metricMgr = UIToolkit::getUIMetricsManager();
		l->setWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );
		l->setHeight( newButton->getHeight() );

		commandPane_->add( l, AlignRight );
	}

	Label* l = new Label();
	l->setCaption("");
	UIMetricsManager* metricMgr = UIToolkit::getUIMetricsManager();
	l->setWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );
	l->setHeight( newButton->getHeight() );

	commandPane_->add( newButton, AlignRight );
	commandPane_->add( l, AlignRight );

	if ( defaultButton ) {
		newButton->setDefault( true );
		newButton->setFocused();
	}

	buttons_.push_back( newButton );

	//this->setWidth( ( newButton->getWidth() + l->getWidth() ) * buttons_.size() + l->getWidth() );

	return newButton;
}

void MessageDialog::setMessage( const String& message )
{
	message_ = message;
	messageLabel_->setCaption( message_ );


	double msgWidth = messageLabel_->getContext()->getTextWidth( message );
	double msgHeight = messageLabel_->getContext()->getTextHeight( message );

	if ( msgWidth > messageLabel_->getWidth() ) {
		//adjust bounds

		Rect bounds = getBounds();

		double prefHeight = messageLabel_->getPreferredHeight();
		double dy = fabs( messageLabel_->getHeight() - prefHeight );

		bounds.inflate( 0, dy/2.0 );
		setBounds( &bounds );

		bounds = messageLabel_->getBounds();

		messageLabel_->setHeight( prefHeight );

		bounds = infoLabel_->getBounds();

		bounds.offset( 0, dy );

		infoLabel_->setBounds( &bounds );

		//infoLabel_->setTop( messageLabel_->getBottom() + 5 );
	}

}

void MessageDialog::setInformation( const String& information )
{
	information_ = information;
	infoLabel_->setCaption( information_ );

	double infoWidth = infoLabel_->getContext()->getTextWidth( information );

	if ( infoWidth > infoLabel_->getWidth() ) {
		//adjust bounds

		Rect bounds = getBounds();

		double prefHeight = infoLabel_->getPreferredHeight();

		double dy = fabs(infoLabel_->getHeight() - prefHeight);

		bounds.inflate( 0, dy/2.0 );

		setBounds( &bounds );

		bounds = infoLabel_->getBounds();

		infoLabel_->setHeight( prefHeight );
	}
}

void MessageDialog::setApplicationIcon( Image* icon )
{
	applicationIcon_ = icon;
}

void MessageDialog::verifyUIState()
{
	if ( true == message_.empty() ) {
		throw InvalidMessageDialogException( MAKE_ERROR_MSG_2("Message is empty. This is incorrect and useless - please fix!!!") );
	}

	if ( true == information_.empty() ) {
		throw InvalidMessageDialogException( MAKE_ERROR_MSG_2("Information is empty. This is incorrect and useless - please fix!!!") );
	}

	if ( true == buttons_.empty() ) {
		throw InvalidMessageDialogException( MAKE_ERROR_MSG_2("No buttons are present. This is incorrect and useless - please fix!!!") );
	}


}


/**
$Id$
*/
