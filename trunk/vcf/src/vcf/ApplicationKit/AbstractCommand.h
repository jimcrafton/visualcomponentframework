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


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.6.4.1  2003/09/12 00:09:31  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.6  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.22.1  2003/03/12 03:09:11  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTCOMMAND_H__


