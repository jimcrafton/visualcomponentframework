#ifndef _VCF_COMMONDIALOG_H__
#define _VCF_COMMONDIALOG_H__
//CommonDialog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class CommonDialog CommonDialog.h "vcf/ApplicationKit/CommonDialog.h"
Base class for all the standard, or "common" dialog classes. A common
dialog is one like a color dialog, or font selection dialog or 
open or save file dialog. These are generally provided by the 
windowing system, and these classes just provide convenient 
wrappers around them.

To display any common dialog, you simply call the execute() function.
This funtion will return true if the user chose something, like a 
font, color, or filename, and false if the user canceled the dialog.

*/
class APPLICATIONKIT_API CommonDialog : public Component {
public:

	CommonDialog(){};

	virtual ~CommonDialog(){};

	/**
	"Executes" or displays the dialog.
	@return bool returns true if the user made a valid selection,
	otherwise false.
	*/
	virtual bool execute() = 0;

	/**
	* Special initializations may then happen here.
	*@see Component::afterCreate()
	*/
	virtual void afterCreate( ComponentEvent* event ){};
};

}; // namespace VCF


#endif // _VCF_COMMONDIALOG_H__

/**
$Id$
*/
