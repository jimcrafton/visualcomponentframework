//ReplaceDialog.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

#include "ReplaceDialog.h"

using namespace VCF;



ReplaceDialog::ReplaceDialog()
{
	setWidth( 500 );
	setHeight( 250 );
	setCaption( "Replace" );

	Rect clientRect = this->getClientBounds();
	
	
	double y = UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta );
	double x = clientRect.right_ - (100 + UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ));

	findNext_ = new CommandButton();
	findNext_->setBounds( x, y, 100, findNext_->getPreferredHeight() );
	findNext_->setCaption( "&Find Next" );	
	add( findNext_ );

	y += findNext_->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager ::mtControlVerticalSpacing );

	findNext_->ButtonClicked += new ClassProcedure1<ButtonEvent*,ReplaceDialog>(this,&ReplaceDialog::findNextClicked, "ReplaceDialog::findNextClicked" );


	replace_ = new CommandButton();
	replace_->setBounds( x, y, 100, replace_->getPreferredHeight() );
	replace_->setCaption( "&Replace" );	
	add( replace_ );

	y += replace_->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager ::mtControlVerticalSpacing );

	replace_->ButtonClicked += new ClassProcedure1<ButtonEvent*,ReplaceDialog>(this,&ReplaceDialog::replaceClicked, "ReplaceDialog::replaceClicked" );


	replaceAll_ = new CommandButton();
	replaceAll_->setBounds( x, y, 100, replaceAll_->getPreferredHeight() );
	replaceAll_->setCaption( "Replace &All" );
	add( replaceAll_ );

	replaceAll_->ButtonClicked += new ClassProcedure1<ButtonEvent*,ReplaceDialog>(this,&ReplaceDialog::replaceAllClicked, "ReplaceDialog::replaceAllClicked" );

	y += replaceAll_->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager ::mtControlVerticalSpacing );


	cancel_ = new CommandButton();
	cancel_->setBounds( x, y, 100, cancel_->getPreferredHeight() );
	cancel_->setCaption( "Close" );
	cancel_->setCommandType( BC_CANCEL );
	add( cancel_ );
	

	

	y = UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta );
	x = replaceAll_->getLeft() - (275 + UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ));

	searchStrings_ = new StdStringsChoiceType::Control();
	
	searchString_ = (StdStringsChoiceType::Control*)searchStrings_;

	searchString_->setBounds( &Rect(x, y, x+275, y+searchString_->getPreferredHeight()) );

	add( searchString_ );

	searchString_->setComboBoxStyle( cbsDropDownWithEdit );


	x = UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing );

	Label* label = new Label();
	label->setCaption( "Search for:" );
	label->setBounds( x, y, 
						(searchString_->getLeft() - UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing )) - x,
						searchString_->getHeight() );
	add( label );	

	
	y += label->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing );


	x = replaceAll_->getLeft() - (275 + UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ));

	replaceStrings_ = new StdStringsChoiceType::Control();
	
	replaceString_ = (StdStringsChoiceType::Control*)replaceStrings_;

	replaceString_->setBounds( &Rect(x, y, x+275, y+replaceString_->getPreferredHeight()) );

	add( replaceString_ );

	replaceString_->setComboBoxStyle( cbsDropDownWithEdit );


	x = UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing );

	label = new Label();
	label->setCaption( "Replace with:" );
	label->setBounds( x, y, 
						(replaceString_->getLeft() - UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing )) - x,
						replaceString_->getHeight() );
	add( label );	

	
	y += label->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing );



	caseSensitive_ = new StdBoolType::Control();

	caseSensitive_->setCaption( "Match Case" );
	caseSensitive_->setBounds( x, y, 175, caseSensitive_->getPreferredHeight() );
	add( caseSensitive_ );
	y += caseSensitive_->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing )/2.0;

	matchWordOnly_ = new StdBoolType::Control();
	matchWordOnly_->setCaption( "Match Word only" );
	matchWordOnly_->setBounds( x, y, 175, matchWordOnly_->getPreferredHeight() );
	add( matchWordOnly_ );
	y += matchWordOnly_->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing )/2.0;

	
	y += matchWordOnly_->getHeight() + UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing )/2.0;


	double newHeight = getHeight() + (y - clientRect.getHeight());

	setHeight( newHeight );


	findNext_->setDefault(true);

	searchString_->setFocused();
}

ReplaceDialog::~ReplaceDialog()
{

}


void ReplaceDialog::findNextClicked( VCF::ButtonEvent* e )
{

	replaceInfo_.caseSensitive_ = caseSensitive_;
	replaceInfo_.matchWordOnly_ = matchWordOnly_;
	
	replaceInfo_.searchString_ = searchString_;	

	bool addString = true;
	ListModel* listModel = searchString_->getListModel();
	VCF::Enumerator<VCF::ListItem*>* items = listModel->getItems();
	while ( items->hasMoreElements() ) {
		VCF::ListItem* item = items->nextElement();
		if ( item->getCaption() == replaceInfo_.searchString_ ) {
			addString = false;
			break;
		}
	}

	if ( addString ) {
		listModel->insertItem( 0, new DefaultListItem( NULL, replaceInfo_.searchString_ ) );
	}

	replaceInfo_.searchStrings_ = searchStrings_;

	TextEditDocument* doc = (TextEditDocument*)DocumentManager::getDocumentManager()->getCurrentDocument();
	if ( !doc->find( replaceInfo_ ) ) {
		Dialog::showMessage( "Couldn't find string \"" + replaceInfo_.searchString_ + "\"" );
	}
	else {
		doc->setSelectionRange( replaceInfo_.position_, replaceInfo_.searchString_.size() );
		replaceInfo_.position_ += replaceInfo_.searchString_.size();
	}
}

void ReplaceDialog::replaceClicked( VCF::ButtonEvent* e )
{
	
	replaceInfo_.caseSensitive_ = caseSensitive_;
	replaceInfo_.matchWordOnly_ = matchWordOnly_;

	replaceInfo_.searchString_ = searchString_;	

	replaceInfo_.position_ -= replaceInfo_.searchString_.size();
	replaceInfo_.replaceString_ = replaceString_;	

	bool addString = true;
	ListModel* listModel = replaceString_->getListModel();
	VCF::Enumerator<VCF::ListItem*>* items = listModel->getItems();
	while ( items->hasMoreElements() ) {
		VCF::ListItem* item = items->nextElement();
		if ( item->getCaption() == replaceInfo_.replaceString_ ) {
			addString = false;
			break;
		}
	}

	if ( addString ) {
		listModel->insertItem( 0, new DefaultListItem( NULL, replaceInfo_.replaceString_ ) );
	}

	replaceInfo_.replaceStrings_ = replaceStrings_;


	TextEditDocument* doc = (TextEditDocument*)DocumentManager::getDocumentManager()->getCurrentDocument();
	if ( !doc->replace( replaceInfo_ ) ) {
		Dialog::showMessage( "Couldn't replace string \"" + replaceInfo_.replaceString_ + "\"" );
	}
	else {
		doc->setSelectionRange( replaceInfo_.position_, replaceInfo_.searchString_.size() );
		replaceInfo_.position_ += replaceInfo_.searchString_.size();
	}
}

void ReplaceDialog::replaceAllClicked( VCF::ButtonEvent* e )
{	
	replaceInfo_.caseSensitive_ = caseSensitive_;
	replaceInfo_.matchWordOnly_ = matchWordOnly_;

	replaceInfo_.searchString_ = searchString_;	

	replaceInfo_.position_ -= replaceInfo_.searchString_.size();
	replaceInfo_.replaceString_ = replaceString_;	

	bool addString = true;
	ListModel* listModel = replaceString_->getListModel();
	VCF::Enumerator<VCF::ListItem*>* items = listModel->getItems();
	while ( items->hasMoreElements() ) {
		VCF::ListItem* item = items->nextElement();
		if ( item->getCaption() == replaceInfo_.replaceString_ ) {
			addString = false;
			break;
		}
	}

	if ( addString ) {
		listModel->insertItem( 0, new DefaultListItem( NULL, replaceInfo_.replaceString_ ) );
	}

	replaceInfo_.replaceStrings_ = replaceStrings_;

	TextEditDocument* doc = (TextEditDocument*)DocumentManager::getDocumentManager()->getCurrentDocument();
	if ( !doc->replaceAll( replaceInfo_ ) ) {
		Dialog::showMessage( "Couldn't replace string \"" + replaceInfo_.replaceString_ + "\"" );
	}
}


