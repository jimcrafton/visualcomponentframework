#include <vcf/ApplicationKit/ApplicationKit.h>
#include <vcf/ApplicationKit/TitledBorder.h>
#include <vcf/ApplicationKit/ControlsKit.h>
#include <vcf/ApplicationKit/ColumnLayoutContainer.h>


#include "TeXLabel.hpp"
#include "TeXTypes.hpp"
#include "TeXLabel.tab.hpp"

void SetTeXLabel(const char *);
void DisplayTex(VCF::Rect&, VCF::GraphicsContext *, Tex *, VCF::Font *);
int yyparse(void *);

using namespace VCF;

TeXLabel::TeXLabel()
	: CustomControl()
{
	markup_tree_ = NULL;
}

TeXLabel::~TeXLabel()
{
}

void TeXLabel::setCaption(VCF::String const& caption)
{
	caption_ = caption;
	SetTeXLabel(caption.ansi_c_str());
	yyparse(&markup_tree_);
}

void TeXLabel::paint(VCF::GraphicsContext *ctx)
{
	CustomControl::paint(ctx);
	if(markup_tree_)
	{
		Rect bounds = getClientBounds();
		DisplayTex(bounds, ctx, (Tex *)markup_tree_, getFont());
	}
}

double TeXLabel::getPreferredHeight()
{
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor(UIMetricsManager::htLabelHeight);
}






void setFont(Control *c)
{
	//if you're on XP you may want to use Arial Unicode MS, otherwise try 
	//Lucida Sans Unicode
	//Win98 users may be SOL here.
	//c->getFont()->setName(L"Arial Unicode MS");
	c->getFont()->setName(L"Lucida Sans Unicode");
	c->getFont()->setPointSize(14);
}

class TeXLabelWindow
   : public Window
{
public:
	TeXLabelWindow()
		: Window()
	{
		ControlSized += new ControlEventHandler<TeXLabelWindow>(this,
			&TeXLabelWindow::onResized, "TeXLabelWindow::onResized" );
		setContainer(new StandardContainer());
		setCaption("LaTeX Style Markup for VCF");

		TeXLabel *label;
		Panel *panel;
		ColumnLayoutContainer *container;

		panel = new Panel();
		container = new ColumnLayoutContainer();
		container->setColumnCount(4);
		for(int i = 0; i < 4; i++)
			container->setColumnWidth(i,140);
		panel->setContainer(container);
		add(panel, AlignTop);
		panel->setBorder(new TitledBorder("Greek characters"));
		panel->setHeight(120);

		VCF::String list1[] = {
			"alpha", "beta", "gamma", "delta", "xi", "mu", "Gamma", "Delta", "Lambda",
			"phi", "varphi", "Phi", ""
		};
		for(VCF::String *s = list1; *s != ""; ++s)
		{
			label = new TeXLabel();
			panel->add(label, AlignTop);
			::setFont(label);
			label->setCaption("\\\\" + *s + " = \\" + *s);
			label->setHeight(label->getPreferredHeight());
		}

		panel = new Panel();
		container = new ColumnLayoutContainer();
		container->setColumnCount(4);
		for(int i2 = 0; i2 < 4; i2++)
			container->setColumnWidth(i2,140);
		panel->setContainer(container);
		add(panel, AlignTop);
		panel->setBorder(new TitledBorder("Mathematical accents"));
		panel->setHeight(120);

		VCF::String list2[] = {
			"hat", "grave", "bar", "check", "dot", "vec", "tilde", "ddot",
			"acute", "breve", ""
		};
		for(VCF::String *s2 = list2; *s2 != ""; ++s2)
		{
			label = new TeXLabel();
			panel->add(label, AlignTop);
			::setFont(label);
			label->setCaption("\\\\" + *s2 + "\\{a\\} = \\" + *s2 + "{a}");
			label->setHeight(label->getPreferredHeight());
		}

		panel = new Panel();
		panel->setContainer(new StandardContainer());
		panel->setLeftBorderWidth(8);
		add(panel, AlignTop);
		panel->setBorder(new TitledBorder("Markup"));
		panel->setHeight(180);

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\{\\\\bf Bold text\\} = {\\bf Bold text}");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\{\\\\em Emphasized text\\} = {\\em Emphasized text}");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\\\underline\\{Underlined text\\} = \\underline{Underlined text}");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\\\sout\\{Strike out\\} = \\sout{Strike out}");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\\\textbf\\{Mix \\\\emph\\{\\`n\\}\\} \\\\emph\\{M\\\\underline\\{atc\\}\\}h= \\textbf{Mix \\emph{`n}} \\emph{M\\underline{atc}}h");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("Superscript: n\\^\\{n+1\\}x = n^{n+1}x");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("Subscript: n\\_\\{n+1\\}x = n_{n+1}x");
		label->setHeight(label->getPreferredHeight());

		panel = new Panel();
		panel->setContainer(new StandardContainer());
		panel->setLeftBorderWidth(8);
		add(panel, AlignTop);
		panel->setBorder(new TitledBorder("Miscellaneous"));
		panel->setHeight(140);

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\`Smart quotes\\' = `Smart quotes'");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\`\\`Smart quotes\\'\\' = ``Smart quotes''");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("Dagger\\^\\{\\\\dagger\\} = Dagger^{\\dagger}");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\{\\}\\^\\{\\\\circ\\}C = (5/9)\\\\cdot(\\{\\}\\^\\{\\\\circ\\}F - 32) == {}^{\\circ}C = (5/9)\\cdot({}^{\\circ}F - 32)");
		label->setHeight(label->getPreferredHeight());

		label = new TeXLabel();
		panel->add(label, AlignTop);
		::setFont(label);
		label->setCaption("\\\\infty or \\\\inf = \\infty or \\inf");
		label->setHeight(label->getPreferredHeight());

		setBounds(100, 100, 640, 480);
	}

	void onResized(ControlEvent *)
	{
		Enumerator<Control *> *children = getChildren();
		Rect bounds = getClientBounds();

		while(children->hasMoreElements())
		{
			Control *c = children->nextElement();
			c->setWidth(bounds.getWidth());
		}
	}
};

class TeXLabelApp
   : public Application
{
public:
	TeXLabelApp(int argc, char *argv[])
	   : Application(argc, argv)
	{ }

	virtual bool initRunningApplication()
	{
		Application::initRunningApplication();
		Window *mainWindow = new TeXLabelWindow();

		setMainWindow(mainWindow);
		mainWindow->show();

		return true;
	}

};

int main(int argc, char *argv[])
{
	Application* app = new TeXLabelApp(argc, argv);
	Application::main();
	return 0;
}
