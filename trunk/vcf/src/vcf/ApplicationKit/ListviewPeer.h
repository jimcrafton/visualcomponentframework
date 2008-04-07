#ifndef _VCF_LISTVIEWPEER_H__
#define _VCF_LISTVIEWPEER_H__
//ListviewPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_LISTPEER_H__
#include "vcf/ApplicationKit/ListPeer.h"
#endif 

namespace VCF{

class ListItem;




/**
\class ListviewPeer ListviewPeer.h "vcf/ApplicationKit/ListviewPeer.h"
*/

class APPLICATIONKIT_API ListviewPeer : public ListPeer{
public:
	virtual ~ListviewPeer(){};	

	virtual bool ensureVisible(const uint32& index, bool partialOK ) = 0;
	
	virtual void setColumnWidth( const uint32& index, const double& width, ListViewControl::AutoSizeType type=ListViewControl::lcatAutoSizeNone ) = 0;

	virtual double getColumnWidth( const uint32& index ) = 0;

	virtual TextAlignmentType getColumnTextAlignment( const uint32& index ) = 0;

	virtual void setColumnTextAlignment( const uint32& index, const TextAlignmentType& val ) = 0;

	virtual IconStyleType getIconStyle() = 0;

	virtual void setIconStyle( const IconStyleType& iconStyle ) = 0;

	virtual IconAlignType getIconAlignment() = 0;

	virtual void setIconAlignment( const IconAlignType& iconAlignType ) = 0;

	virtual bool getAllowLabelEditing() = 0;

	virtual void setAllowLabelEditing( const bool& allowLabelEditing ) = 0;		

	virtual int32 getDisplayOptions() = 0;

	virtual void setDisplayOptions( const int32& displayOptions ) = 0;
};

}


#endif // _VCF_LISTVIEWPEER_H__

/**
$Id$
*/
