//CommandGroup.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//CommandGroup.h
#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

CommandGroup::CommandGroup()
{

}

CommandGroup::~CommandGroup()
{
	std::vector<Command*>::iterator it = commands_.begin();
	while ( it != commands_.end() ) {
		Command* command = *it;
		delete command;
		command = NULL;
		it++;
	}
}

void CommandGroup::undo()
{
	std::vector<Command*>::reverse_iterator it = commands_.rbegin();
	while ( it != commands_.rend() ) {
		Command* command = *it;
		command->undo();
		it++;
	}
}

void CommandGroup::redo()
{
	std::vector<Command*>::iterator it = commands_.begin();
	while ( it != commands_.end() ) {
		Command* command = *it;
		command->redo();
		it++;
	}
}

void CommandGroup::execute()
{
	std::vector<Command*>::iterator it = commands_.begin();
	while ( it != commands_.end() ) {
		Command* command = *it;
		command->execute();
		it++;
	}
}


/**
$Id$
*/
