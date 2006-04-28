#ifndef _TEXTEDIT_H__
#define _TEXTEDIT_H__
//TextEdit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


class TextEdit : public VCF::SDIDocumentBasedApplication {
public:

	enum ActionTag {
		atEditFind = 1001,
		atEditReplace,
		atFilePrint = 3001
	};
	TextEdit( int argc, char *argv[] );

	FindInfo currentFindInfo_;
	ReplaceInfo currentReplaceInfo_;


	void onExit( VCF::Event* e );

	void onPrint( VCF::Event* e );

	void onUpdatePrint( VCF::ActionEvent* e );

	void onFind( VCF::Event* e );

	void onUpdateFind( VCF::ActionEvent* e );

	void onReplace( VCF::Event* e );

	void onUpdateReplace( VCF::ActionEvent* e );

	virtual bool initRunningApplication();

	virtual void terminateRunningApplication() ;

	void onDocInitialized( VCF::Event* e );
};


#endif //_TEXTEDIT_H__

/**
$Id$
*/
