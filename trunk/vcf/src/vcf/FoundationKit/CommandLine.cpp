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
						arg.append( tmpArgStart, tmpArgEnd - tmpArgStart );
						tmpArgStart = tmpArgEnd;
					}
					tmpArgStart++;					
				}
				
				tmpArgEnd ++;
			}
			
			if ( arg.empty() ) {
				arg.append( tmpArgStart, tmpArgEnd - tmpArgStart );
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


bool CommandLine::isSwitch(const String& aParam)
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


bool CommandLine::hasSwitch(const String& aSwitch)
{
	CommandLineMap::iterator theIterator;
	theIterator = commandLine_.find(aSwitch);
	return (theIterator != commandLine_.end());
}


String CommandLine::getSafeArgument(const String& aSwitch, int index, const String& defaultVal)
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


String CommandLine::getArgument( int index )
{
	String result;
	if ( (index >= 0) && (index < originalCommandLine_.size()) ) {
		result = originalCommandLine_[index];
	}
	return result;
}

String CommandLine::getArgument( const String& aSwitch, int index )
{
   if ( hasSwitch( aSwitch ) )
   {
	   CommandLineMap::iterator theIterator = commandLine_.find(aSwitch);
	   if (theIterator!=commandLine_.end())
      {
         if ((int)(*theIterator).second.strings_.size() > index)
         {
            return (*theIterator).second.strings_[index];
         }
      }
   }

   throw (int)0;

   return "";
}


int CommandLine::getArgumentCount(const String& aSwitch)
{
	int result = -1;

	if ( hasSwitch(aSwitch) )  {
		CommandLineMap::iterator theIterator = commandLine_.find( aSwitch );
		if (theIterator!=commandLine_.end())      {
			result = (*theIterator).second.strings_.size();
		}
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/10 20:42:07  ddiego
*osx updates
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.1  2003/08/13 02:18:32  ddiego
*changed the way you start up the ApplicationKit a bit. now pass
*in the argc/argv parameters to the application instance constructor
*
*Revision 1.2  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.2  2003/05/30 04:13:11  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.1.2.1  2003/05/30 01:41:20  ddiego
*added Commandline.cpp
*
*/


