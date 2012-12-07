//[!output PROJECT_NAME]About.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "[!output PROJECT_NAME]About.h"


using namespace VCF;


[!output PROJECT_NAME]About::[!output PROJECT_NAME]About()
{
	setWidth( 300 );
	setHeight( 100 );

	CommandButton* okBtn = new CommandButton();
	okBtn->setWidth( okBtn->getPreferredWidth() );
	okBtn->setHeight( okBtn->getPreferredHeight() );

	okBtn->setTop( getHeight() - (okBtn->getHeight()+35) );
	okBtn->setLeft( getWidth() - (okBtn->getWidth()+25) );
	add( okBtn );
	okBtn->setFocused();
	okBtn->setCommandType( BC_OK );
	okBtn->setCaption( "&OK" );

	Label* label = new Label();
	label->setBounds( &Rect(25, 10, 200, 45) );
	add( label );
	label->setCaption( "About [!output PROJECT_NAME]." );

	setCaption( "About [!output PROJECT_NAME]" );
}

[!output PROJECT_NAME]About::~[!output PROJECT_NAME]About()
{

}


