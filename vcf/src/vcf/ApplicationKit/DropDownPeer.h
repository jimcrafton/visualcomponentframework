#ifndef _VCF_DROPDOWNPEER_H__
#define _VCF_DROPDOWNPEER_H__
//DropDownPeer.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef _VCF_LISTPEER_H__
#include "vcf/ApplicationKit/ListPeer.h"
#endif 

namespace VCF {
	class APPLICATIONKIT_API DropDownPeer : public ListPeer {
	public:
		virtual ~DropDownPeer(){}

		virtual void enableEditBox( bool val ) = 0;
		virtual bool editBoxEnabled() = 0;

		virtual void setEditText( const String& text ) = 0;
		virtual String getEditText() = 0;

		virtual void setDropDownWidth( double val ) = 0;
		virtual double getDropDownWidth() = 0;

		virtual void setDropDownCount( const uint32& dropDownCount ) = 0;

	};

};



#endif //_VCF_DROPDOWNPEER_H__