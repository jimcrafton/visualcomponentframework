//Transformations.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"





/**
This is a simple application that demonstrates how to modify the 
transformation matrix of a GraphicsContext.  
*/

using namespace VCF;

/**
A simple panel that holds a series of slider control's that enable the 
user to manipulate the values of the translate, scale, shear, and rotation
values for a transformation matrix.
*/
class TransFormController : public Panel {
public:

	enum {
		transXTag = 0,
		transYTag,
		shearXTag,
		shearYTag,
		rotateTag,
		scaleXTag,
		scaleYTag
	}; 

	TransFormController() :xfrmView_(NULL),useConcatFunctions_(false){
		HorizontalLayoutContainer* container = new HorizontalLayoutContainer();
		setContainer( container );		
		
		translateX = new Label();
		translateX->setCaption( "Translate X:" );
		add( translateX );

		SliderControl* slider = new SliderControl();
		slider->setName( "translateX" );
		add( slider );
		slider->setTag( transXTag );
		slider->PositionChanged += 
			new GenericEventHandler<TransFormController>( this, &TransFormController::onSliderValChanged, "TransFormController::onSliderValChanged" );

		slider->setMaxValue( 400 );
		slider->setMinValue( -400 );
		slider->setTickFrequency( 80 );



		translateY = new Label();
		translateY->setCaption( "Translate Y:" );
		add( translateY );

		slider = new SliderControl();
		slider->setName( "translateY" );
		add( slider );
		slider->setTag( transYTag );
		slider->PositionChanged += getEventHandler( "TransFormController::onSliderValChanged" );
		slider->setMaxValue( 400 );
		slider->setMinValue( -400 );
		slider->setTickFrequency( 80 );

		shearX = new Label();
		shearX->setCaption( "Shear X:" );
		add( shearX );

		slider = new SliderControl();
		slider->setName( "shearX" );
		add( slider );
		slider->setTag( shearXTag );
		slider->PositionChanged += getEventHandler( "TransFormController::onSliderValChanged" );
		slider->setMinValue( -360 );
		slider->setMaxValue( 360 );
		slider->setHasTickMarks( false );
		slider->setTickFrequency( 72 );


		shearY = new Label();
		shearY->setCaption( "Shear Y:" );
		add( shearY );

		slider = new SliderControl();
		slider->setName( "shearY" );
		add( slider );
		slider->setTag( shearYTag );
		slider->PositionChanged += getEventHandler( "TransFormController::onSliderValChanged" );
		slider->setMinValue( -360 );
		slider->setMaxValue( 360 );
		slider->setHasTickMarks( false );
		slider->setTickFrequency( 72 );


		scaleX = new Label();
		scaleX->setCaption( "Scale X:" );
		add( scaleX );

		slider = new SliderControl();
		slider->setName( "scaleX" );
		slider->setPosition( 100 );
		add( slider );
		slider->setTag( scaleXTag );
		slider->PositionChanged += getEventHandler( "TransFormController::onSliderValChanged" );

		scaleY = new Label();
		scaleY->setCaption( "Scale Y:" );
		add( scaleY );

		slider = new SliderControl();
		slider->setName( "scaleY" );
		slider->setPosition( 100 );
		add( slider );
		slider->setTag( scaleYTag );
		slider->PositionChanged += getEventHandler( "TransFormController::onSliderValChanged" );

		rotate = new Label();
		rotate->setCaption( "Rotate:" );
		add( rotate );

		slider = new SliderControl();
		slider->setName( "rotate" );
		add( slider );
		slider->setTag( rotateTag );
		slider->PositionChanged += getEventHandler( "TransFormController::onSliderValChanged" );
		slider->setMaxValue( 360 );
		slider->setHasTickMarks( false );
		slider->setTickFrequency( 36 );


		CommandButton* reset = new CommandButton();
		reset->setCaption( "Reset" );
		reset->addButtonClickHandler( new GenericEventHandler<TransFormController>( this, &TransFormController::onReset, "TransFormController::onReset" ) );
		add( reset );

		CheckBoxControl* checkBox = new CheckBoxControl();
		checkBox->setCaption( "Use GraphicsContext::concatXXX functions" );
		checkBox->addButtonClickHandler( new GenericEventHandler<TransFormController>( this, &TransFormController::onUseConcatFunctions, "TransFormController::onUseConcatFunctions" ) );
		add( checkBox );
	}

	virtual double getPreferredHeight() {

		HorizontalLayoutContainer* container = (HorizontalLayoutContainer*)getContainer();
		return container->getMinimumVisibleHeight();
	}

	void onReset( Event* e ) {
		SliderControl* slider = (SliderControl*) findComponent( "translateX" );
		slider->setPosition( 0.0 );

		slider = (SliderControl*) findComponent( "translateY" );
		slider->setPosition( 0.0 );

		slider = (SliderControl*) findComponent( "scaleX" );
		slider->setPosition( 100.0 );

		slider = (SliderControl*) findComponent( "scaleY" );
		slider->setPosition( 100.0 );

		slider = (SliderControl*) findComponent( "shearX" );
		slider->setPosition( 0.0 );

		slider = (SliderControl*) findComponent( "shearY" );
		slider->setPosition( 0.0 );

		slider = (SliderControl*) findComponent( "rotate" );
		slider->setPosition( 0.0 );
	}

	void onUseConcatFunctions( Event* e ) {
		useConcatFunctions_ = !useConcatFunctions_;
		if ( NULL != xfrmView_ ) {
			xfrmView_->repaint();
		}
	}

	void onSliderValChanged( Event* e ) {
		SliderControl* slider = (SliderControl*)e->getSource();
		switch( slider->getTag() ) {
			case transXTag : {
				translateX->setCaption( "Translate X: " + StringUtils::toString( slider->getPosition() ) );
			}
			break;

			case transYTag : {
				translateY->setCaption( "Translate Y: " + StringUtils::toString( slider->getPosition() ) );
			}
			break;

			case shearXTag : {
				shearX->setCaption( "Shear X: " + StringUtils::toString( slider->getPosition() ) );
			}
			break;

			case shearYTag : {
				shearY->setCaption( "Shear Y: " + StringUtils::toString( slider->getPosition() ) );
			}
			break;

			case scaleXTag : {
				scaleX->setCaption( "Scale X: " + StringUtils::toString( slider->getPosition() ) );
			}
			break;

			case scaleYTag : {
				scaleY->setCaption( "Scale Y: " + StringUtils::toString( slider->getPosition() ) );
			}
			break;

			case rotateTag : {
				rotate->setCaption( "Rotate: " + StringUtils::toString( slider->getPosition() ) );
			}
			break;
		}

		if ( NULL != xfrmView_ ) {
			xfrmView_->repaint();
		}
	}

	Label* translateX;
	Label* translateY;
	Label* shearX;
	Label* shearY;
	Label* scaleX;
	Label* scaleY;
	Label* rotate;

	Control* xfrmView_;

	bool useConcatFunctions_;

	double getTransX() {
		
		SliderControl* slider = (SliderControl*) findComponent( "translateX" );
		return slider->getPosition();
	}

	double getTransY() {
		
		SliderControl* slider = (SliderControl*) findComponent( "translateY" );
		return slider->getPosition();
	}

	double getShearX() {
		
		SliderControl* slider = (SliderControl*) findComponent( "shearX" );
		return slider->getPosition();
	}

	double getShearY() {
		
		SliderControl* slider = (SliderControl*) findComponent( "shearY" );
		return slider->getPosition();
	}

	double getScaleX() {
		
		SliderControl* slider = (SliderControl*) findComponent( "scaleX" );
		return slider->getPosition() / 100.0;
	}

	double getScaleY() {
		
		SliderControl* slider = (SliderControl*) findComponent( "scaleY" );
		return slider->getPosition() / 100.0;
	}

	double getRotate() {
		
		SliderControl* slider = (SliderControl*) findComponent( "rotate" );
		return slider->getPosition();
	}

};



bool operator<( const Rect& lhs, const Rect& rhs ) 
{
	
	return (lhs.getWidth() * lhs.getHeight()) < (rhs.getWidth() * rhs.getHeight());
}


/**
A simple custom control that demonstrates drawing with the a matrix and how to 
modify the matrix a whole unit.
*/
class TransformView : public CustomControl {
public:
	TransformView() {

	}

	virtual void paint( GraphicsContext* context ) {
		CustomControl::paint( context );

		Rect r = getClientBounds();
		r.inflate( -10, -10 );

		context->setColor( Color::getColor("white") );
		context->rectangle( &r );
		context->fillPath();

		if ( !(context->getViewableBounds() < r) ) {
			context->setClippingRect( &r );
		}

		int gcs = context->saveState();

		if ( controller_->useConcatFunctions_ ) {
			context->concatRotation( controller_->getRotate() );
			context->concatScale( controller_->getScaleX(), controller_->getScaleY() );
			context->concatShear( controller_->getShearX(), controller_->getShearY() );
			context->concatTranslation( controller_->getTransX(), controller_->getTransY() );
		}
		else {
			context->setRotation( controller_->getRotate() );
			context->setScale( controller_->getScaleX(), controller_->getScaleY() );
			context->setShear( controller_->getShearX(), controller_->getShearY() );
			context->setTranslation( controller_->getTransX(), controller_->getTransY() );
		}

		context->setStrokeWidth( 1 );

		context->setColor( Color::getColor("black") );


		Rect rect(30,40,100,230);
		context->rectangle( rect );

		context->circle( 500, 200, 50 );

		context->strokePath();
		
		

		context->ellipse( 200, 300, 300, 450 );
		context->setColor( Color::getColor("green") );
		context->fillPath();


		context->setStrokeWidth( 2.5 );
		context->setColor( Color::getColor("red") );
		context->strokePath();


		context->setStrokeWidth( 4 );
		context->setColor( Color::getColor("purple") );
		context->roundRect( 350, 400, 500, 500, 20, 20 );
		context->strokePath();

		context->getCurrentFont()->setName( "Arial" );
		context->getCurrentFont()->setPointSize( 15 );

		context->textAt( 200, 200, "Hello There!!" );


		//note - you may have to adjust the path to this accordingly
		//feel free to try different images as well
		Image* img = GraphicsToolkit::createImage( "test.bmp" );
		if ( NULL != img ) {

			context->drawImage( 500, 270, img );

			delete img;
		}

		context->restoreState( gcs );

	}

	TransFormController* controller_;
};



class TransformationsWindow : public Window {
public:
	TransformationsWindow() {
		setCaption( "Transformations" );
		setVisible( true );

		TransformView* xfrmView = new TransformView() ;

		add( xfrmView, AlignClient ) ;

		TransFormController* controller = new TransFormController();
		controller->setHeight( controller->getPreferredHeight() );

		add( controller, AlignTop );

		xfrmView->controller_ = controller;
		controller->xfrmView_ = xfrmView;
	}

	virtual ~TransformationsWindow(){};


	
};




class TransformationsApplication : public Application {
public:

	TransformationsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new TransformationsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 550.0, 700.0 );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TransformationsApplication( argc, argv );

	Application::main();
	
	return 0;
}


