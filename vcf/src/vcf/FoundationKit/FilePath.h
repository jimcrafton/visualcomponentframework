#ifndef _VCF_FILEPATH_H__
#define _VCF_FILEPATH_H__
//FilePath.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {




/**
*  A FilePath represents a path to a file in the filesystem.
*
*  FilePath collects some static functions used to split a filename
*  into its components, or to directly get those components.
*  Particular attention has been given to the performance.
*
*  Beside that its an object storing a pathname in a Native ( 'nix' ) format
*  so that more complex operations can be performed without repetitions.
*/


	class FOUNDATIONKIT_API FilePath : public VCF::Object {
	public:

		enum {
			DriveSeparator      = L':',
			DirectorySeparator	= L'/',
			ExtensionCharacter	= L'.',
		};
		
	public:
		FilePath();
		
		FilePath( const String& filename );
		
		FilePath( const FilePath& filePath );
		
		virtual ~FilePath();
		
		
		static String getDriveSeparator();
		
		static String getDirectorySeparator() {
			return L"/";
		}
		
		static String getDirectorySeparatorOSSpecific();
		
		static String getExtensionSeparator() {
			return L".";
		}
		
		inline FilePath& operator= ( const FilePath& path ){
			filename_ = transformToNative( path.filename_ );
			return *this;
		}
		
		
		inline FilePath& operator= ( const String& filename ) {
			filename_ = transformToNative( filename );
			return *this;
		}
		
		
		inline operator String () const {
			return filename_;
		}
		
		// Commented otherwise some compilers get confused ( warning C4927 vc70 ).
		//inline operator String& () {
		//	return filename_;
		//}
		
		
		bool empty() const {
			return filename_.empty();
		}
		
		
		
		/**
		*returns the drivename for filesystems that support them (i.e.
		*VMS and Win32) on 'nix systems this returns an empty string
		*The 'DriveSeparator' character is excluded
		*/
		String getDriveName() const;
		
		
		/**
		*returns the directory portion of the file name including
		*the 'DirectorySeparator' character at the end
		*/
		String getPathName( const bool& includeDriveName=false ) const;
		
		
		/**
		*returns the name component of the filename (i.e without
		*path information )
		*@param true to include the extension in the name
		*/
		String getBaseName( const bool& includeExtension=false ) const;
		
		
		/**
		*returns an extension. The extension is the
		*<b><i>last</i></b> occurence of the "." to the end
		*of the filename string. For example:<br>
		*If the filename is : "foo/bar/baz.1.2a.text" then
		*the return value will be ".text"
		*@return String the file name extension including the "." character.
		*If no extension is found returns an empty string
		*/
		String getExtension() const ;
		
		
		/**
		*tells if a filename is a relative path
		*@param path the path to check
		*@return true if the filename is a relative path
		*/
		static bool isRelativePath( const String& filename );
		
		/**
		*tells if the filename is a relative path
		*@return true if the filename is a relative path
		*/
		bool isRelativePath() const;
		
		/**
		*tells if a path is a directory name
		* (i.e. with the 'DirectorySeparator' character at the end )
		*returns true if the path is a directory name
		*@param path the path to check
		*@return true if the path is a directory name
		*/
		static bool isDirectoryName( const String& path );
		
		/**
		*returns true if the filename is a directory name
		* (i.e. with the 'DirectorySeparator' character at the end )
		*@return true if the path is a directory name
		*/
		bool isDirectoryName() const;
		
		/**
		*returns the filename converted to the native format ('nix)
		*The filename may not be a full path name
		*@return the filename
		*/
		String getFileName() const{
			return filename_;
		}
		
		
		/**
		*returns the filename converted to the format specific for the OS
		*The filename may not be a full path name
		*@return the converted string
		*/
		static String transformToNative( const String& filename );
		
		/**
		*converts the filename into the format specific for the OS
		*The filename may not be a full path name
		*@return the FilePath object itself
		*/
		FilePath& transformToNative();
		
		/**
		*returns the filename converted to the format specific for the OS
		*The filename may not be a full path name
		*@return the converted string
		*/
		static String transformToOSSpecific( const String& filename );
		
		/**
		*converts the filename into the format specific for the OS
		*The filename may not be a full path name
		*@return the FilePath object itself
		*/
		FilePath& transformToOSSpecific();
		
		/**
		*returns the pathname relative to the working path
		*@param the path to transform.
		*@param the working path. From this part it is taken only 
		* the part on the left of the last DirectorySeparator
		* to form the directory name.
		* If not given then working path information is retrieved
		* from the system.
		*@return the transformed string
		*@see FilePath::makeDirectoryName()
		*/
		static String getTransformedToRelativePathName( const String& fullPath, const String& workingPath=L"" );
		
		/**
		*transform the pathname into one relative to the working path
		*@param the working path.
		*If not given then working path information is retrieved
		*from the system
		*@return the FilePath object itself
		*/
		FilePath& transformToRelativePathName( const String& workingPath=L"" );
		
		/**
		*expand a relative pathname into a full pathname based on the working path
		*@param the path to transform.
		*@param the working path. From this part it is taken only 
		* the part on the left of the last DirectorySeparator
		* to form the directory name.
		*If not given then working path information is retrieved
		*from the system
		*@return the transformed string
		*@see FilePath::makeDirectoryName()
		*/
		static String getExpandedRelativePathName( const String& fullPath, const String& workingPath=L"" );
		
		/**
		*transform a relative pathname into a full pathname based on the working path
		*@param the working path.
		*If not given then working path information is retrieved
		*from the system
		*@return the FilePath object itself
		*/
		FilePath& expandRelativePathName( const String& workingPath=L"" );
		
		/**
		*separates a path into a vector filled by its components
		* i.e. the subdirectories composing the path.
		* each one of them with the 'DirectorySeparator' character at the end
		* Drive and filetitle are excluded.
		*@param fullname the full filename to separate
		*@return the vector containing the components
		*/
		static std::vector<String> getPathComponents( const String& fullpath );
		
		/**
		*separates a path into a vector filled by its components
		* i.e. the subdirectories composing the path.
		* each one of them with the 'DirectorySeparator' character at the end
		* Drive and filetitle are excluded.
		*@return the vector containing the components
		*/
		std::vector<String> getPathComponents() const;


		
		
			
	public:
		/**
		* ensures a path to have the 'DirectorySeparator' as its final character.
		* Under windows it tests against both the '/' and '\' characters.
		* With VCF the convention is that directory names must be terminated
		* with a 'DirectorySeparator' character.
		*@param fullname the full filename
		*@param remove, false to ensure that the name has the directory character at the end,
		*true to remove the existing directory separator at the end if present.
		*@return the changed fullname. Which is empty if the original one was empty too.
		*/
		static String makeDirectoryName( const String& fullname, const bool& remove = false );
		
		
	public:
		
		/**
		* Split a full fullname into its drive and path components.
		* The expression ( fullname == drive + pathname ) is invariant.
		* Under Windows it tests against both the '/' and '\' characters.
		*@param fullname the full filename to split
		*@param drive gather the drive component, which is everything ending at the 
		*       <b><i>last</i></b> 'DirectorySeparator' character ( this one included )
		*       drive is empty if the filesystem does not support it ( as in the 'nix' syztems ).
		*@param pathname everything after that separator ( excluded )
		*/
		static void splitDrive( const String& fullname, String& drive, String& pathname );
		
		/**
		* Splits a full fullname into its path and filename components.
		* The expression ( fullname == path + filename ) is invariant.
		* Under windows it tests against both the '/' and '\' characters.
		*@param fullname the full filename to split
		*@param path gather the path component, which is everything ending at the 
		*       <b><i>last</i></b> '\\' or '/' character separator ( this one included )
		*       Path is empty if there is no such separator.
		*@param name everything after that separator ( excluded )
		*/
		static void splitPath( const String& fullname, String& path, String& name );
		
		/**
		* Splits a full fullname into its root and extension components.
		* The expression ( fullname == root + ext ) is invariant.
		* therefore ( as in Python ):
		*       ( root, ext ) = ( 'foo', '.txt' ) when fullname = 'foo.txt'
		*       ( root, ext ) = ( 'foo', '' ) when fullname = 'foo', instead than: ( 'foo', '.' )
		*@param fullname the full filename to split
		*@param root everything before the <b><i>last</i></b> 'ExtensionSeparator' character (excluded).
		*@param ext everything after that separator ( included )
		*           The extension is empty if there is no such separator.
		*/
		static void splitExtension( const String& fullname, String& root, String& ext );
		
		
		
		
		/**
		*returns the drivename for filesystems that support them (i.e.
		*VMS and Win32) on 'nix systems this returns an empty string
		*The 'DriveSeparator' character is excluded
		*/
		static String getDriveName( const String& fullname );
		
		
		/**
		*returns the directory portion of the file name including
		*the 'DirectorySeparator' character at the end
		*/
		static String getPathName( const String& fullname, const bool& includeDriveName=false );
		
		
		/**
		*returns the name component of the filename (i.e without
		*path information )
		*@param true to include the extension in the name
		*/
		static String getBaseName( const String& fullname, const bool& includeExtension=false );
		
		
		/**
		*returns an extension. The extension is the
		*<b><i>last</i></b> occurence of the "." to the end
		*of the filename string. For example:<br>
		*If the filename is : "foo/bar/baz.1.2a.text" then
		*the return value will be ".text"
		*@return String the file name extension including the "." character.
		*If no extension is found returns an empty string
		*/
		static String getExtension( const String& fullname );
		
		
		
		
		
		/**
		* helper function to check if a filename matches a wildcards pattern
		* In the current implementation wildcards include only the '*' character.
		*@param fullname the full filename to separate
		*@return the vector containing the components
		*/
		static bool wildCharsMatchName( const String& filename, const String& wildChars );
		
		
	protected:
		String filename_;
	};


///////////////////////////////////////////////////////////////////////////////
// inlines

/*static*/ inline String FilePath::getDirectorySeparatorOSSpecific() {
#ifdef WIN32
	return L"\\";
#else
	return L"/";
#endif
}

inline bool FilePath::isRelativePath() const
{
	return FilePath::isRelativePath( filename_ );
}

inline bool FilePath::isDirectoryName() const
{
	return FilePath::isDirectoryName( filename_ );
}

inline String FilePath::getDriveName() const
{
	return FilePath::getDriveName( filename_ );
}

inline String FilePath::getPathName( const bool& includeDriveName ) const
{
	return FilePath::getPathName( filename_, includeDriveName );
}

inline String FilePath::getBaseName( const bool& includeExtension ) const
{
	return FilePath::getBaseName( filename_, includeExtension );
}

inline String FilePath::getExtension() const
{
	return FilePath::getExtension( filename_ );
}

inline FilePath& FilePath::transformToNative()
{
	filename_ = FilePath::transformToNative( filename_ );
	return (*this);
}

inline FilePath& FilePath::transformToOSSpecific()
{
	filename_ = FilePath::transformToOSSpecific( filename_ );
	return (*this);
}

inline FilePath& FilePath::transformToRelativePathName( const String& workingPath )
{
	filename_ = FilePath::getTransformedToRelativePathName( filename_, workingPath );
	return (*this);
}

inline FilePath& FilePath::expandRelativePathName( const String& workingPath )
{
	filename_ = FilePath::getExpandedRelativePathName( filename_, workingPath );
	return (*this);
}

inline std::vector<String> FilePath::getPathComponents() const {
	return FilePath::getPathComponents( getPathName() );
}




}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/10 19:09:45  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2.2.2  2004/11/10 01:55:43  marcelloptr
*[bugfix: 1063548] FilePath crashes on relative non Native paths
*
*Revision 1.2.2.1  2004/09/17 11:38:06  ddiego
*added program info support in library and process classes.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/18 14:45:19  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.2  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5.4.1  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.5  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.4  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.4.4.3  2003/09/19 21:24:21  ddiego
*small changes
*
*Revision 1.4.4.2  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.4.4.1  2003/08/23 12:44:22  marcelloptr
*improved comments in FilePath
*
*Revision 1.4  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.10.2  2003/03/23 03:23:53  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.10.1  2003/03/12 03:11:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.4.4  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.2.4.3  2002/07/16 04:23:18  ddiego
*modified FilePath to get the drivename and path name in one fucntion
*will correctly ignore the drive separator in non WIN32 systems
*mods ot VCFBuilder to load external projects within a workspace
*using relative paths ! - this needs to be migrated over to xmake
*as well
*
*Revision 1.2.4.2  2002/07/15 04:06:14  ddiego
*fixing saving the various project file ot take advantage to relative path
*and the FilePath object
*
*Revision 1.2.4.1  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.2  2002/06/24 04:24:49  ddiego
*mods to VCFBuilder
*
*Revision 1.1  2002/06/18 21:18:32  ddiego
*added FilePath
*/


#endif // _VCF_FILEPATH_H__


