//TabbedPages.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TabbedPages.h"
#include "vcf/ApplicationKit/DefaultTabModel.h"
#include "vcf/ApplicationKit/DefaultTabPage.h"
#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/Containers.h"
#include "vcf/GraphicsKit/DrawUIState.h"



#define SCROLL_FWD_TAG	200
#define SCROLL_BKWD_TAG	201

using namespace VCF;



class TabSheet : public Panel {
public:
	TabSheet() {
		setBorder( NULL );
	}

	virtual void paint( GraphicsContext* ctx ) {
		CustomControl::paint( ctx );

		Rect bounds = getClientBounds();

		DrawUIState state;
		state.setEnabled( isEnabled() );
		state.setActive( isActive() );

		ctx->drawThemeTabContent( &bounds, state );

		paintChildren( ctx );
	}
};





TabbedPages::TabbedPages():
	CustomControl( true ),
	model_( NULL )
{
	setContainerDelegate( this );
	setContainer( new StandardContainer() );
	init();
}

void TabbedPages::init()
{
	setBorder( NULL );
	//add a listener to the tab model

	setTabModel( new DefaultTabModel() );

	addComponent( getViewModel() );

	borderWidth_ = UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta );;
	Size sz = UIToolkit::getUIMetricSize( UIMetricsManager::mtTabSize );
	tabHeight_ =  sz.height_; // 21.0;

	tabViewOffset_ = 0.0;


	CallBack* ev = new ClassProcedure1<ButtonEvent*,TabbedPages>( this, &TabbedPages::onScrollButtonClicked, "onScrollButtonClicked" );
	
}

TabbedPages::~TabbedPages()
{
	
}

/*
void TabbedPages::recalcScrollerButtonsPos()
{
	

	TabModel* model = getModel();
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

	GraphicsContext* ctxToUse = ctx;

	if ( NULL == ctxToUse ) {
		ctxToUse = getContext();
	}

	result = ctxToUse->getTextWidth( page->getPageName() ) + 5.0 + tabHeight_;

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

	

	if ( NULL != model_ ){
		Enumerator<TabPage*>* pages = model_->getPages();

		Rect tabsRect(0,0,0,0);

		TabPage* selectedPage = NULL;

		double currentLeft = bounds.left_;
		Rect selectedRect;


		uint32 pageCount = model_->getPageCount();

		double tabWidth =  tabAreaBounds_.getWidth() / pageCount;
		double width = tabWidth;


		while ( true == pages->hasMoreElements() ){
			TabPage* page = pages->nextElement();
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
		}
/*
		//if ( oldClipRect.isEmpty() ) {
			//oldClipRect.setRect( 0, 0, getWidth(), getHeight() );
		//}

		//context->setClippingRect( &oldClipRect );

		if ( NULL != selectedPage ) {

			Control* component = selectedPage->getPageComponent();

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

TabModel* TabbedPages::getModel()
{
	return model_;
}

void TabbedPages::setTabModel( TabModel* model )
{
	if ( NULL != model_ ) {
//		model_->release();
	}

	model_ = model;


	
	if ( NULL != model_ ) {
		Model* mod = dynamic_cast<Model*>(model_);
		if ( NULL != mod ) {
			mod->addView( this ); //calls setViewModel() for us
		}


		CallBack* ev = getCallback( "TabbedPages::onTabPageAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<TabModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageAdded, "TabbedPages::onTabPageAdded" );
		}
		model_->TabPageAdded.add( (EventHandler*)ev );

		ev = getCallback( "TabbedPages::onTabPageRemoved" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<TabModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageRemoved, "TabbedPages::onTabPageRemoved" );
		}
		model_->TabPageRemoved.add( (EventHandler*)ev );


		ev = getCallback( "TabbedPages::onTabPageSelected" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<TabModelEvent*,TabbedPages>( this, &TabbedPages::onTabPageSelected, "TabbedPages::onTabPageSelected" );
		}
		model_->TabPageSelected.add( (EventHandler*)ev );		
	}
	else {
		setViewModel( NULL );
	}

}

void TabbedPages::onTabPageAdded( TabModelEvent* event )
{
	//calculate the total width
	//needed by all the tab pages
	//if the width is gbreater than the controls
	//width then we need to make the scroll buttons
	//visible
	//repaint();

	TabPage* page = event->page;

	TabSheet* sheet = new TabSheet();
	page->setPageComponent( sheet );
	add( sheet, AlignClient );
	//sheet->setVisible( true );


	resizeChildren(NULL);

	//recalcScrollerButtonsPos();
}

void TabbedPages::onTabPageRemoved( TabModelEvent* event )
{
	TabPage* page = event->page;
	TabPage* pageToMakeCurrent = NULL;
	TabModel* model = getModel();
	bool next = false;
	if ( NULL != page ) {
		Enumerator<TabPage*>* pages = model->getPages();

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

		Control* control = page->getPageComponent();
		page->setPageComponent( NULL );

		remove( control );
		removeComponent( control );
		control->free();


	}
	if ( pageToMakeCurrent == page ) {
		pageToMakeCurrent = NULL;
	}

	if ( NULL != pageToMakeCurrent ) {
		model->setSelectedPage( pageToMakeCurrent );
	}
	resizeChildren(NULL);

	//recalcScrollerButtonsPos();
}

void TabbedPages::onTabPageSelected( TabModelEvent* event )
{
	TabPage* page = event->page;
	if ( true == page->isSelected() ){
		Enumerator<Control*>* children = getChildren();
		while ( true == children->hasMoreElements() ){
			Control* comp = children->nextElement();
			if ( comp != page->getPageComponent() ){
				if ( comp->getVisible() ) {
					comp->setVisible( false );
				}
			}
		}
		page->getPageComponent()->setVisible( true );

		Container* container = page->getPageComponent()->getContainer();
		if ( NULL != container ) {
			container->resizeChildren(NULL);
			/*
			Control* tabControl = container->getFirstTabControl();
			if ( NULL != tabControl ) {
				tabControl->setFocused();
			}
			else {

			}
			*/
			page->getPageComponent()->setFocused();
		}
	}
	repaint();
}

TabPage* TabbedPages::addNewPage( const String& caption )
{
	DefaultTabPage* page = new DefaultTabPage();
	page->setModel( getViewModel() );
	page->setPageName( caption );

	tabHeight_ = maxVal<double>( tabHeight_, page->getPreferredHeight() );

	TabModel* model = getModel();
	model->addTabPage( page );

	model->setSelectedPage( page );

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
		TabModel* model = getModel();
		if ( NULL != model ){
			Enumerator<TabPage*>* pages = model->getPages();
			if ( NULL != pages ){
				while ( true == pages->hasMoreElements() ){
					TabPage* page = pages->nextElement();
					if ( NULL != page ){
						if ( true == page->containsPoint( event->getPoint() ) ){
							model_->setSelectedPage( page );
							resizeChildren(NULL);
							break;
						}
					}
				}
			}
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
			TabModel* model = getModel();
			double width = 0.0;
			Enumerator<TabPage*>* pages = model->getPages();
			while ( true == pages->hasMoreElements() ) {
				TabPage* aPage = pages->nextElement();

				width += getTabPageWidth( aPage );
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


/**
$Id$
*/
