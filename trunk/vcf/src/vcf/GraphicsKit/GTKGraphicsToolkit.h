#ifndef _VCF_GTKGRAPHICSTOOLKIT_H__
#define _VCF_GTKGRAPHICSTOOLKIT_H__ 
//GTKGraphicsToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

/**
 
*/
class GRAPHICSKIT_API GTKGraphicsToolkit : public GraphicsToolkit
{
public:

	GTKGraphicsToolkit();

	virtual ~GTKGraphicsToolkit();

	virtual ContextPeer* internal_createContextPeer( const unsigned long& width,
	                                                 const unsigned long& height );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual FontPeer* internal_createFontPeer( const String& fontName );

	virtual FontPeer* internal_createFontPeer( const String& fontName,
	                                           const double& pointSize );

	virtual Image* internal_createImage( const unsigned long& width,
	                                     const unsigned long& height );

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect );

	virtual Font* getDefaultSystemFont()
	{
		return systemFont_;
	}

	PangoContext* getGTKPangoContext()
	{
		return gtkPangoContext_;
	}

	bool isInitialized()
	{
		return initialized_;
	}

	void init();

	virtual double getDPI();

	GtkStyle* getDefaultGTKStyle()
	{
		return defaultGTKStyle_;
	}

	virtual PrintSessionPeer* internal_createPrintSessionPeer();

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer();

	virtual double internal_getDPI( GraphicsContext* context );
	
protected:
	bool initialized_;
	Font* systemFont_;
	PangoContext* gtkPangoContext_;
	GtkStyle* defaultGTKStyle_;

	void loadSystemColors();
	void initSystemFont();
};


}
; //end of namespace VCF


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
*Revision 1.5.4.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.2.1  2003/08/25 03:13:44  ddiego
*adjusted the gtk peers to account for the new toolkit method names
*
*Revision 1.4  2003/08/09 02:56:44  ddiego
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
*Revision 1.3.2.1  2003/06/01 16:43:59  ddiego
*further GTK support added
*
*Revision 1.3  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.3  2003/04/17 04:29:49  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.2.2.2  2003/04/14 19:10:31  ddiego
*mods to better support fonts and text using Pango - not finished, and
*may not compile
*
*Revision 1.2.2.1  2003/03/12 03:10:53  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/20 02:46:02  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Auto generated header for class GTKGraphicsToolkit
*/


#endif // _VCF_GTKGRAPHICSTOOLKIT_H__


