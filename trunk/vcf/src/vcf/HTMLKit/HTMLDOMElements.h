#ifndef _VCF_HTMLDOMELEMENTS_H__
#define _VCF_HTMLDOMELEMENTS_H__

//HTMLDOMElements.h

/*
Copyright 2000-2006 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

/**
\par
These classes provide a \em very thin wrapper around 
the browsers HTML DOM nodes, so you can do more advanced
manipulation of browsers document content. They do not
completely expose all the functionality, but they do 
expose most of the more commonly used functions.
\par
Currently, on Win32, these classes represent a thin layer
over the IHTMLElement, IHTMLDocument2, and 
IHTMLElementCollection COM interfaces exposed by the MSHTML 
and WebBrowser modules.
*/
namespace VCF {

class HTMLElement;
class HTMLDocument;

class HTMLElementCollectionPeer;
class HTMLElementPeer;
class HTMLDocumentPeer;

/**
\class HTMLElementCollection HTMLDOMElements.h "vcf/HTMLKit/HTMLDOMElements.h"
This is a collection of 0 or more HTMLElement nodes
*/
class HTMLKIT_API HTMLElementCollection {
public:

	friend class HTMLElement;
	friend class HTMLDocument;

	HTMLElementCollection();
	
	HTMLElementCollection( const HTMLElementCollection& rhs );

	~HTMLElementCollection();

	void setPeer( HTMLElementCollectionPeer* collection );

	HTMLElementCollectionPeer* getPeer() const{
		return peer_;
	}

	bool null() const;	

	HTMLElementCollection& operator= ( const HTMLElementCollection& rhs );	

	String toString() const ;

	void setLength( long len ) ;

	long getLength() const ;


	HTMLElement* item( const String& name, long index );

	HTMLElement* item( const String& name );
	HTMLElement* item( long index );

	HTMLElement* operator[](long index);
	HTMLElement* operator[](const String& name);


	HTMLElementCollection tags( const String& tag ) ;

private:
	HTMLElementCollectionPeer* peer_;
	HTMLElement* currentItem_;
};

/**
\class HTMLElement HTMLDOMElements.h "vcf/HTMLKit/HTMLDOMElements.h"
This represents an individual node. 
*/
class HTMLKIT_API HTMLElement {
public:	
	HTMLElement();

	HTMLElement( const HTMLElement& rhs );

	HTMLElement( HTMLElementPeer* element );

	~HTMLElement();

	HTMLElement& operator= ( const HTMLElement& rhs );

	void setPeer( HTMLElementPeer* element );

	HTMLElementPeer* getPeer() const{
		return peer_;
	}

	bool null() const ;

	void setAttribute( const String& attributeName,
						const String& attributeValue,
						bool caseSensitive );

	String getAttribute(const String& attributeName, bool caseSensitive=true) const ;

	bool removeAttribute( const String& attributeName, bool caseSensitive=true ) ;

	void setClassName( const String& className );

	String getClassName() const ;

	void setID( const String& id );

	String getID() const;

	String getTagName() const ;

	HTMLElement getParent() const ;

	void setTitle( const String& title ) ;

	String getTitle() const;

	void setLanguage( const String& language ) ;

	String getLanguage() const ;

	void scrollIntoView( bool atTop ) ;

	bool contains( const HTMLElement& child ) const ;

	long getSourceIndex() const ;

	void setLang( const String& language );

	String getLang() const ;
	
	long getOffsetLeft() const ;

	long getOffsetTop() const ;

	long getOffsetWidth() const ;

	long getOffsetHeight() const ;

	HTMLElement getOffsetParent() const ;

	void setInnerHTML( const String& html ) ;

	String getInnerHTML() const ;

	void setInnerText( const String& text ) ;

	String getInnerText() const ;

	void setOuterHTML( const String& html ) ;

	String getOuterHTML() const ;

	void setOuterText( const String& text ) ;

	String getOuterText() const ;


	void insertAdjacentHTML( const String& where, const String& html ) ;

	void insertAdjacentText( const String& where, const String& text ) ;

	HTMLElement getParentTextEdit() const ;

	bool getIsTextEdit() const ;

	void click() ;

	String toString() const ;

	HTMLElementCollection getChildren() ;

	HTMLElementCollection getAll() ;	
	 
private:
	HTMLElementPeer* peer_;
	/*	
            
get_style    put_onhelp    get_onhelp    
put_onclick    get_onclick    put_ondblclick    
get_ondblclick    put_onkeydown    get_onkeydown    
put_onkeyup    get_onkeyup    put_onkeypress    
get_onkeypress    put_onmouseout    get_onmouseout    
put_onmouseover    get_onmouseover    put_onmousemove    
get_onmousemove    put_onmousedown    get_onmousedown    
put_onmouseup    get_onmouseup    get_document    
            
    put_onselectstart    get_onselectstart    
           
get_recordNumber

get_filters    put_ondragstart    get_ondragstart    
toString    put_onbeforeupdate    get_onbeforeupdate    
put_onafterupdate    get_onafterupdate    put_onerrorupdate    
get_onerrorupdate    put_onrowexit    get_onrowexit    
put_onrowenter    get_onrowenter    put_ondatasetchanged    
get_ondatasetchanged    put_ondataavailable    get_ondataavailable    
put_ondatasetcomplete    get_ondatasetcomplete    put_onfilterchange    
get_onfilterchange           

	*/
};





/**
\class HTMLDocument HTMLDOMElements.h "vcf/HTMLKit/HTMLDOMElements.h"
*/
class HTMLKIT_API HTMLDocument {
public:

	HTMLDocument();	

	HTMLDocument( const HTMLDocument& rhs );

	~HTMLDocument();	

	HTMLDocument& operator= ( const HTMLDocument& rhs );

	void setPeer( HTMLDocumentPeer* doc );

	HTMLDocumentPeer* getPeer() const{
		return peer_;
	}

	bool null() const;

	HTMLElementCollection getAll();

	HTMLElement getBody() const ;

	HTMLElement getActiveElement() const ;


	HTMLElementCollection getImages() ;

	HTMLElementCollection getApplets() ;

	HTMLElementCollection getLinks() ;

	HTMLElementCollection getForms() ;

	HTMLElementCollection getAnchors() ;
	
	void setTitle( const String& title ) ;

	String getTitle() const ;

	HTMLElementCollection getScripts() ;


	String getReadyState() const ;

	HTMLElementCollection getEmbeds() ;

	HTMLElementCollection getPlugins() ;

	String getReferrer() const ;
	
	String getLastModified() const ;
	
	void setURL( const String& url ) ;

	String getURL() const ;

	void setDomain( const String& domain ) ;

	String getDomain() const ;

	void setCookie( const String& cookie ) ;

	String getCookie() const ;

	bool getExpando() const ;

	void setExpando( bool expando ) ;

	void setCharset( const String& val ) ;

	String getCharset() const ;

	void setDefaultCharset( const String& val ) ;

	String getDefaultCharset() const ;

	String getMimeType() const ;

	String getFileSize() const ;

	int getIntFileSize() const ;

	String getFileCreatedDate() const ;

	String getFileModifiedDate() const ;

	String getFileUpdatedDate() const ;

	String getSecurity() const ;

	String getProtocol() const ;

	String getNameProp() const ;

	String toString() const ;
	   
	void write( const String& text ) ;

	void writeln( const String& text ) ;

	HTMLElement createElement( const String& elementTag ) const ;

	/**
	Returns the element at the point x, y. The x/y corrdinates
	are in client local coordinate space.
	@return HTMLElement the element found. If no element was found
	the HTMLElement's null() method will return true.
	*/
	HTMLElement elementFromPoint( long x, long y );

	void setDesignMode( bool val ) ;

	bool getDesignMode() const ;
	
	void copy() ;

	void cut() ;

	void paste() ;

	void selectAll() ;

	void underline() ;

	void bold() ;

	void italic () ;

	void justifyLeft () ;

	void justifyRight () ;

	void justifyCenter () ;

	void justifyFull () ;

	void outdent () ;

	void indent () ;

	void clearSelection () ;
	
	 
/*get_selection    
    get_frames      
    put_alinkColor    get_alinkColor  
put_bgColor    get_bgColor    put_fgColor    
get_fgColor  put_linkColor    get_linkColor    
put_vlinkColor    get_vlinkColor      
get_location          
            
                 
open    close    clear    
queryCommandSupported    queryCommandEnabled    queryCommandState    
queryCommandIndeterm    queryCommandText    queryCommandValue    
execCommand    execCommandShowHelp
*/

private:
	HTMLDocumentPeer* peer_;
};



};



#endif //_VCF_HTMLDOMELEMENTS_H__