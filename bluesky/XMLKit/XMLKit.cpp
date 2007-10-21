////XMLKit.cpp


#include "XMLKit.h"


#include <libxml/parser.h>


#include <libxml/xpathInternals.h>

#include "vcf/FoundationKit/Dictionary.h"




#include "DOM3.h"






#pragma comment ( lib, "ws2_32.lib" )



using namespace VCF;




void XMLKit::init( int argc, char **argv ) 
{
	xmlInitParser();
}

void XMLKit::terminate()
{
	xmlCleanupParser();

#ifdef _DEBUG   
	//it appears that unless MEM_LIST is defined, the call below does nothing
	xmlMemoryDump();
#endif
}
	

	
void XMLUtils::freeXMLStr( xmlChar* str )
{
	xmlFreeFunc freeFunc;
	xmlMallocFunc f1;			
	xmlReallocFunc f3;
	xmlStrdupFunc f4;
	xmlMemGet( &freeFunc, &f1, &f3, &f4 );
	
	freeFunc( str );
}
	


	

	

XMLSaxParser::XMLSaxParser(): parser_(NULL)
{
	memset(&saxHandler_,0,sizeof(saxHandler_));

	saxHandler_.internalSubset = internalSubsetSAXFunc;
	saxHandler_.entityDecl = entityDeclSAXFunc;
	saxHandler_.notationDecl = notationDeclSAXFunc;
	saxHandler_.attributeDecl = attributeDeclSAXFunc;
	saxHandler_.elementDecl = elementDeclSAXFunc;
	saxHandler_.unparsedEntityDecl = unparsedEntityDeclSAXFunc;
	saxHandler_.startDocument = startDocumentSAXFunc;
	saxHandler_.endDocument = endDocumentSAXFunc;
	saxHandler_.startElement = startElementSAXFunc;
	saxHandler_.endElement = endElementSAXFunc;
	saxHandler_.reference = referenceSAXFunc;
	saxHandler_.characters = charactersSAXFunc;
	saxHandler_.ignorableWhitespace = ignorableWhitespaceSAXFunc;
	saxHandler_.processingInstruction = processingInstructionSAXFunc;
	saxHandler_.comment = commentSAXFunc;
	saxHandler_.warning = warningSAXFunc;
	saxHandler_.error = errorSAXFunc;
	saxHandler_.fatalError = fatalErrorSAXFunc;
	saxHandler_.cdataBlock = cdataBlockSAXFunc;
	saxHandler_.externalSubset = externalSubsetSAXFunc;
	saxHandler_.startElementNs = startElementNsSAX2Func;
	saxHandler_.endElementNs = endElementNsSAX2Func;



	parser_ = xmlCreatePushParserCtxt( &saxHandler_, this, NULL, 0, NULL );
}

XMLSaxParser::~XMLSaxParser() 
{
	xmlFreeParserCtxt( parser_ );
}


void XMLSaxParser::parse( const String& xml ) 
{
	AnsiString tmp = xml;

	xmlParseChunk( parser_, tmp.c_str(), tmp.size(), 1 );
}


void XMLSaxParser::parseChunk( const String& xmlChunk, bool finished ) 
{
	AnsiString tmp = xmlChunk;

	xmlParseChunk( parser_, tmp.c_str(), tmp.size(), finished ? 1 : 0 );
}

void XMLSaxParser::finishParsing()
{
	parseChunk( "", true );
}

void XMLSaxParser::internalSubsetSAXFunc(void * ctx, 
			 const xmlChar * name, 
			 const xmlChar * ExternalID, 
			 const xmlChar * SystemID) 
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->InternalSubset(name,ExternalID,SystemID);
	}
}

void XMLSaxParser::entityDeclSAXFunc(void * ctx, 
			 const xmlChar * name, 
			 int type, 
			 const xmlChar * publicId, 
			 const xmlChar * systemId, 
			 xmlChar * content)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->EntityDecl(name,type,publicId,systemId,content);
	}
}

void XMLSaxParser::notationDeclSAXFunc(void * ctx, const xmlChar * name, 
								const xmlChar * publicId, const xmlChar * systemId)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->NotationDecl(name,publicId,systemId);
	}
}

void XMLSaxParser::attributeDeclSAXFunc(void * ctx, 
			 const xmlChar * elem, 
			 const xmlChar * fullname, 
			 int type, 
			 int def, 
			 const xmlChar * defaultValue, 
			 xmlEnumerationPtr tree)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->AttributeDecl(elem,fullname,type,def,defaultValue,tree);
	}			
}

void XMLSaxParser::elementDeclSAXFunc(void * ctx, 
			 const xmlChar * name, 
			 int type, 
			 xmlElementContentPtr content)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->ElementDecl(name,type,content);
	}
}

void XMLSaxParser::unparsedEntityDeclSAXFunc(void * ctx, 
			 const xmlChar * name, 
			 const xmlChar * publicId, 
			 const xmlChar * systemId, 
			 const xmlChar * notationName)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->UnparsedEntityDecl(name,publicId,systemId,notationName);
	}
}

void XMLSaxParser::startDocumentSAXFunc(void * ctx)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->StartDocument();
	}			
}

void XMLSaxParser::endDocumentSAXFunc(void * ctx)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->EndDocument();
	}	
}

void XMLSaxParser::startElementSAXFunc (void * ctx, 
			 const xmlChar * name, 
			 const xmlChar ** atts)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->StartElement(name,atts);
	}	
}

void XMLSaxParser::endElementSAXFunc(void * ctx, 
			 const xmlChar * name)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->EndElement(name);
	}	
}

void XMLSaxParser::referenceSAXFunc(void * ctx, 
			 const xmlChar * name)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->Reference(name);
	}
}

void XMLSaxParser::charactersSAXFunc(void * ctx, 
			 const xmlChar * ch, 
			 int len)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->Characters(ch,len);
	}
}

void XMLSaxParser::ignorableWhitespaceSAXFunc(void * ctx, 
			 const xmlChar * ch, 
			 int len)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->IgnorableWhitespace(ch,len);
	}
}

void XMLSaxParser::processingInstructionSAXFunc(void * ctx, 
			 const xmlChar * target, 
			 const xmlChar * data)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->ProcessingInstruction(target,data);
	}
}

void XMLSaxParser::commentSAXFunc(void * ctx, 
			 const xmlChar * value)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->Comment(value);
	}
}

void XMLSaxParser::warningSAXFunc(void * ctx, const char * msg, ...)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {

		va_list argList;
		va_start( argList, ctx ); 
		char tmp[1024];
		
		_vsnprintf( tmp, sizeof(tmp), msg, argList );
		tmp[sizeof(tmp)-1] = 0;
		
		va_end( argList );


		thisPtr->Warning(tmp);
	}
}

void XMLSaxParser::errorSAXFunc(void * ctx, const char * msg, ...)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {

		va_list argList;
		va_start( argList, ctx ); 
		char tmp[1024];
		
		_vsnprintf( tmp, sizeof(tmp), msg, argList );
		tmp[sizeof(tmp)-1] = 0;
		
		va_end( argList );


		thisPtr->Error(tmp);
	}
}


void XMLSaxParser::fatalErrorSAXFunc(void * ctx, const char * msg, ...)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {

		va_list argList;
		va_start( argList, ctx ); 
		char tmp[1024];
		
		_vsnprintf( tmp, sizeof(tmp), msg, argList );
		tmp[sizeof(tmp)-1] = 0;
		
		va_end( argList );


		thisPtr->FatalError(tmp);
	}
}

void XMLSaxParser::cdataBlockSAXFunc(void * ctx,  const xmlChar * value, int len)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->CDATABlock(value,len);
	}			
}

void XMLSaxParser::externalSubsetSAXFunc	(void * ctx, 
			 const xmlChar * name, 
			 const xmlChar * ExternalID, 
			 const xmlChar * SystemID)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->ExternalSubset(name,ExternalID,SystemID);
	}
}

void XMLSaxParser::startElementNsSAX2Func(void * ctx, 
			 const xmlChar * localname, 
			 const xmlChar * prefix, 
			 const xmlChar * URI, 
			 int nb_namespaces, 
			 const xmlChar ** namespaces, 
			 int nb_attributes, 
			 int nb_defaulted, 
			 const xmlChar ** attributes)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->StartElementNs(localname,prefix,URI,nb_namespaces,namespaces,nb_attributes,nb_defaulted,attributes);
	}
}

void XMLSaxParser::endElementNsSAX2Func(void * ctx, 
			 const xmlChar * localname, 
			 const xmlChar * prefix, 
			 const xmlChar * URI)
{
	XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
	if ( NULL != thisPtr ) {
		thisPtr->EndElementNs(localname,prefix,URI);
	}			
}



void XmlNamespace::freeResource(xmlNsPtr res)
{
	xmlFreeNs( res );
}



void XmlNode::freeResource(xmlNodePtr res)
{
	xmlUnlinkNode( res );
	xmlFreeNode( res );
}

bool XmlNode::getChildren( std::vector<XmlNode>& nodes ) const 
{
	xmlNode *child = resource_->children;
	while ( NULL != child ) {			
		nodes.push_back( XmlNode(child) );
		child = child->next;
	}

	return !nodes.empty();
}

XmlNode XmlNode::getParent() const
{
	return XmlNode(resource_->parent);
}

XMLNodeType XmlNode::getType() const 
{
	return (XMLNodeType) resource_->type;
}


String XmlNode::getPath() const 
{
	String result;

	xmlChar* res = 
		xmlGetNodePath( resource_ );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}


XmlNode XmlNode::copy( bool deep ) const 
{
	return XmlNode( xmlCopyNode( resource_, deep ? 1 : 2 ) );
}


XmlNode XmlNode::copyList() const 
{
	return XmlNode( xmlCopyNodeList( resource_ ) );
}

String XmlNode::getAttribute( const String& name ) const 
{
	String result;

	xmlChar* res = 
		xmlGetProp( resource_, (const xmlChar*)name.ansi_c_str() );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}

void XmlNode::setNamespaceAttr( const XmlNamespace& ns, const String& name, const String& value )
{
	AnsiString n = name;
	AnsiString v = value;

	xmlSetNsProp( resource_, ns.get(), (const xmlChar*)n.c_str(), (const xmlChar*)v.c_str() );
}

void XmlNode::setAttribute( const String& name, const String& value )
{
	AnsiString n = name;
	AnsiString v = value;

	xmlSetProp( resource_, (const xmlChar*)n.c_str(), (const xmlChar*)v.c_str() );
}

bool XmlNode::empty() const 
{
	return xmlIsBlankNode( resource_ ) == 1 ? true : false;
}


String XmlNode::getContent() const 
{
	String result;

	xmlChar* res = 
		xmlNodeGetContent( resource_ );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}		

String XmlNode::getLang() const 
{
	String result;

	xmlChar* res = 
		xmlNodeGetLang( resource_ );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}

String XmlNode::getBase() const 
{
	String result;

	xmlChar* res = 
		xmlNodeGetBase( resource_->doc, resource_ );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}

void XmlNode::setBase( const String& val ) 
{
	xmlNodeSetBase( resource_, (const xmlChar*)val.ansi_c_str() );
}

XmlNode::PreservesSpace XmlNode::getPreservesSpace() const 
{
	return (PreservesSpace) xmlNodeGetSpacePreserve( resource_ );
}

bool XmlNode::isText() const 
{
	return xmlNodeIsText( resource_ ) == 1 ? true : false;
}

int XmlNode::getLineNumber() const 
{
	return xmlGetLineNo( resource_ );
}

void XmlNode::setBaseURI( const String& val ) 
{
	xmlNodeSetBase( resource_, (const xmlChar*) val.ansi_c_str() );
}

void XmlNode::setContent( const String& val ) 
{
	xmlNodeSetContent( resource_, (const xmlChar*) val.ansi_c_str() );
}

void XmlNode::setLang( const String& val ) 
{
	xmlNodeSetLang( resource_, (const xmlChar*) val.ansi_c_str() );
}

void XmlNode::setName( const String& val ) 
{
	xmlNodeSetName( resource_, (const xmlChar*) val.ansi_c_str() );
}

String XmlNode::getName() const 
{
	String result = (const char*)resource_->name;

	return result;
}

int XmlNode::reconcileNamespaces() const 
{
	return xmlReconciliateNs( resource_->doc, resource_ );
}

bool XmlNode::getNamespaceList( std::vector<XmlNamespace>& namespaces ) const
{
	xmlNsPtr* res = xmlGetNsList( resource_->doc, resource_ );

	if ( NULL != res ) {
		while ( NULL != *res ) {
			namespaces.push_back( XmlNamespace(*res) );
			res ++;
		}
	}
	return !namespaces.empty();
}

void XmlNode::setNamespace( const XmlNamespace& ns )
{
	xmlSetNs( resource_, ns.get() );
}

XmlNamespace XmlNode::searchNamespace( const String& ns ) 
{
	return XmlNamespace( 
				xmlSearchNs( resource_->doc, resource_, (const xmlChar*)ns.ansi_c_str() ) 
				);
}

XmlNamespace XmlNode::searchNamespaceByHRef( const String& href ) 
{
	return XmlNamespace( 
				xmlSearchNsByHref( resource_->doc, resource_, (const xmlChar*)href.ansi_c_str() ) 
				);
}

XmlNode* XmlNode::copy( const XmlDocument& doc, bool extended ); 


void XmlNode::addChild( XmlNode& child ) 
{
	if ( !child.isNull() ) {
		xmlAddChild( resource_, child.detach() );
	}
}

void XmlNode::addNextSibling( XmlNode& element ) 
{
	if ( !element.isNull() ) {
		xmlAddNextSibling( resource_, element.detach() );
	}
}

void XmlNode::addPrevSibling( XmlNode& element ) 
{
	if ( !element.isNull() ) {
		xmlAddPrevSibling( resource_, element.detach() );
	}
}

void XmlNode::addSibling( XmlNode& element ) 
{
	if ( !element.isNull() ) {
		xmlAddSibling( resource_, element.detach() );
	}
}

XmlNode* XmlNode::copy( const XmlDocument& doc, bool extended )
{
	XmlNode* result = NULL;
	xmlNodePtr res = xmlDocCopyNode( resource_, doc.get(), extended ? 2 : 1 );

	if ( res ) {
		result = new XmlNode();
		result->attach( res);
	}
	return result;
}


XmlDocument XmlNode::getDocument() const 
{
	return XmlDocument(resource_->doc);
}

void XmlNode::setDocument ( const XmlDocument& doc )
{
	xmlSetTreeDoc( resource_, doc.get() );
}






		
void XmlDocument::freeResource(xmlDocPtr res)
{
	xmlFreeDoc( res );
}


void XmlDocument::setXML( const String& xml )
{
	if ( owned_ ) {
		if ( resource_ ) {
			xmlFreeDoc(resource_);
		}
	}

	AnsiString s = xml;
	attach( xmlParseMemory( s.c_str(), s.size() ) );
}


XmlNode XmlDocument::getRoot() const 
{
	return XmlNode( xmlDocGetRootElement( resource_ ) );
}



XmlDocument* XmlDocument::copy( bool recursive ) const 
{
	XmlDocument* result = NULL;

	xmlDocPtr res = xmlCopyDoc( resource_, recursive ? 1 : 0 );

	if ( NULL != res ) {
		result = new XmlDocument();
		result->attach(res);
	}

	return result;
}


XmlNode* XmlDocument::newCDATABlock( const String& data ) 
{
	XmlNode* result = NULL;

	AnsiString tmp = data;
	xmlNodePtr res = xmlNewCDataBlock( resource_, (const xmlChar*)tmp.c_str(), tmp.size() );
	if ( NULL != res ) {
		result = new XmlNode();
		result->attach( res );
	}	

	return result;
}

XmlNode* XmlDocument::newCharRef( const String& name ) 
{
	XmlNode* result = NULL;

	AnsiString tmp = name;
	xmlNodePtr res = xmlNewCharRef( resource_, (const xmlChar*)tmp.c_str() );
	if ( NULL != res ) {
		result = new XmlNode();
		result->attach( res );
	}	

	return result;
}

XmlNode* XmlDocument::newComment( const String& comment ) 
{
	XmlNode* result = NULL;

	AnsiString tmp = comment;
	xmlNodePtr res = xmlNewDocComment( resource_, (const xmlChar*)tmp.c_str() );
	if ( NULL != res ) {
		result = new XmlNode();
		result->attach( res );
	}	

	return result;
}

XmlNode* XmlDocument::newFragment() 
{
	XmlNode* result = NULL;
	xmlNodePtr res = xmlNewDocFragment( resource_ );
	if ( NULL != res ) {
		result = new XmlNode();
		result->attach( res );
	}	

	return result;
}

XmlNode* XmlDocument::newNode( const XmlNamespace& ns, const String& name, const String& content ) 
{
	
	XmlNode* result = NULL;
	xmlNodePtr res = xmlNewDocNode( resource_, ns.get(), 
									(const xmlChar*)name.ansi_c_str(),
									(const xmlChar*)content.ansi_c_str() );
	if ( NULL != res ) {
		result = new XmlNode();
		result->attach( res );
	}	

	return result;
}

XmlNode* XmlDocument::newNode( const String& name, const String& content ) 
{
	return newNode(XmlNamespace(), name, content);
}

XmlNode* XmlDocument::newRawNode( const XmlNamespace& ns, const String& name, const String& content ) 
{
	
	XmlNode* result = NULL;
	xmlNodePtr res = xmlNewDocRawNode( resource_, ns.get(), 
									(const xmlChar*)name.ansi_c_str(),
									(const xmlChar*)content.ansi_c_str() );
	if ( NULL != res ) {
		result = new XmlNode();
		result->attach( res );
	}	

	return result;
}

XmlNode* XmlDocument::newRawNode( const String& name, const String& content ) 
{
	return newRawNode(XmlNamespace(), name, content);
}

XmlNode* XmlDocument::newProcessingInstruction( const String& name, const String& content ) 
{
	XmlNode* result = NULL;
	xmlNodePtr res = xmlNewDocPI( resource_,(const xmlChar*)name.ansi_c_str(),
									(const xmlChar*)content.ansi_c_str() );
	if ( NULL != res ) {
		result = new XmlNode();
		result->attach( res );
	}

	return result;
}

XmlDocument* XmlDocument::newDocument() 
{
	XmlDocument* result = NULL;

	xmlDocPtr res = xmlNewDoc( (const xmlChar*)"1.0" );
	if ( NULL != res ) {
		result = new XmlDocument();
		result->attach( res );
	}
	
	return result;
}


VariantData XmlDocument::matches( const String& xpathQuery, std::vector<XmlNode>& found )
{
	VariantData result;
	result.setNull();

	found.clear();

	xmlXPathContextPtr xpathCtx = NULL; 
	xmlXPathObjectPtr xpathObj = NULL;

	xpathCtx = xmlXPathNewContext( resource_ );
	xpathObj = xmlXPathEval( (const xmlChar*)xpathQuery.ansi_c_str(), xpathCtx);

	switch ( xpathObj->type ) {
		case XPATH_NODESET : {
			if ( NULL != xpathObj->nodesetval ) {
				for ( int i=0;i < xpathObj->nodesetval->nodeNr; i++ ) {
					found.push_back(XmlNode( xpathObj->nodesetval->nodeTab[i] ));
				}
			}
		}
		break;

		case XPATH_BOOLEAN : {
			result = xpathObj->boolval != 0 ? true : false;
		}
		break;

		case XPATH_NUMBER : {
			result = xpathObj->floatval;
		}
		break;

		case XPATH_STRING : {
			result = String( (const char*) xpathObj->stringval );
		}
		break;
		/* we ignore the rest???
XPATH_POINT = 5
XPATH_RANGE = 6
XPATH_LOCATIONSET = 7
XPATH_USERS = 8
XPATH_XSLT_TREE 
*/
	}

	

	xmlXPathFreeObject(xpathObj);
	xmlXPathFreeContext(xpathCtx); 

	return result;
}

XmlNode XmlDocument::select( const String& xpathQuery )
{
	XmlNode result;
	std::vector<XmlNode> found;
	matches( xpathQuery, found );
	if ( !found.empty() ) {
		result = found.front();
	}

	return result;
}





void XPathExpression::freeResource(xmlXPathCompExprPtr res)
{
	xmlXPathFreeCompExpr( res );
}


void XPathExpression::compile( const String& xpathQuery )
{
	assign( NULL ); //free's up old expression
	attach( xmlXPathCompile( (const xmlChar*)xpathQuery.ansi_c_str() ) );
}






XPathIterator::XPathIterator( const XmlDocument& doc ):
	BaseT(),xpathObj_(NULL)
{
	attach( xmlXPathNewContext( doc.get() ) );
}

void XPathIterator::freeResource(xmlXPathContextPtr res)
{
	xmlXPathFreeContext( res );
}


VariantData XPathIterator::eval( const XPathExpression& expression ) {

	VariantData result;
	result.setNull();

	nodes_.clear();

	if ( NULL != xpathObj_ ) {
		xmlXPathFreeObject( xpathObj_ );
	}

	xpathObj_ = xmlXPathCompiledEval( expression.get(), resource_ );

	switch ( xpathObj_->type ) {				
		case XPATH_BOOLEAN : {
			result = xpathObj_->boolval != 0 ? true : false;
		}
		break;

		case XPATH_NUMBER : {
			result = xpathObj_->floatval;
		}
		break;

		case XPATH_STRING : {
			result = String( (const char*) xpathObj_->stringval );
		}
		break;
		/* we ignore the rest???
XPATH_POINT = 5
XPATH_RANGE = 6
XPATH_LOCATIONSET = 7
XPATH_USERS = 8
XPATH_XSLT_TREE 
*/
	}

	return result;
}


XmlNode XPathIterator::select( const XPathExpression& expression )
{
	XmlNode result;

	eval( expression );

	switch ( xpathObj_->type ) {
		case XPATH_NODESET : {
			if ( NULL != xpathObj_->nodesetval ) {
				if ( xpathObj_->nodesetval->nodeNr > 0 ) {
					result = xpathObj_->nodesetval->nodeTab[0];
				}
			}
		}
		break;
	}

	return result;
}


XPathNodeIterator XPathIterator::selectNodes( const XPathExpression& expression )
{
	eval( expression );

	switch ( xpathObj_->type ) {
		case XPATH_NODESET : {
			if ( NULL != xpathObj_->nodesetval ) {
				for ( int i=0;i < xpathObj_->nodesetval->nodeNr; i++ ) {
					nodes_.push_back(XmlNode( xpathObj_->nodesetval->nodeTab[i] ));
				}

				return XPathNodeIterator(nodes_);
			}
		}
		break;
	}

	return XPathNodeIterator();
}

void XPathIterator::registerNamespaces( Dictionary& namespaceDict ) 
{
	Dictionary::Enumerator* items = namespaceDict.getEnumerator();
	while ( items->hasMoreElements() )  {
		Dictionary::pair ns = items->nextElement();
		const String& prefix = ns.first;
		
		VariantData& v = ns.second;
		//make sure this is actually a String!
		VCF_ASSERT( pdString == v.type );
		if ( pdString == v.type ) {
			const String& nsUri = v;
			
			xmlXPathRegisterNs( resource_, 
								(const xmlChar*) prefix.ansi_c_str(),
								(const xmlChar*) nsUri.ansi_c_str() );
		}
	}
}





XMLTextReader::XMLTextReader():
	xmlReader_(NULL)
{
	createXMLReader();
}

XMLTextReader::~XMLTextReader()
{
	if ( NULL != xmlReader_ ) {
		xmlFreeTextReader( xmlReader_ );
		xmlSetStructuredErrorFunc( NULL, NULL );
	}
}


size_t XMLTextReader::getAttributeCount() const 
{
	VCF_ASSERT( NULL != xmlReader_ );

	size_t result = 0;
	int res = xmlTextReaderAttributeCount( xmlReader_ );

	if ( res < 0 ) {
		//throw an exception????
	}
	else {
		result = res;
	}
	return result;
}

String XMLTextReader::getBaseURI() const 
{
	String result;
	VCF_ASSERT( NULL != xmlReader_ );

	const xmlChar* uri = xmlTextReaderConstBaseUri( xmlReader_ );
	if ( NULL != uri ) {
		result = (const char*)uri;
	}

	return result;
}

int XMLTextReader::getBytesConsumed() const 
{
	int result = -1;

	result = xmlTextReaderByteConsumed( xmlReader_ );

	return result;
}

bool XMLTextReader::close() 
{
	return xmlTextReaderClose( xmlReader_ ) < 0 ? false : true;
}

String XMLTextReader::getEncoding() const 
{
	String result;
	const xmlChar* enc = xmlTextReaderConstEncoding( xmlReader_ );
	if ( NULL != enc ) {
		result = (const char*) enc;
	}
	return result;
}

String XMLTextReader::getLocalName() const 
{
	String result;
	const xmlChar* val = xmlTextReaderConstLocalName( xmlReader_ );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getName() const 
{
	String result;
	const xmlChar* val = xmlTextReaderConstName( xmlReader_ );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getNamespaceURI() const 
{
	String result;
	const xmlChar* val = xmlTextReaderConstNamespaceUri( xmlReader_ );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getPrefix() const 
{
	String result;
	const xmlChar* val = xmlTextReaderConstPrefix( xmlReader_ );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getTextValue() const 
{
	String result;
	const xmlChar* val = xmlTextReaderConstValue( xmlReader_ );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getLang() const 
{
	String result;
	const xmlChar* val = xmlTextReaderConstXmlLang( xmlReader_ );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getVersion() const 
{
	String result;
	const xmlChar* val = xmlTextReaderConstXmlVersion( xmlReader_ );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

int XMLTextReader::getCurrentDepth() const 
{
	int result = -1;

	result = xmlTextReaderDepth( xmlReader_ );

	return result;
}

XmlNode XMLTextReader::expand() 
{			
	xmlNodePtr nodePtr = xmlTextReaderExpand( xmlReader_ );

	XmlNode result( nodePtr );
	result.detach();

	return result;
}

String XMLTextReader::getAttribute( const String& name ) const 
{

	String result;
	const xmlChar* val = xmlTextReaderGetAttribute( xmlReader_, (const xmlChar*) name.ansi_c_str() );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getAttribute( const size_t& index ) const 
{

	String result;
	const xmlChar* val = xmlTextReaderGetAttributeNo( xmlReader_, index );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}

String XMLTextReader::getAttribute( const String& localName, const String& namespaceURI ) const 
{

	String result;
	const xmlChar* val = 
		xmlTextReaderGetAttributeNs( xmlReader_, 
										(const xmlChar*) localName.ansi_c_str(),
										(const xmlChar*) namespaceURI.ansi_c_str() );
	if ( NULL != val ) {
		result = (const char*) val;
	}
	return result;
}


int XMLTextReader::getCurrentParserColumn() const 
{
	return xmlTextReaderGetParserColumnNumber( xmlReader_ );
}

int XMLTextReader::getCurrentParserLine() const 
{
	return xmlTextReaderGetParserLineNumber( xmlReader_ );
}

bool XMLTextReader::parserLoadsDTD() const 
{
	int res = xmlTextReaderGetParserProp( xmlReader_, XML_PARSER_LOADDTD );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::parserUsingDefaultAttrs() const 
{
	int res = xmlTextReaderGetParserProp( xmlReader_, XML_PARSER_DEFAULTATTRS );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::parserWillValidate() const 
{
	int res = xmlTextReaderGetParserProp( xmlReader_, XML_PARSER_VALIDATE );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::parserWillSubstituteEntities() const 
{
	int res = xmlTextReaderGetParserProp( xmlReader_, XML_PARSER_SUBST_ENTITIES );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

void XMLTextReader::setParserLoadsDTD( bool val ) 
{
	int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_LOADDTD, val ? 1 : 0 );			
	if ( res < 0 ) {
		//throw exception???
	}
}

void XMLTextReader::setParserDefaultAttrs( bool val ) 
{
	int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_DEFAULTATTRS, val ? 1 : 0 );			
	if ( res < 0 ) {
		//throw exception???
	}
}

void XMLTextReader::setParserWillValidate( bool val ) 
{
	int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_VALIDATE, val ? 1 : 0 );			
	if ( res < 0 ) {
		//throw exception???
	}
}

void XMLTextReader::setParserWillSubstituteEntities( bool val ) 
{			
	int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_SUBST_ENTITIES, val ? 1 : 0 );			
	if ( res < 0 ) {
		//throw exception???
	}
}


bool XMLTextReader::hasAttributes() const 
{
	int res = xmlTextReaderHasAttributes( xmlReader_ );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::hasValue() const 
{
	int res = xmlTextReaderHasValue( xmlReader_ );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::isDefaultValue() const 
{
	int res = xmlTextReaderIsDefault( xmlReader_ );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::isEmptyElement() const 
{
	int res = xmlTextReaderIsEmptyElement( xmlReader_ );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::isNamespace() const 
{
	int res = xmlTextReaderIsNamespaceDecl( xmlReader_ );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::isParserValid() const 
{
	int res = xmlTextReaderIsValid( xmlReader_ );
	bool result = false;
	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

String XMLTextReader::lookupNamespace( const String& prefix ) const 
{
	String result;
	xmlChar* res = xmlTextReaderLookupNamespace( xmlReader_, (const xmlChar*) prefix.ansi_c_str() );	
	
	if ( NULL != res ) {

		result = (const char*)res;

		XMLUtils::freeXMLStr(res);
	}

	return result;
}
	
bool XMLTextReader::moveToAttribute( const String& attributeName ) 
{
	bool result = false;

	int res = xmlTextReaderMoveToAttribute( xmlReader_, (const xmlChar*) attributeName.ansi_c_str() );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::moveToAttribute( size_t index ) 
{
	bool result = false;

	int res = xmlTextReaderMoveToAttributeNo( xmlReader_, index );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::moveToAttribute( const String& localAttrName, const String& namespaceURI ) 
{
	bool result = false;

	int res = 
		xmlTextReaderMoveToAttributeNs( xmlReader_, 
										(const xmlChar*) localAttrName.ansi_c_str(),
										(const xmlChar*) namespaceURI.ansi_c_str() );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::moveToElement() 
{
	bool result = false;

	int res = 
		xmlTextReaderMoveToElement( xmlReader_ );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::moveToFirstAttribute() 
{
	bool result = false;

	int res = 
		xmlTextReaderMoveToFirstAttribute( xmlReader_ );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::moveToNextAttribute() 
{
	bool result = false;

	int res = 
		xmlTextReaderMoveToNextAttribute( xmlReader_ );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::next() 
{
	bool result = false;

	int res = 
		xmlTextReaderNext( xmlReader_ );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::nextSibling() 
{
	bool result = false;

	int res = 
		xmlTextReaderNextSibling( xmlReader_ );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

XMLNodeType XMLTextReader::getNodeType() const 
{
	XMLNodeType result = ntNone;

	int res = 
		xmlTextReaderNodeType( xmlReader_ );

	if ( res >= 0 ) {
		result = (XMLNodeType) res;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

int XMLTextReader::getQuoteChar() const 
{
	return xmlTextReaderQuoteChar(xmlReader_);
}

bool XMLTextReader::read() 
{
	bool result = false;

	int res = 
		xmlTextReaderRead( xmlReader_ );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::readAttrValue() 
{
	bool result = false;

	int res = 
		xmlTextReaderReadAttributeValue( xmlReader_ );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

String XMLTextReader::readInnerXml() 
{
	String result;

	xmlChar* res = 
		xmlTextReaderReadInnerXml( xmlReader_ );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}

String XMLTextReader::readOuterXml() 
{
	String result;

	xmlChar* res = 
		xmlTextReaderReadOuterXml( xmlReader_ );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}

String XMLTextReader::readString() 
{
	String result;

	xmlChar* res = 
		xmlTextReaderReadString( xmlReader_ );

	if ( NULL != res ) {
		result = (const char*)res;

		XMLUtils::freeXMLStr( res );
	}

	return result;
}

bool XMLTextReader::schemaValidate( const String& xsd ) 
{
	bool result = false;

	int res = 
		xmlTextReaderSchemaValidate( xmlReader_, xsd.ansi_c_str() );

	if ( res == 1 ) {
		result = true;
	}
	else if ( res < 0 ) {
		//throw exception???
	}

	return result;
}

bool XMLTextReader::isEOF() const {
	return getState() & psEOF ? true : false;
}

int XMLTextReader::getState() const {
	return xmlTextReaderReadState( xmlReader_ );
}

XmlNode XMLTextReader::getCurrentNode() 
{
	XmlNode result( xmlTextReaderCurrentNode(xmlReader_) );
	result.detach();

	return result;
}


void XMLTextReader::setXML( const String& xml ) 
{
	if ( NULL != xmlInputBuf_ ) {
		xmlInputBuf_ = NULL;
		
		checkBuffers();	
		
		xmlTextReaderSetup(xmlReader_, xmlInputBuf_, NULL, NULL, XML_PARSE_RECOVER );
	}
	add( xml );
}

void XMLTextReader::add( const String& xml ) 
{
	AnsiString str = xml;

	XMLTextReader::add( (const unsigned char*)str.c_str(), str.size() );
}

void XMLTextReader::add( const unsigned char* xmlBuffer, size_t length ) 
{
	checkBuffers();		

	int res = xmlBufferAdd( xmlBuf_, (const xmlChar*)xmlBuffer, length );

	if ( res < 0 ) {
		//throw exception??
	}
}		

void XMLTextReader::checkBuffers() {
	if ( NULL != xmlInputBuf_ ) {
		return;
	}

	xmlInputBuf_ = xmlAllocParserInputBuffer( XML_CHAR_ENCODING_NONE );
	xmlBuf_ = xmlInputBuf_->buffer;
}

void XMLTextReader::createXMLReader()
{
	if ( xmlReader_ != NULL ) {
		return;
	}

	xmlInputBuf_ = NULL;
	xmlBuf_ = NULL;
	
	checkBuffers();

	xmlReader_ = xmlNewTextReader( xmlInputBuf_, NULL );			
	

	xmlSetStructuredErrorFunc( this, XMLTextReader::xmlStructuredErrorFunc );

	VCF_ASSERT( xmlReader_ != NULL );
}

void XMLTextReader::xmlStructuredErrorFunc(void * userData,  xmlErrorPtr error)
{
	XMLTextReader* thisPtr = (XMLTextReader*)userData;

	if ( NULL != thisPtr ) {

		XMLReaderError err;
		if ( NULL != error ) {
			err.code = error->code;
			err.ctx = thisPtr;
			err.domain = error->domain;
			
			if ( NULL != error->file ) {
				err.filename = error->file;
			}
			
			err.int1 = error->int1;
			err.int2 = error->int2;
			if ( NULL != error->str1 ) {
				err.str1 = error->str1;
			}
			
			if ( NULL != error->str2 ) {
				err.str2 = error->str2;
			}
			
			if ( NULL != error->str3 ) {
				err.str3 = error->str3;
			}
			
			err.level = error->level;
			err.line = error->line;
			
			if ( NULL != error->message ) {
				err.message = error->message;
			}
			
			printf( "error: %s \n", error->message );

			err.node = error->node;
		}

		thisPtr->Error( err );
	}
}











