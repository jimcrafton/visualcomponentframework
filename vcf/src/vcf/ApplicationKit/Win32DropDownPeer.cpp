//Win32DropDownPeer.cpp



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/DropDownPeer.h"
#include "vcf/ApplicationKit/Win32DropDownPeer.h"
#include "vcf/ApplicationKit/ListModel.h"



using namespace VCFWin32;
using namespace VCF;


Win32DropDownPeer::Win32DropDownPeer()
{

}

Win32DropDownPeer::~Win32DropDownPeer()
{

}

void Win32DropDownPeer::create( Control* owningControl )
{
	CreateParams params = createParams();
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
		                             L"COMBOBOX",
									 NULL,
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( params.second,
		                             "COMBOBOX",
									 NULL,
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}

	if ( NULL != hwnd_ ){
		peerControl_ = owningControl;

		Win32Object::registerWin32Object( this );

		subclassWindow();
		registerForFontChanges();

		CallBack* cb = 
			new ClassProcedure1<Event*,Win32DropDownPeer>( this, &Win32DropDownPeer::onCtrlModelChanged, "Win32DropDownPeer::onCtrlModelChanged" );

		owningControl->ControlModelChanged += cb;

		cb = 
			new ClassProcedure1<Event*,Win32DropDownPeer>( this, &Win32DropDownPeer::onListModelChanged, "Win32DropDownPeer::onListModelChanged" );

		setCreated( true );
	}
}

Win32Object::CreateParams Win32DropDownPeer::createParams()
{
	Win32Object::CreateParams result;
	result.first = BORDERED_VIEW | CBS_AUTOHSCROLL | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED |CBS_NOINTEGRALHEIGHT;
	//result.first &= ~WS_BORDER;

	result.second = 0;

	return result;
}

bool Win32DropDownPeer::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc)
{
	bool result = false;
	wndProcResult = 0;

	return result;
}

void Win32DropDownPeer::enableEditBox( bool val )
{

}

bool Win32DropDownPeer::editBoxEnabled()
{
	return false;
}

void Win32DropDownPeer::setEditText( const String& text )
{
	
}

String Win32DropDownPeer::getEditText()
{
	return getText();
}

void Win32DropDownPeer::setDropDownWidth( double val )
{
	//CB_SETDROPPEDWIDTH
}

double Win32DropDownPeer::getDropDownWidth()
{
	return 0.0;
}

void Win32DropDownPeer::setDropDownCount( const uint32& dropDownCount )
{

}

void Win32DropDownPeer::onCtrlModelChanged( Event* e )
{
 	Model* model = peerControl_->getViewModel();
	model->ModelChanged += getCallback( "Win32DropDownPeer::onListModelChanged" );		
}

void Win32DropDownPeer::onListModelChanged( Event* e )
{
	ListModel* lm = (ListModel*)e->getSource();

	
	
	InvalidateRect( hwnd_, NULL, TRUE );
}