//HTMLKit.cpp

#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/HTMLBrowserControl.h"


#include "vcf/FoundationKit/RTTIMacros.h"


using namespace VCF;


_class_rtti_(HTMLBrowserControl, "VCF::Control", HTMLBROWSERCONTROL_CLASSID)
_delegate_(HTMLDelegate, URLLoadingBegun );
_delegate_(HTMLDelegate, URLLoading );
_delegate_(HTMLDelegate, URLLoaded );
_delegate_(HTMLDelegate, URLLoadError );
_delegate_(HTMLDelegate, StatusChanged );
_delegate_(HTMLNewWindowDelegate, NewWindowDisplayed );
_delegate_(HTMLDelegate, TitleChanged );
_delegate_(HTMLAuthenticationDelegate, AuthenticationRequested );
_delegate_( HTMLShowMessageDelegate, ShowMessageRequested );
_delegate_( HTMLTranslateURLDelegate, TranslateURLRequested );

_property_( String, "currentURL", getCurrentURL, setCurrentURL, "" );
_property_( bool, "allowPopups", getAllowsPopupWindows, setAllowsPopupWindows, "" );
_property_( bool, "allowScrollbars", getAllowsScrollbars, setAllowsScrollbars, "" );
_property_( bool, "allowTextSelection", getAllowsTextSelection, setAllowsTextSelection, "" );
_property_( bool, "allowContextMenu", getAllowDefaultContextMenu, setAllowDefaultContextMenu, "" );
_property_( bool, "updateModelOnDocumentCompleted", shouldUpdateModelOnDocumentCompleted, setUpdateModelOnDocumentCompleted, "" );
_property_( bool, "updateDOMOnDocumentCompleted", shouldUpdateDOMOnDocumentCompleted, setUpdateDOMOnDocumentCompleted, "" );
_property_( bool, "notifyForURLTranslation", shouldNotifyForURLTranslation, setNotifyForURLTranslation, "" );

_property_dictionary_( VariantData, String, "elementKeys", getKeyForElementName, setKeyForElementName, "" )
_class_rtti_end_


_class_rtti_(DOMDocumentComponent, "VCF::Component", "DOMDocumentComponent")
_class_rtti_end_


_class_rtti_(DOMElementComponent, "VCF::Component", "DOMElementComponent")
	_delegate_(HTMLElementDelegate, Click);
	_delegate_(HTMLElementDelegate, DblClick);
	_delegate_(HTMLElementDelegate, DragStart);
	_delegate_(HTMLElementDelegate, DragEnd);
	_delegate_(HTMLElementDelegate, KeyDown);
	_delegate_(HTMLElementDelegate, KeyPress);
	_delegate_(HTMLElementDelegate, KeyUp);
	_delegate_(HTMLElementDelegate, MouseDown);
	_delegate_(HTMLElementDelegate, MouseMove);
	_delegate_(HTMLElementDelegate, MouseOver);
	_delegate_(HTMLElementDelegate, MouseOut);
	_delegate_(HTMLElementDelegate, MouseUp);
_class_rtti_end_








void HTMLKit::init( int argc, char** argv )
{
	HTMLToolkit::create();

	REGISTER_CLASSINFO_EXTERNAL( HTMLBrowserControl );
	REGISTER_CLASSINFO_EXTERNAL( DOMElementComponent );
	REGISTER_CLASSINFO_EXTERNAL( DOMDocumentComponent );

	Component::registerComponent( "VCF::HTMLBrowserControl", ADDITIONAL_CATEGORY );
}


void HTMLKit::terminate()
{
	HTMLToolkit::destroy();
}


/**
$Id$
*/
