#ifndef _VCF_DESKTOP_H__
#define _VCF_DESKTOP_H__
//Desktop.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class GraphicsContext;

class DesktopPeer;

/**
\class Desktop Desktop.h "vcf/ApplicationKit/Desktop.h"
The desktop represents the Windowing systems bottom most
control or "window" and is usually the first window the 
User sees when the system starts up. The Desktop is also 
sometimes refered to as the Shell, as in Microsoft Windows. 
A desktop may or may not allow files, i.e. it in fact is
an actual location on the filesystem.
*/
class APPLICATIONKIT_API Desktop : public VCF::Object {
public:
	static Desktop* create();

	Desktop();

	virtual ~Desktop();

	GraphicsContext* getContext() {
		return context_;
	}

	/**
	*Prepares the desktop for painting.
	*MUST be called before calling getContext(), or errors
	*may occur
	*@param Rect* specifies an optional rectangular region to clip
	*the drawing to. The rectangles coords are screen coords.
	*/
	void beginPainting( Rect* clippingRect = NULL);

	/**
	*called after finished painting on the desktop
	*allows for native Windowing system cleanup to happen
	*/
	void endPainting();

	bool supportsVirtualDirectories();


	bool hasFileSystemDirectory();

	String getDirectory();

	DesktopPeer* getDesktopPeer() {
		return peer_;
	}

	static Desktop* getDesktop() {
		return Desktop::desktopInstance;
	}

	ulong32 getWidth();

	ulong32 getHeight();

	Rect getUsableBounds();

	Point getCurrentMousePosition();
	/**
	*called by the UIToolkit. repeated calls after the first initialization
	*do nothing
	*/
	void init();
protected:


	static Desktop* desktopInstance;
	GraphicsContext* context_;
	bool paintingInitialized_;
	DesktopPeer* peer_;
private:
};


}; //end of namespace VCF


#endif // _VCF_DESKTOP_H__

/**
$Id$
*/
