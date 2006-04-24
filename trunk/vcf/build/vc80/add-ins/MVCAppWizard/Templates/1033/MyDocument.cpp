#include "vcf/ApplicationKit/ApplicationKit.h"
#include "[!output PROJECT_NAME]Document.h"

using namespace VCF;

[!output PROJECT_NAME]Document::[!output PROJECT_NAME]Document()
{

}

[!output PROJECT_NAME]Document::~[!output PROJECT_NAME]Document()
{

}

void [!output PROJECT_NAME]Document::initNew()
{

}

void [!output PROJECT_NAME]Document::empty()
{
	Document::empty();
}

bool [!output PROJECT_NAME]Document::saveAsType( const VCF::String& fileType, VCF::OutputStream& stream )
{
	return false;
}

bool [!output PROJECT_NAME]Document::openFromType( const VCF::String& fileType, VCF::InputStream& stream )
{
	return false;
}


