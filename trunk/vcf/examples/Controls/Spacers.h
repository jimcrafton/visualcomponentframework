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
	}
	
	VerticalSpacer(double height) : VCF::CustomControl( false ){		
		setHeight( height );
		isTransparent_ = true;
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
	}
	
	HorizontalSpacer(double width) : VCF::CustomControl( false ){		
		setWidth( width );		
		isTransparent_ = true;
	}

	virtual ~HorizontalSpacer(){}

protected :

private :

};


#endif //_SPACERS_H__

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:15:00  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/08/30 03:50:47  dougtinkham
*added copyright
*
*/