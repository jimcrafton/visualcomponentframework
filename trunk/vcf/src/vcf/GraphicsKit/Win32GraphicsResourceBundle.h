
#ifndef _WIN32GRAPHICSRESOURCEBUNDLE_H__
#define _WIN32GRAPHICSRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/Win32ResourceBundle.h"


namespace VCF  {

class GRAPHICSKIT_API Win32GraphicsResourceBundle : public Win32ResourceBundle, public GraphicsResourceBundlePeer {
public:
	Win32GraphicsResourceBundle();

	virtual ~Win32GraphicsResourceBundle();

	
	/**
	*returns an Image based on a given resource name
	*/
	virtual Image* getImage( const String& resourceName );

	
protected:
	
	
};

};




/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/02 03:04:26  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.2.1  2004/12/19 07:09:20  ddiego
*more modifications to better handle resource bundles, especially
*if they are part of a LibraryApplication instance.
*
*Revision 1.2  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/08/27 03:50:48  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*/







#endif //_WIN32GRAPHICSRESOURCEBUNDLE_H__



