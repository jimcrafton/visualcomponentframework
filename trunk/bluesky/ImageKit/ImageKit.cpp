//ImageKit.cpp

#include "ImageKit.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/OpenGLKit/OpenGLToolkit.h"
#include "vcf/FoundationKit/StringTokenizer.h"

using namespace VCF;


_class_rtti_(IKFilter, "VCF::Object", "IKFilter")
_class_rtti_end_



_class_rtti_(HueAdjust, "VCF::IKFilter", "HueAdjust")
_property_( double, "hueVal", getHueVal, setHueVal, "" );
_class_rtti_end_




_class_rtti_(Brighten, "VCF::IKFilter", "Brighten")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Brighten")
	_property_( double, "brightness", getBrightness, setBrightness, "" );
	_property_attr_("brightness", IKFilter::MinAttr, 0.0 );
	_property_attr_("brightness", IKFilter::MaxAttr, 1.0 );
	_property_attr_("brightness", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("brightness", IKFilter::InputAttr, true );	
_class_rtti_end_



	


_class_rtti_(Mixer, "VCF::IKFilter", "Mixer")
_property_object_( IKImage, "input2Image", getInput2Image, setInput2Image, "" );
_class_rtti_end_

_class_rtti_(GaussianBlur, "VCF::IKFilter", "GaussianBlur")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Gaussian Blur")
	_property_( int, "radius", getRadius, setRadius, "" );
	_property_attr_("radius", IKFilter::MinAttr, 1 );
	_property_attr_("radius", IKFilter::MaxAttr, 7 );
	_property_attr_("radius", IKFilter::DefaultAttr, 4 );
	_property_attr_("radius", IKFilter::InputAttr, true );	

	_property_( float, "amount", getAmount, setAmount, "" );
	_property_attr_("amount", IKFilter::MinAttr, 0.0 );
	_property_attr_("amount", IKFilter::MaxAttr, 5.0 );
	_property_attr_("amount", IKFilter::DefaultAttr, 2.0 );
	_property_attr_("amount", IKFilter::InputAttr, true );	
_class_rtti_end_


_class_rtti_(Emboss, "VCF::IKFilter", "Emboss")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Emboss")
	_property_( float, "displacement", getDisplacement, setDisplacement, "" );
	_property_attr_("displacement", IKFilter::MinAttr, 0.00001 );
	_property_attr_("displacement", IKFilter::MaxAttr, 0.005 );
	_property_attr_("displacement", IKFilter::DefaultAttr, 0.001 );
	_property_attr_("displacement", IKFilter::InputAttr, true );	

	_property_( float, "intensity", getIntensity, setIntensity, "" );
	_property_attr_("intensity", IKFilter::MinAttr, 0.0 );
	_property_attr_("intensity", IKFilter::MaxAttr, 5.0 );
	_property_attr_("intensity", IKFilter::DefaultAttr, 2.0 );
	_property_attr_("intensity", IKFilter::InputAttr, true );	
_class_rtti_end_


_class_rtti_(BrightPass, "VCF::IKFilter", "BrightPass")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Bright Pass")
	_property_( double, "threshold", getThreshold, setThreshold, "" );
	_property_attr_("threshold", IKFilter::MinAttr, 0.0 );
	_property_attr_("threshold", IKFilter::MaxAttr, 1.0 );
	_property_attr_("threshold", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("threshold", IKFilter::InputAttr, true );	
_class_rtti_end_



_class_rtti_(RadialBlur, "VCF::IKFilter", "RadialBlur")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Radial Blur")

	_property_( double, "centerX", getCenterX, setCenterX, "" );
	_property_attr_("centerX", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerX", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerX", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("centerX", IKFilter::InputAttr, true );	

	_property_( double, "centerY", getCenterY, setCenterY, "" );
	_property_attr_("centerY", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerY", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerY", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("centerY", IKFilter::InputAttr, true );	


	_property_( double, "progress", getProgress, setProgress, "" );
	_property_attr_("progress", IKFilter::MinAttr, 0.0 );
	_property_attr_("progress", IKFilter::MaxAttr, 1.0 );
	_property_attr_("progress", IKFilter::DefaultAttr, 0.0 );
	_property_attr_("progress", IKFilter::InputAttr, true );	

	_property_( int, "count", getCount, setCount, "" );
	_property_attr_("count", IKFilter::MinAttr, 1 );
	_property_attr_("count", IKFilter::MaxAttr, 24 );
	_property_attr_("count", IKFilter::DefaultAttr, 24 );
	_property_attr_("count", IKFilter::InputAttr, true );	

_class_rtti_end_



_class_rtti_(Wavy, "VCF::IKFilter", "Wavy")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Wavy")

	_property_( double, "amplitude", getAmplitude, setAmplitude, "" );
	_property_attr_("amplitude", IKFilter::MinAttr, 0.0 );
	_property_attr_("amplitude", IKFilter::MaxAttr, 10.0 );
	_property_attr_("amplitude", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("amplitude", IKFilter::InputAttr, true );	

	_property_( double, "frequency", getFrequency, setFrequency, "" );
	_property_attr_("frequency", IKFilter::MinAttr, 0.0 );
	_property_attr_("frequency", IKFilter::MaxAttr, 10.0 );
	_property_attr_("frequency", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("frequency", IKFilter::InputAttr, true );	
_class_rtti_end_



_class_rtti_(Wavy2, "VCF::IKFilter", "Wavy2")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Wavy2")

	_property_( double, "amount", getAmount, setAmount, "" );
	_property_attr_("amount", IKFilter::MinAttr, 0.0 );
	_property_attr_("amount", IKFilter::MaxAttr, 1.0 );
	_property_attr_("amount", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("amount", IKFilter::InputAttr, true );	

	_property_( double, "xAmplitude", getXAmplitude, setXAmplitude, "" );
	_property_attr_("xAmplitude", IKFilter::MinAttr, 0.0 );
	_property_attr_("xAmplitude", IKFilter::MaxAttr, 10.0 );
	_property_attr_("xAmplitude", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("xAmplitude", IKFilter::InputAttr, true );	

	_property_( double, "yAmplitude", getYAmplitude, setYAmplitude, "" );
	_property_attr_("yAmplitude", IKFilter::MinAttr, 0.0 );
	_property_attr_("yAmplitude", IKFilter::MaxAttr, 10.0 );
	_property_attr_("yAmplitude", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("yAmplitude", IKFilter::InputAttr, true );	

	_property_( double, "progress", getProgress, setProgress, "" );
	_property_attr_("progress", IKFilter::MinAttr, 0.0 );
	_property_attr_("progress", IKFilter::MaxAttr, 100.0 );
	_property_attr_("progress", IKFilter::DefaultAttr, 0.0 );
	_property_attr_("progress", IKFilter::InputAttr, true );	
_class_rtti_end_


_class_rtti_(BlackAndWhite, "VCF::IKFilter", "BlackAndWhite")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Black and White")

	_property_( double, "midpoint", getMidpoint, setMidpoint, "" );
	_property_attr_("midpoint", IKFilter::MinAttr, 0.0 );
	_property_attr_("midpoint", IKFilter::MaxAttr, 1.0 );
	_property_attr_("midpoint", IKFilter::DefaultAttr, 0.8 );
	_property_attr_("midpoint", IKFilter::InputAttr, true );
_class_rtti_end_



_class_rtti_(Bloom, "VCF::IKFilter", "Bloom")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Bloom")

	_property_( double, "bloomIntensity", getBloomIntensity, setBloomIntensity, "" );
	_property_attr_("bloomIntensity", IKFilter::MinAttr, 0.0 );
	_property_attr_("bloomIntensity", IKFilter::MaxAttr, 1.0 );
	_property_attr_("bloomIntensity", IKFilter::DefaultAttr, 0.8 );
	_property_attr_("bloomIntensity", IKFilter::InputAttr, true );

	_property_( double, "baseIntensity", getBaseIntensity, setBaseIntensity, "" );
	_property_attr_("baseIntensity", IKFilter::MinAttr, 0.0 );
	_property_attr_("baseIntensity", IKFilter::MaxAttr, 10.0 );
	_property_attr_("baseIntensity", IKFilter::DefaultAttr, 0.8 );
	_property_attr_("baseIntensity", IKFilter::InputAttr, true );

	_property_( double, "bloomSaturation", getBloomSaturation, setBloomSaturation, "" );
	_property_attr_("bloomSaturation", IKFilter::MinAttr, 0.0 );
	_property_attr_("bloomSaturation", IKFilter::MaxAttr, 10.0 );
	_property_attr_("bloomSaturation", IKFilter::DefaultAttr, 0.8 );
	_property_attr_("bloomSaturation", IKFilter::InputAttr, true );

	_property_( double, "baseSaturation", getBaseSaturation, setBaseSaturation, "" );
	_property_attr_("baseSaturation", IKFilter::MinAttr, 0.0 );
	_property_attr_("baseSaturation", IKFilter::MaxAttr, 10.0 );
	_property_attr_("baseSaturation", IKFilter::DefaultAttr, 0.8 );
	_property_attr_("baseSaturation", IKFilter::InputAttr, true );

	_property_( double, "threshold", getThreshold, setThreshold, "" );
	_property_attr_("threshold", IKFilter::MinAttr, 0.0 );
	_property_attr_("threshold", IKFilter::MaxAttr, 10.0 );
	_property_attr_("threshold", IKFilter::DefaultAttr, 0.8 );
	_property_attr_("threshold", IKFilter::InputAttr, true );
	
_class_rtti_end_
	

_class_rtti_(Pixelate, "VCF::IKFilter", "Pixelate")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Pixelate")

	_property_( double, "progress", getProgress, setProgress, "" );
	_property_attr_("progress", IKFilter::MinAttr, 0.0 );
	_property_attr_("progress", IKFilter::MaxAttr, 1.0 );
	_property_attr_("progress", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("progress", IKFilter::InputAttr, true );	
_class_rtti_end_


_class_rtti_(LightStreak, "VCF::IKFilter", "LightStreak")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Light Streak")

	_property_( double, "brightThreshold", getBrightThreshold, setBrightThreshold, "" );
	_property_attr_("brightThreshold", IKFilter::MinAttr, 0.0 );
	_property_attr_("brightThreshold", IKFilter::MaxAttr, 1.0 );
	_property_attr_("brightThreshold", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("brightThreshold", IKFilter::InputAttr, true );	

	_property_( double, "scale", getScale, setScale, "" );
	_property_attr_("scale", IKFilter::MinAttr, 0.0 );
	_property_attr_("scale", IKFilter::MaxAttr, 1.0 );
	_property_attr_("scale", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("scale", IKFilter::InputAttr, true );	

	_property_( double, "attenuation", getAttenuation, setAttenuation, "" );
	_property_attr_("attenuation", IKFilter::MinAttr, 0.0 );
	_property_attr_("attenuation", IKFilter::MaxAttr, 1.0 );
	_property_attr_("attenuation", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("attenuation", IKFilter::InputAttr, true );	

	_property_( double, "xDirection", getXDirection, setXDirection, "" );
	_property_attr_("xDirection", IKFilter::MinAttr, 0.0 );
	_property_attr_("xDirection", IKFilter::MaxAttr, 1.0 );
	_property_attr_("xDirection", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("xDirection", IKFilter::InputAttr, true );	

	_property_( double, "yDirection", getYDirection, setYDirection, "" );
	_property_attr_("yDirection", IKFilter::MinAttr, 0.0 );
	_property_attr_("yDirection", IKFilter::MaxAttr, 1.0 );
	_property_attr_("yDirection", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("yDirection", IKFilter::InputAttr, true );	

	
	_property_( double, "pixelWidth", getPixelWidth, setPixelWidth, "" );
	_property_attr_("pixelWidth", IKFilter::MinAttr, 0.0 );
	_property_attr_("pixelWidth", IKFilter::MaxAttr, 1.0 );
	_property_attr_("pixelWidth", IKFilter::DefaultAttr, 0.0009766 );
	_property_attr_("pixelWidth", IKFilter::InputAttr, true );	

	_property_( double, "pixelHeight", getPixelHeight, setPixelHeight, "" );
	_property_attr_("pixelHeight", IKFilter::MinAttr, 0.0 );
	_property_attr_("pixelHeight", IKFilter::MaxAttr, 1.0 );
	_property_attr_("pixelHeight", IKFilter::DefaultAttr, 0.0013021 );
	_property_attr_("pixelHeight", IKFilter::InputAttr, true );	

	_property_( int, "numSamples", getNumSamples, setNumSamples, "" );
	_property_attr_("numSamples", IKFilter::MinAttr, 1 );
	_property_attr_("numSamples", IKFilter::MaxAttr, 10 );
	_property_attr_("numSamples", IKFilter::DefaultAttr, 2 );
	_property_attr_("numSamples", IKFilter::InputAttr, true );	

	_property_( int, "iteration", getIteration, setIteration, "" );
	_property_attr_("iteration", IKFilter::MinAttr, 1 );
	_property_attr_("iteration", IKFilter::MaxAttr, 5 );
	_property_attr_("iteration", IKFilter::DefaultAttr, 1 );
	_property_attr_("iteration", IKFilter::InputAttr, true );	
_class_rtti_end_


_class_rtti_(Ripple, "VCF::IKFilter", "Ripple")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Ripple")

	_property_( double, "centerX", getCenterX, setCenterX, "" );
	_property_attr_("centerX", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerX", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerX", IKFilter::DefaultAttr, 0.50 );
	_property_attr_("centerX", IKFilter::InputAttr, true );	

	_property_( double, "centerY", getCenterY, setCenterY, "" );
	_property_attr_("centerY", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerY", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerY", IKFilter::DefaultAttr, 0.50 );
	_property_attr_("centerY", IKFilter::InputAttr, true );

	_property_( double, "amplitude", getAmplitude, setAmplitude, "" );
	_property_attr_("amplitude", IKFilter::MinAttr, 0.0 );
	_property_attr_("amplitude", IKFilter::MaxAttr, 1.0 );
	_property_attr_("amplitude", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("amplitude", IKFilter::InputAttr, true );	

	_property_( double, "frequency", getFrequency, setFrequency, "" );
	_property_attr_("frequency", IKFilter::MinAttr, 0.0 );
	_property_attr_("frequency", IKFilter::MaxAttr, 100.0 );
	_property_attr_("frequency", IKFilter::DefaultAttr, 50.0 );
	_property_attr_("frequency", IKFilter::InputAttr, true );	

	_property_( double, "phase", getPhase, setPhase, "" );
	_property_attr_("phase", IKFilter::MinAttr, 0.0 );
	_property_attr_("phase", IKFilter::MaxAttr, 1.0 );
	_property_attr_("phase", IKFilter::DefaultAttr, 0.20 );
	_property_attr_("phase", IKFilter::InputAttr, true );		
_class_rtti_end_



_class_rtti_(Swirl, "VCF::IKFilter", "Swirl")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Swirl")

	_property_( double, "centerX", getCenterX, setCenterX, "" );
	_property_attr_("centerX", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerX", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerX", IKFilter::DefaultAttr, 0.50 );
	_property_attr_("centerX", IKFilter::InputAttr, true );	

	_property_( double, "centerY", getCenterY, setCenterY, "" );
	_property_attr_("centerY", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerY", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerY", IKFilter::DefaultAttr, 0.50 );
	_property_attr_("centerY", IKFilter::InputAttr, true );

	_property_( double, "spiralStrength", getSpiralStrength, setSpiralStrength, "" );
	_property_attr_("spiralStrength", IKFilter::MinAttr, 0.0 );
	_property_attr_("spiralStrength", IKFilter::MaxAttr, 10.0 );
	_property_attr_("spiralStrength", IKFilter::DefaultAttr, 1.150 );
	_property_attr_("spiralStrength", IKFilter::InputAttr, true );	

	_property_( double, "xFrequency", getXFrequency, setXFrequency, "" );
	_property_attr_("xFrequency", IKFilter::MinAttr, 0.0 );
	_property_attr_("xFrequency", IKFilter::MaxAttr, 100.0 );
	_property_attr_("xFrequency", IKFilter::DefaultAttr, 1.0 );
	_property_attr_("xFrequency", IKFilter::InputAttr, true );	

	_property_( double, "yFrequency", getYFrequency, setYFrequency, "" );
	_property_attr_("yFrequency", IKFilter::MinAttr, 0.0 );
	_property_attr_("yFrequency", IKFilter::MaxAttr, 1.0 );
	_property_attr_("yFrequency", IKFilter::DefaultAttr, 1.0 );
	_property_attr_("yFrequency", IKFilter::InputAttr, true );		
_class_rtti_end_



_class_rtti_(Pinch, "VCF::IKFilter", "Pinch")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Pinch")

	_property_( double, "centerX", getCenterX, setCenterX, "" );
	_property_attr_("centerX", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerX", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerX", IKFilter::DefaultAttr, 0.50 );
	_property_attr_("centerX", IKFilter::InputAttr, true );	

	_property_( double, "centerY", getCenterY, setCenterY, "" );
	_property_attr_("centerY", IKFilter::MinAttr, 0.0 );
	_property_attr_("centerY", IKFilter::MaxAttr, 1.0 );
	_property_attr_("centerY", IKFilter::DefaultAttr, 0.50 );
	_property_attr_("centerY", IKFilter::InputAttr, true );

	_property_( double, "radius", getRadius, setRadius, "" );
	_property_attr_("radius", IKFilter::MinAttr, 0.0 );
	_property_attr_("radius", IKFilter::MaxAttr, 1.0 );
	_property_attr_("radius", IKFilter::DefaultAttr, 0.5 );
	_property_attr_("radius", IKFilter::InputAttr, true );	

	_property_( double, "amount", getAmount, setAmount, "" );
	_property_attr_("amount", IKFilter::MinAttr, 0.0 );
	_property_attr_("amount", IKFilter::MaxAttr, 100.0 );
	_property_attr_("amount", IKFilter::DefaultAttr, 1.0 );
	_property_attr_("amount", IKFilter::InputAttr, true );	
_class_rtti_end_




_class_rtti_(DirectionalBlur, "VCF::IKFilter", "DirectionalBlur")
	_attribute_(IKFilter::CategoryAttr, "Image Processing")
	_attribute_(IKFilter::DisplayNameAttr, "Directional Blur")

	_property_( double, "angle", getAngle, setAngle, "" );
	_property_attr_("angle", IKFilter::MinAttr, 0.0 );
	_property_attr_("angle", IKFilter::MaxAttr, 360.0 );
	_property_attr_("angle", IKFilter::DefaultAttr, 0.0 );
	_property_attr_("angle", IKFilter::InputAttr, true );	

	_property_( double, "amount", getAmount, setAmount, "" );
	_property_attr_("amount", IKFilter::MinAttr, 0.0 );
	_property_attr_("amount", IKFilter::MaxAttr, 100.0 );
	_property_attr_("amount", IKFilter::DefaultAttr, 0.50 );
	_property_attr_("amount", IKFilter::InputAttr, true );
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




void ImageKit::init( int argc, char** argv )
{
	ImageKit::instance = new ImageKit();

	{
		GLInit g;		

		AnsiString s = (const char*)glGetString(GL_VERSION);
		size_t dotPos = s.find(".");
		if ( dotPos != String::npos ) {
			int majorVersion = StringUtils::fromStringAsInt( s.substr(0,dotPos) );
			if ( majorVersion < ImageKit::MinOpenGLVersion ) {
				throw RuntimeException( "The Open GL version for this machine is too old.\nImageKit will not work correctly on this PC.\nTry updating your video card drivers." );
			}
		}
		else {
			throw RuntimeException( "Unable to determine valid Open GL version.\nImageKit will not work correctly on this PC.\nTry updating your video card drivers." );
		}

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
	REGISTER_CLASSINFO_EXTERNAL(Emboss);
	REGISTER_CLASSINFO_EXTERNAL(BrightPass);
	REGISTER_CLASSINFO_EXTERNAL(RadialBlur);
	REGISTER_CLASSINFO_EXTERNAL(Wavy);
	REGISTER_CLASSINFO_EXTERNAL(Wavy2);
	REGISTER_CLASSINFO_EXTERNAL(BlackAndWhite);
	REGISTER_CLASSINFO_EXTERNAL(Bloom);
	REGISTER_CLASSINFO_EXTERNAL(Pixelate);
	REGISTER_CLASSINFO_EXTERNAL(LightStreak);
	REGISTER_CLASSINFO_EXTERNAL(Ripple);
	REGISTER_CLASSINFO_EXTERNAL(Swirl);
	REGISTER_CLASSINFO_EXTERNAL(Pinch);
	REGISTER_CLASSINFO_EXTERNAL(DirectionalBlur);	
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



const String& IKFilter::CategoryAttr = "category";
const String& IKFilter::DisplayNameAttr = "displayName";
const String& IKFilter::MinAttr = "min";
const String& IKFilter::MaxAttr = "max";
const String& IKFilter::DefaultAttr = "default";
const String& IKFilter::InputAttr = "input";
const String& IKFilter::OutputAttr = "output";



IKFilter::IKFilter():
	inputImage_(NULL),
	outputImage_(NULL),
	insertBuiltins_(false)
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

	Class* clazz = ClassRegistry::getClass( filterClassName );
	if ( NULL != clazz ) {
		Enumerator<Property*>* props = clazz->getProperties();
		while ( props->hasMoreElements() ) {
			Property* prop = props->nextElement();

			if ( prop->hasAttribute( IKFilter::DefaultAttr ) && 
				prop->hasAttribute( IKFilter::MinAttr ) && 
				prop->hasAttribute( IKFilter::MaxAttr ) ) {

				FilterPropertyAttribute info;
				info.defaultVal = prop->getAttribute( IKFilter::DefaultAttr );
				info.minVal = prop->getAttribute( IKFilter::MinAttr );
				info.maxVal = prop->getAttribute( IKFilter::MaxAttr );
				info.displayName = prop->getDisplayName();
				info.propertyName = prop->getName();

				result.push_back( info );
			}
		}
	}

	return result;
}

FilterCategories IKFilter::getFilterCategories( const String& filterClassName )
{
	FilterCategories result;

	Class* clazz = ClassRegistry::getClass( filterClassName );
	if ( NULL != clazz ) {
		String cats = clazz->getAttribute( IKFilter::CategoryAttr );

		StringTokenizer tok(cats,",");
		tok.getElements( result );
	}

	return result;
}

void IKFilter::registerFilter( const String& filterClassName, const String& filterDisplayName, 
					const FilterCategories& categories, const FilterPropertyAttributes& attributes )
{
	Class* clazz = ClassRegistry::getClass( filterClassName );
	if ( NULL != clazz ) {
		String catString;
		FilterCategories::const_iterator it = categories.begin();
		while ( it != categories.end() ) {
			if ( it != categories.begin() ) {
				catString += ",";
			}
			catString += *it;
			++it;
		}


		clazz->addAttribute( IKFilter::CategoryAttr, catString );
		clazz->addAttribute( IKFilter::DisplayNameAttr, filterDisplayName );

		FilterPropertyAttributes::const_iterator it2 = attributes.begin();
		while ( it2 != attributes.end() ) {
			const FilterPropertyAttribute& attr = *it2;

			Property* prop = clazz->getProperty( attr.propertyName );
			if ( NULL != prop ) {
				prop->addAttribute( IKFilter::DefaultAttr, attr.defaultVal );
				prop->addAttribute( IKFilter::MinAttr, attr.minVal );
				prop->addAttribute( IKFilter::MaxAttr, attr.maxVal );
			}
			++it2;
		}
	}
}

String IKFilter::getFilterDisplayName( const String& filterClassName )
{
	Class* clazz = ClassRegistry::getClass( filterClassName );
	if ( NULL != clazz ) {
		return clazz->getAttribute( IKFilter::DisplayNameAttr );
	}

	return String();
}

FilterPropertyAttribute IKFilter::getFilterAttribute( const String& filterClassName, const String& propertyName )
{
	FilterPropertyAttribute result;
	
	Class* clazz = ClassRegistry::getClass( filterClassName );
	if ( NULL != clazz ) {		
		Property* prop = clazz->getProperty(propertyName );

		if ( prop != NULL ) {
			if ( prop->hasAttribute( IKFilter::DefaultAttr ) && 
				prop->hasAttribute( IKFilter::MinAttr ) && 
				prop->hasAttribute( IKFilter::MaxAttr ) ) {
				
				result.defaultVal = prop->getAttribute( IKFilter::DefaultAttr );
				result.minVal = prop->getAttribute( IKFilter::MinAttr );
				result.maxVal = prop->getAttribute( IKFilter::MaxAttr );
				result.displayName = prop->getDisplayName();
				result.propertyName = prop->getName();
			}
		}
	}

	return result;
}

FilterCategories IKFilter::getCategories()
{
	FilterCategories result;

	std::vector<VariantData> vals = ClassRegistry::getAttrValuesByClass( classid(IKFilter), IKFilter::CategoryAttr );

	std::vector<VariantData>::iterator it = vals.begin();
	while ( it != vals.end() ) {
		result.push_back( *it );
		++it;
	}

	return result;	
}

Array<String> IKFilter::getFiltersForCategory( const String& category )
{
	Array<String> result;


	std::vector<Class*> classes = ClassRegistry::getClassesWithAttribute( classid(IKFilter), IKFilter::CategoryAttr );

	std::vector<Class*>::iterator it = classes.begin();
	while ( it != classes.end() ) {
		Class* clazz = *it;

		String catStr = clazz->getAttribute( IKFilter::CategoryAttr );

		StringTokenizer tok(catStr,",");
		
		while ( tok.hasMoreElements() ) {
			String cat = tok.nextElement();

			if ( cat == category ) {
				result.push_back( clazz->getClassName() );
			}
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

	
	if ( inputNames_.empty() ) {
		Class* clazz = getClass();
		Enumerator<Property*>* props = clazz->getProperties();
		while ( props->hasMoreElements() ) {
			Property* prop = props->nextElement();
			if ( prop->hasAttribute( IKFilter::InputAttr ) ) {
				inputNames_.push_back( prop->getName() );
			}
		}
	}

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

		
		Class* clazz = getClass();
		Enumerator<Property*>* props = clazz->getProperties();

		while ( props->hasMoreElements() ) {
			Property* property = props->nextElement();

			if ( property->hasAttribute( IKFilter::InputAttr ) ) {
				AnsiString s = property->getName();
				
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
			}
		}



		//add built in functions

		if ( insertBuiltins_ ) {			
			Resource* res = System::getResourceBundle()->getResource( "builtins.shader" );
			if ( NULL != res ) {
				src.append( (const char*)res->getData(), res->getDataSize() );
				delete res;

				src += "\n\n";
			}
			else {
				throw RuntimeException( "Shader built in functions don't exist! Most likely reason is that the builtins.shader resource file is missing." );
			}			
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
			StringUtils::trace( src );
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








