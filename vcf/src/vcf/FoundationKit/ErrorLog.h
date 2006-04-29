#ifndef _VCF_ERRORLOG_H__
#define _VCF_ERRORLOG_H__
//ErrorLog.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
\class ErrorLog ErrorLog.h "vcf/FoundationKit/ErrorLog.h"
*An ErrorLog represents a place to output status
*during the life of a running application. It takes
*care of managing the existence of a an error log on
*the system, and updating it with data.
*/
class FOUNDATIONKIT_API ErrorLog : public Object {
public:
	/**
	*@param String the name of the log file
	*to create. Must be a fully qualified path
	*/
	ErrorLog( const String& ouputFilename = "" );

	virtual ~ErrorLog();

	/**
	*send the string data contained in the text
	*parameter to the log. This is currently a
	*a blocking call, and does not support asynchronous
	*file I/O.
	*@param String the status data to send to the log file
	*/
	virtual void toLog( const String& text );
protected:

private:
	String outputFileName_;
	OutputStream* errStream_;
};


}; //end of namespace VCF


#endif // _VCF_ERRORLOG_H__

/**
$Id$
*/
