//DataBaseKitRTTI.inl

/*
Copyright 2000-2006 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
this declares all the RTTI for the DataBaseKit's classes.
This was created to improved compile times
*/



namespace VCF {
/*
static String DataFieldTypeNames[] = { "dftUnknown",
										"dftString", 
										"dftSmallint", 
										"dftInteger", 
										"dftWord", 
										"dftBoolean", 
										"dftFloat", 
										"dftCurrency", 
										"dftBCD", 
										"dftDate", 
										"dftTime", 
										"dftDateTime", 
										"dftBytes", 
										"dftVarBytes", 
										"dftAutoInc", 
										"dftBlob", 
										"dftMemo", 
										"dftGraphic", 
										"dftFmtMemo", 
										"dftParadoxOle", 
										"dftDBaseOle", 
										"dftTypedBinary", 
										"dftCursor", 
										"dftFixedChar", 
										"dftUnicodeString", 
										"dftLargeint", 		
										"dftADT", 
										"dftArray", 
										"dftReference", 
										"dftDataSet", 
										"dftOraBlob", 
										"dftOraClob", 
										"dftVariant", 
										"dftInterface", 
										"dftIDispatch", 
										"dftGuid" };
*/



_class_abstract_rtti_(DataField, "VCF::Component", DATAFIELD_CLASSID )
_class_rtti_end_



_class_rtti_(StringField, "VCF::DataField", STRINGFIELD_CLASSID )
_class_rtti_end_


_class_rtti_(BooleanField, "VCF::DataField", BOOLEANFIELD_CLASSID )
_class_rtti_end_


_class_rtti_(DateTimeField, "VCF::DataField", DATETIMEFIELD_CLASSID )
_class_rtti_end_


_class_rtti_(DoubleField, "VCF::DataField", DOUBLEFIELD_CLASSID )
_class_rtti_end_


_class_rtti_(IntegerField, "VCF::DataField", INTEGERFIELD_CLASSID )
_class_rtti_end_


};