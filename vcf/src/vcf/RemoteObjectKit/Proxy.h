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

	virtual VCF::VariantData* invoke( const VCF::String& methodName,
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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.7.8.1  2004/04/26 21:58:46  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/12 03:11:48  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.14.1  2003/01/08 00:19:48  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PROXY_H__


