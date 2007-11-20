#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"

#include "XMLKit.h"


#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libxslt/extensions.h>
#include <libxml/xpathInternals.h>


#include <libxml\xmlwriter.h>



#if !defined(VCF_DISABLE_PRAGMA_LINKING)
#   define USE_INTERNETKIT_DLL
#endif

#include "vcf/InternetKit/InternetKit.h"



#define testxml			"<stuff a=\"1\" b=\"23\">Wow!<animal>Zebra</animal><animal>Cow</animal></stuff>"

#define BooksXML		"<books xmlns:bk=\"http://www.example.com/books\">\n"\
							"<bk:book>\n"\
								"<bk:title>Title</bk:title>\n"\
								"<bk:author>Author Name</bk:author>\n"\
								"<bk:price>5.50</bk:price>\n"\
							"</bk:book>\n"\
						"</books>\n"


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


void testXPath( const String& s, XmlDocument& doc )
{
	std::vector<XmlNode> nodes;
	System::println( "------------------------------------------------------------------------------" );
	System::println( "xpath: " + s );
	
	VariantData res = doc.matches( s, nodes );
	System::println( "doc.matches() returned: " + res.toString() );

	System::println( "results:" );
	for (size_t i=0;i<nodes.size();i++ ) {
		const XmlNode& n = nodes[i];
		
		
		System::println( "Node name: " + n.getName() + " path: " + n.getPath() + " text: " + n.getContent() );
	}
	
}








class XSLTTransformContext : public Attachable<xsltTransformContextPtr,XSLTTransformContext> {
public:
	typedef Attachable<xsltTransformContextPtr,XSLTTransformContext> BaseT;
	

	XSLTTransformContext( const XSLTStyleSheet& styleSheet, const XmlDocument& doc ):BaseT()
	{

	}

	XSLTTransformContext():BaseT()
	{
		
	}
	
	XSLTTransformContext( xsltTransformContextPtr val ):BaseT(val)
	{
		
	}
	
	XSLTTransformContext( const XSLTTransformContext& val ):BaseT(val)
	{
		
	}
	
	XSLTTransformContext& operator=( xsltTransformContextPtr rhs )
	{
		assign(rhs);
		return *this;
	}
	
	static void freeResource(xsltTransformContextPtr res)
	{
		xsltFreeTransformContext(res);
	}
};



void Test_Function( xmlXPathParserContextPtr ctxt,
                                 int nargs)
{
	valuePush(ctxt, xmlXPathNewString((const xmlChar *)"HOLA"));
}

void* MyxsltExtInitFunction(xsltTransformContextPtr ctxt, const xmlChar * URI)
{
	void* res = NULL;

	xsltRegisterExtFunction( ctxt, (const xmlChar*)"test", (const xmlChar*)"urn:foo.bar", Test_Function );

	return res;
}

void MyxsltExtShutdownFunction( xsltTransformContextPtr ctxt, 
					 const xmlChar * URI, 
					 void * data)
{

}



void testXSLT()
{
	
	
	int r = xsltRegisterExtModule( (const xmlChar*)"urn:foo.bar", MyxsltExtInitFunction, MyxsltExtShutdownFunction );

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	XSLTStyleSheet stylesheet;
	stylesheet.parse( "cdcatalog.xsl" );

	XmlDocument doc;
	doc.load( "cdcatalog.xml" );

	XmlDocument* res = stylesheet.transform( doc );	

	if ( res ) {
		FileOutputStream fos( "xslt-proc-results.html" );
		fos << res->toString();
		fos.close();
	}

	delete res;

	stylesheet = NULL;
}



	class XmlSchema : public Attachable<xmlSchemaPtr,XmlSchema> {
	public:
		typedef Attachable<xmlSchemaPtr,XmlSchema> BaseT;
		
		XmlSchema():BaseT(),currentCtx_(NULL){}
		
		XmlSchema( xmlSchemaPtr val ):BaseT(val),currentCtx_(NULL){}
		
		XmlSchema( const XmlSchema& val ):BaseT(val),currentCtx_(NULL){}
		
		~XmlSchema()
		{
			if ( NULL != currentCtx_ ) {
				xmlSchemaFreeParserCtxt( currentCtx_ );
			}
		}

		XmlSchema& operator=( xmlSchemaPtr rhs ) {BaseT::operator=(rhs); return *this;} 
		
		static void freeResource(xmlSchemaPtr res) {xmlSchemaFree(res);}

		void parseSchema( const XmlDocument& doc ) {
			if ( NULL != currentCtx_ ) {
				xmlSchemaFreeParserCtxt( currentCtx_ );
			}

			currentCtx_ = xmlSchemaNewDocParserCtxt( doc.get() );
			attach( xmlSchemaParse( currentCtx_ ) );
		}
	protected:
		xmlSchemaParserCtxtPtr currentCtx_;

	};

void testSchema()
{
	XmlSchema schema;
}





	class XmlTextWriter : public Attachable<xmlTextWriterPtr,XmlTextWriter> {
	public:
		typedef Attachable<xmlTextWriterPtr,XmlTextWriter> BaseT;
		
		XmlTextWriter():BaseT(),outputBuffer_(NULL),writeStream_(NULL)
		{
			//initOutputBuffer();
			//attach( xmlNewTextWriter( outputBuffer_ ) );
		}
		
		XmlTextWriter( OutputStream* stream ):BaseT(),outputBuffer_(NULL),writeStream_(NULL)
		{
			initWithStream(stream);
		}

		XmlTextWriter( XMLSaxParser& parser ):BaseT(),outputBuffer_(NULL),writeStream_(NULL)
		{
			initWithParser(parser);
		}

		XmlTextWriter( XmlDocument& doc ):BaseT(),outputBuffer_(NULL),writeStream_(NULL)
		{
			initWithDocument(doc);
		}

		XmlTextWriter( XmlDocument& doc, XmlNode& node ):BaseT(),outputBuffer_(NULL),writeStream_(NULL)
		{
			initWithDocument(doc,node);
		}

		
		static void freeResource(xmlTextWriterPtr res) {xmlFreeTextWriter(res);}

		
		void initWithStream( OutputStream* stream )
		{
			writeStream_ = stream;
			initOutputBuffer();
			attach( xmlNewTextWriter( outputBuffer_ ) );
		}

		void initWithParser( XMLSaxParser& parser ) 
		{
			attach( xmlNewTextWriterPushParser( parser.internal_getParser(), 0 ) );
		}

		void initWithDocument( XmlDocument& doc ) 
		{
			doc = NULL; //clear anything else in there
			attach( xmlNewTextWriterDoc( &doc.get(), 0 ) );
		}

		void initWithDocument( XmlDocument& doc, XmlNode& node ) 
		{
			doc = NULL; //clear anything else in there
			attach( xmlNewTextWriterTree( doc.get(), node.get(), 0 ) );
		}

		void startDocument( const String& version="", const String& encoding="", const String& standalone="" ) 
		{	
			int res = xmlTextWriterStartDocument( resource_, 
										version.empty() ? NULL : version.ansi_c_str(), 
										encoding.empty() ? NULL : encoding.ansi_c_str(),
										standalone.empty() ? NULL : standalone.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

			
		void startDTD( const String& name, const String& publicID, const String& systemID )
		{
			int res = 
				xmlTextWriterStartDTD( resource_, 
										(const xmlChar*) name.ansi_c_str(),
										(const xmlChar*) publicID.ansi_c_str(),
										(const xmlChar*) systemID.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void startDTDAttrList( const String& name )
		{
			int res = 
				xmlTextWriterStartDTDAttlist( resource_, 
										(const xmlChar*) name.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		

		void startDTDEntity( bool parameterEntity,  const String& name )
		{
			int res = 
				xmlTextWriterStartDTDEntity( resource_, parameterEntity ? 1 : 0,
												(const xmlChar*) name.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void startDTDElement( const String& name )
		{
			int res = 
				xmlTextWriterStartDTDElement( resource_, (const xmlChar*) name.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endDTD()
		{
			int res = xmlTextWriterEndDTD( resource_ );
			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endDTDAttrList()
		{
			int res = xmlTextWriterEndDTDAttlist( resource_ );
			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endDTDElement()
		{
			int res = xmlTextWriterEndDTDElement( resource_ );
			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endDTDEntity()
		{
			int res = xmlTextWriterEndDTDEntity( resource_ );
			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endDocument()
		{
			int res = xmlTextWriterEndDocument( resource_ );
			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void startCDATA()
		{
			int res = 
				xmlTextWriterStartCDATA( resource_ );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void startComment()
		{
			int res = 
				xmlTextWriterStartComment( resource_ );

			if ( res == -1 ) {
				throw XmlException();
			}
		}


		void startElement( const String& name )
		{
			int res = 
				xmlTextWriterStartElement( resource_, (const xmlChar*) name.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void startElementNamespace( const String& prefix, const String& name, const String& URI )
		{
			int res = 
				xmlTextWriterStartElementNS( resource_, 
											prefix.empty() ? NULL : (const xmlChar*) prefix.ansi_c_str(),
											(const xmlChar*) name.ansi_c_str(),
											URI.empty() ? NULL : (const xmlChar*) URI.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void startProcessingInstruction( const String& target )
		{
			int res = 
				xmlTextWriterStartPI( resource_, (const xmlChar*) target.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void startAttribute( const String& name )
		{
			int res = 
				xmlTextWriterStartAttribute( resource_, (const xmlChar*) name.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}
		
		void startAttributeNamespace( const String& prefix, const String& name, const String& URI )
		{
			int res = 
				xmlTextWriterStartAttributeNS( resource_, 
											prefix.empty() ? NULL : (const xmlChar*) prefix.ansi_c_str(),
											(const xmlChar*) name.ansi_c_str(),
											URI.empty() ? NULL : (const xmlChar*) URI.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endAttribute()
		{
			int res = 
				xmlTextWriterEndAttribute( resource_ );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endElement()
		{
			int res = 
				xmlTextWriterEndElement( resource_ );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endProcessingInstruction()
		{
			int res = 
				xmlTextWriterEndPI( resource_ );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endCDATA()
		{
			int res = 
				xmlTextWriterEndCDATA( resource_ );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void endComment()
		{
			int res = 
				xmlTextWriterEndComment( resource_ );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void attribute( const String& prefix, const String& name, const String& URI, const String& content )
		{
			int res = 
				xmlTextWriterWriteAttributeNS( resource_, 
											prefix.empty() ? NULL : (const xmlChar*) prefix.ansi_c_str(),
											(const xmlChar*) name.ansi_c_str(),
											URI.empty() ? NULL : (const xmlChar*) URI.ansi_c_str(),
											(const xmlChar*) content.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void attribute( const String& name, const String& content )
		{
			int res = 
				xmlTextWriterWriteAttribute( resource_, 
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) content.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void base64( const uchar* data, size_t dataLength )
		{
			int res = 
				xmlTextWriterWriteBase64( resource_, (const char*)data, 0, dataLength );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void base64( const String& data )
		{
			AnsiString tmp = data;
			base64( (const uchar*)tmp.c_str(), tmp.size() );
		}

		void binaryHex( const uchar* data, size_t dataLength )
		{
			int res = 
				xmlTextWriterWriteBinHex( resource_, (const char*)data, 0, dataLength );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void binaryHex( const String& data )
		{
			AnsiString tmp = data;
			binaryHex( (const uchar*)tmp.c_str(), tmp.size() );
		}

		void CDATA( const String& data )
		{
			int res = 
				xmlTextWriterWriteCDATA( resource_, (const xmlChar*)data.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void comment( const String& comment )
		{
			int res = 
				xmlTextWriterWriteComment( resource_, (const xmlChar*)comment.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTD( const String& name, const String& publicID, const String& systemID, const String& subset )
		{
			int res = 
				xmlTextWriterWriteDTD( resource_, 
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) publicID.ansi_c_str(),
											(const xmlChar*) systemID.ansi_c_str(),
											(const xmlChar*) subset.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTDAttrList( const String& name, const String& content )
		{
			int res = 
				xmlTextWriterWriteDTDAttlist( resource_, 
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) content.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTDElement( const String& name, const String& content )
		{
			int res = 
				xmlTextWriterWriteDTDElement( resource_, 
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) content.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTDEntity( bool parameterEntity, const String& name, const String& publicID, const String& systemID, 
						const String& notation, const String& content )
		{
			int res = 
				xmlTextWriterWriteDTDEntity( resource_, parameterEntity ? 1 : 0,
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) publicID.ansi_c_str(),
											(const xmlChar*) systemID.ansi_c_str(),
											(const xmlChar*) notation.ansi_c_str(),
											(const xmlChar*) content.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTDExternalEntity( bool parameterEntity, const String& name, const String& publicID, 
								const String& systemID, const String& notation )
		{
			int res = 
				xmlTextWriterWriteDTDExternalEntity( resource_, parameterEntity ? 1 : 0,
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) publicID.ansi_c_str(),
											(const xmlChar*) systemID.ansi_c_str(),
											(const xmlChar*) notation.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTDExternalEntityContents( const String& publicID, const String& systemID, const String& notation )
		{
			int res = 
				xmlTextWriterWriteDTDExternalEntityContents( resource_, 
											(const xmlChar*) publicID.ansi_c_str(),
											(const xmlChar*) systemID.ansi_c_str(),
											(const xmlChar*) notation.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTDInternalEntity( bool parameterEntity, const String& name, const String& content )
		{
			int res = 
				xmlTextWriterWriteDTDInternalEntity( resource_, parameterEntity ? 1 : 0,
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) content.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void DTDNotation( const String& name, const String& publicID, const String& systemID )
		{
			int res = 
				xmlTextWriterWriteDTDNotation( resource_,
											(const xmlChar*) name.ansi_c_str(),
											(const xmlChar*) publicID.ansi_c_str(),
											(const xmlChar*) systemID.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void element( const String& name, const String& contents )
		{
			int res = 
				xmlTextWriterWriteElement( resource_, 
										(const xmlChar*)name.ansi_c_str(),
										(const xmlChar*)contents.ansi_c_str());

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void elementNamespace( const String& prefix, const String& name, const String& URI, const String& contents )
		{
			int res = 
				xmlTextWriterWriteElementNS( resource_, 
											prefix.empty() ? NULL : (const xmlChar*) prefix.ansi_c_str(),
											(const xmlChar*) name.ansi_c_str(),
											URI.empty() ? NULL : (const xmlChar*) URI.ansi_c_str(),
											(const xmlChar*) contents.ansi_c_str() );

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void processingInstruction( const String& target, const String& contents )
		{
			int res = 
				xmlTextWriterWritePI( resource_, 
										(const xmlChar*)target.ansi_c_str(),
										(const xmlChar*)contents.ansi_c_str());

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void rawContent( const String& contents )
		{
			int res = 
				xmlTextWriterWriteRaw( resource_, (const xmlChar*)contents.ansi_c_str());

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void rawString( const String& contents )
		{
			int res = 
				xmlTextWriterWriteString( resource_, (const xmlChar*)contents.ansi_c_str());

			if ( res == -1 ) {
				throw XmlException();
			}
		}

		void flush() 
		{
			xmlTextWriterFlush( resource_ );
		}
	protected:
		OutputStream* writeStream_;
		xmlOutputBufferPtr	outputBuffer_;

		void initOutputBuffer() {

			VCF_ASSERT( NULL != writeStream_ );

			outputBuffer_ = 
				xmlOutputBufferCreateIO( XmlTextWriter::writeCallback, 
											XmlTextWriter::closeCallback, this, NULL );


			VCF_ASSERT( NULL != outputBuffer_ );

			if ( NULL == outputBuffer_ ) {
				throw XmlException();
			}
		}

		

		static int writeCallback(void * context,  const char * buffer, int len)
		{

			XmlTextWriter* thisPtr = (XmlTextWriter*)context;
			int res = thisPtr->writeStream_->write( (const uchar*)buffer, len );
			if ( res >= 0 ) {
				return res;
			}

			return -1;
		}

		static int closeCallback( void * context )
		{
			XmlTextWriter* thisPtr = (XmlTextWriter*)context;

			return -1;
		}
	};


void testTextWriter()
{
	XmlDocument doc;
	XmlTextWriter writer(doc);

	writer.startDocument();

	writer.startElement( "foo" );
	writer.rawContent( "Stuff!" );
	
	writer.elementNamespace( "boo", "trills", "http://a.b.c", "wacky, wacky, wey do" );	

	writer.endElement();
	writer.comment( "all done here" );
	writer.endDocument();
	
	writer.flush();

	System::println( "XmlTextWriter results: \n" + doc.toString() );
}

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );	
	InternetKit::init(argc, argv);

	XMLKit::init( argc, argv );

	System::println( "XMLkit XML version: " + XMLKit::getXMLVersion() );
	System::println( "XMLkit XSLT version: " + XMLKit::getXSLTVersion() );


	{
		
		XMLSaxParser p;
		p.StartElement += MystartElementSAXFunc2;
		
		p.parse( testxml );
		
		
		XMLTextReader rdr;
		rdr.setXML( testxml );

		System::println( "lang: " + rdr.getLang() );
		System::println( "uri: " + rdr.getBaseURI() );
		System::println( "ns: " + rdr.getNamespaceURI() );
	

		while ( rdr.read() ) {			
			System::println( "Name: " + rdr.getName() + " depth: " + rdr.getCurrentDepth() );

				

			System::println( "Inner XML: { " + rdr.readInnerXml() + " }" );
		}



		AsyncURL url("http://www.w3schools.com/xpath/books.xml");
		
		url.get();

		url.wait();

		String xml = url.getDataAsString();

		System::println( "Retrieved url " + url.getURLString() + " contents:\n" + xml );

		rdr.setXML( xml );

		System::println( "lang: " + rdr.getLang() );
		System::println( "uri: " + rdr.getBaseURI() );
		System::println( "ns: " + rdr.getNamespaceURI() );
	

		while ( rdr.read() ) {			
			System::println( "Name: " + rdr.getName() + " depth: " + rdr.getCurrentDepth() );

				

			System::println( "Inner XML: { " + rdr.readInnerXml() + " }" );
		}


		XmlDocument doc;
		doc.setXML(xml);

		XmlNode root = doc.getRoot();
		std::vector<XmlNode> children;
		root.getChildren( children );
		std::vector<XmlNode>::iterator cit = children.begin();
		while ( cit != children.end() ) {
			XmlNode& child = *cit;
			System::println( "Name: " + child.getName() + ", path: " + child.getPath() );
			++cit;
		}



		testXPath( "/bookstore/book", doc );
		testXPath( "/bookstore/book[1]", doc );
		testXPath( "/bookstore/book/price/text()", doc );
		testXPath( "/bookstore/book[price>35]/price", doc );
		testXPath( "/bookstore/book[1]/price<34", doc );
		testXPath( "/bookstore/book[1]/price>34", doc );

		testXPath( "/bookstore/book[1]/price + 34", doc );
		testXPath( "sum(//price/text())", doc );

		
		XPathIterator xp(doc);
		XPathExpression exp;
		exp.compile( "/bookstore/book" );
		XPathNodeIterator it = xp.selectNodes(exp);
		while ( it != xp.end() ) {
			const XmlNode& n = *it;

			System::println( "Node: " + n.getPath() );

			it ++;
		}

		it = xp.begin();
		do {
			const XmlNode& n = *it;
			System::println( "Node: " + n.getName() + " contents:\n" + n.getContent() );
		} while ( it.next() );


		{

			System::println( BooksXML );

			XMLTextReader rdr;
			rdr.setXML( BooksXML );
			
			
			System::println( "lang: " + rdr.getLang() );
			System::println( "uri: " + rdr.getBaseURI() );
			System::println( "ns: " + rdr.getNamespaceURI() );
			
			
			while ( rdr.read() ) {			
				System::println( "\tName: " + rdr.getName() + " depth: " + rdr.getCurrentDepth() );
				System::println( "\tprefix: " + rdr.getPrefix() + " ns: " + rdr.getNamespaceURI() );

			}
			
			doc.setXML( BooksXML );
			
			XPathIterator xp(doc);
			Dictionary nsDict;
			nsDict["bk"] = "http://www.example.com/books";
			xp.registerNamespaces(nsDict);
			
			XPathNodeIterator it = xp.selectNodes("/books/bk:book");
			while ( it != xp.end() && !it.isNull() ) {
				const XmlNode& n = *it;

				std::vector<XmlNamespace> ns;
				n.getNamespaceList(ns);

				std::vector<XmlNamespace>::iterator itn = ns.begin();
				while ( itn != ns.end() ) {
					XmlNamespace& xns = *itn;
					System::println( "Node ns info - prefix: " + xns.getPrefix() + " uri: " + xns.getURI() );
					++itn;
				}


				System::println( "Node: " + n.getPath() );
				
				it ++;
			}
		}

	
		

		XmlDocument* doc2 = XmlDocument::newDocument();

		root = doc2->newNode( "n1" );

		doc2->setRoot( root );
		
		root.addChild( doc2->newNode( "spaz" ) );
		root.addChild( doc2->newNode( "goofy" ) );
		root.addChild( doc2->newNode( "donald" ) );

		String res;
		res += doc2;
		
		res = root.toString();
	
		XPathIterator xp2(*doc2);
		xp2.select("/n1/goofy").setContent( "Hello World" );

		root.setAttribute( "happy", "yes" );
		xp2.select("/n1/spaz").setAttributeAsVariant( "noise", 10 );

		res = root.toString();


		FileOutputStream fos("doc2.xml");
		TextOutputStream tos(&fos);
		tos << doc2->toString();

		delete doc2;
	}






	testXSLT();


	testTextWriter();

	XMLKit::terminate();

	InternetKit::terminate();
	FoundationKit::terminate();
	return 0;
}