#ifndef _VCF_DISTRIBUTEDEXCEPTION_H__
#define _VCF_DISTRIBUTEDEXCEPTION_H__
//DistributedException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFRemote  {

/**
*Class DistributedException documentation
*/
class REMOTEKIT_API DistributedException : public VCF::BasicException {
public:
	DistributedException();

	virtual ~DistributedException() throw();

protected:

private:
};


}; //end of namespace VCFRemote


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/04 15:21:20  thrysoee
*Fix gcc error "looser throw specifier"
*This error occurs when a method in a derived class has a different throw specifier.
*http://www.agapow.net/programming/looser_throw_specifier.html
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.4.24.1  2004/04/26 21:58:46  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.3  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DISTRIBUTEDEXCEPTION_H__


