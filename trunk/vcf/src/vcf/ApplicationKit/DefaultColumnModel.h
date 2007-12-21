#ifndef _VCF_DEFAULTCOLUMNMODEL_H__
#define _VCF_DEFAULTCOLUMNMODEL_H__
//DefaultColumnModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_COLUMNMODEL_H__
#	include "vcf/ApplicationKit/ColumnModel.h"
#endif // _VCF_COLUMNMODEL_H__


#define DEFAULTCOLUMNMODEL_CLASSID		"14b09dc3-777d-48cb-86d9-a311364cc41b"


namespace VCF  {

/**
\class DefaultColumnModel DefaultColumnModel.h "vcf/ApplicationKit/DefaultColumnModel.h"
*Class DefaultColumnModel documentation
*/
class APPLICATIONKIT_API DefaultColumnModel : public ColumnModel, public Persistable {
public:

	DefaultColumnModel();

	virtual ~DefaultColumnModel();
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


}; //end of namespace VCF


#endif // _VCF_DEFAULTCOLUMNMODEL_H__

/**
$Id$
*/
