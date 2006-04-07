#ifndef _VCF_VFFOUTPUTSTREAM_H__
#define _VCF_VFFOUTPUTSTREAM_H__
//VFFOutputStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


/**
\class VFFOutputStream VFFOutputStream.h "vcf/ApplicationKit/VFFOutputStream.h"  
The VFFOutputStream class is used to support writing a component (
and it's child components) to a stream. The output is text data,
and is human readable. It's loosely based on Borland's DFM file format
that was used in Delphi 3.0 (I have no idea if Borland still
uses this or not).

The VFF (Visual Form File) output is a hierarchical set of "blocks",
with each block representing an object (component). Each block 
contains a set of properties, and an optional sub-block that lists the
events of the component. Each child component is represented by 
another block nested inside the main block. There is only one "root"
block for a given output stream.

A block starts with "object", and ends with "end". Each object has the
name of the object followed by a colon (':'), the class name of the object
followed by a comma (',') and the class UUID of the object (though this 
may be left blank). The class UUID is in single quotes. For example:
\code
object Foo1 : Foo, '1234556777'
end
\endcode
The example gives an instance of the Foo component (whose UUID is the
string "1234556777") and the instance is named "Foo1".
This example assumes that the Foo class has been registered with the
VCF's ClassRegistry.


Each object block has a list of 0 or more properties that are written out
as name/value pairs. The exact syntax is defined as the name of the property
followed by an equals sign ('='), followed by the value of the property.
For example:
\code
object Foo1 : Foo, '1234556777'
	tag = 12
end
\endcode
Property values that are string types are written out between single 
quotes like so:
\code
object Foo1 : Foo, '1234556777'
	toolTipText = 'Some helpful text'
end
\endcode
Numbers are written out as either integers or floating point with 5 
decimals points of accuracy (i.e. 9.12345). Boolean values are written
either as "true" or "false" as in:
\code
object Foo1 : Foo, '1234556777'
	doubleBuffered = true
end
\endcode

Some properties may themselves be complex object that are also written out
using name/value pairs. For example, a Control component has a Font
object that is it's "font" property. The Font class has several of it's 
own properties. When this occurs these "sub" properties are written
using the name of the property followed by a period ('.') and the 
name of the sub property. For example:
\code
object Foo1 : Foo, '1234556777'
	font.italic = true
	font.color.red = 0.02341
	font.color.green = 0.02341
	font.color.blue = 0.02341
end
\endcode

Some properties may point to another object that is itself a component
(a component property) and part of the "graph" of objects being written 
out. In this case the object is referred to by it's name, preceded by 
the "at" sign ('@'). For example:
\code
object Foo1 : Foo, '1234556777'
	border = @EtchedBorder1
end
\endcode
The border property of Foo1 points to an instance of a border component
named "EtchedBorder1". EtchedBorder1 will be defined somewhere else in 
the file. If not, an error will result in reading the VFF file. If the
component property is not assigned, or NULL, then the value for the
property will be the string "null".
\code
object Foo1 : Foo, '1234556777'
	border = null
end
\endcode


Some properties may actually be made of binary data. In this case the 
data is prefixed with the open curly bracket ('{') and terminated with 
the close curly bracket ('}'). Each byte of data is written out as a 
pair of hexadecimal numbers, effectively doubling the actual storage
space required to save the data. Thus if the data in question is 8
bytes long, it will take 16 characters to represent it. An example of
some binary data of 12 bytes:
\code
object Foo1 : Foo, '1234556777'
	data = {00FFACFE0201104043092FA2}
end
\endcode


Properties that are enumeration values are written out using the name of the
enumeration value as text. For example
\code
object Foo1 : Foo, '1234556777'
	alignment = AlignNone
end
\endcode


A component may have event handlers attached to it's delegates. This 
list of delegates and attached event handlers is a sub block inside the
main object block and is optional. It startes with "delegates" and 
ends with "end". The block may have 0 or more delegates listed. Each 
listed delegate has the name of the delegate, followed by an equals 
sign ('=') and a list of 1 or more event handlers. The list of event 
handlers is preceded by the open square bracket ('['), and completed 
with the closed square bracket (']'). Each event handler is separated 
by a comma (','). A fully qualified event handler is made up of the 
name of the source component followed by the "at" sign ('@') and the 
name of the event handler instance itself. For example:
\code
object Foo1 : Foo, '1234556777'
	delegates
		ComponentDeleted = [
			sdasd.vff@VFFDocument::rootFrameDestroyed]
	end
end
\endcode
This would tell us that Foo1's ComponentDeleted delegate has an event
handler named "VFFDocument::rootFrameDestroyed". This event handler's
source is the component named "sdasd.vff".

@see ClassRegistry
@see REGISTER_CLASSINFO
*/
class APPLICATIONKIT_API VFFOutputStream : public Object, public OutputStream {
public:
	VFFOutputStream( OutputStream* stream ) {
		stream_ = stream;
		tabLevel_ = 0;
		saveUnNamedComponents_ = false;
	}

	virtual ~VFFOutputStream(){};

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom) {
		stream_->seek( offset, offsetFrom );
	}

	virtual unsigned long getSize() {
		return stream_->getSize();
	}

	virtual char* getBuffer() {
		return stream_->getBuffer();
	}

	virtual ulong32 getCurrentSeekPos() {
		return stream_->getCurrentSeekPos();
	}

	virtual unsigned long write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes ) {
		return stream_->write( bytesToWrite, sizeOfBytes );
	}

	void writeComponent( Component* component );

	String getTabString();

	void setSaveUnNamedComponents( const bool& val ) {
		saveUnNamedComponents_ = val;
	}
protected:
	OutputStream* stream_;
	long tabLevel_;
	bool saveUnNamedComponents_;

	String binToHex( Persistable* persistableObject );

	/**
	This virtual method gets called by writeComponent() and is used 
	to prepare the "header" of a component section. You can override
	this and "customize" how this data appears. The default implementation
	simply retrieves the class name and UUID from the component's Class
	instance.
	*/
	virtual void getComponentHeader( Component* component, String& className, String& classID, String& fallBackClassName );

	void writeObject( Object* object, const String& objectPropertyName );

	void writeProperty( Property* property );

	void writeEvents( Component* component );

	String generateEventHandlerString( EventProperty* eventProperty, EventHandler* handler );
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.8  2006/03/18 22:17:42  ddiego
*removed par tag for doxygen comments as its not needed and
*screws up the doc formatting.
*
*Revision 1.2.6.7  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2.6.6  2005/10/09 04:32:44  ddiego
*added some minor fixes in component persistence for vcf builder.
*
*Revision 1.2.6.5  2005/10/04 01:57:03  ddiego
*fixed some miscellaneous issues, especially with model ownership.
*
*Revision 1.2.6.4  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.2.6.3  2005/08/15 03:10:51  ddiego
*minor updates to vff in out streaming.
*
*Revision 1.2.6.2  2005/08/09 04:30:35  ddiego
*minor vff output stream change.
*
*Revision 1.2.6.1  2005/08/08 03:18:40  ddiego
*minor updates
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
*Revision 1.7.4.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.6.4.1  2003/09/12 00:09:34  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.6  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/12 03:11:46  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.20.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/02/28 01:07:09  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.3  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VFFOUTPUTSTREAM_H__


