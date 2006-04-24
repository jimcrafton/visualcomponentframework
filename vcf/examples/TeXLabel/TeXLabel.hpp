
#ifndef TEX_LABEL_HPP
#define TEX_LABEL_HPP



class TeXLabel
	: public VCF::CustomControl
{
public:
	TeXLabel();
	~TeXLabel();

	void setCaption(VCF::String const&);
	virtual void paint(VCF::GraphicsContext *);
	double getPreferredHeight();

protected:
	VCF::String caption_;
	void *markup_tree_;
};


#endif
