#ifndef _VCF_HTMLBROWSERPEER_H__
#define _VCF_HTMLBROWSERPEER_H__
//HTMLBrowserPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
*HTMLBrowserPeer describes
*a generic interface for a browser control.
*Since browsers have become so common, as well as useful,
*it has been added to the set of peers for the ApplicationKit.
*/
class APPLICATIONKIT_API HTMLBrowserPeer : public VCF::Interface {
public:
	virtual ~HTMLBrowserPeer(){};

	virtual String getCurrentURL() = 0;

	virtual void setCurrentURL( const String& url ) = 0;

	virtual void goBack() = 0;

	virtual void goForward() = 0;

	virtual void goHome() = 0;

	virtual void refresh() = 0;

	virtual bool isLoadingURL() = 0;

	virtual void stopLoadingURL() = 0;

	virtual void setFromHTML( const String& html ) = 0;
protected:

private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.26.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.3.26.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.3  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_HTMLBROWSERPEER_H__


