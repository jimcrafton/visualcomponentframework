#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"

#include "XMLKit.h"


#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libxslt/extensions.h>
#include <libxml/xpathInternals.h>






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

	class XmlSchemaContext : public Attachable<xmlSchemaParserCtxtPtr,XmlSchemaContext> {
	public:
		typedef Attachable<xmlSchemaParserCtxtPtr,XmlSchemaContext> BaseT;
		
		XmlSchemaContext( const String& uri ) :BaseT()
		{
			initFromURI( uri );
		}

		XmlSchemaContext( const XmlDocument& doc ) :BaseT()
		{
			initFromDocument( doc );
		}

		XmlSchemaContext():BaseT(){}
		
		XmlSchemaContext( xmlSchemaParserCtxtPtr val ):BaseT(val){}
		
		XmlSchemaContext( const XmlSchemaContext& val ):BaseT(val){}
		

		XmlSchemaContext& operator=( xmlSchemaParserCtxtPtr rhs ) {BaseT::operator=(rhs); return *this;} 
		
		static void freeResource(xmlSchemaParserCtxtPtr res) {xmlSchemaFreeParserCtxt(res);}

		void initFromURI( const String& uri ) {
			attach( xmlSchemaNewParserCtxt( uri.ansi_c_str() ) );
		}

		void initFromDocument( const XmlDocument& doc ) {
			attach( xmlSchemaNewDocParserCtxt( doc.get() ) );
		}

		//void setSAXHandler( 
	};

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