////XMLKit.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include <libxml/tree.h>
#include <libxml/parser.h>


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


		void parse( const String& xml ) {
			AnsiString tmp = xml;

			xmlParseChunk( parser_, tmp.c_str(), tmp.size(), 1 );
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

	const xmlChar** tmp = atts;
	while ( *tmp != 0 ) {
		printf( "attr: %s\n", (const char*)*tmp );
		tmp ++;
	}
}

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );


	XMLKit::init( argc, argv );

	xmlSAXHandler sax = {0};
	sax.startElement = MystartElementSAXFunc;
	
	xmlParserCtxtPtr parser = xmlCreatePushParserCtxt( &sax, 
														NULL,
														NULL, 
														0,
														NULL );

	
	xmlParseChunk( parser, testxml, strlen(testxml), 1 );

	xmlFreeParserCtxt(parser);



	XMLSaxParser p;
	p.StartElement += MystartElementSAXFunc2;

	p.parse( testxml );


	XMLKit::terminate();

	FoundationKit::terminate();
	return 0;
}


