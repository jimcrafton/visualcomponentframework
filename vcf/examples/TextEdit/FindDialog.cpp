//FindDialog.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "FindDialog.h"
#include "TextEditDocument.h"

using namespace VCF;


FindDialog::FindDialog()
{
	setWidth( 500 );
	setHeight( 200 );
	setCaption( "Find" );

	Rect clientRect = this->getClientBounds();
	
	UIMetricsManager* metrics = UIToolkit::getUIMetricsManager();
	double y = metrics->getPreferredSpacingFor( UIMetricsManager::stWindowBorderDelta );
	double x = clientRect.right_ - (100 + metrics->getPreferredSpacingFor( UIMetricsManager::stWindowBorderDelta ));

	find_ = new CommandButton();
	find_->setBounds( x, y, 100, find_->getPreferredHeight() );
	find_->setCaption( "&Find" );	
	add( find_ );

	y += find_->getHeight() + metrics->getPreferredSpacingFor( UIMetricsManager ::stControlVerticalSpacing );

	find_->addButtonClickHandler( new ButtonEventHandler<FindDialog>(this,&FindDialog::findClicked, "FindDialog::findClicked" ) );

	
	cancel_ = new CommandButton();
	cancel_->setBounds( x, y, 100, cancel_->getPreferredHeight() );
	cancel_->setCaption( "Close" );
	cancel_->setCommandType( BC_CANCEL );
	add( cancel_ );
	

	

	y = metrics->getPreferredSpacingFor( UIMetricsManager::stWindowBorderDelta );
	x = find_->getLeft() - (275 + metrics->getPreferredSpacingFor( UIMetricsManager::stControlHorizontalSpacing ));

	searchStrings_ = new StdStringsChoiceType::Control();
	
	searchString_ = (StdStringsChoiceType::Control*)searchStrings_;

	searchString_->setBounds( &Rect(x, y, x+275, y+searchString_->getPreferredHeight()) );

	add( searchString_ );

	searchString_->setComboBoxStyle( cbsDropDownWithEdit );


	x = metrics->getPreferredSpacingFor( UIMetricsManager::stControlHorizontalSpacing );

	Label* label = new Label();
	label->setCaption( "Search for:" );
	label->setBounds( x, y, 
						(searchString_->getLeft() - metrics->getPreferredSpacingFor( UIMetricsManager::stControlHorizontalSpacing )) - x,
						searchString_->getHeight() );
	add( label );	

	
	y += label->getHeight() + metrics->getPreferredSpacingFor( UIMetricsManager::stControlVerticalSpacing );

	caseSensitive_ = new StdBoolType::Control();

	caseSensitive_->setCaption( "Match Case" );
	caseSensitive_->setBounds( x, y, 175, caseSensitive_->getPreferredHeight() );
	add( caseSensitive_ );
	y += caseSensitive_->getHeight() + metrics->getPreferredSpacingFor( UIMetricsManager::stControlVerticalSpacing )/2.0;

	matchWordOnly_ = new StdBoolType::Control();
	matchWordOnly_->setCaption( "Match Word only" );
	matchWordOnly_->setBounds( x, y, 175, matchWordOnly_->getPreferredHeight() );
	add( matchWordOnly_ );
	y += matchWordOnly_->getHeight() + metrics->getPreferredSpacingFor( UIMetricsManager::stControlVerticalSpacing )/2.0;

	
	find_->setDefault(true);

	double newHeight = getHeight() + (y - clientRect.getHeight());

	setHeight( newHeight );

	searchString_->setFocused();
}

FindDialog::~FindDialog()
{

}

void FindDialog::findClicked( ButtonEvent* e )
{	
	findInfo_.caseSensitive_ = caseSensitive_;
	findInfo_.matchWordOnly_ = matchWordOnly_;
	findInfo_.searchString_ = searchString_;	

	bool addString = true;
	ListModel* listModel = searchString_->getListModel();
	VCF::Enumerator<VCF::ListItem*>* items = listModel->getItems();
	while ( items->hasMoreElements() ) {
		VCF::ListItem* item = items->nextElement();
		if ( item->getCaption() == findInfo_.searchString_ ) {
			addString = false;
			break;
		}
	}

	if ( addString ) {
		listModel->insertItem( 0, new DefaultListItem( NULL, findInfo_.searchString_ ) );
	}

	findInfo_.searchStrings_ = searchStrings_;

	TextEditDocument* doc = (TextEditDocument*)DocumentManager::getDocumentManager()->getCurrentDocument();
	if ( !doc->find( findInfo_ ) ) {
		Dialog::showMessage( "Couldn't find string \"" + findInfo_.searchString_ + "\"" );
	}
	else {
		doc->setSelectionRange( findInfo_.position_, findInfo_.searchString_.size() );
		findInfo_.position_ += findInfo_.searchString_.size();
	}

}

