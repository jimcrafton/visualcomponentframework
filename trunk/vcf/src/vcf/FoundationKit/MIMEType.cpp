//MIMEType.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/MIMEType.h"

using namespace VCF;


std::map<String,String> MIMEType::registeredFileExtensions;


MIMEType::MIMEType()
{

}


MIMEType::MIMEType( const String& data )
{
	data_ = data;
}

MIMEType::MIMEType( const String& type, const String& subType )
{
	data_ = type + "/" + subType;
}

MIMEType::MIMEType( const String& type, const String& subType, const std::vector<Parameter>& parameters )
{
	data_ = type + "/" + subType;

	std::vector<Parameter>::const_iterator it = parameters.begin();
	while ( it != parameters.end() )  {
		const Parameter& param = *it;
		data_ += ";" + param.first + "=" + param.second;
		it ++;
	}
}

void MIMEType::setFromFileName( const FilePath& fileName )
{
	std::map<String,String>::iterator found =
		MIMEType::registeredFileExtensions.find( fileName.getExtension() );

	if ( found != MIMEType::registeredFileExtensions.end() ) {
		data_ = found->second;
	}
}

String MIMEType::getType() const
{
	String result;

	VCF_ASSERT( !data_.empty() ) ;

	int pos = data_.find_first_of("/");
	if ( pos != String::npos ) {
		result = data_.substr( 0, pos );
		StringUtils::trimWhiteSpaces( result );
	}

	return result;
}

String MIMEType::getSubType() const
{
	String result;

	VCF_ASSERT( !data_.empty() ) ;

	int pos = data_.find_first_of("/");
	if ( pos != String::npos ) {
		int pos2 = data_.find_first_of(";");
		if ( pos2 == String::npos ) {
			pos2 = data_.size();
		}
		result = data_.substr( pos+1, pos2-(pos+1) );
		StringUtils::trimWhiteSpaces( result );
	}

	return result;
}

std::vector<MIMEType::Parameter> MIMEType::getParameters() const
{
	std::vector<Parameter> result;

	VCF_ASSERT( !data_.empty() ) ;

	int pos = data_.find_first_of(";");

	if ( pos != String::npos ) {
		int pos2 = data_.find_first_of(";",pos+1);
		while ( (pos != String::npos) && (pos2!=String::npos) ) {

			MIMEType::Parameter parameter;
			String p = data_.substr( pos+1, pos2-(pos+1) );

			int pos3 = p.find_first_of("=");
			if ( pos3 != String::npos ) {
				parameter.first = p.substr(0,pos3);
				StringUtils::trimWhiteSpaces( parameter.first );

				parameter.second = p.substr(pos3+1,p.size()-(pos3+1));
				StringUtils::trimWhiteSpaces( parameter.second );

				result.push_back( parameter );
			}
			else {
				//throw exception! Malformed MIME Type
			}


			pos = pos2;

			pos2 = data_.find_first_of(";",pos+1);
		}

		if ( (pos!=String::npos) && (pos2==String::npos) ) {
			pos2 = data_.size();
			//last param
			MIMEType::Parameter parameter;
			String p = data_.substr( pos+1, pos2-(pos+1) );

			pos = p.find_first_of("=");
			if ( pos != String::npos ) {
				parameter.first = p.substr(0,pos);
				StringUtils::trimWhiteSpaces( parameter.first );

				parameter.second = p.substr(pos+1,p.size()-(pos+1));
				StringUtils::trimWhiteSpaces( parameter.second );

				result.push_back( parameter );
			}
			else {
				//throw exception! Malformed MIME Type
			}
		}
	}

	return result;
}

String MIMEType::canonicalValue( const String& value )
{
	String result;

	const VCFChar* P = value.c_str();
	const VCFChar* start = P;
	const VCFChar* current = P;

	int size = value.size();

	const int inQuotes = 1;
	const int inComments = 2;

	int state = 0;

	while ( (P-start) < size ) {
		switch ( *P ) {
			case '"' : {
				if ( state != inQuotes && (*(P-1) != '\\') ) {
					state = inQuotes;

					if ( (P-current) > 0 ) {
						result.append( current, (P-current)-1);
					}
					current = P+1;
				}
				else if ( state == inQuotes && *(P-1) != '\\' ) {
					state = 0;

					result.append( current, (P-current));
					current = P+1;

				}
			}
			break;

			case '(' : {
				if ( (state != inQuotes) && (state!=inComments) && (*(P-1) != '\\') ) {
					state = inComments;

					if ( (P-current) > 0 ) {
						result.append( current, (P-current)-1);
					}
				}
			}
			break;

			case ')' : {
				if ( (state != inQuotes) && (state==inComments) && (*(P-1) != '\\') ) {
					state = 0;
					current = P+1;
				}
			}
			break;

		}

		P++;
	}

	if ( current < P ) {
		result.append( current, P-current);
	}

	StringUtils::trimWhiteSpaces( result );

	return result;
}

bool MIMEType::compare( const MIMEType& rhs ) const
{
	bool result = true;

	if ( result ) {
		result = getType() == rhs.getType();
	}

	if ( result ) {
		result = getSubType() == rhs.getSubType();
	}


	if ( result ) {
		std::vector<MIMEType::Parameter> params = getParameters();
		std::vector<MIMEType::Parameter> rhsParams = rhs.getParameters();

		result = params.size() == rhsParams.size();

		if ( result ) {
			std::vector<MIMEType::Parameter>::iterator it = params.begin();
			std::vector<MIMEType::Parameter>::iterator rhsIt = rhsParams.begin();

			while ( it != params.end() ) {
				MIMEType::Parameter& p1 = *it;
				MIMEType::Parameter& p2 = *rhsIt;

				result = p1.first == p2.first;

				if ( result ) {
					String s1 = MIMEType::canonicalValue(p1.second);
					String s2 = MIMEType::canonicalValue(p2.second);
					result = s1 == s2;

					if ( !result ) {
						break;
					}
				}
				else {
					break;
				}

				it ++;
				rhsIt ++;
			}
		}
	}

	return result;
}


bool MIMEType::isTextType() const
{
	return getType() == "text";
}

bool MIMEType::isImageType() const
{
	return getType() == "image";
}

bool MIMEType::isAudioType() const
{
	return getType() == "audio";
}

bool MIMEType::isVideoType() const
{
	return getType() == "video";
}

bool MIMEType::isApplicationType() const
{
	return getType() == "application";
}

void MIMEType::registerExtension( const String& extension, const String& mimeType )
{
	MIMEType::registeredFileExtensions[extension] = mimeType;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


