//X11Application.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/X11Application.h"


using namespace VCF;

X11Application::X11Application():
	app_(NULL),
	handleID_(0)
{

}

X11Application::~X11Application()
{

}


bool X11Application::initApp( const std::vector<VCF::String>& appCmdLine )
{
	bool result = true;

	//do X11 specific start up crap here

	return result;
}

void X11Application::terminateApp()
{

}


void X11Application::setApplication( VCF::AbstractApplication* application )
{
	app_ = application;
}

ResourceBundle* X11Application::getResourceBundle()
{
	return NULL;
}

String X11Application::getFileName()
{
	String result;

	return result;
}

String X11Application::getCurrentDirectory()
{
	String result;

	return result;
}

void X11Application::setCurrentDirectory( const String& currentDirectory )
{

}

long X11Application::getHandleID()
{
	return handleID_;
}

void X11Application::setHandleID( const long& handleID )
{
	handleID_ = handleID;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:39  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.2.1  2003/03/12 03:12:44  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2002/12/26 04:44:12  ddiego
*odds and ends
*
*Revision 1.1.2.1  2002/12/26 04:32:11  ddiego
*added basic peer implementation to ApplicationKit so that we can now create
*a VERY simple application and terminate correctly. Woohoo! First steps
*of running on linux!
*
Auto generated C++ implementation for class X11Application
*/


