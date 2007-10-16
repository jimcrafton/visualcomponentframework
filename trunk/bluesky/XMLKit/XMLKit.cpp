////XMLKit.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>



#pragma comment ( lib, "ws2_32.lib" )



namespace VCF {
	class XMLKit {
	public:
		static void init( int argc, char **argv ) 
		{
			xmlInitParser();
		}

		static void terminate()
		{
			xmlCleanupParser();
    
#ifdef _DEBUG
			xmlMemoryDump();
#endif
		}
	};

	
	class XMLUtils {
	public:
		
		static void freeXMLStr( xmlChar* str )
		{
			xmlFreeFunc freeFunc;
			xmlMallocFunc f1;			
			xmlReallocFunc f3;
			xmlStrdupFunc f4;
			xmlMemGet( &freeFunc, &f1, &f3, &f4 );
			
			freeFunc( str );
		}
	};



	typedef Delegate3<const xmlChar*,const xmlChar*,const xmlChar*> InternalSubsetDelegate;
	typedef Delegate5<const xmlChar*,int,const xmlChar*,const xmlChar*,xmlChar*> EntityDeclDelegate;
	typedef Delegate3<const xmlChar*,const xmlChar*,const xmlChar*> NotationDeclDelegate;
	typedef Delegate6<const xmlChar*, 
					 const xmlChar*, 
					 int, 
					 int, 
					 const xmlChar*, 
					 xmlEnumerationPtr>	AttributeDeclDelegate;

	typedef Delegate3<const xmlChar*,int,xmlElementContentPtr> ElementDeclDelegate;
	typedef Delegate4<const xmlChar *, 
					 const xmlChar *, 
					 const xmlChar *, 
					 const xmlChar *> UnparsedEntityDeclDelegate;

	typedef Delegate2<const xmlChar*,const xmlChar**> StartElementDelegate;
	typedef Delegate1<const xmlChar*> EndElementDelegate;
	typedef Delegate1<const xmlChar*> ReferenceDelegate;
	typedef Delegate2<const xmlChar *,int> CharactersDelegate;
	typedef Delegate2<const xmlChar *,int> IgnorableWhitespaceDelegate;
	typedef Delegate2<const xmlChar *,const xmlChar *> ProcessingInstructionDelegate;
	typedef Delegate1<const xmlChar*> CommentDelegate;
	typedef Delegate1<const char *> WarningDelegate;
	typedef Delegate1<const char *> ErrorDelegate;
	typedef Delegate1<const char *> FatalErrorDelegate;
	typedef Delegate2<const xmlChar*,int> CDATABlockDelegate;
	typedef Delegate3<const xmlChar*,const xmlChar*,const xmlChar*> ExternalSubsetDelegate;
	typedef Delegate8<const xmlChar*, 
					 const xmlChar*, 
					 const xmlChar*, 
					 int, 
					 const xmlChar**, 
					 int, 
					 int, 
					 const xmlChar**> StartElementNsDelegate;

	typedef Delegate3<const xmlChar*, const xmlChar*, const xmlChar*> EndElementNsDelegate;
	
	
	


	class XMLSaxParser {
	public:
		InternalSubsetDelegate InternalSubset;
		EntityDeclDelegate EntityDecl;
		NotationDeclDelegate NotationDecl;
		AttributeDeclDelegate AttributeDecl;
		ElementDeclDelegate ElementDecl;
		UnparsedEntityDeclDelegate UnparsedEntityDecl;
		Delegate0 StartDocument;
		Delegate0 EndDocument;
		StartElementDelegate StartElement;
		EndElementDelegate EndElement;
		ReferenceDelegate Reference;
		CharactersDelegate Characters;
		IgnorableWhitespaceDelegate IgnorableWhitespace;
		ProcessingInstructionDelegate ProcessingInstruction;
		CommentDelegate Comment;
		WarningDelegate Warning;
		ErrorDelegate Error;
		FatalErrorDelegate FatalError;
		CDATABlockDelegate CDATABlock;
		ExternalSubsetDelegate ExternalSubset;
		StartElementNsDelegate StartElementNs;
		EndElementNsDelegate EndElementNs;


		XMLSaxParser(): parser_(NULL)
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

		~XMLSaxParser() 
		{
			xmlFreeParserCtxt( parser_ );
		}


		void parse( const String& xml ) 
		{
			AnsiString tmp = xml;

			xmlParseChunk( parser_, tmp.c_str(), tmp.size(), 1 );
		}


		void parseChunk( const String& xmlChunk, bool finished=false ) 
		{
			AnsiString tmp = xmlChunk;

			xmlParseChunk( parser_, tmp.c_str(), tmp.size(), finished ? 1 : 0 );
		}

		void finishParsing()
		{
			parseChunk( "", true );
		}

	protected:
		xmlSAXHandler saxHandler_;
		xmlParserCtxtPtr parser_;

		static void	internalSubsetSAXFunc(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar * ExternalID, 
					 const xmlChar * SystemID) 
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->InternalSubset(name,ExternalID,SystemID);
			}
		}

		static void	entityDeclSAXFunc(void * ctx, 
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

		static void notationDeclSAXFunc(void * ctx, const xmlChar * name, 
										const xmlChar * publicId, const xmlChar * systemId)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->NotationDecl(name,publicId,systemId);
			}
		}

		static void	attributeDeclSAXFunc(void * ctx, 
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

		static void	elementDeclSAXFunc(void * ctx, 
					 const xmlChar * name, 
					 int type, 
					 xmlElementContentPtr content)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->ElementDecl(name,type,content);
			}
		}

		static void	unparsedEntityDeclSAXFunc(void * ctx, 
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

		static void	startDocumentSAXFunc(void * ctx)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->StartDocument();
			}			
		}

		static void	endDocumentSAXFunc(void * ctx)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->EndDocument();
			}	
		}

		static void	startElementSAXFunc		(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar ** atts)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->StartElement(name,atts);
			}	
		}

		static void	endElementSAXFunc(void * ctx, 
					 const xmlChar * name)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->EndElement(name);
			}	
		}

		static void	referenceSAXFunc(void * ctx, 
					 const xmlChar * name)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->Reference(name);
			}
		}

		static void	charactersSAXFunc(void * ctx, 
					 const xmlChar * ch, 
					 int len)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->Characters(ch,len);
			}
		}

		static void ignorableWhitespaceSAXFunc(void * ctx, 
					 const xmlChar * ch, 
					 int len)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->IgnorableWhitespace(ch,len);
			}
		}

		static void	processingInstructionSAXFunc(void * ctx, 
					 const xmlChar * target, 
					 const xmlChar * data)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->ProcessingInstruction(target,data);
			}
		}

		static void	commentSAXFunc(void * ctx, 
					 const xmlChar * value)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->Comment(value);
			}
		}

		static void	warningSAXFunc(void * ctx, const char * msg, ...)
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

		static void	errorSAXFunc(void * ctx, const char * msg, ...)
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


		static void	fatalErrorSAXFunc(void * ctx, const char * msg, ...)
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

		static void cdataBlockSAXFunc(void * ctx,  const xmlChar * value, int len)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->CDATABlock(value,len);
			}			
		}

		static void	externalSubsetSAXFunc	(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar * ExternalID, 
					 const xmlChar * SystemID)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->ExternalSubset(name,ExternalID,SystemID);
			}
		}

		static void	startElementNsSAX2Func(void * ctx, 
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

		static void endElementNsSAX2Func(void * ctx, 
					 const xmlChar * localname, 
					 const xmlChar * prefix, 
					 const xmlChar * URI)
		{
			XMLSaxParser* thisPtr = (XMLSaxParser*)ctx;
			if ( NULL != thisPtr ) {
				thisPtr->EndElementNs(localname,prefix,URI);
			}			
		}

	};




	enum XMLNodeType {
		ntNone = 0,
		ntElement = 1,
		ntAttribute = 2,
		ntText = 3,
		ntCDATA = 4,
		ntEntityReference = 5,
		ntEntity = 6,
		ntProcessingInstruction = 7,
		ntComment = 8,
		ntDocument = 9,
		ntDocumentType = 10,
		ntDocumentFragment = 11,
		ntNotation = 12,
		ntWhitespace = 13,
		ntSignificantWhitespace = 14,			
		ntEndElement = 15,
		ntEndEntity = 16,
		ntXmlDeclaration = 17
	};


	class XMLTextReader;

	class XMLReaderError {
	public:

		XMLReaderError():domain(0),code(0),level(0),line(-1),int1(0),int2(0),ctx(NULL),node(NULL){}

		int	domain;
		int	code;
		String message;
		int	level;
		String filename;
		int	line;
		String str1;
		String str2;
		String str3;
		int	int1;
		int	int2;
		XMLTextReader* ctx;
		void *	node;


		bool empty() const {
			return domain == 0 &&
					code == 0 &&
					level == 0 && 
					line == -1 &&
					int1 == 0 &&
					int2 == 0 &&
					ctx == NULL &&
					node == NULL &&
					message.empty() &&
					filename.empty() &&
					str1.empty() &&
					str2.empty() &&
					str3.empty();
		}
	};




	

	template <typename Type, typename Impl>
	class Attachable {
	public:
		Attachable():owned_(false), resource_(NULL) {}

		Attachable( Type val ):owned_(false), resource_(val) {}

		Attachable( const Attachable<Type,Impl>& val ):owned_(false), resource_(val.resource_) {}


		~Attachable()	{
			if ( owned_ ) {
				VCF_ASSERT( NULL != resource_ );
				if ( resource_ ) {
					Impl::freeResource(resource_);
				}
			}
		}


		Type detach() {
			xmlNodePtr result = resource_;
			owned_ = false;
			return result;
		}

		void attach(Type val) {
			owned_ = true;
			resource_ = val;
		}

		Type get() const {
			return resource_;
		}

		void assign( Type rhs ) {
			if ( owned_ ) {
				if ( resource_ ) {
					Impl::freeResource(resource_);
				}
			}

			resource_ = rhs;
			owned_ = false;
		}

		bool isNull() const {
			return (NULL == resource_) ? true : false;
		}
	protected:
		bool owned_;
		Type resource_;

	};


	class XmlDocument;

	class XmlNamespace : public Attachable<xmlNsPtr,XmlNamespace> {
	public:
		typedef Attachable<xmlNsPtr,XmlNamespace> BaseT;

		XmlNamespace():BaseT()
		{

		}

		XmlNamespace( xmlNsPtr val ):BaseT(val)
		{
			
		}

		XmlNamespace( const XmlNamespace& val ):BaseT(val)
		{
			
		}

		XmlNamespace& operator=( xmlNsPtr rhs )
		{
			assign(rhs);
			return *this;
		}

		static void freeResource(xmlNsPtr res)
		{
			xmlFreeNs( res );
		}
	protected:
		
		
	};

	class XmlNode : public Attachable<xmlNodePtr,XmlNode> {
	public:

		enum PreservesSpace {
			psDefault = 0,
			psPreserves = 1,
			psNotInherited = -1
		};

		typedef Attachable<xmlNodePtr,XmlNode> BaseT;

		XmlNode():BaseT()
		{

		}

		XmlNode( xmlNodePtr val ):BaseT(val)
		{
			
		}

		XmlNode( const XmlNode& val ):BaseT(val)
		{
			
		}

		XmlNode& operator=( xmlNodePtr rhs )
		{
			assign(rhs);
			return *this;
		}

		static void freeResource(xmlNodePtr res)
		{
			xmlUnlinkNode( res );
			xmlFreeNode( res );
		}

		bool getChildren( std::vector<XmlNode>& nodes ) const 
		{
			xmlNode *child = resource_->children;
			while ( NULL != child ) {			
				nodes.push_back( XmlNode(child) );
				child = child->next;
			}

			return !nodes.empty();
		}

		XmlNode getParent() const
		{
			return XmlNode(resource_->parent);
		}

		XMLNodeType getType() const 
		{
			return (XMLNodeType) resource_->type;
		}


		String getPath() const {
			String result;

			xmlChar* res = 
				xmlGetNodePath( resource_ );

			if ( NULL != res ) {
				result = (const char*)res;

				XMLUtils::freeXMLStr( res );
			}

			return result;
		}


		XmlNode copy( bool deep ) const {
			return XmlNode( xmlCopyNode( resource_, deep ? 1 : 2 ) );
		}


		XmlNode copyList() const {
			return XmlNode( xmlCopyNodeList( resource_ ) );
		}

		String getAttribute( const String& name ) const 
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

		void setNamespaceAttr( const XmlNamespace& ns, const String& name, const String& value )
		{
			AnsiString n = name;
			AnsiString v = value;

			xmlSetNsProp( resource_, ns.get(), (const xmlChar*)n.c_str(), (const xmlChar*)v.c_str() );
		}

		void setAttribute( const String& name, const String& value )
		{
			AnsiString n = name;
			AnsiString v = value;

			xmlSetProp( resource_, (const xmlChar*)n.c_str(), (const xmlChar*)v.c_str() );
		}

		bool empty() const {
			return xmlIsBlankNode( resource_ ) == 1 ? true : false;
		}


		String getContent() const 
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

		String getLang() const 
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

		String getBase() const 
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

		void setBase( const String& val ) 
		{
			xmlNodeSetBase( resource_, (const xmlChar*)val.ansi_c_str() );
		}

		PreservesSpace getPreservesSpace() const 
		{
			return (PreservesSpace) xmlNodeGetSpacePreserve( resource_ );
		}

		bool isText() const 
		{
			return xmlNodeIsText( resource_ ) == 1 ? true : false;
		}

		int getLineNumber() const 
		{
			return xmlGetLineNo( resource_ );
		}

		void setBaseURI( const String& val ) 
		{
			xmlNodeSetBase( resource_, (const xmlChar*) val.ansi_c_str() );
		}

		void setContent( const String& val ) 
		{
			xmlNodeSetContent( resource_, (const xmlChar*) val.ansi_c_str() );
		}

		void setLang( const String& val ) 
		{
			xmlNodeSetLang( resource_, (const xmlChar*) val.ansi_c_str() );
		}

		void setName( const String& val ) 
		{
			xmlNodeSetName( resource_, (const xmlChar*) val.ansi_c_str() );
		}

		String getName() const 
		{
			String result = (const char*)resource_->name;

			return result;
		}

		int reconcileNamespaces() const 
		{
			return xmlReconciliateNs( resource_->doc, resource_ );
		}

		XmlDocument getDocument() const ;

		void setDocument ( const XmlDocument& );

		bool getNamespaceList( std::vector<XmlNamespace>& namespaces )
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

		void setNamespace( const XmlNamespace& ns )
		{
			xmlSetNs( resource_, ns.get() );
		}

		XmlNamespace searchNamespace( const String& ns ) 
		{
			return XmlNamespace( 
						xmlSearchNs( resource_->doc, resource_, (const xmlChar*)ns.ansi_c_str() ) 
						);
		}

		XmlNamespace searchNamespaceByHRef( const String& href ) 
		{
			return XmlNamespace( 
						xmlSearchNsByHref( resource_->doc, resource_, (const xmlChar*)href.ansi_c_str() ) 
						);
		}

		XmlNode* copy( const XmlDocument& doc, bool extended ); 

		
		void addChild( XmlNode& child ) 
		{
			if ( !child.isNull() ) {
				xmlAddChild( resource_, child.detach() );
			}
		}

		void addNextSibling( XmlNode& element ) 
		{
			if ( !element.isNull() ) {
				xmlAddNextSibling( resource_, element.detach() );
			}
		}

		void addPrevSibling( XmlNode& element ) 
		{
			if ( !element.isNull() ) {
				xmlAddPrevSibling( resource_, element.detach() );
			}
		}

		void addSibling( XmlNode& element ) 
		{
			if ( !element.isNull() ) {
				xmlAddSibling( resource_, element.detach() );
			}
		}
	};



	class XmlDocument : public Attachable<xmlDocPtr,XmlDocument> {
	public:
		typedef Attachable<xmlDocPtr,XmlDocument> BaseT;

		XmlDocument():BaseT()
		{

		}

		XmlDocument( xmlDocPtr val ):BaseT(val)
		{
			
		}

		XmlDocument( const XmlDocument& val ):BaseT(val)
		{
			
		}

		XmlDocument& operator=( xmlDocPtr rhs )
		{
			assign(rhs);
			return *this;
		}

		static void freeResource(xmlDocPtr res)
		{
			xmlFreeDoc( res );
		}
		
		XmlNode getRoot() const 
		{
			return XmlNode( xmlDocGetRootElement( resource_ ) );
		}



		XmlDocument* copy( bool recursive ) const {
			XmlDocument* result = NULL;

			xmlDocPtr res = xmlCopyDoc( resource_, recursive ? 1 : 0 );

			if ( NULL != res ) {
				result = new XmlDocument();
				result->attach(res);
			}

			return result;
		}


		XmlNode* newCDATABlock( const String& data ) {
			XmlNode* result = NULL;

			AnsiString tmp = data;
			xmlNodePtr res = xmlNewCDataBlock( resource_, (const xmlChar*)tmp.c_str(), tmp.size() );
			if ( NULL != res ) {
				result = new XmlNode();
				result->attach( res );
			}	

			return result;
		}

		XmlNode* newCharRef( const String& name ) {
			XmlNode* result = NULL;

			AnsiString tmp = name;
			xmlNodePtr res = xmlNewCharRef( resource_, (const xmlChar*)tmp.c_str() );
			if ( NULL != res ) {
				result = new XmlNode();
				result->attach( res );
			}	

			return result;
		}

		XmlNode* newComment( const String& comment ) {
			XmlNode* result = NULL;

			AnsiString tmp = comment;
			xmlNodePtr res = xmlNewDocComment( resource_, (const xmlChar*)tmp.c_str() );
			if ( NULL != res ) {
				result = new XmlNode();
				result->attach( res );
			}	

			return result;
		}

		XmlNode* newFragment() {
			XmlNode* result = NULL;
			xmlNodePtr res = xmlNewDocFragment( resource_ );
			if ( NULL != res ) {
				result = new XmlNode();
				result->attach( res );
			}	

			return result;
		}

		XmlNode* newNode( const XmlNamespace& ns, const String& name, const String& content ) {
			
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

		XmlNode* newNode( const String& name, const String& content ) {
			return newNode(XmlNamespace(), name, content);
		}

		XmlNode* newRawNode( const XmlNamespace& ns, const String& name, const String& content ) {
			
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

		XmlNode* newRawNode( const String& name, const String& content ) {
			return newRawNode(XmlNamespace(), name, content);
		}

		XmlNode* newProcessingInstruction( const String& name, const String& content ) {
			XmlNode* result = NULL;
			xmlNodePtr res = xmlNewDocPI( resource_,(const xmlChar*)name.ansi_c_str(),
											(const xmlChar*)content.ansi_c_str() );
			if ( NULL != res ) {
				result = new XmlNode();
				result->attach( res );
			}
		}

		static XmlDocument* newDocument() 
		{
			XmlDocument* result = NULL;

			xmlDocPtr res = xmlNewDoc( (const xmlChar*)"1.0" );
			if ( NULL != res ) {
				result = new XmlDocument();
				result->attach( res );
			}
			
			return result;
		}
	};




	typedef Delegate1<const XMLReaderError&> XMLReaderErrorDelegate;

	class XMLTextReader {
	public:

		enum ParseringFlags {
			pfLoadDTD = 0x01,
			pfDefaultAttrs = 0x02,
			pfValidate = 0x04,
			pfSubstEntities = 0x08,
		};

		enum ParserState {
				psInitial = XML_TEXTREADER_MODE_INITIAL,
				psInteractive = XML_TEXTREADER_MODE_INTERACTIVE,
				psError = XML_TEXTREADER_MODE_ERROR,
				psEOF = XML_TEXTREADER_MODE_EOF,
				psClosed = XML_TEXTREADER_MODE_CLOSED,
				psReading = XML_TEXTREADER_MODE_READING
		};

		XMLReaderErrorDelegate Error;
		

		XMLTextReader():
			xmlReader_(NULL)
		{
			createXMLReader();
		}

		~XMLTextReader()
		{
			if ( NULL != xmlReader_ ) {
				xmlFreeTextReader( xmlReader_ );
				xmlSetStructuredErrorFunc( NULL, NULL );
			}
		}


		size_t getAttributeCount() const 
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

		String getBaseURI() const 
		{
			String result;
			VCF_ASSERT( NULL != xmlReader_ );

			const xmlChar* uri = xmlTextReaderConstBaseUri( xmlReader_ );
			if ( NULL != uri ) {
				result = (const char*)uri;
			}

			return result;
		}

		int getBytesConsumed() const 
		{
			int result = -1;

			result = xmlTextReaderByteConsumed( xmlReader_ );

			return result;
		}

		bool close() 
		{
			return xmlTextReaderClose( xmlReader_ ) < 0 ? false : true;
		}

		String getEncoding() const 
		{
			String result;
			const xmlChar* enc = xmlTextReaderConstEncoding( xmlReader_ );
			if ( NULL != enc ) {
				result = (const char*) enc;
			}
			return result;
		}

		String getLocalName() const 
		{
			String result;
			const xmlChar* val = xmlTextReaderConstLocalName( xmlReader_ );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}

		String getName() const 
		{
			String result;
			const xmlChar* val = xmlTextReaderConstName( xmlReader_ );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}
		
		String getNamespaceURI() const 
		{
			String result;
			const xmlChar* val = xmlTextReaderConstNamespaceUri( xmlReader_ );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}

		String getPrefix() const 
		{
			String result;
			const xmlChar* val = xmlTextReaderConstPrefix( xmlReader_ );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}

		String getTextValue() const 
		{
			String result;
			const xmlChar* val = xmlTextReaderConstValue( xmlReader_ );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}

		String getLang() const 
		{
			String result;
			const xmlChar* val = xmlTextReaderConstXmlLang( xmlReader_ );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}

		String getVersion() const 
		{
			String result;
			const xmlChar* val = xmlTextReaderConstXmlVersion( xmlReader_ );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}

		int getCurrentDepth() const 
		{
			int result = -1;

			result = xmlTextReaderDepth( xmlReader_ );

			return result;
		}

		XmlNode expand() 
		{			
			xmlNodePtr nodePtr = xmlTextReaderExpand( xmlReader_ );

			XmlNode result( nodePtr );
			result.detach();

			return result;
		}

		String getAttribute( const String& name ) const 
		{

			String result;
			const xmlChar* val = xmlTextReaderGetAttribute( xmlReader_, (const xmlChar*) name.ansi_c_str() );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}
		
		String getAttribute( const size_t& index ) const 
		{

			String result;
			const xmlChar* val = xmlTextReaderGetAttributeNo( xmlReader_, index );
			if ( NULL != val ) {
				result = (const char*) val;
			}
			return result;
		}
		
		String getAttribute( const String& localName, const String& namespaceURI ) const 
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


		int getCurrentParserColumn() const 
		{
			return xmlTextReaderGetParserColumnNumber( xmlReader_ );
		}

		int getCurrentParserLine() const 
		{
			return xmlTextReaderGetParserLineNumber( xmlReader_ );
		}

		bool parserLoadsDTD() const 
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

		bool parserUsingDefaultAttrs() const 
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

		bool parserWillValidate() const 
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

		bool parserWillSubstituteEntities() const 
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

		void setParserLoadsDTD( bool val ) 
		{
			int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_LOADDTD, val ? 1 : 0 );			
			if ( res < 0 ) {
				//throw exception???
			}
		}

		void setParserDefaultAttrs( bool val ) 
		{
			int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_DEFAULTATTRS, val ? 1 : 0 );			
			if ( res < 0 ) {
				//throw exception???
			}
		}

		void setParserWillValidate( bool val ) 
		{
			int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_VALIDATE, val ? 1 : 0 );			
			if ( res < 0 ) {
				//throw exception???
			}
		}

		void setParserWillSubstituteEntities( bool val ) 
		{			
			int res = xmlTextReaderSetParserProp( xmlReader_, XML_PARSER_SUBST_ENTITIES, val ? 1 : 0 );			
			if ( res < 0 ) {
				//throw exception???
			}
		}


		bool hasAttributes() const 
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

		bool hasValue() const 
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

		bool isDefaultValue() const 
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

		bool isEmptyElement() const 
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

		bool isNamespace() const 
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

		bool isParserValid() const 
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

		String lookupNamespace( const String& prefix ) const 
		{
			String result;
			xmlChar* res = xmlTextReaderLookupNamespace( xmlReader_, (const xmlChar*) prefix.ansi_c_str() );	
			
			if ( NULL != res ) {

				result = (const char*)res;

				XMLUtils::freeXMLStr(res);
			}

			return result;
		}
			
		bool moveToAttribute( const String& attributeName ) 
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

		bool moveToAttribute( size_t index ) 
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

		bool moveToAttribute( const String& localAttrName, const String& namespaceURI ) 
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

		bool moveToElement() 
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

		bool moveToFirstAttribute() 
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

		bool moveToNextAttribute() 
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

		bool next() 
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

		bool nextSibling() 
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

		XMLNodeType getNodeType() const 
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

		int getQuoteChar() const 
		{
			return xmlTextReaderQuoteChar(xmlReader_);
		}

		bool read() 
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

		bool readAttrValue() 
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

		String readInnerXml() 
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

		String readOuterXml() 
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

		String readString() 
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

		bool schemaValidate( const String& xsd ) 
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

		bool isEOF() const {
			return getState() & psEOF ? true : false;
		}

		int getState() const {
			return xmlTextReaderReadState( xmlReader_ );
		}

		XmlNode getCurrentNode() 
		{
			XmlNode result( xmlTextReaderCurrentNode(xmlReader_) );
			result.detach();

			return result;
		}


		void setXML( const String& xml ) {
			if ( NULL != xmlInputBuf_ ) {
				xmlFreeParserInputBuffer(xmlInputBuf_);
				xmlInputBuf_ = NULL;
				
				checkBuffers();	

				xmlTextReaderSetup(xmlReader_, xmlInputBuf_, NULL, NULL, XML_PARSE_RECOVER );
			}

			//xmlTextReaderSetup
			add( xml );
		}

		void add( const String& xml ) {
			AnsiString str = xml;

			add( (const unsigned char*)str.c_str(), str.size() );
		}

		void add( const unsigned char* xmlBuffer, size_t length ) {
			checkBuffers();		

			int res = xmlBufferAdd( xmlBuf_, (const xmlChar*)xmlBuffer, length );

			if ( res < 0 ) {
				//throw exception??
			}
		}
	protected:
		xmlTextReaderPtr xmlReader_;
		xmlBufferPtr xmlBuf_;
		xmlParserInputBufferPtr xmlInputBuf_;

		

		void checkBuffers() {
			if ( NULL != xmlInputBuf_ ) {
				return;
			}

			xmlInputBuf_ = xmlAllocParserInputBuffer( XML_CHAR_ENCODING_NONE );
			xmlBuf_ = xmlInputBuf_->buffer;
		}

		void createXMLReader()
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

		static void	xmlStructuredErrorFunc(void * userData,  xmlErrorPtr error)
		{
			XMLTextReader* thisPtr = (XMLTextReader*)userData;

			if ( NULL != thisPtr ) {

				XMLReaderError err;
				if ( NULL != error ) {
					err.code = error->code;
					err.ctx = thisPtr;
					err.domain = error->domain;
					err.filename = error->file;
					err.int1 = error->int1;
					err.int2 = error->int2;
					err.str1 = error->str1;
					err.str2 = error->str2;
					err.str3 = error->str3;
					err.level = error->level;
					err.line = error->line;
					err.message = error->message;
					
					printf( "error: %s \n", error->message );

					err.node = error->node;
				}

				thisPtr->Error( err );
			}
		}
	};








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
};


#define testxml			"<stuff a=\"1\" b=\"23\">Wow!<animal>Zebra</animal><animal>Cow</animal></stuff>"

using namespace VCF;

void	MystartElementSAXFunc		(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar ** atts)
{
	printf( "name: %s\n", (const char*) name );
}


void MystartElementSAXFunc2( const xmlChar * name, 
					 const xmlChar ** atts)
{
	printf( "@MystartElementSAXFunc2 name: %s\n", (const char*) name );
	
	if ( NULL != atts ) {
		const xmlChar** tmp = atts;
		while ( *tmp != 0 ) {
			printf( "attr: %s\n", (const char*)*tmp );
			tmp ++;
		}
	}
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );	
	XMLKit::init( argc, argv );

	{
		
		XMLSaxParser p;
		p.StartElement += MystartElementSAXFunc2;
		
		p.parse( testxml );
		

		xmlBuffer buf = {0};
		xmlParserInputBuffer xib = {0};
		xib.buffer = &buf;


		xmlTextReaderPtr tr = xmlNewTextReader( &xib, NULL );


		int res = xmlReaderNewMemory( tr, testxml, strlen(testxml), NULL, NULL, XML_PARSE_RECOVER );

		res = xmlTextReaderRead(tr);

		xmlFreeTextReader( tr );

		
		XMLTextReader rdr;
		rdr.setXML( testxml );

		System::println( "lang: " + rdr.getLang() );
		System::println( "uri: " + rdr.getBaseURI() );
		System::println( "ns: " + rdr.getNamespaceURI() );
	

		while ( rdr.read() ) {			
			System::println( "Name: " + rdr.getName() + " depth: " + rdr.getCurrentDepth() );

				

			System::println( "Inner XML: { " + rdr.readInnerXml() + " }" );
		}
	}

	XMLKit::terminate();
	FoundationKit::terminate();
	return 0;
}


