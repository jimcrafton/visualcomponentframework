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

	enum DataFieldType {
		dftUnknown = 0,
		dftString, 
		dftSmallint, 
		dftInteger, 
		dftWord, 
		dftBoolean, 
		dftFloat, 
		dftCurrency, 
		dftBCD, 
		dftDate, 
		dftTime, 
		dftDateTime, 
		dftBytes, 
		dftVarBytes, 
		dftAutoInc, 
		dftBlob, 
		dftMemo, 
		dftGraphic, 
		dftFmtMemo, 
		dftParadoxOle, 
		dftDBaseOle, 
		dftTypedBinary, 
		dftCursor, 
		dftFixedChar, 
		dftUnicodeString, 
		dftLargeint, 		
		dftADT, 
		dftArray, 
		dftReference, 
		dftDataSet, 
		dftOraBlob, 
		dftOraClob, 
		dftVariant, 
		dftInterface, 
		dftIDispatch, 
		dftGuid
	};

	class FieldDefinitions;
	class DataField;


	class DATABASEKIT_API FieldDefinition {
	public:
		int fieldNumber;
		DataFieldType dataType;
		bool internalCalcField;
		String name;
		int precision;
		bool required;
		size_t size;
		FieldDefinitions* owner;
		

		FieldDefinition():fieldNumber(0), dataType(dftUnknown),internalCalcField(false),precision(0),required(false), size(0),owner(NULL) {

		}

		
		DataField* createField(); 

		Class* getFieldClass();


		friend class FieldDefinitions;
	protected:
	};


	class DataSet;
	

	class DATABASEKIT_API FieldDefinitions {
	public:
		FieldDefinitions();

		void clear();

		size_t size() const {
			return fields_.size();
		}

		void add( const String& name, DataFieldType dataType, size_t size, bool required );

		void add( FieldDefinition& val );

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