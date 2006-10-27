#include "DatabaseKit.h"


using namespace VCF;

FieldDefinitions::FieldDefinitions():
	dataSet_(NULL),
	updated_(false)
{

}


void FieldDefinitions::clear()
{
	fields_.clear();
}

void FieldDefinitions::add( const String& name, FieldType dataType, size_t size, bool required )
{
	updated_ = false;
}

FieldDefinition* FieldDefinitions::find( const String& name )
{

	FieldDefinition* result = NULL;


	int i = indexOf(name);

	if ( i >= 0 ) {
		result = &fields_[i];
	}	

	return result;
}

int FieldDefinitions::indexOf( const String& name )
{	
	int result = -1;

	std::vector<FieldDefinition>::iterator it = fields_.begin();
	while ( it != fields_.end() ) {
		if ( name == (*it).name ) {
			result = it - fields_.begin();

			break;
		}
		++it;
	}

	return result;
}

void FieldDefinitions::update()
{
	if ( NULL != dataSet_ ) {
		dataSet_->updateFieldDefs();
	}
}