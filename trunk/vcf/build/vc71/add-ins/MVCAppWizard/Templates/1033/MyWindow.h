#ifndef _[!output UPPER_CASE_PROJECT_NAME]WINDOW_H__
#define _[!output UPPER_CASE_PROJECT_NAME]WINDOW_H__

#define [!output UPPER_CASE_PROJECT_NAME]WINDOW_CLASSID		"[!output WINDOW_UUID]"


/**
class [!output PROJECT_NAME]Window documentation
*/
class [!output PROJECT_NAME]Window  : public VCF::Window{
public: 
	BEGIN_CLASSINFO( [!output PROJECT_NAME]Window, "[!output PROJECT_NAME]Window", "VCF::Window", [!output UPPER_CASE_PROJECT_NAME]WINDOW_CLASSID )
	END_CLASSINFO( [!output PROJECT_NAME]Window )

	[!output PROJECT_NAME]Window();
	virtual ~[!output PROJECT_NAME]Window();


protected:
	void onDocInitialized( VCF::Event* e ) ;
};




#endif //_[!output UPPER_CASE_PROJECT_NAME]WINDOW_H__



