#ifndef _VCF_TABMODEL_H__
#define _VCF_TABMODEL_H__
//TabModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define TABMODEL_CLASSID	"4A9D66D7-3B26-11d4-B54C-00C04F0196DA"

class TabPage;

/**
\class TabModel TabModel.h "vcf/ApplicationKit/TabModel.h"
The Tab model is a interface for describing what a model that implements
a series of tabs should do. It does not \emnot inherit from the Model class
directly. This is to allow different implementations different base classes.
For example, you might have a simple list model that inherits/implements the 
Model class, and the TabModel class. This would be suitable for most controls.
However you might want a fancier implementation, perhaps that is based 
off of the Document and TabModel classes. This would still allow you to 
use the same control with either style.
*/

class APPLICATIONKIT_API TabModel  {
public:

	TabModel(){

	};

	virtual ~TabModel(){};

	virtual void addTabPageAddedHandler( EventHandler* handler ) = 0;

	virtual void removeTabPageAddedHandler( EventHandler* handler ) = 0;

	virtual void addTabPageRemovedHandler( EventHandler* handler ) = 0;

	virtual void removeTabPageRemovedHandler( EventHandler* handler ) = 0;

	virtual void addTabPageSelectedHandler( EventHandler* handler ) = 0;

	virtual void removeTabPageSelectedHandler( EventHandler* handler ) = 0;

	virtual void addTabPage( TabPage* page ) = 0;

	virtual void insertTabPage( const ulong32& index, TabPage* page ) = 0;

	virtual void deleteTabPage( TabPage* page ) = 0;

	virtual void deleteTabPage( const ulong32& index ) = 0;

	virtual void clearTabPages() = 0;

	virtual TabPage* getPageFromPageName( const String& pageName ) = 0;

	virtual TabPage* getPageAt( const ulong32& index ) = 0;

	virtual ulong32 getItemIndex( TabPage* item ) = 0;

	virtual TabPage* getSelectedPage() = 0;

	virtual void setSelectedPage( TabPage* page ) = 0;

	virtual void setSelectedPage( const ulong32& index ) = 0;

	virtual Enumerator<TabPage*>* getPages() = 0;

	virtual uint32 getPageCount() = 0;
};

};


#endif // _VCF_TABMODEL_H__

/**
$Id$
*/
