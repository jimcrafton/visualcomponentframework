#ifndef _VCF_DEFAULTLISTMODEL_H__
#define _VCF_DEFAULTLISTMODEL_H__
//DefaultListModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_SIMPLELISTMODEL_H__
#	include "vcf/ApplicationKit/SimpleListModel.h"
#endif // _VCF_LISTMODEL_H__





namespace VCF{

#define DEFAULTLISTMODEL_CLASSID			"ED88C0A9-26AB-11d4-B539-00C04F0196DA"

/**
\class DefaultListModel DefaultListModel.h "vcf/ApplicationKit/DefaultListModel.h"
*/
class APPLICATIONKIT_API DefaultListModel : public SimpleListModel, public Persistable {
public:

	DefaultListModel();

	virtual ~DefaultListModel();

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );
protected:
};

};


#endif // _VCF_DEFAULTLISTMODEL_H__

/**
$Id$
*/
