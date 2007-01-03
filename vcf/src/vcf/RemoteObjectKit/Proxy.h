#ifndef _VCF_PROXY_H__
#define _VCF_PROXY_H__
//Proxy.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFRemote {

class VCF::Object;

class REMOTEKIT_API Proxy : public VCF::Persistable {
public:
	Proxy( VCF::Object* localObjectInstance = NULL );

	virtual ~Proxy();

	virtual VCF::VariantData invoke( const VCF::String& methodName,
		                              const VCF::uint32& argCount,
									  VCF::VariantData** arguments );
    virtual bool isRemote() {
		return isRemote_;
	}

    virtual VCF::String getClassName();

    virtual VCF::String getClassID();

	InstanceID* getInstanceID() {
		return &instanceID_;
	}

	virtual void saveToStream( VCF::OutputStream * stream );

	virtual void loadFromStream( VCF::InputStream * stream );

    static Proxy* createInstance( const VCF::String& className );

	static Proxy* createInstanceByClassID( const VCF::String& classID );

protected:
	void marshallArguments( const VCF::uint32& argCount,
							VCF::VariantData** arguments,
							VCF::OutputStream* marshallingStream );
private:
	/**
	*this represents a pointer to the local Object that the
	*Proxy might represent. It is only non-NULL if the Object
	*instance requested from Proxy::createInstance() or createInstanceByClassID()
	*exists on the Proxy process's ClassRegistry. Otherwise the Proxy represents
	*an Object instance from either another process on the same machine, or
	*an Object instance from some remote machine.
	*/
	VCF::Object* localObjectInstance_;

	/**
	*indicates whether the Proxy represents a local in process Object, or
	*an Object from outside the process.
	*/
	bool isRemote_;

	VCF::String className_;

	VCF::String classID_;

    InstanceID instanceID_;
};

}; //end of namespace VCFRemote


#endif // _VCF_PROXY_H__

/**
$Id$
*/
