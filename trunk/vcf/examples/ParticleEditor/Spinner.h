#ifndef SPINNER_H
#define SPINNER_H

#include "vcf/ApplicationKit/PushButton.h"
#include "vcf/ApplicationKit/ControlContainer.h"
#include "vcf/ApplicationKit/TextControl.h"

namespace VCF{

typedef Delegate1<TextEvent*> TextEventDelegate; 

class Spinner:public Panel {
public:
	DELEGATE(TextEventDelegate,SpinnerChanged);

	Spinner():Panel() {
		setBorder(0);
		setHeight(22);
		setWidth(120);

		mValue=new TextControl();
		mValue->getTextModel()->addTextModelChangedHandler( (EventHandler*) new ClassProcedure1<TextEvent*,Spinner>(this,&Spinner::onTextChanged));
		add(mValue,AlignClient);

		Panel *updown=new Panel();
		updown->setBorder(0);

		PushButton *down=new PushButton();
		down->setCaption("-");
		down->setWidth(20);
		down->MouseDown.add(new ClassProcedure1<MouseEvent*,Spinner>(this,&Spinner::onDownDown));
		down->MouseDoubleClicked.add(new ClassProcedure1<MouseEvent*,Spinner>(this,&Spinner::onDownDown));
		down->MouseUp.add(new ClassProcedure1<MouseEvent*,Spinner>(this,&Spinner::onDownUp));
		updown->add(down,AlignLeft);

		PushButton *up = new PushButton();
		up->setCaption("+");
		up->setWidth(20);
		up->MouseDown.add(new ClassProcedure1<MouseEvent*,Spinner>(this,&Spinner::onUpDown));
		up->MouseDoubleClicked.add(new ClassProcedure1<MouseEvent*,Spinner>(this,&Spinner::onUpDown));
		up->MouseUp.add(new ClassProcedure1<MouseEvent*,Spinner>(this,&Spinner::onUpUp));
		updown->add(up,AlignRight);

		updown->setWidth(40);
		add(updown,AlignRight);

		setMin(0);
		setMax(1);
		setIncrement(1);
		setValue(0);

		mPreTimer=new TimerComponent();
		mPreTimer->getTimerPulse().add(new ClassProcedure1<TimerEvent*,Spinner>(this,&Spinner::onPreTimer));
		addComponent(mPreTimer);

		mTimer=new TimerComponent();
		mTimer->getTimerPulse().add(new ClassProcedure1<TimerEvent*,Spinner>(this,&Spinner::onTimer));
		addComponent(mTimer);

		mDown=false;
		mInteger=true;
	}

	void setInteger(bool i){
		mInteger=i;
	}

	void setValue(float value){
		if(value<mMin){
			value=mMin;
		}
		else if(value>mMax){
			value=mMax;
		}

		String text;
		if(mInteger){
			text=StringUtils::toString((int)value);
		}
		else{
			text=StringUtils::toString(value);
		}
		mValue->getTextModel()->setText(text);
	}

	float getValue(){
		float value=0;
		try{
			if(mInteger){
				value=StringUtils::fromStringAsInt(mValue->getTextModel()->getText());
			}
			else{
				value=StringUtils::fromStringAsFloat(mValue->getTextModel()->getText());
			}
		}
		catch(std::exception &e){
			e; // Get rid of unused e warning
			value=0;
		}
		return value;
	}

	void setMin(float m){
		mMin=m;
	}

	void setMax(float m){
		mMax=m;
	}

	void setIncrement(float inc){
		mIncrement=inc;
	}

protected:
	void onDownDown(MouseEvent *e){
		setValue(getValue()-mIncrement);
		mPreTimer->setTimeoutInterval(500);
		mPreTimer->setActivated(true);
		mDown=true;
	}

	void onDownUp(MouseEvent *e){
		mPreTimer->setActivated(false);
		mTimer->setActivated(false);
	}

	void onUpDown(MouseEvent *e){
		setValue(getValue()+mIncrement);
		mPreTimer->setTimeoutInterval(500);
		mPreTimer->setActivated(true);
		mDown=false;
	}

	void onUpUp(MouseEvent *e){
		mPreTimer->setActivated(false);
		mTimer->setActivated(false);
	}

	void onPreTimer(TimerEvent *e){
		mPreTimer->setActivated(false);
		mTimer->setTimeoutInterval(50);
		mTimer->setActivated(true);
	}

	void onTimer(TimerEvent *e){
		if(mDown){
			setValue(getValue()-mIncrement);
		}
		else{
			setValue(getValue()+mIncrement);
		}
	}

	void onTextChanged(TextEvent *e){
		int value=getValue();
		if(value<mMin || value>mMax){
			setValue(value);
		}

		SpinnerChanged(e);
	}

	TimerComponent *mPreTimer;
	TimerComponent *mTimer;
	TextControl *mValue;
	float mMin;
	float mMax;
	float mIncrement;
	bool mDown;
	bool mInteger;
};

}

#endif

/**
$Id$
*/
