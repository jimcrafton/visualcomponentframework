//UndoAppApplication.h

#ifndef _[!output UPPER_CASE_PROJECT_NAME]APPAPPLICATION_H__
#define _[!output UPPER_CASE_PROJECT_NAME]APPAPPLICATION_H__

using namespace VCF;

/**
*Class [!output PROJECT_NAME]Application documentation
*/
class [!output PROJECT_NAME]Application : public VCF::Application {
public:
	[!output PROJECT_NAME]Application( int argc, char** argv );

	virtual ~[!output PROJECT_NAME]Application();

	virtual bool initRunningApplication();

[!if UNDO_REDO]
	VCF::UndoRedoStack* getCommandStack() {
		return &m_commandStack;
	}

	VCF::UndoRedoStack m_commandStack;

[!endif]
	static [!output PROJECT_NAME]Application* get[!output PROJECT_NAME]Application() {
		return ([!output PROJECT_NAME]Application*)Application::getRunningInstance();
	}
protected:

private:
};


#endif //_[!output UPPER_CASE_PROJECT_NAME]APPAPPLICATION_H__


