#ifndef _VCF_XMLPARSER_H__
#define _VCF_XMLPARSER_H__
//XMLParser.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class XMLNode;


/**
\class XMLAttr XMLParser.h "vcf/FoundationKit/XMLParser.h"
*Class XMLAttr documentation
*/
class FOUNDATIONKIT_API XMLAttr : public Object {
public:
	XMLAttr ( const String& name="", const String& value="", XMLNode* node=NULL ) {
		name_ = name;
		value_ = value;
		node_ = node;
	}

	XMLAttr ( const XMLAttr& attr ): Object(attr) {
		name_ = attr.name_;
		value_ = attr.value_;
		node_ = attr.node_;
	}

	virtual ~XMLAttr(){};

	XMLAttr& operator = ( const XMLAttr& attr ) {
		name_ = attr.name_;
		value_ = attr.value_;
		return *this;
	}

	inline String getName() const {
		return name_;
	}

	inline void setName( const String& name ) {
		name_ = name;
	}

	inline String getValue() const {
		return value_;
	}

	inline void setValue( const String& value ) {
		value_ = value;
	}

	inline XMLNode* getNode() const {
		return node_;
	}

	inline void setNode( XMLNode* node ) {
		node_ = node;
	}

	virtual String toString() const ;

protected:
	String name_;
	String value_;
	XMLNode* node_;
};



/**
\class XMLNode XMLParser.h "vcf/FoundationKit/XMLParser.h"
*Class XMLNode represents a single node in a
*parsed XML document.
*Nodes have a name, parent node, and 0 or more
*attributes represented as XMLAttr(s). In addition
*the node may have a string of characters that
*represent character data (CDATA)
*/
class FOUNDATIONKIT_API XMLNode : public Object {
public:
	XMLNode( const String& name="", XMLNode* parentNode=NULL );

	XMLNode( const XMLNode& node );

	virtual ~XMLNode();

	XMLNode& operator = ( const XMLNode& node );

	/**
	*gets the name of the node
	*/
	inline String getName() const {
		return name_;
	}

	/**
	*sets the name of the node. Generally done during parsing
	*/
	inline void setName( const String& name ) {
		name_ = name;
	}

	/**
	*gets the parent node of this node. May
	*return NULL if this is a root, or
	*top level node of the XML document
	*@return XMLNode the parent node. NULL if this
	*is a root node.
	*/
	inline XMLNode* getParentNode() const {
		return parentNode_;
	}

	/**
	*sets the parent node. Generally called by the parser
	*during the parsing phase of the XML document
	*/
	inline void setParentNode( XMLNode* parentNode ) {
		parentNode_ = parentNode;
	}

	/**
	*gets the collection of attributes for this node
	*@return Enumerator<XMLAttr>* an enumerator of XMLAttr
	*objects
	*/
	inline Enumerator<XMLAttr>* getAttrs() const {
		return attrsContainer_.getEnumerator();
	}

	XMLAttr* getAttrByName( const String& name ) const ;

	XMLAttr* getAttrByIndex( const uint32& index ) const ;

	/**
	*adds a new attribute to the node. Generally called by
	*parser.
	*/
	inline void addAttr( const XMLAttr& attr ) {
		attrs_.push_back( attr );
	}

	/**
	*adds a new attribute to the node. Generally called by
	*parser.
	*/
	inline void addAttr( const String& name, const String& value ) {
		XMLAttr attr( name, value, this );
		attrs_.push_back( attr );
	}


	/**
	*clears all the current attributes
	*/
	inline void clearAttrs() {
		attrs_.clear();
	}

	/**
	*returns the character data associated with this node.
	*/
	inline String getCDATA() const {
		return CDATA_;
	}

	/**
	*sets the character data for this node.
	*/
	inline void setCDATA( const String& CDATA ) {
		CDATA_ = CDATA;
	}

	inline void addChildNode( XMLNode* node ) {
		node->setParentNode( this );
		childNodes_.push_back( node );
	}

	inline XMLNode* addChildNode( const String& nodeName ) {
		//node added automagically in the constructor
		XMLNode* node = new XMLNode( nodeName, this );
		return node;
	}

	void removeNode( XMLNode* node );

	XMLNode* getNodeByName( const String& name ) const ;

	XMLNode* getNodeByIndex( const uint32& index ) const ;

	inline Enumerator<XMLNode*>* getChildNodes() const {
		return 	childNodesContainer_.getEnumerator();
	};

	void clearChildNodes();

	virtual String toString() const ;
protected:
	String CDATA_;
	String name_;
	XMLNode* parentNode_;

	std::vector<XMLNode*> childNodes_;
	EnumeratorContainer<std::vector<XMLNode*>,XMLNode*> childNodesContainer_;

	std::vector<XMLAttr> attrs_;
	EnumeratorContainer<std::vector<XMLAttr>,XMLAttr> attrsContainer_;
	int32 getDepth() const ;
};


/**
\class XMLParserEvent XMLParser.h "vcf/FoundationKit/XMLParser.h"
*Class XMLParserEvent documentation
*/
class FOUNDATIONKIT_API XMLParserEvent : public Event {
public:
	XMLParserEvent( Object * source, XMLNode* node ):
		Event(source){
		node_ = node;
	};


	virtual ~XMLParserEvent(){};

	/**
	*gets the XMLNode for this event
	*/
	XMLNode* getNode() {
		return node_;
	}
protected:

	XMLNode* node_;

};

/**
\class XMLParserHandler XMLParser.h "vcf/FoundationKit/XMLParser.h"
*Class XMLParserHandler documentation
*/
/*
template <class SOURCE_TYPE> class XMLParserHandler : public EventHandlerInstance<SOURCE_TYPE,XMLParserEvent> {
public:
	XMLParserHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,XMLParserEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,XMLParserEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~XMLParserHandler(){};

};
*/

typedef Delegate1<XMLParserEvent*> XMLParserDelegate;


/**
\class XMLNode XMLParser.h "vcf/FoundationKit/XMLParser.h"
*XMLParser is a very simple non-validating XML parser. Currently
*only really handles basic XML documents. Does <I><B>not</B></I>
*handle parsing DTDs yet. Allows outside objects to be notified of
*parsing events as the XML document is parsed. Events are:
*<ul>
*<li>
*NodeFound events. These are fired whenever a new node is discovered. The node
*is created, it's attributes are parsed, and then the event is fired. When receiving this
*event you can safely assume that any attributes for the node will be correctly filled
*out at this point, as well as the node having a valid parent node. CDATA may not be filled out
*at this point, there is a seperate event for it.
*</li>
*<li>
*NodeCDATAFound events. These are fired off when character data is found.
*The current node's CDATA is set, and then the event is fired. Handlers
*may safely assume that the node that the event object points to has valid
*CDATA.
*</li>
*</ul>
*When parsing XML, all XML comments are currently ignored.
*@author Jim Crafton
*@version 1.0
@delegates
	@del NodeFound
	@del NodeCDATAFound

*/
class FOUNDATIONKIT_API XMLParser : public ObjectWithCallbacks {
public:
	enum XMLTagType {
		TagCDATA	=	-3,
		TagComment	=	'!',
		TagSymbol	=	-1,
		TagOpen		=	'<',
		TagClose	=	'>',
		TagEnd		=	'/',
		TagEquals	=	'=',
		TagQuote	=	'\"'
	};

	XMLParser();

	virtual ~XMLParser();

	/**
	@delegate NodeFound this is fired whenever a new node is encountered during the
	parsing of the xml data
	@event XMLParserEvent
	*/
	DELEGATE(XMLParserDelegate,NodeFound)

	/**
	@delegate NodeCDATAFound this is fired whenever CDATA is encountered during the
	parsing of the xml data.
	@event XMLParserEvent
	*/
	DELEGATE(XMLParserDelegate,NodeCDATAFound)


	/**
	*tries to parse and process the next node.
	*@return bool true if successful, false if the parsing failed.
	*/
	bool nextNode();

	/**
	*parses the XML data represented by the xmlString argument.
	*@param String the XML data to parse
	*/
	void parse( const String& xmlString );

	void parse( InputStream* stream );

	Enumerator<XMLNode*>* getParsedNodes();
protected:

	const VCFChar* tokenPtr_;
	const VCFChar* sourcePtr_;
	const VCFChar* xmlBufferStart_;
	int32 sourceSize_;
	String tokenString_;
	bool dtdStarted_;
	std::map<String,String> entityMap_;

	XMLTagType token_;

	XMLNode* currentNode_;

	std::vector<XMLNode*> parsedNodes_;
	EnumeratorContainer<std::vector<XMLNode*>,XMLNode*> parsedNodesContainer_;

	const VCFChar* parseComments( const VCFChar* commentPtrStart );

	void parseEntity( const VCFChar* entityPtrStart, const VCFChar* entityPtrEnd );

	const VCFChar* parseNode( const VCFChar* nodePtrStart, const VCFChar* nodePtrEnd );

	const VCFChar* parseAttrs( const VCFChar* attrPtrStart, const VCFChar* attrPtrEnd );

	void clearNodes();

	const VCFChar* skipWhitespace( const VCFChar* start, const int& length );

	const VCFChar* skipTillWhitespace( const VCFChar* start, const int& length );

	String decodeText( const String& text );

	bool whiteSpace( const VCFChar& ch );



private:
};


}; //end of namespace VCF


#endif // _VCF_XMLPARSER_H__

/**
$Id$
*/
