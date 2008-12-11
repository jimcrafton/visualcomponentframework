//Test.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Panel.h"
#include "GraphvizKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"




using namespace VCF;


#define DOT_GRAPH		"graph {rank = same; A; B; C;}"

#define DOT_ER			"graph ER {"\
	"node [shape=box]; course; institute; student;"\
	"node [shape=ellipse]; {node [label=\"name\"] name0; name1; name2;}"\
	"	code; grade; number;"\
	"node [shape=diamond,style=filled,color=lightgrey]; \"C-I\"; \"S-C\"; \"S-I\";"\
	"name0 -- course;"\
	"code -- course;"\
	"course -- \"C-I\" [label=\"n\",len=1.00];"\
	"\"C-I\" -- institute [label=\"1\",len=1.00];"\
	"institute -- name1;"\
	"institute -- \"S-I\" [label=\"1\",len=1.00];"\
	"\"S-I\" -- student [label=\"n\",len=1.00];"\
	"student -- grade;"\
	"student -- name2;"\
	"student -- number;"\
	"student -- \"S-C\" [label=\"m\",len=1.00];"\
	"\"S-C\" -- course [label=\"n\",len=1.00];"\
	"label = \"\\n\\nEntity Relation Diagram\\ndrawn by NEATO\";"\
	"fontsize=20;"\
	"}"\


class DotViewPane : public Panel {
public:

	DotViewPane(): checkSB(false){}
	void loadFromFile( const String& fileName ) {
		graph.loadFromFile(fileName);

		graph.layout();

		checkSB = true;

		repaint();
	}

	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint(ctx);
		ctx->setAntiAliasingOn(true);

		if ( !graph.null() ) {

			graph.render(ctx);


			if ( checkSB ) {
				Rect r = graph.getTransformedBoundingBox();				
				getScrollable()->setVirtualViewWidth( r.getWidth() );
				getScrollable()->setVirtualViewHeight( r.getHeight() );
			}

			checkSB = false;
		}
	}

	AGraph graph;
	bool checkSB;
};

class DotViewer : public Window {
public:
	DotViewer()
		{
		//setCaption( "Test" );	

		//graph.load( DOT_ER );

		//Agdisc_t agd;
		

		//FILE* f;
		//agread( f );

		/*

		Agnode_t *n, *m;
		Agedge_t *e;
		Agsym_t *a;
		
		Agnode_t *n1;
		Agnode_t *n2;
		Agnode_t *n3;
		Agnode_t *n4;
		Agnode_t *n5;

		Agnode_t* o;


		n = agnode(graph.get(), "n");
		m = agnode(graph.get(), "m");
		e = agedge(graph.get(), n, m);


		n1 = agnode(graph.get(), "n1");
		n2 = agnode(graph.get(), "n2");
		n3 = agnode(graph.get(), "n3");
		n4 = agnode(graph.get(), "n4");
		n5 = agnode(graph.get(), "n5");

		o = agnode(graph.get(), "o");

		agedge(graph.get(), n1, o);
		agedge(graph.get(), n2, o);
		agedge(graph.get(), n3, o);
		agedge(graph.get(), n4, o);
		agedge(graph.get(), n5, o);


		agedge(graph.get(), n5, m);

		agedge(graph.get(), m, o);



		agedge(graph.get(), m, n4);
		agedge(graph.get(), n, n4);

		agedge(graph.get(), n, n2);
		agedge(graph.get(), n5, n2);
		agedge(graph.get(), n4, n2);

		agedge(graph.get(), n, n3);


		agsafeset(n, "color", "red", "");
*/

		//graph.layout();

		

	}

	virtual ~DotViewer(){};
};



_class_rtti_(DotViewer, "VCF::Window", "DotViewer")
_class_rtti_end_

_class_rtti_(DotViewPane, "VCF::Panel", "DotViewPane")
_class_rtti_end_


class DotViewApp : public Application {
public:

	DotViewApp( int argc, char** argv ) : Application(argc, argv) {
		GraphvizKit::init(argc,argv);

		addCallback( new ClassProcedure1<Event*,DotViewApp>(this, &DotViewApp::onFileOpen), "DotViewApp::onFileOpen" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		REGISTER_CLASSINFO_EXTERNAL(DotViewer);
		REGISTER_CLASSINFO_EXTERNAL(DotViewPane);

		Window* mainWindow = Frame::createWindow( classid(DotViewer) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

	virtual void terminateRunningApplication() {

		GraphvizKit::terminate();

		Application::terminateRunningApplication();
	}

	void onFileOpen( Event* ) {
		CommonFileOpenDialog fo;

		if ( fo.execute() ) {

			DotViewPane* pane = (DotViewPane*) findComponent( "viewPane", true );
			pane->loadFromFile( fo.getFileName() );
		}
	}
};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<DotViewApp>(argc,argv);
}


