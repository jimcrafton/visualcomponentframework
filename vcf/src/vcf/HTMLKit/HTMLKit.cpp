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
_property_( String, "currentURL", getCurrentURL, setCurrentURL, "" );
_property_( bool, "allowPopups", getAllowsPopupWindows, setAllowsPopupWindows, "" );
_property_( bool, "allowScrollbars", getAllowsScrollbars, setAllowsScrollbars, "" );
_property_( bool, "allowTextSelection", getAllowsTextSelection, setAllowsTextSelection, "" );
_property_( bool, "allowContextMenu", getAllowDefaultContextMenu, setAllowDefaultContextMenu, "" );
_property_( bool, "updateModelOnDocumentCompleted", shouldUpdateModelOnDocumentCompleted, setUpdateModelOnDocumentCompleted, "" );
_property_( bool, "updateDOMOnDocumentCompleted", shouldUpdateDOMOnDocumentCompleted, setUpdateDOMOnDocumentCompleted, "" );

_property_dictionary_( String, VariantData, "elementKeys", getElementNameForKey, setElementNameForKey, "" )
_class_rtti_end_





		








void HTMLKit::init( int argc, char** argv )
{
	HTMLToolkit::create();

	REGISTER_CLASSINFO_EXTERNAL( HTMLBrowserControl );

	Component::registerComponent( "VCF::HTMLBrowserControl", ADDITIONAL_CATEGORY );
}


void HTMLKit::terminate()
{
	HTMLToolkit::destroy();
}


/**
$Id$
*/
