//GraphicsToolKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/JPEGLoader.h"
#include "vcf/GraphicsKit/PNGLoader.h"


using namespace VCF;


GraphicsToolkit::GraphicsToolkit()
{
	GraphicsToolkit::graphicsToolkitInstance = this;

	initContentTypes();

	colorNameMap_       = new MapStringColorName();
	systemColorNameMap_ = new MapStringColorName();

	initColorMap();

	fontInfoContainer_.initContainer( availableSystemFonts_ );		
}

GraphicsToolkit::~GraphicsToolkit()
{
	destroySystemColorNameMap();

	std::map<uint32,Color*>::iterator it = systemColors_.begin();
	while ( it != systemColors_.end() ){
		delete it->second;
		it++;
	}
	systemColors_.clear();

	destroyColorMaps();

	std::map<String,ImageLoader*>::iterator it3 = imageLoaders_.begin();
	while ( it3 != imageLoaders_.end() ){
		delete it3->second;
		it3->second = NULL;
		it3 ++;
	}
	imageLoaders_.clear();

	availableSystemFonts_.clear();
}



ContextPeer* GraphicsToolkit::createContextPeer( const uint32& width, const uint32& height )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createContextPeer( width, height );
}

ContextPeer* GraphicsToolkit::createContextPeer( OSHandleID contextID )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createContextPeer( contextID );
}

FontPeer* GraphicsToolkit::createFontPeer( const String& fontName )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createFontPeer( fontName );
}

FontPeer* GraphicsToolkit::createFontPeer( const String& fontName, const double& pointSize )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createFontPeer( fontName, pointSize );
}


Image* GraphicsToolkit::createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createImage( width, height, imageType );
}

Image* GraphicsToolkit::createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createImage( context, rect, imageType );
}

Image* GraphicsToolkit::createImage( const String& fileName )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createImage( fileName );
}

PrintSessionPeer* GraphicsToolkit::createPrintSessionPeer()
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createPrintSessionPeer();
}

GraphicsResourceBundle* GraphicsToolkit::getResourceBundle()
{
	return dynamic_cast<GraphicsResourceBundle*>( System::getResourceBundle() );
}



void GraphicsToolkit::saveImage( const String& fileName, Image* image )
{
	GraphicsToolkit::graphicsToolkitInstance->internal_saveImage( fileName, image );
}

void GraphicsToolkit::registerImageLoader( const String& name, ImageLoader* imageLoader )
{
	GraphicsToolkit::graphicsToolkitInstance->internal_registerImageLoader( name, imageLoader );
}

ImageLoader* GraphicsToolkit::getImageLoader( const String& contentType )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getImageLoader( contentType );
}

ImageLoader* GraphicsToolkit::getImageLoaderForFileName( const String& fileName )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getImageLoaderForFileName( fileName );
}

Color* GraphicsToolkit::getSystemColor( const uint32& systemColor )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getSystemColor( systemColor );
}

String GraphicsToolkit::getSystemColorNameFromMap( Color& color )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getSystemColorNameFromMap( color );
}

String GraphicsToolkit::getColorNameFromMap( const Color& color )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getColorNameFromMap( color );
}

Color* GraphicsToolkit::getColorFromColormap( const int& gray )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getColorFromColormap( gray );
}

Color* GraphicsToolkit::getColorFromColormap( const String& colorName )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getColorFromColormap( colorName );
}

Color* GraphicsToolkit::getColorMatchFromColormap( const Color& color )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getColorMatchFromColormap( color );
}

void GraphicsToolkit::printColorNameMap( )
{
	GraphicsToolkit::graphicsToolkitInstance->internal_printColorNameMap();
}

Enumerator<VCF::FontInfo>* GraphicsToolkit::getAvailableSystemFonts()
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getAvailableSystemFonts();
}

VCF::Font* GraphicsToolkit::getDefaultSystemFont()
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getDefaultSystemFont( );
}

double GraphicsToolkit::getDPI( GraphicsContext* context )
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_getDPI(context);
}

GraphicsResourceBundlePeer* GraphicsToolkit::createGraphicsResourceBundlePeer()
{
	return GraphicsToolkit::graphicsToolkitInstance->internal_createGraphicsResourceBundlePeer();
}


void GraphicsToolkit::systemSettingsChanged()
{
	GraphicsToolkit::graphicsToolkitInstance->internal_systemSettingsChanged();
}



GraphicsToolkit* GraphicsToolkit::internal_getDefaultGraphicsToolkit()
{
	if ( NULL == GraphicsToolkit::graphicsToolkitInstance ){
		//throw exception
	}

	return GraphicsToolkit::graphicsToolkitInstance;
}

Image* GraphicsToolkit::internal_createImage( const String& fileName )
{
	VCF_ASSERT( !fileName.empty() );

	Image* result = NULL;

	bool resString = false;

	if ( fileName.size() > 4 ) {
		if ( fileName.substr(0,4) == "res:" ) {
			resString = true;
		}
	}

	if ( resString ) {
		String resName = fileName.substr(4,fileName.size()-4);
		result = GraphicsToolkit::getResourceBundle()->getImage( resName );
	}
	else {
		
		FilePath fp = fileName;

		if ( !File::exists( fp ) ) {
			throw RuntimeException( String("File \"") + fileName + "\" doesn't exist!" );
		}

		String ext = fp.getExtension();
		ext = StringUtils::lowerCase( ext );
		/**
		Oops forgot to remove the "." character!
		Marcello caught this! Thanks Marcello!
		*/
		if ( !ext.empty() ) {
			if ( ext[0] == '.' ) {
				ext.erase(0,1);
			}
		}
		std::map<String,String>::iterator it = contentTypes_.find( ext );
		if ( it != contentTypes_.end() ){
			ImageLoader* imageLoader = getImageLoader( it->second );
			if ( NULL != imageLoader ){
				result = imageLoader->loadImageFromFile( fileName );
			}
		}
	}

	

	if ( NULL == result ) {
		//throw RuntimeException( String("Unable to create image for file \"") + fileName + "\"" );
	}

	return result;
}

void GraphicsToolkit::internal_saveImage( const String& fileName, Image* image )
{
	FilePath fp = fileName;
	String ext = fp.getExtension();

	ext = StringUtils::lowerCase( ext );
	/**
	Oops forgot to remove the "." character!
	Marcello caught this! Thanks Marcello!
	*/
	if ( !ext.empty() ) {
		if ( ext[0] == '.' ) {
			ext.erase(0,1);
		}
	}
	std::map<String,String>::iterator it = contentTypes_.find( ext );
	if ( it != contentTypes_.end() ){
		ImageLoader* imageLoader = getImageLoader( it->second );
		if ( NULL != imageLoader ){
			if ( true == imageLoader->canSaveImage() ) {
				imageLoader->saveImageToFile( fileName, image );
			}
			else {
				throw RuntimeException( "ImageLoader does not support saving images of type " + it->first );
			}
		}
	}
}


void GraphicsToolkit::internal_registerImageLoader( const String& name, ImageLoader* imageLoader )
{
	imageLoaders_[name] = imageLoader;
}

bool GraphicsToolkit::getAvailableImageTypes( std::vector< std::pair<String,String> >& contentTypes )
{
	GraphicsToolkit* kit = internal_getDefaultGraphicsToolkit();

	std::map<String,ImageLoader*>::iterator it =  kit->imageLoaders_.begin();
	while ( it != kit->imageLoaders_.end() ){
		std::map<String,String>::iterator it2 =  kit->contentTypes_.begin();
		while ( it2 != kit->contentTypes_.end() ) {
			if ( it2->second == it->first ) {
				std::pair<String,String> entry(it2->first,it->first);
				contentTypes.push_back( entry );

				// Might be more than one with the same extension, don't exit - aroman
				//break;
			}
			it2 ++;
		}
		it ++;
	}

	return !contentTypes.empty();
}

void GraphicsToolkit::initContentTypes()
{
	contentTypes_["jpeg"] = "image/jpeg";
	contentTypes_["jpe"] = "image/jpeg";
	contentTypes_["jpg"] = "image/jpeg";
	contentTypes_["gif"] = "image/gif";
	contentTypes_["bmp"] = "image/bmp";
	contentTypes_["rle"] = "image/bmp";
	contentTypes_["dib"] = "image/bmp";
	contentTypes_["wmf"] = "image/emf";
	contentTypes_["emf"] = "image/emf";
	contentTypes_["tif"] = "image/tiff";
	contentTypes_["tiff"] = "image/tiff";
	contentTypes_["tga"] = "image/targa";
	contentTypes_["jfif"] = "image/jpeg";
	contentTypes_["png"] = "image/png";
	contentTypes_["pcx"] = "image/pcx";
	contentTypes_["sgi"] = "image/sgi";
	contentTypes_["koala"] = "image/koala";
	contentTypes_["koa"] = "image/koala";
	contentTypes_["lbm"] = "image/lbm";
	contentTypes_["iff"] = "image/iff";
	contentTypes_["pcx"] = "image/pcx";
	contentTypes_["mng"] = "image/mng";
	contentTypes_["ppm"] = "image/pnm";
	contentTypes_["pgm"] = "image/pnm";
	contentTypes_["pbm"] = "image/pnm";
	contentTypes_["ras"] = "image/ras";
	contentTypes_["psd"] = "image/psd";
}

ImageLoader* GraphicsToolkit::internal_getImageLoader( const String& contentType )
{
	ImageLoader* result = NULL;
	std::map<String,ImageLoader*>::iterator it = imageLoaders_.find( contentType );
	if ( it != imageLoaders_.end() ){
		result = it->second;
	}
	return result;
}

ImageLoader* GraphicsToolkit::internal_getImageLoaderForFileName( const String& fileName )
{
	ImageLoader* result = NULL;
	FilePath fp = fileName;
	String ext = fp.getExtension();

	ext = StringUtils::lowerCase( ext );
	std::map<String,String>::iterator it = contentTypes_.find( ext );
	if ( it != contentTypes_.end() ){
		result = getImageLoader( it->second );
	}

	return result;
}

Color* GraphicsToolkit::internal_getSystemColor( const uint32& systemColor )
{
	Color* result = NULL;
	std::map<uint32,Color*>::iterator found = this->systemColors_.find( systemColor );
	if ( found != systemColors_.end() ){
		result = found->second;
	}
	return result;
}

String GraphicsToolkit::internal_getSystemColorNameFromMap( Color& sysColor ) const
{
	// not pointer are used, so any color can be compared
	String result = ColorNames::unknownColorName_;
	GraphicsToolkit::MapStringColorName::const_iterator found = systemColorNameMap_->find( sysColor );
	if ( found != systemColorNameMap_->end() ){
		result = found->second;
	}
	return result;
}

Color* GraphicsToolkit::internal_getColorFromColormap( const String& colorName )
{
	Color* result = NULL;
	MapStringColor::iterator found = colorMap_.find( colorName );
	if ( found != colorMap_.end() ){
		result = found->second;
	}
	return result;
}

Color* GraphicsToolkit::internal_getColorFromColormap( const int& gray )
{
	String colorName = Format("gray%d") % gray;
	return getColorFromColormap( colorName );
}

String GraphicsToolkit::internal_getColorNameFromMap( const Color& color ) const
{
	// not pointer are used, so any color can be compared
	String result = ColorNames::unknownColorName_;
	MapStringColorName::const_iterator found = colorNameMap_->find( color );
	if ( found != colorNameMap_->end() ){
		result = found->second;
	}
	return result;
}

void GraphicsToolkit::internal_printColorNameMap( ) const
{
	MapStringColorName::const_iterator it = colorNameMap_->begin();
	while ( it != colorNameMap_->end() ) {
		Color c = it->first;
		String s = it->second;
		String sg = getColorNameFromMap(c);
		double dr = c.getRed();
		double dg = c.getGreen();
		double db = c.getBlue();
		uint8 cr = (uint8)(dr*255+0.5);
		uint8 cg = (uint8)(dg*255+0.5);
		uint8 cb = (uint8)(db*255+0.5);
		StringUtils::trace( Format("r=%0.06g, g=%0.06g, b=%0.06g - (%-25s) [%3d, %3d, %3d] (0x%02X, 0x%02X, 0x%02X) <%-25s>\n") % dr % dg % db % s.c_str() %  cr % cg % cb % cr % cg % cb % sg.c_str());
		it ++;
	}
}

Color* GraphicsToolkit::internal_getColorMatchFromColormap( const Color& color )
{
	const Color* closestColor = NULL;

	const Color* closestClr = NULL;

	String sFound;

	MapStringColorName::iterator it = colorNameMap_->find( color );
	if ( it != colorNameMap_->end() ){
		closestClr = &it->first;
		sFound = it->second;
	}
	else {
		ColorSpace::HSLtype hslColor = ColorSpace::ColorToHSL ( color );

		double diffH, diffS, diffL;
		double diffMinH = ColorSpace::HSLMax, diffMinS = ColorSpace::HSLMax, diffMinL = ColorSpace::HSLMax;
		const Color* c = NULL;
		ColorSpace::HSLtype hsl;

		it = colorNameMap_->begin();
		while ( it != colorNameMap_->end() )  {
			c = &it->first;
			Color cc = it->first;
			String ss = it->second;
			hsl = ColorSpace::ColorToHSL( *c );

			// H, S, L is the best order to follow for comparison
			diffH = fabs( hslColor.H - hsl.H );
			if ( diffH <= diffMinH ) {
				diffMinH = diffH;
				diffS = fabs( hslColor.S - hsl.S );
				if ( diffS <= diffMinS ) {
					diffMinS = diffS;
					diffL = fabs( hslColor.L - hsl.L );
					if ( diffL <= diffMinL ) {
						diffMinL = diffL;
						closestClr = c;
						sFound = it->second;
					}
				}
			}

			it++;
		}

		//Note: Colors in colorNameMap_ do not have s_ initialized
		//it = colorNameMap_->find( *closestClr );
		//if ( it == colorNameMap_->end() ) {
		//	StringUtils::traceWithArgs("Warning: color not matched ((%s -> ) %0.2f, %0.2f, %0.2f\n", ((closestClr->s_)?closestClr->s_->c_str():"???"), diffMinH, diffMinS, diffMinL );
		//} else {
		//	StringUtils::traceWithArgs("Ok: color matched (%s -> %s) %0.2f, %0.2f, %0.2f\n", color.s_->c_str(), ((closestClr->s_)?closestClr->s_->c_str():"???"), diffMinH, diffMinS, diffMinL );
		//}
	}

	MapStringColor::iterator f = colorMap_.find( sFound );
	closestColor = f->second;

	return const_cast<Color*>(closestColor);
}

void GraphicsToolkit::initGraphicsToolkit()
{
#if defined(VCF_WIN) && !defined(VCF_AGG)
	GraphicsToolkit::graphicsToolkitInstance = new Win32GraphicsToolkit();
#elif VCF_AGG
	GraphicsToolkit::graphicsToolkitInstance = new AggGraphicsToolkit();
#elif VCF_X11
	GraphicsToolkit::graphicsToolkitInstance = new X11GraphicsToolkit();

#elif VCF_GTK
	GraphicsToolkit::graphicsToolkitInstance = new GTKGraphicsToolkit();

#elif VCF_OSX
	GraphicsToolkit::graphicsToolkitInstance = new OSXGraphicsToolkit();

#elif VCF_XCB
	GraphicsToolkit::graphicsToolkitInstance = new XCBGraphicsToolkit();
#endif


	if ( NULL == GraphicsToolkit::graphicsToolkitInstance ){
		throw NoGraphicsToolkitFoundException( MAKE_ERROR_MSG_2(NO_GFX_TOOLKIT_ERROR) );
	}

	System::internal_replaceResourceBundleInstance( new GraphicsResourceBundle() );

#if !defined(VCF_MINGW) /* cant compile ImageLoaders for now, so just turn they off for MINGW */
	
	GraphicsToolkit::registerImageLoader( "image/jpeg", new JPEGLoader() );

	GraphicsToolkit::registerImageLoader( "image/png", new PNGLoader() );
#endif
	
}

void GraphicsToolkit::terminate()
{
	delete GraphicsToolkit::graphicsToolkitInstance;

	GraphicsToolkit::graphicsToolkitInstance = NULL;
}


void GraphicsToolkit::initColorMap()
{
	ColorNames colorNames_;



	//note: the preferred way to do this would be:
	//initColorNameMapItem( ColorNames::at( ColorNames::aliceblue ) , (VCF::uchar)0xF0, (VCF::uchar)0xF8, (VCF::uchar)0xFF )
	//however that might be too expensive??? - need to do a quick profile to see if it is worth worrying about

#ifdef  VCF_LARGE_COLOR_LIST
    //from http://www.winvideo.net/colori.htm

    //shades of gray
    //color name r/g/b hex bg/fg color sample
	//						name				 , R			   , G				 , B					// 0xFFRRGGBB
    initColorNameMapItem( "black"                   , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x00 );   // 0xFF000000   //  0;0;0
    initColorNameMapItem( "gray"                    , (VCF::uchar)0xBE, (VCF::uchar)0xBE, (VCF::uchar)0xBE );   // 0xFFBEBEBE   //  190;190;190
    initColorNameMapItem( "dimgray"                 , (VCF::uchar)0x69, (VCF::uchar)0x69, (VCF::uchar)0x69 );   // 0xFF696969   //  105;105;105 // frequently mispelled as dimgray
    initColorNameMapItem( "lightgray"               , (VCF::uchar)0xD3, (VCF::uchar)0xD3, (VCF::uchar)0xD3 );   // 0xFFD3D3D3   //  211;211;211
    initColorNameMapItem( "lightslategray"          , (VCF::uchar)0x77, (VCF::uchar)0x88, (VCF::uchar)0x99 );   // 0xFF778899   //  119;136;153
    initColorNameMapItem( "slategray"               , (VCF::uchar)0x70, (VCF::uchar)0x80, (VCF::uchar)0x90 );   // 0xFF708090   //  112;128;144
    initColorNameMapItem( "slategray1"              , (VCF::uchar)0xC6, (VCF::uchar)0xE2, (VCF::uchar)0xFF );   // 0xFFC6E2FF   //  198;226;255
    initColorNameMapItem( "slategray2"              , (VCF::uchar)0xB9, (VCF::uchar)0xD3, (VCF::uchar)0xEE );   // 0xFFB9D3EE   //  185;211;238
    initColorNameMapItem( "slategray3"              , (VCF::uchar)0x9F, (VCF::uchar)0xB6, (VCF::uchar)0xCD );   // 0xFF9FB6CD   //  159;182;205
    initColorNameMapItem( "slategray4"              , (VCF::uchar)0x6C, (VCF::uchar)0x7B, (VCF::uchar)0x8B );   // 0xFF6C7B8B   //  108;123;139
    initColorNameMapItem( "slategray"               , (VCF::uchar)0x70, (VCF::uchar)0x80, (VCF::uchar)0x90 );   // 0xFF708090   //  112;128;144
    initColorNameMapItem( "gray0"                   , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x00 );   // 0xFF000000   //  0;0;0
    initColorNameMapItem( "gray1"                   , (VCF::uchar)0x03, (VCF::uchar)0x03, (VCF::uchar)0x03 );   // 0xFF030303   //  3;3;3
    initColorNameMapItem( "gray2"                   , (VCF::uchar)0x05, (VCF::uchar)0x05, (VCF::uchar)0x05 );   // 0xFF050505   //  5;5;5
    initColorNameMapItem( "gray3"                   , (VCF::uchar)0x08, (VCF::uchar)0x08, (VCF::uchar)0x08 );   // 0xFF080808   //  8;8;8
    initColorNameMapItem( "gray4"                   , (VCF::uchar)0x0A, (VCF::uchar)0x0A, (VCF::uchar)0x0A );   // 0xFF0A0A0A   //  10;10;10
    initColorNameMapItem( "gray5"                   , (VCF::uchar)0x0D, (VCF::uchar)0x0D, (VCF::uchar)0x0D );   // 0xFF0D0D0D   //  13;13;13
    initColorNameMapItem( "gray6"                   , (VCF::uchar)0x0F, (VCF::uchar)0x0F, (VCF::uchar)0x0F );   // 0xFF0F0F0F   //  15;15;15
    initColorNameMapItem( "gray7"                   , (VCF::uchar)0x12, (VCF::uchar)0x12, (VCF::uchar)0x12 );   // 0xFF121212   //  18;18;18
    initColorNameMapItem( "gray8"                   , (VCF::uchar)0x14, (VCF::uchar)0x14, (VCF::uchar)0x14 );   // 0xFF141414   //  20;20;20
    initColorNameMapItem( "gray98"                  , (VCF::uchar)0x17, (VCF::uchar)0x17, (VCF::uchar)0x17 );   // 0xFF171717   //  23;23;23
    initColorNameMapItem( "gray10"                  , (VCF::uchar)0x1A, (VCF::uchar)0x1A, (VCF::uchar)0x1A );   // 0xFF1A1A1A   //  26;26;26
    initColorNameMapItem( "gray11"                  , (VCF::uchar)0x1C, (VCF::uchar)0x1C, (VCF::uchar)0x1C );   // 0xFF1C1C1C   //  28;28;28
    initColorNameMapItem( "gray12"                  , (VCF::uchar)0x1F, (VCF::uchar)0x1F, (VCF::uchar)0x1F );   // 0xFF1F1F1F   //  31;31;31
    initColorNameMapItem( "gray13"                  , (VCF::uchar)0x21, (VCF::uchar)0x21, (VCF::uchar)0x21 );   // 0xFF212121   //  33;33;33
    initColorNameMapItem( "gray14"                  , (VCF::uchar)0x24, (VCF::uchar)0x24, (VCF::uchar)0x24 );   // 0xFF242424   //  36;36;36
    initColorNameMapItem( "gray15"                  , (VCF::uchar)0x26, (VCF::uchar)0x26, (VCF::uchar)0x26 );   // 0xFF262626   //  38;38;38
    initColorNameMapItem( "gray16"                  , (VCF::uchar)0x29, (VCF::uchar)0x29, (VCF::uchar)0x29 );   // 0xFF292929   //  41;41;41
    initColorNameMapItem( "gray17"                  , (VCF::uchar)0x2B, (VCF::uchar)0x2B, (VCF::uchar)0x2B );   // 0xFF2B2B2B   //  43;43;43
    initColorNameMapItem( "gray18"                  , (VCF::uchar)0x2E, (VCF::uchar)0x2E, (VCF::uchar)0x2E );   // 0xFF2E2E2E   //  46;46;46
    initColorNameMapItem( "gray19"                  , (VCF::uchar)0x30, (VCF::uchar)0x30, (VCF::uchar)0x30 );   // 0xFF303030   //  48;48;48
    initColorNameMapItem( "gray20"                  , (VCF::uchar)0x33, (VCF::uchar)0x33, (VCF::uchar)0x33 );   // 0xFF333333   //  51;51;51
    initColorNameMapItem( "gray21"                  , (VCF::uchar)0x36, (VCF::uchar)0x36, (VCF::uchar)0x36 );   // 0xFF363636   //  54;54;54
    initColorNameMapItem( "gray22"                  , (VCF::uchar)0x38, (VCF::uchar)0x38, (VCF::uchar)0x38 );   // 0xFF383838   //  56;56;56
    initColorNameMapItem( "gray23"                  , (VCF::uchar)0x3B, (VCF::uchar)0x3B, (VCF::uchar)0x3B );   // 0xFF3B3B3B   //  59;59;59
    initColorNameMapItem( "gray24"                  , (VCF::uchar)0x3D, (VCF::uchar)0x3D, (VCF::uchar)0x3D );   // 0xFF3D3D3D   //  61;61;61
    initColorNameMapItem( "gray25"                  , (VCF::uchar)0x40, (VCF::uchar)0x40, (VCF::uchar)0x40 );   // 0xFF404040   //  64;64;64
    initColorNameMapItem( "gray26"                  , (VCF::uchar)0x42, (VCF::uchar)0x42, (VCF::uchar)0x42 );   // 0xFF424242   //  66;66;66
    initColorNameMapItem( "gray27"                  , (VCF::uchar)0x45, (VCF::uchar)0x45, (VCF::uchar)0x45 );   // 0xFF454545   //  69;69;69
    initColorNameMapItem( "gray28"                  , (VCF::uchar)0x47, (VCF::uchar)0x47, (VCF::uchar)0x47 );   // 0xFF474747   //  71;71;71
    initColorNameMapItem( "gray29"                  , (VCF::uchar)0x4A, (VCF::uchar)0x4A, (VCF::uchar)0x4A );   // 0xFF4A4A4A   //  74;74;74
    initColorNameMapItem( "gray30"                  , (VCF::uchar)0x4D, (VCF::uchar)0x4D, (VCF::uchar)0x4D );   // 0xFF4D4D4D   //  77;77;77
    initColorNameMapItem( "gray31"                  , (VCF::uchar)0x4F, (VCF::uchar)0x4F, (VCF::uchar)0x4F );   // 0xFF4F4F4F   //  79;79;79
    initColorNameMapItem( "gray32"                  , (VCF::uchar)0x52, (VCF::uchar)0x52, (VCF::uchar)0x52 );   // 0xFF525252   //  82;82;82
    initColorNameMapItem( "gray33"                  , (VCF::uchar)0x54, (VCF::uchar)0x54, (VCF::uchar)0x54 );   // 0xFF545454   //  84;84;84
    initColorNameMapItem( "gray34"                  , (VCF::uchar)0x57, (VCF::uchar)0x57, (VCF::uchar)0x57 );   // 0xFF575757   //  87;87;87
    initColorNameMapItem( "gray35"                  , (VCF::uchar)0x59, (VCF::uchar)0x59, (VCF::uchar)0x59 );   // 0xFF595959   //  89;89;89
    initColorNameMapItem( "gray36"                  , (VCF::uchar)0x5C, (VCF::uchar)0x5C, (VCF::uchar)0x5C );   // 0xFF5C5C5C   //  92;92;92
    initColorNameMapItem( "gray37"                  , (VCF::uchar)0x5E, (VCF::uchar)0x5E, (VCF::uchar)0x5E );   // 0xFF5E5E5E   //  94;94;94
    initColorNameMapItem( "gray38"                  , (VCF::uchar)0x61, (VCF::uchar)0x61, (VCF::uchar)0x61 );   // 0xFF616161   //  97;97;97
    initColorNameMapItem( "gray39"                  , (VCF::uchar)0x63, (VCF::uchar)0x63, (VCF::uchar)0x63 );   // 0xFF636363   //  99;99;99
    initColorNameMapItem( "gray40"                  , (VCF::uchar)0x66, (VCF::uchar)0x66, (VCF::uchar)0x66 );   // 0xFF666666   //  102;102;102
    initColorNameMapItem( "gray41"                  , (VCF::uchar)0x69, (VCF::uchar)0x69, (VCF::uchar)0x69 );   // 0xFF696969   //  105;105;105
    initColorNameMapItem( "gray42"                  , (VCF::uchar)0x6B, (VCF::uchar)0x6B, (VCF::uchar)0x6B );   // 0xFF6B6B6B   //  107;107;107
    initColorNameMapItem( "gray43"                  , (VCF::uchar)0x6E, (VCF::uchar)0x6E, (VCF::uchar)0x6E );   // 0xFF6E6E6E   //  110;110;110
    initColorNameMapItem( "gray44"                  , (VCF::uchar)0x70, (VCF::uchar)0x70, (VCF::uchar)0x70 );   // 0xFF707070   //  112;112;112
    initColorNameMapItem( "gray45"                  , (VCF::uchar)0x73, (VCF::uchar)0x73, (VCF::uchar)0x73 );   // 0xFF737373   //  115;115;115
    initColorNameMapItem( "gray46"                  , (VCF::uchar)0x75, (VCF::uchar)0x75, (VCF::uchar)0x75 );   // 0xFF757575   //  117;117;117
    initColorNameMapItem( "gray47"                  , (VCF::uchar)0x78, (VCF::uchar)0x78, (VCF::uchar)0x78 );   // 0xFF787878   //  120;120;120
    initColorNameMapItem( "gray48"                  , (VCF::uchar)0x7A, (VCF::uchar)0x7A, (VCF::uchar)0x7A );   // 0xFF7A7A7A   //  122;122;122
    initColorNameMapItem( "gray49"                  , (VCF::uchar)0x7D, (VCF::uchar)0x7D, (VCF::uchar)0x7D );   // 0xFF7D7D7D   //  125;125;125
    initColorNameMapItem( "gray50"                  , (VCF::uchar)0x7F, (VCF::uchar)0x7F, (VCF::uchar)0x7F );   // 0xFF7F7F7F   //  127;127;127
    initColorNameMapItem( "gray51"                  , (VCF::uchar)0x82, (VCF::uchar)0x82, (VCF::uchar)0x82 );   // 0xFF828282   //  130;130;130
    initColorNameMapItem( "gray52"                  , (VCF::uchar)0x85, (VCF::uchar)0x85, (VCF::uchar)0x85 );   // 0xFF858585   //  133;133;133
    initColorNameMapItem( "gray53"                  , (VCF::uchar)0x87, (VCF::uchar)0x87, (VCF::uchar)0x87 );   // 0xFF878787   //  135;135;135
    initColorNameMapItem( "gray54"                  , (VCF::uchar)0x8A, (VCF::uchar)0x8A, (VCF::uchar)0x8A );   // 0xFF8A8A8A   //  138;138;138
    initColorNameMapItem( "gray55"                  , (VCF::uchar)0x8C, (VCF::uchar)0x8C, (VCF::uchar)0x8C );   // 0xFF8C8C8C   //  140;140;140
    initColorNameMapItem( "gray56"                  , (VCF::uchar)0x8F, (VCF::uchar)0x8F, (VCF::uchar)0x8F );   // 0xFF8F8F8F   //  143;143;143
    initColorNameMapItem( "gray57"                  , (VCF::uchar)0x91, (VCF::uchar)0x91, (VCF::uchar)0x91 );   // 0xFF919191   //  145;145;145
    initColorNameMapItem( "gray58"                  , (VCF::uchar)0x94, (VCF::uchar)0x94, (VCF::uchar)0x94 );   // 0xFF949494   //  148;148;148
    initColorNameMapItem( "gray59"                  , (VCF::uchar)0x96, (VCF::uchar)0x96, (VCF::uchar)0x96 );   // 0xFF969696   //  150;150;150
    initColorNameMapItem( "gray60"                  , (VCF::uchar)0x99, (VCF::uchar)0x99, (VCF::uchar)0x99 );   // 0xFF999999   //  153;153;153
    initColorNameMapItem( "gray61"                  , (VCF::uchar)0x9C, (VCF::uchar)0x9C, (VCF::uchar)0x9C );   // 0xFF9C9C9C   //  156;156;156
    initColorNameMapItem( "gray62"                  , (VCF::uchar)0x9E, (VCF::uchar)0x9E, (VCF::uchar)0x9E );   // 0xFF9E9E9E   //  158;158;158
    initColorNameMapItem( "gray63"                  , (VCF::uchar)0xA1, (VCF::uchar)0xA1, (VCF::uchar)0xA1 );   // 0xFFA1A1A1   //  161;161;161
    initColorNameMapItem( "gray64"                  , (VCF::uchar)0xA3, (VCF::uchar)0xA3, (VCF::uchar)0xA3 );   // 0xFFA3A3A3   //  163;163;163
    initColorNameMapItem( "gray65"                  , (VCF::uchar)0xA6, (VCF::uchar)0xA6, (VCF::uchar)0xA6 );   // 0xFFA6A6A6   //  166;166;166
    initColorNameMapItem( "gray66"                  , (VCF::uchar)0xA8, (VCF::uchar)0xA8, (VCF::uchar)0xA8 );   // 0xFFA8A8A8   //  168;168;168
    initColorNameMapItem( "gray67"                  , (VCF::uchar)0xAB, (VCF::uchar)0xAB, (VCF::uchar)0xAB );   // 0xFFABABAB   //  171;171;171
    initColorNameMapItem( "gray68"                  , (VCF::uchar)0xAD, (VCF::uchar)0xAD, (VCF::uchar)0xAD );   // 0xFFADADAD   //  173;173;173
    initColorNameMapItem( "gray69"                  , (VCF::uchar)0xB0, (VCF::uchar)0xB0, (VCF::uchar)0xB0 );   // 0xFFB0B0B0   //  176;176;176
    initColorNameMapItem( "gray70"                  , (VCF::uchar)0xB3, (VCF::uchar)0xB3, (VCF::uchar)0xB3 );   // 0xFFB3B3B3   //  179;179;179
    initColorNameMapItem( "gray71"                  , (VCF::uchar)0xB5, (VCF::uchar)0xB5, (VCF::uchar)0xB5 );   // 0xFFB5B5B5   //  181;181;181
    initColorNameMapItem( "gray72"                  , (VCF::uchar)0xB8, (VCF::uchar)0xB8, (VCF::uchar)0xB8 );   // 0xFFB8B8B8   //  184;184;184
    initColorNameMapItem( "gray73"                  , (VCF::uchar)0xBA, (VCF::uchar)0xBA, (VCF::uchar)0xBA );   // 0xFFBABABA   //  186;186;186
    initColorNameMapItem( "gray74"                  , (VCF::uchar)0xBD, (VCF::uchar)0xBD, (VCF::uchar)0xBD );   // 0xFFBDBDBD   //  189;189;189
    initColorNameMapItem( "gray75"                  , (VCF::uchar)0xBF, (VCF::uchar)0xBF, (VCF::uchar)0xBF );   // 0xFFBFBFBF   //  191;191;191
    initColorNameMapItem( "gray76"                  , (VCF::uchar)0xC2, (VCF::uchar)0xC2, (VCF::uchar)0xC2 );   // 0xFFC2C2C2   //  194;194;194
    initColorNameMapItem( "gray77"                  , (VCF::uchar)0xC4, (VCF::uchar)0xC4, (VCF::uchar)0xC4 );   // 0xFFC4C4C4   //  196;196;196
    initColorNameMapItem( "gray78"                  , (VCF::uchar)0xC7, (VCF::uchar)0xC7, (VCF::uchar)0xC7 );   // 0xFFC7C7C7   //  199;199;199
    initColorNameMapItem( "gray79"                  , (VCF::uchar)0xC9, (VCF::uchar)0xC9, (VCF::uchar)0xC9 );   // 0xFFC9C9C9   //  201;201;201
    initColorNameMapItem( "gray80"                  , (VCF::uchar)0xCC, (VCF::uchar)0xCC, (VCF::uchar)0xCC );   // 0xFFCCCCCC   //  204;204;204
    initColorNameMapItem( "gray81"                  , (VCF::uchar)0xCF, (VCF::uchar)0xCF, (VCF::uchar)0xCF );   // 0xFFCFCFCF   //  207;207;207
    initColorNameMapItem( "gray82"                  , (VCF::uchar)0xD1, (VCF::uchar)0xD1, (VCF::uchar)0xD1 );   // 0xFFD1D1D1   //  209;209;209
    initColorNameMapItem( "gray83"                  , (VCF::uchar)0xD4, (VCF::uchar)0xD4, (VCF::uchar)0xD4 );   // 0xFFD4D4D4   //  212;212;212
    initColorNameMapItem( "gray84"                  , (VCF::uchar)0xD6, (VCF::uchar)0xD6, (VCF::uchar)0xD6 );   // 0xFFD6D6D6   //  214;214;214
    initColorNameMapItem( "gray85"                  , (VCF::uchar)0xD9, (VCF::uchar)0xD9, (VCF::uchar)0xD9 );   // 0xFFD9D9D9   //  217;217;217
    initColorNameMapItem( "gray86"                  , (VCF::uchar)0xDB, (VCF::uchar)0xDB, (VCF::uchar)0xDB );   // 0xFFDBDBDB   //  219;219;219
    initColorNameMapItem( "gray87"                  , (VCF::uchar)0xDE, (VCF::uchar)0xDE, (VCF::uchar)0xDE );   // 0xFFDEDEDE   //  222;222;222
    initColorNameMapItem( "gray88"                  , (VCF::uchar)0xE0, (VCF::uchar)0xE0, (VCF::uchar)0xE0 );   // 0xFFE0E0E0   //  224;224;224
    initColorNameMapItem( "gray89"                  , (VCF::uchar)0xE3, (VCF::uchar)0xE3, (VCF::uchar)0xE3 );   // 0xFFE3E3E3   //  227;227;227
    initColorNameMapItem( "gray90"                  , (VCF::uchar)0xE5, (VCF::uchar)0xE5, (VCF::uchar)0xE5 );   // 0xFFE5E5E5   //  229;229;229
    initColorNameMapItem( "gray91"                  , (VCF::uchar)0xE8, (VCF::uchar)0xE8, (VCF::uchar)0xE8 );   // 0xFFE8E8E8   //  232;232;232
    initColorNameMapItem( "gray92"                  , (VCF::uchar)0xEB, (VCF::uchar)0xEB, (VCF::uchar)0xEB );   // 0xFFEBEBEB   //  235;235;235
    initColorNameMapItem( "gray93"                  , (VCF::uchar)0xED, (VCF::uchar)0xED, (VCF::uchar)0xED );   // 0xFFEDEDED   //  237;237;237
    initColorNameMapItem( "gray94"                  , (VCF::uchar)0xF0, (VCF::uchar)0xF0, (VCF::uchar)0xF0 );   // 0xFFF0F0F0   //  240;240;240
    initColorNameMapItem( "gray95"                  , (VCF::uchar)0xF2, (VCF::uchar)0xF2, (VCF::uchar)0xF2 );   // 0xFFF2F2F2   //  242;242;242
    initColorNameMapItem( "gray96"                  , (VCF::uchar)0xF5, (VCF::uchar)0xF5, (VCF::uchar)0xF5 );   // 0xFFF5F5F5   //  245;245;245
    initColorNameMapItem( "gray97"                  , (VCF::uchar)0xF7, (VCF::uchar)0xF7, (VCF::uchar)0xF7 );   // 0xFFF7F7F7   //  247;247;247
    initColorNameMapItem( "gray98"                  , (VCF::uchar)0xFA, (VCF::uchar)0xFA, (VCF::uchar)0xFA );   // 0xFFFAFAFA   //  250;250;250
    initColorNameMapItem( "gray99"                  , (VCF::uchar)0xFC, (VCF::uchar)0xFC, (VCF::uchar)0xFC );   // 0xFFFCFCFC   //  252;252;252
    initColorNameMapItem( "gray100"                 , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFFFFFFFF   //  255;255;255

    //shades of blue
    //color name r/g/b hex bg/fg color sample
	//						name				 , R			   , G				 , B					// 0xFFRRGGBB
    initColorNameMapItem( "aliceblue"               , (VCF::uchar)0xF0, (VCF::uchar)0xF8, (VCF::uchar)0xFF );   // 0xFFF0F8FF   //  240;248;255
    initColorNameMapItem( "blueviolet"              , (VCF::uchar)0x8A, (VCF::uchar)0x2B, (VCF::uchar)0xE2 );   // 0xFF8A2BE2   //  138;43;226
    initColorNameMapItem( "cadetblue"               , (VCF::uchar)0x5F, (VCF::uchar)0x9E, (VCF::uchar)0xA0 );   // 0xFF5F9EA0   //  95;158;160
    initColorNameMapItem( "cadetblue1"              , (VCF::uchar)0x98, (VCF::uchar)0xF5, (VCF::uchar)0xFF );   // 0xFF98F5FF   //  152;245;255
    initColorNameMapItem( "cadetblue2"              , (VCF::uchar)0x8E, (VCF::uchar)0xE5, (VCF::uchar)0xEE );   // 0xFF8EE5EE   //  142;229;238
    initColorNameMapItem( "cadetblue3"              , (VCF::uchar)0x7A, (VCF::uchar)0xC5, (VCF::uchar)0xCD );   // 0xFF7AC5CD   //  122;197;205
    initColorNameMapItem( "cadetblue4"              , (VCF::uchar)0x53, (VCF::uchar)0x86, (VCF::uchar)0x8B );   // 0xFF53868B   //  83;134;139
    initColorNameMapItem( "cornflowerblue"          , (VCF::uchar)0x64, (VCF::uchar)0x95, (VCF::uchar)0xED );   // 0xFF6495ED   //  100;149;237
    initColorNameMapItem( "darkslateblue"           , (VCF::uchar)0x48, (VCF::uchar)0x3D, (VCF::uchar)0x8B );   // 0xFF483D8B   //  72;61;139
    initColorNameMapItem( "darkturquoise"           , (VCF::uchar)0x00, (VCF::uchar)0xCE, (VCF::uchar)0xD1 );   // 0xFF00CED1   //  0;206;209
    initColorNameMapItem( "deepskyblue"             , (VCF::uchar)0x00, (VCF::uchar)0xBF, (VCF::uchar)0xFF );   // 0xFF00BFFF   //  0;191;255
    initColorNameMapItem( "deepskyblue1"            , (VCF::uchar)0x00, (VCF::uchar)0xBF, (VCF::uchar)0xFF );   // 0xFF00BFFF   //  0;191;255
    initColorNameMapItem( "deepskyblue2"            , (VCF::uchar)0x00, (VCF::uchar)0xB2, (VCF::uchar)0xEE );   // 0xFF00B2EE   //  0;178;238
    initColorNameMapItem( "deepskyblue3"            , (VCF::uchar)0x00, (VCF::uchar)0x9A, (VCF::uchar)0xCD );   // 0xFF009ACD   //  0;154;205
    initColorNameMapItem( "deepskyblue4"            , (VCF::uchar)0x00, (VCF::uchar)0x68, (VCF::uchar)0x8B );   // 0xFF00688B   //  0;104;139
    initColorNameMapItem( "dodgerblue"              , (VCF::uchar)0x1E, (VCF::uchar)0x90, (VCF::uchar)0xFF );   // 0xFF1E90FF   //  30;144;255
    initColorNameMapItem( "dodgerblue1"             , (VCF::uchar)0x1E, (VCF::uchar)0x90, (VCF::uchar)0xFF );   // 0xFF1E90FF   //  30;144;255
    initColorNameMapItem( "dodgerblue2"             , (VCF::uchar)0x1C, (VCF::uchar)0x86, (VCF::uchar)0xEE );   // 0xFF1C86EE   //  28;134;238
    initColorNameMapItem( "dodgerblue3"             , (VCF::uchar)0x18, (VCF::uchar)0x74, (VCF::uchar)0xCD );   // 0xFF1874CD   //  24;116;205
    initColorNameMapItem( "dodgerblue4"             , (VCF::uchar)0x10, (VCF::uchar)0x4E, (VCF::uchar)0x8B );   // 0xFF104E8B   //  16;78;139
    initColorNameMapItem( "lightblue"               , (VCF::uchar)0xAD, (VCF::uchar)0xD8, (VCF::uchar)0xE6 );   // 0xFFADD8E6   //  173;216;230
    initColorNameMapItem( "lightblue1"              , (VCF::uchar)0xBF, (VCF::uchar)0xEF, (VCF::uchar)0xFF );   // 0xFFBFEFFF   //  191;239;255
    initColorNameMapItem( "lightblue2"              , (VCF::uchar)0xB2, (VCF::uchar)0xDF, (VCF::uchar)0xEE );   // 0xFFB2DFEE   //  178;223;238
    initColorNameMapItem( "lightblue3"              , (VCF::uchar)0x9A, (VCF::uchar)0xC0, (VCF::uchar)0xCD );   // 0xFF9AC0CD   //  154;192;205
    initColorNameMapItem( "lightblue4"              , (VCF::uchar)0x68, (VCF::uchar)0x83, (VCF::uchar)0x8B );   // 0xFF68838B   //  104;131;139
    initColorNameMapItem( "lightcyan"               , (VCF::uchar)0xE0, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFFE0FFFF   //  224;255;255
    initColorNameMapItem( "lightcyan1"              , (VCF::uchar)0xE0, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFFE0FFFF   //  224;255;255
    initColorNameMapItem( "lightcyan2"              , (VCF::uchar)0xD1, (VCF::uchar)0xEE, (VCF::uchar)0xEE );   // 0xFFD1EEEE   //  209;238;238
    initColorNameMapItem( "lightcyan3"              , (VCF::uchar)0xB4, (VCF::uchar)0xCD, (VCF::uchar)0xCD );   // 0xFFB4CDCD   //  180;205;205
    initColorNameMapItem( "lightcyan4"              , (VCF::uchar)0x7A, (VCF::uchar)0x8B, (VCF::uchar)0x8B );   // 0xFF7A8B8B   //  122;139;139
    initColorNameMapItem( "lightskyblue"            , (VCF::uchar)0x87, (VCF::uchar)0xCE, (VCF::uchar)0xFA );   // 0xFF87CEFA   //  135;206;250
    initColorNameMapItem( "lightskyblue1"           , (VCF::uchar)0xB0, (VCF::uchar)0xE2, (VCF::uchar)0xFF );   // 0xFFB0E2FF   //  176;226;255
    initColorNameMapItem( "lightskyblue2"           , (VCF::uchar)0xA4, (VCF::uchar)0xD3, (VCF::uchar)0xEE );   // 0xFFA4D3EE   //  164;211;238
    initColorNameMapItem( "lightskyblue3"           , (VCF::uchar)0x8D, (VCF::uchar)0xB6, (VCF::uchar)0xCD );   // 0xFF8DB6CD   //  141;182;205
    initColorNameMapItem( "lightskyblue4"           , (VCF::uchar)0x60, (VCF::uchar)0x7B, (VCF::uchar)0x8B );   // 0xFF607B8B   //  96;123;139
    initColorNameMapItem( "lightslateblue"          , (VCF::uchar)0x84, (VCF::uchar)0x70, (VCF::uchar)0xFF );   // 0xFF8470FF   //  132;112;255
    initColorNameMapItem( "lightsteelblue"          , (VCF::uchar)0xB0, (VCF::uchar)0xC4, (VCF::uchar)0xDE );   // 0xFFB0C4DE   //  176;196;222
    initColorNameMapItem( "lightsteelblue1"         , (VCF::uchar)0xCA, (VCF::uchar)0xE1, (VCF::uchar)0xFF );   // 0xFFCAE1FF   //  202;225;255
    initColorNameMapItem( "lightsteelblue2"         , (VCF::uchar)0xBC, (VCF::uchar)0xD2, (VCF::uchar)0xEE );   // 0xFFBCD2EE   //  188;210;238
    initColorNameMapItem( "lightsteelblue3"         , (VCF::uchar)0xA2, (VCF::uchar)0xB5, (VCF::uchar)0xCD );   // 0xFFA2B5CD   //  162;181;205
    initColorNameMapItem( "lightsteelblue4"         , (VCF::uchar)0x6E, (VCF::uchar)0x7B, (VCF::uchar)0x8B );   // 0xFF6E7B8B   //  110;123;139
    initColorNameMapItem( "mediumaquamarine"        , (VCF::uchar)0x66, (VCF::uchar)0xCD, (VCF::uchar)0xAA );   // 0xFF66CDAA   //  102;205;170
    initColorNameMapItem( "mediumblue"              , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0xCD );   // 0xFF0000CD   //  0;0;205
    initColorNameMapItem( "mediumslateblue"         , (VCF::uchar)0x7B, (VCF::uchar)0x68, (VCF::uchar)0xEE );   // 0xFF7B68EE   //  123;104;238
    initColorNameMapItem( "mediumturquoise"         , (VCF::uchar)0x48, (VCF::uchar)0xD1, (VCF::uchar)0xCC );   // 0xFF48D1CC   //  72;209;204
    initColorNameMapItem( "midnightblue"            , (VCF::uchar)0x19, (VCF::uchar)0x19, (VCF::uchar)0x70 );   // 0xFF191970   //  25;25;112
    initColorNameMapItem( "navyblue"                , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x80 );   // 0xFF000080   //  0;0;128
    initColorNameMapItem( "paleturquoise"           , (VCF::uchar)0xAF, (VCF::uchar)0xEE, (VCF::uchar)0xEE );   // 0xFFAFEEEE   //  175;238;238
    initColorNameMapItem( "paleturquoise1"          , (VCF::uchar)0xBB, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFFBBFFFF   //  187;255;255
    initColorNameMapItem( "paleturquoise2"          , (VCF::uchar)0xAE, (VCF::uchar)0xEE, (VCF::uchar)0xEE );   // 0xFFAEEEEE   //  174;238;238
    initColorNameMapItem( "paleturquoise3"          , (VCF::uchar)0x96, (VCF::uchar)0xCD, (VCF::uchar)0xCD );   // 0xFF96CDCD   //  150;205;205
    initColorNameMapItem( "paleturquoise4"          , (VCF::uchar)0x66, (VCF::uchar)0x8B, (VCF::uchar)0x8B );   // 0xFF668B8B   //  102;139;139
    initColorNameMapItem( "powderblue"              , (VCF::uchar)0xB0, (VCF::uchar)0xE0, (VCF::uchar)0xE6 );   // 0xFFB0E0E6   //  176;224;230
    initColorNameMapItem( "royalblue"               , (VCF::uchar)0x41, (VCF::uchar)0x69, (VCF::uchar)0xE1 );   // 0xFF4169E1   //  65;105;225
    initColorNameMapItem( "royalblue1"              , (VCF::uchar)0x48, (VCF::uchar)0x76, (VCF::uchar)0xFF );   // 0xFF4876FF   //  72;118;255
    initColorNameMapItem( "royalblue2"              , (VCF::uchar)0x43, (VCF::uchar)0x6E, (VCF::uchar)0xEE );   // 0xFF436EEE   //  67;110;238
    initColorNameMapItem( "royalblue3"              , (VCF::uchar)0x3A, (VCF::uchar)0x5F, (VCF::uchar)0xCD );   // 0xFF3A5FCD   //  58;95;205
    initColorNameMapItem( "royalblue4"              , (VCF::uchar)0x27, (VCF::uchar)0x40, (VCF::uchar)0x8B );   // 0xFF27408B   //  39;64;139
    initColorNameMapItem( "royalblue5"              , (VCF::uchar)0x00, (VCF::uchar)0x22, (VCF::uchar)0x66 );   // 0xFF002266   //  00;34;102
    initColorNameMapItem( "skyblue"                 , (VCF::uchar)0x87, (VCF::uchar)0xCE, (VCF::uchar)0xEB );   // 0xFF87CEEB   //  135;206;235
    initColorNameMapItem( "skyblue1"                , (VCF::uchar)0x87, (VCF::uchar)0xCE, (VCF::uchar)0xFF );   // 0xFF87CEFF   //  135;206;255
    initColorNameMapItem( "skyblue2"                , (VCF::uchar)0x7E, (VCF::uchar)0xC0, (VCF::uchar)0xEE );   // 0xFF7EC0EE   //  126;192;238
    initColorNameMapItem( "skyblue3"                , (VCF::uchar)0x6C, (VCF::uchar)0xA6, (VCF::uchar)0xCD );   // 0xFF6CA6CD   //  108;166;205
    initColorNameMapItem( "skyblue4"                , (VCF::uchar)0x4A, (VCF::uchar)0x70, (VCF::uchar)0x8B );   // 0xFF4A708B   //  74;112;139
    initColorNameMapItem( "slateblue"               , (VCF::uchar)0x6A, (VCF::uchar)0x5A, (VCF::uchar)0xCD );   // 0xFF6A5ACD   //  106;90;205
    initColorNameMapItem( "slateblue1"              , (VCF::uchar)0x83, (VCF::uchar)0x6F, (VCF::uchar)0xFF );   // 0xFF836FFF   //  131;111;255
    initColorNameMapItem( "slateblue2"              , (VCF::uchar)0x7A, (VCF::uchar)0x67, (VCF::uchar)0xEE );   // 0xFF7A67EE   //  122;103;238
    initColorNameMapItem( "slateblue3"              , (VCF::uchar)0x69, (VCF::uchar)0x59, (VCF::uchar)0xCD );   // 0xFF6959CD   //  105;89;205
    initColorNameMapItem( "slateblue4"              , (VCF::uchar)0x47, (VCF::uchar)0x3C, (VCF::uchar)0x8B );   // 0xFF473C8B   //  71;60;139
    initColorNameMapItem( "steelblue"               , (VCF::uchar)0x46, (VCF::uchar)0x82, (VCF::uchar)0xB4 );   // 0xFF4682B4   //  70;130;180
    initColorNameMapItem( "steelblue1"              , (VCF::uchar)0x63, (VCF::uchar)0xB8, (VCF::uchar)0xFF );   // 0xFF63B8FF   //  99;184;255
    initColorNameMapItem( "steelblue2"              , (VCF::uchar)0x5C, (VCF::uchar)0xAC, (VCF::uchar)0xEE );   // 0xFF5CACEE   //  92;172;238
    initColorNameMapItem( "steelblue3"              , (VCF::uchar)0x4F, (VCF::uchar)0x94, (VCF::uchar)0xCD );   // 0xFF4F94CD   //  79;148;205
    initColorNameMapItem( "steelblue4"              , (VCF::uchar)0x36, (VCF::uchar)0x64, (VCF::uchar)0x8B );   // 0xFF36648B   //  54;100;139
    initColorNameMapItem( "aquamarine"              , (VCF::uchar)0x7F, (VCF::uchar)0xFF, (VCF::uchar)0xD4 );   // 0xFF7FFFD4   //  127;255;212
    initColorNameMapItem( "aquamarine1"             , (VCF::uchar)0x7F, (VCF::uchar)0xFF, (VCF::uchar)0xD4 );   // 0xFF7FFFD4   //  127;255;212
    initColorNameMapItem( "aquamarine2"             , (VCF::uchar)0x76, (VCF::uchar)0xEE, (VCF::uchar)0xC6 );   // 0xFF76EEC6   //  118;238;198
    initColorNameMapItem( "aquamarine3"             , (VCF::uchar)0x66, (VCF::uchar)0xCD, (VCF::uchar)0xAA );   // 0xFF66CDAA   //  102;205;170
    initColorNameMapItem( "aquamarine4"             , (VCF::uchar)0x45, (VCF::uchar)0x8B, (VCF::uchar)0x74 );   // 0xFF458B74   //  69;139;116
    initColorNameMapItem( "azure"                   , (VCF::uchar)0xF0, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFFF0FFFF   //  240;255;255
    initColorNameMapItem( "azure1"                  , (VCF::uchar)0xF0, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFFF0FFFF   //  240;255;255
    initColorNameMapItem( "azure2"                  , (VCF::uchar)0xE0, (VCF::uchar)0xEE, (VCF::uchar)0xEE );   // 0xFFE0EEEE   //  224;238;238
    initColorNameMapItem( "azure3"                  , (VCF::uchar)0xC1, (VCF::uchar)0xCD, (VCF::uchar)0xCD );   // 0xFFC1CDCD   //  193;205;205
    initColorNameMapItem( "azure4"                  , (VCF::uchar)0x83, (VCF::uchar)0x8B, (VCF::uchar)0x8B );   // 0xFF838B8B   //  131;139;139
    initColorNameMapItem( "blue"                    , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0xFF );   // 0xFF0000FF   //  0;0;255
    initColorNameMapItem( "blue1"                   , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0xFF );   // 0xFF0000FF   //  0;0;255
    initColorNameMapItem( "blue2"                   , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0xEE );   // 0xFF0000EE   //  0;0;238
    initColorNameMapItem( "blue3"                   , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0xCD );   // 0xFF0000CD   //  0;0;205
    initColorNameMapItem( "blue4"                   , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x8B );   // 0xFF00008B   //  0;0;139
    initColorNameMapItem( "cyan"                    , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFF00FFFF   //  0;255;255
    initColorNameMapItem( "cyan1"                   , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFF00FFFF   //  0;255;255
    initColorNameMapItem( "cyan2"                   , (VCF::uchar)0x00, (VCF::uchar)0xEE, (VCF::uchar)0xEE );   // 0xFF00EEEE   //  0;238;238
    initColorNameMapItem( "cyan3"                   , (VCF::uchar)0x00, (VCF::uchar)0xCD, (VCF::uchar)0xCD );   // 0xFF00CDCD   //  0;205;205
    initColorNameMapItem( "cyan4"                   , (VCF::uchar)0x00, (VCF::uchar)0x8B, (VCF::uchar)0x8B );   // 0xFF008B8B   //  0;139;139
    initColorNameMapItem( "navy"                    , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x80 );   // 0xFF000080   //  0;0;128
    initColorNameMapItem( "turquoise"               , (VCF::uchar)0x40, (VCF::uchar)0xE0, (VCF::uchar)0xD0 );   // 0xFF40E0D0   //  64;224;208
    initColorNameMapItem( "turquoise1"              , (VCF::uchar)0x00, (VCF::uchar)0xF5, (VCF::uchar)0xFF );   // 0xFF00F5FF   //  0;245;255
    initColorNameMapItem( "turquoise2"              , (VCF::uchar)0x00, (VCF::uchar)0xE5, (VCF::uchar)0xEE );   // 0xFF00E5EE   //  0;229;238
    initColorNameMapItem( "turquoise3"              , (VCF::uchar)0x00, (VCF::uchar)0xC5, (VCF::uchar)0xCD );   // 0xFF00C5CD   //  0;197;205
    initColorNameMapItem( "turquoise4"              , (VCF::uchar)0x00, (VCF::uchar)0x86, (VCF::uchar)0x8B );   // 0xFF00868B   //  0;134;139
    initColorNameMapItem( "darkslategray"           , (VCF::uchar)0x2F, (VCF::uchar)0x4F, (VCF::uchar)0x4F );   // 0xFF2F4F4F   //  47;79;79
    initColorNameMapItem( "darkslategray1"          , (VCF::uchar)0x97, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFF97FFFF   //  151;255;255
    initColorNameMapItem( "darkslategray2"          , (VCF::uchar)0x8D, (VCF::uchar)0xEE, (VCF::uchar)0xEE );   // 0xFF8DEEEE   //  141;238;238
    initColorNameMapItem( "darkslategray3"          , (VCF::uchar)0x79, (VCF::uchar)0xCD, (VCF::uchar)0xCD );   // 0xFF79CDCD   //  121;205;205
    initColorNameMapItem( "darkslategray4"          , (VCF::uchar)0x52, (VCF::uchar)0x8B, (VCF::uchar)0x8B );   // 0xFF528B8B   //  82;139;139

    //shades of brown
    //color name r/g/b hex bg/fg color sample
	//						name				 , R			   , G				 , B					// 0xFFRRGGBB
    initColorNameMapItem( "rosybrown"               , (VCF::uchar)0xBC, (VCF::uchar)0x8F, (VCF::uchar)0x8F );   // 0xFFBC8F8F   //  188;143;143
    initColorNameMapItem( "rosybrown1"              , (VCF::uchar)0xFF, (VCF::uchar)0xC1, (VCF::uchar)0xC1 );   // 0xFFFFC1C1   //  255;193;193
    initColorNameMapItem( "rosybrown2"              , (VCF::uchar)0xEE, (VCF::uchar)0xB4, (VCF::uchar)0xB4 );   // 0xFFEEB4B4   //  238;180;180
    initColorNameMapItem( "rosybrown3"              , (VCF::uchar)0xCD, (VCF::uchar)0x9B, (VCF::uchar)0x9B );   // 0xFFCD9B9B   //  205;155;155
    initColorNameMapItem( "rosybrown4"              , (VCF::uchar)0x8B, (VCF::uchar)0x69, (VCF::uchar)0x69 );   // 0xFF8B6969   //  139;105;105
    initColorNameMapItem( "saddlebrown"             , (VCF::uchar)0x8B, (VCF::uchar)0x45, (VCF::uchar)0x13 );   // 0xFF8B4513   //  139;69;19
    initColorNameMapItem( "sandybrown"              , (VCF::uchar)0xF4, (VCF::uchar)0xA4, (VCF::uchar)0x60 );   // 0xFFF4A460   //  244;164;96
    initColorNameMapItem( "beige"                   , (VCF::uchar)0xF5, (VCF::uchar)0xF5, (VCF::uchar)0xDC );   // 0xFFF5F5DC   //  245;245;220
    initColorNameMapItem( "brown"                   , (VCF::uchar)0xA5, (VCF::uchar)0x2A, (VCF::uchar)0x2A );   // 0xFFA52A2A   //  165;42;42
    initColorNameMapItem( "brown1"                  , (VCF::uchar)0xFF, (VCF::uchar)0x40, (VCF::uchar)0x40 );   // 0xFFFF4040   //  255;64;64
    initColorNameMapItem( "brown2"                  , (VCF::uchar)0xEE, (VCF::uchar)0x3B, (VCF::uchar)0x3B );   // 0xFFEE3B3B   //  238;59;59
    initColorNameMapItem( "brown3"                  , (VCF::uchar)0xCD, (VCF::uchar)0x33, (VCF::uchar)0x33 );   // 0xFFCD3333   //  205;51;51
    initColorNameMapItem( "brown4"                  , (VCF::uchar)0x8B, (VCF::uchar)0x23, (VCF::uchar)0x23 );   // 0xFF8B2323   //  139;35;35
    initColorNameMapItem( "burlywood"               , (VCF::uchar)0xDE, (VCF::uchar)0xB8, (VCF::uchar)0x87 );   // 0xFFDEB887   //  222;184;135
    initColorNameMapItem( "burlywood1"              , (VCF::uchar)0xFF, (VCF::uchar)0xD3, (VCF::uchar)0x9B );   // 0xFFFFD39B   //  255;211;155
    initColorNameMapItem( "burlywood2"              , (VCF::uchar)0xEE, (VCF::uchar)0xC5, (VCF::uchar)0x91 );   // 0xFFEEC591   //  238;197;145
    initColorNameMapItem( "burlywood3"              , (VCF::uchar)0xCD, (VCF::uchar)0xAA, (VCF::uchar)0x7D );   // 0xFFCDAA7D   //  205;170;125
    initColorNameMapItem( "burlywood4"              , (VCF::uchar)0x8B, (VCF::uchar)0x73, (VCF::uchar)0x55 );   // 0xFF8B7355   //  139;115;85
    initColorNameMapItem( "chocolate"               , (VCF::uchar)0xD2, (VCF::uchar)0x69, (VCF::uchar)0x1E );   // 0xFFD2691E   //  210;105;30
    initColorNameMapItem( "chocolate1"              , (VCF::uchar)0xFF, (VCF::uchar)0x7F, (VCF::uchar)0x24 );   // 0xFFFF7F24   //  255;127;36
    initColorNameMapItem( "chocolate2"              , (VCF::uchar)0xEE, (VCF::uchar)0x76, (VCF::uchar)0x21 );   // 0xFFEE7621   //  238;118;33
    initColorNameMapItem( "chocolate3"              , (VCF::uchar)0xCD, (VCF::uchar)0x66, (VCF::uchar)0x1D );   // 0xFFCD661D   //  205;102;29
    initColorNameMapItem( "chocolate4"              , (VCF::uchar)0x8B, (VCF::uchar)0x45, (VCF::uchar)0x13 );   // 0xFF8B4513   //  139;69;19
    initColorNameMapItem( "peru"                    , (VCF::uchar)0xCD, (VCF::uchar)0x85, (VCF::uchar)0x3F );   // 0xFFCD853F   //  205;133;63
    initColorNameMapItem( "tan"                     , (VCF::uchar)0xD2, (VCF::uchar)0xB4, (VCF::uchar)0x8C );   // 0xFFD2B48C   //  210;180;140
    initColorNameMapItem( "tan1"                    , (VCF::uchar)0xFF, (VCF::uchar)0xA5, (VCF::uchar)0x4F );   // 0xFFFFA54F   //  255;165;79
    initColorNameMapItem( "tan2"                    , (VCF::uchar)0xEE, (VCF::uchar)0x9A, (VCF::uchar)0x49 );   // 0xFFEE9A49   //  238;154;73
    initColorNameMapItem( "tan3"                    , (VCF::uchar)0xCD, (VCF::uchar)0x85, (VCF::uchar)0x3F );   // 0xFFCD853F   //  205;133;63
    initColorNameMapItem( "tan4"                    , (VCF::uchar)0x8B, (VCF::uchar)0x5A, (VCF::uchar)0x2B );   // 0xFF8B5A2B   //  139;90;43

    //shades of green
    //color name r/g/b hex bg/fg color sample
	//						name				 , R			   , G				 , B					// 0xFFRRGGBB
    initColorNameMapItem( "darkgreen"               , (VCF::uchar)0x00, (VCF::uchar)0x64, (VCF::uchar)0x00 );   // 0xFF006400   //  0;100;0
    initColorNameMapItem( "darkkhaki"               , (VCF::uchar)0xBD, (VCF::uchar)0xB7, (VCF::uchar)0x6B );   // 0xFFBDB76B   //  189;183;107
    initColorNameMapItem( "darkolivegreen"          , (VCF::uchar)0x55, (VCF::uchar)0x6B, (VCF::uchar)0x2F );   // 0xFF556B2F   //  85;107;47
    initColorNameMapItem( "darkolivegreen1"         , (VCF::uchar)0xCA, (VCF::uchar)0xFF, (VCF::uchar)0x70 );   // 0xFFCAFF70   //  202;255;112
    initColorNameMapItem( "darkolivegreen2"         , (VCF::uchar)0xBC, (VCF::uchar)0xEE, (VCF::uchar)0x68 );   // 0xFFBCEE68   //  188;238;104
    initColorNameMapItem( "darkolivegreen3"         , (VCF::uchar)0xA2, (VCF::uchar)0xCD, (VCF::uchar)0x5A );   // 0xFFA2CD5A   //  162;205;90
    initColorNameMapItem( "darkolivegreen4"         , (VCF::uchar)0x6E, (VCF::uchar)0x8B, (VCF::uchar)0x3D );   // 0xFF6E8B3D   //  110;139;61
    initColorNameMapItem( "darkseagreen"            , (VCF::uchar)0x8F, (VCF::uchar)0xBC, (VCF::uchar)0x8F );   // 0xFF8FBC8F   //  143;188;143
    initColorNameMapItem( "darkseagreen1"           , (VCF::uchar)0xC1, (VCF::uchar)0xFF, (VCF::uchar)0xC1 );   // 0xFFC1FFC1   //  193;255;193
    initColorNameMapItem( "darkseagreen2"           , (VCF::uchar)0xB4, (VCF::uchar)0xEE, (VCF::uchar)0xB4 );   // 0xFFB4EEB4   //  180;238;180
    initColorNameMapItem( "darkseagreen3"           , (VCF::uchar)0x9B, (VCF::uchar)0xCD, (VCF::uchar)0x9B );   // 0xFF9BCD9B   //  155;205;155
    initColorNameMapItem( "darkseagreen4"           , (VCF::uchar)0x69, (VCF::uchar)0x8B, (VCF::uchar)0x69 );   // 0xFF698B69   //  105;139;105
    initColorNameMapItem( "forestgreen"             , (VCF::uchar)0x22, (VCF::uchar)0x8B, (VCF::uchar)0x22 );   // 0xFF228B22   //  34;139;34
    initColorNameMapItem( "greenyellow"             , (VCF::uchar)0xAD, (VCF::uchar)0xFF, (VCF::uchar)0x2F );   // 0xFFADFF2F   //  173;255;47
    initColorNameMapItem( "lawngreen"               , (VCF::uchar)0x7C, (VCF::uchar)0xFC, (VCF::uchar)0x00 );   // 0xFF7CFC00   //  124;252;0
    initColorNameMapItem( "lightseagreen"           , (VCF::uchar)0x20, (VCF::uchar)0xB2, (VCF::uchar)0xAA );   // 0xFF20B2AA   //  32;178;170
    initColorNameMapItem( "limegreen"               , (VCF::uchar)0x32, (VCF::uchar)0xCD, (VCF::uchar)0x32 );   // 0xFF32CD32   //  50;205;50
    initColorNameMapItem( "mediumseagreen"          , (VCF::uchar)0x3C, (VCF::uchar)0xB3, (VCF::uchar)0x71 );   // 0xFF3CB371   //  60;179;113
    initColorNameMapItem( "mediumspringgreen"       , (VCF::uchar)0x00, (VCF::uchar)0xFA, (VCF::uchar)0x9A );   // 0xFF00FA9A   //  0;250;154
    initColorNameMapItem( "mintcream"               , (VCF::uchar)0xF5, (VCF::uchar)0xFF, (VCF::uchar)0xFA );   // 0xFFF5FFFA   //  245;255;250
    initColorNameMapItem( "olivedrab"               , (VCF::uchar)0x6B, (VCF::uchar)0x8E, (VCF::uchar)0x23 );   // 0xFF6B8E23   //  107;142;35
    initColorNameMapItem( "olivedrab1"              , (VCF::uchar)0xC0, (VCF::uchar)0xFF, (VCF::uchar)0x3E );   // 0xFFC0FF3E   //  192;255;62
    initColorNameMapItem( "olivedrab2"              , (VCF::uchar)0xB3, (VCF::uchar)0xEE, (VCF::uchar)0x3A );   // 0xFFB3EE3A   //  179;238;58
    initColorNameMapItem( "olivedrab3"              , (VCF::uchar)0x9A, (VCF::uchar)0xCD, (VCF::uchar)0x32 );   // 0xFF9ACD32   //  154;205;50
    initColorNameMapItem( "olivedrab4"              , (VCF::uchar)0x69, (VCF::uchar)0x8B, (VCF::uchar)0x22 );   // 0xFF698B22   //  105;139;34
    initColorNameMapItem( "palegreen"               , (VCF::uchar)0x98, (VCF::uchar)0xFB, (VCF::uchar)0x98 );   // 0xFF98FB98   //  152;251;152
    initColorNameMapItem( "palegreen1"              , (VCF::uchar)0x9A, (VCF::uchar)0xFF, (VCF::uchar)0x9A );   // 0xFF9AFF9A   //  154;255;154
    initColorNameMapItem( "palegreen2"              , (VCF::uchar)0x90, (VCF::uchar)0xEE, (VCF::uchar)0x90 );   // 0xFF90EE90   //  144;238;144
    initColorNameMapItem( "palegreen3"              , (VCF::uchar)0x7C, (VCF::uchar)0xCD, (VCF::uchar)0x7C );   // 0xFF7CCD7C   //  124;205;124
    initColorNameMapItem( "palegreen4"              , (VCF::uchar)0x54, (VCF::uchar)0x8B, (VCF::uchar)0x54 );   // 0xFF548B54   //  84;139;84
    initColorNameMapItem( "seagreen"                , (VCF::uchar)0x2E, (VCF::uchar)0x8B, (VCF::uchar)0x57 );   // 0xFF2E8B57   //  46;139;87
    initColorNameMapItem( "seagreen1"               , (VCF::uchar)0x54, (VCF::uchar)0xFF, (VCF::uchar)0x9F );   // 0xFF54FF9F   //  84;255;159
    initColorNameMapItem( "seagreen2"               , (VCF::uchar)0x4E, (VCF::uchar)0xEE, (VCF::uchar)0x94 );   // 0xFF4EEE94   //  78;238;148
    initColorNameMapItem( "seagreen3"               , (VCF::uchar)0x43, (VCF::uchar)0xCD, (VCF::uchar)0x80 );   // 0xFF43CD80   //  67;205;128
    initColorNameMapItem( "seagreen4"               , (VCF::uchar)0x2E, (VCF::uchar)0x8B, (VCF::uchar)0x57 );   // 0xFF2E8B57   //  46;139;87
    initColorNameMapItem( "springgreen"             , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0x7F );   // 0xFF00FF7F   //  0;255;127
    initColorNameMapItem( "springgreen1"            , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0x7F );   // 0xFF00FF7F   //  0;255;127
    initColorNameMapItem( "springgreen2"            , (VCF::uchar)0x00, (VCF::uchar)0xEE, (VCF::uchar)0x76 );   // 0xFF00EE76   //  0;238;118
    initColorNameMapItem( "springgreen3"            , (VCF::uchar)0x00, (VCF::uchar)0xCD, (VCF::uchar)0x66 );   // 0xFF00CD66   //  0;205;102
    initColorNameMapItem( "springgreen4"            , (VCF::uchar)0x00, (VCF::uchar)0x8B, (VCF::uchar)0x45 );   // 0xFF008B45   //  0;139;69
    initColorNameMapItem( "yellowgreen"             , (VCF::uchar)0x9A, (VCF::uchar)0xCD, (VCF::uchar)0x32 );   // 0xFF9ACD32   //  154;205;50
    initColorNameMapItem( "chartreuse"              , (VCF::uchar)0x7F, (VCF::uchar)0xFF, (VCF::uchar)0x00 );   // 0xFF7FFF00   //  127;255;0
    initColorNameMapItem( "chartreuse1"             , (VCF::uchar)0x7F, (VCF::uchar)0xFF, (VCF::uchar)0x00 );   // 0xFF7FFF00   //  127;255;0
    initColorNameMapItem( "chartreuse2"             , (VCF::uchar)0x76, (VCF::uchar)0xEE, (VCF::uchar)0x00 );   // 0xFF76EE00   //  118;238;0
    initColorNameMapItem( "chartreuse3"             , (VCF::uchar)0x66, (VCF::uchar)0xCD, (VCF::uchar)0x00 );   // 0xFF66CD00   //  102;205;0
    initColorNameMapItem( "chartreuse4"             , (VCF::uchar)0x45, (VCF::uchar)0x8B, (VCF::uchar)0x00 );   // 0xFF458B00   //  69;139;0
    initColorNameMapItem( "green"                   , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0x00 );   // 0xFF00FF00   //  0;255;0
    initColorNameMapItem( "green1"                  , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0x00 );   // 0xFF00FF00   //  0;255;0
    initColorNameMapItem( "green2"                  , (VCF::uchar)0x00, (VCF::uchar)0xEE, (VCF::uchar)0x00 );   // 0xFF00EE00   //  0;238;0
    initColorNameMapItem( "green3"                  , (VCF::uchar)0x00, (VCF::uchar)0xCD, (VCF::uchar)0x00 );   // 0xFF00CD00   //  0;205;0
    initColorNameMapItem( "green4"                  , (VCF::uchar)0x00, (VCF::uchar)0x8B, (VCF::uchar)0x00 );   // 0xFF008B00   //  0;139;0
    initColorNameMapItem( "khaki"                   , (VCF::uchar)0xF0, (VCF::uchar)0xE6, (VCF::uchar)0x8C );   // 0xFFF0E68C   //  240;230;140
    initColorNameMapItem( "khaki1"                  , (VCF::uchar)0xFF, (VCF::uchar)0xF6, (VCF::uchar)0x8F );   // 0xFFFFF68F   //  255;246;143
    initColorNameMapItem( "khaki2"                  , (VCF::uchar)0xEE, (VCF::uchar)0xE6, (VCF::uchar)0x85 );   // 0xFFEEE685   //  238;230;133
    initColorNameMapItem( "khaki3"                  , (VCF::uchar)0xCD, (VCF::uchar)0xC6, (VCF::uchar)0x73 );   // 0xFFCDC673   //  205;198;115
    initColorNameMapItem( "khaki4"                  , (VCF::uchar)0x8B, (VCF::uchar)0x86, (VCF::uchar)0x4E );   // 0xFF8B864E   //  139;134;78

    //shades of orange
    //color name r/g/b hex bg/fg color sample
	//						name				 , R			   , G				 , B					// 0xFFRRGGBB
    initColorNameMapItem( "darkorange"              , (VCF::uchar)0xFF, (VCF::uchar)0x8C, (VCF::uchar)0x00 );   // 0xFFFF8C00   //  255;140;0
    initColorNameMapItem( "darkorange1"             , (VCF::uchar)0xFF, (VCF::uchar)0x7F, (VCF::uchar)0x00 );   // 0xFFFF7F00   //  255;127;0
    initColorNameMapItem( "darkorange2"             , (VCF::uchar)0xEE, (VCF::uchar)0x76, (VCF::uchar)0x00 );   // 0xFFEE7600   //  238;118;0
    initColorNameMapItem( "darkorange3"             , (VCF::uchar)0xCD, (VCF::uchar)0x66, (VCF::uchar)0x00 );   // 0xFFCD6600   //  205;102;0
    initColorNameMapItem( "darkorange4"             , (VCF::uchar)0x8B, (VCF::uchar)0x45, (VCF::uchar)0x00 );   // 0xFF8B4500   //  139;69;0
    initColorNameMapItem( "darksalmon"              , (VCF::uchar)0xE9, (VCF::uchar)0x96, (VCF::uchar)0x7A );   // 0xFFE9967A   //  233;150;122
    initColorNameMapItem( "lightcoral"              , (VCF::uchar)0xF0, (VCF::uchar)0x80, (VCF::uchar)0x80 );   // 0xFFF08080   //  240;128;128
    initColorNameMapItem( "lightsalmon"             , (VCF::uchar)0xFF, (VCF::uchar)0xA0, (VCF::uchar)0x7A );   // 0xFFFFA07A   //  255;160;122
    initColorNameMapItem( "lightsalmon1"            , (VCF::uchar)0xFF, (VCF::uchar)0xA0, (VCF::uchar)0x7A );   // 0xFFFFA07A   //  255;160;122
    initColorNameMapItem( "lightsalmon2"            , (VCF::uchar)0xEE, (VCF::uchar)0x95, (VCF::uchar)0x72 );   // 0xFFEE9572   //  238;149;114
    initColorNameMapItem( "lightsalmon3"            , (VCF::uchar)0xCD, (VCF::uchar)0x81, (VCF::uchar)0x62 );   // 0xFFCD8162   //  205;129;98
    initColorNameMapItem( "lightsalmon4"            , (VCF::uchar)0x8B, (VCF::uchar)0x57, (VCF::uchar)0x42 );   // 0xFF8B5742   //  139;87;66
    initColorNameMapItem( "peachpuff"               , (VCF::uchar)0xFF, (VCF::uchar)0xDA, (VCF::uchar)0xB9 );   // 0xFFFFDAB9   //  255;218;185
    initColorNameMapItem( "peachpuff1"              , (VCF::uchar)0xFF, (VCF::uchar)0xDA, (VCF::uchar)0xB9 );   // 0xFFFFDAB9   //  255;218;185
    initColorNameMapItem( "peachpuff2"              , (VCF::uchar)0xEE, (VCF::uchar)0xCB, (VCF::uchar)0xAD );   // 0xFFEECBAD   //  238;203;173
    initColorNameMapItem( "peachpuff3"              , (VCF::uchar)0xCD, (VCF::uchar)0xAF, (VCF::uchar)0x95 );   // 0xFFCDAF95   //  205;175;149
    initColorNameMapItem( "peachpuff4"              , (VCF::uchar)0x8B, (VCF::uchar)0x77, (VCF::uchar)0x65 );   // 0xFF8B7765   //  139;119;101
    initColorNameMapItem( "bisque"                  , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xC4 );   // 0xFFFFE4C4   //  255;228;196
    initColorNameMapItem( "bisque1"                 , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xC4 );   // 0xFFFFE4C4   //  255;228;196
    initColorNameMapItem( "bisque2"                 , (VCF::uchar)0xEE, (VCF::uchar)0xD5, (VCF::uchar)0xB7 );   // 0xFFEED5B7   //  238;213;183
    initColorNameMapItem( "bisque3"                 , (VCF::uchar)0xCD, (VCF::uchar)0xB7, (VCF::uchar)0x9E );   // 0xFFCDB79E   //  205;183;158
    initColorNameMapItem( "bisque4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x7D, (VCF::uchar)0x6B );   // 0xFF8B7D6B   //  139;125;107
    initColorNameMapItem( "coral"                   , (VCF::uchar)0xFF, (VCF::uchar)0x7F, (VCF::uchar)0x50 );   // 0xFFFF7F50   //  255;127;80
    initColorNameMapItem( "coral1"                  , (VCF::uchar)0xFF, (VCF::uchar)0x72, (VCF::uchar)0x56 );   // 0xFFFF7256   //  255;114;86
    initColorNameMapItem( "coral2"                  , (VCF::uchar)0xEE, (VCF::uchar)0x6A, (VCF::uchar)0x50 );   // 0xFFEE6A50   //  238;106;80
    initColorNameMapItem( "coral3"                  , (VCF::uchar)0xCD, (VCF::uchar)0x5B, (VCF::uchar)0x45 );   // 0xFFCD5B45   //  205;91;69
    initColorNameMapItem( "coral4"                  , (VCF::uchar)0x8B, (VCF::uchar)0x3E, (VCF::uchar)0x2F );   // 0xFF8B3E2F   //  139;62;47
    initColorNameMapItem( "honeydew"                , (VCF::uchar)0xF0, (VCF::uchar)0xFF, (VCF::uchar)0xF0 );   // 0xFFF0FFF0   //  240;255;240
    initColorNameMapItem( "honeydew1"               , (VCF::uchar)0xF0, (VCF::uchar)0xFF, (VCF::uchar)0xF0 );   // 0xFFF0FFF0   //  240;255;240
    initColorNameMapItem( "honeydew2"               , (VCF::uchar)0xE0, (VCF::uchar)0xEE, (VCF::uchar)0xE0 );   // 0xFFE0EEE0   //  224;238;224
    initColorNameMapItem( "honeydew3"               , (VCF::uchar)0xC1, (VCF::uchar)0xCD, (VCF::uchar)0xC1 );   // 0xFFC1CDC1   //  193;205;193
    initColorNameMapItem( "honeydew4"               , (VCF::uchar)0x83, (VCF::uchar)0x8B, (VCF::uchar)0x83 );   // 0xFF838B83   //  131;139;131
    initColorNameMapItem( "orange"                  , (VCF::uchar)0xFF, (VCF::uchar)0xA5, (VCF::uchar)0x00 );   // 0xFFFFA500   //  255;165;0
    initColorNameMapItem( "orange1"                 , (VCF::uchar)0xFF, (VCF::uchar)0xA5, (VCF::uchar)0x00 );   // 0xFFFFA500   //  255;165;0
    initColorNameMapItem( "orange2"                 , (VCF::uchar)0xEE, (VCF::uchar)0x9A, (VCF::uchar)0x00 );   // 0xFFEE9A00   //  238;154;0
    initColorNameMapItem( "orange3"                 , (VCF::uchar)0xCD, (VCF::uchar)0x85, (VCF::uchar)0x00 );   // 0xFFCD8500   //  205;133;0
    initColorNameMapItem( "orange4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x5A, (VCF::uchar)0x00 );   // 0xFF8B5A00   //  139;90;0
    initColorNameMapItem( "salmon"                  , (VCF::uchar)0xFA, (VCF::uchar)0x80, (VCF::uchar)0x72 );   // 0xFFFA8072   //  250;128;114
    initColorNameMapItem( "salmon1"                 , (VCF::uchar)0xFF, (VCF::uchar)0x8C, (VCF::uchar)0x69 );   // 0xFFFF8C69   //  255;140;105
    initColorNameMapItem( "salmon2"                 , (VCF::uchar)0xEE, (VCF::uchar)0x82, (VCF::uchar)0x62 );   // 0xFFEE8262   //  238;130;98
    initColorNameMapItem( "salmon3"                 , (VCF::uchar)0xCD, (VCF::uchar)0x70, (VCF::uchar)0x54 );   // 0xFFCD7054   //  205;112;84
    initColorNameMapItem( "salmon4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x4C, (VCF::uchar)0x39 );   // 0xFF8B4C39   //  139;76;57
    initColorNameMapItem( "sienna"                  , (VCF::uchar)0xA0, (VCF::uchar)0x52, (VCF::uchar)0x2D );   // 0xFFA0522D   //  160;82;45
    initColorNameMapItem( "sienna1"                 , (VCF::uchar)0xFF, (VCF::uchar)0x82, (VCF::uchar)0x47 );   // 0xFFFF8247   //  255;130;71
    initColorNameMapItem( "sienna2"                 , (VCF::uchar)0xEE, (VCF::uchar)0x79, (VCF::uchar)0x42 );   // 0xFFEE7942   //  238;121;66
    initColorNameMapItem( "sienna3"                 , (VCF::uchar)0xCD, (VCF::uchar)0x68, (VCF::uchar)0x39 );   // 0xFFCD6839   //  205;104;57
    initColorNameMapItem( "sienna4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x47, (VCF::uchar)0x26 );   // 0xFF8B4726   //  139;71;38

    //shades of red
    //color name r/g/b hex bg/fg color sample
    initColorNameMapItem( "deeppink"                , (VCF::uchar)0xFF, (VCF::uchar)0x14, (VCF::uchar)0x93 );   // 0xFFFF1493   //  255;20;147
    initColorNameMapItem( "deeppink1"               , (VCF::uchar)0xFF, (VCF::uchar)0x14, (VCF::uchar)0x93 );   // 0xFFFF1493   //  255;20;147
    initColorNameMapItem( "deeppink2"               , (VCF::uchar)0xEE, (VCF::uchar)0x12, (VCF::uchar)0x89 );   // 0xFFEE1289   //  238;18;137
    initColorNameMapItem( "deeppink3"               , (VCF::uchar)0xCD, (VCF::uchar)0x10, (VCF::uchar)0x76 );   // 0xFFCD1076   //  205;16;118
    initColorNameMapItem( "deeppink4"               , (VCF::uchar)0x8B, (VCF::uchar)0x0A, (VCF::uchar)0x50 );   // 0xFF8B0A50   //  139;10;80
    initColorNameMapItem( "hotpink"                 , (VCF::uchar)0xFF, (VCF::uchar)0x69, (VCF::uchar)0xB4 );   // 0xFFFF69B4   //  255;105;180
    initColorNameMapItem( "hotpink1"                , (VCF::uchar)0xFF, (VCF::uchar)0x6E, (VCF::uchar)0xB4 );   // 0xFFFF6EB4   //  255;110;180
    initColorNameMapItem( "hotpink2"                , (VCF::uchar)0xEE, (VCF::uchar)0x6A, (VCF::uchar)0xA7 );   // 0xFFEE6AA7   //  238;106;167
    initColorNameMapItem( "hotpink3"                , (VCF::uchar)0xCD, (VCF::uchar)0x60, (VCF::uchar)0x90 );   // 0xFFCD6090   //  205;96;144
    initColorNameMapItem( "hotpink4"                , (VCF::uchar)0x8B, (VCF::uchar)0x3A, (VCF::uchar)0x62 );   // 0xFF8B3A62   //  139;58;98
    initColorNameMapItem( "indianred"               , (VCF::uchar)0xCD, (VCF::uchar)0x5C, (VCF::uchar)0x5C );   // 0xFFCD5C5C   //  205;92;92
    initColorNameMapItem( "indianred1"              , (VCF::uchar)0xFF, (VCF::uchar)0x6A, (VCF::uchar)0x6A );   // 0xFFFF6A6A   //  255;106;106
    initColorNameMapItem( "indianred2"              , (VCF::uchar)0xEE, (VCF::uchar)0x63, (VCF::uchar)0x63 );   // 0xFFEE6363   //  238;99;99
    initColorNameMapItem( "indianred3"              , (VCF::uchar)0xCD, (VCF::uchar)0x55, (VCF::uchar)0x55 );   // 0xFFCD5555   //  205;85;85
    initColorNameMapItem( "indianred4"              , (VCF::uchar)0x8B, (VCF::uchar)0x3A, (VCF::uchar)0x3A );   // 0xFF8B3A3A   //  139;58;58
    initColorNameMapItem( "lightpink"               , (VCF::uchar)0xFF, (VCF::uchar)0xB6, (VCF::uchar)0xC1 );   // 0xFFFFB6C1   //  255;182;193
    initColorNameMapItem( "lightpink1"              , (VCF::uchar)0xFF, (VCF::uchar)0xAE, (VCF::uchar)0xB9 );   // 0xFFFFAEB9   //  255;174;185
    initColorNameMapItem( "lightpink2"              , (VCF::uchar)0xEE, (VCF::uchar)0xA2, (VCF::uchar)0xAD );   // 0xFFEEA2AD   //  238;162;173
    initColorNameMapItem( "lightpink3"              , (VCF::uchar)0xCD, (VCF::uchar)0x8C, (VCF::uchar)0x95 );   // 0xFFCD8C95   //  205;140;149
    initColorNameMapItem( "lightpink4"              , (VCF::uchar)0x8B, (VCF::uchar)0x5F, (VCF::uchar)0x65 );   // 0xFF8B5F65   //  139;95;101
    initColorNameMapItem( "mediumvioletred"         , (VCF::uchar)0xC7, (VCF::uchar)0x15, (VCF::uchar)0x85 );   // 0xFFC71585   //  199;21;133
    initColorNameMapItem( "mistyrose"               , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xE1 );   // 0xFFFFE4E1   //  255;228;225
    initColorNameMapItem( "mistyrose1"              , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xE1 );   // 0xFFFFE4E1   //  255;228;225
    initColorNameMapItem( "mistyrose2"              , (VCF::uchar)0xEE, (VCF::uchar)0xD5, (VCF::uchar)0xD2 );   // 0xFFEED5D2   //  238;213;210
    initColorNameMapItem( "mistyrose3"              , (VCF::uchar)0xCD, (VCF::uchar)0xB7, (VCF::uchar)0xB5 );   // 0xFFCDB7B5   //  205;183;181
    initColorNameMapItem( "mistyrose4"              , (VCF::uchar)0x8B, (VCF::uchar)0x7D, (VCF::uchar)0x7B );   // 0xFF8B7D7B   //  139;125;123
    initColorNameMapItem( "orangered"               , (VCF::uchar)0xFF, (VCF::uchar)0x45, (VCF::uchar)0x00 );   // 0xFFFF4500   //  255;69;0
    initColorNameMapItem( "orangered1"              , (VCF::uchar)0xFF, (VCF::uchar)0x45, (VCF::uchar)0x00 );   // 0xFFFF4500   //  255;69;0
    initColorNameMapItem( "orangered2"              , (VCF::uchar)0xEE, (VCF::uchar)0x40, (VCF::uchar)0x00 );   // 0xFFEE4000   //  238;64;0
    initColorNameMapItem( "orangered3"              , (VCF::uchar)0xCD, (VCF::uchar)0x37, (VCF::uchar)0x00 );   // 0xFFCD3700   //  205;55;0
    initColorNameMapItem( "orangered4"              , (VCF::uchar)0x8B, (VCF::uchar)0x25, (VCF::uchar)0x00 );   // 0xFF8B2500   //  139;37;0
    initColorNameMapItem( "palevioletred"           , (VCF::uchar)0xDB, (VCF::uchar)0x70, (VCF::uchar)0x93 );   // 0xFFDB7093   //  219;112;147
    initColorNameMapItem( "palevioletred1"          , (VCF::uchar)0xFF, (VCF::uchar)0x82, (VCF::uchar)0xAB );   // 0xFFFF82AB   //  255;130;171
    initColorNameMapItem( "palevioletred2"          , (VCF::uchar)0xEE, (VCF::uchar)0x79, (VCF::uchar)0x9F );   // 0xFFEE799F   //  238;121;159
    initColorNameMapItem( "palevioletred3"          , (VCF::uchar)0xCD, (VCF::uchar)0x68, (VCF::uchar)0x89 );   // 0xFFCD6889   //  205;104;137
    initColorNameMapItem( "palevioletred4"          , (VCF::uchar)0x8B, (VCF::uchar)0x47, (VCF::uchar)0x5D );   // 0xFF8B475D   //  139;71;93
    initColorNameMapItem( "violetred"               , (VCF::uchar)0xD0, (VCF::uchar)0x20, (VCF::uchar)0x90 );   // 0xFFD02090   //  208;32;144
    initColorNameMapItem( "violetred1"              , (VCF::uchar)0xFF, (VCF::uchar)0x3E, (VCF::uchar)0x96 );   // 0xFFFF3E96   //  255;62;150
    initColorNameMapItem( "violetred2"              , (VCF::uchar)0xEE, (VCF::uchar)0x3A, (VCF::uchar)0x8C );   // 0xFFEE3A8C   //  238;58;140
    initColorNameMapItem( "violetred3"              , (VCF::uchar)0xCD, (VCF::uchar)0x32, (VCF::uchar)0x78 );   // 0xFFCD3278   //  205;50;120
    initColorNameMapItem( "violetred4"              , (VCF::uchar)0x8B, (VCF::uchar)0x22, (VCF::uchar)0x52 );   // 0xFF8B2252   //  139;34;82
    initColorNameMapItem( "firebrick"               , (VCF::uchar)0xB2, (VCF::uchar)0x22, (VCF::uchar)0x22 );   // 0xFFB22222   //  178;34;34
    initColorNameMapItem( "firebrick1"              , (VCF::uchar)0xFF, (VCF::uchar)0x30, (VCF::uchar)0x30 );   // 0xFFFF3030   //  255;48;48
    initColorNameMapItem( "firebrick2"              , (VCF::uchar)0xEE, (VCF::uchar)0x2C, (VCF::uchar)0x2C );   // 0xFFEE2C2C   //  238;44;44
    initColorNameMapItem( "firebrick3"              , (VCF::uchar)0xCD, (VCF::uchar)0x26, (VCF::uchar)0x26 );   // 0xFFCD2626   //  205;38;38
    initColorNameMapItem( "firebrick4"              , (VCF::uchar)0x8B, (VCF::uchar)0x1A, (VCF::uchar)0x1A );   // 0xFF8B1A1A   //  139;26;26
    initColorNameMapItem( "pink"                    , (VCF::uchar)0xFF, (VCF::uchar)0xC0, (VCF::uchar)0xCB );   // 0xFFFFC0CB   //  255;192;203
    initColorNameMapItem( "pink1"                   , (VCF::uchar)0xFF, (VCF::uchar)0xB5, (VCF::uchar)0xC5 );   // 0xFFFFB5C5   //  255;181;197
    initColorNameMapItem( "pink2"                   , (VCF::uchar)0xEE, (VCF::uchar)0xA9, (VCF::uchar)0xB8 );   // 0xFFEEA9B8   //  238;169;184
    initColorNameMapItem( "pink3"                   , (VCF::uchar)0xCD, (VCF::uchar)0x91, (VCF::uchar)0x9E );   // 0xFFCD919E   //  205;145;158
    initColorNameMapItem( "pink4"                   , (VCF::uchar)0x8B, (VCF::uchar)0x63, (VCF::uchar)0x6C );   // 0xFF8B636C   //  139;99;108
    initColorNameMapItem( "red"                     , (VCF::uchar)0xFF, (VCF::uchar)0x00, (VCF::uchar)0x00 );   // 0xFFFF0000   //  255;0;0
    initColorNameMapItem( "red1"                    , (VCF::uchar)0xFF, (VCF::uchar)0x00, (VCF::uchar)0x00 );   // 0xFFFF0000   //  255;0;0
    initColorNameMapItem( "red2"                    , (VCF::uchar)0xEE, (VCF::uchar)0x00, (VCF::uchar)0x00 );   // 0xFFEE0000   //  238;0;0
    initColorNameMapItem( "red3"                    , (VCF::uchar)0xCD, (VCF::uchar)0x00, (VCF::uchar)0x00 );   // 0xFFCD0000   //  205;0;0
    initColorNameMapItem( "red4"                    , (VCF::uchar)0x8B, (VCF::uchar)0x00, (VCF::uchar)0x00 );   // 0xFF8B0000   //  139;0;0
    initColorNameMapItem( "tomato"                  , (VCF::uchar)0xFF, (VCF::uchar)0x63, (VCF::uchar)0x47 );   // 0xFFFF6347   //  255;99;71
    initColorNameMapItem( "tomato1"                 , (VCF::uchar)0xFF, (VCF::uchar)0x63, (VCF::uchar)0x47 );   // 0xFFFF6347   //  255;99;71
    initColorNameMapItem( "tomato2"                 , (VCF::uchar)0xEE, (VCF::uchar)0x5C, (VCF::uchar)0x42 );   // 0xFFEE5C42   //  238;92;66
    initColorNameMapItem( "tomato3"                 , (VCF::uchar)0xCD, (VCF::uchar)0x4F, (VCF::uchar)0x39 );   // 0xFFCD4F39   //  205;79;57
    initColorNameMapItem( "tomato4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x36, (VCF::uchar)0x26 );   // 0xFF8B3626   //  139;54;38

    //shades of violet
    //color name r/g/b hex bg/fg color sample
    initColorNameMapItem( "darkorchid"              , (VCF::uchar)0x99, (VCF::uchar)0x32, (VCF::uchar)0xCC );   // 0xFF9932CC   //  153;50;204
    initColorNameMapItem( "darkorchid1"             , (VCF::uchar)0xBF, (VCF::uchar)0x3E, (VCF::uchar)0xFF );   // 0xFFBF3EFF   //  191;62;255
    initColorNameMapItem( "darkorchid2"             , (VCF::uchar)0xB2, (VCF::uchar)0x3A, (VCF::uchar)0xEE );   // 0xFFB23AEE   //  178;58;238
    initColorNameMapItem( "darkorchid3"             , (VCF::uchar)0x9A, (VCF::uchar)0x32, (VCF::uchar)0xCD );   // 0xFF9A32CD   //  154;50;205
    initColorNameMapItem( "darkorchid4"             , (VCF::uchar)0x68, (VCF::uchar)0x22, (VCF::uchar)0x8B );   // 0xFF68228B   //  104;34;139
    initColorNameMapItem( "darkviolet"              , (VCF::uchar)0x94, (VCF::uchar)0x00, (VCF::uchar)0xD3 );   // 0xFF9400D3   //  148;0;211
    initColorNameMapItem( "lavenderblush"           , (VCF::uchar)0xFF, (VCF::uchar)0xF0, (VCF::uchar)0xF5 );   // 0xFFFFF0F5   //  255;240;245
    initColorNameMapItem( "lavenderblush1"          , (VCF::uchar)0xFF, (VCF::uchar)0xF0, (VCF::uchar)0xF5 );   // 0xFFFFF0F5   //  255;240;245
    initColorNameMapItem( "lavenderblush2"          , (VCF::uchar)0xEE, (VCF::uchar)0xE0, (VCF::uchar)0xE5 );   // 0xFFEEE0E5   //  238;224;229
    initColorNameMapItem( "lavenderblush3"          , (VCF::uchar)0xCD, (VCF::uchar)0xC1, (VCF::uchar)0xC5 );   // 0xFFCDC1C5   //  205;193;197
    initColorNameMapItem( "lavenderblush4"          , (VCF::uchar)0x8B, (VCF::uchar)0x83, (VCF::uchar)0x86 );   // 0xFF8B8386   //  139;131;134
    initColorNameMapItem( "mediumorchid"            , (VCF::uchar)0xBA, (VCF::uchar)0x55, (VCF::uchar)0xD3 );   // 0xFFBA55D3   //  186;85;211
    initColorNameMapItem( "mediumorchid1"           , (VCF::uchar)0xE0, (VCF::uchar)0x66, (VCF::uchar)0xFF );   // 0xFFE066FF   //  224;102;255
    initColorNameMapItem( "mediumorchid2"           , (VCF::uchar)0xD1, (VCF::uchar)0x5F, (VCF::uchar)0xEE );   // 0xFFD15FEE   //  209;95;238
    initColorNameMapItem( "mediumorchid3"           , (VCF::uchar)0xB4, (VCF::uchar)0x52, (VCF::uchar)0xCD );   // 0xFFB452CD   //  180;82;205
    initColorNameMapItem( "mediumorchid4"           , (VCF::uchar)0x7A, (VCF::uchar)0x37, (VCF::uchar)0x8B );   // 0xFF7A378B   //  122;55;139
    initColorNameMapItem( "mediumpurple"            , (VCF::uchar)0x93, (VCF::uchar)0x70, (VCF::uchar)0xDB );   // 0xFF9370DB   //  147;112;219
    initColorNameMapItem( "mediumpurple1"           , (VCF::uchar)0xAB, (VCF::uchar)0x82, (VCF::uchar)0xFF );   // 0xFFAB82FF   //  171;130;255
    initColorNameMapItem( "mediumpurple2"           , (VCF::uchar)0x9F, (VCF::uchar)0x79, (VCF::uchar)0xEE );   // 0xFF9F79EE   //  159;121;238
    initColorNameMapItem( "mediumpurple3"           , (VCF::uchar)0x89, (VCF::uchar)0x68, (VCF::uchar)0xCD );   // 0xFF8968CD   //  137;104;205
    initColorNameMapItem( "mediumpurple4"           , (VCF::uchar)0x5D, (VCF::uchar)0x47, (VCF::uchar)0x8B );   // 0xFF5D478B   //  93;71;139
    initColorNameMapItem( "lavender"                , (VCF::uchar)0xE6, (VCF::uchar)0xE6, (VCF::uchar)0xFA );   // 0xFFE6E6FA   //  230;230;250
    initColorNameMapItem( "magenta"                 , (VCF::uchar)0xFF, (VCF::uchar)0x00, (VCF::uchar)0xFF );   // 0xFFFF00FF   //  255;0;255
    initColorNameMapItem( "magenta1"                , (VCF::uchar)0xFF, (VCF::uchar)0x00, (VCF::uchar)0xFF );   // 0xFFFF00FF   //  255;0;255
    initColorNameMapItem( "magenta2"                , (VCF::uchar)0xEE, (VCF::uchar)0x00, (VCF::uchar)0xEE );   // 0xFFEE00EE   //  238;0;238
    initColorNameMapItem( "magenta3"                , (VCF::uchar)0xCD, (VCF::uchar)0x00, (VCF::uchar)0xCD );   // 0xFFCD00CD   //  205;0;205
    initColorNameMapItem( "magenta4"                , (VCF::uchar)0x8B, (VCF::uchar)0x00, (VCF::uchar)0x8B );   // 0xFF8B008B   //  139;0;139
    initColorNameMapItem( "maroon"                  , (VCF::uchar)0xB0, (VCF::uchar)0x30, (VCF::uchar)0x60 );   // 0xFFB03060   //  176;48;96
    initColorNameMapItem( "maroon1"                 , (VCF::uchar)0xFF, (VCF::uchar)0x34, (VCF::uchar)0xB3 );   // 0xFFFF34B3   //  255;52;179
    initColorNameMapItem( "maroon2"                 , (VCF::uchar)0xEE, (VCF::uchar)0x30, (VCF::uchar)0xA7 );   // 0xFFEE30A7   //  238;48;167
    initColorNameMapItem( "maroon3"                 , (VCF::uchar)0xCD, (VCF::uchar)0x29, (VCF::uchar)0x90 );   // 0xFFCD2990   //  205;41;144
    initColorNameMapItem( "maroon4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x1C, (VCF::uchar)0x62 );   // 0xFF8B1C62   //  139;28;98
    initColorNameMapItem( "orchid"                  , (VCF::uchar)0xDA, (VCF::uchar)0x70, (VCF::uchar)0xD6 );   // 0xFFDA70D6   //  218;112;214
    initColorNameMapItem( "orchid1"                 , (VCF::uchar)0xFF, (VCF::uchar)0x83, (VCF::uchar)0xFA );   // 0xFFFF83FA   //  255;131;250
    initColorNameMapItem( "orchid2"                 , (VCF::uchar)0xEE, (VCF::uchar)0x7A, (VCF::uchar)0xE9 );   // 0xFFEE7AE9   //  238;122;233
    initColorNameMapItem( "orchid3"                 , (VCF::uchar)0xCD, (VCF::uchar)0x69, (VCF::uchar)0xC9 );   // 0xFFCD69C9   //  205;105;201
    initColorNameMapItem( "orchid4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x47, (VCF::uchar)0x89 );   // 0xFF8B4789   //  139;71;137
    initColorNameMapItem( "plum"                    , (VCF::uchar)0xDD, (VCF::uchar)0xA0, (VCF::uchar)0xDD );   // 0xFFDDA0DD   //  221;160;221
    initColorNameMapItem( "plum1"                   , (VCF::uchar)0xFF, (VCF::uchar)0xBB, (VCF::uchar)0xFF );   // 0xFFFFBBFF   //  255;187;255
    initColorNameMapItem( "plum2"                   , (VCF::uchar)0xEE, (VCF::uchar)0xAE, (VCF::uchar)0xEE );   // 0xFFEEAEEE   //  238;174;238
    initColorNameMapItem( "plum3"                   , (VCF::uchar)0xCD, (VCF::uchar)0x96, (VCF::uchar)0xCD );   // 0xFFCD96CD   //  205;150;205
    initColorNameMapItem( "plum4"                   , (VCF::uchar)0x8B, (VCF::uchar)0x66, (VCF::uchar)0x8B );   // 0xFF8B668B   //  139;102;139
    initColorNameMapItem( "purple"                  , (VCF::uchar)0xA0, (VCF::uchar)0x20, (VCF::uchar)0xF0 );   // 0xFFA020F0   //  160;32;240
    initColorNameMapItem( "purple1"                 , (VCF::uchar)0x9B, (VCF::uchar)0x30, (VCF::uchar)0xFF );   // 0xFF9B30FF   //  155;48;255
    initColorNameMapItem( "purple2"                 , (VCF::uchar)0x91, (VCF::uchar)0x2C, (VCF::uchar)0xEE );   // 0xFF912CEE   //  145;44;238
    initColorNameMapItem( "purple3"                 , (VCF::uchar)0x7D, (VCF::uchar)0x26, (VCF::uchar)0xCD );   // 0xFF7D26CD   //  125;38;205
    initColorNameMapItem( "purple4"                 , (VCF::uchar)0x55, (VCF::uchar)0x1A, (VCF::uchar)0x8B );   // 0xFF551A8B   //  85;26;139
    initColorNameMapItem( "thistle"                 , (VCF::uchar)0xD8, (VCF::uchar)0xBF, (VCF::uchar)0xD8 );   // 0xFFD8BFD8   //  216;191;216
    initColorNameMapItem( "thistle1"                , (VCF::uchar)0xFF, (VCF::uchar)0xE1, (VCF::uchar)0xFF );   // 0xFFFFE1FF   //  255;225;255
    initColorNameMapItem( "thistle2"                , (VCF::uchar)0xEE, (VCF::uchar)0xD2, (VCF::uchar)0xEE );   // 0xFFEED2EE   //  238;210;238
    initColorNameMapItem( "thistle3"                , (VCF::uchar)0xCD, (VCF::uchar)0xB5, (VCF::uchar)0xCD );   // 0xFFCDB5CD   //  205;181;205
    initColorNameMapItem( "thistle4"                , (VCF::uchar)0x8B, (VCF::uchar)0x7B, (VCF::uchar)0x8B );   // 0xFF8B7B8B   //  139;123;139
    initColorNameMapItem( "violet"                  , (VCF::uchar)0xEE, (VCF::uchar)0x82, (VCF::uchar)0xEE );   // 0xFFEE82EE   //  238;130;238

    //shades of white
    //color name r/g/b hex bg/fg color sample
    initColorNameMapItem( "antiquewhite"            , (VCF::uchar)0xFA, (VCF::uchar)0xEB, (VCF::uchar)0xD7 );   // 0xFFFAEBD7   //  250;235;215
    initColorNameMapItem( "antiquewhite1"           , (VCF::uchar)0xFF, (VCF::uchar)0xEF, (VCF::uchar)0xDB );   // 0xFFFFEFDB   //  255;239;219
    initColorNameMapItem( "antiquewhite2"           , (VCF::uchar)0xEE, (VCF::uchar)0xDF, (VCF::uchar)0xCC );   // 0xFFEEDFCC   //  238;223;204
    initColorNameMapItem( "antiquewhite3"           , (VCF::uchar)0xCD, (VCF::uchar)0xC0, (VCF::uchar)0xB0 );   // 0xFFCDC0B0   //  205;192;176
    initColorNameMapItem( "antiquewhite4"           , (VCF::uchar)0x8B, (VCF::uchar)0x83, (VCF::uchar)0x78 );   // 0xFF8B8378   //  139;131;120
    initColorNameMapItem( "floralwhite"             , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xF0 );   // 0xFFFFFAF0   //  255;250;240
    initColorNameMapItem( "ghostwhite"              , (VCF::uchar)0xF8, (VCF::uchar)0xF8, (VCF::uchar)0xFF );   // 0xFFF8F8FF   //  248;248;255
    initColorNameMapItem( "navajowhite"             , (VCF::uchar)0xFF, (VCF::uchar)0xDE, (VCF::uchar)0xAD );   // 0xFFFFDEAD   //  255;222;173
    initColorNameMapItem( "navajowhite1"            , (VCF::uchar)0xFF, (VCF::uchar)0xDE, (VCF::uchar)0xAD );   // 0xFFFFDEAD   //  255;222;173
    initColorNameMapItem( "navajowhite2"            , (VCF::uchar)0xEE, (VCF::uchar)0xCF, (VCF::uchar)0xA1 );   // 0xFFEECFA1   //  238;207;161
    initColorNameMapItem( "navajowhite3"            , (VCF::uchar)0xCD, (VCF::uchar)0xB3, (VCF::uchar)0x8B );   // 0xFFCDB38B   //  205;179;139
    initColorNameMapItem( "navajowhite4"            , (VCF::uchar)0x8B, (VCF::uchar)0x79, (VCF::uchar)0x5E );   // 0xFF8B795E   //  139;121;94
    initColorNameMapItem( "oldlace"                 , (VCF::uchar)0xFD, (VCF::uchar)0xF5, (VCF::uchar)0xE6 );   // 0xFFFDF5E6   //  253;245;230
    initColorNameMapItem( "whitesmoke"              , (VCF::uchar)0xF5, (VCF::uchar)0xF5, (VCF::uchar)0xF5 );   // 0xFFF5F5F5   //  245;245;245
    initColorNameMapItem( "gainsboro"               , (VCF::uchar)0xDC, (VCF::uchar)0xDC, (VCF::uchar)0xDC );   // 0xFFDCDCDC   //  220;220;220
    initColorNameMapItem( "ivory"                   , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xF0 );   // 0xFFFFFFF0   //  255;255;240
    initColorNameMapItem( "ivory1"                  , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xF0 );   // 0xFFFFFFF0   //  255;255;240
    initColorNameMapItem( "ivory2"                  , (VCF::uchar)0xEE, (VCF::uchar)0xEE, (VCF::uchar)0xE0 );   // 0xFFEEEEE0   //  238;238;224
    initColorNameMapItem( "ivory3"                  , (VCF::uchar)0xCD, (VCF::uchar)0xCD, (VCF::uchar)0xC1 );   // 0xFFCDCDC1   //  205;205;193
    initColorNameMapItem( "ivory4"                  , (VCF::uchar)0x8B, (VCF::uchar)0x8B, (VCF::uchar)0x83 );   // 0xFF8B8B83   //  139;139;131
    initColorNameMapItem( "linen"                   , (VCF::uchar)0xFA, (VCF::uchar)0xF0, (VCF::uchar)0xE6 );   // 0xFFFAF0E6   //  250;240;230
    initColorNameMapItem( "seashell"                , (VCF::uchar)0xFF, (VCF::uchar)0xF5, (VCF::uchar)0xEE );   // 0xFFFFF5EE   //  255;245;238
    initColorNameMapItem( "seashell1"               , (VCF::uchar)0xFF, (VCF::uchar)0xF5, (VCF::uchar)0xEE );   // 0xFFFFF5EE   //  255;245;238
    initColorNameMapItem( "seashell2"               , (VCF::uchar)0xEE, (VCF::uchar)0xE5, (VCF::uchar)0xDE );   // 0xFFEEE5DE   //  238;229;222
    initColorNameMapItem( "seashell3"               , (VCF::uchar)0xCD, (VCF::uchar)0xC5, (VCF::uchar)0xBF );   // 0xFFCDC5BF   //  205;197;191
    initColorNameMapItem( "seashell4"               , (VCF::uchar)0x8B, (VCF::uchar)0x86, (VCF::uchar)0x82 );   // 0xFF8B8682   //  139;134;130
    initColorNameMapItem( "snow"                    , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xFA );   // 0xFFFFFAFA   //  255;250;250
    initColorNameMapItem( "snow1"                   , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xFA );   // 0xFFFFFAFA   //  255;250;250
    initColorNameMapItem( "snow2"                   , (VCF::uchar)0xEE, (VCF::uchar)0xE9, (VCF::uchar)0xE9 );   // 0xFFEEE9E9   //  238;233;233
    initColorNameMapItem( "snow3"                   , (VCF::uchar)0xCD, (VCF::uchar)0xC9, (VCF::uchar)0xC9 );   // 0xFFCDC9C9   //  205;201;201
    initColorNameMapItem( "snow4"                   , (VCF::uchar)0x8B, (VCF::uchar)0x89, (VCF::uchar)0x89 );   // 0xFF8B8989   //  139;137;137
    initColorNameMapItem( "wheat"                   , (VCF::uchar)0xF5, (VCF::uchar)0xDE, (VCF::uchar)0xB3 );   // 0xFFF5DEB3   //  245;222;179
    initColorNameMapItem( "wheat1"                  , (VCF::uchar)0xFF, (VCF::uchar)0xE7, (VCF::uchar)0xBA );   // 0xFFFFE7BA   //  255;231;186
    initColorNameMapItem( "wheat2"                  , (VCF::uchar)0xEE, (VCF::uchar)0xD8, (VCF::uchar)0xAE );   // 0xFFEED8AE   //  238;216;174
    initColorNameMapItem( "wheat3"                  , (VCF::uchar)0xCD, (VCF::uchar)0xBA, (VCF::uchar)0x96 );   // 0xFFCDBA96   //  205;186;150
    initColorNameMapItem( "wheat4"                  , (VCF::uchar)0x8B, (VCF::uchar)0x7E, (VCF::uchar)0x66 );   // 0xFF8B7E66   //  139;126;102
    initColorNameMapItem( "white"                   , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xFF );   // 0xFFFFFFFF   //  255;255;255

    //shades of yellow
    //color name r/g/b hex bg/fg color sample
    initColorNameMapItem( "blanchedalmond"          , (VCF::uchar)0xFF, (VCF::uchar)0xEB, (VCF::uchar)0xCD );   // 0xFFFFEBCD   //  255;235;205
    initColorNameMapItem( "darkgoldenrod"           , (VCF::uchar)0xB8, (VCF::uchar)0x86, (VCF::uchar)0x0B );   // 0xFFB8860B   //  184;134;11
    initColorNameMapItem( "darkgoldenrod1"          , (VCF::uchar)0xFF, (VCF::uchar)0xB9, (VCF::uchar)0x0F );   // 0xFFFFB90F   //  255;185;15
    initColorNameMapItem( "darkgoldenrod2"          , (VCF::uchar)0xEE, (VCF::uchar)0xAD, (VCF::uchar)0x0E );   // 0xFFEEAD0E   //  238;173;14
    initColorNameMapItem( "darkgoldenrod3"          , (VCF::uchar)0xCD, (VCF::uchar)0x95, (VCF::uchar)0x0C );   // 0xFFCD950C   //  205;149;12
    initColorNameMapItem( "darkgoldenrod4"          , (VCF::uchar)0x8B, (VCF::uchar)0x65, (VCF::uchar)0x08 );   // 0xFF8B6508   //  139;101;8
    initColorNameMapItem( "lemonchiffon"            , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xCD );   // 0xFFFFFACD   //  255;250;205
    initColorNameMapItem( "lemonchiffon1"           , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xCD );   // 0xFFFFFACD   //  255;250;205
    initColorNameMapItem( "lemonchiffon2"           , (VCF::uchar)0xEE, (VCF::uchar)0xE9, (VCF::uchar)0xBF );   // 0xFFEEE9BF   //  238;233;191
    initColorNameMapItem( "lemonchiffon3"           , (VCF::uchar)0xCD, (VCF::uchar)0xC9, (VCF::uchar)0xA5 );   // 0xFFCDC9A5   //  205;201;165
    initColorNameMapItem( "lemonchiffon4"           , (VCF::uchar)0x8B, (VCF::uchar)0x89, (VCF::uchar)0x70 );   // 0xFF8B8970   //  139;137;112
    initColorNameMapItem( "lightgoldenrod"          , (VCF::uchar)0xEE, (VCF::uchar)0xDD, (VCF::uchar)0x82 );   // 0xFFEEDD82   //  238;221;130
    initColorNameMapItem( "lightgoldenrod1"         , (VCF::uchar)0xFF, (VCF::uchar)0xEC, (VCF::uchar)0x8B );   // 0xFFFFEC8B   //  255;236;139
    initColorNameMapItem( "lightgoldenrod2"         , (VCF::uchar)0xEE, (VCF::uchar)0xDC, (VCF::uchar)0x82 );   // 0xFFEEDC82   //  238;220;130
    initColorNameMapItem( "lightgoldenrod3"         , (VCF::uchar)0xCD, (VCF::uchar)0xBE, (VCF::uchar)0x70 );   // 0xFFCDBE70   //  205;190;112
    initColorNameMapItem( "lightgoldenrod4"         , (VCF::uchar)0x8B, (VCF::uchar)0x81, (VCF::uchar)0x4C );   // 0xFF8B814C   //  139;129;76
    initColorNameMapItem( "lightgoldenrodyellow"    , (VCF::uchar)0xFA, (VCF::uchar)0xFA, (VCF::uchar)0xD2 );   // 0xFFFAFAD2   //  250;250;210
    initColorNameMapItem( "lightyellow"             , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xE0 );   // 0xFFFFFFE0   //  255;255;224
    initColorNameMapItem( "lightyellow1"            , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xE0 );   // 0xFFFFFFE0   //  255;255;224
    initColorNameMapItem( "lightyellow2"            , (VCF::uchar)0xEE, (VCF::uchar)0xEE, (VCF::uchar)0xD1 );   // 0xFFEEEED1   //  238;238;209
    initColorNameMapItem( "lightyellow3"            , (VCF::uchar)0xCD, (VCF::uchar)0xCD, (VCF::uchar)0xB4 );   // 0xFFCDCDB4   //  205;205;180
    initColorNameMapItem( "lightyellow4"            , (VCF::uchar)0x8B, (VCF::uchar)0x8B, (VCF::uchar)0x7A );   // 0xFF8B8B7A   //  139;139;122
    initColorNameMapItem( "palegoldenrod"           , (VCF::uchar)0xEE, (VCF::uchar)0xE8, (VCF::uchar)0xAA );   // 0xFFEEE8AA   //  238;232;170
    initColorNameMapItem( "papayawhip"              , (VCF::uchar)0xFF, (VCF::uchar)0xEF, (VCF::uchar)0xD5 );   // 0xFFFFEFD5   //  255;239;213
    initColorNameMapItem( "cornsilk"                , (VCF::uchar)0xFF, (VCF::uchar)0xF8, (VCF::uchar)0xDC );   // 0xFFFFF8DC   //  255;248;220
    initColorNameMapItem( "cornsilk1"               , (VCF::uchar)0xFF, (VCF::uchar)0xF8, (VCF::uchar)0xDC );   // 0xFFFFF8DC   //  255;248;220
    initColorNameMapItem( "cornsilk2"               , (VCF::uchar)0xEE, (VCF::uchar)0xE8, (VCF::uchar)0xCD );   // 0xFFEEE8CD   //  238;232;205
    initColorNameMapItem( "cornsilk3"               , (VCF::uchar)0xCD, (VCF::uchar)0xC8, (VCF::uchar)0xB1 );   // 0xFFCDC8B1   //  205;200;177
    initColorNameMapItem( "cornsilk4"               , (VCF::uchar)0x8B, (VCF::uchar)0x88, (VCF::uchar)0x78 );   // 0xFF8B8878   //  139;136;120
    initColorNameMapItem( "gold"                    , (VCF::uchar)0xFF, (VCF::uchar)0xD7, (VCF::uchar)0x00 );   // 0xFFFFD700   //  255;215;0
    initColorNameMapItem( "gold1"                   , (VCF::uchar)0xFF, (VCF::uchar)0xD7, (VCF::uchar)0x00 );   // 0xFFFFD700   //  255;215;0
    initColorNameMapItem( "gold2"                   , (VCF::uchar)0xEE, (VCF::uchar)0xC9, (VCF::uchar)0x00 );   // 0xFFEEC900   //  238;201;0
    initColorNameMapItem( "gold3"                   , (VCF::uchar)0xCD, (VCF::uchar)0xAD, (VCF::uchar)0x00 );   // 0xFFCDAD00   //  205;173;0
    initColorNameMapItem( "gold4"                   , (VCF::uchar)0x8B, (VCF::uchar)0x75, (VCF::uchar)0x00 );   // 0xFF8B7500   //  139;117;0
    initColorNameMapItem( "goldenrod"               , (VCF::uchar)0xDA, (VCF::uchar)0xA5, (VCF::uchar)0x20 );   // 0xFFDAA520   //  218;165;32
    initColorNameMapItem( "goldenrod1"              , (VCF::uchar)0xFF, (VCF::uchar)0xC1, (VCF::uchar)0x25 );   // 0xFFFFC125   //  255;193;37
    initColorNameMapItem( "goldenrod2"              , (VCF::uchar)0xEE, (VCF::uchar)0xB4, (VCF::uchar)0x22 );   // 0xFFEEB422   //  238;180;34
    initColorNameMapItem( "goldenrod3"              , (VCF::uchar)0xCD, (VCF::uchar)0x9B, (VCF::uchar)0x1D );   // 0xFFCD9B1D   //  205;155;29
    initColorNameMapItem( "goldenrod4"              , (VCF::uchar)0x8B, (VCF::uchar)0x69, (VCF::uchar)0x14 );   // 0xFF8B6914   //  139;105;20
    initColorNameMapItem( "moccasin"                , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xB5 );   // 0xFFFFE4B5   //  255;228;181
    initColorNameMapItem( "yellow"                  , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0x00 );   // 0xFFFFFF00   //  255;255;0
    initColorNameMapItem( "yellow1"                 , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0x00 );   // 0xFFFFFF00   //  255;255;0
    initColorNameMapItem( "yellow2"                 , (VCF::uchar)0xEE, (VCF::uchar)0xEE, (VCF::uchar)0x00 );   // 0xFFEEEE00   //  238;238;0
    initColorNameMapItem( "yellow3"                 , (VCF::uchar)0xCD, (VCF::uchar)0xCD, (VCF::uchar)0x00 );   // 0xFFCDCD00   //  205;205;0
    initColorNameMapItem( "yellow4"                 , (VCF::uchar)0x8B, (VCF::uchar)0x8B, (VCF::uchar)0x00 );   // 0xFF8B8B00   //  139;139;0

    //metal rgb according to netscape
    //color name r/g/b hex bg/fg color sample
    initColorNameMapItem( "copper"                  , (VCF::uchar)0xB8, (VCF::uchar)0x73, (VCF::uchar)0x33 );   // 0xFFB87333   //  184;115;51
    initColorNameMapItem( "gold"                    , (VCF::uchar)0xCD, (VCF::uchar)0x7F, (VCF::uchar)0x32 );   // 0xFFCD7F32   //  205;127;50
    initColorNameMapItem( "silver"                  , (VCF::uchar)0xE6, (VCF::uchar)0xE8, (VCF::uchar)0xFA );   // 0xFFE6E8FA   //  230;232;250

#else

    initColorNameMapItem( "aliceblue"            , (VCF::uchar)0xF0, (VCF::uchar)0xF8, (VCF::uchar)0xFF );  // 0xFFF0F8FF
    initColorNameMapItem( "antiquewhite"         , (VCF::uchar)0xFA, (VCF::uchar)0xEB, (VCF::uchar)0xD7 );  // 0xFFFAEBD7
    initColorNameMapItem( "aqua"                 , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0xFF );  // 0xFF00FFFF
    initColorNameMapItem( "aquamarine"           , (VCF::uchar)0x7F, (VCF::uchar)0xFF, (VCF::uchar)0xD4 );  // 0xFF7FFFD4
    initColorNameMapItem( "azure"                , (VCF::uchar)0xF0, (VCF::uchar)0xFF, (VCF::uchar)0xFF );  // 0xFFF0FFFF
    initColorNameMapItem( "beige"                , (VCF::uchar)0xF5, (VCF::uchar)0xF5, (VCF::uchar)0xDC );  // 0xFFF5F5DC
    initColorNameMapItem( "bisque"               , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xC4 );  // 0xFFFFE4C4
    initColorNameMapItem( "black"                , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x00 );  // 0xFF000000
    initColorNameMapItem( "blanchedalmond"       , (VCF::uchar)0xFF, (VCF::uchar)0xEB, (VCF::uchar)0xCD );  // 0xFFFFEBCD
    initColorNameMapItem( "blue"                 , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0xFF );  // 0xFF0000FF
    initColorNameMapItem( "blueviolet"           , (VCF::uchar)0x8A, (VCF::uchar)0x2B, (VCF::uchar)0xE2 );  // 0xFF8A2BE2
    initColorNameMapItem( "brown"                , (VCF::uchar)0xA5, (VCF::uchar)0x2A, (VCF::uchar)0x2A );  // 0xFFA52A2A
    initColorNameMapItem( "burlywood"            , (VCF::uchar)0xDE, (VCF::uchar)0xB8, (VCF::uchar)0x87 );  // 0xFFDEB887
    initColorNameMapItem( "cadetblue"            , (VCF::uchar)0x5F, (VCF::uchar)0x9E, (VCF::uchar)0xA0 );  // 0xFF5F9EA0
    initColorNameMapItem( "chartreuse"           , (VCF::uchar)0x7F, (VCF::uchar)0xFF, (VCF::uchar)0x00 );  // 0xFF7FFF00
    initColorNameMapItem( "chocolate"            , (VCF::uchar)0xD2, (VCF::uchar)0x69, (VCF::uchar)0x1E );  // 0xFFD2691E
    initColorNameMapItem( "coral"                , (VCF::uchar)0xFF, (VCF::uchar)0x7F, (VCF::uchar)0x50 );  // 0xFFFF7F50
    initColorNameMapItem( "cornflowerblue"       , (VCF::uchar)0x64, (VCF::uchar)0x95, (VCF::uchar)0xED );  // 0xFF6495ED
    initColorNameMapItem( "cornsilk"             , (VCF::uchar)0xFF, (VCF::uchar)0xF8, (VCF::uchar)0xDC );  // 0xFFFFF8DC
    initColorNameMapItem( "crimson"              , (VCF::uchar)0xDC, (VCF::uchar)0x14, (VCF::uchar)0x3C );  // 0xFFDC143C
    initColorNameMapItem( "cyan"                 , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0xFF );  // 0xFF00FFFF
    initColorNameMapItem( "darkblue"             , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x8B );  // 0xFF00008B
    initColorNameMapItem( "darkcyan"             , (VCF::uchar)0x00, (VCF::uchar)0x8B, (VCF::uchar)0x8B );  // 0xFF008B8B
    initColorNameMapItem( "darkgoldenrod"        , (VCF::uchar)0xB8, (VCF::uchar)0x86, (VCF::uchar)0x0B );  // 0xFFB8860B
    initColorNameMapItem( "darkgray"             , (VCF::uchar)0xA9, (VCF::uchar)0xA9, (VCF::uchar)0xA9 );  // 0xFFA9A9A9
    initColorNameMapItem( "darkgreen"            , (VCF::uchar)0x00, (VCF::uchar)0x64, (VCF::uchar)0x00 );  // 0xFF006400
    initColorNameMapItem( "darkkhaki"            , (VCF::uchar)0xBD, (VCF::uchar)0xB7, (VCF::uchar)0x6B );  // 0xFFBDB76B
    initColorNameMapItem( "darkmagenta"          , (VCF::uchar)0x8B, (VCF::uchar)0x00, (VCF::uchar)0x8B );  // 0xFF8B008B
    initColorNameMapItem( "darkolivegreen"       , (VCF::uchar)0x55, (VCF::uchar)0x6B, (VCF::uchar)0x2F );  // 0xFF556B2F
    initColorNameMapItem( "darkorange"           , (VCF::uchar)0xFF, (VCF::uchar)0x8C, (VCF::uchar)0x00 );  // 0xFFFF8C00
    initColorNameMapItem( "darkorchid"           , (VCF::uchar)0x99, (VCF::uchar)0x32, (VCF::uchar)0xCC );  // 0xFF9932CC
    initColorNameMapItem( "darkred"              , (VCF::uchar)0x8B, (VCF::uchar)0x00, (VCF::uchar)0x00 );  // 0xFF8B0000
    initColorNameMapItem( "darksalmon"           , (VCF::uchar)0xE9, (VCF::uchar)0x96, (VCF::uchar)0x7A );  // 0xFFE9967A
    initColorNameMapItem( "darkseagreen"         , (VCF::uchar)0x8F, (VCF::uchar)0xBC, (VCF::uchar)0x8B );  // 0xFF8FBC8B
    initColorNameMapItem( "darkslateblue"        , (VCF::uchar)0x48, (VCF::uchar)0x3D, (VCF::uchar)0x8B );  // 0xFF483D8B
    initColorNameMapItem( "darkslategray"        , (VCF::uchar)0x2F, (VCF::uchar)0x4F, (VCF::uchar)0x4F );  // 0xFF2F4F4F
    initColorNameMapItem( "darkturquoise"        , (VCF::uchar)0x00, (VCF::uchar)0xCE, (VCF::uchar)0xD1 );  // 0xFF00CED1
    initColorNameMapItem( "darkviolet"           , (VCF::uchar)0x94, (VCF::uchar)0x00, (VCF::uchar)0xD3 );  // 0xFF9400D3
    initColorNameMapItem( "deeppink"             , (VCF::uchar)0xFF, (VCF::uchar)0x14, (VCF::uchar)0x93 );  // 0xFFFF1493
    initColorNameMapItem( "deepskyblue"          , (VCF::uchar)0x00, (VCF::uchar)0xBF, (VCF::uchar)0xFF );  // 0xFF00BFFF
    initColorNameMapItem( "dimgray"              , (VCF::uchar)0x69, (VCF::uchar)0x69, (VCF::uchar)0x69 );  // 0xFF696969
    initColorNameMapItem( "dodgerblue"           , (VCF::uchar)0x1E, (VCF::uchar)0x90, (VCF::uchar)0xFF );  // 0xFF1E90FF
    initColorNameMapItem( "firebrick"            , (VCF::uchar)0xB2, (VCF::uchar)0x22, (VCF::uchar)0x22 );  // 0xFFB22222
    initColorNameMapItem( "floralwhite"          , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xF0 );  // 0xFFFFFAF0
    initColorNameMapItem( "forestgreen"          , (VCF::uchar)0x22, (VCF::uchar)0x8B, (VCF::uchar)0x22 );  // 0xFF228B22
    initColorNameMapItem( "fuchsia"              , (VCF::uchar)0xFF, (VCF::uchar)0x00, (VCF::uchar)0xFF );  // 0xFFFF00FF
    initColorNameMapItem( "gainsboro"            , (VCF::uchar)0xDC, (VCF::uchar)0xDC, (VCF::uchar)0xDC );  // 0xFFDCDCDC
    initColorNameMapItem( "ghostwhite"           , (VCF::uchar)0xF8, (VCF::uchar)0xF8, (VCF::uchar)0xFF );  // 0xFFF8F8FF
    initColorNameMapItem( "gold"                 , (VCF::uchar)0xFF, (VCF::uchar)0xD7, (VCF::uchar)0x00 );  // 0xFFFFD700
    initColorNameMapItem( "goldenrod"            , (VCF::uchar)0xDA, (VCF::uchar)0xA5, (VCF::uchar)0x20 );  // 0xFFDAA520
    initColorNameMapItem( "gray"                 , (VCF::uchar)0x80, (VCF::uchar)0x80, (VCF::uchar)0x80 );  // 0xFF808080
    initColorNameMapItem( "green"                , (VCF::uchar)0x00, (VCF::uchar)0x80, (VCF::uchar)0x00 );  // 0xFF008000
    initColorNameMapItem( "greenyellow"          , (VCF::uchar)0xAD, (VCF::uchar)0xFF, (VCF::uchar)0x2F );  // 0xFFADFF2F
    initColorNameMapItem( "honeydew"             , (VCF::uchar)0xF0, (VCF::uchar)0xFF, (VCF::uchar)0xF0 );  // 0xFFF0FFF0
    initColorNameMapItem( "hotpink"              , (VCF::uchar)0xFF, (VCF::uchar)0x69, (VCF::uchar)0xB4 );  // 0xFFFF69B4
    initColorNameMapItem( "indianred"            , (VCF::uchar)0xCD, (VCF::uchar)0x5C, (VCF::uchar)0x5C );  // 0xFFCD5C5C
    initColorNameMapItem( "indigo"               , (VCF::uchar)0x4B, (VCF::uchar)0x00, (VCF::uchar)0x82 );  // 0xFF4B0082
    initColorNameMapItem( "ivory"                , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xF0 );  // 0xFFFFFFF0
    initColorNameMapItem( "khaki"                , (VCF::uchar)0xF0, (VCF::uchar)0xE6, (VCF::uchar)0x8C );  // 0xFFF0E68C
    initColorNameMapItem( "lavender"             , (VCF::uchar)0xE6, (VCF::uchar)0xE6, (VCF::uchar)0xFA );  // 0xFFE6E6FA
    initColorNameMapItem( "lavenderblush"        , (VCF::uchar)0xFF, (VCF::uchar)0xF0, (VCF::uchar)0xF5 );  // 0xFFFFF0F5
    initColorNameMapItem( "lawngreen"            , (VCF::uchar)0x7C, (VCF::uchar)0xFC, (VCF::uchar)0x00 );  // 0xFF7CFC00
    initColorNameMapItem( "lemonchiffon"         , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xCD );  // 0xFFFFFACD
    initColorNameMapItem( "lightblue"            , (VCF::uchar)0xAD, (VCF::uchar)0xD8, (VCF::uchar)0xE6 );  // 0xFFADD8E6
    initColorNameMapItem( "lightcoral"           , (VCF::uchar)0xF0, (VCF::uchar)0x80, (VCF::uchar)0x80 );  // 0xFFF08080
    initColorNameMapItem( "lightcyan"            , (VCF::uchar)0xE0, (VCF::uchar)0xFF, (VCF::uchar)0xFF );  // 0xFFE0FFFF
    initColorNameMapItem( "lightgoldenrodyellow" , (VCF::uchar)0xFA, (VCF::uchar)0xFA, (VCF::uchar)0xD2 );  // 0xFFFAFAD2
    initColorNameMapItem( "lightgray"            , (VCF::uchar)0xD3, (VCF::uchar)0xD3, (VCF::uchar)0xD3 );  // 0xFFD3D3D3
    initColorNameMapItem( "lightgreen"           , (VCF::uchar)0x90, (VCF::uchar)0xEE, (VCF::uchar)0x90 );  // 0xFF90EE90
    initColorNameMapItem( "lightpink"            , (VCF::uchar)0xFF, (VCF::uchar)0xB6, (VCF::uchar)0xC1 );  // 0xFFFFB6C1
    initColorNameMapItem( "lightsalmon"          , (VCF::uchar)0xFF, (VCF::uchar)0xA0, (VCF::uchar)0x7A );  // 0xFFFFA07A
    initColorNameMapItem( "lightseagreen"        , (VCF::uchar)0x20, (VCF::uchar)0xB2, (VCF::uchar)0xAA );  // 0xFF20B2AA
    initColorNameMapItem( "lightskyblue"         , (VCF::uchar)0x87, (VCF::uchar)0xCE, (VCF::uchar)0xFA );  // 0xFF87CEFA
    initColorNameMapItem( "lightslategray"       , (VCF::uchar)0x77, (VCF::uchar)0x88, (VCF::uchar)0x99 );  // 0xFF778899
    initColorNameMapItem( "lightsteelblue"       , (VCF::uchar)0xB0, (VCF::uchar)0xC4, (VCF::uchar)0xDE );  // 0xFFB0C4DE
    initColorNameMapItem( "lightyellow"          , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xE0 );  // 0xFFFFFFE0
    initColorNameMapItem( "lime"                 , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0x00 );  // 0xFF00FF00
    initColorNameMapItem( "limegreen"            , (VCF::uchar)0x32, (VCF::uchar)0xCD, (VCF::uchar)0x32 );  // 0xFF32CD32
    initColorNameMapItem( "linen"                , (VCF::uchar)0xFA, (VCF::uchar)0xF0, (VCF::uchar)0xE6 );  // 0xFFFAF0E6
    initColorNameMapItem( "magenta"              , (VCF::uchar)0xFF, (VCF::uchar)0x00, (VCF::uchar)0xFF );  // 0xFFFF00FF
    initColorNameMapItem( "maroon"               , (VCF::uchar)0x80, (VCF::uchar)0x00, (VCF::uchar)0x00 );  // 0xFF800000
    initColorNameMapItem( "mediumaquamarine"     , (VCF::uchar)0x66, (VCF::uchar)0xCD, (VCF::uchar)0xAA );  // 0xFF66CDAA
    initColorNameMapItem( "mediumblue"           , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0xCD );  // 0xFF0000CD
    initColorNameMapItem( "mediumorchid"         , (VCF::uchar)0xBA, (VCF::uchar)0x55, (VCF::uchar)0xD3 );  // 0xFFBA55D3
    initColorNameMapItem( "mediumpurple"         , (VCF::uchar)0x93, (VCF::uchar)0x70, (VCF::uchar)0xDB );  // 0xFF9370DB
    initColorNameMapItem( "mediumseagreen"       , (VCF::uchar)0x3C, (VCF::uchar)0xB3, (VCF::uchar)0x71 );  // 0xFF3CB371
    initColorNameMapItem( "mediumslateblue"      , (VCF::uchar)0x7B, (VCF::uchar)0x68, (VCF::uchar)0xEE );  // 0xFF7B68EE
    initColorNameMapItem( "mediumspringgreen"    , (VCF::uchar)0x00, (VCF::uchar)0xFA, (VCF::uchar)0x9A );  // 0xFF00FA9A
    initColorNameMapItem( "mediumturquoise"      , (VCF::uchar)0x48, (VCF::uchar)0xD1, (VCF::uchar)0xCC );  // 0xFF48D1CC
    initColorNameMapItem( "mediumvioletred"      , (VCF::uchar)0xC7, (VCF::uchar)0x15, (VCF::uchar)0x85 );  // 0xFFC71585
    initColorNameMapItem( "midnightblue"         , (VCF::uchar)0x19, (VCF::uchar)0x19, (VCF::uchar)0x70 );  // 0xFF191970
    initColorNameMapItem( "mintcream"            , (VCF::uchar)0xF5, (VCF::uchar)0xFF, (VCF::uchar)0xFA );  // 0xFFF5FFFA
    initColorNameMapItem( "mistyrose"            , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xE1 );  // 0xFFFFE4E1
    initColorNameMapItem( "moccasin"             , (VCF::uchar)0xFF, (VCF::uchar)0xE4, (VCF::uchar)0xB5 );  // 0xFFFFE4B5
    initColorNameMapItem( "navajowhite"          , (VCF::uchar)0xFF, (VCF::uchar)0xDE, (VCF::uchar)0xAD );  // 0xFFFFDEAD
    initColorNameMapItem( "navy"                 , (VCF::uchar)0x00, (VCF::uchar)0x00, (VCF::uchar)0x80 );  // 0xFF000080
    initColorNameMapItem( "oldlace"              , (VCF::uchar)0xFD, (VCF::uchar)0xF5, (VCF::uchar)0xE6 );  // 0xFFFDF5E6
    initColorNameMapItem( "olive"                , (VCF::uchar)0x80, (VCF::uchar)0x80, (VCF::uchar)0x00 );  // 0xFF808000
    initColorNameMapItem( "olivedrab"            , (VCF::uchar)0x6B, (VCF::uchar)0x8E, (VCF::uchar)0x23 );  // 0xFF6B8E23
    initColorNameMapItem( "orange"               , (VCF::uchar)0xFF, (VCF::uchar)0xA5, (VCF::uchar)0x00 );  // 0xFFFFA500
    initColorNameMapItem( "orangered"            , (VCF::uchar)0xFF, (VCF::uchar)0x45, (VCF::uchar)0x00 );  // 0xFFFF4500
    initColorNameMapItem( "orchid"               , (VCF::uchar)0xDA, (VCF::uchar)0x70, (VCF::uchar)0xD6 );  // 0xFFDA70D6
    initColorNameMapItem( "palegoldenrod"        , (VCF::uchar)0xEE, (VCF::uchar)0xE8, (VCF::uchar)0xAA );  // 0xFFEEE8AA
    initColorNameMapItem( "palegreen"            , (VCF::uchar)0x98, (VCF::uchar)0xFB, (VCF::uchar)0x98 );  // 0xFF98FB98
    initColorNameMapItem( "paleturquoise"        , (VCF::uchar)0xAF, (VCF::uchar)0xEE, (VCF::uchar)0xEE );  // 0xFFAFEEEE
    initColorNameMapItem( "palevioletred"        , (VCF::uchar)0xDB, (VCF::uchar)0x70, (VCF::uchar)0x93 );  // 0xFFDB7093
    initColorNameMapItem( "papayawhip"           , (VCF::uchar)0xFF, (VCF::uchar)0xEF, (VCF::uchar)0xD5 );  // 0xFFFFEFD5
    initColorNameMapItem( "peachpuff"            , (VCF::uchar)0xFF, (VCF::uchar)0xDA, (VCF::uchar)0xB9 );  // 0xFFFFDAB9
    initColorNameMapItem( "peru"                 , (VCF::uchar)0xCD, (VCF::uchar)0x85, (VCF::uchar)0x3F );  // 0xFFCD853F
    initColorNameMapItem( "pink"                 , (VCF::uchar)0xFF, (VCF::uchar)0xC0, (VCF::uchar)0xCB );  // 0xFFFFC0CB
    initColorNameMapItem( "plum"                 , (VCF::uchar)0xDD, (VCF::uchar)0xA0, (VCF::uchar)0xDD );  // 0xFFDDA0DD
    initColorNameMapItem( "powderblue"           , (VCF::uchar)0xB0, (VCF::uchar)0xE0, (VCF::uchar)0xE6 );  // 0xFFB0E0E6
    initColorNameMapItem( "purple"               , (VCF::uchar)0x80, (VCF::uchar)0x00, (VCF::uchar)0x80 );  // 0xFF800080
    initColorNameMapItem( "red"                  , (VCF::uchar)0xFF, (VCF::uchar)0x00, (VCF::uchar)0x00 );  // 0xFFFF0000
    initColorNameMapItem( "rosybrown"            , (VCF::uchar)0xBC, (VCF::uchar)0x8F, (VCF::uchar)0x8F );  // 0xFFBC8F8F
    initColorNameMapItem( "royalblue"            , (VCF::uchar)0x41, (VCF::uchar)0x69, (VCF::uchar)0xE1 );  // 0xFF4169E1
    initColorNameMapItem( "saddlebrown"          , (VCF::uchar)0x8B, (VCF::uchar)0x45, (VCF::uchar)0x13 );  // 0xFF8B4513
    initColorNameMapItem( "salmon"               , (VCF::uchar)0xFA, (VCF::uchar)0x80, (VCF::uchar)0x72 );  // 0xFFFA8072
    initColorNameMapItem( "sandybrown"           , (VCF::uchar)0xF4, (VCF::uchar)0xA4, (VCF::uchar)0x60 );  // 0xFFF4A460
    initColorNameMapItem( "seagreen"             , (VCF::uchar)0x2E, (VCF::uchar)0x8B, (VCF::uchar)0x57 );  // 0xFF2E8B57
    initColorNameMapItem( "seashell"             , (VCF::uchar)0xFF, (VCF::uchar)0xF5, (VCF::uchar)0xEE );  // 0xFFFFF5EE
    initColorNameMapItem( "sienna"               , (VCF::uchar)0xA0, (VCF::uchar)0x52, (VCF::uchar)0x2D );  // 0xFFA0522D
    initColorNameMapItem( "silver"               , (VCF::uchar)0xC0, (VCF::uchar)0xC0, (VCF::uchar)0xC0 );  // 0xFFC0C0C0
    initColorNameMapItem( "skyblue"              , (VCF::uchar)0x87, (VCF::uchar)0xCE, (VCF::uchar)0xEB );  // 0xFF87CEEB
    initColorNameMapItem( "slateblue"            , (VCF::uchar)0x6A, (VCF::uchar)0x5A, (VCF::uchar)0xCD );  // 0xFF6A5ACD
    initColorNameMapItem( "slategray"            , (VCF::uchar)0x70, (VCF::uchar)0x80, (VCF::uchar)0x90 );  // 0xFF708090
    initColorNameMapItem( "snow"                 , (VCF::uchar)0xFF, (VCF::uchar)0xFA, (VCF::uchar)0xFA );  // 0xFFFFFAFA
    initColorNameMapItem( "springgreen"          , (VCF::uchar)0x00, (VCF::uchar)0xFF, (VCF::uchar)0x7F );  // 0xFF00FF7F
    initColorNameMapItem( "steelblue"            , (VCF::uchar)0x46, (VCF::uchar)0x82, (VCF::uchar)0xB4 );  // 0xFF4682B4
    initColorNameMapItem( "tan"                  , (VCF::uchar)0xD2, (VCF::uchar)0xB4, (VCF::uchar)0x8C );  // 0xFFD2B48C
    initColorNameMapItem( "teal"                 , (VCF::uchar)0x00, (VCF::uchar)0x80, (VCF::uchar)0x80 );  // 0xFF008080
    initColorNameMapItem( "thistle"              , (VCF::uchar)0xD8, (VCF::uchar)0xBF, (VCF::uchar)0xD8 );  // 0xFFD8BFD8
    initColorNameMapItem( "tomato"               , (VCF::uchar)0xFF, (VCF::uchar)0x63, (VCF::uchar)0x47 );  // 0xFFFF6347
    initColorNameMapItem( "turquoise"            , (VCF::uchar)0x40, (VCF::uchar)0xE0, (VCF::uchar)0xD0 );  // 0xFF40E0D0
    initColorNameMapItem( "violet"               , (VCF::uchar)0xEE, (VCF::uchar)0x82, (VCF::uchar)0xEE );  // 0xFFEE82EE
    initColorNameMapItem( "wheat"                , (VCF::uchar)0xF5, (VCF::uchar)0xDE, (VCF::uchar)0xB3 );  // 0xFFF5DEB3
    initColorNameMapItem( "white"                , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xFF );  // 0xFFFFFFFF
    initColorNameMapItem( "whitesmoke"           , (VCF::uchar)0xF5, (VCF::uchar)0xF5, (VCF::uchar)0xF5 );  // 0xFFF5F5F5
    initColorNameMapItem( "yellow"               , (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0x00 );  // 0xFFFFFF00
    initColorNameMapItem( "yellowgreen"          , (VCF::uchar)0x9A, (VCF::uchar)0xCD, (VCF::uchar)0x32 );  // 0xFF9ACD32

    //colorMap_["transparent"]           =   new Color( (VCF::uchar)0xFF, (VCF::uchar)0xFF, (VCF::uchar)0xFF );    // 0x00FFFFFF

    //colorMap_[WHITE]                   =   new Color( 1.0f, 1.0f, 1.0f );
    //colorMap_[BLACK]                   =   new Color( 0.0f, 0.0f, 0.0f );
    //colorMap_[GRAY]                    =   new Color( 0.5f, 0.5f, 0.5f );
    //colorMap_[YELLOW]                  =   new Color( 1.0f, 1.0f, 0.0f );
    //colorMap_[GREEN]                   =   new Color( 0.0f, 1.0f, 0.0f );
    //colorMap_[BLUE]                    =   new Color( 0.0f, 0.0f, 1.0f );
    //colorMap_[RED]                     =   new Color( 1.0f, 0.0f, 0.0f );
    //colorMap_[PURPLE]                  =   new Color( 0.5f, 0.0f, 1.0f );
    //colorMap_[LT_BLUE]                 =   new Color( 0.0f, 1.0f, 1.0f );


#endif	// VCF_LARGE_COLOR_LIST


	String name;
	for (int c = 0; c <= 255; c++) {
		name = Format("gray%d") % c;
		initColorNameMapItem( name, (VCF::uchar)c, (VCF::uchar)c, (VCF::uchar)c );	// 0xFFF0F8FF
	}


}


void GraphicsToolkit::initColorNameMapItem( const VCF::String& colorName, const uint8& r, const uint8& g, const uint8& b)
{
	MapStringColor::iterator found = colorMap_.find( colorName );
	if ( found != colorMap_.end() ) {
		// we update the color values associated to the color name 
		// and prevent memory leak
		Color* clr = found->second;

		// what happens if we are using the color map inside a loop somewherelse ?
		// May we get into an infinite loop ? I think no, if the loop is well written.
		clr->setRGB8( r, g, b );

		// we keep only one color for the same color name
		MapStringColorName::iterator it = colorNameMap_->begin();
		while ( it != colorNameMap_->end() ) {
			String name = it->second;
			if ( name == colorName ) {
				colorNameMap_->erase( it );
				(*colorNameMap_)[*clr] = colorName;
				break;
			}
			++it;
		}
	}
	else {
		Color* color = new Color( (VCF::uchar)r, (VCF::uchar)g, (VCF::uchar)b );

		colorMap_[colorName] = color;
		(*colorNameMap_)[*color] = colorName;
	}
}

void GraphicsToolkit::destroyColorMaps()
{
	MapStringColor::iterator it = colorMap_.begin();
	while ( it != colorMap_.end() ){
		Color* c = it->second;
		delete c;
		c = NULL;
		it ++;
	}
	colorMap_.clear();


	if ( NULL != colorNameMap_ ) {
		// can be destroyed indipendently from colorMap_
		//MapStringColorName::const_iterator it2 = colorNameMap_->begin();
		//while ( it2 != colorNameMap_->end() ){
		//	const String* s = it2->second;
		//	delete s;
		//	s = NULL;
		//	it2 ++;
		//}
		colorNameMap_->clear();
		delete colorNameMap_;
	}
}

void GraphicsToolkit::destroySystemColorNameMap()
{
	// can be destroyed indipendently from systemColorMap_
	//MapStringColorName::const_iterator it = systemColorNameMap_->begin();
	//while ( it != systemColorNameMap_->end() ){
	//	const String* s = it->second;
	//	delete s;
	//	s = NULL;
	//	it ++;
	//}

	if ( systemColorNameMap_ ) {
		systemColorNameMap_->clear();
		delete systemColorNameMap_;
	}
}


/**
$Id$
*/
