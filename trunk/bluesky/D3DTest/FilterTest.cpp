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
		addCallback( new ClassProcedure1<Event*,ImageView>(this, &ImageView::saveImage), "ImageView::saveImage" );
		addCallback( new ClassProcedure1<Event*,ImageView>(this, &ImageView::resetImage), "ImageView::resetImage" );
		
	}

	virtual ~ImageView(){}

	IKFilter* filter;

	IKImage image;
	bool useFilterImage;
	Point lastPt;
	Point currentTrans;	
	double currentScaleFactor;
	double currentAngle;

	virtual void mouseWheel( MouseEvent* e ) {
		if ( e->getMouseDelta() > 0 ) {
			currentScaleFactor += 0.05;
		}
		else {
			currentScaleFactor -= 0.05;
		}

		currentScaleFactor = minVal( 15.0, maxVal( 0.0115, currentScaleFactor ) );
		updateStatus();
		repaint();
	}

	virtual void mouseDown( MouseEvent* e ) {
		setFocused();
		if ( e->hasLeftButton() ) {			
			lastPt = *e->getPoint();
			keepMouseEvents();
		}
		else if ( e->hasRightButton() ) {
			keepMouseEvents();
		}
	}

	virtual void mouseUp( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			lastPt = *e->getPoint();
			releaseMouseEvents();
		}
		else if ( e->hasRightButton() ) {
			releaseMouseEvents();			
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		if ( e->hasLeftButton() ) {
			currentTrans.x_ +=  (e->getPoint()->x_ - lastPt.x_);
			currentTrans.y_ +=  (e->getPoint()->y_ - lastPt.y_);
			lastPt = *e->getPoint();
			updateStatus();
			repaint();
		}
		else if ( e->hasRightButton() ) {

			Rect r = getClientBounds();
			Point center = r.getCenter();			
			Point p = *e->getPoint();

			double dx = p.x_ - center.x_;
			double dy = p.y_ - center.y_;
			currentAngle = (atan2( dx, dy ) * 180.0/M_PI) * -1.0;

			updateStatus();

			repaint();
		}
	}

	void resetXfrms() {
		currentTrans.x_ = 0;
		currentTrans.y_ = 0;
		currentScaleFactor = 1.0;
		currentAngle = 0;
	}

	void updateStatus() {
		StatusBar* status = (StatusBar*)Application::getRunningInstance()->findComponent( "status", true );
		status->setStatusPaneText( 0, Format("Offset: %0.1f, %0.1f   Angle: %0.3f   Scale: %d%%") 
										% currentTrans.x_ 
										% currentTrans.y_ 
										% currentAngle 
										% (int)(currentScaleFactor*100.0) );
	}

	virtual void paint( GraphicsContext* ) {
		IKImageContext ic(this);

		Rect r = getClientBounds();

		if ( NULL == filter ) {
			filter = new IKFilter();
		}

		ic.initView( r.getWidth(), r.getHeight() );

		double x = r.getWidth()/2.0 - image.getSize().width/2;
		double y = r.getHeight()/2.0 - image.getSize().height/2;		
		
		ic.multiTransformMatrix( Matrix2D::translation(-(r.getWidth()/2.0),-(r.getHeight()/2.0)) *
								Matrix2D::scaling( currentScaleFactor, currentScaleFactor ) *
								Matrix2D::rotation(currentAngle) *
								Matrix2D::translation(r.getWidth()/2.0,r.getHeight()/2.0) *
								Matrix2D::translation(currentTrans.x_,currentTrans.y_) );

		ic.clear( &Color(0.0,0.0,0.0,1.0) );

		
		if ( image.getHandle() != 0 && !useFilterImage ) {

			ic.draw( x, y, &image );


		}
		else if ( useFilterImage ) {
			ic.draw( x, y, filter->getOutputImage() );
		}
	}


	
	void resetImage( Event* e ) {
		resetXfrms();
		useFilterImage = false;
		repaint();
	}

	void compileFilter( Event* e ) {
		Control* shaderEdit = (Control*)Application::getRunningInstance()->findComponent( "shaderEdit", true );
		Control* shaderErrors = (Control*)Application::getRunningInstance()->findComponent( "shaderErrors", true );
		shaderErrors->setVisible(false);

		String text = shaderEdit->getModel()->getValueAsString();

		if ( NULL == filter ) {
			filter = new IKFilter();
		}


		try {
			filter->initFromData( text );
			filter->setInputImage( &image );
			useFilterImage = true;
			repaint();
		}
		catch (BasicException&){
			shaderErrors->setHeight( 100 );
			shaderErrors->setVisible(true);			
			shaderErrors->getModel()->setValueAsString( filter->getCompileStatus() );
			useFilterImage = false;
			repaint();
		}
	}

	

	void saveImage( Event* ) {
		CommonFileSaveDialog dlg( this );
		std::vector< std::pair<String,String> > contentTypes;
		GraphicsToolkit::getAvailableImageTypes( contentTypes );
		std::vector< std::pair<String,String> >::iterator it = contentTypes.begin();
		while ( it != contentTypes.end() ) {
			std::pair<String,String>& type = *it;

			dlg.addFilter( type.second + " (*." + type.first + " )", type.first );
			it ++;
		}


		if ( dlg.execute() ) {
			FilePath fileName = dlg.getFileName();
			if ( fileName.getExtension().empty() ) {
				fileName += "." + dlg.getFileExtension();
			}

			IKImage* img = NULL;
			
			if ( image.getHandle() != 0 && !useFilterImage ) {
				img = &image;
			}
			else if ( useFilterImage ) {
				img = filter->getOutputImage();
			}

			if ( NULL != img ) {
				Image* tmpImg = GraphicsToolkit::createImage( img->getSize().width, img->getSize().height );

				img->renderToImage( tmpImg );

				GraphicsToolkit::saveImage( fileName, tmpImg );

				delete tmpImg;
			}
		}
	}

	void openImage( Event* ) {
		CommonFileOpenDialog dlg( this );
		std::vector< std::pair<String,String> > contentTypes;
		GraphicsToolkit::getAvailableImageTypes( contentTypes );
		std::vector< std::pair<String,String> >::iterator it = contentTypes.begin();
		while ( it != contentTypes.end() ) {
			std::pair<String,String>& type = *it;

			dlg.addFilter( type.second + " (*." + type.first + " )", type.first );
			it ++;
		}


		if ( dlg.execute() ) {
			resetXfrms();
			image.initFromFile( dlg.getFileName() );

			StatusBar* status = (StatusBar*)Application::getRunningInstance()->findComponent( "status", true );
			status->setStatusPaneText( 1, Format("Dimensions: %d x %d") % image.getSize().width % image.getSize().height );		

			useFilterImage = false;
			setFocused();
			repaint();
			updateStatus();
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

		addCallback( new ClassProcedure1<Event*,FilterTest>(this, &FilterTest::saveFilterAs), "FilterTest::saveFilterAs" );
		addCallback( new ClassProcedure1<Event*,FilterTest>(this, &FilterTest::openFilter), "FilterTest::openFilter" );		
		addCallback( new ClassProcedure1<Event*,FilterTest>(this, &FilterTest::viewEditor), "FilterTest::viewEditor" );		
		addCallback( new ClassProcedure1<Event*,FilterTest>(this, &FilterTest::viewStatus), "FilterTest::viewStatus" );		
	}

	void viewEditor( Event* e ) {
		Control* editPanel = (Control*)Application::getRunningInstance()->findComponent( "editPanel", true );
		editPanel->setVisible( !editPanel->getVisible() );

		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( editPanel->getVisible() );
	}

	void viewStatus( Event* e ) {
		Control* status = (Control*)Application::getRunningInstance()->findComponent( "status", true );
		status->setVisible( !status->getVisible() );

		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( status->getVisible() );
	}

	void saveFilterAs( Event* ) {
		CommonFileSaveDialog dlg( getMainWindow() );
		dlg.addFilter( "ImageKit Filter (*.shader)", "*.shader" );
		if ( dlg.execute() ) {
			Control* shaderEdit = (Control*)findComponent( "shaderEdit", true );

			FileOutputStream fos(dlg.getFileName());
			AnsiString s = shaderEdit->getModel()->getValueAsString();
			fos.write( (const uchar*)s.c_str(), s.length() );
		}
	}

	void openFilter( Event* ) {
		CommonFileOpenDialog dlg( getMainWindow() );
		dlg.addFilter( "ImageKit Filter (*.shader)", "*.shader" );
		if ( dlg.execute() ) {
			Control* shaderEdit = (Control*)findComponent( "shaderEdit", true );

			FileInputStream fis(dlg.getFileName());
			
			String s;
			fis >> s;
			shaderEdit->getModel()->setValueAsString( s );
		}
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
		delete res;

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


