//CommandLine.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/*
  Original code from Chris Losinger's CCmdLine class

 Copyright (C) 1999 Chris Losinger, Smaller Animals Software.
   http://www.smalleranimals.com

   This software is provided 'as-is', without any express
   or implied warranty.  In no event will the authors be
   held liable for any damages arising from the use of this software.

   Permission is granted to anyone to use this software
   for any purpose, including commercial applications, and
   to alter it and redistribute it freely, subject to the
   following restrictions:

     1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment
   in the product documentation would be appreciated but is not required.

     2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.

     3. This notice may not be removed or altered from any source
   distribution.

*/
#include "vcf/FoundationKit/FoundationKit.h"


using namespace VCF;

int CommandLine::splitLine( const std::vector<String>& commandLine )
{
	commandLine_.clear();
	originalCommandLine_.clear();
	commandLineContainer_.initContainer( originalCommandLine_ );
	
	originalCommandLine_ = commandLine;
	
	String curParam; // current argv[x]
	int argc = originalCommandLine_.size();
	// skip the exe name (start with i = 1)
	for (int i = 1; i < argc; i++)  {
		// if it's a switch, start a new CommandLine
		if ( isSwitch(originalCommandLine_[i]))  {
			curParam = originalCommandLine_[i];
			
			String arg;
			
			// look at next input string to see if it's a switch or an argument
			if (i + 1 < argc)  {
				if (!isSwitch(originalCommandLine_[i + 1])) {
					// it's an argument, not a switch
					arg = originalCommandLine_[i + 1];
					
					// skip to next
					i++;
				}
				else {
					arg = "";
				}
			}
			
			// add it
			CmdParam cmd;
			
			// only add non-empty args
			if (arg != "")  {
				cmd.strings_.push_back(arg);
			}
			
			// add the CmdParam to 'this'
			std::pair<CommandLineMap::iterator, bool> res = commandLine_.insert(CommandLineMap::value_type(curParam, cmd));
			
		}
		else  {
			// it's not a new switch, so it must be more stuff for the last switch
			
			// ...let's add it
			CommandLineMap::iterator theIterator;
			
			// get an iterator for the current param
			theIterator = commandLine_.find(curParam);
			if (theIterator!=commandLine_.end())  {
				(*theIterator).second.strings_.push_back(originalCommandLine_[i]);
			}
			else  {
				// ??
			}
		}
	}
	
	return commandLine_.size();
}


int CommandLine::splitLine( int argc, char **argv )
{
	std::vector<String> args;
	
	for ( int j=0;j<argc;j++ ) {
		args.push_back( String(argv[j]) );
	}
	
	return splitLine( args );
}

int CommandLine::splitLine( const String& commandLine )
{
	std::vector<String> args;
	const VCF::WideChar* P = commandLine.c_str();
	const VCF::WideChar* start = P;
	const VCF::WideChar* argStart = P;
	
	int sz = commandLine.size();
	while ( (P - start) < sz ) {
		if ( *P == '\"' ) {
			P++;
			while ( ((P - start) < sz) && (*P != '\"' ) ) {
				P++;
			}
			P++;
		}
		
		if ( *P == '\"' ) {
			continue; //loop again
		}
		
		if ( *P == ' ' ) {
			//argument
			//strip out begin/end quotes
			
			String arg;
			const VCF::WideChar* tmpArgStart = argStart;
			const VCF::WideChar* tmpArgEnd = tmpArgStart;
			while ( tmpArgEnd < P ) {
				if ( *tmpArgEnd == '\"' ) {
					if ( tmpArgStart != tmpArgEnd ) {
						arg = arg.append( tmpArgStart, tmpArgEnd - tmpArgStart );
						tmpArgStart = tmpArgEnd;
					}
					tmpArgStart++;					
				}
				
				tmpArgEnd ++;
			}
			
			if ( arg.empty() ) {
				arg.assign( tmpArgStart, tmpArgEnd - tmpArgStart );
			}
			
			args.push_back( arg );
			
			while ( (*P == ' ') && ((P - start) < sz) ) {
				P++;
			}
			argStart = P;
			P--;
		}
		
		P++;
	}
	if ( argStart < P ) {
		String arg;
		arg.assign( argStart, P-argStart );
		args.push_back( arg );
	}
	
	return splitLine( args );
}


bool CommandLine::isSwitch(const String& aParam) const
{
   if (aParam.empty())
      return false;

   // switches must non-empty
   // must have at least one character after the '-'

   if (aParam.size() <= 1)  {
      return false;
   }

   // switches always start with '-'
   if (aParam[0]=='-')   {
      // allow negative numbers as arguments.
      // ie., don't count them as switches
      return (!isdigit(aParam[1]));
   }
   else   {
      return false;
   }
}


bool CommandLine::hasSwitch(const String& aSwitch) const
{
	String aParam = aSwitch;
	if ( aParam[0] != '-' )   {
		aParam.insert(0,"-");
	}

	CommandLineMap::const_iterator theIterator = commandLine_.find(aParam);
	return (theIterator != commandLine_.end());
}


String CommandLine::getSafeArgument(const String& aSwitch, size_t index, const String& defaultVal) const
{
   String result;

   if ( !defaultVal.empty() ) {
	   result = defaultVal;
   }

   try
   {
      result = getArgument(aSwitch, index);
   }
   catch (...)
   {
   }

   return result;
}


String CommandLine::getArgument( size_t index ) const
{
	String result;
	if ( (index >= 0) && (index < originalCommandLine_.size()) ) {
		result = originalCommandLine_[index];
	}
	return result;
}

String CommandLine::getArgument( const String& aSwitch, size_t index )const 
{
   if ( hasSwitch( aSwitch ) )
   {
	   CommandLineMap::const_iterator theIterator = commandLine_.find(aSwitch);
	   if (theIterator!=commandLine_.end())
      {
         if ((*theIterator).second.strings_.size() > index)
         {
            return (*theIterator).second.strings_[index];
         }
      }
   }

   throw (int)0;

   return "";
}


int CommandLine::getArgumentCount(const String& aSwitch) const
{
	int result = -1;

	if ( hasSwitch(aSwitch) )  {
		CommandLineMap::const_iterator theIterator = commandLine_.find( aSwitch );
		if (theIterator!=commandLine_.end())      {
			result = (*theIterator).second.strings_.size();
		}
	}

	return result;
}


/**
$Id$
*/
