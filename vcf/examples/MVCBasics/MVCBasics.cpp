//MVCBasics.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"

using namespace VCF;



class CircleShape {
public:

	CircleShape( const Point& pt, const double& radius ) :  center_(pt), radius_(radius) {}

	CircleShape():radius_(0.0){}

	//gotta be a good C++ citizen and provide an operator== overload so
	//we can use this in STL Algorithms

	bool operator==( const CircleShape& rhs ) const{
		return 	center_ == rhs.center_ && radius_ == rhs.radius_;
	}

	/**
    * implementation of operator != is needed for BCB 5 because of the
    * ackward implementation of the find algorithm in RW STL
	*/
	bool operator!=( const CircleShape& rhs ) const{
		return ( !operator==( rhs ) );
	}

	Point center_;
	double radius_;
};


/**
First lets create a model - this will store a collection of circles.
Each circle will have a point defining it's center and a radius.
This model allows us to add, remove and get individual circles, as
well as access to the vector that stores the circles.
*/

class CircleModel : public AbstractModel {
public:

	enum {
		CircleAdded = Model::MODEL_LAST_EVENT + 100,
		CircleRemoved
	};

	void addCircle( const CircleShape& circle ) {
		circles_.push_back( circle );

		ModelEvent e( this, CircleModel::CircleAdded );
		ModelChanged.fireEvent( &e );
		updateAllViews();
	}

	void addCircle( const Point& pt, const double& radius ) {
		addCircle( CircleShape(pt,radius) );
	}

	void removeCircle( const CircleShape& circle ) {
		std::vector<CircleShape>::iterator found = std::find( circles_.begin(), circles_.end(), circle );
		if ( found != circles_.end() ) {

			circles_.erase( found );

			ModelEvent e( this, CircleModel::CircleRemoved );
			ModelChanged.fireEvent( &e );
			updateAllViews();
		}
	}

	CircleShape& getCircle( int index ) {
		return circles_.at(index);
	}

	const CircleShape& getCircle( int index ) const {
		return circles_.at(index);
	}

	std::vector<CircleShape>& getCircles() {
		return circles_;
	}

	const std::vector<CircleShape>& getCircles() const {
		return circles_;
	}

	int size() const {
		return circles_.size();
	}


	/**
	We need to override the Model::empty() method so we can support
	clearing out our model.
	*/
	virtual void empty() {
		//remove all the circles!
		circles_.clear();

		//make sure to call the super class's implementation
		AbstractModel::empty();
	}

	std::vector<CircleShape> circles_;
};






class MVCBasicsPart1Window : public Window {
public:
	MVCBasicsPart1Window() {
		setCaption( "MVCBasics Part 1" );
		setVisible( true );

		CircleModel* model = new CircleModel();

		model->addCircle( Point(100,200), 100 );
		model->addCircle( Point(234,550), 300 );
		model->addCircle( Point(300,400), 80 );

		model->addView( this );
	}


	virtual void paint( GraphicsContext* ctx ) {
		Window::paint( ctx );

		CircleModel* model = (CircleModel*)getViewModel();

		const std::vector<CircleShape>& circles = model->getCircles();
		for ( std::vector<CircleShape>::const_iterator it = circles.begin(); it!=circles.end(); it++ ) {
			const CircleShape& circle = *it;

			ctx->circle( circle.center_, circle.radius_ );

		}
		ctx->setColor( Color::getColor("black") );
		ctx->strokePath();
	}
};





class MVCBasicsPart2View : public AbstractView {
public:
	MVCBasicsPart2View(){}

	virtual void paintView( GraphicsContext* ctx ) {


		Control* control = AbstractView::getViewControl();

		Rect r = control->getClientBounds();

		ctx->rectangle( &r );
		ctx->setColor( Color::getColor("white") );
		ctx->fillPath();


		CircleModel* model = (CircleModel*)getViewModel();

		const std::vector<CircleShape>& circles = model->getCircles();
		for ( std::vector<CircleShape>::const_iterator it = circles.begin(); it!=circles.end(); it++ ) {
			const CircleShape& circle = *it;

			ctx->circle( circle.center_, circle.radius_ );

		}
		ctx->setColor( Color::getColor("black") );
		ctx->strokePath();
	}
};


class MVCBasicsPart2Window : public Window {
public:
	MVCBasicsPart2Window() {
		setCaption( "MVCBasics Part 2" );
		setVisible( true );

		CircleModel* model = new CircleModel();

		model->addCircle( Point(100,200), 100 );
		model->addCircle( Point(234,550), 300 );
		model->addCircle( Point(300,400), 80 );

		View* view = new MVCBasicsPart2View();

		this->setView( view );
		model->addView( view );
	}


};

class MVCBasicsPart3Window : public Window {
public:
	MVCBasicsPart3Window() {
		setCaption( "MVCBasics Part 3" );
		setVisible( true );

		CircleModel* model = new CircleModel();

		model->addCircle( Point(100,200), 100 );
		model->addCircle( Point(234,550), 300 );
		model->addCircle( Point(300,400), 80 );

		View* view = new MVCBasicsPart2View();

		this->setView( view );
		model->addView( view );

		MouseClicked +=
			new MouseEventHandler<MVCBasicsPart3Window>( this, &MVCBasicsPart3Window::onMouseClicked, "MVCBasicsPart3Window::onMouseClicked" );

		KeyUp +=
			new KeyboardEventHandler<MVCBasicsPart3Window>( this, &MVCBasicsPart3Window::onKeyUp, "MVCBasicsPart3Window::onKeyUp" );
	}


	void onMouseClicked( MouseEvent* e ) {
		CircleModel* model = (CircleModel*)getView()->getViewModel();

		model->addCircle( *e->getPoint(), 50 );

	}

	void onKeyUp( KeyboardEvent* e ) {

		if ( e->getVirtualCode() == vkDelete ) {
			CircleModel* model = (CircleModel*)getView()->getViewModel();

			model->empty();
		}
	}
};


class MVCBasicsPart4View : public AbstractView {
public:


	virtual void paintView( GraphicsContext* ctx ) {


		Control* control = AbstractView::getViewControl();

		Rect r = control->getClientBounds();



		ctx->rectangle( &r );
		ctx->setColor( Color::getColor("white") );
		ctx->fillPath();



		CircleModel* model = (CircleModel*)getViewModel();

		const std::vector<CircleShape>& circles = model->getCircles();
		for ( std::vector<CircleShape>::const_iterator it = circles.begin(); it!=circles.end(); it++ ) {
			const CircleShape& circle = *it;

			ctx->setColor( Color::getColor("blue") );
			ctx->circle( circle.center_, circle.radius_ );
			ctx->fillPath();

			ctx->setColor( Color::getColor("black") );
			ctx->circle( circle.center_, circle.radius_ );
			ctx->strokePath();

		}

		EtchedBorder bdr;
		bdr.setStyle( GraphicsContext::etSunken );
		bdr.paint( &r, ctx );
	}
};


class MyMVCController : public Component {
public:

	CircleModel* model_;

	void onMouseClicked( MouseEvent* e ) {

		if ( e->hasLeftButton() ) {
			model_->addCircle( *e->getPoint(), 50 );
		}
		else if ( e->hasRightButton() ) {

			const std::vector<CircleShape>& circles = model_->getCircles();

			std::vector<CircleShape>::const_iterator it = circles.begin();
			Rect r;
			while ( it != circles.end() ) {
				const CircleShape& shape = *it;
				r.left_ = shape.center_.x_ - shape.radius_;
				r.top_ = shape.center_.y_ - shape.radius_;
				r.right_ = shape.center_.x_ + shape.radius_;
				r.bottom_ = shape.center_.y_ + shape.radius_;

				if ( r.containsPt( e->getPoint() ) ) {
					model_->removeCircle( shape );
					break;
				}
				it ++;
			}

		}
	}

	void onKeyUp( KeyboardEvent* e ) {

		if ( e->getVirtualCode() == vkDelete ) {
			model_->empty();
		}
	}
};



class CircleInfoUI : public CustomControl {
public:
	CircleInfoUI() : CustomControl(true) {

		EtchedBorder* bdr = new EtchedBorder();
		bdr->setStyle( GraphicsContext::etSunken );
		setBorder( bdr );


		setContainer( new StandardContainer() );

		circleCount_ = new Label();
		circleCount_->setCaption( "" );

		circleCount_->setHeight( 50 );
		getContainer()->add( circleCount_, AlignTop );

		modelState_ = new Label();
		modelState_->setCaption( "" );

		modelState_->setHeight( 50 );
		getContainer()->add( modelState_, AlignClient );
	}

	virtual void paint( GraphicsContext* ctx ) {
		CustomControl::paint( ctx );
		getContainer()->paintChildren( ctx );
	}

	virtual void updateView( Model* model ) {
		CircleModel* circleModel = (CircleModel*)model;

		String text = StringUtils::format( "Number of circle shapes: %d", circleModel->getCircles().size() );

		circleCount_->setCaption( text );

		CustomControl::updateView( model );
	}


	virtual void setViewModel( Model* model ) {
		EventHandler* ev = getEventHandler( "CircleInfoUI::onCircleModelChanged" );


		if ( NULL != model ) {
			if ( NULL != ev ) {
				model->removeModelHandler( ev );
			}
		}

		CustomControl::setViewModel( model );

		if ( NULL != model ) {
			if ( NULL == ev ) {
				ev = new GenericEventHandler<CircleInfoUI>( this, &CircleInfoUI::onCircleModelChanged, "CircleInfoUI::onCircleModelChanged" );
			}
			model->addModelHandler( ev );
		}
	}


	void onCircleModelChanged( Event* e ) {
		switch ( e->getType() ) {
			case CircleModel::CircleAdded : {
				modelState_->setCaption( "New Circle Added" );
			}
			break;

			case CircleModel::CircleRemoved : {
				modelState_->setCaption( "Circle removed" );
			}
			break;

			case Model::MODEL_EMPTIED : {
				modelState_->setCaption( "Model emptied." );
			}
			break;
		}
	}

protected:
	Label* circleCount_;
	Label* modelState_;
};

class MVCBasicsWindow : public Window {
public:

	MVCBasicsWindow() {
		setContainer( new StandardContainer() );

		setCaption( "MVC Basics" );

		CommandButton* btn1 = new CommandButton();
		btn1->ButtonClicked +=
			new GenericEventHandler<MVCBasicsWindow>(this, &MVCBasicsWindow::example1, "MVCBasicsWindow::example1" );
		btn1->setHeight( btn1->getPreferredHeight() );
		btn1->setCaption( "MVC Basics Part 1" );
		add( btn1, AlignTop );

		CommandButton* btn2 = new CommandButton();
		btn2->ButtonClicked +=
			new GenericEventHandler<MVCBasicsWindow>(this, &MVCBasicsWindow::example2, "MVCBasicsWindow::example2" );
		btn2->setHeight( btn2->getPreferredHeight() );
		btn2->setCaption( "MVC Basics Part 2" );
		add( btn2, AlignTop );

		CommandButton* btn3 = new CommandButton();
		btn3->ButtonClicked +=
			new GenericEventHandler<MVCBasicsWindow>(this, &MVCBasicsWindow::example3, "MVCBasicsWindow::example3" );
		btn3->setHeight( btn3->getPreferredHeight() );
		btn3->setCaption( "MVC Basics Part 3" );
		add( btn3, AlignTop );

		CommandButton* btn4 = new CommandButton();
		btn4->ButtonClicked +=
			new GenericEventHandler<MVCBasicsWindow>(this, &MVCBasicsWindow::example4, "MVCBasicsWindow::example4" );
		btn4->setHeight( btn4->getPreferredHeight() );
		btn4->setCaption( "MVC Basics Part 4" );
		add( btn4, AlignTop );

		CommandButton* btn5 = new CommandButton();
		btn5->ButtonClicked +=
			new GenericEventHandler<MVCBasicsWindow>(this, &MVCBasicsWindow::example5, "MVCBasicsWindow::example5" );
		btn5->setHeight( btn5->getPreferredHeight() );
		btn5->setCaption( "MVC Basics Part 5" );
		add( btn5, AlignTop );

		show();
	}

	void example1( VCF::Event* ) {
		Window* wnd = new MVCBasicsPart1Window();
		wnd->show();
	}

	void example2( VCF::Event* ) {
		Window* wnd = new MVCBasicsPart2Window();
		wnd->show();
	}

	void example3( VCF::Event* ) {
		Window* wnd = new MVCBasicsPart3Window();
		wnd->show();
	}

	void example4( VCF::Event* ) {
		Window* wnd = new Window();
		MyMVCController* controller = new MyMVCController();

		wnd->setCaption( "MVCBasics Part 4" );

		CircleModel* model = new CircleModel();

		model->addCircle( Point(100,200), 100 );
		model->addCircle( Point(234,550), 300 );
		model->addCircle( Point(300,400), 80 );

		View* view = new MVCBasicsPart4View();

		wnd->setView( view );
		model->addView( view );

		wnd->MouseClicked +=
			new MouseEventHandler<MyMVCController>( controller, &MyMVCController::onMouseClicked, "MyMVCController::onMouseClicked" );

		wnd->KeyUp +=
			new KeyboardEventHandler<MyMVCController>( controller, &MyMVCController::onKeyUp, "MyMVCController::onKeyUp" );

		controller->model_ = model;

		wnd->addComponent( controller );
		wnd->show();
	}

	void example5( VCF::Event* ) {
		Window* wnd = new Window();
		MyMVCController* controller = new MyMVCController();

		wnd->setCaption( "MVCBasics Part 5" );

		CircleModel* model = new CircleModel();

		model->addCircle( Point(100,200), 100 );
		model->addCircle( Point(234,550), 300 );
		model->addCircle( Point(300,400), 80 );


		Panel* circlePanel = new Panel();
		circlePanel->setBorder( NULL );

		wnd->add( circlePanel, AlignClient );

		CircleInfoUI* circleInfo = new CircleInfoUI();
		circleInfo->setHeight( 200 );

		model->addView( circleInfo );

		wnd->add( circleInfo, AlignBottom );


		View* view = new MVCBasicsPart4View();

		circlePanel->setView( view );
		model->addView( view );

		circlePanel->MouseClicked +=
			new MouseEventHandler<MyMVCController>( controller, &MyMVCController::onMouseClicked, "MyMVCController::onMouseClicked" );

		circlePanel->KeyUp +=
			new KeyboardEventHandler<MyMVCController>( controller, &MyMVCController::onKeyUp, "MyMVCController::onKeyUp" );

		controller->model_ = model;

		wnd->addComponent( controller );
		wnd->show();
	}
};


class MVCBasicsApplication : public Application {
public:

	MVCBasicsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new MVCBasicsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new MVCBasicsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:15:08  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/23 12:31:57  marcelloptr
*minor fix
*
*Revision 1.2.2.1  2004/10/16 15:22:38  kiklop74
*Updated MVCBasics example to enable compilation on BCB 5
*
*Revision 1.2  2004/08/07 02:47:32  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/08 15:09:42  ddiego
*made the change to the StandardContainer name - the
*old StandardContainer is now called DesignTimeContainer and
*the old FixedStandardContainer is now renamed to StandardContainer.
*
*Revision 1.1.2.5  2004/06/06 07:05:27  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


