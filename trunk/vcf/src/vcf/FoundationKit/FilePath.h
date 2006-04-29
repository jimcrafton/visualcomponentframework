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
\class FilePath FilePath.h "vcf/FoundationKit/FilePath.h"
A FilePath represents a path to a file in the filesystem.

\par
FilePath collects some static functions used to split a filename
into its components, or to directly get those components.
Particular attention has been given to the performance.

\par
Beside that its an object storing a pathname in a Native ( Unix style ) 
format so that more complex operations can be performed without repetitions.
*/


	class FOUNDATIONKIT_API FilePath  { 
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
		
		/**
		Returns the string (usually a single character)
		that is used to separate the drive identifier
		from the rest of the path string. For example
		on Win32 systems this usually returns a ":"
		character.
		*/
		static String getDriveSeparator();
		
		/**
		Returns the string used to separate a directory
		identifiers in the format used internally by the 
		FilePath class. Note that this may be different than
		the directory seperator used natively by the OS. 
		For example, on a Win32 system the directory 
		separator is the "\" character.
		*/
		static String getDirectorySeparator() {
			return L"/";
		}
		
		/**
		Returns the string used to separate a directory
		identifiers in the format used natively by the OS. 
		For example, on a Win32 system the directory 
		separator is the "\" character.
		*/
		static String getDirectorySeparatorOSSpecific();
		
		static String getExtensionSeparator() {
			return L".";
		}
		
		/**
		Assigns a FilePath to another
		*/
		inline FilePath& operator= ( const FilePath& path ){
			filename_ = transformToNative( path.filename_ );
			return *this;
		}
		
		
		/**
		Assigns a string to a file path instance. Assumes
		the string value is actually some valid file path
		*/
		inline FilePath& operator= ( const String& filename ) {
			filename_ = transformToNative( filename );
			return *this;
		}

		inline FilePath& operator+= ( const String& filename ) {
			filename_ += transformToNative( filename );
			return *this;
		}
		
		/**
		Returns the string value of hte FilePath. This is done 
		by simply returning the value of the filename_
		member value.
		*/
		inline operator String () const {
			return filename_;
		}
		
		// Commented otherwise some compilers get confused ( warning C4927 vc70 ).
		//inline operator String& () {
		//	return filename_;
		//}
		
		
		/**
		Returns whether or not the value of the 
		FilePath is empty. This is equivalent 
		to a String::empty() function call.
		@see String::empty()
		*/
		bool empty() const {
			return filename_.empty();
		}
		
		
		
		/**
		returns the drivename for filesystems that support them (i.e.
		VMS and Win32) on 'nix systems this returns an empty string
		The 'DriveSeparator' character is excluded
		*/
		String getDriveName() const;
		
		
		/**
		Returns the directory portion of the file name including
		the 'DirectorySeparator' character at the end
		*/
		String getPathName( const bool& includeDriveName=false ) const;
		
		
		/**
		Returns the name component of the filename (i.e without
		path information )
		@param true to include the extension in the name
		*/
		String getBaseName( const bool& includeExtension=false ) const;
		
		
		/**
		Returns an extension. The extension is the
		\em last occurence of the "." to the end
		of the filename string. For example:<br>
		If the filename is : "foo/bar/baz.1.2a.text" then
		the return value will be ".text"
		@return String the file name extension including the "." character.
		If no extension is found returns an empty string.
		*/
		String getExtension() const ;
		
		
		/**
		Tells if a filename is a relative path.
		@param path the path to check
		@return true if the filename is a relative path
		*/
		static bool isRelativePath( const String& filename );
		
		/**
		Tells if the filename is a relative path.
		@return true if the filename is a relative path
		*/
		bool isRelativePath() const;
		
		/**
		Tells if a path is a directory name.
		A path is considered a directory name
		if the 'DirectorySeparator' character at the end.
		Returns true if the path is a directory name
		@param path the path to check
		@return true if the path is a directory name
		*/
		static bool isDirectoryName( const String& path );
		
		/**
		Returns true if the filename is a directory name.
		A file name is considered a directory name if the 
		'DirectorySeparator' character at the end.
		@return true if the path is a directory name
		*/
		bool isDirectoryName() const;
		
		/**
		returns the filename converted to the native format ('nix)
		The filename may not be a full path name. 
		@return the filename
		*/
		String getFileName() const{
			return filename_;
		}
		
		
		/**
		Returns the filename converted to the format specifically
		used internally by the FilePath. The format looks like:
		\verbatim
		[<drive_letter>:]/[dir1/][dir2/][dir_n/]
		\endverbatim
		The filename may not be a full path name.
		@return the converted string
		*/
		static String transformToNative( const String& filename );
		
		/**
		Converts the FilePath filename to the format specifically
		used internally by the FilePath. The format looks like:
		\verbatim
		[<drive_letter>:]/[dir1/][dir2/][dir_n/]
		\endverbatim
		The filename may not be a full path name
		@return the FilePath object itself
		*/
		FilePath& transformToNative();
		
		/**
		Returns the filename converted to the format specific 
		for the OS. The filename may not be a full path name
		@return the converted string
		*/
		static String transformToOSSpecific( const String& filename );
		
		/**
		converts the filename into the format specific for the OS
		The filename may not be a full path name
		@return the FilePath object itself
		*/
		FilePath& transformToOSSpecific();
		
		/**
		returns the pathname relative to the working path
		@param the path to transform.
		@param the working path. From this part it is taken only 
		the part on the left of the last DirectorySeparator
		to form the directory name.
		If not given then working path information is retrieved
		from the system.
		@return the transformed string
		@see FilePath::makeDirectoryName()
		*/
		static String getTransformedToRelativePathName( const String& fullPath, const String& workingPath=L"" );
		
		/**
		transform the pathname into one relative to the working path
		@param the working path.
		If not given then working path information is retrieved
		from the system
		@return the FilePath object itself
		*/
		FilePath& transformToRelativePathName( const String& workingPath=L"" );
		
		/**
		expand a relative pathname into a full pathname based on the working path
		@param the path to transform.
		@param the working path. From this part it is taken only 
		the part on the left of the last DirectorySeparator
		to form the directory name.
		If not given then working path information is retrieved
		from the system
		@return the transformed string
		@see FilePath::makeDirectoryName()
		*/
		static String getExpandedRelativePathName( const String& fullPath, const String& workingPath=L"" );
		
		/**
		transform a relative pathname into a full pathname based on the working path
		@param the working path.
		If not given then working path information is retrieved
		from the system
		@return the FilePath object itself
		*/
		FilePath& expandRelativePathName( const String& workingPath=L"" );
		
		/**
		separates a path into a vector filled by its components
		i.e. the subdirectories composing the path.
		each one of them with the 'DirectorySeparator' character at the end
		Drive and filetitle are excluded.
		@param fullname the full filename to separate
		@return the vector containing the components
		*/
		static std::vector<String> getPathComponents( const String& fullpath );
		
		/**
		separates a path into a vector filled by its components
		i.e. the subdirectories composing the path.
		each one of them with the 'DirectorySeparator' character at the end
		Drive and filetitle are excluded.
		@return the vector containing the components
		*/
		std::vector<String> getPathComponents() const;

		
		/**
		Ensures a path has a 'DirectorySeparator' as its final character.
		Under Win32 it tests against both the '/' and '\' characters.
		The VCF uses the convention that directory names must be terminated
		with a 'DirectorySeparator' character.
		@param fullname the full filename
		@param remove, false to ensure that the name has the directory 
		character at the end, true to remove the existing directory separator 
		at the end if present.
		@return the changed fullname. Which is empty if the original one was 
		empty too.
		*/
		static String makeDirectoryName( const String& fullname, const bool& remove = false );
		
		
		/**
		Split a full fullname into its drive and path components.
		The expression ( fullname == drive + pathname ) is invariant.
		Under Win32 it tests against both the '/' and '\' characters.
		@param fullname the full filename to split
		@param drive gather the drive component, which is everything ending at the 
		\em last 'DirectorySeparator' character ( this one included )
		drive is empty if the filesystem does not support it ( as in the 'nix' syztems ).
		@param pathname everything after that separator ( excluded )
		*/
		static void splitDrive( const String& fullname, String& drive, String& pathname );
		
		/**
		Splits a full fullname into its path and filename components.
		The expression ( fullname == path + filename ) is invariant.
		Under Win32 it tests against both the '/' and '\' characters.
		@param fullname the full filename to split
		@param path gather the path component, which is everything ending at the 
		     \em last '\\' or '/' character separator ( this one included )
		     Path is empty if there is no such separator.
		@param name everything after that separator ( excluded )
		*/
		static void splitPath( const String& fullname, String& path, String& name );
		
		/**
		* Splits a full fullname into its root and extension components.
		* The expression ( fullname == root + ext ) is invariant.
		* therefore ( as in Python ):
		\verbatim
		( root, ext ) = ( 'foo', '.txt' ) when fullname = 'foo.txt'
		( root, ext ) = ( 'foo', '' ) when fullname = 'foo', instead than: ( 'foo', '.' )
		\endverbatim
		@param fullname the full filename to split
		@param root everything before the \em last 'ExtensionSeparator' character (excluded).
		@param ext everything after that separator ( included )
		         The extension is empty if there is no such separator.
		*/
		static void splitExtension( const String& fullname, String& root, String& ext );
		
		
		
		
		/**
		returns the drivename for filesystems that support them (i.e.
		VMS and Win32) on 'nix systems this returns an empty string
		The 'DriveSeparator' character is excluded
		*/
		static String getDriveName( const String& fullname );
		
		
		/**
		returns the directory portion of the file name including
		the 'DirectorySeparator' character at the end
		*/
		static String getPathName( const String& fullname, const bool& includeDriveName=false );
		
		
		/**
		returns the name component of the filename (i.e without
		path information )
		@param true to include the extension in the name
		*/
		static String getBaseName( const String& fullname, const bool& includeExtension=false );
		
		
		/**
		returns an extension. The extension is the
		*\em last occurence of the "." to the end
		of the filename string. For example:<br>
		If the filename is : "foo/bar/baz.1.2a.text" then
		the return value will be ".text"
		@return String the file name extension including the "." character.
		If no extension is found returns an empty string
		*/
		static String getExtension( const String& fullname );
		
		
		
		
		
		/**
		* helper function to check if a filename matches a wildcards pattern
		* In the current implementation wildcards include only the '*' character.
		@param fullname the full filename to separate
		@return the vector containing the components
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


#endif // _VCF_FILEPATH_H__

/**
$Id$
*/
