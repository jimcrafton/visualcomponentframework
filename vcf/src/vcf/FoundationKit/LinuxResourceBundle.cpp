
#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/FoundationKit/LinuxResourceBundle.h"
#include "vcf/FoundationKit/StringTokenizer.h"

using namespace VCF;

namespace 
{
    const String gResourceStringsFileName = "Resources.strings";
    void CleanString(String& str)
    {
        StringUtils::trimWhiteSpaces(str);
        str = StringUtils::trim(str, '\"');
    }
    void ParseResourceLine(const String& line, String& id, String& value)
    {
        StringTokenizer tok(line, "=");
        id = tok.nextElement();
        CleanString(id);
        value = tok.nextElement();
        CleanString(value);
    }
}

LinuxResourceBundle::LinuxResourceBundle():
	resourceHandle_(NULL)
{
}

LinuxResourceBundle::~LinuxResourceBundle()
{
}

String LinuxResourceBundle::getString( const String& resourceName )
{
    String result = resourceName;

    String resourceDir = System::findResourceDirectory();
    FilePath filePath(resourceDir+gResourceStringsFileName);

    if(File::exists(filePath)) {
        FileInputStream fis( filePath );
		TextInputStream tis(&fis);

        while(!tis.isEOS()) {
            String line;
            tis.readLine(line);
            String id, value;
            ParseResourceLine(line, id, value);
            if(resourceName == id) {
                result = value;
            }
        }
    }

	return result;
}

String LinuxResourceBundle::getVFF( const String& resourceName )
{
	String result;

	return result;
}

Resource* LinuxResourceBundle::getResource( const String& resourceName )
{
    String resourceDir = System::findResourceDirectory();
    FilePath filePath(resourceDir+resourceName);

    Resource* result = NULL;
    if(File::exists(filePath)) {
        FileInputStream fs(filePath);
        ulong32 size = fs.getSize();
        char* buf = new char[size];
        fs.read( (unsigned char*)buf, size );
    
    
        result = new Resource( buf, size, resourceName );
        delete [] buf;
    }
	return result;
}

ProgramInfo* LinuxResourceBundle::getProgramInfo()
{
	return NULL;
}
