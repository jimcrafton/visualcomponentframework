#ifndef _VCF_SYSTEMPEER_H__
#define _VCF_SYSTEMPEER_H__
//SystemPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class DateTime;
class ResourceBundle;

/**
*Defines the SYstem Peer interface
*/
class FOUNDATIONKIT_API SystemPeer {
public:
	virtual ~SystemPeer(){};
	/**
	*tries to return a long representing the current tick count of the system
	*/
	virtual unsigned long getTickCount()=0;

	/**
	*causes the calling thread to pause for the
	*specified number of milliseconds
	*@param unsigned int the number of milliseconds to pause the thread
	*/
	virtual void sleep( const uint32& milliseconds ) = 0;

	virtual bool doesFileExist( const String& fileName ) = 0;

	virtual String getEnvironmentVariable( const String& variableName ) = 0;

	virtual void setEnvironmentVariable( const String& variableName, const String& newValue ) = 0;

	virtual void addPathDirectory( const String& directory ) = 0;

	virtual String getCurrentWorkingDirectory() = 0;

	virtual void setCurrentWorkingDirectory( const String& currentDirectory ) = 0;

	virtual void setDateToSystemTime( DateTime* date ) = 0;

	virtual void setDateToLocalTime( DateTime* date ) = 0;

	virtual void setCurrentThreadLocale( Locale* locale ) = 0;

	virtual bool isUnicodeEnabled() = 0;

	virtual DateTime convertUTCTimeToLocalTime( const DateTime& date ) = 0;	

	virtual DateTime convertLocalTimeToUTCTime( const DateTime& date ) = 0;	

	virtual String getOSName() = 0;
	virtual String getOSVersion() = 0;

	virtual ProgramInfo* getProgramInfoFromFileName( const String& fileName ) = 0;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:41  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.2.2.3  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.2.2.2  2004/08/27 03:50:46  ddiego
*finished off therest of the resource refactoring code. We
*can now load in resoruces either from the burned in data in the .exe
*or from resource file following the Apple bundle layout scheme.
*
*Revision 1.2.2.1  2004/08/21 21:06:53  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/19 04:08:53  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.15.2.2  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.15.2.1  2004/04/21 02:17:24  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.15  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.14  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.13.2.1  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*Revision 1.13  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.6.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.12  2003/02/26 04:30:43  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.2.1  2002/12/27 23:04:44  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.11  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.10.4.1  2002/09/18 21:50:57  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.10  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.12.1  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.9  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SYSTEMPEER_H__


