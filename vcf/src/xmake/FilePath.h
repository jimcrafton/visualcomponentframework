
/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/

//FilePath.h



#ifndef _FILEPATH_H__
#define _FILEPATH_H__



namespace xmake {

	class FilePath  {
	public:

		enum {
			DirectorySeparator	= '/',
			ExtensionCharacter	= '.',
			DriveSeparator		= ':'
		};

		FilePath();

		FilePath( const String& filename );

		FilePath( const FilePath& filePath );

		virtual ~FilePath();


		static String getDirectorySeparator() {
			return "/";
		}

		static String getDriveSeparator();

		static String getExtensionSeparator() {
			return ".";
		}


		inline FilePath& operator= ( const FilePath& path ){
			filename_ = path.filename_;
			convertToNative(filename_);
			return *this;
		}


		inline FilePath& operator= ( const String& filename ) {
			filename_ = filename;
			convertToNative(filename_);
			return *this;
		}


		inline operator String () const {
			return filename_;
		}


		inline operator String& () {
			return filename_;
		}


		bool empty() const {
			return filename_.empty();
		}

		

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
		*returns the name component of the filename. 
		*/
		String getName( const bool& includeExtension=false ) const;



		/**
		*returns the drivename for filesystems that support them (i.e. 
		*VMS and Win32) on 'nix systems this returns an empty string
		*/
		String getDriveName() const;


		/**
		*returns the directory portion of the file name 
		*/
		String getPathName( const bool& includeDriveName=false ) const;


		bool doesFileExist() const;

		bool isRelativePath() const;

		bool isDirectory() const;

		String getFileName() const{
			return filename_;
		}		

		String transformToRelativePathName( const String& workingPath="" ) const;

		String transformToOSSpecific() const;

		String expandRelativePathName( const String& workingPath="" ) const;

		std::vector<String> getPathComponents() const {
			return separatePathComponents( getPathName() );
		}

	protected:
		std::vector<String> separatePathComponents( const String& path ) const;

		void convertToNative( String& filename ) const;		

		String filename_;

	};

};





#endif //_FILEPATH_H__


