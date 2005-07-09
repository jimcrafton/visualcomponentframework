#ifndef _XMLPARSER_H__
#define _XMLPARSER_H__
//XMLParser.h


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace xmake {


typedef char VCFChar;




class XMLNode;


/**
*Class XMLAttr documentation
*/
class  XMLAttr  {
public:
	
	XMLAttr ( const String& name="", const String& value="", XMLNode* node=NULL ) {
		name_ = name;
		value_ = value;
		node_ = node;
	}
	
	XMLAttr ( const XMLAttr& attr ) {
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
class  XMLNode  {
public:

	typedef std::vector<XMLNode*> Vector;
	typedef Vector::iterator Iterator;


	XMLNode( const String& name="", XMLNode* parentNode=NULL );

	XMLNode( const XMLNode& node );

	virtual ~XMLNode();

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

	XMLAttr* getAttrByIndex( const long& index );

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
		XMLNode* node = new XMLNode( nodeName, this );
		childNodes_.push_back( node );
		return node;
	}

	void removeNode( XMLNode* node );

	XMLNode* getNodeByName( const String& name );

	XMLNode* getNodeByIndex( const long& index );

	inline Enumerator<XMLNode*>* getChildNodes() {
		return 	childNodesContainer_.getEnumerator();
	};

	void clearChildNodes();

	virtual String toString();
	
	Vector& getChildNodesVector() {
		return childNodes_;
	}
protected:
	String CDATA_;
	String name_;
	XMLNode* parentNode_;
	
	Vector childNodes_;
	EnumeratorContainer<Vector,XMLNode*> childNodesContainer_;

	std::vector<XMLAttr> attrs_;
	EnumeratorContainer<std::vector<XMLAttr>,XMLAttr> attrsContainer_;
	long getDepth();
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
*/
class  XMLParser  { 
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
	*tries to parse and process the next node. 
	*@return bool true if successful, false if the parsing failed.
	*/
	bool nextNode();

	/**
	*parses the XML data represented by the xmlString argument.
	*@param String the XML data to parse
	*/
	void parse( const String& xmlString );


	Enumerator<XMLNode*>* getParsedNodes();

	void resortParsedNodes();

	void addEntity( const String& entityName, const String& value );
protected:

	const VCFChar* tokenPtr_;
	const VCFChar* sourcePtr_;
	const VCFChar* xmlBufferStart_;
	long sourceSize_;
	bool dtdStarted_;

	String tokenString_;	
	
	XMLTagType token_;
	
	XMLNode* currentNode_;

	std::vector<XMLNode*> parsedNodes_;
	EnumeratorContainer<std::vector<XMLNode*>,XMLNode*> parsedNodesContainer_;

	const VCFChar* parseComments( const VCFChar* commentPtrStart );

	void parseEntity( const VCFChar* entityPtrStart, const VCFChar* entityPtrEnd );

	const VCFChar* parseNode( const VCFChar* nodePtrStart, const VCFChar* nodePtrEnd );

	const VCFChar* parseAttrs( const VCFChar* attrPtrStart, const VCFChar* attrPtrEnd );

	void clearNodes();

	void addChildren( XMLNode* parent );

	const VCFChar* skipWhitespace( const VCFChar* start, const int& length );
	const VCFChar* skipTillWhitespace( const VCFChar* start, const int& length );

	String decodeText( const String& text );

	bool whiteSpace( const VCFChar& ch );

	std::map<String,String> entityMap_;
private:
};



};//end of namespace xmake



/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:18  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2004/12/21 01:25:17  marcelloptr
*added cvs log section
*
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.1  2004/04/28 04:07:36  ddiego
*migration towards new directory structure
*
*Revision 1.6  2003/12/18 05:16:08  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.4.1  2003/10/30 17:54:06  ddiego
*updated the xml parser to support attributes better (be more
*forgiving with syntax) and handle !ENTITY and (most importantly)
*handle ![CDATA[ ]]> tags, as well as simple support for entity parsing
*like &amp; or &lt;
*
*Revision 1.5  2003/05/17 20:38:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.1  2003/03/12 03:13:36  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2003/02/26 04:31:16  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.3.8.1  2002/12/11 16:55:46  ddiego
*added dependency generation for projects. You can now specify
*which projects depend on each other
*
*Revision 1.3  2002/09/12 03:26:12  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.12.1  2002/07/16 15:52:48  ddiego
*mods to xmake to separate it into a lib file and
*command line program. This means there is now a
*separate libXmake for using in other programs
*also moved all the xmake classes into their
*own xmake namespace.
*Changes made to the makefile as well as a new
*dsp for the libXmake
*
*Revision 1.2  2002/03/15 16:33:22  ddiego
*gcc compile fixes
*
*Revision 1.1  2002/02/25 05:01:53  ddiego
*added the xmake project
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif //_XMLPARSER_H__


