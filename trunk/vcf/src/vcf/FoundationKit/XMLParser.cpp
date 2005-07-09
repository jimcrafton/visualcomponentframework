//XMLParser.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//XMLParser.h

#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;

String XMLAttr::toString()
{
	String result = " " + getName() + "=\"" + getValue() + "\" ";
	return result;
}


XMLNode::XMLNode( const String& name, XMLNode* parentNode )
{
	name_ = name;
	parentNode_ = parentNode;
	attrsContainer_.initContainer( attrs_ );
	childNodesContainer_.initContainer( childNodes_ );

	if ( NULL != parentNode ) {
		parentNode->addChildNode( this );
	}
}


XMLNode::XMLNode( const XMLNode& node ) :
    Object(node)
{
	name_ = node.name_;
	parentNode_ = node.parentNode_;
	CDATA_ = node.CDATA_;
	attrs_ = node.attrs_;
	//childNodes_ = node.childNodes_;
	std::vector<XMLNode*>::const_iterator it = node.childNodes_.begin();
	while ( it != node.childNodes_.end() ) {
		XMLNode* childNode = *it;
		XMLNode* newNode = new XMLNode( *childNode );

		addChildNode( newNode );

		it ++;
	}

	attrsContainer_.initContainer( attrs_ );
	childNodesContainer_.initContainer( childNodes_ );
}

XMLNode::~XMLNode()
{
	clearChildNodes();
}

XMLNode& XMLNode::operator = ( const XMLNode& node )
{
	clearChildNodes();

	name_ = node.name_;
	parentNode_ = node.parentNode_;
	CDATA_ = node.CDATA_;
	attrs_ = node.attrs_;

	std::vector<XMLNode*>::const_iterator it = node.childNodes_.begin();
	while ( it != node.childNodes_.end() ) {
		XMLNode* childNode = *it;
		XMLNode* newNode = new XMLNode( *childNode );
		addChildNode( newNode );

		it ++;
	}

	attrsContainer_.initContainer( attrs_ );
	childNodesContainer_.initContainer( childNodes_ );

	return *this;
}

XMLAttr* XMLNode::getAttrByName( const String& name )
{
	XMLAttr* result = NULL;
	std::vector<XMLAttr>::iterator it = attrs_.begin();
	while ( it != attrs_.end() ){
		if ( name == (*it).getName() ) {
			result = &(*it);
			break;
		}
		it ++;
	}
	return result;
}

XMLAttr* XMLNode::getAttrByIndex( const ulong32& index )
{
	XMLAttr* result = NULL;
	if ( index < attrs_.size() ) {
		result = &attrs_[index];
	}
	return result;
}

void XMLNode::removeNode( XMLNode* node )
{
	std::vector<XMLNode*>::iterator found = std::find( childNodes_.begin(), childNodes_.end(), node );
	if ( found != childNodes_.end() ){
		childNodes_.erase( found );
	}
}

XMLNode* XMLNode::getNodeByName( const String& name )
{
	XMLNode* result = NULL;

	std::vector<XMLNode*>::iterator it = childNodes_.begin();
	while ( it != childNodes_.end() ) {
		XMLNode* node = *it;
		if ( node->getName() == name ) {
			result = node;
			break;
		}
		it ++;
	}

	return result;
}

XMLNode* XMLNode::getNodeByIndex( const ulong32& index )
{
	XMLNode* result = NULL;
	if ( (index >= 0) && (index < childNodes_.size()) ) {
		result = childNodes_[index];
	}

	return result;
}

void XMLNode::clearChildNodes()
{
	std::vector<XMLNode*>::iterator it = childNodes_.begin();
	while ( it != childNodes_.end() ) {
		XMLNode* node = *it;
		delete node;
		node = NULL;
		it ++;
	}
	childNodes_.clear();
}

long XMLNode::getDepth()
{
	long result = 0;

	XMLNode* parent = getParentNode();
	while ( NULL != parent ) {
		result ++;
		parent = parent->getParentNode();
	}

	return result;
}

String XMLNode::toString()
{
	String result;

	String tab;
	int tabsize = getDepth();
	for ( int i=0;i<tabsize;i++) {
		tab += "\t";
	}
	String nodeString = tab + "<" + getName() + " ";
	result += nodeString;

	std::vector<XMLAttr>::iterator attrIt = attrs_.begin();
	while ( attrIt != attrs_.end() ){
		XMLAttr* attr = &(*attrIt);
		result += attr->toString();
		attrIt ++;
	}

	if ( true == childNodes_.empty() && true == CDATA_.empty() ) {
		nodeString = "/>";
		result += nodeString;
	}
	else {
		nodeString = ">\n";
		result += nodeString;

		if ( !CDATA_.empty() ) {
			result += tab + "\t" + CDATA_ + "\n";
		}

		std::vector<XMLNode*>::iterator nodeIt = childNodes_.begin();
		while ( nodeIt != childNodes_.end() ) {
			XMLNode* node = *nodeIt;
			result += node->toString();
			nodeIt ++;
		}
		nodeString = tab + "</" + getName() + ">";
		result += nodeString;
	}

	// Only write out the ending newline if we're not the root node
	if (tabsize>0) {
		result += "\n";
	}

	return result;
}





XMLParser::XMLParser()
{
	parsedNodesContainer_.initContainer( parsedNodes_ );
	currentNode_ = NULL;

	dtdStarted_ = false;

	entityMap_["amp"] = "&";
	entityMap_["quot"] = "\"";
	entityMap_["apos"] = "'";
	entityMap_["lt"] = "<";
	entityMap_["gt"] = ">";
}

XMLParser::~XMLParser()
{
	clearNodes();
}

Enumerator<XMLNode*>* XMLParser::getParsedNodes()
{
	return parsedNodesContainer_.getEnumerator();
}

void XMLParser::clearNodes()
{
	std::vector<XMLNode*>::iterator it = parsedNodes_.begin();
	if ( it != parsedNodes_.end() ) {
		// the first node is the root, delete it, and all the children go as well
		XMLNode* node = *it;
		delete node;
		node = NULL;
	}
	parsedNodes_.clear();
}

void XMLParser::parse( const String& xmlString )
{
	currentNode_ = NULL;
	clearNodes();
	if ( ! xmlString.empty() ) {
		sourcePtr_ = xmlString.c_str();
		xmlBufferStart_ = sourcePtr_;
		sourceSize_ = xmlString.size();

		while ( nextNode() ) {

		}
	}
}

void XMLParser::parse( InputStream* stream )
{
	int sz = stream->getSize();

	if ( sz == 0 ) { //nothing to parse
		return;
	}

	char* tmpBuffer = new char[sz+1];
	memset( tmpBuffer, 0, (sz+1)*sizeof(char));

	stream->seek( 0, stSeekFromStart );
	stream->read( tmpBuffer, sz );

	String xmlText = tmpBuffer;

	delete [] tmpBuffer;

	parse( xmlText );
}

const VCFChar* XMLParser::skipWhitespace( const VCFChar* start, const int& length )
{
	const VCFChar* result = start;
	while ( ((result-start) < length) && (*result == ' ') || (*result == '\n') || (*result == '\t') || (*result == '\r') ) {
		result ++;
	}

	return result;
}

const VCFChar* XMLParser::skipTillWhitespace( const VCFChar* start, const int& length )
{
	const VCFChar* result = start;
	while ( ((result-start) < length) && (*result != ' ') && (*result != '\n') && (*result != '\t') && (*result != '\r') ) {
		result ++;
	}

	return result;
}

void XMLParser::parseEntity( const VCFChar* entityPtrStart, const VCFChar* entityPtrEnd )
{

}

bool XMLParser::nextNode()
{
	if ( sourceSize_ <= (sourcePtr_ - xmlBufferStart_) ) {
		return false;
	}

	const VCFChar* P = sourcePtr_;
	const VCFChar* tokenStart;
	while ( (*P != 0) && ((' ' == *P) || (13 == *P) || (10 == *P) || (9 == *P)) ) {
		P++;
	}

	tokenPtr_ = P;

	switch( *P ) {

		case ']' : {
			if ( dtdStarted_ ) {
				while ( (*P != XMLParser::TagClose) && (*P != 0) ) {
					P++;
				}

				P++;

				sourcePtr_ = P;
				dtdStarted_ = false;
				return true;
			}
		}
		break;

		case XMLParser::TagOpen : {
			P++;
			tokenStart = P;

			if ( *P == '?' ) {
				P++;

				//processing instructions - skip for now
				while ( (*P != '?') && (*P != 0) ) {
					P++;
				}
				if ( *P != '?' ) {
					throw RuntimeException( "Malformed XML processing node - end '?' expected, but none found." );
				}

				P++;
				P = skipWhitespace( P, sourceSize_-(P-sourcePtr_) );
				if ( *P != XMLParser::TagClose ) {
					throw RuntimeException( "Malformed XML processing node - end '>' expected, but none found." );
				}
				P++;

				sourcePtr_ = P;
				return true;

			}
			else if ( *P == '!' ) {
				//check for '!'

				P++;
				if ( (*P == '-') && (*(P+1) == '-') ) {
					P += 2;
					//comment
					const VCFChar* endComments = parseComments( P );
					P = endComments;
					P++;
					sourcePtr_ = P;
					return true;


				}

				String test;
				test.append( P, 25 );
				if ( test.find( "DOCTYPE" ) != String::npos ) {
					while ( ((*P != XMLParser::TagClose) && (*P != '[')) && (*P != 0) ) {
						P++;
					}
					if ( *P != XMLParser::TagClose ) {
						dtdStarted_ = true;
					}
					else {
						dtdStarted_ = false;
					}
					//skip over the doctype decl
					P++;
					sourcePtr_ = P;
					
					return true;

				}
				else if ( test.find( "ENTITY" ) != String::npos ) {
					P += 6;
					tokenStart = P;

					while ( (*P != XMLParser::TagClose) && (*P != 0) ) {
						P++;
					}

					parseEntity( tokenStart, P );

					P++;
					sourcePtr_ = P;
					return true;
				}
				else if ( test.find( "[CDATA[" ) != String::npos ) {
					P += 7;
					tokenPtr_ = P;

					while ( ((*P != ']') || (*(P+1) != ']') ||
							(*(P+2) != XMLParser::TagClose)) && (*P != 0) ) {
						P++;
					}

					tokenString_ = "";

					tokenString_.append( tokenPtr_, P - tokenPtr_ );
					if ( NULL != currentNode_ ) {
						currentNode_->setCDATA( currentNode_->getCDATA() + tokenString_ );
							XMLParserEvent event( this, currentNode_ );
							NodeCDATAFound.fireEvent( &event );
					}

					P+= 3;
				}
			}
			else {

				if ( *tokenStart != XMLParser::TagEnd ) {
					//parse the node for attributes

					XMLNode* node = new XMLNode("", currentNode_ );

					parsedNodes_.push_back( node );
					currentNode_ = node;
					P = parseNode( tokenStart, P+(sourceSize_-(P-sourcePtr_)) );
				}
				else {
					while ( (*P != XMLParser::TagClose) && (*P != 0) ) {
						P++;
					}
				}
				const VCFChar* endTag = P;
				endTag--;
				bool endTagFound = false;
				if ( *endTag == XMLParser::TagEnd ) {
					endTagFound = true;
				}

				//skip past the closing node
				P++;
				if ( true == endTagFound ) {
					P++;
					sourcePtr_ = P;
					if ( NULL != currentNode_ ) {
						currentNode_ = currentNode_->getParentNode();
					}
					return true;
				}
				else {
					if ( *tokenStart == XMLParser::TagEnd ) {
						sourcePtr_ = P;
						if ( NULL != currentNode_ ) {
							currentNode_ = currentNode_->getParentNode();
						}
						return true;
					}
				}
			}
		}
		break;

		default : {
			tokenString_ = "";
			//check for character data
			while ( (*P != '<') && ( (P - xmlBufferStart_ ) < sourceSize_) ) {
				P++;
			}

			tokenString_.append( tokenPtr_, P - tokenPtr_ );
			if ( NULL != currentNode_ ) {
				currentNode_->setCDATA( currentNode_->getCDATA() + decodeText( tokenString_ ) );
				XMLParserEvent event( this, currentNode_ );
				NodeCDATAFound.fireEvent( &event );
			}
		}
		break;

	}

	sourcePtr_ = P;
	return sourceSize_ > ( sourcePtr_ - xmlBufferStart_ );
}


const VCFChar* XMLParser::parseComments( const VCFChar* commentPtrStart )
{
	const VCFChar* result = NULL;
	bool commentsFinished = false;
	while ( (false == commentsFinished) && (sourceSize_ > ( commentPtrStart - xmlBufferStart_ )) ) {
		switch ( *commentPtrStart ) {
			case '-' : {
				const VCFChar* tmp = commentPtrStart;
				tmp++;
				if ( *tmp == '-' ) {
					tmp ++;
					if ( *tmp == XMLParser::TagClose ) {
						//poof - Elvis has left the building ! comments are finished
						commentPtrStart = tmp;
						commentsFinished = true;
					}
				}
			}
			break;
		}
		commentPtrStart++;
	}

	result = commentPtrStart;

	return result;
}

const VCFChar* XMLParser::parseNode( const VCFChar* nodePtrStart, const VCFChar* nodePtrEnd )
{
	const VCFChar* result = nodePtrStart;
	const VCFChar* start = nodePtrStart;

	start = skipWhitespace( start, nodePtrEnd-nodePtrStart );

	const VCFChar* P = start;
	const VCFChar* end = P;

	while ( (*end != XMLParser::TagClose) && (*end != XMLParser::TagEnd) && (*end != 0) ) {
		end++;
	}
	P = skipTillWhitespace( start, end-start );

	String s;
	s.append( start, P - start );
	currentNode_->setName( s );

	P = skipWhitespace( P, end-P );


	P = parseAttrs( P, nodePtrEnd );

	while ( (*P != XMLParser::TagClose) && (*P != 0) ) {
		P++;
	}

	result = P;

	XMLParserEvent event( this, currentNode_ );
	NodeFound.fireEvent( &event );

	return result;
}


const VCFChar* XMLParser::parseAttrs( const VCFChar* attrPtrStart, const VCFChar* attrPtrEnd )
{
	const VCFChar* result;

	currentNode_->clearAttrs();

	const VCFChar* P = skipWhitespace(attrPtrStart,attrPtrEnd-attrPtrStart);

	bool nextAttr = (P < attrPtrEnd) && (*P != XMLParser::TagClose) &&
			(*P != XMLParser::TagEnd) && (*P != XMLParser::TagOpen);
	while ( true == nextAttr ) {
		const VCFChar* nameStart = P;
		const VCFChar* assignmentStart = P;

		while ( ((' ' != *assignmentStart) && ('\n' != *assignmentStart) &&
					('\r' != *assignmentStart) && ('\t' != *assignmentStart)) &&
					(*assignmentStart != XMLParser::TagEquals) &&
					(assignmentStart < attrPtrEnd)  ) {

			assignmentStart++;
		}

		if ( *assignmentStart != XMLParser::TagEquals ) {
			assignmentStart = skipWhitespace( assignmentStart, attrPtrEnd-assignmentStart );
		}

		P = skipTillWhitespace( P, assignmentStart-P );

		String name;
		String value;
		name.append( nameStart, P - nameStart );

		P = assignmentStart;

		bool assignmentOperatorFound = false;
		switch ( *P ) {
			case XMLParser::TagEquals : {
				P++;
				P = skipWhitespace(P,attrPtrEnd-P);
				assignmentOperatorFound = true;
			}
			break;

			case 9 : case ' ' : case 10 : case 13: {
				while ( ((' ' == *P) || (13 == *P) || (10 == *P) || (9 == *P)) && (P < attrPtrEnd)  ) {
					P++;
				}
				if ( *P == XMLParser::TagEquals ) {
					P = skipWhitespace(P,attrPtrEnd-P);
					assignmentOperatorFound = true;
				}
			}
			break;
		}

		if ( true == assignmentOperatorFound ) {
			//goto the first quote
			while ( (*P != XMLParser::TagQuote) && (P < attrPtrEnd)  ) {
				P++;
			}
			if ( *P != XMLParser::TagQuote ) {
				throw RuntimeException( "Malformed XML Attribute - string literal expected, but no beginning quote (\") found." );
			}
			P++;
			const VCFChar* valueStart = P;

			//goto end quote
			while ( (*P != XMLParser::TagQuote) && (P < attrPtrEnd)  ) {
				P++;
			}

			if ( *P != XMLParser::TagQuote ) {
				throw RuntimeException( "Malformed XML Attribute - string literal expected, but no beginning quote (\") found." );
			}

			value.append( valueStart, P - valueStart );

			value = decodeText( value );

			currentNode_->addAttr( XMLAttr(name,value,currentNode_) );

			P++;

			//get rid of the white space
			P = skipWhitespace(P,attrPtrEnd-P);
		}
		else {
			throw RuntimeException( "Malformed XML Attribute" );
		}

		nextAttr = (P < attrPtrEnd) && (*P != XMLParser::TagClose) &&
			(*P != XMLParser::TagEnd) && (*P != XMLParser::TagOpen);
	}

	result = P;
	return result;
}




bool XMLParser::whiteSpace( const VCFChar& ch )
{
	return (ch == ' ') || (ch == '\n') || (ch == '\t') || (ch == '\r');
}

String XMLParser::decodeText( const String& text )
{
	String result ;

	const VCFChar* P = text.c_str();
	const VCFChar* start = P;
	const VCFChar* currentStart = P;
	int size = text.size();

	String entity;
	const VCFChar* entityStart = NULL;
	while ( (P-start) < size ) {
		switch ( *P ) {
			case '&' : {
				if ( *(P+1) != ';' ) {
					entityStart = P;
				}
				else {
					entityStart = NULL;
				}
			}
			break;

			case ';' : {
				if ( (*(P-1) != '&') && (NULL != entityStart) ) {

					result.append( currentStart, entityStart - currentStart );

					entityStart++;
					entityStart = skipWhitespace( entityStart, P-entityStart );

					const VCFChar* end = skipTillWhitespace( entityStart, P-entityStart );

					entity = "";
					entity.append( entityStart, end-entityStart );

					if ( entity[0] == '#' ) {

						int number = 0;
						String numRef = entity.substr(1,entity.size()-1);

						if( (numRef[0] == 'x') || (numRef[0] == 'X') ) {
							numRef.erase(0,1);
                            number = StringUtils::fromStringAsHexNumber( numRef );
						}
						else {
                            number = StringUtils::fromStringAsInt( numRef );
						}

						if( number >= 0 && number <= 255 ) {
							entity = String( sizeof(VCFChar),(VCFChar)number );
						}
						else {
							entity = StringUtils::toString( number );
						}
					}
					else {
						std::map<String,String>::iterator found = entityMap_.find( entity );
						if ( found != entityMap_.end() ) {
							entity = found->second;
						}
						else {
							entity = L"????";
						}
					}


					result.append( entity );

					currentStart = P+1;
				}
			}
			break;
		}
		P++;
	}

	if ( result.empty() ) {
		result = text;
	}
	else {
		if ( start != currentStart ) {
			result.append( currentStart, P - currentStart );
		}
	}

	return result;


}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/04/09 17:21:35  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/11/01 02:58:35  pallindo
*XMLNode's toString() now correctly writes out a node correctly if it just has CDATA.  It also now no longer writes out the final newline if it is the root node.
*
*Revision 1.2.2.1  2004/09/16 03:26:26  ddiego
*fixed it so we can now get program information from a resource bundle. This can be embedded in the exe like in windows, or read from an external file a la OS X info.plist xml files.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.1.2.3  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:26  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.13.4.1  2004/04/21 02:17:27  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.13  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.2.1  2003/10/30 20:08:17  ddiego
*fixed the xml parsing code to be more forgiving with attributes and
*to support the <![CDATA[ ]]> tag. also limited support for basic
*entities like &amp;, &lt;, and &quot;. Skipps over <?xml> tags
*and <!ENTITY> tags
*
*Revision 1.12  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.11.2.1  2003/08/06 21:28:03  ddiego
*minor changes
*
*Revision 1.11  2003/05/17 20:37:42  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:12:51  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.8.3  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.9.8.2  2003/01/08 00:19:55  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9.8.1  2002/11/28 05:12:05  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.9  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.8.6.3  2002/07/23 16:42:46  ddiego
*fixed bug in VCF::XMLNode::clearChildNodes that did not
*properly call the std::vector<>::clear() method !
*Damn do I feel STUPID !!!! oh well, at least it is
*fixed now
*
*Revision 1.8.6.2  2002/07/23 05:16:29  ddiego
*more config editing - having a problem with copying an XMLNode on the
*stack
*
*Revision 1.8.6.1  2002/07/22 04:36:09  ddiego
*added more config editing code
*added operator=() to VCF::XMLNode
*fixed copy ctor bug in XMLNode( const XMLNode& )
*
*Revision 1.8  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.3  2002/04/27 15:52:35  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.7.4.2  2002/03/25 04:19:46  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.7.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


