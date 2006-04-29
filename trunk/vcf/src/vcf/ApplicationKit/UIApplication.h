#ifndef _VCF_UIAPPLICATION_H__
#define _VCF_UIAPPLICATION_H__
//UIApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define UIAPPLICATION_CLASSID		"ec9764b9-cb25-4c3b-9ac7-eeea0cf3b26f"


namespace VCF  {

/**
*Class UIApplication documentation
*/
class UIApplication : public Application {
public:

	BEGIN_CLASSINFO(UIApplication, "UIApplication", "Application", UIAPPLICATION_CLASSID)
	END_CLASSINFO(UIApplication)

	UIApplication();

	virtual ~UIApplication();

protected:

private:
};


}; //end of namespace VCF


#endif // _VCF_UIAPPLICATION_H__

/**
$Id$
*/
