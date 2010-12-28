#ifndef _VCF_XMLKIT_H__
#define _VCF_XMLKIT_H__

//XMLKit.h

/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




/**
Handle the extension based on the compiler
*/
# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1500)
#     define _LIB_CPLVERNUM "vc90"	
#   elif (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80"
#   elif (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
#  ifdef VCF_BCC
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif



//auto link stuff
#if defined(VCF_MSC) || defined(VCF_BCC)
	#ifdef USE_XMLKIT_DLL
		#define XMLKIT_DLL
		// using dynamic link library
		#ifdef _DEBUG
			#pragma comment(lib, "XMLKit_"_LIB_CPLVERNUM"_d.lib")
		#else
			#pragma comment(lib, "XMLKit_"_LIB_CPLVERNUM".lib")
		#endif
	#elif defined USE_XMLKIT_LIB
		// using statically linked library
	#	ifdef	VCF_STATIC_CRT
	#		ifdef _DEBUG
	#			pragma comment(lib, "XMLKit_"_LIB_CPLVERNUM"_scrtd.lib")
	#		else
	#			pragma comment(lib, "XMLKit_"_LIB_CPLVERNUM"_scrt.lib")
	#		endif
	#	else
	#		ifdef _DEBUG
	#			pragma comment(lib, "XMLKit_"_LIB_CPLVERNUM"_sd.lib")
	#		else
	#			pragma comment(lib, "XMLKit_"_LIB_CPLVERNUM"_s.lib")
	#		endif
	#	endif	
	#endif
#endif //VCF_MSC



//export crap
#ifdef XMLKIT_DLL
	#if defined(XMLKIT_EXPORTS)
		#define XMLKIT_API __declspec(dllexport)
	#else
		#define XMLKIT_API __declspec(dllimport)
	#endif
#else
	#define XMLKIT_API
#endif //XMLKIT_DLL



#include "vcf/FoundationKit/FoundationKit.h"

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <libxslt/xsltInternals.h>



namespace VCF {
	class XMLKIT_API XMLKit {
	public:
		static void init( int argc, char **argv );

		static void terminate();

		static String getXMLVersion();
		static String getXSLTVersion();
	};

	
	class XMLKIT_API XMLUtils {
	public:
		
		static void freeXMLStr( xmlChar* str );
	};


	namespace XMLText {

		enum EncodingType {
			etError = XML_CHAR_ENCODING_ERROR,
			etNone = XML_CHAR_ENCODING_NONE,
			etUTF8 = XML_CHAR_ENCODING_UTF8,
			etUTF16LE = XML_CHAR_ENCODING_UTF16LE,
			etUTF16BE = XML_CHAR_ENCODING_UTF16BE,
			etUCS4LE = XML_CHAR_ENCODING_UCS4LE,
			etUCS4BE = XML_CHAR_ENCODING_UCS4BE,
			etEBCDIC = XML_CHAR_ENCODING_EBCDIC,
			etUCS4_2143 = XML_CHAR_ENCODING_UCS4_2143,
			etUCS4_3412 = XML_CHAR_ENCODING_UCS4_3412,
			etUCS2 = XML_CHAR_ENCODING_UCS2,
			etISOLatin1 = XML_CHAR_ENCODING_8859_1,
			etISO8859_1 = XML_CHAR_ENCODING_8859_1,
			etISOLatin2 = XML_CHAR_ENCODING_8859_2,
			etISO8859_2 = XML_CHAR_ENCODING_8859_2,
			etISO8859_3 = XML_CHAR_ENCODING_8859_3,
			etISO8859_4 = XML_CHAR_ENCODING_8859_4,
			etISO8859_5 = XML_CHAR_ENCODING_8859_5,
			etISO8859_6 = XML_CHAR_ENCODING_8859_6,
			etISO8859_7 = XML_CHAR_ENCODING_8859_7,
			etISO8859_8 = XML_CHAR_ENCODING_8859_8,
			etISO8859_9 = XML_CHAR_ENCODING_8859_9,
			etISO2022_JP = XML_CHAR_ENCODING_2022_JP,
			etShiftJIS = XML_CHAR_ENCODING_SHIFT_JIS,
			etEUC_JP = XML_CHAR_ENCODING_EUC_JP,
			etAscii = XML_CHAR_ENCODING_ASCII,
		};
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
	
	
	


	class XMLKIT_API XMLSaxParser {
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


		XMLSaxParser();

		~XMLSaxParser();


		void parse( const String& xml );

		void parseChunk( const String& xmlChunk, bool finished=false );

		void parseChunk( const uchar* xmlChunk, size_t chunkSize, bool finished=false );

		void finishParsing();

		xmlParserCtxtPtr internal_getParser() {
			return parser_;
		}
	protected:
		xmlSAXHandler saxHandler_;
		xmlParserCtxtPtr parser_;

		static void	internalSubsetSAXFunc(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar * ExternalID, 
					 const xmlChar * SystemID);

		static void	entityDeclSAXFunc(void * ctx, 
					 const xmlChar * name, 
					 int type, 
					 const xmlChar * publicId, 
					 const xmlChar * systemId, 
					 xmlChar * content);

		static void notationDeclSAXFunc(void * ctx, const xmlChar * name, 
										const xmlChar * publicId, const xmlChar * systemId);

		static void	attributeDeclSAXFunc(void * ctx, 
					 const xmlChar * elem, 
					 const xmlChar * fullname, 
					 int type, 
					 int def, 
					 const xmlChar * defaultValue, 
					 xmlEnumerationPtr tree);

		static void	elementDeclSAXFunc(void * ctx, 
					 const xmlChar * name, 
					 int type, 
					 xmlElementContentPtr content);

		static void	unparsedEntityDeclSAXFunc(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar * publicId, 
					 const xmlChar * systemId, 
					 const xmlChar * notationName);

		static void	startDocumentSAXFunc(void * ctx);

		static void	endDocumentSAXFunc(void * ctx);

		static void	startElementSAXFunc		(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar ** atts);

		static void	endElementSAXFunc(void * ctx, 
					 const xmlChar * name);

		static void	referenceSAXFunc(void * ctx, 
					 const xmlChar * name);

		static void	charactersSAXFunc(void * ctx, 
					 const xmlChar * ch, 
					 int len);

		static void ignorableWhitespaceSAXFunc(void * ctx, 
					 const xmlChar * ch, 
					 int len);

		static void	processingInstructionSAXFunc(void * ctx, 
					 const xmlChar * target, 
					 const xmlChar * data);

		static void	commentSAXFunc(void * ctx, 
					 const xmlChar * value);

		static void	warningSAXFunc(void * ctx, const char * msg, ...);

		static void	errorSAXFunc(void * ctx, const char * msg, ...);


		static void	fatalErrorSAXFunc(void * ctx, const char * msg, ...);

		static void cdataBlockSAXFunc(void * ctx,  const xmlChar * value, int len);

		static void	externalSubsetSAXFunc	(void * ctx, 
					 const xmlChar * name, 
					 const xmlChar * ExternalID, 
					 const xmlChar * SystemID);

		static void	startElementNsSAX2Func(void * ctx, 
					 const xmlChar * localname, 
					 const xmlChar * prefix, 
					 const xmlChar * URI, 
					 int nb_namespaces, 
					 const xmlChar ** namespaces, 
					 int nb_attributes, 
					 int nb_defaulted, 
					 const xmlChar ** attributes);

		static void endElementNsSAX2Func(void * ctx, 
					 const xmlChar * localname, 
					 const xmlChar * prefix, 
					 const xmlChar * URI);

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

	class XMLKIT_API XMLError {
	public:

		XMLError():domain(0),code(0),level(0),line(-1),int1(0),int2(0),ctx(NULL),node(NULL){}

		XMLError(xmlErrorPtr err);
		XMLError(xmlErrorPtr err, void* ctxPtr);

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
		void* ctx;
		void*	node;


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

	typedef Delegate1<const XMLError&> XMLErrorDelegate;
	

	class XMLKIT_API XmlException : public BasicException{
	public:
		XmlException();
		XmlException(xmlErrorPtr err);
		virtual ~XmlException() throw() {};
	};

	class XMLKIT_API ValidSchemaParseException : public XmlException {
	public:
		ValidSchemaParseException():XmlException(){}
	};

	class XMLKIT_API SchemaValidationException : public XmlException {
	public:
		SchemaValidationException():XmlException(){}
	};

	

	template <typename Type, typename Impl>
	class Attachable {
	public:
		Attachable():owned_(false), resource_(NULL) {}

		Attachable( Type val ):owned_(false), resource_(val) {}

		Attachable( const Attachable<Type,Impl>& val ):owned_(false), resource_(val.resource_) {}

		typedef Type ValueT;

		~Attachable()	{
			if ( owned_ ) {				
				if ( resource_ ) {
					Impl::freeResource(resource_);
				}
			}
		}


		Type detach() {
			Type result = resource_;
			owned_ = false;
			return result;
		}

		void attach(Type val) {
			if ( resource_ && owned_ ) {
				Impl::freeResource(resource_);
			}
			owned_ = true;
			resource_ = val;
		}

		Type get() const {
			return resource_;
		}

		Type& get() {
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

	class XMLKIT_API XmlNamespace : public Attachable<xmlNsPtr,XmlNamespace> {
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

		static void freeResource(xmlNsPtr res);


		String getPrefix() const {
			return String( (const char*)resource_->prefix );
		}

		String getURI() const {
			return String( (const char*)resource_->href );
		}
	protected:
		
		
	};

	class XMLKIT_API XmlNode : public Attachable<xmlNodePtr,XmlNode>, public Object {
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

		static void freeResource(xmlNodePtr res);

		bool getChildren( std::vector<XmlNode>& nodes ) const ;

		bool hasChildren() const ;

		size_t getChildCount() const ;

		XmlNode getParent() const;

		XmlNode getChild( const String& name ) const;

		XMLNodeType getType() const ;

		String getPath() const ;

		XmlNode copy( bool deep ) const;

		XmlNode copyList() const ;

		String getAttribute( const String& name ) const ;

		void setNamespaceAttr( const XmlNamespace& ns, const String& name, const String& value );

		void setAttribute( const String& name, const String& value );
		void setAttributeAsVariant( const String& name, const VariantData& value );

		bool empty() const;

		String getContent() const ;

		String getLang() const ;

		String getBase() const ;

		void setBase( const String& val ) ;

		PreservesSpace getPreservesSpace() const ;

		bool isText() const ;

		int getLineNumber() const ;

		void setBaseURI( const String& val ) ;

		void setContent( const String& val ) ;

		void setLang( const String& val ) ;

		void setName( const String& val ) ;

		String getName() const ;

		int reconcileNamespaces() const ;

		XmlDocument getDocument() const ;

		void setDocument ( const XmlDocument& );

		bool getNamespaceList( std::vector<XmlNamespace>& namespaces ) const;

		void setNamespace( const XmlNamespace& ns );

		XmlNamespace searchNamespace( const String& ns ) ;

		XmlNamespace searchNamespaceByHRef( const String& href ) ;

		XmlNode* copy( const XmlDocument& doc, bool extended ); 
		
		void addChild( XmlNode& child ) ;

		void addNextSibling( XmlNode& element );

		void addPrevSibling( XmlNode& element );

		void addSibling( XmlNode& element ) ;


		virtual String toString() const ;

		virtual Object* clone( bool deep = false ) const ;
	};



	class XMLKIT_API XmlDocument : public Attachable<xmlDocPtr,XmlDocument>, public Object {
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

		static void freeResource(xmlDocPtr res);


		void setXML( const String& xml );

		void setHTML( const String& html );
		
		XmlNode getRoot() const;

		XmlNode setRoot( const XmlNode& root );

		XmlDocument* copy( bool recursive ) const;

		XmlNode newCDATABlock( const String& data );

		XmlNode newCharRef( const String& name );

		XmlNode newComment( const String& comment );

		XmlNode newFragment();

		XmlNode newNode( const XmlNamespace& ns, const String& name, const String& content="" );

		XmlNode newNode( const String& name, const String& content="" );

		XmlNode newRawNode( const XmlNamespace& ns, const String& name, const String& content );

		XmlNode newRawNode( const String& name, const String& content );

		XmlNode newProcessingInstruction( const String& name, const String& content );

		static XmlDocument* newDocument();

		VariantData matches( const String& xpathQuery, std::vector<XmlNode>& found );

		XmlNode select( const String& xpathQuery );


		void load( const String& fileName );

		void loadHTML( const String& fileName );

		//virtual Object methods:

		
		virtual String toString() const ;

		virtual Object* clone( bool deep = false ) const ;

		void dump();
		
	};



	//	
	class XMLKIT_API XPathExpression : public Attachable<xmlXPathCompExprPtr,XPathExpression> {
	public:
		typedef Attachable<xmlXPathCompExprPtr,XPathExpression> BaseT;

		XPathExpression():BaseT()
		{
			
		}

		XPathExpression( xmlXPathCompExprPtr val ):BaseT(val)
		{
			
		}

		XPathExpression( const XPathExpression& val ):BaseT(val)
		{
			
		}
		
		XPathExpression& operator=( xmlXPathCompExprPtr rhs )
		{
			assign(rhs);
			return *this;
		}

		static void freeResource(xmlXPathCompExprPtr res);


		void compile( const String& xpathQuery );
	};


	class XPathIterator;

	typedef std::vector<XmlNode> XmlNodeList;

	class XMLKIT_API XPathNodeIterator {
	public:	
		XPathNodeIterator():nodes_(NULL){}

		XPathNodeIterator& operator++() {
			if ( NULL != nodes_ ) {
				++iterator_;
			}
			return *this;
		}

		XPathNodeIterator operator++(int) {
			if ( NULL != nodes_ ) {
				++iterator_;
			}
			return *this;
		}
		
		bool operator != ( const XPathNodeIterator& rhs ) const {
			return iterator_ != rhs.iterator_;
		}

		
		XmlNode& operator*() {
			if ( NULL == nodes_ ) {
				static XmlNode nullNode;
				return nullNode;
			}

			return *iterator_;
		}

		const XmlNode& operator*() const {
			if ( NULL == nodes_ ) {
				static XmlNode nullNode;
				return nullNode;
			}

			return *iterator_;
		}

		bool atEnd() const {
			if ( NULL == nodes_ ) {
				return true;
			}
			return iterator_ == nodes_->end();
		}

		bool next() {
			if ( NULL == nodes_ ) {
				return false;
			}

			++iterator_;
			return iterator_ != nodes_->end();
		}

		bool isNull() const {
			return NULL == nodes_;
		}

		friend class XPathIterator;
	protected:		
		typedef XmlNodeList::iterator NodeIter;
		typedef XmlNodeList::const_iterator ConstNodeIter;

		XPathNodeIterator( XmlNodeList& nodes ):nodes_(&nodes) {
			iterator_ = nodes_->begin();
		}

		XPathNodeIterator( XmlNodeList& nodes, XmlNodeList::iterator it ):
			nodes_(&nodes), iterator_(it) {}

		XmlNodeList* nodes_;
		XmlNodeList::iterator iterator_;
	};

	class XMLKIT_API XPathIterator : public Attachable<xmlXPathContextPtr,XPathIterator> {
	public:
		typedef Attachable<xmlXPathContextPtr,XPathIterator> BaseT;

		XPathIterator( const XmlDocument& doc );

		static void freeResource(xmlXPathContextPtr res);

		VariantData eval( const String& xpathQuery );

		VariantData eval( const XPathExpression& expression );

		XmlNode select( const String& xpathQuery ) {
			XPathExpression exp;
			exp.compile(xpathQuery);
			return select( exp );
		}

		XmlNode select( const XPathExpression& expression );

		XPathNodeIterator selectNodes( const String& xpathQuery ) {
			XPathExpression exp;
			exp.compile(xpathQuery);
			return selectNodes( exp );
		}

		XPathNodeIterator selectNodes( const XPathExpression& expression );

		XPathNodeIterator end() {
			return XPathNodeIterator(nodes_, nodes_.end());
		}

		XPathNodeIterator begin() {
			return XPathNodeIterator(nodes_, nodes_.begin());
		}

		void registerNamespaces( Dictionary& namespaceDict );

	protected:
		xmlXPathObjectPtr xpathObj_;
		XmlNodeList nodes_;
	};



	

	class XMLKIT_API XMLTextReader {
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

		

		XMLErrorDelegate Error;
		

		XMLTextReader();

		~XMLTextReader();


		size_t getAttributeCount() const;

		String getBaseURI() const ;

		int getBytesConsumed() const ;

		bool close() ;

		String getEncoding() const;

		String getLocalName() const;

		String getName() const ;
		
		String getNamespaceURI() const ;

		String getPrefix() const ;

		String getTextValue() const ;

		String getLang() const ;

		String getVersion() const;

		int getCurrentDepth() const ;

		XmlNode expand();

		String getAttribute( const String& name ) const;
		
		String getAttribute( const size_t& index ) const;
		
		String getAttribute( const String& localName, const String& namespaceURI ) const;

		int getCurrentParserColumn() const;

		int getCurrentParserLine() const;

		bool parserLoadsDTD() const;

		bool parserUsingDefaultAttrs() const;

		bool parserWillValidate() const;

		bool parserWillSubstituteEntities() const;

		void setParserLoadsDTD( bool val );

		void setParserDefaultAttrs( bool val );

		void setParserWillValidate( bool val ) ;

		void setParserWillSubstituteEntities( bool val );

		bool hasAttributes() const;

		bool hasValue() const;

		bool isDefaultValue() const;

		bool isEmptyElement() const;

		bool isNamespace() const;

		bool isParserValid() const;

		String lookupNamespace( const String& prefix ) const;
			
		bool moveToAttribute( const String& attributeName );

		bool moveToAttribute( size_t index );

		bool moveToAttribute( const String& localAttrName, const String& namespaceURI );

		bool moveToElement();

		bool moveToFirstAttribute();

		bool moveToNextAttribute();

		bool next();

		bool nextSibling();

		XMLNodeType getNodeType() const;

		int getQuoteChar() const;

		bool read();

		bool readAttrValue();

		String readInnerXml();

		String readOuterXml();

		String readString();

		bool schemaValidate( const String& xsd );

		bool isEOF() const;

		int getState() const;

		XmlNode getCurrentNode();

		void setXML( const String& xml );

		void add( const String& xml );

		void add( const unsigned char* xmlBuffer, size_t length );

		XMLText::EncodingType getEncodingType() const ;
		void setEncodingType( XMLText::EncodingType val );
	protected:
		xmlTextReaderPtr xmlReader_;
		xmlBufferPtr xmlBuf_;
		xmlParserInputBufferPtr xmlInputBuf_;
		XMLText::EncodingType encodingType_;

		

		void checkBuffers();

		void createXMLReader();

		static void	xmlStructuredErrorFunc(void * userData,  xmlErrorPtr error);
	};








	
	class XMLKIT_API XmlTextWriter : public Attachable<xmlTextWriterPtr,XmlTextWriter> {
	public:
		typedef Attachable<xmlTextWriterPtr,XmlTextWriter> BaseT;
		
		XmlTextWriter();
		
		XmlTextWriter( OutputStream* stream );

		XmlTextWriter( XMLSaxParser& parser );

		XmlTextWriter( XmlDocument& doc );

		XmlTextWriter( XmlDocument& doc, XmlNode& node );

		
		static void freeResource(xmlTextWriterPtr res);

		
		void initWithStream( OutputStream* stream );

		void initWithParser( XMLSaxParser& parser );

		void initWithDocument( XmlDocument& doc );

		void initWithDocument( XmlDocument& doc, XmlNode& node ) ;

		void startDocument( const String& version="", const String& encoding="", const String& standalone="" );
			
		void startDTD( const String& name, const String& publicID, const String& systemID );

		void startDTDAttrList( const String& name );

		void startDTDEntity( bool parameterEntity,  const String& name );

		void startDTDElement( const String& name );

		void endDTD();

		void endDTDAttrList();

		void endDTDElement();

		void endDTDEntity();

		void endDocument();

		void startCDATA();

		void startComment();


		void startElement( const String& name );

		void startElementNamespace( const String& prefix, const String& name, const String& URI );

		void startProcessingInstruction( const String& target );

		void startAttribute( const String& name );
		
		void startAttributeNamespace( const String& prefix, const String& name, const String& URI );

		void endAttribute();

		void endElement();

		void endProcessingInstruction();

		void endCDATA();

		void endComment();

		void attribute( const String& prefix, const String& name, const String& URI, const String& content );

		void attribute( const String& name, const String& content );

		void base64( const uchar* data, size_t dataLength );

		void base64( const String& data );

		void binaryHex( const uchar* data, size_t dataLength );

		void binaryHex( const String& data );

		void CDATA( const String& data );

		void comment( const String& comment );

		void DTD( const String& name, const String& publicID, const String& systemID, const String& subset );

		void DTDAttrList( const String& name, const String& content );

		void DTDElement( const String& name, const String& content );

		void DTDEntity( bool parameterEntity, const String& name, const String& publicID, const String& systemID, 
						const String& notation, const String& content );

		void DTDExternalEntity( bool parameterEntity, const String& name, const String& publicID, 
								const String& systemID, const String& notation );

		void DTDExternalEntityContents( const String& publicID, const String& systemID, const String& notation );

		void DTDInternalEntity( bool parameterEntity, const String& name, const String& content );

		void DTDNotation( const String& name, const String& publicID, const String& systemID );

		void element( const String& name, const String& contents );

		void elementNamespace( const String& prefix, const String& name, const String& URI, const String& contents );

		void processingInstruction( const String& target, const String& contents );

		void rawContent( const String& contents );

		void text( const String& contents );

		void flush();
		
	protected:
		OutputStream* writeStream_;
		xmlOutputBufferPtr	outputBuffer_;

		void initOutputBuffer();
		static int writeCallback(void * context,  const char * buffer, int len);
		static int closeCallback( void * context );
	};
	






	

	class XMLKIT_API XmlSchemaContext : public Attachable<xmlSchemaParserCtxtPtr,XmlSchemaContext> {
	public:
		typedef Attachable<xmlSchemaParserCtxtPtr,XmlSchemaContext> BaseT;
		

		XMLErrorDelegate ParserError;

		XmlSchemaContext( const String& uri );

		XmlSchemaContext( const XmlDocument& doc );

		XmlSchemaContext();
		
		XmlSchemaContext( xmlSchemaParserCtxtPtr val );
		
		XmlSchemaContext( const XmlSchemaContext& val );
		

		XmlSchemaContext& operator=( xmlSchemaParserCtxtPtr rhs );
		
		static void freeResource(xmlSchemaParserCtxtPtr res);

		void initFromURI( const String& uri );

		void initFromDocument( const XmlDocument& doc );
	protected:
		void initAndAttach( xmlSchemaParserCtxtPtr ptr );
		static void	parserErrorHandler( void* userData, xmlErrorPtr error );
	};



	class XMLKIT_API XmlValidSchemaContext : public Attachable<xmlSchemaValidCtxtPtr,XmlValidSchemaContext> {
	public:
		typedef Attachable<xmlSchemaValidCtxtPtr,XmlValidSchemaContext> BaseT;
		

		
		XMLErrorDelegate ValidityError;
		

		XmlValidSchemaContext();
		
		XmlValidSchemaContext( xmlSchemaValidCtxtPtr val );
		
		XmlValidSchemaContext( const XmlValidSchemaContext& val );
		
		~XmlValidSchemaContext();

		XmlValidSchemaContext& operator=( xmlSchemaValidCtxtPtr rhs );
		
		static void freeResource(xmlSchemaValidCtxtPtr res);


		void parse( const XmlSchemaContext& ctx );

		int getOptions() const ;

		void setOptions( int val );

		void validate( XmlDocument& doc );

		void validate( XmlNode& node );

		bool isValid() const ;

	protected:
		xmlSchemaPtr schema_;

		static void	validityErrorHandler( void* userData, xmlErrorPtr error );
	};


	class XMLKIT_API XmlSchema {
	public:
		void setSchema( XmlDocument& schema ) {
			schemaCtx_.initFromDocument( schema );
		}

		bool validate( XmlDocument& document ) {
			bool result = false;

			VCF_ASSERT( !schemaCtx_.isNull() );

			if ( !schemaCtx_.isNull() ) {
				XmlValidSchemaContext validCtx;
				
				try {
					validCtx.parse(schemaCtx_);
					
					try {
						validCtx.validate( document );
						result = true;
					}
					catch ( SchemaValidationException& ) {
						result = false;
					}
					catch ( std::exception&) {
						throw;
					}
				}
				catch ( ValidSchemaParseException& ) {
					result = false;
				}
				catch ( std::exception& ) {
					throw;
				}
			}

			return result;
		}
		
		XmlSchemaContext schemaCtx_;
	};





	///////////////////XSLT stuff //////////////////////

	class XMLKIT_API XSLTStyleSheet : public Attachable<xsltStylesheetPtr,XSLTStyleSheet> {
	public:
		typedef Attachable<xsltStylesheetPtr,XSLTStyleSheet> BaseT;
		
		XSLTStyleSheet();
		
		XSLTStyleSheet( xsltStylesheetPtr val );
		
		XSLTStyleSheet( const XSLTStyleSheet& val );
		
		XSLTStyleSheet& operator=( xsltStylesheetPtr rhs );
		
		static void freeResource(xsltStylesheetPtr res);

		void newStyleSheet();

		void parse( const String& fileName ) ;

		void parseDocument( const XmlDocument& doc );

		XmlDocument* transform( const XmlDocument& doc );
	};





};




#endif //_VCF_XMLKIT_H__