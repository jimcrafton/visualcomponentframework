#if     _MSC_VER > 1000
#pragma once
#endif


#ifndef _REPLACEDIALOG_H__
#define _REPLACEDIALOG_H__

#include "DataExchange.h"
#include "TextEditDocument.h"




class ReplaceDialog : public VCF::Dialog {
public:
	ReplaceDialog();
	virtual ~ReplaceDialog();		

	
	StdBoolType caseSensitive_;
	StdBoolType matchWordOnly_;
	
	StdStringChoiceType searchString_;
	StdStringsChoiceType searchStrings_;

	StdStringChoiceType replaceString_;
	StdStringsChoiceType replaceStrings_;
protected:		
	
	VCF::CommandButton* findNext_;
	VCF::CommandButton* replace_;
	VCF::CommandButton* replaceAll_;
	VCF::CommandButton* cancel_;

	void findNextClicked( VCF::ButtonEvent* e );
	void replaceClicked( VCF::ButtonEvent* e );
	void replaceAllClicked( VCF::ButtonEvent* e );

	ReplaceInfo replaceInfo_;
};



#endif //_REPLACEDIALOG_H__