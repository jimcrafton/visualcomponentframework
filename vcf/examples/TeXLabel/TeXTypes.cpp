
#include "TeXTypes.hpp"


Group::Group(Tex *value, FaceModifiers modifiers)
	: value_(value)
	, modifiers_(modifiers)
{ }

void Group::paint(VCF::GraphicsContext *ctx, VCF::Rect& bounds, VCF::Font *f)
{
	VCF::Font f2 = *f;
	if(modifiers_ & FM_BOLD)
		f2.setBold(true);
	if(modifiers_ & FM_EMPH)
		f2.setItalic(!f2.getItalic());
	if(modifiers_ & FM_ITALIC)
		f2.setItalic(true);
	if(modifiers_ & FM_UNDERLINE)
		f2.setUnderlined(true);
	//if(modifiers_ & FM_OVERLINE)
	//	f2.setItalic(true);
	if(modifiers_ & FM_STRIKE)
		f2.setStrikeOut(true);
	ctx->setCurrentFont(&f2);
	if(value_)
		value_->paint(ctx, bounds, &f2);
	ctx->setCurrentFont(f);
}

Pair::Pair(Tex *value1, Tex *value2)
	: value1_(value1)
	, value2_(value2)
{ }

void Pair::paint(VCF::GraphicsContext *ctx, VCF::Rect& bounds, VCF::Font *f)
{
	if(value1_)
		value1_->paint(ctx, bounds, f);
	if(value2_)
		value2_->paint(ctx, bounds, f);
}

void String::paint(VCF::GraphicsContext *ctx, VCF::Rect& bounds, VCF::Font *)
{
	ctx->textBoundedBy(&bounds, value_,
		(long)(VCF::GraphicsContext::tdoLeftAlign | VCF::GraphicsContext::tdoBottomAlign));
	bounds.setLeft(bounds.getLeft() + ctx->getTextWidth(value_));
}

SuperScript::SuperScript(Tex *value)
	: value_(value)
{ }

void SuperScript::paint(VCF::GraphicsContext *ctx, VCF::Rect& bounds, VCF::Font *f)
{
	double fontSize = f->getPixelSize();
	f->setPixelSize(fontSize * 0.75);
	double offset = f->getPixelSize() * 0.5;
	bounds.offset(0, -offset);
	ctx->setCurrentFont(f);
	if(value_)
		value_->paint(ctx, bounds, f);
	f->setPixelSize(fontSize);
	bounds.offset(0, offset);
	ctx->setCurrentFont(f);
}

SubScript::SubScript(Tex *value)
	: value_(value)
{ }

void SubScript::paint(VCF::GraphicsContext *ctx, VCF::Rect& bounds, VCF::Font *f)
{
	double fontSize = f->getPixelSize();
	f->setPixelSize(fontSize * 0.75);
	double offset = f->getPixelSize() * 0.20;
	bounds.offset(0, offset);
	ctx->setCurrentFont(f);
	if(value_)
		value_->paint(ctx, bounds, f);
	f->setPixelSize(fontSize);
	bounds.offset(0, -offset);
	ctx->setCurrentFont(f);
}

