//UndoAppApplication.h

#ifndef _$$ROOT$$APPAPPLICATION_H__
#define _$$ROOT$$APPAPPLICATION_H__



using namespace VCF;


/**
*Class $$Root$$Application documentation
*/
class $$Root$$Application : public VCF::Application { 
public:
	$$Root$$Application( int argc, char *argv[] );

	virtual ~$$Root$$Application();

	virtual bool initRunningApplication();
	
	VCF::UndoRedoStack* getCommandStack() {
		return &m_commandStack;
	}
	
	VCF::UndoRedoStack m_commandStack;

	static $$Root$$Application* get$$Root$$Application() {
		return ($$Root$$Application*)Application::getRunningInstance();
	}
protected:

private:
};


#endif //_$$ROOT$$APPAPPLICATION_H__


