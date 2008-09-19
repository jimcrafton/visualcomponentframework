#ifndef _VCF_HTMLBROWSERCONTROL_H__
#define _VCF_HTMLBROWSERCONTROL_H__
//HTMLBrowserControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#ifndef _VCF_HTMLDOMELEMENTS_H__
#include "vcf/ApplicationKit/HTMLDOMElements.h"
#endif

#include "vcf/FoundationKit/Dictionary.h"



#if _MSC_VER > 1000
#   pragma once
#endif


#define HTMLBROWSERCONTROL_CLASSID		"3bfb2646-a7e9-40b2-948b-9eef92db7965"


namespace VCF  {
	/**
	This is event is used when an authentication event is 
	fired by the underlying browser peer. This happens if a 
	URL is being opened and it needs a username and password.
	The handler for this event should set the username and 
	password to some meaningful value.
	*/
	class HTMLAuthenticationEvent : public Event {
	public:
		inline HTMLAuthenticationEvent( Object* source, const String& url );


		String userName;
		String password;
		String url;
		bool authenticationCancelled;

		virtual Object* clone( bool deep=false ) {
			return new HTMLAuthenticationEvent(*this);
		}		
	};

	typedef Delegate1<HTMLAuthenticationEvent*> HTMLAuthenticationDelegate;


	/**
	Generic HTML event sent for all other events generated by the HTML Browser.
	*/
	class HTMLKIT_API HTMLEvent : public Event {
	public:
		HTMLEvent( Object* source, uint32 type ):Event(source,type), value(0),maxValue(0) {};

		virtual Object* clone( bool deep=false ) {
			return new HTMLEvent(*this);
		}
	
		/**
		The value of the event. Generally gets set during progress events.
		@see HTMLBrowserControl::StatusChanged
		@see HTMLBrowserControl::URLLoading
		*/
		uint32 value;

		/**
		The maximum value of the event. Generally gets set during progress events.
		@see HTMLBrowserControl::StatusChanged
		@see HTMLBrowserControl::URLLoading
		*/
		uint32 maxValue;

		/**
		The status of the event. 
		@see HTMLBrowserControl::StatusChanged
		*/
		String status;

		/**
		The URL the event is associated with. 
		*/
		String url;

	};


	typedef Delegate1<HTMLEvent*> HTMLDelegate; 

	class HTMLKIT_API HTMLNewWindowEvent : public Event {
	public:
		HTMLNewWindowEvent( Object* source, uint32 type ):Event(source,type), allowNewWindow(true) {};

		virtual Object* clone( bool deep=false ) {
			return new HTMLNewWindowEvent(*this);
		}
	
		
		bool allowNewWindow;
	};

	typedef Delegate1<HTMLNewWindowEvent*> HTMLNewWindowDelegate; 


	/**
	An event thats used for HTMLElement events. 
	*/
	class HTMLKIT_API HTMLElementEvent : public Event {
	public:
		HTMLElementEvent( Object* source, uint32 type ):Event(source,type) {};

		virtual Object* clone( bool deep=false ) {
			return new HTMLElementEvent(*this);
		}

		/**
		The id of the element that triggered the event.
		*/
		String elementID;
	};

	typedef Delegate1<HTMLElementEvent*> HTMLElementDelegate; 


	typedef std::pair<VariantData,String> KeyedHTMLElement;

/**
\class HTMLBrowserControl HTMLBrowserControl.h "vcf/HTMLKit/HTMLBrowserControl.h"
The HTMLBrowserControl provides a wrapper around the native HTML rendering 
and UI presentation for the platform. This class provides  all the basic 
features to implement a simple HTML browsing application. For 
more advanced uses, you can take advantage of it's other features
and use the HTMLElement, HTMLDocument, and HTMLElementCollection
classes.
\par
On Win32 this means a custom COM based wrapper around Internet Explorer's 
IWebBrowser2 interface. 
\par 
The HTMLBrowserControl allows a number of customizations of the UI presented
when the HTML is rendered. You can control features such as 
	\li whether or not scrollbars are shown, 
	\li whether or not to allow popup windows, 
	\li whether or not to allow the user to select text in the UI
	\li whether to use the default authentication dialog when 
	prompted for a user name and password
	\li whether or not the default context menu should be used
\par
There are also a number of events that you can respond to, such as 
	\li when a url starts to load
	\li events fired while the url is in the process of loading
	\li when the url loading is complete
	\li a url loading error
	\li when the status changes, allowing you to output the status text
	\li when a new window is about to be displayed
	\li when the title changes
	\li when authentication is being requested
	\li when an HTML element is clicked on with the mouse

\par
In addition, you can access the HTML document, which allows you to 
traverse to any element within the document.
@see HTMLElement
@see HTMLDocument
@see HTMLElementCollection
*/
class HTMLKIT_API HTMLBrowserControl : public Control {
public:
	HTMLBrowserControl();
	virtual ~HTMLBrowserControl();
	
	/**
	A series of enums that allows you control the behaviour or 
	appearance of the browser control.
	*/
	enum HTMLPolicy {
		hpNone = 0,
		/**
		Allows popup windows to be show if this is set, otherwise if 
		the page contents or script request a new window, it will be 
		denied.
		*/
		hpAllowPopups =			0x0001,

		/**
		Determines whether or not scrollbars are made visible. If it's 
		set, then they are allwos to become visible. If it's not
		then no scrollbars will ever appear.
		*/
		hpAllowsScrollbars =	0x0002,

		/**
		Determines if the browser will allow the user to select text.
		*/
		hpAllowsTextSelection = 0x0004,

		/**
		Determines if the browser should use the platform native authentication
		dialog when a request for user name and password is made. If this
		isn't set then you can customize the interface.
		*/
		hpUseDefaultAuthenticationUI  = 0x0008,

		/**
		Determines whether or not the browser should use it's default popup menu
		or allow it to be customized. If it's customized, then it uses the 
		popup menu of the control if it exists.
		*/
		hpAllowDefaultContextMenu  = 0x0010,

		hpUpdateModelOnDocumentCompleted = 0x0020,

		hpUpdateDOMOnDocumentCompleted = 0x0040,

	};

	enum HTMLEvents{
		heBase = 'HTev',
		heURLLoadingBegun,
		heURLLoading,
		heURLLoaded,
		heURLLoadError,
		heStatusChanged,
		heNewWindowDisplayed,
		heTitleChanged,
		heAuthenticationRequested,
		heElementClicked
	};

	/**
	@delegate URLLoadingBegun
	@event HTMLEvent
	@eventtype heURLLoadingBegun
	*/
	DELEGATE( HTMLDelegate,URLLoadingBegun );

	/**
	@delegate URLLoading
	@event HTMLEvent
	@eventtype heURLLoading
	*/
	DELEGATE( HTMLDelegate,URLLoading );

	/**
	@delegate URLLoaded
	@event HTMLEvent
	@eventtype heURLLoaded
	*/
	DELEGATE( HTMLDelegate,URLLoaded );

	/**
	@delegate URLLoadError
	@event HTMLEvent
	@eventtype heURLLoadError
	*/
	DELEGATE( HTMLDelegate,URLLoadError );


	/**
	@delegate StatusChanged
	@event HTMLEvent
	@eventtype heStatusChanged
	*/
	DELEGATE( HTMLDelegate,StatusChanged );

	/**
	@delegate NewWindowDisplayed
	@event HTMLEvent
	@eventtype heNewWindowDisplayed
	*/
	DELEGATE( HTMLNewWindowDelegate,NewWindowDisplayed );

	/**
	@delegate TitleChanged
	@event HTMLEvent
	@eventtype heTitleChanged
	*/
	DELEGATE( HTMLDelegate,TitleChanged );
	
	/**
	@delegate AuthenticationRequested
	@event HTMLAuthenticationEvent
	@eventtype heAuthenticationRequested
	*/
	DELEGATE( HTMLAuthenticationDelegate,AuthenticationRequested );


	virtual void paint( GraphicsContext* ctx );

	virtual void modelChanged( Model* oldModel, Model* newModel );

	/**
	Gets the current url of the HTML that the control
	is showing
	*/
	String getCurrentURL();

	/**
	Sets the current URL. This will start the process of loading the URL.
	It's not safe to access the control's HTMLDocument until the
	URLLoaded event is fired.
	*/
	void setCurrentURL( const String& url );

	/**
	Go back to the previously loaded URL
	*/
	void goBack();

	/** 
	Go forward to the next loaded URL
	*/
	void goForward();

	/**
	Go to the "home" page/URL as specified by the platforms internet settings.
	*/
	void goHome();

	/**
	Refresh the current URL. This will cause it to be re-loaded.
	*/
	void refresh();

	/**
	Returns true if the control is currently busy loading a URL.
	*/
	bool isLoadingURL();

	/**
	Programmatically stop the URL from loading.
	*/
	void stopLoadingURL();


	void setFromHTML( const String& html );

	/**
	Get the title for the HTML
	*/
	String getTitle();

	/**
	Toggles the edit mode of the HTML Document. If you pass in true
	the HTML displayed will become editable, if you pass in false it
	will become readonly.
	*/
	void edit( const bool& val );

	/**
	Take the user's current selection and copy it to the clipboard
	*/
	void copy();

	/**
	Select everything in the document
	*/
	void selectAll();

	/**
	Return whether or not popup windows are allowed. 
	*/
	bool getAllowsPopupWindows() {
		return (policyState_ & hpAllowPopups) ? true : false;
	}

	void setAllowsPopupWindows( const bool& val );

	bool getAllowsScrollbars() {
		return (policyState_ & hpAllowsScrollbars) ? true : false;
	}

	void setAllowsScrollbars( const bool& val );

	bool getAllowsTextSelection() {
		return (policyState_ & hpAllowsTextSelection) ? true : false;
	}	

	void setAllowsTextSelection( const bool& val );

	bool getUseDefaultAuthenticationUI() {
		return (policyState_ & hpUseDefaultAuthenticationUI) ? true : false;
	}

	void setUseDefaultAuthenticationUI( const bool& val ) {
		if ( val ) {
			policyState_ |= hpUseDefaultAuthenticationUI;
		}
		else {
			policyState_ &= ~hpUseDefaultAuthenticationUI;
		}		
	}

	bool getAllowDefaultContextMenu() {
		return (policyState_ & hpAllowDefaultContextMenu) ? true : false;
	}

	void setAllowDefaultContextMenu( const bool& val ) {
		if ( val ) {
			policyState_ |= hpAllowDefaultContextMenu;
		}
		else {
			policyState_ &= ~hpAllowDefaultContextMenu;
		}		
	}

	bool shouldUpdateModelOnDocumentCompleted() {		
		return (policyState_ & hpUpdateModelOnDocumentCompleted) ? true : false;
	}

	void setUpdateModelOnDocumentCompleted( const bool& val ) {
		if ( val ) {
			policyState_ |= hpUpdateModelOnDocumentCompleted;
			if ( policyState_ & hpUpdateDOMOnDocumentCompleted ) {
				policyState_ &= ~hpUpdateDOMOnDocumentCompleted;
			}
		}
		else {
			policyState_ &= ~hpUpdateModelOnDocumentCompleted;
		}
	}

	bool shouldUpdateDOMOnDocumentCompleted() {		
		return (policyState_ & hpUpdateDOMOnDocumentCompleted) ? true : false;
	}

	void setUpdateDOMOnDocumentCompleted( const bool& val ) {
		if ( val ) {
			policyState_ |= hpUpdateDOMOnDocumentCompleted;
			if ( policyState_ & hpUpdateModelOnDocumentCompleted ) {
				policyState_ &= ~hpUpdateModelOnDocumentCompleted;
			}
		}
		else {
			policyState_ &= ~hpUpdateDOMOnDocumentCompleted;
		}
	}


	String getActiveElementID();

	String getElementIDFromPoint( Point* pt );

	String getElementHTMLText( const String& elementName );

	void setElementHTMLText( const String& elementName, const String& html );

	String getElementText( const String& elementName );

	void setElementText( const String& elementName, const String& text );	
	
	/**
	Sets one of the more common event handlers for an element. Some elements
	may not respond to this.
	This will fire a HTMLElementEvent instance.
	*/
	bool setElementClickedEventHandler( const String& elementName, EventHandler* handler );


	HTMLDocument getDocument();

	void setElementNameForKey( const VariantData& key, const String& elementName );
	String getElementNameForKey( const VariantData& key );

	void setKeyForElement( HTMLElement& element, const String& elementName, const VariantData& key );

	bool getKeyedElements( std::vector<KeyedHTMLElement>& keyedElements );

	void updateModelFromDOM();
	void updateDOMFromModel();

protected:
	enum {
		ModelChanged = 0x01,
		InternalDOMDocumentChanged = 0x02
	};


	HTMLBrowserPeer* browserPeer_;
	uint32 policyState_;
	std::map<VariantData,String> elementKeys_;
	uint32 modelChangeState_;

	void onModelChanged( ModelEvent* e );

	void inputElementChanged( Event* e );

private:
};



HTMLAuthenticationEvent::HTMLAuthenticationEvent( Object* source, const String& aUrl ):
	Event( source, HTMLBrowserControl::heAuthenticationRequested),
	url(aUrl),
	authenticationCancelled(false)
{

}


}; //end of namespace VCF


#endif // _VCF_HTMLBROWSERCONTROL_H__

/**
$Id$
*/
