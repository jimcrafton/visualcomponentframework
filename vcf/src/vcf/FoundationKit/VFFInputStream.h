#ifndef _VCF_VFFINPUTSTREAM_H__
#define _VCF_VFFINPUTSTREAM_H__
//VFFInputStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class InputStream;
class VFFParser;
class UnitTransformer;



/**
\class VFFInputStream VFFInputStream.h "vcf/ApplicationKit/VFFInputStream.h"  
*/
class FOUNDATIONKIT_API VFFInputStream : public Object, public InputStream {
public:
	public:
	enum UsageFlags {
		ufCreateComponent				=	0x0001,
		ufCreateChildren				=	0x0002,
		ufCreateChildrenIfNoInstance	=	0x0004,
		ufFindSubComponent				=	0x0008
	};

	VFFInputStream( InputStream* stream );

	VFFInputStream( const String& vffString );

	virtual ~VFFInputStream();

	virtual void seek(const uint64& offset, const VCF::SeekType& offsetFrom) {
		stream_->seek( offset, offsetFrom );
	}

	virtual uint64 getSize() {
		return stream_->getSize();
	}

	virtual uchar* getBuffer() {
		return stream_->getBuffer();
	}

	virtual VCF::uint64 getCurrentSeekPos() {
		return stream_->getCurrentSeekPos();
	}

	virtual uint64 read( unsigned char* bytesToRead, uint64 sizeOfBytes ) {
		return stream_->read( bytesToRead, sizeOfBytes );
	}



	typedef String (*ComponentConstantFunc)(const String&);

	/**
	Register a constant value to be used. This can only hold basic types
	like an int, double, string, or bool. The symbolic name of the 
	@param String the name of the constant.
	@param String the value of the constant.
	*/
	static void registerComponentConstant( const String& name, const String& data );
	
	/**
	Register a constant value to be used. This can only hold basic types
	like an int, double, string, or bool. The symbolic name of the 
	@param String the name of the constant.
	@param ComponentConstantFunc a function pointer that is used to retrieve the 
	value of the constant name.
	*/
	static void registerComponentConstant( const String& name, ComponentConstantFunc funcPtr );

	static void internal_clearComponentConstants();

	/**
	Returns a value for a specific constant name.
	*/
	static bool getComponentConstant( const String& name, String& value );


	/**
	*retreives the outer most class/UUID that contains all other obejcts
	*in this VFF stream
	*/
	void getOuterClassNameAndUUID( String& className, String& UUID, String& fallbackClassName );

	/**
	*reads in a new component. The method creates a new instance for the caller.
	*@return Component*  usually this is a top level component like a Frame
	*/
	Component* readNewComponent();

	/**
	*reads in a Component from the stream, and assigns it's value to the
	*component instance passed in
	*@param Component* must NOT be null. Represents the already existing component
	*that will be updated as a result of reading the contents of the stream.
	*/
	void readComponentInstance( Component* component );

	/**
	Assumes we have a new, empty, top level component (typically a FormRootWindow
	instance), but NO child components yet. Will create child components as neccessary
	*/
	void readNewComponentInstance( Component* component );


	void setAllComponentsInDesignMode( const bool& val ) {
		setDesignMode_ = val;
	}

	virtual bool isEOS()
	{
		// stub impl.
		return false;
	}

	static void setRootComponent( Component* component ) {
		VFFInputStream::rootComponent_ = component;
	}
protected:

	class DeferredPropertySetter {
	public:
		DeferredPropertySetter( const String& pv, const String& pn, VCF::Object* src ) {
			propertyVal = pv;
			propertyName = pn;
			source = src;
			keyValid = false;
		}

		DeferredPropertySetter( const String& pv, const String& pn, VCF::Object* src, const VariantData& k ) {
			propertyVal = pv;
			propertyName = pn;
			source = src;
			key = k;
			keyValid = true;
		}

		bool keyValid;
		VariantData key;
		String propertyVal;
		String propertyName;
		VCF::Object* source;
	};

	class DeferredDelegateSetter {
	public:
		VCF::Object* source;
		String delegateName;		
		std::vector<String> callbackIds;
	};

	

	void hexToBin( const String& hexString, VCF::Persistable* persistableObject );

	void processAsignmentTokens( const VCFChar& token, const String& currentSymbol, VCF::Class* clazz );

	void processAsignmentTokens( const VCFChar& token, const String& currentSymbol, const VariantData& key, Class* clazz );

	void processDelegateAsignment( const VCFChar& token, const String& currentSymbol, VCF::Class* clazz );
	

	void readDelegates( Component* component, VCF::Class* clazz );

	void readDelegate( Component* component, VCF::Class* clazz );

	Component* readObject( Component* componentInstance, int flags );
		//bool createComponent, bool createChildren );

	void assignDeferredProperties( Component* component );

	Object* createClassInstance( const String& className, const String& classID, const String& fallbackClassName );

	Component* createNewComponent( Component* componentInstance, int flags );

	String transform( const String& originalValue );

	std::vector<DeferredPropertySetter*> deferredProperties_;
	std::vector<DeferredDelegateSetter*> deferredDelegates_;
	
	Component* topLevelComponent_;
	bool atTopLevel_;
	int32 componentInputLevel_;
	bool topLevelControlVisibility_;
	bool setDesignMode_;
	InputStream* stream_;
	VFFParser* parser_;
	bool deleteStream_;
	
	static Component* rootComponent_;

	void componentLoaded( Component* component );
};


};


#endif // _VCF_VFFINPUTSTREAM_H__

/**
$Id$
*/
