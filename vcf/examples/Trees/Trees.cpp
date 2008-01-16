//Trees.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/TreeControl.h"

using namespace VCF;






class HiResClock {
public:

	HiResClock(){
		QueryPerformanceFrequency( &frequency_ );
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}



	void start() {
		QueryPerformanceCounter( &performanceCounter1_ );
	}

	void stop() {
		QueryPerformanceCounter( &performanceCounter2_ );
	}

	void clear() {
		memset( &performanceCounter1_, 0, sizeof(performanceCounter1_) );
		memset( &performanceCounter2_, 0, sizeof(performanceCounter2_) );
	}

	operator double() const {
		return duration();
	}

	double duration() const {
		return (double)(performanceCounter2_.LowPart - performanceCounter1_.LowPart)/(double)frequency_.LowPart;
	}
protected:
	LARGE_INTEGER frequency_;
	LARGE_INTEGER performanceCounter1_;
	LARGE_INTEGER performanceCounter2_;
private:
	HiResClock( const HiResClock& rhs );


	HiResClock& operator=( const HiResClock& rhs );
};









#define TREESWINDOW_CLASSID		"6d549178-fc6d-4942-9828-6e7314d8be4f"


class TreesWindow : public Window {
public:
};

_class_rtti_(TreesWindow, "VCF::Window", TREESWINDOW_CLASSID)
_class_rtti_end_





struct TreeValRef {

	TreeValRef(): parent(NULL),nextSibling(NULL),prevSibling(NULL){}

	VariantData data;
	TreeModel::Key key;

	TreeValRef* parent;
	TreeValRef* nextSibling;
	TreeValRef* prevSibling;
};


typedef std::map<TreeModel::Key,TreeValRef> TrMap;
typedef std::multimap<TreeModel::Key,TreeModel::Key> ParentChildMap;
typedef ParentChildMap::value_type PCVal;
typedef std::pair<ParentChildMap::iterator,ParentChildMap::iterator> PCRange;

class TrModel {
public:

	TreeModel::Key add( const VariantData& v, TreeModel::Key parent ) {
		static uint32 lastKey = 0;

		lastKey ++;

		TreeValRef ref;
		ref.key = lastKey;
		ref.data = v;


		TrMap::iterator found = data.find( parent );
		if ( found != data.end() ) {
			TreeValRef& pr = found->second;

			ref.parent = &pr;
		}	


		PCRange range = pcData.equal_range( parent );

		bool rangeValid = false;
		while ( range.first != range.second ) {
			rangeValid = true;
			range.first = range.second;
			break;
			//StringUtils::trace( Format("k/v: %d-%d\n") % range.first->first % range.first->second );
			++range.first;
		}

		if ( rangeValid ) {
			range.first --;
		}
		 

		data[ (TreeModel::Key)lastKey ] = ref;

		found = data.find( lastKey );
		TreeValRef& ref2 = found->second;
		
		if ( rangeValid ) {
			TreeModel::Key k = range.first->second;
			TreeModel::Key kp = range.first->first;
			
			found = data.find( k );
			if ( found != data.end() ) {
				TreeValRef& r = found->second;
				
				r.nextSibling = &ref2;
				
				ref2.prevSibling = &r;
			}
		}


		pcData.insert( PCVal(parent,ref2.key) );

		return lastKey;
	}


	void remove( TreeModel::Key k ) {
		TrMap::iterator found = data.find( k );
		if ( found != data.end() ) {
			
			TreeValRef& ref = found->second;

			if ( ref.prevSibling ) {
				ref.prevSibling->nextSibling = ref.nextSibling;
			}
			if ( ref.nextSibling ) {
				ref.nextSibling->prevSibling = ref.prevSibling;
			}

			bool validRange = false;
			PCRange range = pcData.equal_range( k );
			//yank children
			while ( range.first != range.second ) {
				validRange = true;
				remove( range.first->second );
				++range.first;				
			}

			if ( validRange ) {
				pcData.erase( range.first, range.second );
			}

			data.erase( found );
		}
	}

	TreeModel::Key parent( TreeModel::Key k ) {
		TreeModel::Key result(-1);

		TrMap::iterator found = data.find( k );
		if ( found != data.end() ) {
			TreeValRef& ref = found->second;

			result = ref.parent->key;
		}
		
		return result;
	}

	TreeModel::Key next( TreeModel::Key k ) {
		TreeModel::Key result(-1);

		TrMap::iterator found = data.find( k );
		if ( found != data.end() ) {
			TreeValRef& ref = found->second;

			if ( ref.nextSibling ) {
				result = ref.nextSibling->key;
			}
		}
		
		return result;
	}

	VariantData value( TreeModel::Key k ) {
		VariantData result;

		TrMap::iterator found = data.find( k );
		if ( found != data.end() ) {
			TreeValRef& ref = found->second;

			result = ref.data;
		}
		
		return result;
	}

	size_t size() const {
		return data.size();
	}

	TrMap data;
	ParentChildMap pcData;
};

 




class TreesApplication : public Application {
public:

	TreesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(TreesWindow);

		Window* mainWindow = Frame::createWindow( classid(TreesWindow) );


		TreeControl* treeCtrl = (TreeControl*)mainWindow->findComponent( "treeCtrl" );


		TreeModel* tm = treeCtrl->getTreeModel();


		TrModel m;

		uint32 k1 = m.add( "s1", 0 );
		uint32 k2 = m.add( "s2", k1 );
		uint32 k3 = m.add( "s3", k1 );
		uint32 k4 = m.add( "s4", k1 );
		uint32 k5 = m.add( "s5", k4 );
		uint32 k6 = m.add( "s6", k5 );

		HiResClock clock;

		for (int i=0;i<10000;i++ ) {
			clock.start();
			uint32 k = m.add( i, k6 );
			clock.stop();

			//System::println( Format("insert #%d took %.8f seconds") % (i+1) % clock.duration() );
		}


		TreeModel::Key p = m.parent(k3);
		System::println( Format("parent %d") % p );

		
		TreeModel::Key s = m.next( k2 );
		while ( s != (TreeModel::Key)-1 ) {
			System::println( Format("sibling %d") % s );
			s = m.next( s );
		}


		System::println( Format("size %u") % m.size() );

		m.remove( k3 );

		System::println( Format("size %u") % m.size() );

		s = m.next( k2 );
		while ( s != (TreeModel::Key)-1 ) {
			System::println( Format("sibling %d") % s );
			s = m.next( s );
		}


		clock.start();
		m.remove( k6 );
		clock.stop();
		System::println( Format("remove took %.8f seconds") % clock.duration() );

		System::println( Format("size %u") % m.size() );
		

		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TreesApplication( argc, argv );

	Application::main();
	
	return 0;
}


