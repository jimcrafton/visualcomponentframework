
#ifndef _VCF_PROGRAMINFO_H__
#define _VCF_PROGRAMINFO_H__

namespace VCF {
	/**
	\par
	This class provides a platform neutral way to access additional
	information about a program, most intended to displayed in a
	human readable format. 
	\par
	The actual information may come from a number of different sources,
	some of which are platform dependant. These may include:
		\li binary resource data embedded directly into the executable
		such as Win32 resources (see VS_VERSIONINFO and GetFileVersionInfo)
		\li external files such as Mac OS X Info.plist files. 
	\par
	You should never create a new instance of this by hand. Instead you should 
	retrieve this from the Sytem's resource bundle.
	@see System::getResourceBundle
	@see ResourceBundle::getProgramInfo
	*/
	class FOUNDATIONKIT_API ProgramInfo : public Object {
	public:

		ProgramInfo( const String& programName, 
						const String& programFileName, 
						const String& author,
						const String& copyright,
						const String& company,
						const String& description,
						const String& programVersion,
						const String& fileVersion):
							programName_(programName),
							programFileName_(programFileName),
							author_(author),
							copyright_(copyright),
							company_(company),
							description_(description),
							programVersion_(programVersion),
							fileVersion_(fileVersion){}



		String getProgramName() const {
			return programName_;
		}

		/**
		*The name of the author of the package
		*/
		String getAuthor()  const {
			return author_;
		}

		/**
		*the copyright, if any, for the package
		*/
		String getCopyright()  const {
			return copyright_;
		}

		/**
		*The name of the company responsible for the package
		*/
		String getCompany()  const {
			return company_;
		}

		String getDescription() const  {
			return description_;
		}

		String getFileVersion() const {
			return fileVersion_;
		}

		String getProgramVersion() const {
			return programVersion_;
		}

		String getProgramFileName() const {
			return programFileName_;	
		}
	protected:
		String programName_;
		String programFileName_;
		String author_;
		String copyright_;
		String company_;
		String description_;
		String programVersion_;
		String fileVersion_;
	};


};



#endif //_VCF_PROGRAMINFO_H__

