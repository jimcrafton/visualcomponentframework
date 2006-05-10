//LinuxResourceBundle.h

#ifndef _VCF_LINUXRESOURCEBUNDLE_H__
#define _VCF_LINUXRESOURCEBUNDLE_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/ResourceBundlePeer.h"

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
$Id$
*/
