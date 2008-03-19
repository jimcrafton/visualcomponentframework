//Dictionary.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"

using namespace VCF;

Dictionary::Dictionary():
	ownsObjectValues_(false)
{
	dataContainer_.initContainer( data_ );
}

Dictionary::~Dictionary()
{
	clear();
}

Dictionary::Dictionary( const Dictionary& rhs ):
	Object(rhs),
	ownsObjectValues_(false)
{
	dataContainer_.initContainer( data_ );
	*this = rhs;
}

Dictionary& Dictionary::operator=( const Dictionary& rhs )
{
	data_ = rhs.data_;
	ownsObjectValues_ = rhs.ownsObjectValues_;

	return *this;
}



Dictionary::size_type Dictionary::size() const
{
	return data_.size();
}

Dictionary::size_type Dictionary::max_size() const
{
	return data_.max_size();
}

bool Dictionary::empty() const
{
	return data_.empty();
}



void Dictionary::clear()
{
	if ( ownsObjectValues_ ) {
		DictionaryMap::iterator it = data_.begin();
		while ( it != data_.end() ) {
			Dictionary::pair& item = *it;
			
			if ( pdObject == item.second.type ) {
				Object* o = item.second;
				if ( NULL != o ) {
					o->free();
				}
			}
			
			it ++;
		}
	}

	data_.clear();
}

void Dictionary::loadFromStream( InputStream* stream, const MIMEType& type )
{
	int dictSize = 0;

	stream->read( dictSize );

	for ( int i=0;i<dictSize;i++ ) {
		String name;
		stream->read( name );

		VariantData vd;

		VariantDataInputStream vdis(stream);
		vdis.readVariantData( &vd );

		data_[name] = vd;
	}
}

void Dictionary::saveToStream( OutputStream* stream, const MIMEType& type )
{
	DictionaryMap::iterator it = data_.begin();

	stream->write( (int)data_.size() );

	while ( it != data_.end() ) {
		Dictionary::pair& item = *it;

		stream->write( item.first );

		VariantDataOutputStream vdos(stream);
		vdos.writeVariantData( &item.second );

		it ++;
	}
}

Dictionary::Value& Dictionary::operator[](const Dictionary::Key& key)
{
	return data_[key];
}

Dictionary::Value Dictionary::operator[](const Dictionary::Key& key) const
{
	Dictionary::Value result;

	DictionaryMap::const_iterator found = data_.find( key );
	if ( found != data_.end() ) {
		result = found->second;
	}

	return result;
}


Dictionary::Value& Dictionary::get(const Dictionary::Key& key)
{
	return data_[key];
}

Dictionary::Value Dictionary::get(const Dictionary::Key& key) const
{
	Dictionary::Value result;

	DictionaryMap::const_iterator found = data_.find( key );
	if ( found != data_.end() ) {
		result = found->second;
	}

	return result;
}

bool Dictionary::keyExists(const Key& key) const
{
	DictionaryMap::const_iterator found = data_.find( key );

	return found != data_.end();
}


void Dictionary::insert( const Dictionary::Key& key, const Dictionary::Value& value )
{
	data_[key] = value;
}

void Dictionary::remove( const Dictionary::Key& key )
{
	DictionaryMap::iterator found = data_.find(key);
	if ( found != data_.end() ) {
		data_.erase( found );
	}
}

Dictionary::Enumerator* Dictionary::getEnumerator()
{
	return dataContainer_.getEnumerator();
}

const Dictionary::Enumerator* Dictionary::getEnumerator() const 
{
	return dataContainer_.getEnumerator();
}
/**
$Id$
*/
