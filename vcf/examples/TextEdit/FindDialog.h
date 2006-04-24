#if     _MSC_VER > 1000
#pragma once
#endif


#ifndef _FINDDIALOG_H__
#define _FINDDIALOG_H__



#include "DataExchange.h"
#include "TextEditDocument.h"



class FindDialog : public VCF::Dialog {
public:
	FindDialog();
	virtual ~FindDialog();		

	
	StdBoolType caseSensitive_;
	StdBoolType matchWordOnly_;
	
	StdStringChoiceType searchString_;
	StdStringsChoiceType searchStrings_;
protected:		
	
	VCF::CommandButton* find_;
	VCF::CommandButton* cancel_;

	void findClicked( VCF::ButtonEvent* e );

	FindInfo findInfo_;
};




#endif //_FINDDIALOG_H__


