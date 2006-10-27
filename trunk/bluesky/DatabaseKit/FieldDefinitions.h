#ifndef _VCF_FIELDDEFINITIONS_H__
#define _VCF_FIELDDEFINITIONS_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

	enum FieldType {
		ftNone = 0
	};

	class FieldDefinitions;

	class FieldDefinition {
	public:
		int fieldNumber;
		FieldType dataType;
		bool internalCalcField;
		String name;
		int precision;
		bool required;
		size_t size;

		FieldDefinition():fieldNumber(0), dataType(ftNone),internalCalcField(false),precision(0),required(false), size(0) {

		}
	};


	class DataSet;

	class FieldDefinitions {
	public:
		FieldDefinitions();

		void clear();

		size_t size() const {
			fields_.size();
		}

		void add( const String& name, FieldType dataType, size_t size, bool required );

		FieldDefinition* find( const String& name );

		int indexOf( const String& name );

		void update();


		std::vector<FieldDefinition>& fields() {
			return fields_;
		}

		const std::vector<FieldDefinition>& fields() const{
			return fields_;
		}

		DataSet* getDataSet() const {
			return dataSet_;
		}

		void setDataSet( DataSet* val ) {
			dataSet_ = val;
		}

		bool isUpdated() const {
			return updated_;
		}

		void setUpdated( bool val ) {
			updated_ = val;
		}
	protected:
		std::vector<FieldDefinition> fields_;
		DataSet* dataSet_;
		bool updated_;
	};


};

#endif //_VCF_FIELDDEFINITIONS_H__