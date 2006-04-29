#ifndef _VCF_COMMANDLINE_H__
#define _VCF_COMMANDLINE_H__
//CommandLine.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


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



namespace VCF {

// handy little container for our argument vector
struct CmdParam {
	std::vector<String> strings_;
};

/**
\class CommandLine CommandLine.h "vcf/FoundationKit/CommandLine.h"
A utility for parsing command lines.

This was originally written by Chris Losinger, changes were simply
removing the inheritance from std::map<>, and adding a map as a member
variable instead. Also made some cosmetic name changes to conform better with
VCF naming standards.

Example :

   Our example application uses a command line that has two
   required switches and two optional switches. The app should abort
   if the required switches are not present and continue with default
   values if the optional switches are not present.

      Sample command line :
      MyApp.exe -p1 text1 text2 -p2 "this is a big argument" -opt1 -55 -opt2

      Switches -p1 and -p2 are required.
      p1 has two arguments and p2 has one.

      Switches -opt1 and -opt2 are optional.
      opt1 requires a numeric argument.
      opt2 has no arguments.

      Also, assume that the app displays a 'help' screen if the '-h' switch
      is present on the command line.

\code
   #include "CmdLine.h"

   void main(int argc, char **argv)
   {
      // our cmd line parser object
      CommandLine cmdLine;

      // parse argc,argv
      if (cmdLine.splitLine(argc, argv) &lt; 1)
      {
         // no switches were given on the command line, abort
         ASSERT(0);
         exit(-1);
      }

      // test for the 'help' case
      if (cmdLine.HasSwitch("-h"))
      {
         show_help();
         exit(0);
      }

      // get the required arguments
      String p1_1, p1_2, p2_1;
      try
      {
         // if any of these fail, we'll end up in the catch() block
         p1_1 = cmdLine.getArgument("-p1", 0);
         p1_2 = cmdLine.getArgument("-p1", 1);
         p2_1 = cmdLine.getArgument("-p2", 0);

      }
      catch (...)
      {
         // one of the required arguments was missing, abort
         ASSERT(0);
         exit(-1);
      }

      // get the optional parameters

      // convert to an int, default to '100'
      int iOpt1Val =    atoi(cmdLine.getSafeArgument("-opt1", 0, 100));

      // since opt2 has no arguments, just test for the presence of
      // the '-opt2' switch
      bool bOptVal2 =   cmdLine.hasSwitch("-opt2");

      .... and so on....

   }
   \endcode
   @version 1.0 Chris Losinger
   @version 2.0 Jim Crafton
*/
class FOUNDATIONKIT_API CommandLine : public Object {

public:

	CommandLine() {}
	virtual ~CommandLine() {}

/**
parse the command line into switches and arguments.
@return int number of switches found
	*/
	int splitLine( int argc, char **argv );
	
	int splitLine( const String& commandLine );
	
	int splitLine( const std::vector<String>& commandLine );

	/**
	was the switch found on the command line ?
	\code
    ex. if the command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

      call                          return
      ----                          ------
      cmdLine.hasSwitch("-a")       true
      cmdLine.hasSwitch("-z")       false
	  \endcode
	  @return bool true if it has the swith, otherwise false
	*/
	bool hasSwitch( const String& aSwitch ) const ;

	/**
	fetch an argument associated with a switch . if the parameter at
	index iIdx is not found, this will return the default that you
    provide.
	
	example :
	\code
	command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

      call                                      return
      ----                                      ------
      cmdLine.getSafeArgument("-a", 0, "zz")    p1
      cmdLine.getSafeArgument("-a", 1, "zz")    p2
      cmdLine.getSafeArgument("-b", 0, "zz")    p4
      cmdLine.getSafeArgument("-b", 1, "zz")    zz
	  \endcode
	*/

	String getSafeArgument(const String& aSwitch, size_t iIdx, const String& aDefault) const;

	/**
	fetch a argument associated with a switch. throws an exception
	of (int)0, if the parameter at index iIdx is not found.
	
	example :
	\code
	command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

      call                             return
      ----                             ------
      cmdLine.getArgument("-a", 0)     p1
      cmdLine.getArgument("-b", 1)     throws (int)0, returns an empty string
	  \endcode
	*/
	String getArgument( const String& aSwitch, size_t iIdx ) const;

	String getArgument( size_t index ) const;

	/**
	@return the number of arguments found for a given switch. -1 if the
	switch was not found
	*/
	int getArgumentCount(const String& aSwitch) const;

	Enumerator<String>* getOriginalCommands() {
		return commandLineContainer_.getEnumerator();
	}



	size_t getArgCount() const {
		return originalCommandLine_.size();
	}
	
	const std::vector<String>& getOriginalCommandLine() const {
		return originalCommandLine_;
	}
protected:

/**
protected member function
test a parameter to see if it's a switch :
switches are of the form : -x
where 'x' is one or more characters.
the first character of a switch must be non-numeric!
	*/
	bool isSwitch(const String& param) const;
	typedef std::map<String, CmdParam> CommandLineMap;
	CommandLineMap commandLine_;
	std::vector<String> originalCommandLine_;
	EnumeratorContainer<std::vector<String>,String> commandLineContainer_;


};

};


#endif // _VCF_COMMANDLINE_H__

/**
$Id$
*/
