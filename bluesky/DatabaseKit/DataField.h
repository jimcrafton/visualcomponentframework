#ifndef _VCF_DATAFIELD_H__
#define _VCF_DATAFIELD_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

#define DATAFIELD_CLASSID	"48e34264-750f-4fc9-a28f-4e91c2690809"

	enum FieldKindType {
		fkUnknown = 0,
		fkData
	};

	class DATABASEKIT_API DataField : public Object {
	public:

		DataField();

		void initField( const FieldDefinition& val );

		void bind( bool bindField );

		virtual VariantData getCurrentValue();

		virtual bool getAsBoolean();
		virtual DateTime getAsDateTime();
		virtual String getAsString();
		virtual double getAsFloat();
		virtual int getAsInteger();

		DataSet* getDataSet() {
			return dataSet_;
		}

		DataFieldType getDataType() {
			return dataType_;
		}

		String getDisplayName() {
			return displayName_;
		}

		int getDisplayWidth() {
			return displayWidth_;
		}

		String getName() {
			return name_;
		}

		int getFieldNumber() {
			return fieldNumber_;
		}

		FieldKindType getKind() {
			return kind_;
		}

		bool isVisible() {
			return visible_;
		}

		bool isReadOnly() {
			return readOnly_;
		}

		bool isRequired() {
			return required_;
		}

		int getSize() {
			return size_;
		}

		void setSize( int val ) {
			size_  = val;
		}

		bool getData( unsigned char* buffer, size_t bufferSize );
	protected:
		DataSet* dataSet_;
		DataFieldType dataType_;
		String displayName_;
		int displayWidth_;
		String name_;
		int	fieldNumber_;
		FieldKindType kind_;
		bool visible_;
		bool readOnly_;
		bool required_;
		int size_;
	};



#define STRINGFIELD_CLASSID	"5361c68c-0f88-40a0-847f-c99c5ed916b4"

	class DATABASEKIT_API StringField: public DataField {
	public:
		StringField();

		virtual VariantData getCurrentValue();

		virtual bool getAsBoolean();
		virtual DateTime getAsDateTime();
		virtual String getAsString();
		virtual double getAsFloat();
		virtual int getAsInteger();
	protected:


	};
};

#endif //_VCF_DATAFIELD_H__


