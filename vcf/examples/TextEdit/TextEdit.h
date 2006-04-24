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


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:34:47  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/07/23 21:45:43  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.2.2.1  2005/05/04 20:47:20  marcelloptr
*standard file formatting and cvs log section added
*
*/


#endif //_TEXTEDIT_H__



