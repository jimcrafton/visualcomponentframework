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
class Parser;
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

	VFFInputStream( VCF::InputStream* stream );

	virtual ~VFFInputStream();

	virtual void seek(const uint64& offset, const VCF::SeekType& offsetFrom) {
		stream_->seek( offset, offsetFrom );
	}

	virtual uint64 getSize() {
		return stream_->getSize();
	}

	virtual char* getBuffer() {
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

	/**
	Returns a value for a specific constant name.
	*/
	static bool getComponentConstant( const String& name, String& value );


	/**
	*retreives the outer most class/UUID that contains all other obejcts
	*in this VFF stream
	*/
	void getOuterClassNameAndUUID( VCF::String& className, VCF::String& UUID, VCF::String& fallbackClassName );

	/**
	*reads in a new component, that is the caller passes in a pointer to
	*a pointer of a Component, and the method creates a new instance for the caller.
	*@param Component**  the derefenced component ptr should be NULL when invoking this
	*method, usually this is a top level component like a Frame
	*/
	VCF::Component* readNewComponent();

	/**
	*reads in a Component from the stream, and assigns it's value to the
	*component instance passed in
	*@param Component* must NOT be null. Represents the already existing component
	*that will be updated as a result of reading the contents of the stream.
	*/
	void readComponentInstance( VCF::Component* component );

	/**
	Assumes we have a new, empty, top level component (typically a FormRootWindow
	instance), but NO child components yet. Will create child components as neccessary
	*/
	void readNewComponentInstance( VCF::Component* component );


	void setAllComponentsInDesignMode( const bool& val ) {
		setDesignMode_ = val;
	}

	virtual bool isEOS()
	{
		// stub impl.
		return false;
	}

protected:

	class DeferredPropertySetter {
	public:
		DeferredPropertySetter( const VCF::String& propertyVal, const VCF::String& propertyName, VCF::Object* source ) {
			propertyVal_ = propertyVal;
			propertyName_ = propertyName;
			source_ = source;
		}

		virtual ~DeferredPropertySetter(){};
		VCF::String propertyVal_;
		VCF::String propertyName_;
		VCF::Object* source_;
	};

	VCF::InputStream* stream_;
	VCF::Parser* parser_;
	void hexToBin( const VCF::String& hexString, VCF::Persistable* persistableObject );

	void processAsignmentTokens( const VCF::VCFChar& token, const VCF::String& currentSymbol, VCF::Class* clazz );

	void processDelegateAsignment( const VCF::VCFChar& token, const VCF::String& currentSymbol, VCF::Class* clazz );
	

	void readDelegates( VCF::Component* component, VCF::Class* clazz );

	VCF::Component* readObject( VCF::Component* componentInstance, int flags );
		//bool createComponent, bool createChildren );

	void assignDeferredProperties( VCF::Component* component );

	Object* createClassInstance( const String& className, const String& classID, const String& fallbackClassName );

	std::vector<DeferredPropertySetter*> deferredProperties_;
	VCF::Component* topLevelComponent_;
	bool atTopLevel_;
	int32 componentInputLevel_;
	bool topLevelControlVisibility_;
	bool setDesignMode_;
};


};


#endif // _VCF_VFFINPUTSTREAM_H__

/**
$Id$
*/
