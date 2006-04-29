#ifndef _VCF_STATUSBAR_H__
#define _VCF_STATUSBAR_H__
//StatusBar.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define STATUSBAR_CLASSID		"ca8c2cda-3e41-4e32-9478-8208247c9b66"


namespace VCF  {

/**
\class StatusBar StatusBar.h "vcf/ApplicationKit/StatusBar.h"
*Class StatusBar documentation
*/
class StatusBar : public ControlContainer {
public:

	StatusBar();
	virtual ~StatusBar();


protected:

private:
};


}; //end of namespace VCF


#endif // _VCF_STATUSBAR_H__

/**
$Id$
*/
