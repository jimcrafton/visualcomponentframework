#ifndef _VCF_COMMANDGROUP_H__
#define _VCF_COMMANDGROUP_H__
//CommandGroup.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/AbstractCommand.h"

namespace VCF  {

/**
\class CommandGroup CommandGroup.h "vcf/ApplicationKit/CommandGroup.h"
*Class CommandGroup documentation
*/
class APPLICATIONKIT_API CommandGroup : public AbstractCommand {
public:
	CommandGroup();

	virtual ~CommandGroup();

	virtual void undo();

	virtual void redo();

	virtual void execute();

	void addCommand( Command* command ) {
		commands_.push_back( command );
	}
protected:
	std::vector<Command*> commands_;
private:
};


}; //end of namespace VCF


#endif // _VCF_COMMANDGROUP_H__

/**
$Id$
*/
