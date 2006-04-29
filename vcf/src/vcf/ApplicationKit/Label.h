#ifndef _VCF_LABEL_H__
#define _VCF_LABEL_H__
//Label.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{


enum TextVerticalAlignment {
	tvaTextTop=0,
	tvaTextCenter,
	tvaTextBottom
};

static String TextVerticalAlignmentNames[] = { "tvaTextTop", "tvaTextCenter", "tvaTextBottom" };

#define LABEL_CLASSID			"ED88C09F-26AB-11d4-B539-00C04F0196DA"

/**
\class Label Label.h "vcf/ApplicationKit/Label.h"
*/
class APPLICATIONKIT_API Label :  public VCF::CustomControl {
public:


	Label();

	virtual ~Label(){};

    virtual void paint(GraphicsContext * context);

	void setCaption( const String& caption );

	String getCaption();

	virtual void setName( const String& name );

	TextAlignmentType getTextAlignment() {
		return textAlignment_;
	}

	void setTextAlignment( const TextAlignmentType& textAlignment );

	TextVerticalAlignment getVerticalAlignment() {
		return textVerticalAlignment_;
	}

	void setVerticalAlignment( const TextVerticalAlignment& verticalAlignment );

	Control* getFocusControl() {
		return focusControl_;
	}

	void setFocusControl( Control* focusControl );

	bool getWordWrap() {
		return wordWrap_;
	}

	void setWordWrap( const bool& wordWrap );

	virtual void mnemonicActivate();

	virtual double getPreferredHeight();

	virtual double getPreferredWidth();
private:
	String caption_;
	TextAlignmentType textAlignment_;
	TextVerticalAlignment textVerticalAlignment_;
	Control* focusControl_;
	bool wordWrap_;
};

};


#endif // _VCF_LABEL_H__

/**
$Id$
*/
