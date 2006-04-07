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
class APPLICATIONKIT_API VFFInputStream : public Object, public InputStream {
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

	virtual void seek(const unsigned long& offset, const VCF::SeekType& offsetFrom) {
		stream_->seek( offset, offsetFrom );
	}

	virtual unsigned long getSize() {
		return stream_->getSize();
	}

	virtual char* getBuffer() {
		return stream_->getBuffer();
	}

	virtual VCF::ulong32 getCurrentSeekPos() {
		return stream_->getCurrentSeekPos();
	}

	virtual unsigned long read( unsigned char* bytesToRead, unsigned long sizeOfBytes ) {
		return stream_->read( bytesToRead, sizeOfBytes );
	}

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
	long componentInputLevel_;
	bool topLevelControlVisibility_;
	bool setDesignMode_;
};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.6  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2.6.5  2005/10/09 04:32:44  ddiego
*added some minor fixes in component persistence for vcf builder.
*
*Revision 1.2.6.4  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2.6.3  2005/09/18 22:54:47  ddiego
*fixed some minor bugs in vffinput stream and parser class.
*
*Revision 1.2.6.2  2005/09/16 01:12:01  ddiego
*fixed bug in component loaded function.
*
*Revision 1.2.6.1  2005/08/15 03:10:51  ddiego
*minor updates to vff in out streaming.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.12.2.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.11.2.1  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.11  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.10.4.1  2003/09/12 00:09:34  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.10  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/12 03:11:46  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.8.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.12.1  2002/09/05 04:31:46  ddiego
*fixed hte bug in hte VCFInputStream, nested class instances will now
*read in correctly.
*Also added code to properly update the name manager whenever a new form is
*loaded up to prevent name collision within ina a form class. Fixed
*a bit of selection code in the TreeControl class as well.
*
*Revision 1.7  2002/02/28 01:07:09  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VFFINPUTSTREAM_H__


