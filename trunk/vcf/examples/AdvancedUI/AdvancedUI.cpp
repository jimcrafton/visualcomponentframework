//AdvancedUI.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"

using namespace VCF;

class WhiteBorder : public Border  {
public:
	Font titleFont_;
	String title_;

	WhiteBorder( const String& title ):title_(title){
		titleFont_.setName( "Tahoma" );
		titleFont_.setBold( true );
		titleFont_.setPointSize( 9 );
		titleFont_.setColor( Color::getColor("black") );
	}

	WhiteBorder(){
		titleFont_.setName( "Tahoma" );
		titleFont_.setBold( true );
		titleFont_.setPointSize( 9 );
		titleFont_.setColor( Color::getColor("black") );
	}

	virtual void paint( Control* control, GraphicsContext* context ) {
		paint( &control->getClientBounds(false), context );
	}

	virtual void paint( Rect* bounds, GraphicsContext* context ) {
		int gcs = context->saveState();

		context->setColor( GraphicsToolkit::getSystemColor(SYSCOLOR_FACE) );

		context->moveTo( bounds->left_-1, bounds->top_ );
		context->lineTo( bounds->right_+1, bounds->top_ );
		context->strokePath();


		context->setColor( Color::getColor("white") );
		context->setStrokeWidth( 1 );
		context->setCurrentFont( &titleFont_ );


		context->moveTo( bounds->left_ +1, bounds->top_ );
		context->lineTo( bounds->right_ -1, bounds->top_ );

		context->moveTo( bounds->right_-1, bounds->top_+1 );
		context->lineTo( bounds->right_-1, bounds->bottom_-1 );
		context->lineTo( bounds->left_, bounds->bottom_-1 );
		context->lineTo( bounds->left_, bounds->top_ );
		context->strokePath();

		context->setCurrentFont( &titleFont_ );

		double h = context->getTextHeight( "EM" ) ;
		Rect titleRect = *bounds;
		titleRect.inflate( -1, -1 );
		titleRect.bottom_ = titleRect.top_ + h;
		Color titleColor((unsigned char)182, (unsigned char)189, (unsigned char)210);
		context->setColor( &titleColor );
		context->rectangle( &titleRect );
		context->fillPath();
		
		titleRect.left_ += 10;
		long options = GraphicsContext::tdoCenterVertAlign;
		context->textBoundedBy( &titleRect, title_, options );		
		context->restoreState( gcs );
	}

	virtual Rect getClientRect( Rect* initialBounds, Control* control ) {
		Rect result = *initialBounds;

		result.inflate( -1, -1 );
		GraphicsContext* ctx = control->getContext();
		Font old = *ctx->getCurrentFont();

		ctx->setCurrentFont(&titleFont_);

		result.top_ += ctx->getTextHeight( "EM" );

		ctx->setCurrentFont(&old);

		return result;
	}
};

class HeaderLabel : public Label {
public:
	HeaderLabel() {
		setHeight( getPreferredHeight() );
		getFont()->setName( "Tahoma" );
		getFont()->setPointSize( 9 );
		getFont()->setBold( true );

	}
	virtual void paint( GraphicsContext* ctx ) {
		Label::paint( ctx );

		Rect r = getClientBounds();
		ctx->setColor( Color::getColor("black") );
		ctx->moveTo( r.left_, r.bottom_-1 );
		ctx->lineTo( r.right_, r.bottom_-1 );
		ctx->strokePath();
	}
};




class CategoryItem : public DefaultTreeItem {
public:
	CategoryItem() {

	}

	virtual bool canPaint() {
		return true;
	}

	virtual void paint( GraphicsContext* ctx, Rect* paintRect ) {
		DefaultTreeItem::paint( ctx, paintRect );

		int gcs = ctx->saveState();
		ctx->getCurrentFont()->setPointSize( 10 );
		ctx->getCurrentFont()->setBold( true );
		ctx->getCurrentFont()->setColor( Color::getColor("blue") );
		ctx->getCurrentFont()->setName( "Tahoma" );

		Color col;
		if ( this->isSelected() ) {
			col = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
			double h,l,s;
			col.getHLS(h,l,s);
			l += 0.10;
			col.setHLS( h,l,s );
			ctx->getCurrentFont()->setColor( Color::getColor("black") );
		}
		else {
			col = *Color::getColor("white");
		}
		Rect r = *paintRect;
		r.left_ = 0;
		r.right_ = this->getControl()->getRight();

		ctx->setColor( &col );
		ctx->rectangle( &r );
		ctx->fillPath();
		long options = GraphicsContext::tdoCenterVertAlign;
		ctx->textBoundedBy( paintRect, this->getCaption(), options );		

		if ( this->isSelected() ) {
			ctx->setColor( Color::getColor("black") );
			ctx->moveTo( r.getTopLeft() );
			ctx->lineTo( r.getTopRight() );
			ctx->strokePath();
			
			ctx->moveTo( r.left_, r.bottom_ - 1 );
			ctx->lineTo( r.right_, r.bottom_ - 1 );
			ctx->strokePath();
		}		

		ctx->restoreState( gcs );
	}
};


class TemplateItem : public DefaultListItem {
public:
	String getComments() {
		return comments_;
	}

	void setComments( const String& val ) {
		comments_ = val;
	}

	String comments_;
};


class CategoryPanel : public Panel {
public:
	CategoryPanel() {
		setBorder( NULL );

		selectedItem_ = NULL;

		setColor( Color::getColor("white") );
		setUseColorForBackground( true );
	}

	TemplateItem* selectedItem_;

	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint(ctx);
		
		if ( NULL != selectedItem_ ) {

			Rect commentsRect;
			commentsRect = getClientBounds();

			
			commentsRect.top_ = commentsRect.bottom_ - 100;
			commentsRect.offset( 0, -20 );
			commentsRect.inflate( -10, 0 );


			Color col = *GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP );
			ctx->setColor( &col );

			Point rrSize(15,15);

			ctx->roundRect( &commentsRect, &rrSize );
			ctx->fillPath();

			ctx->setColor( Color::getColor("black") );
			ctx->strokePath();


			commentsRect.inflate( -5, -5 );

			Rect title = commentsRect;
			

			ctx->getCurrentFont()->setName( "Tahoma" );
			ctx->getCurrentFont()->setPointSize( 11 );
			ctx->getCurrentFont()->setBold( true );

			title.bottom_ = title.top_ + (ctx->getTextHeight("EM") * 1.75);

			long options = GraphicsContext::tdoCenterVertAlign | GraphicsContext::tdoCenterHorzAlign;
			ctx->textBoundedBy( &title, selectedItem_->getCaption(), options );

			commentsRect.top_ = title.bottom_;

			ctx->getCurrentFont()->setBold( false );
			ctx->getCurrentFont()->setPointSize( 9 );

			ctx->textBoundedBy( &commentsRect, selectedItem_->getComments(), true );
		}
	}
};


class CategoryTemplatePanel : public Panel {
public:
	CategoryTemplatePanel() {
		setBorder( new WhiteBorder("Choose Wank Style") );

		HorizontalLayoutContainer* container = new HorizontalLayoutContainer();
		container->setMaximizeLastRow( true );
		container->setBorderWidth( 15 );
		container->setColumnTweenWidth( 0, 55 );
		container->setColumnWidth( 0, 275 );
		container->setRowSpacerHeight( 15 );

		setContainer( container );

		setColor( Color::getColor("white") );
		this->setUseColorForBackground(true);

		HeaderLabel* label = new HeaderLabel();

		label->setCaption( "Category" );
		add( label );

		HeaderLabel* label2 = new HeaderLabel();
		label2->setCaption( "Template" );
		add( label2 );

		catPanel_ = new CategoryPanel();

		add( catPanel_ );

		categories_ = new TreeControl();		
		categories_->setVisible( true );
		categories_->setBorder( NULL );
		categories_->ItemSelected += 
			new GenericEventHandler<CategoryTemplatePanel>(this,&CategoryTemplatePanel::onCatItemSelected, "CategoryTemplatePanel::onCatItemSelected");

		categories_->setHeight( 300 );

		catPanel_->add( categories_, AlignTop );


		categories_->getFont()->setName( "Tahoma" );
		categories_->getFont()->setBold( true );
		categories_->getFont()->setPointSize( 12 );
		categories_->getFont()->setColor( Color::getColor("blue") );

		CategoryItem* item = new CategoryItem();
		categories_->getTreeModel()->addNodeItem( item );
		item->setCaption( "Block Diagrams" );

		item = new CategoryItem();
		categories_->getTreeModel()->addNodeItem( item );
		item->setCaption( "Really Big Block Diagrams" );

		item = new CategoryItem();
		categories_->getTreeModel()->addNodeItem( item );
		item->setCaption( "Really Ugly Diagrams" );

		item = new CategoryItem();
		categories_->getTreeModel()->addNodeItem( item );
		item->setCaption( "Tea and Crumpets Diagrams" );



		Color col = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
		double h,l,s;
		col.getHLS(h,l,s);
		l += 0.10;
		col.setHLS( h,l,s );
		

		templates_ = new ListViewControl();		
		templates_->setVisible( true );
		templates_->setColor( &col );
		templates_->setBorder( NULL );
		templates_->getFont()->setName( "Tahoma" );

		templates_->getFont()->setPointSize( 10 );


		TemplateItem* templateItem = new TemplateItem();
		templateItem->setCaption( "Oggle Boggle" );
		templateItem->setImageIndex( 0 );
		templateItem->setComments( "Creates structures relevant to value-add propositions within the relevant vertical Oggle markets." );

		templates_->addItem( templateItem );
		
		templateItem = new TemplateItem();
		templateItem->setCaption( "Sub Tactical Design" );
		templateItem->setImageIndex( 1 );
		templateItem->setComments( "A refreshing look at non capital markets in Design fetish UML." );

		templates_->addItem( templateItem );

		templateItem = new TemplateItem();
		templateItem->setCaption( "Dongle Structures" );
		templateItem->setImageIndex( 2 );
		templateItem->setComments( "Secure application design and structures through the use of 4 dimensionsal Dongles." );

		templates_->addItem( templateItem );


		templates_->ItemSelectionChanged +=
			new GenericEventHandler<CategoryTemplatePanel>(this,&CategoryTemplatePanel::onTemplItemSelected, "CategoryTemplatePanel::onTemplItemSelected");
		

		add( templates_ );

		ImageList* il = new ImageList();
		addComponent( il );

		il->setImageHeight( 93 );
		il->setImageWidth( 93 );
		//try {

		GraphicsResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();

		Image* img =  resBundle->getImage("template1.bmp"); //GraphicsToolkit::createImage( "template1.bmp" );
		if ( NULL != img ) {
			il->addImage( img );
			delete img;
		}

		img = resBundle->getImage("template2.bmp");
		if ( NULL != img ) {
			il->addImage( img );
			delete img;
		}

		img = resBundle->getImage("template3.bmp");
		if ( NULL != img ) {
			il->addImage( img );
			delete img;
		}
		//}
		//catch (BasicException& e ) {
		//	Dialog::showMessage( e.getMessage() );
		//}

		templates_->setLargeImageList( il );
	}

	ListViewControl* templates_;
	TreeControl* categories_;
	CategoryPanel* catPanel_;

	void onCatItemSelected( Event* e ) {

		catPanel_->selectedItem_ = NULL;
		catPanel_->repaint();
		repaint();
	}

	void onTemplItemSelected( Event* e ) {
		
		catPanel_->selectedItem_ = (TemplateItem*)templates_->getSelectedItem();
		catPanel_->repaint();

		repaint();
	}

	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		int gcs = ctx->saveState();

		Rect templateBounds = templates_->getBounds();
		templateBounds.inflate( 5, 5 );
		Rect catBounds = categories_->getBounds();
		catBounds.inflate( 5, 5 );

		Rect itemRect;

		if ( NULL != categories_->getSelectedItem() ) {
			itemRect = *categories_->getSelectedItem()->getBounds();
		}
		
		categories_->translateToScreenCoords( &itemRect );

		translateFromScreenCoords( &itemRect );
		itemRect.bottom_ -= 1;

		std::vector<Point> pts(9);
		pts[0].x_ = catBounds.left_;
		pts[0].y_ = itemRect.top_;

		pts[1].x_ = templateBounds.left_;
		pts[1].y_ = itemRect.top_;

		pts[2].x_ = templateBounds.left_;
		pts[2].y_ = templateBounds.top_;

		pts[3].x_ = templateBounds.right_;
		pts[3].y_ = templateBounds.top_;

		pts[4].x_ = templateBounds.right_;
		pts[4].y_ = templateBounds.bottom_;

		pts[5].x_ = templateBounds.left_;
		pts[5].y_ = templateBounds.bottom_;

		pts[6].x_ = templateBounds.left_;
		pts[6].y_ = itemRect.top_ + itemRect.getHeight();

		pts[7].x_ = catBounds.left_;
		pts[7].y_ = itemRect.top_ + itemRect.getHeight();

		pts[8].x_ = catBounds.left_;
		pts[8].y_ = itemRect.top_;


		Color col = *GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
		double h,l,s;
		col.getHLS(h,l,s);
		l += 0.10;
		col.setHLS( h,l,s );
		ctx->setColor( &col );

		
		
		Point rrSize(20,20);

		//ctx->roundRect( &templateBounds, &rrSize );
		ctx->polyline( pts );
		ctx->fillPath();


		ctx->setColor( Color::getColor("black") );
		ctx->strokePath();



		


		ctx->restoreState( gcs );
	}
};	

class AdvancedUIWindow : public Window {
public:
	AdvancedUIWindow() {
		setCaption( "AdvancedUI" );		

		Panel* p = new CategoryTemplatePanel();

		add( p, AlignClient );
		
	}

	virtual ~AdvancedUIWindow(){};

};




class AdvancedUIApplication : public Application {
public:

	AdvancedUIApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new AdvancedUIWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new AdvancedUIApplication( argc, argv );

	Application::main();
	
	return 0;
}


