//UndoAppApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifndef _CONTROLSAPPAPPLICATION_H__
#define _CONTROLSAPPAPPLICATION_H__



using namespace VCF;


/**
*Class ControlsApplication documentation
*/
class ControlsApplication : public VCF::Application { 
public:
	ControlsApplication( int argc, char** argv );


	virtual ~ControlsApplication();

	virtual bool initRunningApplication();
	
	VCF::UndoRedoStack* getCommandStack() {
		return &m_commandStack;
	}
	
	VCF::UndoRedoStack m_commandStack;

	static ControlsApplication* getControlsApplication() {
		return (ControlsApplication*)Application::getRunningInstance();
	}
protected:

private:
};


#endif //_CONTROLSAPPAPPLICATION_H__

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
