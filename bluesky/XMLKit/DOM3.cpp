#include "XMLKit.h"



#include "DOM3.h"

#ifdef XMLKIT_DOM

using namespace VCF;
using namespace VCF::DOM;


struct DOMFeature {
	DOMString name;
	DOMString version;
};

void parseFeatureString( const DOMString& s, std::vector<DOMFeature>& features )
{
	AnsiString tmp = s;
	const char* P = tmp.c_str();
	const char* P2 = P;
	const char* start = P;

	features.clear();
	
	while ( (P-start) < tmp.length() ) {
		if ( ' ' == *P ) {
			DOMFeature f;
			f.name.assign( P2, P-P2 );

			while ( (P-start) < tmp.length() && (*P == ' ') ) {
				P++;
			}

			if ( ::isdigit(*P) ) {
				P2 = P;
				
				while ( (P-start) < tmp.length() && (*P != ' ') ) {
					P++;
				}

				f.version.assign( P2, P-P2 );
			}
			else {
				P--;
			}

			features.push_back( f );

		}
		P++;
	}
}


bool TypeInfo::isDerivedFrom(const DOMString& typeNamespaceArg, 
							const DOMString& typeNameArg, 
							int derivationMethod ) const 
{
	return false;
}

DOMImplementation* DOMImplementationSource::getDOMImplementation( const DOMString& features)
{
	DOMImplementation* result = NULL;
	std::map<DOMString,DOMImplementationList>::iterator it =
		data_.begin();
	while ( it != data_.end() ) {
		DOMImplementationList& list = it->second;
		for (size_t i=0;i<list.length();i++ ) {
			DOMImplementation* impl = list.item( i );

			std::vector<DOMFeature> featureList;

			parseFeatureString( features, featureList );

			result = NULL;
			std::vector<DOMFeature>::iterator it2 = featureList.begin();
			while ( it2 != featureList.end() ) {
				const DOMFeature& f = *it2;
				if ( impl->hasFeature( f.name, f.version ) ) {
					result = impl;
				}
				else {
					result = NULL;
				}
				++it2;
			}

			if ( result == impl ) {
				break;
			}
		}
		++it;
	}

	return result;
}

void DOMImplementation::registerFeature(const DOMString& feature, const DOMString& version, DOMObject* featureImpl)
{
	DOMString key = feature + "(" + version + ")";
	features_[key] = featureImpl;
}

bool DOMImplementation::hasFeature(const DOMString& feature, const DOMString& version)
{
	DOMString key = feature + "(" + version + ")";
	return features_.find( key ) != features_.end();
}

DocumentType* DOMImplementation::createDocumentType(const DOMString& qualifiedName, 
								 const DOMString& publicId, 
								 const DOMString& systemId)
{
	return NULL;
}

Document* DOMImplementation::createDocument(const DOMString& namespaceURI, 
						 const DOMString& qualifiedName, 
						 const DocumentType& doctype)
{
	return NULL;
}

// Introduced in DOM Level 3:
DOMObject* DOMImplementation::getFeature(const DOMString& feature, const DOMString& version)
{
	DOMString key = feature + "(" + version + ")";
	std::map<DOMString,DOMObject*>::iterator found = features_.find( key );
	if ( found != features_.end() ) {		
		return found->second;		
	}
	return NULL;
}


#endif //XMLKIT_DOM