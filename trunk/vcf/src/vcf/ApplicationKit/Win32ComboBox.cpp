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
	char* tmp = new char[caption.size()];
	memset( tmp, 0, caption.size() );
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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.7  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/12 03:12:22  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


