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
\par
A utility for parsing command lines.
\par
This was originally written by Chris Losinger, changes were simply
removing the inheritance from std::map<>, and adding a map as a member
variable instead. Also made some cosmetic name changes to conform better with
VCF naming standards.
\par
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
	bool hasSwitch( const String& aSwitch );

	/**
	fetch an argument associated with a switch . if the parameter at
	index iIdx is not found, this will return the default that you
    provide.
	\par
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

	String getSafeArgument(const String& aSwitch, int iIdx, const String& aDefault);

	/**
	fetch a argument associated with a switch. throws an exception
	of (int)0, if the parameter at index iIdx is not found.
	\par
	example :
	\code
	command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

      call                             return
      ----                             ------
      cmdLine.getArgument("-a", 0)     p1
      cmdLine.getArgument("-b", 1)     throws (int)0, returns an empty string
	  \endcode
	*/
	String getArgument( const String& aSwitch, int iIdx );

	String getArgument( int index );

	/**
	@return the number of arguments found for a given switch. -1 if the
	switch was not found
	*/
	int getArgumentCount(const String& aSwitch);

	Enumerator<String>* getOriginalCommands() {
		return commandLineContainer_.getEnumerator();
	}



	unsigned long getArgCount() {
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
	bool isSwitch(const String& param);
	typedef std::map<String, CmdParam> CommandLineMap;
	CommandLineMap commandLine_;
	std::vector<String> originalCommandLine_;
	EnumeratorContainer<std::vector<String>,String> commandLineContainer_;


};

};


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.4  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/04/18 04:24:27  dougtinkham
*Added constructor and destructor to remove Internal Compiler Error on DMC
*
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
*Revision 1.1.2.4  2004/07/20 02:30:31  ddiego
*made some minor changes to Directories example, per Marcello.
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.1  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.3  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.2.2.2  2003/08/14 01:13:32  ddiego
*added the Thread::pause method back
*
*Revision 1.2.2.1  2003/08/13 02:18:31  ddiego
*changed the way you start up the ApplicationKit a bit. now pass
*in the argc/argv parameters to the application instance constructor
*
*Revision 1.2  2003/08/09 02:56:44  ddiego
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
*Revision 1.1.2.1  2003/05/30 01:39:44  ddiego
*added CommandLine.h
*
*/


#endif // _VCF_COMMANDLINE_H__


