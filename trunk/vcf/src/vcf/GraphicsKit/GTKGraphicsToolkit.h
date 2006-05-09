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

	virtual Image* internal_createImage( const unsigned long& width, const unsigned long& height, const Image::ImageType& imageType );

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType );

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

	virtual void internal_systemSettingsChanged();
	
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


#endif // _VCF_GTKGRAPHICSTOOLKIT_H__

/**
$Id$
*/
