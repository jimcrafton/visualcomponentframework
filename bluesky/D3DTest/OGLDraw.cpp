//OGLDraw.cpp




#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/RTTIMacros.h"


#include "GL/glew.h"




#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"


#ifdef  _DEBUG
#pragma comment (lib,"glew32sd.lib")
#else
#pragma comment (lib,"glew32s.lib")
#endif




#define FRAG_CODE	"void main()\n"\
	"{\n"\
		"gl_FragColor = vec4(0.4,0.4,0.8,1.0);\n"\
	"}\n"





namespace VCF { 


class GL2DView : public View {
public:
	virtual void paintView( GraphicsContext* ctx ) {
		Rect r = getViewControl()->getClientBounds();

		Color c = *getViewControl()->getColor();

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, r.getWidth(), r.getHeight(), 0, -1, 1);
		glViewport( 0, 0, r.getWidth(), r.getHeight() );
		
		glDisable(GL_DEPTH_TEST);		

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor( c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha() );
		glClear(GL_COLOR_BUFFER_BIT);
	}
};



class GLMat {
public:

	GLMat(){
		ident();
	}

	GLMat& operator=( const Matrix2D& rhs ) {
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


struct Dimensions {
	Dimensions(): width(0), height(0){}
	Dimensions( const Size& sz ): width(sz.width_), height(sz.height_){}

	Dimensions& operator=( const Size& rhs ) {
		width = rhs.width_;
		height = rhs.height_;
		return *this;
	}

	operator Size() const {
		return Size( width, height );
	}

	bool operator ==( const Dimensions& rhs ) const {
		return width == rhs.width && height == rhs.height;
	}

	bool operator !=( const Dimensions& rhs ) const {
		return !operator ==(rhs);
	}

	uint32 width;
	uint32 height;
};


class IKImage;
class IKFilter;




class ImageKit {
public:
	static void init( int argc, char** argv );
	static void terminate();

	static void initDefaultFBO();
	static void destroyDefaultFBO();

	static GLuint getDefaultFBO() {
		return ImageKit::defaultFrameBufferObj;
	}

protected:
	static ImageKit* instance;
	
private:
	static GLuint defaultFrameBufferObj; 

	ImageKit();
	~ImageKit();
};





class IKImageContext {
public:

	IKImageContext();

	void initView( const double width, const double& height );

	void draw( const double& x, const double& y, IKImage* image );

	void setTransformMatrix( const Matrix2D& m ) {
		xfrm_ = m;
	}

	void multiTransformMatrix( const Matrix2D& m ) {
		xfrm_ *= m;
	}

	Matrix2D getTransformMatrix() const {
		return xfrm_;
	}

	void setOpacity( const double& val ) {
		opacity_ = val;
	}

	double getOpacity() const {
		return opacity_;
	}

	
protected:
	Matrix2D xfrm_;
	double opacity_;
	Size viewSize;

	
};



class IKImage : public Object {
public:

	enum {
		NullHandle = 0
	};

	IKImage();
	IKImage( Image* image );
	IKImage( const Dimensions& dimensions );
	IKImage( const uchar* data, const size_t& size, const MIMEType& type  );
	IKImage( const uchar* data, const size_t& size );
	IKImage( const uchar* data, const Dimensions& dimensions );
	IKImage( const String& fileName );

	virtual ~IKImage();

	void initFromImage( Image* image );
	void initFromData( const uchar* data, const size_t& size, const MIMEType& type );
	void initFromData( const uchar* data, const size_t& size );
	void initFromBits( const uchar* data, const Dimensions& dimensions );
	void initFromDimensions( const Dimensions& dimensions );
	void initFromFile( const String& fileName );

	Dimensions getSize() const {
		return size_;
	}

	IKFilter* getFilter() {
		return filter_;
	}

	void setFilter( IKFilter* filter ) {
		filter_ = filter;
	}


	uint32 getHandle() const {
		return imageHandle_;
	}

	void setHandle( const uint32& val );
protected:

	friend class IKImageContext;
	friend class IKFilter;

	uint32 imageHandle_;
	Dimensions size_;
	IKFilter* filter_;	

	static std::map<uint32,Dimensions> texDimensionsMap;

	void bind();


	void destroyTexture();

	void attach( IKImage* img ) {
		imageHandle_ = img->imageHandle_;
	}

	uint32 detach() {
		uint32 result = imageHandle_;
		imageHandle_ = NullHandle;

		return result;
	}
	
};






class IKFilter : public Object {
public:
	IKFilter();
	virtual ~IKFilter();

	void initFromResource( const String& resourceName );
	void initFromFile( const String& fileName );

	std::vector<String> getInputNames() {
		return inputNames_;
	}

	std::vector<String> getOutputNames() {
		return outputNames_;
	}
	
	void apply();

	VariantData getValue( const String& name );
	void setValue( const String& name, const VariantData& val );

	IKImage* getInputImage() {
		return inputImage_;
	}

	void setInputImage( IKImage* val );

	IKImage* getOutputImage();

protected:
	GLuint fragment_;
	GLuint program_;
	String fragmentFilename_;
	String compileStatus_;

	IKImage* inputImage_;
	IKImage* outputImage_;


	std::vector<String> inputNames_;
	std::vector<String> outputNames_;
	
	void initProgram( const String& data );

	
};

_class_rtti_(IKFilter, "VCF::Object", "IKFilter")
_class_rtti_end_

class HueAdjust : public IKFilter {
public:
	HueAdjust():hueVal_(0){ 
		inputNames_.push_back("hueVal"); 

		initFromResource( "HueAdjust" );
	}


	double getHueVal() {
		return hueVal_;
	}

	void setHueVal( const double& val ) {
		hueVal_ = val;
	}


	double hueVal_;
};


_class_rtti_(HueAdjust, "VCF::IKFilter", "HueAdjust")
_property_( double, "hueVal", getHueVal, setHueVal, "" );
_class_rtti_end_




class Brighten : public IKFilter {
public:
	Brighten():brightness_(0){ 
		inputNames_.push_back("brightness"); 

		initFromResource( "Brighten" );
	}


	double getBrightness() {
		return brightness_;
	}

	void setBrightness( const double& val ) {
		brightness_ = val;
	}


	double brightness_;
};


_class_rtti_(Brighten, "VCF::IKFilter", "Brighten")
_property_( double, "brightness", getBrightness, setBrightness, "" );
_class_rtti_end_



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



IKImageContext::IKImageContext():
	opacity_(1.0)
{
	ImageKit::initDefaultFBO();
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
	/*
	glEnable (GL_LINE_SMOOTH);
	glEnable (GL_POLYGON_SMOOTH );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

//	glPolygonMode(GL_FRONT,GL_FILL);
 //glPolygonMode(GL_BACK,GL_FILL);
 glShadeModel(GL_SMOOTH);
*/


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

			filter->apply();

			IKImage* outImg = filter->getOutputImage();

			outImg->bind();

			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, outImg->getHandle(), 0);



			img->bind();


			u=1.0;
			v=1.0;
			
			Dimensions sz = img->getSize();
			
			glColor4f(1.0, 1.0, 1.0, opacity_);
			
			glBegin(GL_POLYGON);
			
			
				glTexCoord2f(0.0, 0.0);
				glVertex2i(0, 0);
				
				glTexCoord2f(u, 0.0);
				glVertex2i(sz.width, 0);
				
				glTexCoord2f(u, v);
				glVertex2i(sz.width, sz.height);
				
				glTexCoord2f(0.0, v);
				glVertex2i(0, sz.height);
			
			
			glEnd();

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
		outImg->bind();


		

		imgSz = outImg->getSize();
		u=1.0;
		v=1.0;
		glPushMatrix();
		
		GLMat m;
		m = xfrm_;
		glMultMatrixd( m );
		
		glColor4f(1.0, 1.0, 1.0, opacity_);
		
		glBegin(GL_POLYGON);
		
		
			glTexCoord2f(0.0, 0.0);
			glVertex2i(x, y);
			
			glTexCoord2f(u, 0.0);
			glVertex2i(x+imgSz.width, y);
			
			glTexCoord2f(u, v);
			glVertex2i(x+imgSz.width, y+imgSz.height);
			
			glTexCoord2f(0.0, v);
			glVertex2i(x, y+imgSz.height);
		
		
		glEnd();
		
		glPopMatrix();

	}
	else {		
		image->bind();
		
		u=1.0;
		v=1.0;
		
		Size sz = image->getSize();
		glPushMatrix();
		
		GLMat m;
		m = xfrm_;
		glMultMatrixd( m );
		
		glColor4f(1.0, 1.0, 1.0, opacity_);
		
		glBegin(GL_POLYGON);
		
		
			glTexCoord2f(0.0, 0.0);
			glVertex2i(x, y);
			
			glTexCoord2f(u, 0.0);
			glVertex2i(x+sz.width_, y);
			
			glTexCoord2f(u, v);
			glVertex2i(x+sz.width_, y+sz.height_);
			
			glTexCoord2f(0.0, v);
			glVertex2i(x, y+sz.height_);
		
		
		glEnd();
		
		glPopMatrix();

	}


	

	

/*
	glDisable (GL_LINE_SMOOTH);
	glDisable (GL_POLYGON_SMOOTH );
	*/
}




IKFilter::IKFilter():
	inputImage_(NULL),
	outputImage_(NULL)
{

}

IKFilter::~IKFilter()
{
	delete outputImage_;
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
		throw RuntimeException( "Shader resource doesn't exist!" );
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

void IKFilter::apply()
{
	glUseProgramObjectARB( program_ );	

	//this should set up a sampler for the shader? I hope...
	int u1 = glGetUniformLocationARB(program_, "inputImage");
	glActiveTexture(GL_TEXTURE0 + 0);
	inputImage_->bind();
	glUniform1iARB(u1, 0);	

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
		}

		++it;
	}


	
}

void IKFilter::initProgram( const String& data )
{
	program_ = fragment_ = 0;
	program_ = glCreateProgramObjectARB();

	if ( 0 == program_ ) {
		const char* errStr = (const char*)gluErrorString( glGetError() );
		String s = L"OpenGL error creating program object: ";
		s += errStr;
		throw RuntimeException( s );
	}

	if( !data.empty() ) {

		fragment_ = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

		if ( 0 == fragment_ ) {
			const char* errStr = (const char*)gluErrorString( glGetError() );
			String s = L"OpenGL error creating fragment shader object: ";
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
		
		::free(errString);

		glAttachObjectARB(program_, fragment_);
		glLinkProgramARB(program_);
	}
}

};//namespace vcf




using namespace VCF;



class OGLView : public OpenGLControl {
public:

	GLuint frag;
	GLuint prog;

	OGLView() {

		hueAdj = NULL;

	}

	IKImage img;
	HueAdjust* hueAdj;
	Brighten* bright;


	void doGL()
	{
		static initialized = false;

		if ( !initialized ) {


			initialized = true;

			img.initFromFile( "res:logo.png" );


			hueAdj = new HueAdjust();

			bright = new Brighten();
		}

		initialized = true;



		Rect r = getClientBounds();

		IKImageContext ic;

		ic.initView( r.getWidth(), r.getHeight() );

		Color c = *getColor();
		glClearColor( c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha() );
		glClear(GL_COLOR_BUFFER_BIT);		
		
		static double a = 0;	
		
		ic.multiTransformMatrix( Matrix2D::rotation(a) * Matrix2D::scaling(1.3,1.3) );
		
		ic.draw( 10, 10, &img );


		ic.setTransformMatrix( Matrix2D::translation( 50, 100 ) );
		ic.setOpacity( sin( 0.1250 * (a/6.28) ) );
		ic.draw( 10, 10, &img );

		ic.setTransformMatrix( Matrix2D() );
		ic.draw( 30, 210, &img );
		ic.draw( 130, 310, &img );

		ic.multiTransformMatrix( Matrix2D::rotation(a) );
		ic.draw( 10, 210, &img );
		ic.draw( 231, 410, &img );

		a += 1.0;





		

		hueAdj->setInputImage( &img );
		hueAdj->setHueVal( 1.5 );

		bright->setInputImage( hueAdj->getOutputImage() );
		bright->setBrightness( 0.5 );

		ic.setTransformMatrix( Matrix2D() );
		ic.setOpacity( 1.0 );
		ic.draw( 300, 350, bright->getOutputImage() );
	}


	virtual void paint(GraphicsContext * context) {
		OpenGLControl::paint( context );

		doGL();

		swapBuffers();
	}
};

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


