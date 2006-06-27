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

int32 X11Application::getHandleID()
{
	return handleID_;
}

void X11Application::setHandleID( const int32& handleID )
{
	handleID_ = handleID;
}


/**
$Id$
*/
