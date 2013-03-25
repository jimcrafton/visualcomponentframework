#ifndef _VCF_UNITTRANSFORMER_H__
#define _VCF_UNITTRANSFORMER_H__
//UnitTransformer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


	class FOUNDATIONKIT_API UnitTransformer {
	public:
		UnitTransformer(){}
		virtual ~UnitTransformer(){}

		virtual String transform( const String& originalValue, Object* context ) = 0;

		static UnitTransformer* getCurrentTransformer();
		static void setCurrentTransformer(UnitTransformer* val);

		static String xfrmString( const String& value, Object* context );
	private:
		static UnitTransformer* currentTransformer_;
	};


};


#endif //_VCF_UNITTRANSFORMER_H__