//X11GraphicsToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//X11GraphicsToolkit.h
#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"


using namespace VCF;




X11GraphicsToolkit::X11GraphicsToolkit():
	X11Display_(NULL),
	X11ScreenID_(-1)

{


	GraphicsToolkit::graphicsToolkitInstance = this;
	loadSystemColors();
	//registerImageLoader( "image/xpm", new XPMLoader() );

	String displayName = getenv( "DISPLAY" );
	if ( true == displayName.empty() ) {
		displayName = ":0.0";
	}

	X11Display_ = XOpenDisplay( displayName.c_str() );
	if ( NULL == X11Display_ ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2( "XOpenDisplay returned a NULL display, display name (" +
									displayName + ") is probably wrong" ) );

	}

	imlib_context_set_display(X11Display_);

	X11ScreenID_ = DefaultScreen( X11Display_ );


	//initialize some basic imlib2 parameters
	Colormap colorMap = DefaultColormap( X11Display_, X11ScreenID_ );

	imlib_context_set_visual( DefaultVisual(X11Display_, X11ScreenID_) );


	imlib_context_set_colormap(colorMap);

	/* set the font cache to 512Kb - again to avoid re-loading */
	imlib_set_font_cache_size(512 * 1024);
	imlib_context_set_anti_alias( 1 );

	//set up the font directories

	/**
	1) add the path /usr/local/share/fonts - this is where all the
	common shared system fonts should be
	*/
	String dir = getSharedFontsPath();
	imlib_add_path_to_font_path( dir.c_str() );

	/**
	2) add the path $HOME/fonts - this is where all the
	user's fonts should be
	*/
	dir = getUserFontsPath();
	imlib_add_path_to_font_path( dir.c_str() );

	/**
	3) add the path(s) in the VCF_FONTS environment variable if it exists
	*/
	String vcfFonts = System::getEnvironmentVariable( "VCF_FONTS" );
	if ( !vcfFonts.empty() ) {
		int pos = vcfFonts.find(":");
		if ( pos == String::npos ) {
			imlib_add_path_to_font_path( vcfFonts.c_str() );
		}
		else {
			while ( pos != String::npos ) {
				dir = vcfFonts.substr( 0, pos );
				imlib_add_path_to_font_path( dir.c_str() );

				vcfFonts.erase( 0, pos + 1 );
				pos = vcfFonts.find(":");
			}

			if ( !vcfFonts.empty() ) {
				imlib_add_path_to_font_path( vcfFonts.c_str() );
			}
		}
	}



	imlib_set_color_usage(128);
	imlib_context_set_dither(1);


	initSystemFont();
}

X11GraphicsToolkit::~X11GraphicsToolkit()
{
	systemFont_->free();

	if ( !colorLookupMap_.empty() ) {
		unsigned long*  pixels = new unsigned long[colorLookupMap_.size()+1];
		memset( pixels, 0, (colorLookupMap_.size()+1) * sizeof(unsigned long) );

		Colormap colorMap = DefaultColormap( X11Display_, X11ScreenID_ );

		//get rid of all the colors
		std::map<ulong32,ulong32>::iterator it = colorLookupMap_.begin();
		int index = 0;
		while ( it != colorLookupMap_.end() ) {

			if ( (it->second != BlackPixel(X11Display_, X11ScreenID_)) && (it->second != WhitePixel(X11Display_, X11ScreenID_)) ) {
				pixels[index] = it->second;
				index ++;
			}
			it ++;
		}

		XFreeColors ( X11Display_, colorMap, pixels, index, 0 );

		delete [] pixels;

		colorLookupMap_.clear();
	}

	XCloseDisplay( X11Display_ );
}

void X11GraphicsToolkit::initSystemFont()
{
	systemFont_ = new Font( "ARIAL", 10 );
	/*
	systemFont_->setAngle( 0.0 );
	systemFont_->setBold( false );
	systemFont_->setItalic( false );
	systemFont_->setUnderlined( false );
	systemFont_->setStrikeOut( false );
	systemFont_->setPixelSize( 10 );
	systemFont_->setName( String( "Arial" ) );
	*/
}

ContextPeer* X11GraphicsToolkit::createContextPeer( const long& contextID )
{
	ContextPeer* result = NULL;

	result = new X11Context( contextID );

	return result;
}

ContextPeer* X11GraphicsToolkit::createContextPeer( const unsigned long& width, const unsigned long& height )
{
	return new X11Context( width, height );
}

FontPeer* X11GraphicsToolkit::createFontPeer( const String& fontName )
{
	return new X11Font( fontName );
}

FontPeer* X11GraphicsToolkit::createFontPeer( const String& fontName, const double& pointSize )
{
	return new X11Font( fontName, pointSize );
}

OpenGLPeer* X11GraphicsToolkit::createOpenGLPeer( GraphicsContext* glContext )
{
#ifdef VCF_OPENGL
	return new X11OpenGLPeer( glContext );
#else
	return NULL;
#endif
}

Image* X11GraphicsToolkit::createImage( const unsigned long& width, const unsigned long& height )
{
	return new X11Image( width, height );
}

Image* X11GraphicsToolkit::createImage( GraphicsContext* context, Rect* rect  )
{
	if ( NULL != context ){
		return new X11Image( context, rect );
	}
	else {
		return NULL;
	}
}


void X11GraphicsToolkit::loadSystemColors()
{

/*	default colors from a windows standard color settings
	use these as defaults until ew find a better way to
	load up stuff from the x resources
	COLOR_WINDOW:                   1.0000, 1.0000, 1.0000
	COLOR_3DDKSHADOW:               0.2510, 0.2510, 0.2510
	COLOR_3DFACE:                   0.8314, 0.8157, 0.7843
	COLOR_BTNFACE:                  0.8314, 0.8157, 0.7843
	COLOR_3DHILIGHT:                1.0000, 1.0000, 1.0000
	COLOR_3DHIGHLIGHT:              1.0000, 1.0000, 1.0000
	COLOR_BTNHILIGHT:               1.0000, 1.0000, 1.0000
	COLOR_BTNHIGHLIGHT:             1.0000, 1.0000, 1.0000
	COLOR_3DLIGHT:                  0.8314, 0.8157, 0.7843
	COLOR_3DSHADOW:                 0.5020, 0.5020, 0.5020
	COLOR_BTNSHADOW:                0.5020, 0.5020, 0.5020
	COLOR_ACTIVEBORDER:             0.8314, 0.8157, 0.7843
	COLOR_ACTIVECAPTION:            0.0392, 0.1412, 0.4157
	COLOR_APPWORKSPACE:             0.5020, 0.5020, 0.5020
	COLOR_BACKGROUND:               0.2275, 0.4314, 0.6471
	COLOR_DESKTOP:                  0.2275, 0.4314, 0.6471
	COLOR_BTNTEXT:                  0.0000, 0.0000, 0.0000
	COLOR_CAPTIONTEXT:              1.0000, 1.0000, 1.0000
	COLOR_GRAYTEXT:                 0.5020, 0.5020, 0.5020
	COLOR_HIGHLIGHT:                0.0392, 0.1412, 0.4157
	COLOR_HIGHLIGHTTEXT:            1.0000, 1.0000, 1.0000
	COLOR_INACTIVEBORDER:           0.8314, 0.8157, 0.7843
	COLOR_INACTIVECAPTION:          0.5020, 0.5020, 0.5020
	COLOR_INACTIVECAPTIONTEXT:      0.8314, 0.8157, 0.7843
	COLOR_INFOBK:                   1.0000, 1.0000, 0.8824
	COLOR_INFOTEXT:                 0.0000, 0.0000, 0.0000
	COLOR_MENU:                     0.8314, 0.8157, 0.7843
	COLOR_MENUTEXT:                 0.0000, 0.0000, 0.0000
	COLOR_WINDOWFRAME:              0.0000, 0.0000, 0.0000
	COLOR_WINDOWTEXT:               0.0000, 0.0000, 0.0000
*/


	Color* sysColor = NULL;
	sysColor = new Color( 0.3176470588235294, 0.3333333333333333, 0.3176470588235294 );//Get X11 equiv for ::GetSysColor( COLOR_BTNSHADOW ) );
	systemColors_[SYSCOLOR_SHADOW] = sysColor;

	sysColor = new Color( 0.6666666666666666, 0.6666666666666666, 0.6666666666666666 );///Get X11 equiv for ::GetSysColor( COLOR_3DFACE ) );
	systemColors_[SYSCOLOR_FACE] = sysColor;

	sysColor = new Color( 1.0000, 1.0000, 1.0000 );//Get X11 equiv for ::GetSysColor( COLOR_3DHILIGHT ) );
	systemColors_[SYSCOLOR_HIGHLIGHT] = sysColor;

	sysColor = new Color( 0.0392, 0.1412, 0.4157 );//Get X11 equiv for ::GetSysColor( COLOR_ACTIVECAPTION ) );
	systemColors_[SYSCOLOR_ACTIVE_CAPTION] = sysColor;

	sysColor = new Color( 0.8314, 0.8157, 0.7843 );//Get X11 equiv for ::GetSysColor( COLOR_ACTIVEBORDER ) );
	systemColors_[SYSCOLOR_ACTIVE_BORDER] = sysColor;

	sysColor = new Color( 0.2275, 0.4314, 0.6471 );//Get X11 equiv for ::GetSysColor( COLOR_DESKTOP ) );
	systemColors_[SYSCOLOR_DESKTOP] = sysColor;

	sysColor = new Color( 1.0000, 1.0000, 1.0000 );//Get X11 equiv for ::GetSysColor( COLOR_CAPTIONTEXT ) );
	systemColors_[SYSCOLOR_CAPTION_TEXT] = sysColor;

	sysColor = new Color( 0.0392, 0.1412, 0.4157 );//Get X11 equiv for ::GetSysColor( COLOR_HIGHLIGHT ) );
	systemColors_[SYSCOLOR_SELECTION] = sysColor;

	sysColor = new Color( 1.0000, 1.0000, 1.0000 );//Get X11 equiv for ::GetSysColor( COLOR_HIGHLIGHTTEXT ) );
	systemColors_[SYSCOLOR_SELECTION_TEXT] = sysColor;

	sysColor = new Color( 0.8314, 0.8157, 0.7843 );//Get X11 equiv for ::GetSysColor( COLOR_INACTIVEBORDER ) );
	systemColors_[SYSCOLOR_INACTIVE_BORDER] = sysColor;

	sysColor = new Color( 0.5020, 0.5020, 0.5020 );//Get X11 equiv for ::GetSysColor( COLOR_INACTIVECAPTION ) );
	systemColors_[SYSCOLOR_INACTIVE_CAPTION] = sysColor;

	sysColor = new Color( 1.0000, 1.0000, 0.8824 );//Get X11 equiv for ::GetSysColor( COLOR_INFOBK ) );
	systemColors_[SYSCOLOR_TOOLTIP] = sysColor;

	sysColor = new Color( 0.0000, 0.0000, 0.0000 );//Get X11 equiv for ::GetSysColor( COLOR_INFOTEXT ) );
	systemColors_[SYSCOLOR_TOOLTIP_TEXT] = sysColor;

	sysColor = new Color( 0.8314, 0.8157, 0.7843 );//Get X11 equiv for ::GetSysColor( COLOR_MENU ) );
	systemColors_[SYSCOLOR_MENU] = sysColor;

	sysColor = new Color( 0.0000, 0.0000, 0.0000 );//Get X11 equiv for ::GetSysColor( COLOR_MENUTEXT ) );
	systemColors_[SYSCOLOR_MENU_TEXT] = sysColor;

	sysColor = new Color( 1.0000, 1.0000, 1.0000 );//Get X11 equiv for ::GetSysColor( COLOR_WINDOW ) );
	systemColors_[SYSCOLOR_WINDOW] = sysColor;

	sysColor = new Color( 0.0000, 0.0000, 0.0000 );//Get X11 equiv for ::GetSysColor( COLOR_WINDOWTEXT ) );
	systemColors_[SYSCOLOR_WINDOW_TEXT] = sysColor;

	sysColor = new Color( 0.0000, 0.0000, 0.0000 );//Get X11 equiv for ::GetSysColor( COLOR_WINDOWFRAME ) );
	systemColors_[SYSCOLOR_WINDOW_FRAME] = sysColor;


}

void X11GraphicsToolkit::initSystemFontNames()
{

}

ulong32 X11GraphicsToolkit::getPixelForColor( Color* color )
{
	ulong32 result = 0;

	uint8 red, green, blue;
	color->getRGB8( red, green, blue );
	//in the future we can get an alpha value

	ulong32 key = red;
	key << 8;
	key += green;

	key << 8;
	key += blue;

	std::map<ulong32,ulong32>::iterator found = colorLookupMap_.find( key );
	if ( found != colorLookupMap_.end() ) {
		result = found->second;
	}
	else {
		Colormap colorMap = DefaultColormap( X11Display_, X11ScreenID_ );
		XColor xColor;
		xColor.red = red * 65535 / 255;
		xColor.green = green * 65535 / 255;
		xColor.blue = blue * 65535 / 255;
		xColor.flags = DoRed | DoGreen | DoBlue;

		if ( ! XAllocColor ( X11Display_, colorMap, &xColor ) ) {
			throw RuntimeException( MAKE_ERROR_MSG_2( "X Color allocation failed" ) );
		}
		else {

		}
		result = xColor.pixel;
		colorLookupMap_[key] = result;
	}

	return result;
}

double X11GraphicsToolkit::getDPI()
{
	double mmHeight = DisplayHeightMM( X11Display_, X11ScreenID_ );
	double height = DisplayHeight( X11Display_, X11ScreenID_ );

	//where 1 inch = 2.54 cm
	double result = height / (mmHeight / 25.4);
	return result;
}

String X11GraphicsToolkit::getSharedFontsPath()
{
	return "/usr/local/share/fonts";
}

String X11GraphicsToolkit::getUserFontsPath()
{
	String result = System::getEnvironmentVariable( "HOME" );

	result += "/fonts";
	return result;
}


/**
$Id$
*/
