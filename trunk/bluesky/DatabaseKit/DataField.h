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

	
	class DATABASEKIT_API ValidateFieldEvent : public Event {
	public:
		ValidateFieldEvent( Object* source ) : Event(source,0),buffer(NULL),bufferSize(0){}

		ValidateFieldEvent( const ValidateFieldEvent& rhs ):Event(rhs),buffer(NULL),bufferSize(0){
			buffer = rhs.buffer;
			bufferSize = rhs.bufferSize;
		}

		virtual Object* clone( bool deep = false ) {
			return new ValidateFieldEvent(*this);
		}

		const unsigned char* buffer;
		size_t bufferSize;
	};



	class DATABASEKIT_API DataField : public Object {
	public:

		DELEGATE(Changed);
		DELEGATE(Validate);

		DataField();

		void initField( const FieldDefinition& val );

		void bind( bool bindField );

		virtual VariantData getValue();

		virtual bool getAsBoolean();
		virtual DateTime getAsDateTime();
		virtual String getAsString();
		virtual double getAsFloat();
		virtual int getAsInteger();

		virtual void setValue( const VariantData& val );

		virtual void setAsBoolean( bool val );
		virtual void setAsDateTime( const DateTime& val );
		virtual void setAsString( const String& val );
		virtual void setAsFloat( const double& val );
		virtual void setAsInteger( const int& val );


		virtual void freeBuffers(){}

		DataSet* getDataSet() {
			return dataSet_;
		}

		DataFieldType getDataType() {
			return dataType_;
		}


		bool isStringType() {
			return (dataType_ == dftString) ||  (dataType_ == dftUnicodeString);
		}

		bool isBlobType() {
			return (dataType_ == dftOraBlob) ||  (dataType_ == dftBlob);
		}

		bool isBinaryType() {
			return (isBlobType()) ||  (dataType_ == dftBytes) ||  (dataType_ == dftVarBytes) ||  (dataType_ == dftGraphic) ||
						 (dataType_ == dftParadoxOle) || (dataType_ == dftDBaseOle) || (dataType_ == dftTypedBinary) ||
						  (dataType_ == dftVariant);
		}

		String getDisplayName();

		void setDisplayName( const String& val );

		int getDisplayWidth() {
			return displayWidth_;
		}

		void setDisplayWidth( int val );

		String getName() {
			return name_;
		}

		void setName( const String& val );

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

		bool isValidating() {
			return validating_;
		}

		int getSize() {
			return size_;
		}

		void setSize( int val ) {
			size_  = val;
		}

		size_t getIndex();

		void setIndex( size_t val );

		bool isNull();

		bool getData( unsigned char* buffer, size_t bufferSize );

		void setData( const unsigned char* buffer, size_t bufferSize ) ;

		void change();

		void dataChanged();

		void propertyChanged( bool layoutAffected );

		void validate( const unsigned char* buffer, size_t bufferSize );
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
		bool validating_;
	};



#define STRINGFIELD_CLASSID	"5361c68c-0f88-40a0-847f-c99c5ed916b4"

	class DATABASEKIT_API StringField: public DataField {
	public:
		StringField();

		virtual VariantData getValue();
		virtual void setValue( const VariantData& val );

		virtual bool getAsBoolean();
		virtual DateTime getAsDateTime();
		virtual String getAsString();
		virtual double getAsFloat();
		virtual int getAsInteger();

		virtual void setAsBoolean( bool val );
		virtual void setAsDateTime( const DateTime& val );
		virtual void setAsString( const String& val );
		virtual void setAsFloat( const double& val );
		virtual void setAsInteger( const int& val );
	protected:


	};




#define BOOLEANFIELD_CLASSID	"79b2b987-1fac-4e2d-b4c5-1295ccc478ce"

	class DATABASEKIT_API BooleanField: public DataField {
	public:
		BooleanField();

		virtual VariantData getValue();
		virtual void setValue( const VariantData& val );

		virtual bool getAsBoolean();		
		virtual String getAsString();
		virtual int getAsInteger();

		virtual void setAsBoolean( bool val );
		virtual void setAsString( const String& val );		
		virtual void setAsInteger( const int& val );
	protected:		

	};



#define DATETIMEFIELD_CLASSID	"35fa49d4-3cfc-402e-9ec9-72d93863171f"

	class DATABASEKIT_API DateTimeField: public DataField {
	public:
		DateTimeField();

		virtual VariantData getValue();
		virtual void setValue( const VariantData& val );

		virtual DateTime getAsDateTime();
		virtual String getAsString();		
		virtual int getAsInteger();

		virtual void setAsDateTime( const DateTime& val );
		virtual void setAsString( const String& val );
		virtual void setAsInteger( const int& val );
	protected:
		

	};





#define DOUBLEFIELD_CLASSID	"5a4e2ca6-dbc8-47f7-a5ed-536cc1eb6b56"

	class DATABASEKIT_API DoubleField: public DataField {
	public:
		DoubleField();

		virtual VariantData getValue();
		virtual void setValue( const VariantData& val );

		virtual String getAsString();
		virtual double getAsFloat();
		virtual int getAsInteger();

		
		
		virtual void setAsString( const String& val );
		virtual void setAsFloat( const double& val );
		virtual void setAsInteger( const int& val );
	protected:
		

	};




#define INTEGERFIELD_CLASSID	"9d9e4968-ff20-4825-8301-791c520fa0ef"

	class DATABASEKIT_API IntegerField: public DataField {
	public:
		IntegerField();

		virtual VariantData getValue();
		virtual void setValue( const VariantData& val );

		virtual bool getAsBoolean();
		virtual DateTime getAsDateTime();
		virtual String getAsString();
		virtual double getAsFloat();
		virtual int getAsInteger();

		virtual void setAsBoolean( bool val );
		virtual void setAsDateTime( const DateTime& val );
		virtual void setAsString( const String& val );
		virtual void setAsFloat( const double& val );
		virtual void setAsInteger( const int& val );
	protected:
		

	};

};




#endif //_VCF_DATAFIELD_H__


