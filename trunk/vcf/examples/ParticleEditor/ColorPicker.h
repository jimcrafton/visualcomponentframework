#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "vcf/ApplicationKit/ControlContainer.h"
#include "vcf/ApplicationKit/TextControl.h"

using namespace VCF;

class ColorPicker:public VCF::ControlContainer{
public:
	DELEGATE(ButtonDelegate,ColorChanged);

	ColorPicker():ControlContainer(){
		setBorder(0);

		mAlpha=0;

		mR=new TextControl();
		mR->setBounds(0,0,25,20);
		mR->getTextModel()->ModelChanged +=
			new ClassProcedure1<TextEvent*,ColorPicker>(this,&ColorPicker::onR);
		add(mR);

		mG=new TextControl();
		mG->setBounds(25,0,25,20);
		mG->getTextModel()->ModelChanged +=
			new ClassProcedure1<TextEvent*,ColorPicker>(this,&ColorPicker::onG);
		add(mG);

		mB=new TextControl();
		mB->setBounds(50,0,25,20);
		mB->getTextModel()->ModelChanged +=
			new ClassProcedure1<TextEvent*,ColorPicker>(this,&ColorPicker::onB);
		add(mB);

		mA=new TextControl();
		mA->setBounds(75,0,25,20);
		mA->getTextModel()->ModelChanged +=
			new ClassProcedure1<TextEvent*,ColorPicker>(this,&ColorPicker::onA);
		add(mA);

		setUseColorForBackground(true);

		setColor(new Color((unsigned char)255,(unsigned char)255,(unsigned char)255),1);

		setWidth(120);
		setHeight(20);
	}

	virtual void setColor(Color *c,float alpha){
		ControlContainer::setColor(c);

		mR->getTextModel()->setText(StringUtils::toString(int(c->getRed()*255)));
		mG->getTextModel()->setText(StringUtils::toString(int(c->getGreen()*255)));
		mB->getTextModel()->setText(StringUtils::toString(int(c->getBlue()*255)));
		mAlpha=alpha;
		mA->getTextModel()->setText(StringUtils::toString(int(alpha*255)));

		repaint();

		ButtonEvent event(this,ITEM_EVENT_SELECTED);
		ColorChanged(&event);
	}

	virtual float getAlpha(){
		return mAlpha;
	}

	void onR(TextEvent *e){
		if ( mR->getTextModel()->getText().empty() ) {
			return;
		}
		Color *c=getColor();
		try{
			int v=StringUtils::fromStringAsInt(mR->getTextModel()->getText());
			c->setRed(float(v)/255.0f);
		}
		catch(std::exception &e){
			e.what();
		}

		ControlContainer::setColor(c);

		repaint();

		ButtonEvent event(this,ITEM_EVENT_SELECTED);
		ColorChanged(&event);
	}

	void onG(TextEvent *e){

		if ( mG->getTextModel()->getText().empty() ) {
			return;
		}

		Color *c=getColor();
		try{
			int v=StringUtils::fromStringAsInt(mG->getTextModel()->getText());
			c->setGreen(float(v)/255.0f);
		}
		catch(std::exception &e){
			e.what();
		}

		ControlContainer::setColor(c);

		repaint();

		ButtonEvent event(this,ITEM_EVENT_SELECTED);
		ColorChanged(&event);
	}

	void onB(TextEvent *e){
		if ( mB->getTextModel()->getText().empty() ) {
			return;
		}

		Color *c=getColor();
		try{
			int v=StringUtils::fromStringAsInt(mB->getTextModel()->getText());
			c->setBlue(float(v)/255.0f);
		}
		catch(std::exception &e){
			e.what();
		}

		ControlContainer::setColor(c);

		repaint();

		ButtonEvent event(this,ITEM_EVENT_SELECTED);
		ColorChanged(&event);
	}

	void onA(TextEvent *e){
		if ( mA->getTextModel()->getText().empty() ) {
			return;
		}

		float a=1;
		try{
			int v=StringUtils::fromStringAsInt(mA->getTextModel()->getText());
			a=float(v)/255.0f;
		}
		catch(std::exception &e){
			e.what();
		}

		mAlpha=a;;

		ButtonEvent event(this,ITEM_EVENT_SELECTED);
		ColorChanged(&event);
	}

	TextControl *mR;
	TextControl *mG;
	TextControl *mB;
	TextControl *mA;

	float mAlpha;
};

#endif

/**
$Id$
*/
