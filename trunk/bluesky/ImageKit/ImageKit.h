#ifndef _VCF_IMAGEKIT_H__
#define _VCF_IMAGEKIT_H__
//OpenGLKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#define GLEW_STATIC

#include "GL/glew.h"


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"




#ifdef  _DEBUG
#pragma comment (lib,"glew32sd.lib")
#else
#pragma comment (lib,"glew32s.lib")
#endif


/**
Handle the extension based on the compiler
*/
# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1500)
#     define _LIB_CPLVERNUM "vc90"
#   elif (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80"
#   elif (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
#  ifdef VCF_BCC
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif






namespace VCF {


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
	enum {
		MinOpenGLVersion = 2
	};

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

	IKImageContext( Control* control );

	~IKImageContext();

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

	void clear( Color* color );
protected:
	Matrix2D xfrm_;
	double opacity_;
	Size viewSize;

	OpenGLPeer* glPeer_;


	static void controlDestroyed(ComponentEvent* e); 
	static std::map<Control*,OpenGLPeer*> glPeerMap;
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

	void renderToImage( Image* image );
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
	

	void render( const double& x, const double& y );
	void renderToFBO( int fbo );
	
};



class FilterPropertyAttribute {
public:
	FilterPropertyAttribute(): minVal(VariantData::null()), maxVal(VariantData::null()),
							defaultVal(VariantData::null()){}

	VariantData minVal;
	VariantData maxVal;
	VariantData defaultVal;
	String displayName;
	String propertyName;

	bool isNull() const {
		return minVal.isNull() && maxVal.isNull() && defaultVal.isNull() && displayName.empty() && propertyName.empty();
	}
};


typedef Array<FilterPropertyAttribute> FilterPropertyAttributes;
typedef Array<String> FilterCategories;

class IKFilterInfo {
public:
	FilterPropertyAttributes attributes;
	FilterCategories categories;
	String displayName;
	String className;
};

class IKFilter : public Object {
public:

	static const String& CategoryAttr;
	static const String& DisplayNameAttr;
	static const String& MinAttr;
	static const String& MaxAttr;
	static const String& DefaultAttr;
	static const String& InputAttr;
	static const String& OutputAttr;


	IKFilter();
	virtual ~IKFilter();

	void initFromResource( const String& resourceName );
	void initFromFile( const String& fileName );
	void initFromData( const String& filterCode );

	virtual void setDefaults(){};

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

	String getCompileStatus() {
		return compileStatus_;
	}

	static FilterPropertyAttributes getFilterAttributes( IKFilter* filter );

	static FilterCategories getFilterCategories( IKFilter* filter );

	static FilterPropertyAttributes getFilterAttributes( const String& filterClassName );

	static FilterCategories getFilterCategories( const String& filterClassName );

	static void registerFilter( const String& filterClassName, const String& filterDisplayName, 
								const FilterCategories& categories, const FilterPropertyAttributes& attributes );

	static FilterPropertyAttribute getFilterAttribute( const String& filterClassName, const String& propertyName );
	static String getFilterDisplayName( const String& filterClassName );

	static FilterCategories getCategories();

	static Array<String> getFiltersForCategory( const String& category );
protected:
	GLuint fragment_;
	GLuint program_;
	String fragmentFilename_;
	String compileStatus_;

	IKImage* inputImage_;
	IKImage* outputImage_;

	bool insertBuiltins_;

	std::vector<String> inputNames_;
	std::vector<String> outputNames_;
	
	void initProgram( const String& data );

	virtual void initFilterVariables();
	
};







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

class GaussianBlur : public IKFilter {
public:
	enum {
		RADIUS =  7,
		KERNEL_SIZE = (RADIUS * 2 + 1),
	};
	float blurKernel[KERNEL_SIZE];
	float offsets[KERNEL_SIZE*2]; //array of vec2

	GaussianBlur() {

		blurRadius = 7;
		blurAmount = 3.0;

		initFromResource( "GaussianBlur" );		
	}

	int getRadius() {
		return blurRadius;
	}

	void setRadius( const int& val ) {
		blurRadius = val;
	}

	float getAmount() {
		return blurAmount;
	}

	void setAmount( const float& val ) {
		blurAmount = val;
	}
protected:

	int blurRadius;
	float blurAmount;

	virtual void initFilterVariables() {
		IKFilter::initFilterVariables();  
        float sigma = blurRadius / blurAmount;

        float twoSigmaSquare = 2.0f * sigma * sigma;
        float sigmaRoot = sqrt(twoSigmaSquare * 3.1428);
        float total = 0.0f;
        float distance = 0.0f;
        int index = 0;
		int i = 0;

		memset(blurKernel,sizeof(float)*KERNEL_SIZE,0);
		memset(offsets,sizeof(float)*(KERNEL_SIZE*2),0);

        for ( i= -blurRadius; i <= blurRadius; ++i)
        {
            distance = i * i;
            index = i + blurRadius;
            blurKernel[index] =  exp(-distance / twoSigmaSquare) / sigmaRoot;
            total += blurKernel[index];
        }

        for ( i = 0; i < KERNEL_SIZE; ++i)
            blurKernel[i] /= total;

		float xOffset = 1.0f / getInputImage()->getSize().width;
        float yOffset = 1.0f / getInputImage()->getSize().height;

        for ( i = -blurRadius; i <= blurRadius; ++i)
        {
            index = (i + blurRadius) * 2;
            offsets[index] = i * xOffset;
			offsets[index+1] = i * yOffset;
        }


		int location = glGetUniformLocationARB( program_, "blurKernel" );

		glUniform1fvARB( location, KERNEL_SIZE, &blurKernel[0] );

		location = glGetUniformLocationARB( program_, "offsets" );

		glUniform2fvARB( location, KERNEL_SIZE*2, &offsets[0] );
	}
};


class Emboss : public IKFilter {
public:
	Emboss() {		
		displacement = 0.001f;
		intensity = 2.0f;
		initFromResource( "Emboss" );		
	}


	float getDisplacement() {
		return displacement;
	}

	void setDisplacement( const float& val ) {
		displacement = val;
	}

	float getIntensity() {
		return intensity;
	}

	void setIntensity( const float& val ) {
		intensity = val;
	}
protected:
	float displacement;
	float intensity;
};

class Mixer : public IKFilter {
public:
	Mixer(){
		inputNames_.push_back("input2Image"); 

		initFromResource( "Mixer" );
	}

	IKImage* getInput2Image() {
		return input2Image_;
	}

	void setInput2Image( IKImage* val );

	IKImage* input2Image_;
};


class BrightPass : public IKFilter {
public:
	BrightPass(){
		initFromResource( "BrightPass" );
	}

	double getThreshold() {
		return threshold;
	}

	void setThreshold( const double& val ) {
		threshold = val;
	}
	double threshold;

};

class RadialBlur : public IKFilter {
public:
	RadialBlur(){
		
		initFromResource( "RadialBlur" );
	}

	double getCenterX() {
		return centerX;
	}

	void setCenterX( const double& val ) {
		centerX = val;
	}

	double getCenterY() {
		return centerY;
	}

	void setCenterY( const double& val ) {
		centerY = val;
	}

	double getProgress() {
		return progress;
	}

	void setProgress( const double& val ) {
		progress = val;
	}

	int getCount() {
		return count;
	}

	void setCount( const int& val ) {
		count = val;
	}

	double centerX;
	double centerY;
	double progress;
	int count;

};



class Wavy : public IKFilter {
public:
	Wavy(){
		
		initFromResource( "Wavy" );
	}

	double getAmplitude() {
		return amplitude;
	}

	void setAmplitude( const double& val ) {
		amplitude = val;
	}

	double getFrequency() {
		return frequency;
	}

	void setFrequency( const double& val ) {
		frequency = val;
	}

	double amplitude;
	double frequency;
};




class Wavy2 : public IKFilter {
public:
	Wavy2(){
		insertBuiltins_ = true;
		initFromResource( "Wavy2" );
	}

	double getAmount() {
		return amount;
	}

	void setAmount( const double& val ) {
		amount = val;
	}

	double getXAmplitude() {
		return xAmplitude;
	}

	void setXAmplitude( const double& val ) {
		xAmplitude = val;
	}

	double getYAmplitude() {
		return yAmplitude;
	}

	void setYAmplitude( const double& val ) {
		yAmplitude = val;
	}

	double getProgress() {
		return progress;
	}

	void setProgress( const double& val ) {
		progress = val;
	}

	double amount;
	double xAmplitude;
	double yAmplitude;
	double progress;
};



class BlackAndWhite : public IKFilter {
public:
	BlackAndWhite(){
		
		initFromResource( "BlackAndWhite" );
	}

	double getMidpoint() {
		return midpoint;
	}

	void setMidpoint( const double& val ) {
		midpoint = val;
	}

	double midpoint;
};


class Bloom : public IKFilter {
public:
	Bloom(){
		insertBuiltins_ = true;
		initFromResource( "Bloom" );
	}

	double getBloomIntensity() {
		return bloomIntensity;
	}

	void setBloomIntensity( const double& val ) {
		bloomIntensity = val;
	}

	double getBaseIntensity() {
		return baseIntensity;
	}

	void setBaseIntensity( const double& val ) {
		baseIntensity = val;
	}

	double getBloomSaturation() {
		return bloomSaturation;
	}

	void setBloomSaturation( const double& val ) {
		bloomSaturation = val;
	}

	double getBaseSaturation() {
		return baseSaturation;
	}

	void setBaseSaturation( const double& val ) {
		baseSaturation = val;
	}

	double getThreshold() {
		return threshold;
	}

	void setThreshold( const double& val ) {
		threshold = val;
	}
	

	double bloomIntensity;
	double baseIntensity;
	double bloomSaturation;
	double baseSaturation;
	double threshold;
	
};


class Pixelate : public IKFilter {
public:
	Pixelate(){
		insertBuiltins_ = true;
		initFromResource( "Pixelate" );
	}

	double getProgress() {
		return progress;
	}

	void setProgress( const double& val ) {
		progress = val;
	}
	double progress;
	
};


class LightStreak : public IKFilter {
public:
	LightStreak(){
		insertBuiltins_ = true;
		initFromResource( "LightStreak" );
	}

	double getBrightThreshold() {
		return brightThreshold;
	}

	void setBrightThreshold( const double& val ) {
		brightThreshold = val;
	}

	double getScale() {
		return scale;
	}

	void setScale( const double& val ) {
		scale = val;
	}

	double getAttenuation() {
		return attenuation;
	}

	void setAttenuation( const double& val ) {
		attenuation = val;
	}

	double getXDirection() {
		return xDirection;
	}

	void setXDirection( const double& val ) {
		xDirection = val;
	}

	double getYDirection() {
		return yDirection;
	}

	void setYDirection( const double& val ) {
		yDirection = val;
	}

	double getPixelWidth() {
		return pixelWidth;
	}

	void setPixelWidth( const double& val ) {
		pixelWidth = val;
	}

	double getPixelHeight() {
		return pixelHeight;
	}

	void setPixelHeight( const double& val ) {
		pixelHeight = val;
	}

	int getNumSamples() {
		return numSamples;
	}

	void setNumSamples( const int& val ) {
		numSamples = val;
	}

	int getIteration() {
		return iteration;
	}

	void setIteration( const int& val ) {
		iteration = val;
	}

	double brightThreshold;
	double scale;
	double attenuation;
	double xDirection;
	double yDirection;
    double pixelWidth;
	double pixelHeight;
    int numSamples;
	int iteration;
};



class Ripple : public IKFilter {
public:
	Ripple(){
		insertBuiltins_ = true;
		initFromResource( "Ripple" );
	}

	double getCenterX() {
		return centerX;
	}

	void setCenterX( const double& val ) {
		centerX = val;
	}

	double getCenterY() {
		return centerY;
	}

	void setCenterY( const double& val ) {
		centerY = val;
	}

	double getAmplitude() {
		return amplitude;
	}

	void setAmplitude( const double& val ) {
		amplitude = val;
	}

	double getFrequency() {
		return frequency;
	}

	void setFrequency( const double& val ) {
		frequency = val;
	}

	double getPhase() {
		return phase;
	}

	void setPhase( const double& val ) {
		phase = val;
	}

	double centerX;
	double centerY;
	double amplitude;
	double frequency;
	double phase;
};



class Swirl : public IKFilter {
public:
	Swirl(){
		insertBuiltins_ = true;
		initFromResource( "Swirl" );
	}

	double getCenterX() {
		return centerX;
	}

	void setCenterX( const double& val ) {
		centerX = val;
	}

	double getCenterY() {
		return centerY;
	}

	void setCenterY( const double& val ) {
		centerY = val;
	}

	double getSpiralStrength() {
		return spiralStrength;
	}

	void setSpiralStrength( const double& val ) {
		spiralStrength = val;
	}

	double getXFrequency() {
		return xFrequency;
	}

	void setXFrequency( const double& val ) {
		xFrequency = val;
	}

	double getYFrequency() {
		return yFrequency;
	}

	void setYFrequency( const double& val ) {
		yFrequency = val;
	}

	double centerX;
	double centerY;
	double spiralStrength;
	double xFrequency;
	double yFrequency;
};

class Pinch : public IKFilter {
public:
	Pinch(){
		insertBuiltins_ = true;
		initFromResource( "Pinch" );
	}

	double getCenterX() {
		return centerX;
	}

	void setCenterX( const double& val ) {
		centerX = val;
	}

	double getCenterY() {
		return centerY;
	}

	void setCenterY( const double& val ) {
		centerY = val;
	}

	double getRadius() {
		return radius;
	}

	void setRadius( const double& val ) {
		radius = val;
	}

	double getAmount() {
		return amount;
	}

	void setAmount( const double& val ) {
		amount = val;
	}

	double centerX;
	double centerY;
	double radius;
	double amount;	
};



class DirectionalBlur : public IKFilter {
public:
	DirectionalBlur(){
		insertBuiltins_ = true;
		initFromResource( "DirectionalBlur" );
	}

	double getAngle() {
		return angle;
	}

	void setAngle( const double& val ) {
		angle = val;
	}

	double getAmount() {
		return amount;
	}

	void setAmount( const double& val ) {
		amount = val;
	}

	double angle;
	double amount;	
};
};


#endif //_VCF_IMAGEKIT_H__