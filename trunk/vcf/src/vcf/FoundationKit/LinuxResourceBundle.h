//LinuxResourceBundle.h

#ifndef _VCF_LINUXRESOURCEBUNDLE_H__
#define _VCF_LINUXRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF {
	class LinuxResourceBundle : public Object, public ResourceBundlePeer {
	public:
	
		LinuxResourceBundle();
		
		virtual ~LinuxResourceBundle();
		
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
		
		virtual OSHandleID getHandleID() {
			return resourceHandle_;
		}
	protected:
		OSHandleID resourceHandle_;
		
	};
};



#endif //_VCF_LINUXRESOURCEBUNDLE_H__

/**
CVS Log info
$Log$
Revision 1.2  2005/07/09 23:15:03  ddiego
merging in changes from devmain-0-6-7 branch.

Revision 1.1.2.1  2005/04/17 16:11:32  ddiego
brought the foundation, agg, and graphics kits uptodate on linux


*/


