//ImageKit.cpp

#include "ImageKit.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/OpenGLKit/OpenGLToolkit.h"

using namespace VCF;


_class_rtti_(IKFilter, "VCF::Object", "IKFilter")
_class_rtti_end_



_class_rtti_(HueAdjust, "VCF::IKFilter", "HueAdjust")
_property_( double, "hueVal", getHueVal, setHueVal, "" );
_class_rtti_end_




_class_rtti_(Brighten, "VCF::IKFilter", "Brighten")
_property_( double, "brightness", getBrightness, setBrightness, "" );
_class_rtti_end_




_class_rtti_(Mixer, "VCF::IKFilter", "Mixer")
_property_object_( IKImage, "input2Image", getInput2Image, setInput2Image, "" );
_class_rtti_end_

_class_rtti_(GaussianBlur, "VCF::IKFilter", "GaussianBlur")
_class_rtti_end_




class GLMatrix {
public:

	GLMatrix(){
		ident();
	}

	GLMatrix& operator=( const Matrix2D& rhs ) {
		ident();

		mat[0] = rhs[Matrix2D::mei00];
		mat[1] = rhs[Matrix2D::mei01];
		mat[2] = 0.0;//z ignored
		mat[3] = rhs[Matrix2D::mei02];

		mat[4] = rhs[Matrix2D::mei10];
		mat[5] = rhs[Matrix2D::mei11];
		mat[6] = 0.0;//z ignored
		mat[7] = rhs[Matrix2D::mei12];

		mat[8] = 0.0;
		mat[9] = 0.0;
		mat[10] = 1.0;//z ignored
		mat[11] = 0.0;

		mat[12] = rhs[Matrix2D::mei20];
		mat[13] = rhs[Matrix2D::mei21];
		mat[14] = 0.0;//z ignored
		mat[15] = rhs[Matrix2D::mei22];

		return *this;
	}

	operator double* () {
		return &mat[0];
	}

	operator const double* () const {
		return &mat[0];
	}

	double mat[16];

	void ident() {
		mat[0] = 1.0;
		mat[1] = 0.0;
		mat[2] = 0.0;
		mat[3] = 0.0;
		mat[4] = 0.0;
		mat[5] = 1.0;
		mat[6] = 0.0;
		mat[7] = 0.0;
		mat[8] = 1.0;
		mat[9] = 0.0;
		mat[10] = 0.0;
		mat[11] = 1.0;
		mat[12] = 0.0;
		mat[13] = 0.0;
		mat[14] = 0.0;
		mat[15] = 1.0;
	}
};




ImageKit* ImageKit::instance = NULL;

ImageKit::ImageKit()
{
	
}

ImageKit::~ImageKit()
{
	
}



class GLInit {
public:
#ifdef WIN32
	WNDCLASSEXW wcex;
	HWND hwnd;
	HDC dc;
	HGLRC hrc;
#endif


	GLInit(){

#ifdef WIN32
	//init glew	
	wcex.cbSize = sizeof(wcex);
	
	wcex.style			= 0;
	wcex.lpfnWndProc	= (WNDPROC)DefWindowProcW;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= ::GetModuleHandleW(NULL);
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground	= 0;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"ImageKit";
	wcex.hIconSm		= NULL;
	
	RegisterClassExW(&wcex);
	
	hwnd = ::CreateWindowExW( 0,
		wcex.lpszClassName,
		NULL,
		WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0,
		0,
		1,
		1,
		NULL,
		NULL, wcex.hInstance, NULL );
	
	dc = ::GetDC( hwnd );
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
			1,                              // version number
			PFD_DRAW_TO_WINDOW |            // support window
			PFD_SUPPORT_OPENGL |          // support OpenGL
			PFD_DOUBLEBUFFER,             // double buffered
			PFD_TYPE_RGBA,                  // RGBA type
			24,                             // 24-bit color depth
			0, 0, 0, 0, 0, 0,               // color bits ignored
			0,                              // no alpha buffer
			0,                              // shift bit ignored
			0,                              // no accumulation buffer
			0, 0, 0, 0,                     // accum bits ignored
			32,                             // 32-bit z-buffer
			0,                              // no stencil buffer
			0,                              // no auxiliary buffer
			PFD_MAIN_PLANE,                 // main layer
			0,                              // reserved
			0, 0, 0                         // layer masks ignored
	};
	
	int pixelformat = ChoosePixelFormat( dc, &pfd );
	::SetPixelFormat( dc, pixelformat, &pfd );
	hrc = wglCreateContext( dc );
	wglMakeCurrent( dc, hrc );
#endif

	}

	~GLInit() {
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( hrc );

		ReleaseDC( hwnd, dc );
		DestroyWindow(hwnd);
		UnregisterClassW(wcex.lpszClassName, wcex.hInstance);
	}
};


_filter_rtti_( Brighten )
	_filter_category_("Image Processing")
	_filter_prop_attr_(0.0, 1.0, 0.5, "brightness","brightness")
_filter_rtti_end_


void ImageKit::init( int argc, char** argv )
{
	ImageKit::instance = new ImageKit();

	{
		GLInit g;		
		//init glew		
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			Dialog::showMessage( String("Error: ") + (const char*)glewGetString(err) ); 
		}		
	}

	REGISTER_CLASSINFO_EXTERNAL(IKFilter);
	REGISTER_CLASSINFO_EXTERNAL(HueAdjust);

	REGISTER_CLASSINFO_EXTERNAL(Brighten);
	REGISTER_CLASSINFO_EXTERNAL(Mixer);
	REGISTER_CLASSINFO_EXTERNAL(GaussianBlur);
	
	REGISTER_IKFILTER( Brighten );
}

void ImageKit::terminate()
{
	delete ImageKit::instance;
}


GLuint ImageKit::defaultFrameBufferObj = 0;

void ImageKit::initDefaultFBO()
{	
	if ( 0 == ImageKit::defaultFrameBufferObj ) {
		glGenFramebuffersEXT( 1, &ImageKit::defaultFrameBufferObj );	
		if ( 0 == ImageKit::defaultFrameBufferObj ) {
			throw RuntimeException( L"Invalid FBO instance - unable to generate a new instance." );
		}
	}
}

void ImageKit::destroyDefaultFBO()
{
	if ( 0 != ImageKit::defaultFrameBufferObj ) {
		glDeleteFramebuffersEXT( 1, &ImageKit::defaultFrameBufferObj );
	}
}








std::map<uint32,Dimensions> IKImage::texDimensionsMap;



IKImage::IKImage():Object(),imageHandle_(IKImage::NullHandle),filter_(NULL)
{

}

IKImage::IKImage( Image* image )
	:Object(),imageHandle_(IKImage::NullHandle),filter_(NULL)
{

}

IKImage::IKImage( const Dimensions& dimensions )
	:Object(),imageHandle_(IKImage::NullHandle),filter_(NULL)
{
	initFromDimensions(dimensions);
}

IKImage::IKImage( const uchar* data, const size_t& size, const MIMEType& type  )
	:Object(),imageHandle_(IKImage::NullHandle),filter_(NULL)
{

}

IKImage::IKImage( const uchar* data, const size_t& size )
:Object(),imageHandle_(IKImage::NullHandle),filter_(NULL)
{

}

IKImage::IKImage( const uchar* data, const Dimensions& dimensions )
:Object(),imageHandle_(IKImage::NullHandle),filter_(NULL)
{

}

IKImage::IKImage( const String& fileName )
:Object(),imageHandle_(IKImage::NullHandle),filter_(NULL)
{

}

IKImage::~IKImage()
{
	destroyTexture();
}

void IKImage::initFromImage( Image* image )
{
	Size sz;
	sz.width_ = image->getWidth();
	sz.height_ = image->getHeight();

	initFromDimensions( sz );
	glTexImage2D(GL_TEXTURE_2D, 0, 
				image->getType() , 
				image->getWidth(), 
				image->getHeight(), 
				0, 
				image->getType() == Image::itColor ? GL_BGRA_EXT : GL_LUMINANCE, 
				GL_UNSIGNED_BYTE, 
				image->getData() );
	
}

void IKImage::initFromDimensions( const Dimensions& dimensions )
{
	if ( imageHandle_ != IKImage::NullHandle ) {
		glDeleteTextures( 1, &imageHandle_ );
	}

	glGenTextures( 1, &imageHandle_ );

	glBindTexture(GL_TEXTURE_2D, imageHandle_);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use nice (linear) scaling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Use nice (linear) scaling

	size_ = dimensions;
	IKImage::texDimensionsMap[imageHandle_] = size_;


	glTexImage2D(GL_TEXTURE_2D, 0, 
				Image::itColor , 
				size_.width, 
				size_.height, 
				0, 
				GL_BGRA_EXT, 
				GL_UNSIGNED_BYTE, 
				NULL );
}

void IKImage::setHandle( const uint32& val )
{
	if ( imageHandle_ != val ) {
		imageHandle_ = val;
		
		std::map<uint32,Dimensions>::iterator found = IKImage::texDimensionsMap.find(imageHandle_);
		if ( found != IKImage::texDimensionsMap.end() ) {
			size_ = found->second;
		}
	}
}

void IKImage::initFromData( const uchar* data, const size_t& size, const MIMEType& type )
{

}

void IKImage::initFromData( const uchar* data, const size_t& size )
{

}

void IKImage::initFromBits( const uchar* data, const Dimensions& dimensions )
{

}

void IKImage::initFromFile( const String& fileName )
{
	Image* img = GraphicsToolkit::createImage( fileName );
	if ( NULL != img ) {
		initFromImage( img );
		delete img;
	}
}

void IKImage::bind() 
{	
	glBindTexture(GL_TEXTURE_2D, imageHandle_);
}

void IKImage::destroyTexture()
{
	if ( imageHandle_ != IKImage::NullHandle ) {

		std::map<uint32,Dimensions>::iterator found = IKImage::texDimensionsMap.find(imageHandle_);
		if ( found != IKImage::texDimensionsMap.end() ) {
			IKImage::texDimensionsMap.erase( found );
		}

		glDeleteTextures( 1, &imageHandle_ );

		imageHandle_ = IKImage::NullHandle;
	}
}



void IKImage::render( const double& x, const double& y )
{
	double u=1.0;
	double v=1.0;	

	glBegin(GL_POLYGON);	
	
		glTexCoord2f(0.0, 0.0);
		glVertex2i(x, y);
		
		glTexCoord2f(u, 0.0);
		glVertex2i(x+size_.width, y);
		
		glTexCoord2f(u, v);
		glVertex2i(x+size_.width, y+size_.height);
		
		glTexCoord2f(0.0, v);
		glVertex2i(x, y+size_.height);	
	
	glEnd();
}

void IKImage::renderToFBO( int fbo )
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo );
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, size_.width, 0, size_.height, -1, 1);
	glViewport(0,0,size_.width, size_.height);

	bind();

	render(0,0);
}

void IKImage::renderToImage( Image* image )
{
	IKImage tmpImg(size_);

	int tmpFBO = 0;
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ImageKit::getDefaultFBO() );

	tmpImg.bind();
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tmpImg.getHandle(), 0);

	renderToFBO( ImageKit::getDefaultFBO() );

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0 );


	bind();

	//glTexImage2D(GL_TEXTURE_2D, 0, 
	//			Image::itColor , 
	//			size_.width, 
	//			size_.height, 
	//			0, 
	//			GL_BGRA_EXT, 
	//			GL_UNSIGNED_BYTE, 
	//			NULL );


	glGetTexImage( GL_TEXTURE_2D, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->getData() );
}







std::map<Control*,OpenGLPeer*> IKImageContext::glPeerMap;


void IKImageContext::controlDestroyed(ComponentEvent* e)
{
	std::map<Control*,OpenGLPeer*>::iterator found = IKImageContext::glPeerMap.find( (Control*)e->getSource() );
	if ( found != IKImageContext::glPeerMap.end() ) {
		OpenGLPeer* peer = found->second;
		delete peer;
		IKImageContext::glPeerMap.erase( found );
	}	
}





IKImageContext::IKImageContext():
	opacity_(1.0),
		glPeer_(NULL)
{
	ImageKit::initDefaultFBO();
}

IKImageContext::IKImageContext( Control* control ):
	opacity_(1.0),
		glPeer_(NULL)
{

	std::map<Control*,OpenGLPeer*>::iterator found = IKImageContext::glPeerMap.find( control );
	if ( found == IKImageContext::glPeerMap.end() ) {

		control->setDoubleBuffered( false );

		control->ComponentDestroyed += IKImageContext::controlDestroyed;

		glPeer_ = OpenGLToolkit::createOpenGLPeer( NULL );

		glPeer_->initGL( control );
		IKImageContext::glPeerMap[control] = glPeer_;
	}
	else {
		glPeer_ = found->second;
		if ( control->isDoubleBuffered() ) {
			control->setDoubleBuffered( false );
		}
	}

	glPeer_->makeCurrent();
	
	ImageKit::initDefaultFBO();
}

IKImageContext::~IKImageContext()
{
	if ( NULL != glPeer_ ) {
		glPeer_->swapBuffers();
	}
}

void IKImageContext::clear( Color* color )
{
	glClearColor( color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha() );
	glClear(GL_COLOR_BUFFER_BIT);	
}

void IKImageContext::initView( const double width, const double& height )
{
	viewSize.width_ = width;
	viewSize.height_ = height;


	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, viewSize.width_, viewSize.height_, 0, -1, 1);
	glViewport( 0, 0, viewSize.width_, viewSize.height_ );
	
	glDisable(GL_DEPTH_TEST);		

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		
}



void IKImageContext::draw( const double& x, const double& y, IKImage* image )
{
	Dimensions imgSz = image->getSize();
	double u=1.0;
	double v=1.0;

	IKFilter* filter = image->getFilter();
	if ( filter ) {

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, ImageKit::getDefaultFBO() );
		
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, imgSz.width, 0, imgSz.height, -1, 1);
		glViewport(0,0,imgSz.width, imgSz.height);
		glEnable(GL_BLEND);
	
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		

	
		std::vector<IKImage*> images;
		std::vector<IKFilter*> filters;


		while ( NULL != filter ) {
			IKImage* inImage = filter->getInputImage();
			if ( NULL == inImage ) {
				break;
			}
			images.insert( images.begin(), inImage );
			filters.insert( filters.begin(), filter );

			filter = inImage->getFilter();
		}


		std::vector<IKImage*>::iterator imgIt = images.begin();
		std::vector<IKFilter*>::iterator filterIt = filters.begin();
		while (imgIt != images.end()) {

			IKImage* img = *imgIt;			

			filter = *filterIt;

			

			IKImage* outImg = filter->getOutputImage();

			outImg->bind();

			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, outImg->getHandle(), 0);


			filter->apply();

			glColor4f(1.0, 1.0, 1.0, opacity_);
		

			outImg->render( 0, 0 );

			glUseProgramObjectARB(0);

			++imgIt;
			++filterIt;
		}

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);


		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, viewSize.width_, viewSize.height_, 0, -1, 1);
		glViewport(0,0,viewSize.width_, viewSize.height_);


		filter = filters.back();
		IKImage* outImg = filter->getOutputImage();	

		glPushMatrix();
		
		GLMatrix m;
		m = xfrm_;
		glMultMatrixd( m );		
		
		glColor4f(1.0, 1.0, 1.0, opacity_);
		outImg->bind();
		outImg->render( x, y );
		
		glPopMatrix();
	}
	else {		
		Size sz = image->getSize();
		glPushMatrix();
		
		GLMatrix m;
		m = xfrm_;
		glMultMatrixd( m );
		
		glColor4f(1.0, 1.0, 1.0, opacity_);

		image->bind();
		image->render(x,y);		
		
		glPopMatrix();

	}


	

	

/*
	glDisable (GL_LINE_SMOOTH);
	glDisable (GL_POLYGON_SMOOTH );
	*/
}


IKFilter::FilterMap IKFilter::registeredFilters;


IKFilter::IKFilter():
	inputImage_(NULL),
	outputImage_(NULL)
{

}

IKFilter::~IKFilter()
{
	delete outputImage_;
}

FilterPropertyAttributes IKFilter::getFilterAttributes( IKFilter* filter )
{
	return IKFilter::getFilterAttributes( filter->getClassName() );
}

FilterCategories IKFilter::getFilterCategories( IKFilter* filter )
{
	return IKFilter::getFilterCategories( filter->getClassName() );
}

FilterPropertyAttributes IKFilter::getFilterAttributes( const String& filterClassName )
{
	FilterPropertyAttributes result;

	IKFilter::FilterMap::iterator found = IKFilter::registeredFilters.find( filterClassName );
	if ( found != IKFilter::registeredFilters.end() ) {
		result = found->second.attributes;
	}

	return result;
}

FilterCategories IKFilter::getFilterCategories( const String& filterClassName )
{
	FilterCategories result;

	IKFilter::FilterMap::iterator found = IKFilter::registeredFilters.find( filterClassName );
	if ( found != IKFilter::registeredFilters.end() ) {
		result = found->second.categories;
	}

	return result;
}

void IKFilter::registerFilter( const String& filterClassName, const String& filterDisplayName, 
					const FilterCategories& categories, const FilterPropertyAttributes& attributes )
{
	IKFilter::FilterMap::iterator found = IKFilter::registeredFilters.find( filterClassName );
	if ( found == IKFilter::registeredFilters.end() ) {
		IKFilterInfo info;
		info.displayName = filterDisplayName;
		info.categories = categories;
		info.attributes = attributes;
		info.className = filterClassName;

		IKFilter::registeredFilters[filterClassName] = info;
	}
}

String IKFilter::getFilterDisplayName( const String& filterClassName )
{
	String result;

	IKFilter::FilterMap::iterator found = IKFilter::registeredFilters.find( filterClassName );
	if ( found != IKFilter::registeredFilters.end() ) {
		result = found->second.displayName;
	}

	return result;
}

FilterPropertyAttribute IKFilter::getFilterAttribute( const String& filterClassName, const String& propertyName )
{
	FilterPropertyAttribute result;
	
	IKFilter::FilterMap::iterator found = IKFilter::registeredFilters.find( filterClassName );
	if ( found != IKFilter::registeredFilters.end() ) {
		FilterPropertyAttributes::iterator it = found->second.attributes.begin();
		while ( it != found->second.attributes.end() ) {
			const FilterPropertyAttribute& attr = *it;
			if ( attr.propertyName == propertyName ) {
				result = attr;
				break;
			}
			++it;
		}
	}

	return result;
}

FilterCategories IKFilter::getCategories()
{
	FilterCategories result;

	IKFilter::FilterMap::iterator it = IKFilter::registeredFilters.begin();
	while ( it != IKFilter::registeredFilters.end() ) {
		const FilterCategories& categories = it->second.categories;
		
		FilterCategories::const_iterator it2 = categories.begin();
		while ( it2 != categories.end() ) {
			FilterCategories::iterator found = std::find( result.begin(), result.end(), *it2 );
			if ( found == result.end() ) {
				result.push_back( *it2 );
			}
			++it2;
		}	

		++it;
	}

	return result;
}

Array<String> IKFilter::getFiltersForCategory( const String& category )
{
	Array<String> result;

	IKFilter::FilterMap::iterator it = IKFilter::registeredFilters.begin();
	while ( it != IKFilter::registeredFilters.end() ) {
		const FilterCategories& categories = it->second.categories;
		
		FilterCategories::const_iterator found = std::find( categories.begin(), categories.end(), category );
		if ( found != categories.end() ) {
			result.push_back( it->second.className );
		}
		++it;
	}

	return result;
}


void IKFilter::setInputImage( IKImage* val )
{
	inputImage_ = val;
}

IKImage* IKFilter::getOutputImage() 
{

	if ( NULL == outputImage_ ) {
		outputImage_ = new IKImage();
	}

	if ( outputImage_->getSize() != inputImage_->getSize() ) {	
		outputImage_->initFromDimensions( inputImage_->getSize() );
	}	

	outputImage_->setFilter(this);

	return outputImage_;
}

void IKFilter::initFromResource( const String& resourceName )
{
	String resName = resourceName + ".shader";
	Resource* res = System::getResourceBundle()->getResource( resName );

	if ( NULL != res ) {
		
		String data;
		
		data.append( (const char*)res->getData(), res->getDataSize() );

		initProgram( data ); 

		delete res;
	}
	else {
		throw RuntimeException( "Shader resource doesn't exist! Shader requested was: " + resName );
	}
}

void IKFilter::initFromFile( const String& fileName )
{
	String data;
	{
		FileInputStream fis(fileName);
		fis >> data;
	}

	initProgram( data ); 
}

void IKFilter::initFromData( const String& filterCode )
{
	initProgram( filterCode ); 
}

VariantData IKFilter::getValue( const String& name )
{
	VariantData result = VariantData::null();

	

	Class* clazz = this->getClass();
	Property* p = clazz->getProperty( name );
	if ( NULL != p ) {
		result = *p->get();
	}

	return result;
}

void IKFilter::setValue( const String& name, const VariantData& val )
{

	Class* clazz = this->getClass();
	Property* p = clazz->getProperty( name );
	if ( NULL != p ) {
		VariantData tmp = val;
		p->set( &tmp );
	}
}

void IKFilter::initFilterVariables()
{
	int activeTexIndex = 0;

	std::vector<String>::iterator it = inputNames_.begin();
	while ( it != inputNames_.end() ) {
		AnsiString s = *it;

		int location = glGetUniformLocationARB( program_, s.c_str() );


		VariantData v = getValue( *it );

		switch ( v.type ) {
			case pdFloat : case pdDouble : {
				float f = v;
				glUniform1fARB( location, f );
			}
			break;

			case pdInt : case pdUInt : case pdLong : case pdULong : {
				int i = v;
				glUniform1iARB( location, i );
			}
			break;

			case pdObject : {
				Object* obj = v;
				if ( NULL != obj ) {
					IKImage* img = dynamic_cast<IKImage*>( obj );
					if ( NULL != img ) {
						activeTexIndex ++;
						glActiveTexture(GL_TEXTURE0 + activeTexIndex);
						img->bind();
						glUniform1iARB(location, activeTexIndex);	
					}
				}
			}
			break;
		}

		++it;
	}
}

void IKFilter::apply()
{
	glUseProgramObjectARB( program_ );	

	int activeTexIndex = 0;
	//this should set up a sampler for the shader? I hope...
	int u1 = glGetUniformLocationARB(program_, "inputImage");
	glActiveTexture(GL_TEXTURE0 + activeTexIndex);
	inputImage_->bind();
	glUniform1iARB(u1, activeTexIndex);	

	
	initFilterVariables();


	glActiveTexture(GL_TEXTURE0);
	inputImage_->bind();
}

void IKFilter::initProgram( const String& data )
{
	program_ = fragment_ = 0;
	program_ = glCreateProgramObjectARB();

	String shaderClassName = StringUtils::toString( typeid(*this) );

	if ( 0 == program_ ) {
		const char* errStr = (const char*)gluErrorString( glGetError() );
		String s = L"OpenGL error creating program object for shader " + shaderClassName + ": ";
		s += errStr;
		throw RuntimeException( s );
	}

	if( !data.empty() ) {

		fragment_ = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

		if ( 0 == fragment_ ) {
			const char* errStr = (const char*)gluErrorString( glGetError() );
			String s = L"OpenGL error creating fragment shader object for shader " + shaderClassName + ": ";
			s += errStr;
			throw RuntimeException( s );
		}

		AnsiString src = "uniform sampler2D inputImage;\n";

		std::vector<String>::iterator it = inputNames_.begin();
		Class* clazz = this->getClass();

		while ( it != inputNames_.end() ) {
			AnsiString s = *it;

			Property* property = clazz->getProperty( *it );
			
			switch ( property->getType() ) {
				case pdFloat : case pdDouble : {
					src += "uniform float " + s + ";\n";
					
				}
				break;
				
				case pdInt : case pdUInt : case pdLong : case pdULong : {
					src += "uniform int " + s + ";\n";
				}
				break;

				case pdObject : {
					if ( property->getTypeClassName() == StringUtils::getClassNameFromTypeInfo(typeid(IKImage)) ) {
						src += "uniform sampler2D " + s + ";\n";
					}
				}
				break;
			}
			
			++it;
		}
		

		src += data + "\n";

		src += "void main (void) { gl_FragColor = shaderMain( inputImage ); }";		


		int len = src.size();
		const char* srcStr = src.c_str();
		glShaderSourceARB(fragment_, 1, (const GLcharARB**)&srcStr, &len);
		
		glCompileShaderARB(fragment_);
		
		int status = 0;
		glGetObjectParameterivARB(fragment_,GL_OBJECT_COMPILE_STATUS_ARB,&status);
		
		char* errString = (char*)malloc(32768);
		glGetInfoLogARB(fragment_,32768,NULL,errString);

		compileStatus_ = errString;
		

		if( !status ) {
			throw RuntimeException( "Shader compile failed for shader " + shaderClassName + ".\n" + compileStatus_ );
		}

		::free(errString);

		glAttachObjectARB(program_, fragment_);
		glLinkProgramARB(program_);
	}
}



void Mixer::setInput2Image( IKImage* val )
{
	input2Image_ = val;
}









