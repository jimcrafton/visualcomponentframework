//OGLDraw.cpp




#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/RTTIMacros.h"





#include "ImageKit.h"


namespace VCF {

	class AnimationEvent : public Event {
	public:
		AnimationEvent( Object* source ): Event(source),currentFrame(0){}


		uint64 currentFrame;

		

	};

	typedef Delegate1<AnimationEvent*> AnimationDelegate;

	class Animation : public Component {
	public:

		DELEGATE(AnimationDelegate,AnimationStarted);
		DELEGATE(AnimationDelegate,AnimationFrame);  //fired for each animation "tick" or frame
		DELEGATE(AnimationDelegate,AnimationFinished);

		static const double InfiniteDuration;


		Animation(): 
			Component(), 
			removeWhenFinished_(false), 			
			start_(DateTime::now()),
			duration_(1.0),
			frameRate_(29.97),
			repeatCount_(1),
			reverseWhenComplete_(false),
			currentFrame_(0),
			endByFrame_(true),
			targetControl_(NULL)

			{

			addCallback( new ClassProcedure1<TimerEvent*,Animation>(this, &Animation::startAnimation), "Animation::startAnimation" );
			addCallback( new ClassProcedure1<TimerEvent*,Animation>(this, &Animation::animationTimer), "Animation::animationTimer" );
		}

		virtual void destroy() {
			UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::animationTimer" ) );
			UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::startAnimation" ) );
			Component::destroy();
		}


		DateTime getStart() {
			return start_;
		}

		void setStart( const DateTime& val ) {
			if ( val != start_ ) {

				UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::animationTimer" ) );
				UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::startAnimation" ) );

				DateTime n = DateTime::now();

				start_ = val;
				
				if ( start_ < n ) {
					UIToolkit::registerTimerHandler( this, (EventHandler*)getCallback( "Animation::startAnimation" ), 0 );
				}
				else {
					DateTimeSpan s = start_ - n;
					UIToolkit::registerTimerHandler( this, (EventHandler*)getCallback( "Animation::startAnimation" ), s.getTotalMilliseconds() );
				}
			}
		}


		double getDuration() {
			return duration_;
		}

		void setDuration( const double& val ) {
			if ( val != duration_ ) {
				duration_ = val;
			}
		}

		void stop() {
			UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::animationTimer" ) );
			UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::startAnimation" ) );

			AnimationEvent stopEvent(this);
			stopEvent.currentFrame = currentFrame_;
			AnimationFinished( &stopEvent );
		}

		void start() {
			UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::animationTimer" ) );
			UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::startAnimation" ) );

			start_ = DateTime::now();			
			
			UIToolkit::registerTimerHandler( this, (EventHandler*)getCallback( "Animation::startAnimation" ), 0 );
		}


		uint64 getCurrentFrame() {
			return currentFrame_;
		}

		uint64 getEstimatedEndFrame() {
			return estimatedEndFrame_;
		}

		Control* getTargetControl() {
			return targetControl_;
		}

		void setTargetControl( Control* val ) {
			targetControl_ = val;
		}
	protected:

		bool removeWhenFinished_;
		DateTime start_; //absolute time to start the animation
		double duration_; //duration of the animation in seconds
		double frameRate_; //frames/timer notifications per second

		uint32 repeatCount_;

		uint64 currentFrame_;
		uint64 estimatedEndFrame_;


		bool reverseWhenComplete_;
		bool endByFrame_;

		Control* targetControl_;

		virtual void processFrame() = 0;

		void startAnimation( TimerEvent* e ) {
			UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::startAnimation" ) );

			uint32 delay = 1000.0 / frameRate_;
			UIToolkit::registerTimerHandler( this, (EventHandler*)getCallback( "Animation::animationTimer" ), delay );

			currentFrame_ = 0;
			DateTime end = start_;
			end.incrMilliSecond( duration_ * 1000.0 );
			DateTimeSpan s = end - start_;
			estimatedEndFrame_ = currentFrame_ + s.getTotalMilliseconds() / delay;

			AnimationEvent tickEvent(this);
			tickEvent.currentFrame = currentFrame_;
			AnimationStarted( &tickEvent );
		}
	
		void animationTimer( TimerEvent* e ) {
			DateTime n = DateTime::now();
			DateTimeSpan s = n - start_;
			

			AnimationEvent tickEvent(this);
			tickEvent.currentFrame = currentFrame_;		

			processFrame();						

			AnimationFrame(&tickEvent);

			if ( NULL != targetControl_ ) {
				targetControl_->repaint();
			}

			if ( Animation::InfiniteDuration != duration_ ) {
				uint64 tmpDuration = duration_ * 1000.0;

				if ( (!endByFrame_ && (s.getTotalMilliseconds() > tmpDuration)) || (endByFrame_ && (currentFrame_ > estimatedEndFrame_)) ) {
					
					//we're done, notify and remove the timer
					UIToolkit::unregisterTimerHandler( (EventHandler*)getCallback( "Animation::animationTimer" ) );
					
					AnimationFinished( &tickEvent );
				}
			}

			currentFrame_ ++;
		}
		
	};


	const double Animation::InfiniteDuration = -1.0;


	class BasicAnimation : public Animation {
	public:
		BasicAnimation(): 
		  Animation(),
		  startVal_(VariantData::null()),
		  endVal_(VariantData::null()),
		  deltaVal_(VariantData::null()),
		  source_(NULL) ,
		  currentProperty_(NULL) {}
		


		VariantData getStartVal() {
			return startVal_;
		}

		void setStartVal( const VariantData& val ) {
			startVal_ = val;
		}

		VariantData getEndVal() {
			return endVal_;
		}

		void setEndVal( const VariantData& val ) {
			endVal_ = val;
		}

		VariantData getDeltaVal() {
			return deltaVal_;
		}

		void setDeltaVal( const VariantData& val ) {
			deltaVal_ = val;
		}

		Object* getSource() {
			return source_;
		}

		void setSource( Object* val ) {
			source_ = val;
		}

		String getPropertyPath() {
			return propertyPath_;
		}

		void setPropertyPath( const String& val ) {
			propertyPath_ = val;
		}
	protected:		

		VariantData startVal_;
		VariantData endVal_;
		VariantData deltaVal_;
		String propertyPath_;
		Object* source_;
		Property* currentProperty_;
		VariantData currentVal_;

		Property* getProperty() {

			Property* result = NULL;

			
			size_t pos = propertyPath_.find( "." );
			
			if( pos != String::npos ) {
				size_t lastPos = 0;
				Object* propSrc = source_;

				Application* app = Application::getRunningInstance();
				

				while ( pos != String::npos ) {
					String s = propertyPath_.substr( lastPos, pos-lastPos );
					Class* clazz = propSrc->getClass();
					if ( NULL == clazz ) {
						throw RuntimeException( "No class found, invalid property path: " + propertyPath_ );
					}

					Property* p = clazz->getProperty( s );
					if ( NULL == p ) {
						Component* component = app->findComponent( s, true );
						if ( NULL != component ) {
							propSrc = component;
						}
						else {
							throw RuntimeException( "No property or component found, invalid property path: " + propertyPath_ );
						}
					}
					else {
						propSrc = *p->get();
					}

					lastPos = pos + 1;
					pos = propertyPath_.find( ".", lastPos );
				}

				if ( NULL != propSrc ) {
					String s = propertyPath_.substr( lastPos, propertyPath_.size()-lastPos );
					Class* clazz = propSrc->getClass();
					if ( NULL == clazz ) {
						throw RuntimeException( "No class found, invalid property path: " + propertyPath_ );
					}
					
					Property* p = clazz->getProperty( s );
					if ( NULL == p ) {
						throw RuntimeException( "No property found, invalid property path: " + propertyPath_ );
					}
					result = clazz->getProperty( s );
				}				
			}
			else {
				Class* clazz = source_->getClass();

				result = clazz->getProperty( propertyPath_ );
			}

			return result;
		}

		virtual void processFrame() {
			if ( NULL == currentProperty_ ) {
				currentProperty_ = getProperty();
			}


			if ( 0 == currentFrame_ ) {				
				currentVal_ = startVal_;
				currentProperty_->set( &startVal_ );
			}
			else {

				if ( startVal_.isInteger() ) {
					uint32 v = currentVal_;
					uint32 d = deltaVal_;
					
					currentVal_ = (v + d);
				}
				else if ( startVal_.isReal() ) {
					double v = currentVal_;
					double d = deltaVal_;
					
					currentVal_ = (v + d);
				}

				currentProperty_->set( &currentVal_ );
			}
		}
	};


	template<typename OpType> 
	class BasicOpAnimation : public BasicAnimation {
	public:
		BasicOpAnimation( OpType op ) : BasicAnimation(), op_(op){}
	protected:
		OpType op_;

		virtual void processFrame() {
			if ( NULL == currentProperty_ ) {
				currentProperty_ = getProperty();
			}


			if ( 0 == currentFrame_ ) {				
				currentVal_ = startVal_;
				currentProperty_->set( &startVal_ );
			}
			else {

				currentVal_ = op_( currentVal_, currentFrame_ );

				currentProperty_->set( &currentVal_ );
			}
		}
	};
	
};


using namespace VCF;

struct SinOp {
	VariantData operator() ( const VariantData& v, const uint32& frame ) {
		VariantData result = sin( double(frame) / 33.0 );
		return result;
	}
};


class OGLView : public CustomControl {
public:


	OGLView(): CustomControl(true){

		hueAdj = NULL;
		//setDoubleBuffered( false );
/*
		BasicOpAnimation<SinOp>* sinAnim = new BasicOpAnimation<SinOp>(SinOp());
		sinAnim->setDuration( 30 );
		sinAnim->setSource( this );
		sinAnim->setStartVal( 0.0 );

		sinAnim->setPropertyPath( "color.red" );
		
		sinAnim->setTargetControl( this );

		sinAnim->start();
		addComponent( sinAnim );



		sinAnim = new BasicOpAnimation<SinOp>(SinOp());
		sinAnim->setDuration( 30 );
		sinAnim->setSource( this );
		sinAnim->setStartVal( 1.0 );

		sinAnim->setPropertyPath( "color.blue" );
		
		sinAnim->setTargetControl( this );

		sinAnim->start();
		addComponent( sinAnim );


		BasicAnimation* a;// = new BasicAnimation();
		


		a = new BasicAnimation();
		
		a->setDuration( Animation::InfiniteDuration );
		a->setSource( this );
		a->setStartVal( 0.0 );
		a->setDeltaVal( 5.0 );

		a->setPropertyPath( "angle" );
		
		a->setTargetControl( this );

		a->start();
		addComponent( a );

*/
		

		angle_ = 0;
	}

	double getAngle() {
		return angle_;
	}

	void setAngle( const double& val ) {		
		angle_ = val;
		repaint();		
	}

	double angle_;
	IKImage img;
	HueAdjust* hueAdj;
	Brighten* bright;
	Mixer* mix;
	GaussianBlur* blur;

	IKFilter* tmp;

	IKImage img2;

	void doGL()
	{
		static initialized = false;

		Rect r = getClientBounds();

		IKImageContext ic(this);

		
		if ( !initialized ) {


			initialized = true;

			img.initFromFile( "res:logo.png" );
			img2.initFromFile( "C:\\Documents and Settings\\jcrafton\\Desktop\\1.jpg" );


			hueAdj = new HueAdjust();

			bright = new Brighten();

			//mix = new Mixer();

			tmp = new IKFilter();
			tmp->initFromResource( "test" );

			blur = new GaussianBlur();

/*

			BasicAnimation* a = new BasicAnimation();
			a->setDuration( 5 );
			a->setSource( hueAdj );
			a->setStartVal( 0.0 );
			a->setDeltaVal( 0.5 );			
			a->setPropertyPath( "hueVal" );			
			a->setTargetControl( this );
			
			a->start();
			addComponent( a );*/

		}

		initialized = true;


		ic.initView( r.getWidth(), r.getHeight() );

		ic.clear( getColor() );
		
		
		ic.multiTransformMatrix( Matrix2D::rotation(angle_) * Matrix2D::scaling(1.3,1.3) );
		
		ic.draw( 10, 10, &img );


		ic.setTransformMatrix( Matrix2D::translation( 50, 100 ) );
		ic.setOpacity( sin( 0.1250 * (angle_/6.28) ) );
		ic.draw( 10, 10, &img );

		ic.setTransformMatrix( Matrix2D() );
		ic.draw( 30, 210, &img );
		ic.draw( 130, 310, &img );

		ic.multiTransformMatrix( Matrix2D::rotation(angle_) );
		ic.draw( 10, 210, &img );
		ic.draw( 231, 410, &img );
		

		//hueAdj->setInputImage( &img );
		//hueAdj->setHueVal( 1.5 );

		//bright->setInputImage( hueAdj->getOutputImage() );
		//bright->setBrightness( 0.5 );

		//mix->setInputImage( &img );
		//mix->setInput2Image( &img2 );

		double y = 10;
		blur->setInputImage( &img2 );
		blur->blurAmount = 2;//.0050;
		ic.setTransformMatrix( Matrix2D() );
		ic.setOpacity( 1.0 );		
		ic.draw( 300, y, blur->getOutputImage() );


		ic.draw( 300, y + img2.getSize().height + 10, &img2 );
	}


	virtual void paint(GraphicsContext * context) {
		doGL();
	}
};



_class_rtti_(OGLView, "VCF::CustomControl", "OGLView")
_property_( double, "angle", getAngle, setAngle, "" );
_class_rtti_end_


class OGLDrawWindow : public Window {
public:
	OGLDrawWindow() {
		setCaption( "OGLDraw" );		

		OGLView* view = new OGLView();
		add( view, AlignClient );
	}

	virtual ~OGLDrawWindow(){};

};




class OGLDrawApplication : public Application {
public:

	OGLDrawApplication( int argc, char** argv ) : Application(argc, argv) {
		
		OpenGLKit::init(argc,argv);
		ImageKit::init(argc,argv);
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		

		
		REGISTER_CLASSINFO_EXTERNAL(OGLView);

		Window* mainWindow = new OGLDrawWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 700.0, 500.0 );
		mainWindow->show();
		
		return result;
	}

	virtual void terminateRunningApplication() {
		ImageKit::terminate();
		Application::terminateRunningApplication();
	}
};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<OGLDrawApplication>(argc,argv);
}


