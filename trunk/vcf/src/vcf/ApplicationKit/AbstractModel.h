#ifndef _VCF_ABSTRACTMODEL_H__
#define _VCF_ABSTRACTMODEL_H__
//AbstractModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {




#define ABSTRACTMODEL_CLASSID	"b4ce8bb3-0e9f-4b4a-a246-b8faef0abf1a"

/**
\class AbstractModel AbstractModel.h "vcf/ApplicationKit/AbstractModel.h"
The AbstractModel is a base class for creating your own custom model
classes. It provides a basic implementation of some of the
Model class's methods.

@delegates
	@del AbstractModel::ModelChanged
	@del AbstractModel::ModelValidate
*/
class APPLICATIONKIT_API AbstractModel : public Model {
public:

	virtual void addModelValidationHandler( EventHandler* handler ) {
		ModelValidate +=  handler;
	}

	virtual void removeModelValidationHandler( EventHandler* handler ) {
		ModelValidate -=  handler;
	}

	virtual void addModelHandler( EventHandler* handler ) {
		ModelChanged +=  handler;
	}

	virtual void removeModelHandler( EventHandler* handler ) {
		ModelChanged -=  handler;
	}

	virtual void validate() {
		ValidationEvent e( this );
		ModelValidate.fireEvent( &e );
	}

	virtual void empty() {
		ModelEvent e( this, Model::MODEL_EMPTIED );
		changed( &e );
	}

};



};


#endif // _VCF_ABSTRACTMODEL_H__

/**
$Id$
*/
