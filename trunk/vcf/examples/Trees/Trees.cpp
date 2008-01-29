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
		TreeModel::Key k1 = tm->insert( "testA" );
		TreeModel::Key k2 = tm->insert( "testB" );
		TreeModel::Key k3 = tm->insert( "testC" );
		TreeModel::Key k4 = tm->insert( "testD" );
		
		tm->insert( "test1 (p = testA)", k1 );

		int i=0;
		for (i=0;i<10;i++ ) {
			tm->insert( "test (p = testB)", k2 );
		}
		
		for (i=0;i<100;i++ ) {
			tm->insert( "test (p = testD)", k4 );
		}

		size_t sz = tm->sizeOf();

		StringUtils::trace( Format("tree mod %u\n") % sz );


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


