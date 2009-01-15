//FilterTest.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ScintillaKit/ScintillaKit.h"
#include "vcf/ApplicationKit/StatusBar.h"

#include "ImageKit.h"


using namespace VCF;

class ImageView : public CustomControl {
public:

	ImageView(): CustomControl(),filter(NULL),useFilterImage(false) {
		addCallback( new ClassProcedure1<Event*,ImageView>(this, &ImageView::openImage), "ImageView::openImage" );
		addCallback( new ClassProcedure1<Event*,ImageView>(this, &ImageView::compileFilter), "ImageView::compileFilter" );
		
	}

	IKFilter* filter;

	IKImage image;
	bool useFilterImage;

	virtual void paint( GraphicsContext* ) {
		IKImageContext ic(this);

		Rect r = getClientBounds();

		if ( NULL == filter ) {
			filter = new IKFilter();
		}

		ic.initView( r.getWidth(), r.getHeight() );

		ic.clear( &Color(0.0,0.0,0.0,1.0) );

		double x = r.getWidth()/2.0 - image.getSize().width/2;
		double y = r.getHeight()/2.0 - image.getSize().height/2;

		if ( image.getHandle() != 0 && !useFilterImage ) {

			ic.draw( x, y, &image );


		}
		else if ( useFilterImage ) {
			ic.draw( x, y, filter->getOutputImage() );
		}
	}


	void compileFilter( Event* e ) {
		Control* shaderEdit = (Control*)Application::getRunningInstance()->findComponent( "shaderEdit", true );

		String text = shaderEdit->getModel()->getValueAsString();

		if ( NULL == filter ) {
			filter = new IKFilter();
		}


		filter->initFromData( text );
		filter->setInputImage( &image );
		useFilterImage = true;
		repaint();
	}

	void openImage( Event* ) {
		CommonFileOpenDialog dlg( this );
		std::vector< std::pair<String,String> > contentTypes;
		GraphicsToolkit::getAvailableImageTypes( contentTypes );
		std::vector< std::pair<String,String> >::iterator it = contentTypes.begin();
		while ( it != contentTypes.end() ) {
			std::pair<String,String>& type = *it;

			dlg.addFilter( type.second + " (*." + type.first + " )", "*." + type.first );
			it ++;
		}


		if ( dlg.execute() ) {
			image.initFromFile( dlg.getFileName() );

			StatusBar* status = (StatusBar*)Application::getRunningInstance()->findComponent( "status", true );
			status->setStatusPaneText( 1, Format("Dimensions: %d x %d") % image.getSize().width % image.getSize().height );

			useFilterImage = false;
			repaint();
		}
	}
};

_class_rtti_(ImageView, "VCF::CustomControl", "ImageView")
_class_rtti_end_


class FilterTestWindow : public Window {
public:
	FilterTestWindow() {}
	virtual ~FilterTestWindow(){};
};

_class_rtti_(FilterTestWindow, "VCF::Window", "FilterTestWindow")
_class_rtti_end_





class FilterTest : public Application {
public:

	FilterTest( int argc, char** argv ) : Application(argc, argv) {
		OpenGLKit::init(argc,argv);
		ImageKit::init(argc,argv);
		ScintillaKit::init(argc,argv);
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(FilterTestWindow);
		REGISTER_CLASSINFO_EXTERNAL(ImageView);
		

		Window* mainWindow = Frame::createWindow( classid(FilterTestWindow) );
		setMainWindow(mainWindow);
		Control* shaderEdit = (Control*)Application::getRunningInstance()->findComponent( "shaderEdit", true );

		Resource* res = this->getResourceBundle()->getResource( "default.shader" );

		String defaultText( (const char*)res->getData(), res->getDataSize() );

		shaderEdit->getModel()->setValueAsString( defaultText );

		mainWindow->initializeSettings(true);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<FilterTest>(argc,argv);
}


