//Win32Component.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Component.h"

using namespace VCF;
using namespace VCFWin32;


Win32Component::Win32Component( Control* component ):
	AbstractWin32Component( component )
{

}

Win32Component::~Win32Component()
{

}

void Win32Component::create( Control* owningControl )
{
	String className = "VCF::Win32Component";
	if ( true != isRegistered() ){
		registerWin32Class( className, wndProc_  );
	}

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	CreateParams params = createParams();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second, className.c_str(),
									 L"",	params.first,
		                             0, 0,
									 1,
									 1,
									 parent,
									 NULL, ::GetModuleHandleW(NULL), NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( params.second, className.ansi_c_str(),
									 "",	params.first,
		                             0, 0,
									 1,
									 1,
									 parent,
									 NULL, ::GetModuleHandleA(NULL), NULL );
	}


	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );
		registerForFontChanges();
	}
	else {
		//throw exception
	}

	setCreated( true );
}


/**
$Id$
*/
