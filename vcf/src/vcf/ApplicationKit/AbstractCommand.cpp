//AbstractCommand.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;


AbstractCommand::AbstractCommand()
{
	stack_ = NULL;
	isUndoable_ = true;
	commandName_ = "";
}

AbstractCommand::~AbstractCommand()
{

}


/**
$Id$
*/
