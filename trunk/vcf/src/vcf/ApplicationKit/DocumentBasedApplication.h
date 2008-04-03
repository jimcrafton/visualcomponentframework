#ifndef _VCF_DOCUMENTBASEDAPPLICATION_H__
#define _VCF_DOCUMENTBASEDAPPLICATION_H__
//DocumentBasedApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class DocumentBasedApplication DocumentBasedApplication.h "vcf/ApplicationKit/DocumentBasedApplication.h"
*/
template <typename DocInterfacePolicy >
class DocumentBasedApplication : public Application,
								public DocumentManagerImpl< DocumentBasedApplication<DocInterfacePolicy>, DocInterfacePolicy> {
public:

	DocumentBasedApplication( int argc, char** argv ) : Application(argc, argv){

	}

	typedef DocumentManagerImpl<DocumentBasedApplication<DocInterfacePolicy>,DocInterfacePolicy> DocMgrImpl;

	virtual bool initRunningApplication() {
		Application::initRunningApplication();

		DocMgrImpl::init();

		const CommandLine& comdLine = FoundationKit::getCommandLine();
		if ( comdLine.hasSwitch( REGISTERDOCTYPES ) ) {
			return false; //exit the app
		}


		DocMgrImpl::createMenus();

		return true;
	}	

	void terminateRunningApplication() {
		DocMgrImpl::terminate();

		Application::terminateRunningApplication();
	}
};



typedef DocumentBasedApplication<SDIPolicy> SDIDocumentBasedApplication;
typedef DocumentBasedApplication<MDIPolicy> MDIDocumentBasedApplication;


};


#endif // _VCF_DOCUMENTBASEDAPPLICATION_H__

/**
$Id$
*/
