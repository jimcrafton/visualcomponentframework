//Trees2.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/XMLKit/XMLKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TreeModel.h"
#include "vcf/ApplicationKit/TreeControl.h"


using namespace VCF;



class XMLTreeModel : public TreeModel {
public:
	virtual Key insert( const VariantData& value, const Key& parentKey=RootKey ) {
		Key result;

		return result;
	}

	virtual void remove( const Key& key ){}

	virtual VariantData get( const Key& key ) {
		const XmlNode* n = keyMap[key];
		VariantData v = n->getName() ;
		return v;
	}

	virtual String getAsString( const Key& key ) {
		const XmlNode* n = keyMap[key];
		return n->getName();
	}

	virtual void set( const Key& key, const VariantData& value ) {
		
	}

	virtual void setAsString( const Key& key, const String& value ) {

	}

	virtual void copy( const Key& srcKey, const Key& destKey, bool deepCopy=false ) {

	}

	virtual void move( const Key& srcKey, const Key& destParentKey ) {

	}

	virtual void clearChildren( const Key& key ) {

	}

	virtual bool getChildren(const Key& key, std::vector<Key>& children ) {
		

	}


	virtual Key getParent( const Key& key ) {

	}

	virtual Key getNextSibling( const Key& key ) {
		Key k;
		return k;
	}

	virtual Key getPrevSibling( const Key& key ) {
		Key k;
		return k;
	}

	virtual Key getFirstChild( const Key& key ) {
		Key k;
		return k;
	}

	virtual bool isLeaf( const Key& key ) {
		return true;
	}

	virtual uint32 getCount() {
		return 0;
	}

	virtual uint32 getChildCount( const Key& key ) {
		return 0;
	}


	void buildMap( const XmlNode& n ) {
		keyMap[counter] = &n;
		counter ++;
		std::vector<XmlNode> nodes;
		n.getChildren(nodes);
		for (size_t i=0;i<nodes.size();i++ ) {
			buildMap(nodes[i]);
		}
	}

	void initKeyMap() {
		counter = RootKey;
		buildMap(root);
	}

	std::map<Key,const XmlNode*> keyMap;
	uint32 counter;

	XmlNode root;
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

		XMLTreeModel* tm = new XMLTreeModel();
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


