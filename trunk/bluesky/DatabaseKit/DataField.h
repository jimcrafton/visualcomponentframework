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


		void bind( bool bindField );

		virtual VariantData getCurrentValue();

		virtual bool getAsBoolean();
		virtual DateTime getAsDateTime();
		virtual String getAsString();
		virtual double getAsFloat();
		virtual int getAsInteger();



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


};

#endif //_VCF_DATAFIELD_H__


