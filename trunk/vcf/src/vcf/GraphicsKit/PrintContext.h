#ifndef _VCF_PRINTCONTEXT_H__
#define _VCF_PRINTCONTEXT_H__
//PrintContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif





/**
\class PrintContext PrintContext.h "vcf/GraphicsKit/PrintContext.h"
This represents the printing context, used for drawing when printing is being invoked.
You can see this in action in the Printing and TextEdit examples in vcf/examples/Printing
and vcf/examples/TextEdit respectively.

You cannot create a PrintContext directly. The only way to get access to one is to 
call the PrintSession::beginPrintingDocument() method.

@see PrintSession
*/
namespace VCF{
	
	class GRAPHICSKIT_API PrintContext : public VCF::GraphicsContext {	
	public:
		PrintContext( OSHandleID contextID ):GraphicsContext(contextID) {};


	};

};


#endif // _VCF_PRINTCONTEXT_H__

/**
$Id$
*/
