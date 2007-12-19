#ifndef _VCF_DEFAULTTABMODEL_H__
#define _VCF_DEFAULTTABMODEL_H__
//DefaultTabModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABMODEL_H__
#	include "vcf/ApplicationKit/TabModel.h"
#endif // _VCF_TABMODEL_H__

#ifndef _VCF_TABPAGE_H__
#	include "vcf/ApplicationKit/TabPage.h"
#endif // _VCF_TABPAGE_H__




namespace VCF {

#define DEFAULTTABMODEL_CLASSID		"86F02174-3E7F-11d4-8EA7-00207811CFAB"

/**
\class DefaultTabModel DefaultTabModel.h "vcf/ApplicationKit/DefaultTabModel.h"
This class represents a default, basic implementation of
the TabModel class.

*/
class APPLICATIONKIT_API DefaultTabModel : public TabModel {
public:

	DefaultTabModel();

	virtual ~DefaultTabModel();

	virtual void insertTabPage( const uint32& index, TabPage* page );

	virtual void deleteTabPage( TabPage* page );

	virtual void deleteTabPage( const uint32& index );

	virtual TabPage* getPageAt( const uint32& index );

	virtual TabPage* getPageFromPageName( const String& pageName );

	virtual uint32 getItemIndex( TabPage* item );

	virtual TabPage* getSelectedPage();

	virtual void setSelectedPage( TabPage* page );

	virtual void setSelectedPage( const uint32& index );

	virtual Enumerator<TabPage*>* getPages();

    /**
     * clears out the model's data
     */
    virtual void empty();

	virtual uint32 getPageCount() {
		return pages_.size();
	}

	bool isFirstPage( TabPage* page );

	bool isLastPage( TabPage* page );

	TabPage* nextPage( TabPage* page );

	TabPage* previousPage( TabPage* page );
protected:
	Array<TabPage*> pages_;
	void tabPageChange( ItemEvent* e );
};

}; //end of namespace VCF


#endif // _VCF_DEFAULTTABMODEL_H__

/**
$Id$
*/
