#include "DatabaseKit.h"


using namespace VCF;


DataField* FieldDefinition::createField()
{
	DataField* result = NULL;

	Class* fieldClass = getFieldClass();

	Object* obj = fieldClass->createInstance();

	if ( NULL != obj ) {
		throw DatabaseError("Unable to create field instance.");
	}

	result = dynamic_cast<DataField*>(obj);

	if ( NULL == result ) {
		obj->free();
		throw DatabaseError("Invalid type of object type created for field.");
	}
	




	return result;
}

Class* FieldDefinition::getFieldClass()
{
	return fieldClass_;
}


FieldDefinitions::FieldDefinitions():
	dataSet_(NULL),
	updated_(false)
{

}


void FieldDefinitions::clear()
{
	fields_.clear();
}

void FieldDefinitions::add( const String& name, DataFieldType dataType, size_t size, bool required )
{
	if ( name.empty() ) {
		throw DatabaseError("Field Name missing/empty.");
	}

	if ( this->indexOf(name) >= 0 ) { //oops we already exist!
		throw DatabaseError("A field definition with this name already exists.");
	}


	FieldDefinition fieldDef;

	fieldDef.owner = this;
	fieldDef.dataType = dataType;
	fieldDef.name = name;
	fieldDef.size = size;
	fieldDef.required = required;

	if ( NULL != dataSet_ ) {
		fieldDef.fieldClass_ = dataSet_->getFieldClass( dataType );
	}


	fields_.push_back( fieldDef );

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
	if ( name.empty() ) {
		throw DatabaseError("Field Name missing/empty.");
	}

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