//QTPlayerAbout.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "QTPlayerAbout.h"
#include "vcf/ApplicationKit/ControlsKit.h"

using namespace VCF;


QTPlayerAbout::QTPlayerAbout()
{
	setBounds( 100, 100, 150, 150 );
	Label* label = new Label();
	label->setBounds( &Rect(25, 10, 200, 45) );
	add( label, AlignClient );
	label->setCaption( "About QuickTime Player." );

	Rect clientRect = getClientBounds();
	
	CommandButton* okBtn = new CommandButton();
	okBtn->setWidth( okBtn->getPreferredWidth() );
	okBtn->setHeight( okBtn->getPreferredHeight() );

	okBtn->setTop( 10 );
	okBtn->setLeft( clientRect.right_ + 20 );

	add( okBtn );

	clientRect.right_ += okBtn->getWidth() + 25 ;
	
	okBtn->setFocused();
	okBtn->setCommandType( BC_OK );
	okBtn->setCaption( "&OK" );

	setCaption( "About QuickTime Player" );

	setClientBounds( &clientRect );	
}

QTPlayerAbout::~QTPlayerAbout()
{

}


