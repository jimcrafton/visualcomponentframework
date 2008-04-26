//TabbedPages.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TabbedPages.h"
#include "vcf/ApplicationKit/DefaultTabPage.h"
#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/Containers.h"
#include "vcf/GraphicsKit/DrawUIState.h"



#define SCROLL_FWD_TAG	200
#define SCROLL_BKWD_TAG	201

using namespace VCF;

void TabSheet::paint( GraphicsContext* ctx )
{
	CustomControl::paint( ctx );
	
	Rect bounds = getClientBounds();
	
	DrawUIState state;
	state.setEnabled( isEnabled() );
	state.setActive( isActive() );
	
	ctx->drawThemeTabContent( &bounds, state );
	
	paintChildren( ctx );
}




TabbedPages::TabbedPages():
	CustomControl( true ),
		selectedPage_(NULL)
{
	setContainerDelegate( this );
	setContainer( new StandardContainer() );
	init();
}

void TabbedPages::init()
{
	setBorder( NULL );
	//add a listener to the tab model

	setTabModel( new TabModel() );

	addComponent( getViewModel() );

	borderWidth_ = UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta );;
	Size sz = UIToolkit::getUIMetricSize( UIMetricsManager::mtTabSize );
	tabHeight_ =  sz.height_; // 21.0;

	tabViewOffset_ = 0.0;


	internalTabChange_ = false;

	CallBack* ev = new ClassProcedure1<ButtonEvent*,TabbedPages>( this, &TabbedPages::onScrollButtonClicked, "onScrollButtonClicked" );
	
}

TabbedPages::~TabbedPages()
{
	
}

/*
void TabbedPages::recalcScrollerButtonsPos()
{
	

	TabModel* model = getTabModel();
	double width = 0.0;
	Enumerator<TabPage*>* pages = model->getPages();
	while ( true == pages->hasMoreElements() ) {
		TabPage* aPage = pages->nextElement();

		width += getTabPageWidth( aPage );
	}


	if ( width > this->getWidth() ) {
		//make the scrollers visible;
		double h = tabAreaBounds_.top_ - borderWidth_/2.0;
		double l = getWidth() - (scrollForward_->getWidth() + borderWidth_/2.0);

		scrollForward_->setTop( 1 );
		scrollForward_->setHeight( h );
		scrollForward_->setWidth( h );

		scrollForward_->setLeft( l );



		scrollBackward_->setTop( 1 );
		scrollBackward_->setHeight( h );
		scrollBackward_->setWidth( h );
		scrollBackward_->setLeft( l - scrollBackward_->getWidth() );


		scrollForward_->setVisible( true );
		scrollBackward_->setVisible( true );
	}
	else {
		tabViewOffset_ = 0;
		scrollForward_->setVisible( false );
		scrollBackward_->setVisible( false );
	}
	
}
*/
double TabbedPages::getTabPageWidth( TabPage* page, GraphicsContext* ctx )
{
	double result;
	
	result = getFont()->getTextWidth( page->getPageName() ) + 5.0 + tabHeight_;

	return result;
}

void TabbedPages::paint( GraphicsContext* context )
{
	CustomControl::paint( context );

	
	Border* border = getBorder();

	Rect bounds;

	if ( NULL != border ) {
		bounds = border->getClientRect( &bounds, this );
	}
	else {
		bounds.setRect( 0, 0, getWidth(), getHeight() );
	}

	
	BackgroundState bkg;
	bkg.setEnabled( isEnabled() );
	bkg.setActive( isActive() );
	bkg.colorType_ = SYSCOLOR_FACE;	
	
	context->drawThemeBackground( &bounds, bkg );
	

	DrawUIState pageState;
	pageState.setEnabled( isEnabled() );
	pageState.setActive( isActive() );
	
	bounds.inflate( -borderWidth_,-borderWidth_ );
	
	Size sz = UIToolkit::getUIMetricSize( UIMetricsManager::mtTabSize );

	
	bounds.top_ += sz.height_;
	
	context->drawThemeTabPage( &bounds, pageState );


	TabModel* tm = getTabModel();

	if ( NULL != tm ){
		Array<TabPage*>::iterator it = tabPages_.begin();

		Rect tabsRect(0,0,0,0);

		TabPage* selectedPage = NULL;

		double currentLeft = bounds.left_;
		Rect selectedRect;


		uint32 pageCount = tabPages_.size();

		double tabWidth =  tabAreaBounds_.getWidth() / pageCount;
		double width = tabWidth;


		while ( it != tabPages_.end() ){
			TabPage* page = *it;
			VCF_ASSERT( NULL != page );
			width = minVal<>( tabWidth, getTabPageWidth( page, context ) );
			tabsRect.setRect( currentLeft, bounds.top_ - tabHeight_,
						          currentLeft+ width, bounds.top_  );
			
			tabsRect.offset( tabViewOffset_, 0 );
			
			
			
			if ( true == page->isSelected() ) {
				selectedPage = page;
				selectedRect = tabsRect;
			}
			else {
				page->paint( context, &tabsRect );
			}
			
			currentLeft += width;
			++it;
		}
/*
		//if ( oldClipRect.isEmpty() ) {
			//oldClipRect.setRect( 0, 0, getWidth(), getHeight() );
		//}

		//context->setClippingRect( &oldClipRect );

		if ( NULL != selectedPage ) {

			Control* component = selectedPage->getTabSheet();

			if ( NULL != component ){
				Rect tmp( tabAreaBounds_ );//*(component->getBounds()) );
				tmp.inflate( 2,2 );
				activePageBorder_.paint( &tmp, context );
			}

			//fill with blank space first
			selectedRect.inflate( 2, 2, 2, 1 );
			context->rectangle( &selectedRect );
			context->fillPath();
			selectedPage->paint( context, &selectedRect );
		}
		*/
		if ( NULL != selectedPage ) {
			selectedRect.inflate( 0, 2, 2, 1 );
			selectedPage->paint( context, &selectedRect );
		}

	}
	paintChildren( context );
}

TabModel* TabbedPages::getTabModel()
{
	return (TabModel*) getViewModel();
}

void TabbedPages::modelChanged( Model* oldModel, Model* newModel )
{
	TabModel* tm = (TabModel*)oldModel;
	if ( NULL != tm ) {
		CallBack* ev = getCallback( "TabbedPages::onTabPageAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageAdded, "TabbedPages::onTabPageAdded" );
		}
		tm->ItemAdded.remove( (EventHandler*)ev );

		ev = getCallback( "TabbedPages::onTabPageRemoved" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageRemoved, "TabbedPages::onTabPageRemoved" );
		}
		tm->ItemRemoved.remove( (EventHandler*)ev );


		ev = getCallback( "TabbedPages::onTabPageSelected" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<TabModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageSelected, "TabbedPages::onTabPageSelected" );
		}
		tm->TabPageSelected.remove( (EventHandler*)ev );
	}

	

	tm = dynamic_cast<TabModel*>( newModel );

	VCF_ASSERT( tm != NULL ) ;

	if ( NULL != tm ) {
		CallBack* ev = getCallback( "TabbedPages::onTabPageAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageAdded, "TabbedPages::onTabPageAdded" );
		}
		tm->ItemAdded.add( (EventHandler*)ev );

		ev = getCallback( "TabbedPages::onTabPageRemoved" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageRemoved, "TabbedPages::onTabPageRemoved" );
		}
		tm->ItemRemoved.add( (EventHandler*)ev );


		ev = getCallback( "TabbedPages::onTabPageSelected" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<TabModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageSelected, "TabbedPages::onTabPageSelected" );
		}
		tm->TabPageSelected.add( (EventHandler*)ev );		
	}	
}

void TabbedPages::setTabModel( TabModel* model )
{
	setViewModel( model );
}

void TabbedPages::onTabPageAdded( ListModelEvent* event )
{
	//calculate the total width
	//needed by all the tab pages
	//if the width is gbreater than the controls
	//width then we need to make the scroll buttons
	//visible
	//repaint();

	if ( !internalTabChange_ ) {
		
		
		TabSheet* sheet = new TabSheet();		
		add( sheet, AlignClient );


		DefaultTabPage* page = new DefaultTabPage();	
		addComponent( page );
		tabPages_.insert( tabPages_.begin() + event->index, page );
		
		page->setControl( this );
		page->setModel( this->getViewModel() );
		page->setIndex( tabPages_.size() - 1 );

		page->setTabSheet( sheet );

		sheet->setPage( page );

		sheet->setVisible( true );
		
		tabHeight_ = maxVal<double>( tabHeight_, page->getPreferredHeight() );
		
		resizeChildren(NULL);
	}
}

void TabbedPages::onTabPageRemoved( ListModelEvent* event )
{
	Array<TabPage*>::iterator found = tabPages_.begin() + event->index;
	Array<TabPage*>::iterator it = found;
	it ++;
	while ( it != tabPages_.end() ) {
		TabPage* itemAfter = *it;
		itemAfter->setIndex( itemAfter->getIndex() - 1 );
		
		++it;
	}

	TabPage* page = *found;
	TabSheet* control = page->getTabSheet();
	page->setTabSheet( NULL );
	
	remove( control );
	removeComponent( control );
	control->free();

	tabPages_.erase( found );

	removeComponent( page );
	page->free();
	
	resizeChildren(NULL);

	

	TabPage* pageToMakeCurrent = NULL;
	
	bool next = false;
	
	Enumerator<TabPage*>* pages = getPages();

	while ( true == pages->hasMoreElements() ) {
		TabPage* aPage = pages->nextElement();
		if ( next ) {
			pageToMakeCurrent = aPage;
			break;
		}
		if ( aPage == page ) {
			next = true;
		}
	}
	if ( (!next) || (NULL == pageToMakeCurrent)  ) {
		pages->reset();
		if ( true == pages->hasMoreElements() ) {
			pageToMakeCurrent = pages->nextElement();
		}
	}

	if ( pageToMakeCurrent == page ) {
		pageToMakeCurrent = NULL;
	}

	if ( NULL != pageToMakeCurrent ) {
		setSelectedPage( pageToMakeCurrent );
	}
	
	//recalcScrollerButtonsPos();
}

void TabbedPages::onTabPageSelected( TabModelEvent* event )
{
	TabPage* page = NULL;
	Array<TabPage*>::iterator it = tabPages_.begin();
	while ( it != tabPages_.end() ){
		TabPage* aPage = *it;
		
		if ( aPage->getIndex() == event->index ) {
			aPage->setSelected( true );
			page = aPage;
		}
		else {
			aPage->setSelected( false );
		}
		
		it++;
	}

	selectedPage_ = page;
	if ( NULL == page ) {
		return;
	}


	Enumerator<Control*>* children = getChildren();
	while ( true == children->hasMoreElements() ){
		Control* comp = children->nextElement();
		if ( comp != page->getTabSheet() ){
			if ( comp->getVisible() ) {
				comp->setVisible( false );
			}
		}
	}
	page->getTabSheet()->setVisible( true );

	Container* container = page->getTabSheet()->getContainer();
	if ( NULL != container ) {
		container->resizeChildren(NULL);		
		page->getTabSheet()->setFocused();
	}

	repaint();
}

TabPage* TabbedPages::addNewPage( const String& caption )
{
	
	TabModel* model = getTabModel();
	model->add( caption );

	TabPage* page = tabPages_.back();

	setSelectedPage( page );

	//recalcScrollerButtonsPos();

	return page;
}


Rect TabbedPages::getClientBounds( const bool& includeBorder )
{
	if ( !includeBorder ) {
		return CustomControl::getClientBounds( includeBorder );
	}


	Rect bounds = getBounds();

	if ( bounds.isEmpty() ) {
		return Rect();
	}


	
	tabAreaBounds_.setRect( 0, 0, bounds.getWidth(), bounds.getHeight() );
	tabAreaBounds_.inflate( -borderWidth_, -borderWidth_ );

	tabAreaBounds_ = UIToolkit::getUIMetricRect( UIMetricsManager::mtTabPaneContentRect, &tabAreaBounds_ );

	
	//tabAreaBounds_.bottom_ = tabAreaBounds_.top_;
	//tabAreaBounds_.top_ = tabAreaBounds_.top_ + tabHeight_;

//	recalcScrollerButtonsPos();

	return tabAreaBounds_;
}

/*
void TabbedPages::resizeChildren()
{
	Rect* bounds = getBounds();
	if ( bounds->isEmpty() ) {
		return;
	}

	tabAreaBounds_.setRect( 0, 0, bounds->getWidth(), bounds->getHeight() );
	tabAreaBounds_.inflate( -borderWidth_, -borderWidth_ );
	tabAreaBounds_.top_ = tabAreaBounds_.top_ + tabHeight_;

	recalcScrollerButtonsPos();

	resizeChildrenUsingBounds( &tabAreaBounds_ );
}
*/

void TabbedPages::mouseDown( MouseEvent* event )
{
	CustomControl::mouseDown( event );
	Rect tabPagesBounds;
	tabPagesBounds.setRect( 0, borderWidth_, getWidth(), borderWidth_ + tabHeight_ );
	if ( true == tabPagesBounds.containsPt( event->getPoint() ) ){
		//find tab		
		Array<TabPage*>::iterator it = tabPages_.begin();	
		
		while ( it != tabPages_.end() ){			
			TabPage* page = *it;
			
			if ( page->containsPoint( event->getPoint() ) ){
				setSelectedPage( page );
				resizeChildren(NULL);
				break;
			}			
			
			++it;
		}
	}
}

void TabbedPages::mouseMove( MouseEvent* event )
{
	CustomControl::mouseMove( event );
}

void TabbedPages::mouseUp( MouseEvent* event )
{
	CustomControl::mouseUp( event );
}

double TabbedPages::getBorderWidth()
{
	return borderWidth_;
}

void TabbedPages::setBorderWidth( const double& borderWidth )
{
	borderWidth_ = borderWidth;
}

double TabbedPages::getTabHeight()
{
	return tabHeight_;
}
	
void TabbedPages::setTabHeight( const double& tabHeight )
{
	tabHeight_ = tabHeight;
}

void TabbedPages::onScrollButtonClicked( ButtonEvent* e )
{
	Control* comp = (Control*)e->getSource();

	switch ( comp->getTag() ) {
		case SCROLL_FWD_TAG : {
			TabModel* model = getTabModel();
			double width = 0.0;
			Array<TabPage*>::iterator it = tabPages_.begin();	
			
			while ( it != tabPages_.end() ){			
				TabPage* page = *it;
				
				width += getTabPageWidth( page );
				
				++it;
			}
			double offset = -((width + comp->getWidth()*2) - getWidth());
			tabViewOffset_ = maxVal<double>( offset, tabViewOffset_ - 25 );
		}
		break;

		case SCROLL_BKWD_TAG : {
			tabViewOffset_ = minVal<double>( 0.0, tabViewOffset_ + 25 );
		}
		break;
	}
	repaint();
}

void TabbedPages::ScrollButton::paint( GraphicsContext* ctx )
{
	//PushButton::paint( ctx );

	DrawUIState state;
	BackgroundState bkState;

	Rect r = getClientBounds(false);

	bkState.colorType_ = SYSCOLOR_FACE;
	ctx->drawThemeBackground( &r, bkState );

	ctx->drawThemeEdge( &r, state, 
						GraphicsContext::etAllSides, GraphicsContext::etRaised );

	



	switch ( getTag() ) {
		case SCROLL_FWD_TAG : {
			//ctx->drawHorizontalScrollButtonRect( &getClientBounds(), false, this->isPressed_ );
		}
		break;

		case SCROLL_BKWD_TAG : {
			//ctx->drawHorizontalScrollButtonRect( &getClientBounds(), true, this->isPressed_ );
		}
		break;
	}
}

TabPage* TabbedPages::getTabPage( const uint32& index )
{
	TabPage* result = NULL;
	if ( index < tabPages_.size() ) {
		tabPages_[index];
	}

	return result;
}

void TabbedPages::setTabPage( const uint32& index, TabPage* page )
{
	if ( index < tabPages_.size() ) {
		tabPages_[index]->free();
		tabPages_[index] = page;
		repaint();
	}
}


TabPage* TabbedPages::getPageFromPageName( const String& pageName )
{
	TabPage* result = NULL;
	
	Array<TabPage*>::iterator it = tabPages_.begin();	
	
	while ( it != tabPages_.end() ){			
		TabPage* page = *it;		
		if ( pageName == page->getPageName() ){
			result = page;
			break;
		}			
		
		++it;
	}

	return result;
}

TabSheet* TabbedPages::getSelectedSheet()
{
	if ( NULL == selectedPage_ ) {
		return NULL;
	}

	return selectedPage_->getTabSheet();
}

void TabbedPages::setSelectedSheet( TabSheet* sheet )
{
	if ( NULL == sheet ) {
		TabPage* nullPg = NULL;
		setSelectedPage( nullPg );
	}
	else {
		setSelectedPage( sheet->getPage() );
	}
}

TabPage* TabbedPages::getSelectedPage()
{
	return selectedPage_;
}

void TabbedPages::setSelectedPage( TabPage* page )
{	
	TabModel* tm = getTabModel();
	if ( NULL != page ) {		
		tm->setSelectedPage( page->getIndex() );
	}
	else {		
		tm->setSelectedPage( TabModel::NoPageSelected );
	}
}

void TabbedPages::setSelectedPageByIndex( const uint32& index )
{
	TabPage* page = NULL;
	Array<TabPage*>::iterator found = tabPages_.begin() + index;
	if ( found != tabPages_.end() ) {
		page = *found;
	}
	
	setSelectedPage( page );	
}

bool TabbedPages::isFirstPage( TabPage* page )
{
	bool result = false;
	
	if ( !tabPages_.empty() ) {
		if ( tabPages_.front() == page ) {
			result = true;
		}
	}

	return result;
}

bool TabbedPages::isLastPage( TabPage* page )
{
	bool result = false;
	
	if ( !tabPages_.empty() ) {
		if ( tabPages_.back() == page ) {
			result = true;
		}
	}

	return result;
}

TabPage* TabbedPages::nextPage( TabPage* page )
{
	TabPage* result = NULL;
	
	Array<TabPage*>::iterator found = std::find( tabPages_.begin(), tabPages_.end(), page );
	if ( found != tabPages_.end() ) {
		found ++;
		if ( found != tabPages_.end() ) {							
			result = *found;
		}
	}

	return result;
}

TabPage* TabbedPages::previousPage( TabPage* page )
{
	TabPage* result = NULL;
	
	Array<TabPage*>::iterator found = std::find( tabPages_.begin(), tabPages_.end(), page );
	if ( found != tabPages_.end() ) {
		found --;
		if ( found >= tabPages_.begin() ) {
			result = *found;
		}
	}

	return result;
}

Enumerator<TabPage*>* TabbedPages::getPages()
{
	return tabPages_.getEnumerator();
}

void TabbedPages::handleEvent( Event* e )
{
	CustomControl::handleEvent( e );
	switch ( e->getType() ){
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)e;
			Component* child = ev->getChildComponent();
			Control* ctrl = dynamic_cast<Control*>(child);
			if ( NULL != ctrl ) {
				TabSheet* tabSheet = dynamic_cast<TabSheet*>(ctrl);
				if ( NULL != tabSheet ) {

					TabModel* tm = getTabModel();

					internalTabChange_ = tm->getCount() == tabPages_.size();


					if ( internalTabChange_ ) {
						
						tm->add( tabSheet->getTitle() );


						DefaultTabPage* page = new DefaultTabPage();	
						addComponent( page );
						tabPages_.push_back( page );
						
						
						page->setControl( this );
						page->setModel( tm );
						page->setIndex( tabPages_.size() - 1 );						
						page->setTabSheet( tabSheet );
						tabSheet->setPage( page );
						
						
						tabHeight_ = maxVal<double>( tabHeight_, page->getPreferredHeight() );
						
						resizeChildren(NULL);


						internalTabChange_ = false;
					}					
				}
				else {
					throw RuntimeException( "Invalid control type added." );
				}
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			
		}
		break;
	}
}

/**
$Id$
*/
