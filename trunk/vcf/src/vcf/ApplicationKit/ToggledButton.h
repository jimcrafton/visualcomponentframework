#ifndef _VCF_TOGGLEDBUTTON_H__
#define _VCF_TOGGLEDBUTTON_H__
//ToggledButton.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define TOGGLEDBUTTON_CLASSID		"3fe39237-6aa6-47f1-b7da-4ccdb4ae01eb"


namespace VCF  {

/**
RadioButtonControl base class for toggled buttons.
This means for a button that stays down if clicked until it is clicked again.
This base class is used as base class for RadioButtonControl, but not for
the PushButton with a toggled behaviour.
*/
class APPLICATIONKIT_API ToggledButton : public CustomControl, public Button {
public:

	ToggledButton();
	virtual ~ToggledButton();


	DELEGATE(ButtonDelegate,ButtonClicked);

	virtual void addButtonClickHandler( EventHandler* handler ) {
		ButtonClicked += handler;
	}

	virtual void removeButtonClickHandler( EventHandler* handler ) {
		ButtonClicked.remove(handler);
	}

    virtual void click();

	/**
	*no-op - ToggledButton's don't support this
	*/
	virtual void setDefault( const bool& defaultButton ) {};

	virtual bool isDefault(){
		return false;
	}

	virtual void setName( const String& name );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	bool isChecked();

	virtual void setChecked( const bool& checked );

	void setCaption( const String& caption );

    String getCaption() {
		return caption_;
	}

	void setCaptionAlignment( const TextAlignmentType& alignment );

	TextAlignmentType getCaptionAlignment() {
		return captionAlignment_;
	}

	virtual void updateView( Model* updatedModel );
protected:
	String caption_;
	TextAlignmentType captionAlignment_;
	bool checked_;


};


}; //end of namespace VCF


#endif // _VCF_TOGGLEDBUTTON_H__

/**
$Id$
*/
