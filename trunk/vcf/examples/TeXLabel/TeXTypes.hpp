
#ifndef TEX_TYPES_HPP
#define TEX_TYPES_HPP


#include <vcf/ApplicationKit/ApplicationKit.h>

enum FaceModifiers
{
	FM_BOLD = (1 << 0),
	FM_EMPH = (1 << 1),
	FM_ITALIC = (1 << 2),
	FM_UNDERLINE = (1 << 3),
	FM_OVERLINE = (1 << 4),
	FM_STRIKE = (1 << 5),
};

struct Tex
{
	virtual ~Tex() { }
	virtual void paint(VCF::GraphicsContext *, VCF::Rect &, VCF::Font *) = 0;
};

struct Group : Tex
{
	Group(Tex *, FaceModifiers);
	void paint(VCF::GraphicsContext *, VCF::Rect &, VCF::Font *);
	Tex *value_;
	FaceModifiers modifiers_;
};

struct Pair : Tex
{
	Pair(Tex *value1, Tex *value2);
	void paint(VCF::GraphicsContext *, VCF::Rect &, VCF::Font *);
	Tex *value1_, *value2_;
};

struct String : Tex
{
	void paint(VCF::GraphicsContext *, VCF::Rect &, VCF::Font *);
	VCF::String value_;
};

struct SuperScript : Tex
{
	SuperScript(Tex *);
	void paint(VCF::GraphicsContext *, VCF::Rect &, VCF::Font *f);
	Tex *value_;
};

struct SubScript : Tex
{
	SubScript(Tex *);
	void paint(VCF::GraphicsContext *, VCF::Rect &, VCF::Font *f);
	Tex *value_;
};


#endif
