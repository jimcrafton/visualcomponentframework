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
\par
This represents the printing context, used for drawing when printing is being invoked.
You can see this in action in the Printing and TextEdit examples in vcf/examples/Printing
and vcf/examples/TextEdit respectively.
\par
You cannot create a PrintContext directly. The only way to get access to one is to 
call the PrintSession::beginPrintingDocument() method.

@see PrintSession
*/
namespace VCF{
	
	class GRAPHICSKIT_API PrintContext : public VCF::GraphicsContext {	
	public:
		PrintContext( ulong32 contextID ):GraphicsContext(contextID) {};


	};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2004/12/02 04:54:02  ddiego
*added some more documentation to the graphics kit classes.
*
*Revision 1.3  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/25 04:43:33  ddiego
*migrated the core printing changes into the graphics kit
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.1  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.7  2003/05/17 20:37:10  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.10.1  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.5.12.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PRINTCONTEXT_H__


