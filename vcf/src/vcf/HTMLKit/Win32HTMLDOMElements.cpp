//Win32HTMLDOMElements.cpp

#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/HTMLKit/HTMLBrowserControl.h"
#include "vcf/HTMLKit/Win32HTMLDOMElements.h"



VCF::HTMLElementCollection::HTMLElementCollection():
	currentItem_(NULL),peer_(NULL)
{
	peer_ = new HTMLElementCollectionPeer();
}

VCF::HTMLElementCollection::HTMLElementCollection( const VCF::HTMLElementCollection& rhs ):
	currentItem_(NULL),peer_(NULL) 
{
	peer_ = new VCF::HTMLElementCollectionPeer();
	*peer_ = *rhs.peer_;
}

VCF::HTMLElementCollection::~HTMLElementCollection()
{
	delete currentItem_;
	delete peer_;
}


bool VCF::HTMLElementCollection::null() const 
{
	return peer_->is_null();
}

VCF::HTMLElementCollection& VCF::HTMLElementCollection::operator= ( const VCF::HTMLElementCollection& rhs ) 
{
	*peer_ = *rhs.peer_;
	return *this;
}

void VCF::HTMLElementCollection::setPeer( VCF::HTMLElementCollectionPeer* collection )
{
	*peer_ = *collection;
}

VCF::String VCF::HTMLElementCollection::toString() const 
{
	bstr_t res;
	
	if ( *peer_ ) {
		(*peer_)->toString( res.out() );
	}
	
	return res.c_str();
}

void VCF::HTMLElementCollection::setLength( long len ) {
	if ( *peer_ ) {
		(*peer_)->put_length( (long)len );
	}
}

long VCF::HTMLElementCollection::getLength() const {
	long result = 0;
	if ( *peer_ ) {
		(*peer_)->get_length( &result );
	}
	return result;
}


VCF::HTMLElement* VCF::HTMLElementCollection::item( const VCF::String& name, long index )
{
	VCF::HTMLElement* result = NULL;
	
	variant_t tmpName = index;
	variant_t tmpIndex = index;
	
	com_ptr<IDispatch> disp;
	(*peer_)->item( tmpName.in(), tmpIndex.in(), disp.out() );
	if ( NULL != disp ) {
		VCF::HTMLElementPeer item = com_cast( disp );
		if ( item ) {
			if ( NULL == currentItem_ ) {
				currentItem_ = new VCF::HTMLElement();
			}
			
			currentItem_->setPeer( &item );
			result = currentItem_;
		}
	}

	return result;
}


VCF::HTMLElement* VCF::HTMLElementCollection::item( const VCF::String& name )
{
	VCF::HTMLElement* result = NULL;
	variant_t tmpName = name.c_str();
	variant_t tmpIndex = name.c_str();
	
	com_ptr<IDispatch> disp;
	(*peer_)->item( tmpName.in(), tmpIndex.in(), disp.out() );
	if ( NULL != disp ) {
		VCF::HTMLElementPeer item = com_cast( disp );
		if ( item ) {
			if ( NULL == currentItem_ ) {
				currentItem_ = new VCF::HTMLElement();
			}
			
			currentItem_->setPeer( &item );
			result = currentItem_;
		}
	}

	return result;
}

VCF::HTMLElement* VCF::HTMLElementCollection::item( long index )
{
	VCF::HTMLElement* result = NULL;

	variant_t tmpName = index;
	variant_t tmpIndex = index;
	
	com_ptr<IDispatch> disp;
	(*peer_)->item( tmpName.in(), tmpIndex.in(), disp.out() );
	if ( NULL != disp ) {
		VCF::HTMLElementPeer item = com_cast( disp );
		if ( item ) {
			if ( NULL == currentItem_ ) {
				currentItem_ = new VCF::HTMLElement();
			}
			
			currentItem_->setPeer( &item );
			result = currentItem_;
		}
	}

	return result;
}


VCF::HTMLElement* VCF::HTMLElementCollection::operator[](long index)
{
	return item(index);
}

VCF::HTMLElement* VCF::HTMLElementCollection::operator[](const VCF::String& name)
{
	return item(name);
}


VCF::HTMLElementCollection VCF::HTMLElementCollection::tags( const VCF::String& tag ) {
	VCF::HTMLElementCollection result;
	
	
	variant_t tmpTag = tag.c_str();
	
	com_ptr<IDispatch> collection;
	
	(*peer_)->tags( tmpTag.in(), collection.out() );
	
	if (collection) {
		*(result.peer_) = com_cast(collection);
	}
	
	return result;
}









VCF::HTMLElement::HTMLElement():
	peer_(NULL)
{
	peer_ = new VCF::HTMLElementPeer();
}

VCF::HTMLElement::HTMLElement( const VCF::HTMLElement& rhs ):
	peer_(NULL)
{
	peer_ = new VCF::HTMLElementPeer();
	*peer_ = *rhs.peer_;
}


VCF::HTMLElement::HTMLElement( VCF::HTMLElementPeer* element ):
	peer_(NULL)
{
	peer_ = new VCF::HTMLElementPeer();
	*peer_ = *element;
}

VCF::HTMLElement::~HTMLElement()
{
	delete peer_;
}

VCF::HTMLElement& VCF::HTMLElement::operator= ( const VCF::HTMLElement& rhs ) 
{
	*peer_ = *rhs.peer_;
	return *this;
}

void VCF::HTMLElement::setPeer( VCF::HTMLElementPeer* element )
{
	*peer_ = *element;
}

bool VCF::HTMLElement::null() const 
{
	return peer_->is_null();
}

void VCF::HTMLElement::setAttribute( const VCF::String& attributeName,
				  const VCF::String& attributeValue,
				  bool caseSensitive ) 
{
	
	bstr_t name = attributeName.c_str();
	variant_t val = attributeValue.c_str();
	(*peer_)->setAttribute( name.in(), val.in(), caseSensitive ? TRUE:FALSE );
}

VCF::String VCF::HTMLElement::getAttribute(const VCF::String& attributeName, bool caseSensitive) const 
{
	VCF::String result;
	
	variant_t tmp;
	bstr_t name = attributeName.c_str();
	
	(*peer_)->getAttribute(name.in(), caseSensitive ? TRUE:FALSE, tmp.out() );
	
	result = (AnsiString)tmp;
	
	return result;
}

bool VCF::HTMLElement::removeAttribute( const VCF::String& attributeName, bool caseSensitive ) 
{
	VARIANT_BOOL result = FALSE;
	bstr_t name = attributeName.c_str();
	(*peer_)->removeAttribute( name.in(), caseSensitive ? TRUE:FALSE, &result );
	return result ? true : false;
}

void VCF::HTMLElement::setClassName( const VCF::String& className ) 
{
	
	(*peer_)->put_className( bstr_t(className.c_str()).in() );
}

VCF::String VCF::HTMLElement::getClassName() const 
{
	bstr_t tmp;
	(*peer_)->get_className( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLElement::setID( const VCF::String& id ) 
{
	
	(*peer_)->put_id( bstr_t(id.c_str()).in() );
}

VCF::String VCF::HTMLElement::getID() const 
{
	bstr_t tmp;
	(*peer_)->get_id( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLElement::getTagName() const 
{
	bstr_t tmp;
	(*peer_)->get_tagName( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::HTMLElement VCF::HTMLElement::getParent() const 
{
	VCF::HTMLElement result;
	VCF::HTMLElementPeer parent;
	(*peer_)->get_parentElement( parent.out() );
	
	result.setPeer( &parent );

	return result;
}

void VCF::HTMLElement::setTitle( const VCF::String& title ) 
{
	(*peer_)->put_title( bstr_t(title.c_str()).in() );		
}

VCF::String VCF::HTMLElement::getTitle() const 
{
	bstr_t tmp;
	(*peer_)->get_title( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLElement::setLanguage( const VCF::String& language ) 
{
	(*peer_)->put_language( bstr_t(language.c_str()).in() );		
}

VCF::String VCF::HTMLElement::getLanguage() const 
{
	bstr_t tmp;
	(*peer_)->get_language( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLElement::scrollIntoView( bool atTop ) 
{
	(*peer_)->scrollIntoView( variant_t(atTop).in() );
}

bool VCF::HTMLElement::contains( const HTMLElement& child ) const 
{
	VARIANT_BOOL result = FALSE;
	
	(*peer_)->contains( child.peer_->in(), &result );
	
	return result ? true : false;
}

long VCF::HTMLElement::getSourceIndex() const 
{
	long result = 0;
	
	(*peer_)->get_sourceIndex( &result );
	
	return result;
}

void VCF::HTMLElement::setLang( const VCF::String& language ) 
{
	(*peer_)->put_lang( bstr_t(language.c_str()).in() );		
}

VCF::String VCF::HTMLElement::getLang() const 
{
	bstr_t tmp;
	(*peer_)->get_lang( tmp.out() );
	return VCF::String(tmp.c_str());
}

long VCF::HTMLElement::getOffsetLeft() const 
{
	long result = 0;
	
	(*peer_)->get_offsetLeft( &result );
	
	return result;
}

long VCF::HTMLElement::getOffsetTop() const 
{
	long result = 0;
	
	(*peer_)->get_offsetTop( &result );
	
	return result;
}

long VCF::HTMLElement::getOffsetWidth() const 
{
	long result = 0;
	
	(*peer_)->get_offsetWidth( &result );
	
	return result;
}

long VCF::HTMLElement::getOffsetHeight() const 
{
	long result = 0;
	
	(*peer_)->get_offsetHeight( &result );
	
	return result;
}

VCF::HTMLElement VCF::HTMLElement::getOffsetParent() const 
{
	VCF::HTMLElement result;
	VCF::HTMLElementPeer parent;
	(*peer_)->get_offsetParent( parent.out() );
	
	result.setPeer( &parent );

	return result;
}

void VCF::HTMLElement::setInnerHTML( const VCF::String& html ) 
{
	(*peer_)->put_innerHTML( bstr_t(html.c_str()).in() );		
}

VCF::String VCF::HTMLElement::getInnerHTML() const 
{
	bstr_t tmp;
	(*peer_)->get_innerHTML( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLElement::setInnerText( const VCF::String& text ) 
{
	(*peer_)->put_innerText( bstr_t(text.c_str()).in() );		
}

VCF::String VCF::HTMLElement::getInnerText() const 
{
	bstr_t tmp;
	(*peer_)->get_innerText( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLElement::setOuterHTML( const VCF::String& html ) 
{
	(*peer_)->put_outerHTML( bstr_t(html.c_str()).in() );		
}

VCF::String VCF::HTMLElement::getOuterHTML() const 
{
	bstr_t tmp;
	(*peer_)->get_outerHTML( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLElement::setOuterText( const VCF::String& text ) 
{
	(*peer_)->put_outerText( bstr_t(text.c_str()).in() );		
}

VCF::String VCF::HTMLElement::getOuterText() const {
	bstr_t tmp;
	(*peer_)->get_outerText( tmp.out() );
	return VCF::String(tmp.c_str());
}


void VCF::HTMLElement::insertAdjacentHTML( const VCF::String& where, const VCF::String& html ) 
{
	(*peer_)->insertAdjacentHTML( bstr_t(where.c_str()).in(), bstr_t(html.c_str()).in() );		
}

void VCF::HTMLElement::insertAdjacentText( const VCF::String& where, const VCF::String& text ) 
{
	(*peer_)->insertAdjacentText( bstr_t(where.c_str()).in(), bstr_t(text.c_str()).in() );		
}

VCF::HTMLElement VCF::HTMLElement::getParentTextEdit() const 
{
	VCF::HTMLElement result;

	VCF::HTMLElementPeer parent;
	(*peer_)->get_parentTextEdit( parent.out() );
	
	result.setPeer( &parent );

	return result;
}

bool VCF::HTMLElement::getIsTextEdit() const 
{
	VARIANT_BOOL result = FALSE;
	(*peer_)->get_isTextEdit( &result );
	return result ? true : false;
}

void VCF::HTMLElement::click() {
	(*peer_)->click();
}

VCF::String VCF::HTMLElement::toString() const 
{
	bstr_t tmp;
	(*peer_)->toString( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::HTMLElementCollection VCF::HTMLElement::getChildren() 
{
	VCF::HTMLElementCollection result;
	com_ptr<IDispatch> collection;
	(*peer_)->get_children( collection.out() );
	if (collection) {
		*result.peer_ = com_cast(collection);
	}
	
	return result;
}

VCF::HTMLElementCollection VCF::HTMLElement::getAll() 
{
	VCF::HTMLElementCollection result;
	com_ptr<IDispatch> collection;
	(*peer_)->get_all( collection.out() );
	if (collection) {
		*result.peer_ = com_cast(collection);
	}
	
	return result;
}












VCF::HTMLDocument::HTMLDocument()
{
	peer_ = new VCF::HTMLDocumentPeer();
}

VCF::HTMLDocument::HTMLDocument( const VCF::HTMLDocument& rhs )
{
	peer_ = new VCF::HTMLDocumentPeer();
	*peer_ = *rhs.peer_;
}

VCF::HTMLDocument::~HTMLDocument()
{
	delete peer_;
}

VCF::HTMLDocument& VCF::HTMLDocument::operator= ( const VCF::HTMLDocument& rhs ) 
{
	*peer_ = *rhs.peer_;
	return *this;
}

void VCF::HTMLDocument::setPeer( HTMLDocumentPeer* doc )
{
	*peer_ = *doc;
}

bool VCF::HTMLDocument::null() const 
{
	return peer_->is_null();
}

VCF::HTMLElementCollection VCF::HTMLDocument::getAll() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_all( result.peer_->out() );		
	return result;
}

VCF::HTMLElement VCF::HTMLDocument::getBody() const 
{
	VCF::HTMLElementPeer element;
	(*peer_)->get_body( element.out() );
	
	return VCF::HTMLElement(&element);
}

VCF::HTMLElement VCF::HTMLDocument::getActiveElement() const 
{
	VCF::HTMLElementPeer element;
	(*peer_)->get_activeElement( element.out() );
	
	return VCF::HTMLElement(&element);
}


VCF::HTMLElementCollection VCF::HTMLDocument::getImages() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_images( result.peer_->out() );		
	return result;
}

VCF::HTMLElementCollection VCF::HTMLDocument::getApplets() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_applets( result.peer_->out() );		
	return result;
}

VCF::HTMLElementCollection VCF::HTMLDocument::getLinks() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_links( result.peer_->out() );		
	return result;
}

VCF::HTMLElementCollection VCF::HTMLDocument::getForms() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_forms( result.peer_->out() );		
	return result;
}

VCF::HTMLElementCollection VCF::HTMLDocument::getAnchors() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_anchors( result.peer_->out() );		
	return result;
}

void VCF::HTMLDocument::setTitle( const VCF::String& title ) 
{
	(*peer_)->put_title( bstr_t(title.c_str()).in() );		
}

VCF::String VCF::HTMLDocument::getTitle() const 
{
	bstr_t tmp;
	(*peer_)->get_title( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::HTMLElementCollection VCF::HTMLDocument::getScripts() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_scripts( result.peer_->out() );		
	return result;
}


VCF::String VCF::HTMLDocument::getReadyState() const 
{
	bstr_t tmp;
	(*peer_)->get_readyState( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::HTMLElementCollection VCF::HTMLDocument::getEmbeds() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_embeds( result.peer_->out() );		
	return result;
}

VCF::HTMLElementCollection VCF::HTMLDocument::getPlugins() 
{
	VCF::HTMLElementCollection result;		
	(*peer_)->get_plugins( result.peer_->out() );		
	return result;
}

VCF::String VCF::HTMLDocument::getReferrer() const 
{
	bstr_t tmp;
	(*peer_)->get_referrer( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getLastModified() const 
{
	bstr_t tmp;
	(*peer_)->get_lastModified( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLDocument::setURL( const VCF::String& url ) 
{
	(*peer_)->put_URL( bstr_t(url.c_str()).in() );		
}

VCF::String VCF::HTMLDocument::getURL() const 
{
	bstr_t tmp;
	(*peer_)->get_URL( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLDocument::setDomain( const VCF::String& domain ) 
{
	(*peer_)->put_domain( bstr_t(domain.c_str()).in() );		
}

VCF::String VCF::HTMLDocument::getDomain() const 
{
	bstr_t tmp;
	(*peer_)->get_domain( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLDocument::setCookie( const VCF::String& cookie ) 
{
	(*peer_)->put_cookie( bstr_t(cookie.c_str()).in() );		
}

VCF::String VCF::HTMLDocument::getCookie() const 
{
	bstr_t tmp;
	(*peer_)->get_cookie( tmp.out() );
	return VCF::String(tmp.c_str());
}

bool VCF::HTMLDocument::getExpando() const 
{
	VARIANT_BOOL result = FALSE;
	(*peer_)->get_expando( &result );
	return result ? true : false;
}

void VCF::HTMLDocument::setExpando( bool expando ) 
{
	(*peer_)->put_expando( expando ? TRUE : FALSE );
}

void VCF::HTMLDocument::setCharset( const VCF::String& val ) 
{
	(*peer_)->put_charset( bstr_t(val.c_str()).in() );		
}

VCF::String VCF::HTMLDocument::getCharset() const 
{
	bstr_t tmp;
	(*peer_)->get_charset( tmp.out() );
	return VCF::String(tmp.c_str());
}

void VCF::HTMLDocument::setDefaultCharset( const VCF::String& val ) 
{
	(*peer_)->put_defaultCharset( bstr_t(val.c_str()).in() );		
}

VCF::String VCF::HTMLDocument::getDefaultCharset() const 
{
	bstr_t tmp;
	(*peer_)->get_defaultCharset( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getMimeType() const 
{
	bstr_t tmp;
	(*peer_)->get_mimeType( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getFileSize() const 
{
	bstr_t tmp;
	(*peer_)->get_fileSize( tmp.out() );
	return VCF::String(tmp.c_str());
}

int VCF::HTMLDocument::getIntFileSize() const 
{
	bstr_t tmp;
	(*peer_)->get_fileSize( tmp.out() );
	return atoi(tmp.s_str().c_str());
}

VCF::String VCF::HTMLDocument::getFileCreatedDate() const 
{
	bstr_t tmp;
	(*peer_)->get_fileCreatedDate( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getFileModifiedDate() const 
{
	bstr_t tmp;
	(*peer_)->get_fileModifiedDate( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getFileUpdatedDate() const 
{
	bstr_t tmp;
	(*peer_)->get_fileUpdatedDate( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getSecurity() const 
{
	bstr_t tmp;
	(*peer_)->get_security( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getProtocol() const 
{
	bstr_t tmp;
	(*peer_)->get_protocol( tmp.out() );
	return VCF::String(tmp.c_str());
}

VCF::String VCF::HTMLDocument::getNameProp() const 
{
	bstr_t tmp;
	(*peer_)->get_nameProp( tmp.out() );
	return VCF::String(tmp.c_str());
} 


VCF::String VCF::HTMLDocument::toString() const 
{
	bstr_t tmp;
	(*peer_)->toString( tmp.out() );
	return VCF::String(tmp.c_str());
} 

void VCF::HTMLDocument::write( const VCF::String& text ) 
{
	
	SAFEARRAY *strArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

	if ( NULL != strArray ) {
		BSTR bstr = SysAllocStringLen(text.c_str(),text.size());
		VARIANT *param;
		hresult hr  = SafeArrayAccessData(strArray,(LPVOID*) & param);
		if ( hr ) {
			param->vt = VT_BSTR;
			param->bstrVal = bstr;
			hr = SafeArrayUnaccessData(strArray);

			(*peer_)->write( strArray );			
		}
		SysFreeString(bstr);
		SafeArrayDestroy(strArray);
	}

/*
This is the code that we'd like to use, but, at the moment
it's not supported by BCC
	safearray_t<variant_t> sarr;
	
	variant_t v = text.c_str();
	sarr.push_back(v);
	
	(*peer_)->write( sarr.in() );
	*/
}

void VCF::HTMLDocument::writeln( const VCF::String& text ) 
{
	SAFEARRAY *strArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

	if ( NULL != strArray ) {
		BSTR bstr = SysAllocStringLen(text.c_str(),text.size());
		VARIANT *param;
		hresult hr  = SafeArrayAccessData(strArray,(LPVOID*) & param);
		if ( hr ) {
			param->vt = VT_BSTR;
			param->bstrVal = bstr;
			hr = SafeArrayUnaccessData(strArray);

			(*peer_)->writeln( strArray );			
		}
		SysFreeString(bstr);
		SafeArrayDestroy(strArray);
	}
	
/*
This is the code that we'd like to use, but, at the moment
it's not supported by BCC
	safearray_t<variant_t> sarr;
	
	variant_t v = text.c_str();
	sarr.push_back(v);
	
	(*peer_)->writeln( sarr.in() );
	*/
}

VCF::HTMLElement VCF::HTMLDocument::createElement( const VCF::String& elementTag ) const 
{
	VCF::HTMLElementPeer element;
	(*peer_)->createElement( bstr_t(elementTag.c_str()).in(), element.out() );
	
	return VCF::HTMLElement(&element);
}

void VCF::HTMLDocument::setDesignMode( bool val ) 
{
	bstr_t mode = val ? "on" : "off";
	(*peer_)->put_designMode( mode.in() );
}

bool VCF::HTMLDocument::getDesignMode() const 
{
	bool result = false;
	bstr_t mode;
	(*peer_)->get_designMode( mode.out() );
	
	if ( mode.s_str() == "off" ) {
		result = false;
	}
	else if ( mode.s_str() == "on" ) {
		result = true;
	}
	
	return result;
}

VCF::HTMLElement VCF::HTMLDocument::elementFromPoint( long x, long y )
{
	VCF::HTMLElement result;

	VCF::HTMLElementPeer element;
	(*peer_)->elementFromPoint( x, y, element.out() );

	if ( !element.is_null() ) {
		result.setPeer( &element );
	}

	return result;
}

void VCF::HTMLDocument::copy() 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Copy";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::cut() 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Cut";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::paste() 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Paste";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::selectAll() 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "SelectAll";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::underline() 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Underline";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::bold() 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Bold";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::italic () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Italic";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::justifyLeft () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "JustifyLeft";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::justifyRight () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "JustifyRight";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::justifyCenter () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "JustifyCenter";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::justifyFull () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "JustifyFull";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::outdent () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Outdent ";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::indent () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Indent";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}

void VCF::HTMLDocument::clearSelection () 
{
	variant_t v;
	VARIANT_BOOL res;
	bstr_t cmd = "Unselect";
	(*peer_)->execCommand( cmd.in(), TRUE, v.in(), &res );
}


