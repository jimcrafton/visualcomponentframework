//Test.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"


#define USE_GRAPHVIZKIT_LIB

#include "GraphvizKit.h"




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



class TestWindow : public Window {
public:
	TestWindow() : 
		graph( agmemread( DOT_ER ) ) //agopen("g", AGDIGRAPH) )
		
		{
		setCaption( "Test" );	

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

		graph.layout();

		

	}

	virtual ~TestWindow(){};

	AGraph graph;

	virtual void paint( GraphicsContext* ctx ) {
		Window::paint(ctx);

		//ctx->setScale( 0.75,0.75 );

		graph.render(ctx);

		//GVC_t* gvc = GraphvizKit::getContext();	

		//ctx->setTranslation( (gvc->bb.UR.x - gvc->bb.LL.x) + 10, 0 );

		//graph.render(ctx);	
	}
};




class TestApplication : public Application {
public:

	TestApplication( int argc, char** argv ) : Application(argc, argv) {
		GraphvizKit::init(argc,argv);
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new TestWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();		
		
		return result;
	}

	virtual void terminateRunningApplication() {

		GraphvizKit::terminate();

		Application::terminateRunningApplication();
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<TestApplication>(argc,argv);
}


