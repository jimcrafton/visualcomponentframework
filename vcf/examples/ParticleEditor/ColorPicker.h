#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "vcf/ApplicationKit/ControlContainer.h"
#include "vcf/ApplicationKit/TextControl.h"

using namespace VCF;

class ColorPicker:public VCF::ControlContainer{
public:
	DELEGATE(ColorChanged);

	ColorPicker():ControlContainer(){
		setBorder(0);

		mAlpha=0;

		mR=new TextControl();
		mR->setBounds(0,0,25,20);
		mR->getTextModel()->addTextModelChangedHandler(new TextModelEventHandler<ColorPicker>(this,&ColorPicker::onR));
		add(mR);

		mG=new TextControl();
		mG->setBounds(25,0,25,20);
		mG->getTextModel()->addTextModelChangedHandler(new TextModelEventHandler<ColorPicker>(this,&ColorPicker::onG));
		add(mG);

		mB=new TextControl();
		mB->setBounds(50,0,25,20);
		mB->getTextModel()->addTextModelChangedHandler(new TextModelEventHandler<ColorPicker>(this,&ColorPicker::onB));
		add(mB);

		mA=new TextControl();
		mA->setBounds(75,0,25,20);
		mA->getTextModel()->addTextModelChangedHandler(new TextModelEventHandler<ColorPicker>(this,&ColorPicker::onA));
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
		ColorChanged.fireEvent(&event);
	}

	virtual float getAlpha(){
		return mAlpha;
	}

	void onR(TextEvent *e){
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
		ColorChanged.fireEvent(&event);
	}

	void onG(TextEvent *e){
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
		ColorChanged.fireEvent(&event);
	}

	void onB(TextEvent *e){
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
		ColorChanged.fireEvent(&event);
	}

	void onA(TextEvent *e){
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
		ColorChanged.fireEvent(&event);
	}

	TextControl *mR;
	TextControl *mG;
	TextControl *mB;
	TextControl *mA;

	float mAlpha;
};

#endif

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:15:09  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.6  2004/11/07 19:31:14  marcelloptr
*more documentation
*
*Revision 1.1.2.3  2004/11/04 21:04:09  pallindo
*Fixed alpha selection in the color picker
*
*Revision 1.1.2.2  2004/11/01 17:19:00  marcelloptr
*just added few lines at the end of file
*
*Revision 1.1.2.1  2004/11/01 14:38:59  pallindo
*Initial checkin of the particle editor example.  Just shows off a more complex opengl application using the VCF.
*
*/


