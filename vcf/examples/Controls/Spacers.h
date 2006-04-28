//Spacers.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifndef _SPACERS_H__
#define _SPACERS_H__


/**
*Class VerticalSpacer
*/
class VerticalSpacer : public VCF::CustomControl {
public :
	VerticalSpacer() : VCF::CustomControl( false ){
		setHeight( 1 );
		isTransparent_ = true;		
		setTabStop( false );
	}
	
	VerticalSpacer(double height) : VCF::CustomControl( false ){		
		setHeight( height );
		isTransparent_ = true;
		setTabStop( false );
	}

	virtual ~VerticalSpacer(){}

protected :

private :

};


/**
*Class HorizontalSpacer
*/
class HorizontalSpacer : public VCF::CustomControl {
public :
	HorizontalSpacer() : VCF::CustomControl( false ){
		setWidth( 1 );
		isTransparent_ = true;
		setTabStop( false );
	}
	
	HorizontalSpacer(double width) : VCF::CustomControl( false ){		
		setWidth( width );		
		isTransparent_ = true;
		setTabStop( false );
	}

	virtual ~HorizontalSpacer(){}

	
protected :

private :

};


#endif //_SPACERS_H__

/**
$Id$
*/
