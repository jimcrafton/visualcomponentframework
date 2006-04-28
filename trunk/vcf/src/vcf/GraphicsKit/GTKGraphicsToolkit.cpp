//GTKGraphicsToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"



using namespace VCF;



GTKGraphicsToolkit::GTKGraphicsToolkit() :
		initialized_( false ),
		defaultGTKStyle_( NULL )
{
	GraphicsToolkit::graphicsToolkitInstance = this;

	CommandLine commandLine = FoundationKit::getCommandLine();
	Enumerator<String>* commands = commandLine.getOriginalCommands();
	int argc = commandLine.getArgCount();
	char** argv = new char * [ argc ];

	int i = 0;
	while ( commands->hasMoreElements() ) {
		String command = commands->nextElement();
		argv[ i ] = new char[ command.size() + 1 ];
		command.copy( argv[ i ], command.size() );
		argv[ i ][ command.size() ] = 0;
		i++;
	}

	gtk_init( &argc, &argv );


	gtkPangoContext_ = gdk_pango_context_get();

	//initialize the default style instance here

	defaultGTKStyle_ = gtk_style_new();

	GdkColormap* cm = gdk_colormap_get_system ();
	defaultGTKStyle_->colormap = ( GdkColormap* ) g_object_ref ( cm );
	defaultGTKStyle_->depth = gdk_colormap_get_visual ( cm ) ->depth;

	GTK_STYLE_GET_CLASS ( defaultGTKStyle_ ) ->realize ( defaultGTKStyle_ );



	if ( NULL == gtkPangoContext_ ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "gdk_pango_context_get() failed, probably cause gtk_init() wasn't called " ) );
	} else {
		initialized_ = true;
		loadSystemColors();

		initSystemFont();
	}

	for ( i = 0;i < argc;i++ ) {
		delete [] argv[ i ];
	}
	delete argv;
}

GTKGraphicsToolkit::~GTKGraphicsToolkit()
{
	delete systemFont_;

	g_object_unref( defaultGTKStyle_ );
	g_object_unref( gtkPangoContext_ );
}

void GTKGraphicsToolkit::init()
{}

void GTKGraphicsToolkit::initSystemFont()
{
	/*
	this was just a quick to test to see font names
	int n_families = 0;
	PangoFontFamily **  families_;
	pango_context_list_families ( gtkPangoContext_, &families_, &n_families);

	for (int i=0; i<n_families; i++)   {
	     const char *name = pango_font_family_get_name (families_[i]);
	  StringUtils::traceWithArgs( "font family name @ %d, %s\n", i, name );
	   }
	*/

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


ContextPeer*
GTKGraphicsToolkit::internal_createContextPeer( const unsigned long& width,
                                                const unsigned long& height )
{
	return new GTKContext( width, height );
}

ContextPeer* GTKGraphicsToolkit::internal_createContextPeer( OSHandleID contextID )
{
	return new GTKContext( contextID );
}

FontPeer* GTKGraphicsToolkit::internal_createFontPeer( const String& fontName )
{
	return new GTKFont( fontName );
}

FontPeer* GTKGraphicsToolkit::internal_createFontPeer( const String& fontName,
                                                       const double& pointSize )
{
	return new GTKFont( fontName, pointSize );
}


Image* GTKGraphicsToolkit::internal_createImage( const unsigned long& width,
                                                 const unsigned long& height )
{
	return new GTKImage( width, height );
}

Image* GTKGraphicsToolkit::internal_createImage( GraphicsContext* context,
                                                 Rect* rect )
{
	return new GTKImage( context, rect );
}


PrintSessionPeer* GTKGraphicsToolkit::internal_createPrintSessionPeer()
{
	return 0;
}

GraphicsResourceBundlePeer* GTKGraphicsToolkit::internal_createGraphicsResourceBundlePeer()
{
	return 0; //new GTKGraphicsResourceBundle();
}

double GTKGraphicsToolkit::internal_getDPI( GraphicsContext* context )
{}

void GTKGraphicsToolkit::loadSystemColors()
{


	//style has initial values that are already set - use these
	//look in the style->fg, style->bg, style->text



	GdkColor color;

	Color* sysColor = NULL;
	color = defaultGTKStyle_->dark[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );

	systemColors_[ SYSCOLOR_SHADOW ] = sysColor;

	color = defaultGTKStyle_->bg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_FACE ] = sysColor;

	color = defaultGTKStyle_->light[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_HIGHLIGHT ] = sysColor;

	color = defaultGTKStyle_->text[ GTK_STATE_ACTIVE ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_ACTIVE_CAPTION ] = sysColor;

	color = defaultGTKStyle_->fg[ GTK_STATE_ACTIVE ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_ACTIVE_BORDER ] = sysColor;

	color = defaultGTKStyle_->fg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_DESKTOP ] = sysColor;

	color = defaultGTKStyle_->text[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_CAPTION_TEXT ] = sysColor;

	color = defaultGTKStyle_->base[ GTK_STATE_SELECTED ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_SELECTION ] = sysColor;

	color = defaultGTKStyle_->text[ GTK_STATE_SELECTED ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_SELECTION_TEXT ] = sysColor;

	color = defaultGTKStyle_->fg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_INACTIVE_BORDER ] = sysColor;

	color = defaultGTKStyle_->bg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_INACTIVE_CAPTION ] = sysColor;

	color = defaultGTKStyle_->bg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_TOOLTIP ] = sysColor;


	color = defaultGTKStyle_->text[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_TOOLTIP_TEXT ] = sysColor;

	color = defaultGTKStyle_->fg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_MENU ] = sysColor;

	color = defaultGTKStyle_->fg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_MENU_TEXT ] = sysColor;

	color = defaultGTKStyle_->base[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_WINDOW ] = sysColor;

	color = defaultGTKStyle_->text[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_WINDOW_TEXT ] = sysColor;

	color = defaultGTKStyle_->fg[ GTK_STATE_NORMAL ];
	sysColor = new Color( ( ( double ) color.red ) / 65535.0,
	                      ( ( double ) color.green ) / 65535.0,
	                      ( ( double ) color.blue ) / 65535.0 );
	systemColors_[ SYSCOLOR_WINDOW_FRAME ] = sysColor;

}

double GTKGraphicsToolkit::getDPI()
{
	double result = 0.0;

	double mmHeight = gdk_screen_height_mm(); // gdk_screen_get_default () );
	double height = gdk_screen_get_height( gdk_screen_get_default () );

	result = height / ( mmHeight / 25.4 );

	return result;
}


/**
$Id$
*/
