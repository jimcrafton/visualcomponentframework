//ControlsAbout.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifndef _CONTROLSABOUT_H__
#define _CONTROLSABOUT_H__




/**
*Class ControlsAbout documentation
*/
class ControlsAbout : public VCF::Dialog { 
public:
	ControlsAbout();

	virtual ~ControlsAbout();

protected:

private:
};


#endif //_CONTROLSABOUT_H__


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