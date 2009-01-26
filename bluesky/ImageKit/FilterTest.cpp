//FilterTest.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ScintillaKit/ScintillaKit.h"
#include "vcf/ApplicationKit/StatusBar.h"
#include "vcf/ApplicationKit/ListModel.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/Label.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/ApplicationKit/TextPeer.h"

#include "ImageKit.h"



using namespace VCF;




class RangeEdit : public Label {
public:

	enum HitState {
		hsNone = 0,
		hsIncHilited,
		hsDecHilited,
		hsIncPressed,
		hsDecPressed,
	};
	
	RangeEdit() : Label(), 
		fractionalDelta_(0.10),
		buttonState_(0), 
		minValue_(VariantData::null()), 
		maxValue_(VariantData::null()),
		editor_(NULL) {

		incStr = L"+";
		decStr = L"-";

		
		addCallback( new ClassProcedure<RangeEdit>(this, &RangeEdit::editorLostFocus), "RangeEdit::editorLostFocus" );
		addCallback( new ClassProcedure1<Event*,RangeEdit>(this, &RangeEdit::endEditing), "RangeEdit::endEditing" );		
		addCallback( new ClassProcedure1<KeyboardEvent*,RangeEdit>(this, &RangeEdit::onEditorKeyPressed), "RangeEdit::onEditorKeyPressed" );
		
	}

	void increment() {
		if ( value_.isReal() ) {
			double v = value_;
			v += (double)deltaVal_;
			setValue( v );
		}
		else if ( value_.isInteger() ) {
			int v = value_;
			v += (int)deltaVal_;
			setValue( v );
		}
	}

	void decrement() {
		if ( value_.isReal() ) {
			double v = value_;
			v -= (double)deltaVal_;
			setValue( v );
		}
		else if ( value_.isInteger() ) {
			int v = value_;
			v -= (int)deltaVal_;
			setValue( v );
		}
	}


	void smallIncrement() {
			if ( value_.isReal() ) {
			double v = value_;
			v += ((double)deltaVal_) * fractionalDelta_;
			setValue( v );
		}
		else if ( value_.isInteger() ) {
			int v = value_;
			v += (int)((double)deltaVal_ * fractionalDelta_);
			setValue( v );
		}
	}

	void smallDecrement() {
		if ( value_.isReal() ) {
			double v = value_;
			v -= ((double)deltaVal_) * fractionalDelta_;
			setValue( v );
		}
		else if ( value_.isInteger() ) {
			int v = value_;
			v -= (int)((double)deltaVal_ * fractionalDelta_);
			setValue( v );
		}
	}

	void setValue( const VariantData& v ) {
		Model* model  = getViewModel();
		if ( NULL != model ) {
			model->setValue( v, getModelKey() );
		}
		else {
			VariantData v2 = v;

			if ( !value_.isUndefined() ) {
				v2 = v.convertToType(value_.type);
			}

			if ( !minValue_.isNull() && !maxValue_.isNull() ) {
				value_ = minVal<>( maxValue_, maxVal<>( minValue_, v2 ) );
			}
			else if ( !minValue_.isNull() && maxValue_.isNull() ) {
				value_ = maxVal<>( minValue_, v2 );
			}
			else if ( minValue_.isNull() && !maxValue_.isNull() ) {
				value_ = minVal<>( maxValue_, v2 );
			}
			else {
				value_ = v2;
			}
		}
	}

	VariantData getValue() {
		Model* model  = getViewModel();
		if ( NULL != model ) {
			return model->getValue( getModelKey() );
		}
		
		return value_;
	}

	void setDelta( const VariantData& v ) {
		deltaVal_ = v;
	}

	VariantData getDelta() {		
		return deltaVal_;
	}

	void setFractionalDelta( const double& v ) {
		fractionalDelta_ = v;
	}

	double getFractionalDelta() {		
		return fractionalDelta_;
	}


	void setMinVal( const VariantData& v ) {
		minValue_ = v;
	}

	VariantData getMinVal() {
		return minValue_;
	}

	void setMaxVal( const VariantData& v ) {
		maxValue_ = v;
	}

	VariantData getMaxVal() {
		return maxValue_;
	}

	virtual void paint( GraphicsContext* context ) {
		CustomControl::paint( context );

		context->setCurrentFont( getFont() );
		

		double y = 0.0;
		double x = 0.0;
		
		String caption;
		if ( getUseLocaleStrings() ) {
			caption = System::getCurrentThreadLocale()->translate( "" );
		}
		else {
			caption = "";
		}
		
		if ( !caption.empty() ) {
			caption += L" : ";
		}


		Model* model  = getViewModel();
		if ( NULL != model ) {
			caption += model->getValueAsString( getModelKey() );
		}
		else {
			caption += value_.toString();
		}
		
		
		
		int32 drawOptions = GraphicsContext::tdoCenterHorzAlign | GraphicsContext::tdoCenterVertAlign;
		Rect bounds = getClientBounds();		

		Rect tmp = bounds;
		tmp.right_ = tmp.left_ + context->getTextWidth( decStr );

		if ( buttonState_ == hsDecHilited ) {
			Color c = *context->getColor();
			double h,s,l;
			c.getHSL(h,l,s);
			l = minVal( 1.0, maxVal( 0.0, l * 1.05 ) );
			c.setHSL(h,l,s);
			context->setColor(&c);

			context->rectangle( &tmp );
			context->fillPath();

			context->textBoundedBy( &tmp, decStr, drawOptions );
		}
		else if ( buttonState_ == hsDecPressed ) {
			//context->setColor(  );

			context->rectangle( &tmp );
			context->fillPath();

			context->textBoundedBy( &tmp, decStr, drawOptions );
		}
		else {
			context->textBoundedBy( &tmp, decStr, drawOptions );
		}

		

		tmp = bounds;
		tmp.left_ = tmp.right_ - context->getTextWidth( incStr );
		if ( buttonState_ == hsIncHilited ) {
			Color c = *context->getColor();
			double h,s,l;
			c.getHSL(h,l,s);
			l = minVal( 1.0, maxVal( 0.0, l * 1.05 ) );
			c.setHSL(h,l,s);
			context->setColor(&c);

			context->rectangle( &tmp );
			context->fillPath();

			context->textBoundedBy( &tmp, incStr, drawOptions );
		}
		else if ( buttonState_ == hsIncPressed ) {

		}
		else {
			context->textBoundedBy( &tmp, incStr, drawOptions );
		}

		bounds.left_ += context->getTextWidth( decStr );
		bounds.right_ -= context->getTextWidth( incStr );

		//x = VCF::maxVal<double>( 1.0, (bounds.getWidth()/2.0) - (context->getTextWidth( caption ) / 2.0) );		
		//y = (bounds.getHeight()/2.0) - (context->getTextHeight(caption)/2.0);


		context->textBoundedBy( &bounds, caption, drawOptions );
	}


	virtual void mouseLeave( MouseEvent* e ) {
		buttonState_ = hsNone;
		repaint();
	}

	virtual void mouseDown( MouseEvent* e ) {		
		if ( e->hasLeftButton() ) {
			lastPt_ = *e->getPoint();
			keepMouseEvents();
		}
	}

	virtual void mouseMove( MouseEvent* e ) {
		Rect r = getIncRect();
		if ( r.containsPt( e->getPoint() ) ) {
			buttonState_ = hsIncHilited;

			if ( e->hasLeftButton() ) {
				buttonState_ = hsIncPressed;
			}
			repaint();
		}
		else if ( getDecRect().containsPt( e->getPoint() ) ) {
			buttonState_ = hsDecHilited;

			if ( e->hasLeftButton() ) {
				buttonState_ = hsDecPressed;
			}
			repaint();
		}
		else {

			if ( e->hasLeftButton() ) {

				int d = e->getPoint()->x_ - lastPt_.x_;
				
				if ( d < 0 ) {
					smallDecrement();
				}
				else if ( d > 0 ){
					smallIncrement();
				}

				lastPt_ = *e->getPoint();
			}


			buttonState_ = hsNone;
			repaint();
		}
	}

	virtual void mouseUp( MouseEvent* e ) {		
		if ( e->hasLeftButton() ) {

			if ( e->hasShiftKey() ) {
				edit();
			}
			else {
				Rect r = getIncRect();
				if ( r.containsPt( e->getPoint() ) ) {
					increment();
				}
				else if ( getDecRect().containsPt( e->getPoint() ) ) {
					decrement();
				}
			}
		}

		releaseMouseEvents();
		buttonState_ = hsNone;
		repaint();
	}

	Rect getIncRect() {
		Rect result = getClientBounds();
		result.left_ = result.right_ - getFont()->getTextWidth( incStr );
		return result;
	}

	Rect getDecRect() {
		Rect result = getClientBounds();
		result.right_ = result.left_ + getFont()->getTextWidth( decStr );
		return result;
	}

	Rect getEditRect() {
		Rect r1 = getDecRect();
		Rect r2 = getIncRect();
		Rect result;
		result = getClientBounds();
		result.left_ = r1.right_;
		result.right_ = r2.left_;
		return result;
	}

	void edit() {

		Container* container = getContainer();
		if ( NULL == container ) {
			container = new StandardContainer();
			setContainer( container );
		}

		if ( NULL == editor_ ) {			
			editor_ = new TextControl();
			
			editor_->setBorder( NULL );
			Rect editRect = getEditRect();
			editor_->setBounds( &editRect );

			String s = value_;

			editor_->getModel()->setValue( s );

			Dictionary styles;
			styles[ Text::psAlignment ] = Text::paCenter;
			editor_->setDefaultStyle( styles );

			
			
			container->add( editor_ );
			editor_->FocusLost += getCallback("RangeEdit::editorLostFocus");
			editor_->KeyPressed += getCallback("RangeEdit::onEditorKeyPressed");
			
			editor_->setFocused();
			editor_->selectAll();
		}
	}

	void endEdit( bool applyEditValue=true ) {

		if ( applyEditValue ) {
			VariantData v = editor_->getModel()->getValue();

			setValue( v );
		}

		editor_->FocusLost -= getCallback("RangeEdit::editorLostFocus");
		editor_->KeyPressed -= getCallback("RangeEdit::onEditorKeyPressed");
		UIToolkit::postEvent( (EventHandler*)getCallback("RangeEdit::endEditing"), NULL, false );
	}
protected:
	VariantData value_;
	VariantData deltaVal_;

	TextControl* editor_;

	VariantData minValue_;
	VariantData maxValue_;

	double fractionalDelta_;
	String incStr;
	String decStr;
	int buttonState_;
	Point lastPt_;

	void editorLostFocus() {
		endEdit();
	}

	void endEditing(Event*) {
		if ( NULL == editor_ ) {
			return;
		}

		Container* container = getContainer();
		if ( NULL != container ) {
			container->remove( editor_ );
			editor_->getOwner()->removeComponent( editor_ );
			editor_->free();
		}
		editor_ = NULL;
		repaint();
	}

	void onEditorKeyPressed( KeyboardEvent* e ) {
		if ( vkEscape == e->virtualKeyCode ) {
			endEdit(false);
		}
		else if ( vkEnter == e->virtualKeyCode ) {
			endEdit(true);
		}
	}
};


_class_rtti_(RangeEdit, "VCF::Label", "RangeEdit")
_property_( VariantData, "value", getValue, setValue, "" );
_property_( VariantData, "min", getMinVal, setMinVal, "" );
_property_( VariantData, "max", getMaxVal, setMaxVal, "" );
_property_( VariantData, "delta", getDelta, setDelta, "" );
_property_( double, "fractionalDelta", getFractionalDelta, setFractionalDelta, "" );
_class_rtti_end_



class ImageView : public CustomControl {
public:

	ImageView(): CustomControl(),filter(NULL),useFilterImage(false) {
		addCallback( new ClassProcedure<ImageView>(this, &ImageView::openImage), "ImageView::openImage" );
		addCallback( new ClassProcedure<ImageView>(this, &ImageView::compileFilter), "ImageView::compileFilter" );
		addCallback( new ClassProcedure<ImageView>(this, &ImageView::saveImage), "ImageView::saveImage" );
		addCallback( new ClassProcedure<ImageView>(this, &ImageView::resetImage), "ImageView::resetImage" );
		
	}

	virtual ~ImageView(){ 
		delete filter;
	}

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
			lastPt = *e->getPoint();
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

			double dx = lastPt.x_ - center.x_;
			double dy = lastPt.y_ - center.y_;
			double prevAngle = (atan2( dx, dy ) * 180.0/M_PI) * -1.0;

			dx = p.x_ - center.x_;
			dy = p.y_ - center.y_;
			currentAngle += ((atan2( dx, dy ) * 180.0/M_PI) * -1.0) - prevAngle;

			lastPt = *e->getPoint();

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


	
	void resetImage() {
		resetXfrms();
		useFilterImage = false;
		repaint();
	}

	void compileFilter() {
		Control* shaderEdit = (Control*)Application::getRunningInstance()->findComponent( "shaderEdit", true );
		Control* shaderErrors = (Control*)Application::getRunningInstance()->findComponent( "shaderErrors", true );
		Control* splitter = (Control*)Application::getRunningInstance()->findComponent( "splitter2", true );

		shaderErrors->setVisible(false);
		splitter->setVisible(false);

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
			splitter->setVisible(true);
			
			shaderErrors->getModel()->setValueAsString( filter->getCompileStatus() );
			useFilterImage = false;
			repaint();
		}
	}

	

	void saveImage() {
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

	void openImage() {
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

		addCallback( new ClassProcedure<FilterTest>(this, &FilterTest::saveFilterAs), "FilterTest::saveFilterAs" );
		addCallback( new ClassProcedure<FilterTest>(this, &FilterTest::openFilter), "FilterTest::openFilter" );		
		addCallback( new ClassProcedure1<Event*,FilterTest>(this, &FilterTest::viewEditor), "FilterTest::viewEditor" );		
		addCallback( new ClassProcedure1<Event*,FilterTest>(this, &FilterTest::viewStatus), "FilterTest::viewStatus" );		
		addCallback( new ClassProcedure1<Event*,FilterTest>(this, &FilterTest::changeFilter), "FilterTest::changeFilter" );	
	}


	void changeFilter(Event* e) {
		ListViewControl* lv = (ListViewControl*) e->getSource();
		ListModel* lm = lv->getListModel();
		String s = lm->get( lv->getSelectedItem() );

		Class* clazz = ClassRegistry::getClassWithAttrValue( classid(IKFilter), IKFilter::DisplayNameAttr, s );
		if ( NULL != clazz ) {
			Object* o = clazz->createInstance();
		}
	}

	void viewEditor( Event* e ) {
		Control* editPanel = (Control*)Application::getRunningInstance()->findComponent( "editPanel", true );
		editPanel->setVisible( !editPanel->getVisible() );
		Control* splitter = (Control*)Application::getRunningInstance()->findComponent( "splitter", true );
		splitter->setVisible( !splitter->getVisible() );

		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( editPanel->getVisible() );
	}

	void viewStatus( Event* e ) {
		Control* status = (Control*)Application::getRunningInstance()->findComponent( "status", true );
		status->setVisible( !status->getVisible() );
		


		MenuItem* item = (MenuItem*)e->getSource();
		item->setChecked( status->getVisible() );
	}

	void saveFilterAs() {
		CommonFileSaveDialog dlg( getMainWindow() );
		dlg.addFilter( "ImageKit Filter (*.shader)", "*.shader" );
		if ( dlg.execute() ) {
			Control* shaderEdit = (Control*)findComponent( "shaderEdit", true );

			FileOutputStream fos(dlg.getFileName());
			AnsiString s = shaderEdit->getModel()->getValueAsString();
			fos.write( (const uchar*)s.c_str(), s.length() );
		}
	}

	void openFilter() {
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
		REGISTER_CLASSINFO_EXTERNAL(RangeEdit);
		
		

		Window* mainWindow = Frame::createWindow( classid(FilterTestWindow) );
		setMainWindow(mainWindow);
		Control* shaderEdit = (Control*)Application::getRunningInstance()->findComponent( "shaderEdit", true );

		Resource* res = this->getResourceBundle()->getResource( "default.shader" );

		String defaultText( (const char*)res->getData(), res->getDataSize() );
		delete res;

		shaderEdit->getModel()->setValueAsString( defaultText );


		Control* filterList = (Control*)Application::getRunningInstance()->findComponent( "filtersList", true );
		ListModel* lm = (ListModel*)filterList->getModel();
		FilterCategories categories = IKFilter::getCategories();
		for ( FilterCategories::iterator i=categories.begin();i!=categories.end();i++ ) {
			const String& category = *i;
			Array<String> filterNames = IKFilter::getFiltersForCategory( category );

			for ( Array<String>::iterator j=filterNames.begin();j!=filterNames.end();j++ ) {
				const String& filter = *j;
				lm->add( IKFilter::getFilterDisplayName(filter) );
			}
		}


		mainWindow->initializeSettings(true);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<FilterTest>(argc,argv);
}


