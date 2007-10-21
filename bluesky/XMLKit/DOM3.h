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


#define readonly 
#define attribute
#define in

/**
implemented from http://www.w3.org/TR/2004/REC-DOM-Level-3-Core-20040407/core.html
*/
namespace VCF {

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

		DOMImplementation* getDOMImplementation( const DOMString& features);

		DOMImplementationList* getDOMImplementationList( const DOMString& features);
	};


	class DocumentType;
	class Document;


	class DOMImplementation : public Object {
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
	};



	class Node : public Object {
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
		bool            hasChildNodes();
		Node               cloneNode(in bool deep);
		// Modified in DOM Level 3:
		void               normalize();
		// Introduced in DOM Level 2:
		bool            isSupported(in DOMString feature, 
			in DOMString version);
		// Introduced in DOM Level 2:
		readonly attribute DOMString       namespaceURI;
		// Introduced in DOM Level 2:
		attribute DOMString       prefix;
		// raises(DOMException) on setting
		
		// Introduced in DOM Level 2:
		readonly attribute DOMString       localName;
		// Introduced in DOM Level 2:
		bool            hasAttributes();
		// Introduced in DOM Level 3:
		readonly attribute DOMString       baseURI;
		
		
		
		// Introduced in DOM Level 3:
		unsigned short     compareDocumentPosition(in Node other)
			raises(DOMException);
		// Introduced in DOM Level 3:
		attribute DOMString       textContent;
		// raises(DOMException) on setting
		// raises(DOMException) on retrieval
		
		// Introduced in DOM Level 3:
		bool            isSameNode(in Node other);
		// Introduced in DOM Level 3:
		DOMString          lookupPrefix(in DOMString namespaceURI);
		// Introduced in DOM Level 3:
		bool            isDefaultNamespace(in DOMString namespaceURI);
		// Introduced in DOM Level 3:
		DOMString          lookupNamespaceURI(in DOMString prefix);
		// Introduced in DOM Level 3:
		bool            isEqualNode(in Node arg);
		// Introduced in DOM Level 3:
		DOMObject          getFeature(in DOMString feature, 
			in DOMString version);
		// Introduced in DOM Level 3:
		DOMUserData        setUserData(in DOMString key, 
			in DOMUserData data, 
			in UserDataHandler handler);
		// Introduced in DOM Level 3:
		DOMUserData        getUserData(in DOMString key);
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
};



#endif //_VCF_DOM_H__