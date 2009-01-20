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

	static FilterCategories getCategories();

	static Array<String> getFiltersForCategory( const String& category );
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

	virtual void initFilterVariables();

	typedef std::map<String,IKFilterInfo> FilterMap;

	static FilterMap registeredFilters;

	
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

	int blurRadius;
	float blurAmount;
protected:
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


};


#endif //_VCF_IMAGEKIT_H__