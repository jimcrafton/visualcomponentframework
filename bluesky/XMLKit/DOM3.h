#ifndef _VCF_DOM_H__
#define _VCF_DOM_H__

//DOM3.h

/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//#define XMLKIT_DOM

#ifdef XMLKIT_DOM  


#define readonly 
#define attribute
#define in

/**
implemented from http://www.w3.org/TR/2004/REC-DOM-Level-3-Core-20040407/core.html
*/
namespace VCF {

	namespace DOM {

	typedef String DOMString;
	typedef uint64 DOMTimeStamp;
	typedef VariantData DOMUserData;
	typedef Object DOMObject;

	/**
	\class DOMException DOM3.h "vcf/FoundationKit/DOM3.h"
	*/
	class DOMException : public BasicException {
	public:

		enum {
			INDEX_SIZE_ERR                 = 1,
			DOMSTRING_SIZE_ERR             = 2,
			HIERARCHY_REQUEST_ERR          = 3,
			WRONG_DOCUMENT_ERR             = 4,
			INVALID_CHARACTER_ERR          = 5,
			NO_DATA_ALLOWED_ERR            = 6,
			NO_MODIFICATION_ALLOWED_ERR    = 7,
			NOT_FOUND_ERR                  = 8,
			NOT_SUPPORTED_ERR              = 9,
			INUSE_ATTRIBUTE_ERR            = 10,
			// Introduced in DOM Level 2:
			INVALID_STATE_ERR              = 11,
			// Introduced in DOM Level 2:
			SYNTAX_ERR                     = 12,
			// Introduced in DOM Level 2:
			INVALID_MODIFICATION_ERR       = 13,
			// Introduced in DOM Level 2:
			NAMESPACE_ERR                  = 14,
			// Introduced in DOM Level 2:
			INVALID_ACCESS_ERR             = 15,
			// Introduced in DOM Level 3:
			VALIDATION_ERR                 = 16,
			// Introduced in DOM Level 3:
			TYPE_MISMATCH_ERR              = 17,
		};

		DOMException():
		  BasicException( "" ){};
		  
		DOMException( const String & message ):
		  BasicException( message ){};
		  
		DOMException( const String & message, const int lineNumber ):
			BasicException(message, lineNumber){};

		DOMException( int errorCode ):
		  BasicException(""), code(errorCode){};

		virtual ~DOMException() throw() {};
		
		unsigned short getDOMErrorCode() const {
			return code;
		}

		void setDOMErrorCode( unsigned short val ) {
			code = val;
		}

	protected:
		unsigned short   code;
	};



	class DOMStringList : public Object {
	public:

		DOMStringList(){}
		DOMStringList( const std::vector<DOMString>& data ): data_(data){}


		DOMString item( size_t index) const {
			if ( index >= data_.size() ) {
				return "";
			}
			return data_[index];
		}

		size_t length() const {
			return data_.size();
		}

		bool contains( const DOMString& str) const {
			std::vector<DOMString>::const_iterator it = data_.begin();
			while ( it != data_.end() ) {
				if ( (*it).find( str ) != String::npos ) {
					return true;
				}
				++it;
			}

			return false;
		}
	protected:
		std::vector<DOMString> data_;
	};



	class NameList : public Object {
	public:
		typedef std::pair<DOMString,DOMString> Value;

		NameList(){}
		NameList( const std::vector<Value>& data ): data_(data){}


		DOMString getName(size_t index) const {
			if ( index >= data_.size() ) {
				return "";
			}

			return data_[index].first;
		}

		DOMString getNamespaceURI(size_t index) const {
			if ( index >= data_.size() ) {
				return "";
			}

			return data_[index].second;
		}

		size_t length() const {
			return data_.size();
		}

		bool contains( const DOMString& str) const {
			std::vector<Value>::const_iterator it = data_.begin();
			while ( it != data_.end() ) {
				if ( (*it).first.find( str ) != String::npos ) {
					return true;
				}
				++it;
			}

			return false;
		}

		bool containsNS(const DOMString& namespaceURI, const DOMString& name) {
			std::vector<Value>::const_iterator it = data_.begin();
			while ( it != data_.end() ) {
				if ( (*it).second.find( namespaceURI ) != String::npos
					&& (*it).first.find( name ) != String::npos ) {
					return true;
				}
				++it;
			}

			return false;
		}

	protected:
		std::vector<Value> data_;
	};



	class TypeInfo {
	public:
		// DerivationMethods
		enum DerivationMethods {
			DERIVATION_RESTRICTION         = 0x00000001,
			DERIVATION_EXTENSION           = 0x00000002,
			DERIVATION_UNION               = 0x00000004,
			DERIVATION_LIST                = 0x00000008
		};

		readonly attribute DOMString typeName() const {
			return name_;
		}

		readonly attribute DOMString typeNamespace() const {
			return namespace_;
		}
		
		
		
		bool isDerivedFrom(const DOMString& typeNamespaceArg, 
							const DOMString& typeNameArg, 
							int derivationMethod ) const ;

	protected:
		DOMString name_;
		DOMString namespace_;
	};




	class DOMImplementation;

	class DOMImplementationList : public Object {
	public:
		DOMImplementation*  item(size_t index) const {
			if ( index >= data_.size() ) {
				return NULL;
			}

			return data_[index];
		}

		size_t length() const {
			return data_.size();
		}
	protected:
		std::vector<DOMImplementation*> data_;
	};


	class DOMImplementationSource : public Object {
	public:

		void addList( const DOMString& features, const DOMImplementationList& list ) {
			data_[features] = list;
		}

		DOMImplementation* getDOMImplementation( const DOMString& features);		

		DOMImplementationList* getDOMImplementationList( const DOMString& features) {
			DOMImplementationList* result = NULL;
			std::map<DOMString,DOMImplementationList>::iterator found = 
				data_.find( features );
			if ( found != data_.end() ) {
				DOMImplementationList& list = found->second;
				result = &list;
			}

			return result;
		}

	protected:
		std::map<DOMString,DOMImplementationList> data_;
	};


	class DocumentType;
	class Document;
	class NodeList;
	class NamedNodeMap;
	class UserDataHandler;


	class DOMImplementation : public Object {
	public:

		void registerFeature(const DOMString& feature, const DOMString& version, DOMObject* featureImpl); 

		bool hasFeature(const DOMString& feature, const DOMString& version);
		// Introduced in DOM Level 2:
		DocumentType* createDocumentType(const DOMString& qualifiedName, 
												const DOMString& publicId, 
												const DOMString& systemId);//raises(DOMException);
		// Introduced in DOM Level 2:
		Document* createDocument(const DOMString& namespaceURI, 
								const DOMString& qualifiedName, 
								const DocumentType& doctype);//raises(DOMException);
		// Introduced in DOM Level 3:
		DOMObject* getFeature(const DOMString& feature, const DOMString& version);
	protected:
		std::map<DOMString,DOMObject*> features_;
	};



	class Node : public Object {
	public:
		// NodeType
		enum NodeType {
			ELEMENT_NODE                   = 1,
			ATTRIBUTE_NODE                 = 2,
			TEXT_NODE                      = 3,
			CDATA_SECTION_NODE             = 4,
			ENTITY_REFERENCE_NODE          = 5,
			ENTITY_NODE                    = 6,
			PROCESSING_INSTRUCTION_NODE    = 7,
			COMMENT_NODE                   = 8,
			DOCUMENT_NODE                  = 9,
			DOCUMENT_TYPE_NODE             = 10,
			DOCUMENT_FRAGMENT_NODE         = 11,
			NOTATION_NODE                  = 12
		};

		// DocumentPosition
		enum DocumentPosition {
			DOCUMENT_POSITION_DISCONNECTED = 0x01,
			DOCUMENT_POSITION_PRECEDING    = 0x02,
			DOCUMENT_POSITION_FOLLOWING    = 0x04,
			DOCUMENT_POSITION_CONTAINS     = 0x08,
			DOCUMENT_POSITION_CONTAINED_BY = 0x10,
			DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20,
		};
		
		readonly attribute DOMString nodeName() const;
		attribute DOMString nodeValue();
		// raises(DOMException) on setting
		// raises(DOMException) on retrieval
		
		readonly attribute unsigned short  nodeType() const;
		readonly attribute Node* parentNode() const;
		readonly attribute NodeList* childNodes() const;
		readonly attribute Node* firstChild() const;
		readonly attribute Node* lastChild() const ;
		readonly attribute Node* previousSibling() const;
		readonly attribute Node* nextSibling() const;
		readonly attribute NamedNodeMap* attributes() const;
		// Modified in DOM Level 2:
		readonly attribute Document* ownerDocument();
		// Modified in DOM Level 3:
		Node* insertBefore(in Node* newChild, in Node* refChild);//raises(DOMException);
		// Modified in DOM Level 3:
		Node* replaceChild(in Node* newChild, in Node* oldChild);//raises(DOMException);
		// Modified in DOM Level 3:
		Node* removeChild(in Node* oldChild);//raises(DOMException);
		// Modified in DOM Level 3:
		Node* appendChild(in Node* newChild);//raises(DOMException);

		bool hasChildNodes();

		Node* cloneNode(in bool deep);

		// Modified in DOM Level 3:
		void normalize();

		// Introduced in DOM Level 2:
		bool isSupported(const DOMString& feature, const DOMString& version);

		// Introduced in DOM Level 2:
		readonly attribute DOMString namespaceURI() const;
		// Introduced in DOM Level 2:
		attribute DOMString prefix() const;
		// raises(DOMException) on setting
		
		// Introduced in DOM Level 2:
		readonly attribute DOMString localName();
		// Introduced in DOM Level 2:
		bool            hasAttributes();
		// Introduced in DOM Level 3:
		readonly attribute DOMString baseURI();
		
		
		
		// Introduced in DOM Level 3:
		unsigned short compareDocumentPosition(in Node* other);//raises(DOMException);
		// Introduced in DOM Level 3:
		attribute DOMString textContent();
		// raises(DOMException) on setting
		// raises(DOMException) on retrieval
		
		// Introduced in DOM Level 3:
		bool isSameNode(const Node* other);
		// Introduced in DOM Level 3:
		DOMString lookupPrefix(const DOMString& namespaceURI);
		// Introduced in DOM Level 3:
		bool isDefaultNamespace(const DOMString& namespaceURI);
		// Introduced in DOM Level 3:
		DOMString          lookupNamespaceURI(const DOMString& prefix);
		// Introduced in DOM Level 3:
		bool isEqualNode(const Node* arg);
		// Introduced in DOM Level 3:
		DOMObject* getFeature(const DOMString& feature, 
			const DOMString& version);
		// Introduced in DOM Level 3:
		DOMUserData* setUserData(const DOMString& key, const DOMUserData& data, in UserDataHandler* handler);
		// Introduced in DOM Level 3:
		DOMUserData* getUserData(const DOMString& key);
	};



	class DocumentFragment : public Node {

	};


	class Element;
	class Text;
	class Comment;
	class CDATASection;
	class ProcessingInstruction;
	class Attr;
	class EntityReference;
	class NodeList;
	class DOMConfiguration;


	class Document : public Node {
	public:

		// Modified in DOM Level 3:
		DocumentType* doctype();
		
		DOMImplementation* implementation();
		
		Element* documentElement();
		
		Element* createElement(const DOMString& tagName);//raises(DOMException);
		
		DocumentFragment* createDocumentFragment();
		
		Text* createTextNode(const DOMString& data);
		
		Comment* createComment(const DOMString& data);
		
		CDATASection*       createCDATASection(const DOMString& data);//raises(DOMException);

		ProcessingInstruction* createProcessingInstruction(const DOMString& target, const DOMString& data);//raises(DOMException);

		Attr* createAttribute(const DOMString& name);//raises(DOMException);

		EntityReference* createEntityReference(const DOMString& name);//			raises(DOMException);

		NodeList* getElementsByTagName(const DOMString& tagname);
		
		// Introduced in DOM Level 2:
		Node* importNode(const Node& importedNode,bool deep);//raises(DOMException);

		// Introduced in DOM Level 2:
		Element* createElementNS(const DOMString& namespaceURI, const DOMString& qualifiedName);//raises(DOMException);

		// Introduced in DOM Level 2:
		Attr* createAttributeNS(const DOMString& namespaceURI, const DOMString& qualifiedName);//raises(DOMException);

		// Introduced in DOM Level 2:
		NodeList* getElementsByTagNameNS(const DOMString& namespaceURI, const DOMString& localName);

		// Introduced in DOM Level 2:
		Element* getElementById(const DOMString& elementId);

		// Introduced in DOM Level 3:
		DOMString inputEncoding();

		// Introduced in DOM Level 3:
		DOMString       xmlEncoding();
		// Introduced in DOM Level 3:
		bool xmlStandalone();
		// raises(DOMException) on setting
		
		// Introduced in DOM Level 3:
		DOMString xmlVersion();
		// raises(DOMException) on setting
		
		// Introduced in DOM Level 3:
		bool strictErrorChecking();
		// Introduced in DOM Level 3:
		DOMString documentURI();
		// Introduced in DOM Level 3:
		Node* adoptNode(const Node& source);//raises(DOMException);
		// Introduced in DOM Level 3:
		DOMConfiguration* domConfig();
		// Introduced in DOM Level 3:
		void normalizeDocument();
		// Introduced in DOM Level 3:
		Node* renameNode(const Node& n, const DOMString& namespaceURI, const DOMString& qualifiedName);//raises(DOMException);
	};



	class NodeList : public Object {
	public:
		NodeList(){}

		NodeList( const std::vector<Node*>& nodes ):data_(nodes){}

		Node* item(in size_t index) const {
			if ( index >= data_.size() ) {
				return NULL;
			}
			return data_[index];
		}

		size_t length() const {
			return data_.size();
		}

	protected:
		std::vector<Node*> data_;
	};



	class NamedNodeMap : public Object {
	public:

		Node* getNamedItem(const DOMString& name) const {
			Node* result = NULL;
			std::map<DOMString,Node*>::const_iterator found = data_.find( name );
			if ( found != data_.end() ) {
				result = found->second;
			}

			return result;
		}

		Node* setNamedItem(Node* arg) {//raises(DOMException);
			Node* result = NULL;

			DOMString name = arg->nodeName();

			result = getNamedItem( name );
			data_[name] = arg;

			return result;
		}

		Node* removeNamedItem(const DOMString& name) { //raises(DOMException);
			Node* result = NULL;
		
			std::map<DOMString,Node*>::iterator found = data_.find( name );
			if ( found != data_.end() ) {
				result = found->second;
				data_.erase( found );
			}
			else {
				throw DOMException( DOMException::NOT_FOUND_ERR );
			}

			return result;
		}

		Node* item(size_t index) const {
			if ( index >= data_.size() ) {
				return NULL;
			}

			Node* result = NULL;
			std::map<DOMString,Node*>::const_iterator it = data_.begin();
			size_t pos = 0;
			while ( pos != index ) {
				++it;
				pos ++;
			}
			if ( it != data_.end() ) {
				result = it->second;
			}
			return result;
		}

		readonly attribute size_t length() const {
			return data_.size();
		}

		// Introduced in DOM Level 2:
		Node* getNamedItemNS(const DOMString& namespaceURI, const DOMString& localName) const {//raises(DOMException);
			Node* result = NULL;

			DOMString name = localName + "(" + namespaceURI + ")";

			std::map<DOMString,Node*>::const_iterator found = data_.find( name );
			if ( found != data_.end() ) {				
				result = found->second;
				if ( localName != result->localName() || namespaceURI != result->namespaceURI() ) {
					result = NULL;
				}
			}		

			return result;
		}

		// Introduced in DOM Level 2:
		Node* setNamedItemNS(Node* arg) {
			Node* result = NULL;

			DOMString name = arg->nodeName();
			DOMString ns = arg->namespaceURI();

			result = getNamedItemNS( ns, name );

			name = name + "(" + ns + ")";

			data_[name] = arg;

			return result;
		}

		// Introduced in DOM Level 2:
		Node* removeNamedItemNS(const DOMString& namespaceURI, const DOMString& localName) {// raises(DOMException);
			Node* result = NULL;

			DOMString name = localName + "(" + namespaceURI + ")";

			std::map<DOMString,Node*>::iterator found = data_.find( name );
			if ( found != data_.end() ) {				
				result = found->second;
				if ( localName != result->localName() || namespaceURI != result->namespaceURI() ) {
					result = NULL;
				}
			}
			
			if ( result != NULL ) {
				data_.erase( found );
			}
			else {
				throw DOMException( DOMException::NOT_FOUND_ERR );
			}
		}
	protected:
		std::map<DOMString,Node*> data_;
	};



	class CharacterData : public Node {
	public:
		attribute DOMString data() const;
		// raises(DOMException) on setting
		// raises(DOMException) on retrieval
		
		readonly attribute size_t length() const;

		DOMString substringData(in size_t offset, in size_t count);//raises(DOMException);

		void appendData(const DOMString& arg);//raises(DOMException);

		void insertData(in size_t offset, in const DOMString& arg);//raises(DOMException);

		void deleteData(in size_t offset, in size_t count);//raises(DOMException);

		void replaceData(in size_t offset, in size_t count, in const DOMString& arg);//raises(DOMException);
	};


	

	class Attr : public Node {
		readonly attribute DOMString name() const;

		readonly attribute bool specified() const;

		attribute DOMString value() const;
		// raises(DOMException) on setting
		
		// Introduced in DOM Level 2:
		readonly attribute Element* ownerElement();
		// Introduced in DOM Level 3:
		readonly attribute TypeInfo* schemaTypeInfo();
		// Introduced in DOM Level 3:
		readonly attribute bool isId() const;
	};


	class Element : public Node {
		readonly attribute DOMString tagName() const ;

		DOMString getAttribute(const DOMString& name);

		void setAttribute(const DOMString& name, const DOMString& value);//raises(DOMException);

		void removeAttribute(const DOMString& name);// raises(DOMException);

		Attr* getAttributeNode(const DOMString& name);

		Attr* setAttributeNode(Attr* newAttr);// raises(DOMException);

		Attr* removeAttributeNode(Attr* oldAttr);// raises(DOMException);

		NodeList getElementsByTagName(const DOMString& name) const;

		// Introduced in DOM Level 2:
		DOMString getAttributeNS(const DOMString& namespaceURI, const DOMString& localName);// raises(DOMException);

		// Introduced in DOM Level 2:
		void setAttributeNS(const DOMString& namespaceURI, 
							const DOMString& qualifiedName, 
							const DOMString& value);//raises(DOMException);

		// Introduced in DOM Level 2:
		void removeAttributeNS(const DOMString& namespaceURI, const DOMString& localName);//raises(DOMException);

		// Introduced in DOM Level 2:
		Attr* getAttributeNodeNS(const DOMString& namespaceURI, const DOMString& localName);//raises(DOMException);

		// Introduced in DOM Level 2:
		Attr* setAttributeNodeNS(Attr* newAttr);//raises(DOMException);

		// Introduced in DOM Level 2:
		NodeList getElementsByTagNameNS(const DOMString& namespaceURI,const DOMString& localName);//raises(DOMException);

		// Introduced in DOM Level 2:
		bool hasAttribute(const DOMString& name);

		// Introduced in DOM Level 2:
		bool hasAttributeNS(const DOMString& namespaceURI, const DOMString& localName);// raises(DOMException);

		// Introduced in DOM Level 3:
		readonly attribute TypeInfo* schemaTypeInfo() const;

		// Introduced in DOM Level 3:
		void setIdAttribute(const DOMString& name, in bool isId);//raises(DOMException);

		// Introduced in DOM Level 3:
		void setIdAttributeNS(const DOMString& namespaceURI, const DOMString& localName, in bool isId);//raises(DOMException);

		// Introduced in DOM Level 3:
		void setIdAttributeNode(Attr* idAttr, in bool isId);//raises(DOMException);
	};



	class Text : public CharacterData {
	public:

		Text* splitText(in unsigned long offset);//raises(DOMException);

		// Introduced in DOM Level 3:
		readonly attribute bool isElementContentWhitespace() const;

		// Introduced in DOM Level 3:
		readonly attribute DOMString wholeText() const;

		// Introduced in DOM Level 3:
		Text* replaceWholeText(const DOMString& content);//raises(DOMException);
	};


	class Comment : public CharacterData {
	public:
	};

	
	class UserDataHandler {
		
		// OperationType
		enum OperationType {
			NODE_CLONED                    = 1,
			NODE_IMPORTED                  = 2,
			NODE_DELETED                   = 3,
			NODE_RENAMED                   = 4,
			NODE_ADOPTED                   = 5,
		};
		
		virtual void handle( unsigned short operation, 
					const DOMString& key, 
					const DOMUserData& data,
					in Node* src,
					in Node* dst ) = 0;
	};


	class DOMLocator;


	class DOMError : public Object {
	public:
		// ErrorSeverity
		enum ErrorSeverity {
			SeverityWarning = 1,
			SeverityError = 2,
			SeverityFatalError = 3,
		};
		

		unsigned short severity() const;
		DOMString message() const ;
		DOMString type() const ;
		DOMObject* relatedException() const;
		DOMObject* relatedData() const ;
		DOMLocator* location() const ;
	};


	class DOMErrorHandler {
	public:

		virtual bool handleError(in DOMError error) = 0;
	};


	class DOMLocator {
	public:
		long lineNumber;
		long columnNumber;
		long byteOffset;
		long utf16Offset;
		Node* relatedNode;
		DOMString uri;
	};


	class DOMConfiguration {
	public:
		void setParameter(const DOMString& name, const DOMUserData& value);// raises(DOMException);
		DOMUserData getParameter(const DOMString& name);// raises(DOMException);

		bool canSetParameter(const DOMString& name, const DOMUserData& value);

		DOMStringList parameterNames() const;
	};

	
	class CDATASection : public Text {
	};
	
	class DocumentType : public Node {
	public:
		DOMString name() const {
			return name_;
		}

		const NamedNodeMap& entities() const {
			return entities_;
		}

		const NamedNodeMap& notations() const {
			return notations_;
		}

		DOMString publicId() const {
			return publicId_;
		}

		DOMString systemId() const {
			return systemId_;
		}

		DOMString internalSubset() const {
			return internalSubset_;
		}
	protected:
		DOMString name_;
		NamedNodeMap entities_;
		NamedNodeMap notations_;

		// Introduced in DOM Level 2:
		DOMString publicId_;

		// Introduced in DOM Level 2:
		DOMString systemId_;

		// Introduced in DOM Level 2:
		DOMString internalSubset_;
	};


	class Notation : public Node {
	public:

		DOMString       publicId;
		DOMString       systemId;
	};

	class Entity : public Node {
	public:
		DOMString publicId() const ;
		DOMString systemId() const;

		DOMString notationName() const;

		// Introduced in DOM Level 3:
		DOMString inputEncoding() const ;

		// Introduced in DOM Level 3:
		DOMString xmlEncoding() const;

		// Introduced in DOM Level 3:
		DOMString xmlVersion() const;
	};


	class EntityReference : public Node {
	};

	class ProcessingInstruction : public Node {
		readonly attribute DOMString target() const ;
		attribute DOMString data() const;
		// raises(DOMException) on setting
		
	};

	}; //namespace DOM
};



#undef readonly 
#undef attribute
#undef in

#endif //XMLKIT_DOM

#endif //_VCF_DOM_H__