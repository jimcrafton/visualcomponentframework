//ControlsAbout.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "ControlsAbout.h"


using namespace VCF;


ControlsAbout::ControlsAbout()
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
	label->setWordWrap( true );
	add( label );
	label->setCaption( "Some standard VCF Controls. Many more exist." );

	setCaption( "About Controls" );
}

ControlsAbout::~ControlsAbout()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:15:00  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/08/30 03:50:47  dougtinkham
*added copyright
*
*/