//OSXResourceBundle.h

#ifndef _VCF_OSXRESOURCEBUNDLE_H__
#define _VCF_OSXRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF {
	class OSXResourceBundle : public Object, public ResourceBundlePeer {
	public:
	
		OSXResourceBundle();
		
		virtual ~OSXResourceBundle();
		
		/**
		*returns a resource string given a resource name
		*/
		virtual String getString( const String& resourceName );

		/**
		*returns the text that represents an VFF file (where VFF stands
		*for "Visual Form File" ). This text is standard XML and contains
		*the component hierarchy and properties for creating a frame.
		*/
		virtual String getVFF( const String& resourceName );

		/**
		*returns a Resource object given the resource's name.
		*this function walks through all the app's resources, by type
		*and then by name. The first match is the resource returned.
		*/
		virtual Resource* getResource( const String& resourceName );

		virtual ProgramInfo* getProgramInfo();
		
		static ProgramInfo* getProgramInfo( const String& fileName );		
	protected:
		static ProgramInfo* getProgramInfo( CFBundleRef bundle );
	
		virtual CFBundleRef getBundle();
	};
};



#endif //_VCF_OSXRESOURCEBUNDLE_H__

/**
CVS Log info
$Log$
Revision 1.2  2004/12/01 04:31:41  ddiego
merged over devmain-0-6-6 code. Marcello did a kick ass job
of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
that he found. Many, many thanks for this Marcello.

Revision 1.1.2.1  2004/10/10 21:18:22  ddiego
added missing osx files

*/


