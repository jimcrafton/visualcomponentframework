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



/**
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

	static ContextPeer* createContextPeer( const unsigned long& width, const unsigned long& height ) ;

	static ContextPeer* createContextPeer( const unsigned long& contextID );

	static FontPeer* createFontPeer( const String& fontName );

	static FontPeer* createFontPeer( const String& fontName, const double& pointSize );

	static Image* createImage( const unsigned long& width, const unsigned long& height );

	static Image* createImage( GraphicsContext* context, Rect* rect );

	/**
	*Create a image from a filename. The file is loaded into a Bitmap instance.
	*The toolkit looks up the file extension and matches the type to
	*an ImageLoader instance. The ImageLoader does the work of actually decoding the image
	*/
	static Image* createImage( const String& fileName );

	static void saveImage( const String& fileName, Image* image );

	static void registerImageLoader( const String& name, ImageLoader* imageLoader );

	static ImageLoader* getImageLoader( const String& contentType );

	static ImageLoader* getImageLoaderForFileName( const String& fileName );

	static Color* getSystemColor( const unsigned long& systemColor );

	static String getSystemColorNameFromMap( Color& color ) ;

	static String getColorNameFromMap( const Color& color ) ;

	static Color* getColorFromColormap( const int& gray );

	static Color* getColorFromColormap( const String& colorName );

	/*
	*Find the named color closest to a color with a given RGB value
	*/
	static Color* getColorMatchFromColormap( const Color& color );

	/*
	*Find a color with a given luminosity contrast with another given color
	*/
	static Color getColorContrast( const Color& clrRef, double deltaL = 0.3 );

	static void printColorNameMap( ) ;

	static Enumerator<FontInfo>* getAvailableSystemFonts();

	static Font* getDefaultSystemFont() ;

	static double getDPI();

	static void initGraphicsToolkit();

	static void terminate();

	static bool getAvailableImageTypes( std::vector< std::pair<String,String> >& contentTypes );

	static GraphicsToolkit* internal_getDefaultGraphicsToolkit();

protected:
	virtual ContextPeer* internal_createContextPeer( const unsigned long& width, const unsigned long& height ) = 0;

	virtual ContextPeer* internal_createContextPeer( const unsigned long& contextID ) = 0;

	virtual FontPeer* internal_createFontPeer( const String& fontName )  = 0;

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize )  = 0;

	virtual Image* internal_createImage( const unsigned long& width, const unsigned long& height ) = 0;

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect ) = 0;

	/**
	*Create a image from a filename. The file is loaded into a Bitmap instance.
	*The toolkit looks up the file extension and matches the type to
	*an ImageLoader instance. The ImageLoader does the work of actually decoding the image
	*/
	virtual Image* internal_createImage( const String& fileName );

	virtual void internal_saveImage( const String& fileName, Image* image );

	void internal_registerImageLoader( const String& name, ImageLoader* imageLoader );

	virtual Color* internal_getSystemColor( const unsigned long& systemColor );

	virtual String internal_getSystemColorNameFromMap( Color& color ) const ;

	virtual String internal_getColorNameFromMap( const Color& color ) const ;

	virtual Font* internal_getDefaultSystemFont() {
		return NULL;
	}

	virtual double internal_getDPI() {
		return -1.0;
	};




	ImageLoader* internal_getImageLoader( const String& contentType );

	ImageLoader* internal_getImageLoaderForFileName( const String& fileName );

	Color* internal_getColorFromColormap( const int& gray );

	Color* internal_getColorFromColormap( const String& colorName );

	/*
	*Find the named color closest to a color with a given RGB value
	*/
	Color* internal_getColorMatchFromColormap( const Color& color );

	/*
	*Find a color with a given luminosity contrast with another given color
	*/
	Color internal_getColorContrast( const Color& clrRef, double deltaL = 0.3 );

	void internal_printColorNameMap( ) const ;

	Enumerator<FontInfo>* internal_getAvailableSystemFonts() {
		return fontInfoContainer_.getEnumerator();
	}





	/**
	this will auto create our list for us - and is the only place where it can be created
	initialization will happen in the ColorNames constructor
	*/
	//ColorNames colorNames_;

	std::map<String,String> contentTypes_;

	MapStringColor colorMap_;
	MapStringColorName* colorNameMap_;

	void initColorMap();
	void initColorNameMapItem( const VCF::String& colorName, const unsigned char & r, const unsigned char & g, const unsigned char & b);
	void destroyColorMaps();

	std::map<unsigned long,Color*> systemColors_;
	MapStringColorName* systemColorNameMap_;
	void destroySystemColorNameMap();

	std::vector<FontInfo> availableSystemFonts_;
	EnumeratorContainer<std::vector<FontInfo>,FontInfo> fontInfoContainer_;


	/**
	this method should be overridden by implementers of the graphics toolkit
	and should initialize the availableSystemFonts_ vector with a series of
	FontInfo instances.
	*/
	virtual void initSystemFontNames() {};

	void initContentTypes();

	static GraphicsToolkit* graphicsToolkitInstance;
	/**
	*ImageLoaders are stored in map, keyed by the MIME content type
	*Thus JPEG loaders are stored under the key:
	*<p><pre>
	*	"image/jpeg"
	*</pre></p>
	*/
	std::map<String, ImageLoader*> imageLoaders_;
};

};	// namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/29 03:58:47  marcelloptr
*Improvements on Color class - changes so to have Color::getColor inlined
*
*Revision 1.1.2.5  2004/06/25 19:52:48  marcelloptr
*adjusted macros and other changes for better performance
*
*Revision 1.1.2.4  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/29 21:13:58  ddiego
*made a few changes to the new OpenGLKit files, adjusting where the
*CVS log was put, and changed a few cases for the export-import definition
*was used. Also added the two projects to the vcfAllProject workspace
*and added the script generated VC7 and VC71 projects as well.
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.11.4.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.2.3  2003/10/28 04:06:12  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.10.2.2  2003/09/24 00:38:47  ddiego
*added a way to get all the registered image loader types
*
*Revision 1.10.2.1  2003/08/14 20:29:51  marcelloptr
*bug [788927] TextControl::getSelectedText() return all text if no text selected
*
*Revision 1.10  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.9.2.2  2003/08/02 00:41:12  marcelloptr
*fixes for vc6;  improved dependencies
*
*Revision 1.9.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.9  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.3  2003/04/17 04:29:49  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.8.2.2  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.2.1  2003/03/12 03:11:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.2.5  2003/02/20 02:46:02  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Revision 1.7.2.4  2003/01/08 04:25:56  marcelloptr
*ColorNames static map and Color::s_ now use String instead than String* - VCF_LARGE_COLOR_LIST introduced
*
*Revision 1.7.2.3  2002/12/30 21:48:07  ddiego
*miscellaneous fixes to the ColorNames class. Adjusted the way it looks up colors
*and got rid of some of the extern variables, also removed the pragma lib in the
*color.cpp file
*
*: ----------------------------------------------------------------------
*
*Revision 1.7.2.2  2002/12/28 22:51:32  marcelloptr
*Color Spaces transformations and Color Names
*
*Revision 1.7.2.1  2002/12/27 23:04:44  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.7  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.6.4.1  2002/09/28 22:22:46  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.6  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.5.12.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_GRAPHICSTOOLKIT_H__


