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
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:23  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
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
*Revision 1.5  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.2.1  2003/08/25 03:14:01  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.4  2003/08/09 02:56:46  ddiego
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
*Revision 1.3.2.3  2003/07/10 04:55:16  ddiego
*added more stuff to GTK port - fixed some issues with events, and
*added support for posting events, and the stubs for a ButtonPeer
*
*Revision 1.3.2.2  2003/06/01 16:44:00  ddiego
*further GTK support added
*
*Revision 1.3.2.1  2003/05/30 04:13:11  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.3  2003/05/17 20:37:33  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.4  2003/04/19 22:22:56  ddiego
*tested the code developed in windows using gtk in linux. Seems to work ok except for a
*few minor compiler glitches. Had to comment out the partial specialization for
*floating point image bits in include/graphics/ImageBits.h. Also made some
*adjustments in the makefiles for building the GraphicsKit and ApplicationKit
*from the build/make/Makefile.
*
*Revision 1.2.2.3  2003/04/17 04:29:51  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.2.2.2  2003/04/14 19:06:26  ddiego
*mods to add better support for fonts and text using Pango. Not
*finished and may not compile! :)
*
*Revision 1.2.2.1  2003/03/12 03:12:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:48  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/20 02:46:03  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
Auto generated C++ implementation for class GTKGraphicsToolkit
*/


