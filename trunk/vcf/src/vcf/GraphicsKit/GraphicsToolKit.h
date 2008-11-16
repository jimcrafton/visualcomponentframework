#ifndef _VCF_GRAPHICSTOOLKIT_H__
#define _VCF_GRAPHICSTOOLKIT_H__
//GraphicsToolKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class Rect;
class Color;
class Image;
class ImageLoader;
class ContextPeer;
class GraphicsContext;
class Font;
class FontPeer;
class GraphicsResourceBundle;
class PrintSessionPeer; 
class GraphicsResourceBundlePeer;
class UIMetricsManager;

/**
\class FontInfo GraphicsToolKit.h "vcf/GraphicsKit/GraphicsToolKit.h"
Use this class to retreive information about a loaded system
font. This class is intended for read only purposes
*/
class GRAPHICSKIT_API FontInfo {
public:
	FontInfo(){}

	FontInfo( const String& aName, const String& aFileName ):
		name_(aName),
		fileName_( aFileName ){}

	FontInfo( const FontInfo& fi ) {
		*this = fi;
	}

	FontInfo& operator=( const FontInfo& rhs ) {
		name_ = rhs.name_;
		fileName_ = rhs.fileName_;
		return *this;
	}

	bool operator == ( const FontInfo& rhs ) const {
		return (name_ == rhs.name_) && (fileName_ == rhs.fileName_);
	}

	bool operator > ( const FontInfo& rhs ) const {
		return (name_ > rhs.name_) && (fileName_ > rhs.fileName_);
	}

	bool operator < ( const FontInfo& rhs ) const {
		return (name_ < rhs.name_) && (fileName_ < rhs.fileName_);
	}

	bool operator != ( const FontInfo& rhs ) const {
		return (name_ != rhs.name_) && (fileName_ != rhs.fileName_);
	}

	/**
	returns the human readable name of the font, such as "Arial", or
	"Century Schoolbook L". This is the name that should be used by the
	Font::setName() and will match when calling the Font::getName()
	*/
	String name() const {
		return name_;
	}


	/**
	This returns the fully qualified file name for the font. This will differ
	greatly from the name returned by FontInfo;;name() or Font::getName().
	For example the name of the font might be "Century Schoolbook L", while the file
	name might be /usr/share/fonts/default/Type1/c0590131.pfb
	*/
	String fileName() const {
		return fileName_;
	}

protected:
	String name_;
	String fileName_;
};



/**
\class GraphicsToolkit GraphicsToolKit.h "vcf/GraphicsKit/GraphicsToolKit.h"
The GraphicsToolkit serves as a way to retreive basic system information
and as a factory for creating various graphics peers, like the ContextPeer,
FontPeer, and the system implementation the Image class
*/
class GRAPHICSKIT_API GraphicsToolkit : public Object{
public:

	typedef std::map<String,Color*> MapStringColor;
	typedef std::map<Color, VCF::String> MapStringColorName;



	GraphicsToolkit();

	virtual ~GraphicsToolkit();

	static ContextPeer* createContextPeer( const uint32& width, const uint32& height ) ;

	static ContextPeer* createContextPeer( OSHandleID contextID );

	static ContextPeer* createContextPeer( Image* image );

	static FontPeer* createFontPeer( const String& fontName );

	static FontPeer* createFontPeer( const String& fontName, const double& pointSize );

	static Image* createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType = Image::itColor );

	static Image* createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType = Image::itColor );	

	static PrintSessionPeer* createPrintSessionPeer();

	static GraphicsResourceBundlePeer* createGraphicsResourceBundlePeer();

	static GraphicsResourceBundle* getResourceBundle();


	/**
	*Create a image from a filename. The file is loaded into a Bitmap instance.
	*The toolkit looks up the file extension and matches the type to
	*an ImageLoader instance. The ImageLoader does the work of actually decoding the image
	*/
	static Image* createImage( const String& fileName );

	static Image* createImage( const MIMEType& type, const unsigned char* imageData, const uint64& dataLength );

	static Image* createImage( const MIMEType& type, InputStream* stream );

	static void saveImage( const String& fileName, Image* image );

	static void registerImageLoader( const String& name, ImageLoader* imageLoader );

	static ImageLoader* getImageLoader( const String& contentType );

	static ImageLoader* getImageLoaderForFileName( const String& fileName );

	static Color* getSystemColor( const uint32& systemColor );

	static String getSystemColorNameFromMap( Color& color ) ;

	static String getColorNameFromMap( const Color& color ) ;

	static Color* getColorFromColormap( const int& gray );

	static Color* getColorFromColormap( const String& colorName );

	/**
	finds the named color closest to another given one.
	@param const Color& color, the given color.
	@return Color*, the closest color found. The color itself if it is 
	in the map.
	*/
	static Color* getColorMatchFromColormap( const Color& color );

	static void printColorNameMap( ) ;

	static Enumerator<FontInfo>* getAvailableSystemFonts();

	static Font* getDefaultSystemFont() ;

	/**
	Returns the crurent DPI for the screen if the context
	parameter is NULL, otherwise returns the dpi that 
	is used by the graphics context.
	*/
	static double getDPI( GraphicsContext* context = NULL );

	static void initGraphicsToolkit();

	static void terminate();

	static bool getAvailableImageTypes( std::vector< std::pair<String,String> >& contentTypes );

	static UIMetricsManager* getUIMetricsManager();

	static double getUIMetricValue( const UIMetricsManager::MetricType& type, const String& text="", Font* alternateFont=NULL );

	static Size getUIMetricSize( const UIMetricsManager::MetricType& type, const String& text="", Font* alternateFont=NULL );

	static Rect getUIMetricRect( const UIMetricsManager::MetricType& type, Rect* rect=NULL, Font* alternateFont=NULL );


	static GraphicsToolkit* internal_getDefaultGraphicsToolkit();

	/**
	Call this function if you need to reload various toolkit 
	resoruces due to a systems settings changes, for example
	teh user enabling or disabling themes.
	*/
	static void systemSettingsChanged();
protected:
	virtual ContextPeer* internal_createContextPeer( const uint32& width, const uint32& height ) = 0;

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID ) = 0;

	virtual ContextPeer* internal_createContextPeer( Image* image ) = 0;

	virtual FontPeer* internal_createFontPeer( const String& fontName )  = 0;

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize )  = 0;

	virtual Image* internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType ) = 0;

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType ) = 0;

	virtual PrintSessionPeer* internal_createPrintSessionPeer() = 0;

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer() = 0;

	virtual double internal_getDPI( GraphicsContext* context ) = 0;


	virtual void internal_systemSettingsChanged() = 0;

	/**
	*Create a image from a filename. The file is loaded into a Bitmap instance.
	*The toolkit looks up the file extension and matches the type to
	*an ImageLoader instance. The ImageLoader does the work of actually decoding the image
	*/
	virtual Image* internal_createImage( const String& fileName );

	virtual Image* internal_createImage( const MIMEType& type, const unsigned char* imageData, const uint64& dataLength );

	virtual Image* internal_createImage( const MIMEType& type, InputStream* stream );

	virtual void internal_saveImage( const String& fileName, Image* image );

	void internal_registerImageLoader( const String& name, ImageLoader* imageLoader );

	virtual Color* internal_getSystemColor( const uint32& systemColor );

	virtual String internal_getSystemColorNameFromMap( Color& color ) const ;

	virtual String internal_getColorNameFromMap( const Color& color ) const ;

	virtual Font* internal_getDefaultSystemFont() {
		return NULL;
	}






	ImageLoader* internal_getImageLoader( const String& contentType );

	ImageLoader* internal_getImageLoaderForFileName( const String& fileName );

	Color* internal_getColorFromColormap( const int& gray );

	Color* internal_getColorFromColormap( const String& colorName );

	/**
	* finds the named color closest to a color with a given RGB value
	*/
	Color* internal_getColorMatchFromColormap( const Color& color );

	/**
	* helper function to print the color map. Used for debugging purposes.
	*/
	void internal_printColorNameMap( ) const ;

	Enumerator<FontInfo>* internal_getAvailableSystemFonts() {
		return fontInfoContainer_.getEnumerator();
	}





	/**
	maps for colors
	*/
	MapStringColor colorMap_;
	MapStringColorName* colorNameMap_;

	void initColorMap();
	void initColorNameMapItem( const VCF::String& colorName, const uint8& r, const uint8& g, const uint8& b );
	void destroyColorMaps();

	std::map<uint32,Color*> systemColors_;
	MapStringColorName* systemColorNameMap_;
	void destroySystemColorNameMap();

	std::vector<FontInfo> availableSystemFonts_;
	EnumeratorContainer<std::vector<FontInfo>,FontInfo> fontInfoContainer_;


	std::map<String,String> contentTypes_;

	UIMetricsManager* metricsMgr_;


	/**
	this method should be overridden by implementers of the graphics toolkit
	and should initialize the availableSystemFonts_ vector with a series of
	FontInfo instances.
	*/
	virtual void initSystemFontNames() {};

	void initContentTypes();

	static GraphicsToolkit* graphicsToolkitInstance;
	/**
	ImageLoaders are stored in a map, keyed by the MIME content type
	Thus JPEG loaders are stored under the key:
	\code
		"image/jpeg"
	\endcode
	*/
	std::map<String, ImageLoader*> imageLoaders_;
};

};	// namespace VCF


#endif // _VCF_GRAPHICSTOOLKIT_H__

/**
$Id$
*/
