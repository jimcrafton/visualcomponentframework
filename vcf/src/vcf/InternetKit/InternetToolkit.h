
#ifndef _VCF_INTERNETTOOLKIT_H__
#define _VCF_INTERNETTOOLKIT_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {
	class URL;

	/**
	\class InternetToolkit InternetToolkit.h "vcf/InternetKit/InternetToolkit.h"
	The InternetToolkit is used to get data from the URL.
	These methods then resolve to platform specific calls.
	*/
	class INTERNETKIT_API InternetToolkit {
	public:
		/**
		Using the URL, the InternetToolkit gets the data 
		and writes to the output stream. This is a blocking 
		call.
		*/
		static void getDataFromURL( URL* url, OutputStream* stream ) {
			InternetToolkit::inetKitInstance->internal_getDataFromURL( url, stream );
		}

		static void create();

		static void terminate();
	protected:
		virtual ~InternetToolkit(){}
		InternetToolkit(){};

		static InternetToolkit* inetKitInstance;

		/**
		This is an abstract method that get re-implemented in a 
		concrete class derived from InternetToolkit that is 
		specific to the platform the VCF is running on.
		*/
		virtual void internal_getDataFromURL( URL* url, OutputStream* stream ) = 0; 

	private:		
		InternetToolkit(const InternetToolkit&);
		InternetToolkit& operator=(const InternetToolkit&);

	};
};

#endif //_VCF_INTERNETTOOLKIT_H__


