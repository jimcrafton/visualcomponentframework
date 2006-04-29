//Win32ComboBox.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;


Win32ComboBox::Win32ComboBox( ComboBoxControl* component ):
	AbstractWin32Component( component )
{
	this->createParams();

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className = this->getClassName();

	this->hwnd_ = ::CreateWindowEx( this->exStyleMask_,
		                             "COMBOBOX",
									 this->windowCaption_.c_str(),
									 this->styleMask_,
		                             this->bounds_.left_,
									 this->bounds_.top_,
									 this->bounds_.getWidth(),
									 this->bounds_.getHeight(),
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );


	if ( NULL != this->hwnd_ ){
		Win32Object::registerWin32Object( this );
		oldComboBoxWndProc_ = (WNDPROC)::SetWindowLong( this->hwnd_, GWL_WNDPROC, (LONG)wndProc_ );
		this->defaultWndProc_ = NULL;

	}
	else {
		//throw exception
	}

	this->setCreated( true );
}

Win32ComboBox::~Win32ComboBox()
{

}

void Win32ComboBox::createParams()
{
	this->styleMask_ = SIMPLE_VIEW | CBS_DROPDOWN | WS_VSCROLL | CBS_AUTOHSCROLL | CBS_HASSTRINGS;
}

void Win32ComboBox::addItem( ListItem * item )
{
	String caption = item->getCaption();
	VCFChar* tmp = new VCFChar[caption.size()];
	memset( tmp, 0, caption.size()*sizeof(VCFChar) );
	caption.copy( tmp, caption.size() );
	int index = ::SendMessage( this->hwnd_, CB_ADDSTRING, 0, (LPARAM)caption.c_str() );
	item->setIndex( index );
	delete [] tmp;
}

void Win32ComboBox::insertItem( const unsigned long& index, ListItem * item )
{

}

LRESULT Win32ComboBox::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, WNDPROC defaultWndProc )
{
	LRESULT result = 0;

	switch ( message ) {
		case WM_PAINT:{
			result = CallWindowProc( oldComboBoxWndProc_, hwnd_, message, wParam, lParam );
		}
		break;

		case WM_COMMAND: {
			AbstractWin32Component::handleEventMessages( message, wParam, lParam );
			result = CallWindowProc( oldComboBoxWndProc_, hwnd_, message, wParam, lParam );
		}
		break;
		default: {
			AbstractWin32Component::handleEventMessages( message, wParam, lParam );
			result = CallWindowProc( oldComboBoxWndProc_, hwnd_, message, wParam, lParam );
		}
	}
	return result;
}

void Win32ComboBox::setBounds( VCF::Rect* rect )
{
	double h = rect->getHeight() * 4;
	::SetWindowPos( this->hwnd_, NULL, rect->left_, rect->top_,
                    rect->getWidth(), h, SWP_NOACTIVATE );
}


/**
$Id$
*/
