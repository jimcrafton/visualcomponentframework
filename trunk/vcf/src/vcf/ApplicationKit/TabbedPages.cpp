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


	borderWidth_ = 8.0;
	tabHeight_ = 12.0;

	tabViewOffset_ = 0.0;


	EventHandler* ev = new ButtonEventHandler<TabbedPages>( this, &TabbedPages::onScrollButtonClicked, "onScrollButtonClicked" );
	/*
	scrollForward_ = new ScrollButton();
	scrollForward_->setHeight( tabHeight_ );
	scrollForward_->setWidth(  tabHeight_ );

	scrollBackward_ = new ScrollButton();
	scrollBackward_->setHeight( tabHeight_ );
	scrollBackward_->setWidth(  tabHeight_ );

	scrollBackward_->setTag( SCROLL_BKWD_TAG );
	scrollForward_->setTag( SCROLL_FWD_TAG );


	scrollForward_->addButtonClickHandler( ev );
	scrollBackward_->addButtonClickHandler( ev );

	add( scrollBackward_ );
	add( scrollForward_ );

	scrollForward_->setVisible( false );
	scrollBackward_->setVisible( false );
	*/

}

TabbedPages::~TabbedPages()
{
	if ( NULL != model_ ){
		model_->release();
	}
}

void TabbedPages::recalcScrollerButtonsPos()
{
	/*

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
	*/
}

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

	Rect bounds = getBounds();
	context->setColor( getColor() );
	context->rectangle( 0, 0, bounds.getWidth(), bounds.getHeight() );
	context->fillPath();

	if ( NULL != model_ ){
		Enumerator<TabPage*>* pages = model_->getPages();
		

		Rect oldClipRect = context->getClippingRect();
		Rect tabClipRect( tabAreaBounds_.left_, 3, tabAreaBounds_.right_, tabAreaBounds_.top_ - 2 );

		//context->setClippingRect( &tabClipRect );

		Rect tabsRect(0,0,0,0);

		TabPage* selectedPage = NULL;

		double currentLeft = tabAreaBounds_.left_;
		Rect selectedRect;


		uint32 pageCount = model_->getPageCount();

		double tabWidth =  tabAreaBounds_.getWidth() / pageCount;
		double width = tabWidth;


		while ( true == pages->hasMoreElements() ){
			TabPage* page = pages->nextElement();
			VCF_ASSERT( NULL != page );
				width = minVal<>( tabWidth, getTabPageWidth( page, context ) );
				tabsRect.setRect( currentLeft, 3,
						          currentLeft+ width, tabAreaBounds_.top_ -2  );

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

		//if ( oldClipRect.isEmpty() ) {
			//oldClipRect.setRect( 0, 0, getWidth(), getHeight() );
		//}

		//context->setClippingRect( &oldClipRect );

		if ( NULL != selectedPage ) {

			Control* component = selectedPage->getPageComponent();

			if ( NULL != component ){
				Rect tmp( tabAreaBounds_ );//*(component->getBounds()) );
				tmp.inflate( 3,3 );
				activePageBorder_.paint( &tmp, context );
			}

			//fill with blank space first
			selectedRect.inflate( 0, 1 );
			context->rectangle( &selectedRect );
			context->fillPath();
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
		model_->release();
	}

	model_ = model;


	if ( NULL != model_ ) {
		model_->addRef();
		model_->addView( this );

		EventHandler* ev = getEventHandler( "TabbedPages::tabTabPageAddedHandler" );
		if ( NULL == ev ) {
			ev = new TabModelEventHandler<TabbedPages>( this, &TabbedPages::onTabPageAdded, "TabbedPages::tabTabPageAddedHandler" );
		}
		model_->addTabPageAddedHandler( ev );

		ev = getEventHandler( "TabbedPages::tabPageRemovedHandler" );
		if ( NULL == ev ) {
			ev = new TabModelEventHandler<TabbedPages>( this, &TabbedPages::onTabPageRemoved, "TabbedPages::tabPageRemovedHandler" );
		}
		model_->addTabPageRemovedHandler( ev );


		ev = getEventHandler( "TabbedPages::tabPageSelectedHandler" );
		if ( NULL == ev ) {
			ev = new TabModelEventHandler<TabbedPages>( this, &TabbedPages::onTabPageSelected, "TabbedPages::tabPageSelectedHandler" );
		}
		model_->addTabPageSelectedHandler( ev );
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
	repaint();

	resizeChildren(NULL);

	recalcScrollerButtonsPos();
}

void TabbedPages::onTabPageRemoved( TabModelEvent* event )
{
	TabPage* page = event->getTabPage();
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

	recalcScrollerButtonsPos();
}

void TabbedPages::onTabPageSelected( TabModelEvent* event )
{
	TabPage* page = event->getTabPage();
	if ( true == page->isSelected() ){
		Enumerator<Control*>* children = getChildren();
		while ( true == children->hasMoreElements() ){
			Control* comp = children->nextElement();
			if ( comp != page->getPageComponent() ){
				comp->setVisible( false );
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
	page->setModel( getModel() );
	page->setPageName( caption );
	Panel* sheet = new Panel();
	sheet->setBorder( NULL );
	page->setPageComponent( sheet );
	add( sheet, AlignClient );
	sheet->setVisible( true );

	tabHeight_ = maxVal<double>( tabHeight_, page->getPreferredHeight() );

	TabModel* model = getModel();
	model->addTabPage( page );

	model->setSelectedPage( page );

	recalcScrollerButtonsPos();

	return page;
}


Rect TabbedPages::getClientBounds( const bool& includeBorder )
{
	Rect bounds = getBounds();

	if ( bounds.isEmpty() ) {
		return Rect();
	}


	tabAreaBounds_.setRect( 0, 0, bounds.getWidth(), bounds.getHeight() );
	tabAreaBounds_.inflate( -borderWidth_, -borderWidth_ );
	tabAreaBounds_.top_ = tabAreaBounds_.top_ + tabHeight_;

	recalcScrollerButtonsPos();

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
	tabPagesBounds.setRect( 0, 0, getWidth(), tabHeight_ );
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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/17 17:56:24  ddiego
*minor mods to the TableControl and the TabbedPages control
*so that drawing updates get drawn better, and we don't have weird missing
*artifacts.
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.24  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.23.2.7  2003/10/12 06:34:13  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.23.2.6  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.23.2.5  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.23.2.4  2003/09/04 21:49:29  ddiego
*minor changes
*
*Revision 1.23.2.3  2003/09/03 01:41:40  ddiego
*some minor fixes
*
*Revision 1.23.2.2  2003/08/22 16:34:39  ddiego
*fixed a mistake in the tabbed pages modle and item
*
*Revision 1.23.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.23  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.22.2.1  2003/08/06 21:27:49  ddiego
*minor changes
*
*Revision 1.22  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.21.2.2  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.21.2.1  2003/03/12 03:13:21  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.21  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.20.2.4  2003/02/02 04:56:40  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.20.2.3  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.20.2.2  2002/12/27 23:05:08  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20.2.1  2002/12/25 22:06:36  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.20  2002/11/18 00:46:10  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.19.4.5  2002/11/16 20:31:35  ddiego
*this fixes the following bugs:
*632802 TextControl's setViewModel not called
*639416 ListViewControl's setViewModel not called
*639417 TreeControl's setViewModel not called
*639418 ListBoxControl's setViewModel not called
*639419 ComboBoxControl's setViewModel not called
*639420 TreeListControl's setViewModel not called
*basically just required that setViewModel() get called. Also made changes to
*the TableControl and teh TabbedPages control
*
*Revision 1.19.4.4  2002/10/04 05:02:55  ddiego
*added beggining support for add new classes. Basic GUI is now in place.
*Also preliminary support for class templates and class wizards
*some documentation done on the format for the XML based class template
*
*Revision 1.19.4.3  2002/09/30 02:16:52  ddiego
*misc piddling
*
*Revision 1.19.4.2  2002/09/27 23:38:36  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.19.4.1  2002/09/24 21:02:37  ddiego
*started to work on fixing up the tabbedpages control
*
*Revision 1.19  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.18.6.1  2002/07/26 04:24:29  ddiego
*added more support for properly querying modified document, and removing the
*documents from the doc tab pages, made some changes in TabbedPages to support
*this as well
*
*Revision 1.18  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.17.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.17.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.17  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


