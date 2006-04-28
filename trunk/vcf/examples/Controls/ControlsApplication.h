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
$Id$
*/
