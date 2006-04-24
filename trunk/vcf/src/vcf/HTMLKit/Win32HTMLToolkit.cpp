//Win32HTMLToolkit.cpp

#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/Win32HTMLToolkit.h"
#include "vcf/ApplicationKit/Win32Object.h"
#include "vcf/ApplicationKit/AbstractWin32Component.h"
#include "vcf/HTMLKit/Win32HTMLBrowser.h"


using namespace VCF;



Win32HTMLToolkit::Win32HTMLToolkit()
{

}

Win32HTMLToolkit::~Win32HTMLToolkit()
{

}

HTMLBrowserPeer* Win32HTMLToolkit::internal_createHTMLBrowserPeer( Control* control )
{
	HTMLBrowserPeer* result = new Win32HTMLBrowser();
	ControlPeer* controlPeer = dynamic_cast<ControlPeer*>( result );
	controlPeer->setControl( control );

	return result;
}