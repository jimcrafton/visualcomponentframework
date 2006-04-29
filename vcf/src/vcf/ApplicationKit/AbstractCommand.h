#ifndef _VCF_ABSTRACTCOMMAND_H__
#define _VCF_ABSTRACTCOMMAND_H__
//AbstractCommand.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/Command.h"

namespace VCF  {

class UndoRedoStack;

/**
\class AbstractCommand AbstractCommand.h "vcf/ApplicationKit/AbstractCommand.h"
*A partial implementation of the Command interface.
*Useful for using as a base class when creating your own Command based
*classes.
*/
class APPLICATIONKIT_API AbstractCommand : public Object, public Command {
public:
	AbstractCommand();

	virtual ~AbstractCommand();

	virtual UndoRedoStack* getOwningStack() {
		return stack_;
	}

	virtual void setOwningStack( UndoRedoStack* stack ) {
		stack_ = stack;
	}

	virtual String getName() {
		return commandName_;
	}

	virtual void setName( const String& name ) {
		commandName_ = name;
	}

	virtual bool isUndoable() {
		return isUndoable_;
	}
protected:
	UndoRedoStack* stack_;
	String commandName_;
	bool isUndoable_;
private:
};


}; //end of namespace VCF


#endif // _VCF_ABSTRACTCOMMAND_H__

/**
$Id$
*/
