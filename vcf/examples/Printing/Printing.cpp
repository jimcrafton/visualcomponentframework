//Printing.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/GraphicsKit/PrintContext.h"


using namespace VCF;





class PrintingWindow : public Window {
public:

	enum {
		printEasyWay = 100,
		printHardWay = 200
	};

	PrintingWindow() {
		setCaption( "Printing" );
		setVisible( true );

		MenuBar* menuBar = new MenuBar();
		setMenuBar( menuBar );
		addComponent( menuBar );

		MenuItem* root = menuBar->getRootMenuItem();

		DefaultMenuItem* printing = new DefaultMenuItem( "Printing", root, menuBar );

		DefaultMenuItem* printingPrintHard = new DefaultMenuItem( "Print the &Hard way...", printing, menuBar );
		printingPrintHard->setTag( printHardWay );
	
		printingPrintHard->addMenuItemClickedHandler( new GenericEventHandler<PrintingWindow>(this,&PrintingWindow::onPrint,"PrintingWindow::onPrint") );

		DefaultMenuItem* printingPrintEasy = new DefaultMenuItem( "Print the &Easy Way...", printing, menuBar );
		printingPrintEasy->setTag( printEasyWay );
	
		printingPrintEasy->addMenuItemClickedHandler( getEventHandler("PrintingWindow::onPrint") );
	}

	virtual void paint( GraphicsContext* context ) {
		Window::paint( context );

		Rect r = this->getClientBounds();

		r.inflate( -10, -10 ) ;

		double y = r.top_;

		r.top_ += context->getTextHeight("EM");

		double dpi = GraphicsToolkit::getDPI();

		Rect page8dot5X11dot0;
		page8dot5X11dot0.right_ = 8.5 * dpi;
		page8dot5X11dot0.bottom_ = 11.0 * dpi;		

		if ( r.getWidth() > r.getHeight() ) {
			double ar = page8dot5X11dot0.getWidth() / page8dot5X11dot0.getHeight();

			page8dot5X11dot0.bottom_ = r.getHeight();
			page8dot5X11dot0.right_ = r.getHeight() * ar;

		}
		else{
			double ar = page8dot5X11dot0.getHeight() / page8dot5X11dot0.getWidth();

			page8dot5X11dot0.right_ = r.getWidth();
			page8dot5X11dot0.bottom_ = r.getWidth() * ar;
		}


		context->textAt( r.left_, y, "This page DPI: " + StringUtils::toString( page8dot5X11dot0.getWidth()/8.5 ) );

		page8dot5X11dot0.offset( r.left_ + (r.getWidth()/2.0 - page8dot5X11dot0.getWidth()/2.0),
									r.top_ + (r.getHeight()/2.0 - page8dot5X11dot0.getHeight()/2.0) );
		

		context->setColor( Color::getColor("white") );
		context->rectangle( &page8dot5X11dot0 );
		context->fillPath();

		context->setColor( Color::getColor("black") );
		context->rectangle( &page8dot5X11dot0 );
		context->strokePath();

		doDrawing( context, page8dot5X11dot0 );
	}

	virtual ~PrintingWindow(){};

	void onPrint( Event* e ) {
		CommonPrint dlg(this);

		dlg.setTitle( "Print Dialog from Printing Example" );
		

		if ( dlg.execute() ) {
			
			PrintSession printSession;			

			printSession.setPrintInfoHandle( dlg.getPrintInfo() );

			printSession.setTitle( "My Print Session!" );

			
			Component* source = (Component*)e->getSource();

			switch ( source->getTag() ) {
				case PrintingWindow::printEasyWay : {
					printSession.PageBegun += 
						new EventHandlerInstance<PrintingWindow,PrintEvent>( this, &PrintingWindow::onPrintPage, "PrintingWindow::onPrintPage" );

					printSession.runDefaultPrintLoop();
				}
				break;

				case PrintingWindow::printHardWay : {
					PrintContext* pc = printSession.beginPrintingDocument();


					printSession.beginPage( pc );


					doDrawing( pc, printSession.getPageDrawingRect() );

					printSession.endPage( pc );

					printSession.endPrintingDocument();

					pc->free();
				}
				break;
			}
		}
	}

	void onPrintStarting( Event* e ) {

	}

	void onPrintPage( PrintEvent* e ) {
		StringUtils::traceWithArgs( "Printing page %d\n", e->getCurrentPage() );

		PrintSession* printSession = (PrintSession*)e->getSource();
		doDrawing( e->getPrintContext(), e->getPageBounds() );
	}


	void doDrawing( GraphicsContext* context, Rect& bounds ) {
		
		long drawingOptions = GraphicsContext::tdoCenterHorzAlign;

		double y = bounds.top_;

		context->textAt( bounds.left_, y, "Here's a sample of printing some text!" );

		y += context->getCurrentFont()->getHeight();

		Rect r = bounds;
		r.top_ = y;

		context->textBoundedBy( &r, "This is some centered text.", drawingOptions );

		y += context->getCurrentFont()->getHeight();
	}
	
};




class PrintingApplication : public Application {
public:

	PrintingApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new PrintingWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new PrintingApplication( argc, argv );

	Application::main();
	
	return 0;
}


