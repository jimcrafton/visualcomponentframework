//Trees2.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/XMLKit/XMLKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TreeModel.h"
#include "vcf/ApplicationKit/TreeControl.h"


using namespace VCF;



class XMLTreeModel : public TreeModel {
public:

	String getNodeString( const XmlNode& n ) {
		String result;

		result = n.getName();

		if ( n.getType() == ntAttribute ) {
			result += ":" + n.getContent();
		}
		else if ( n.getType() == ntCDATA ) {
			result += " CDATA:";
			String s = n.getContent();
			if ( s.length() > 25 ) {
				result += s.substr(0,25) + "...";
			}
			else {
				result += s;
			}
		}
		else if ( n.getType() == ntText ) {
			if ( !n.empty() ) {
				result += ":";
				String s = n.getContent();
				if ( s.length() > 25 ) {
					result += s.substr(0,25) + "...";
				}
				else {
					result += s;
				}
			}
		}

		return result;			
	}

	virtual VariantData get( const Key& key ) {
		if ( key == RootKey ) {
			return VariantData(getNodeString(root));
		}

		XmlNode n( (XmlNode::ValueT) key );

		return VariantData(getNodeString(n));
	}

	virtual bool getChildren(const Key& key, std::vector<Key>& children ) {		
		XmlNode::ValueT val;

		if ( key == RootKey ) {
			val = root.get();
		}
		else {
			val = (XmlNode::ValueT) key;
		}

		XmlNode n(val);
		std::vector<XmlNode> nodes;
		n.getChildren( nodes );
		std::vector<XmlNode>::iterator it = nodes.begin();
		children.resize( nodes.size() );
		size_t i = 0;
		while ( it != nodes.end() ) {
			const XmlNode& child = *it;
			children[i] = (Key) child.get();
			i++;
			++it;
		}
		return !children.empty();
	}


	virtual Key getParent( const Key& key ) {
		if ( key == RootKey ) {
			return (Key) root.get();
		}

		XmlNode n( (XmlNode::ValueT) key );
		return (Key) n.get();
	}

	virtual Key getNextSibling( const Key& key ) {
		Key k = InvalidKey;

		XmlNode::ValueT val;

		if ( key == RootKey ) {
			val = root.get();
		}
		else {
			val = (XmlNode::ValueT) key;
		}

		XmlNode n(val);

		XmlNode p = n.getParent();

		if ( !p.isNull() ) {
			std::vector<XmlNode> nodes;
			p.getChildren( nodes );
			std::vector<XmlNode>::iterator it = nodes.begin();
			
			while ( it != nodes.end() ) {
				const XmlNode& child = *it;
				
				if ( (Key)child.get() == key ) {
					++it;
					if ( it != nodes.end() ) {
						k = (Key)(*it).get();
						break;
					}
				}
					
				++it;
			}
		}


		return k;
	}

	virtual Key getPrevSibling( const Key& key ) {
		Key k = InvalidKey;

		XmlNode::ValueT val;

		if ( key == RootKey ) {
			val = root.get();
		}
		else {
			val = (XmlNode::ValueT) key;
		}

		XmlNode n(val);

		XmlNode p = n.getParent();

		if ( !p.isNull() ) {
			std::vector<XmlNode> nodes;
			p.getChildren( nodes );
			std::vector<XmlNode>::iterator it = nodes.begin();
			
			while ( it != nodes.end() ) {
				const XmlNode& child = *it;
				
				if ( ((Key)child.get() == key) && it != nodes.begin() ) {
					--it;					
					k = (Key)(*it).get();
					break;					
				}
					
				++it;
			}
		}


		return k;
	}

	virtual Key getFirstChild( const Key& key ) {
		Key k = InvalidKey;
		XmlNode::ValueT val;

		if ( key == RootKey ) {
			val = root.get();
		}
		else {
			val = (XmlNode::ValueT) key;
		}

		XmlNode n(val);
		std::vector<XmlNode> nodes;
		n.getChildren( nodes );
		if ( !nodes.empty() ) {
			k = (Key) nodes.front().get();
		}

		return k;
	}

	virtual bool isLeaf( const Key& key ) {
		Key k = InvalidKey;
		XmlNode::ValueT val;

		if ( key == RootKey ) {
			val = root.get();
		}
		else {
			val = (XmlNode::ValueT) key;
		}

		XmlNode n(val);
		return !n.hasChildren();
	}

	virtual uint32 getCount() {
		return calcSize(root);
	}

	virtual uint32 getChildCount( const Key& key ) {		
		XmlNode::ValueT val;

		if ( key == RootKey ) {
			val = root.get();
		}
		else {
			val = (XmlNode::ValueT) key;
		}

		XmlNode n(val);
		return n.getChildCount();
	}



	size_t calcSize( const XmlNode& n ) {
		size_t result = n.getChildCount();
		if ( n.hasChildren() ) {
			std::vector<XmlNode> nodes;
			n.getChildren( nodes );
			std::vector<XmlNode>::iterator it = nodes.begin();
			
			while ( it != nodes.end() ) {
				result += calcSize( *it );
				++it;
			}
		}
	
		return result;
	}
	
	XmlNode root;

protected:
	
};


class Trees2Wnd : public Window {
public:
	Trees2Wnd() {
		setCaption( "Trees2" );		
	}

	virtual ~Trees2Wnd(){};

};



_class_rtti_(Trees2Wnd, "VCF::Window", "Trees2Wnd")
_class_rtti_end_


class Trees2Application : public Application {
public:

	Trees2Application( int argc, char** argv ) : Application(argc, argv) {
		XMLKit::init( argc, argv );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(Trees2Wnd);

		Window* mainWindow = Frame::createWindow( classid(Trees2Wnd) );
		setMainWindow(mainWindow);
		mainWindow->show();
		

		TreeControl* treeCtrl = (TreeControl*)mainWindow->findComponent( "treeCtrl", true );

		XmlDocument doc;
		doc.load( "books.xml"); 


		XMLTreeModel* tm = new XMLTreeModel();
		XmlNode* root = (XmlNode*)doc.getRoot().clone();

		tm->root.attach( root->detach() );

		delete root;

		treeCtrl->setTreeModel( tm );

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new Trees2Application( argc, argv );

	Application::main();
	
	XMLKit::terminate();

	return 0;
}


