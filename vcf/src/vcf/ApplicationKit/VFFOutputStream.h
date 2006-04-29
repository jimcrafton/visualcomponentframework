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


#endif // _VCF_VFFOUTPUTSTREAM_H__

/**
$Id$
*/
