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

	virtual String toString();

protected:
	String name_;
	String value_;
	XMLNode* node_;
};



/**
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
	inline String getName() {
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
	inline XMLNode* getParentNode() {
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
	inline Enumerator<XMLAttr>* getAttrs() {
		return attrsContainer_.getEnumerator();
	}

	XMLAttr* getAttrByName( const String& name );

	XMLAttr* getAttrByIndex( const ulong32& index );

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
	inline String getCDATA() {
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

	XMLNode* getNodeByName( const String& name );

	XMLNode* getNodeByIndex( const ulong32& index );

	inline Enumerator<XMLNode*>* getChildNodes() {
		return 	childNodesContainer_.getEnumerator();
	};

	void clearChildNodes();

	virtual String toString();
protected:
	String CDATA_;
	String name_;
	XMLNode* parentNode_;

	std::vector<XMLNode*> childNodes_;
	EnumeratorContainer<std::vector<XMLNode*>,XMLNode*> childNodesContainer_;

	std::vector<XMLAttr> attrs_;
	EnumeratorContainer<std::vector<XMLAttr>,XMLAttr> attrsContainer_;
	long getDepth();
};


/**
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
*Class XMLParserHandler documentation
*/
template <class SOURCE_TYPE> class XMLParserHandler : public EventHandlerInstance<SOURCE_TYPE,XMLParserEvent> {
public:
	XMLParserHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,XMLParserEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,XMLParserEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~XMLParserHandler(){};

};

/**
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
class FOUNDATIONKIT_API XMLParser : public ObjectWithEvents {
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
	DELEGATE(NodeFound)

	/**
	@delegate NodeCDATAFound this is fired whenever CDATA is encountered during the
	parsing of the xml data.
	@event XMLParserEvent
	*/
	DELEGATE(NodeCDATAFound)


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
	long sourceSize_;
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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.3  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.9.4.2  2003/10/30 20:13:03  ddiego
*fixed some bugs in the xml parser, added support for cdata and basic
*enities, also fiddled with the redirected IO for processes.
*
*Revision 1.9.4.1  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.9  2003/05/17 20:37:17  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.2  2003/05/15 03:01:02  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.8.2.1  2003/03/12 03:11:52  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:44  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.8.3  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.7.8.2  2003/01/08 00:19:48  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7.8.1  2002/11/28 05:12:04  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.7  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.6.6.2  2002/07/22 04:36:09  ddiego
*added more config editing code
*added operator=() to VCF::XMLNode
*fixed copy ctor bug in XMLNode( const XMLNode& )
*
*Revision 1.6.6.1  2002/07/15 04:06:14  ddiego
*fixing saving the various project file ot take advantage to relative path
*and the FilePath object
*
*Revision 1.6  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.4  2002/04/27 15:52:21  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.5.4.3  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.5.4.2  2002/03/25 04:19:46  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.5.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_XMLPARSER_H__


