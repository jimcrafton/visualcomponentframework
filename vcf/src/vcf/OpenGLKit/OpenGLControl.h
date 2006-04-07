#ifndef _VCF_OPENGLCONTROL_H__
#define _VCF_OPENGLCONTROL_H__
//OpenGLControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define OPENGLCONTROL_CLASSID	"5389AAA2-8295-11d4-8F37-00207811CFAB"

/**
\par
This is a custom control that can be used for OpenGL drawing.
It takes care of setting up an OpenGL context and you can 
customize the paint function to do you own OpenGL drawing there.
\par
All the low level setup code to associate a platform window
with the OpenGL system is taken care of for you. 
*/
class OPENGLKIT_API OpenGLControl : public VCF::CustomControl{
public:

	OpenGLControl();
	virtual ~OpenGLControl();


	/**
	Override this function to add you own custom GL 
	graphics calls here. Make sure to call the super
	class though or things won't work correctly!
	\code
	void MyGLControl::paint(GraphicsContext * context)
	{
		OpenGLControl::paint( context );
		//rest of your GL code

		swapBuffers();//need to call this when you're done
	}
	\endcode
	\note
	When you are done with your OPenGL code, you need to call 
	swapBuffers() to push all your changes to the right GL buffer.
	Under the hood it will call the platform's SwapBuffers
	API function, or whatever it's called on your windowing
	system. On Win32 it's called "SwapBuffers". On OS X I
	believe this would end up calling "aglSwapBuffers".
	*/
	virtual void paint(GraphicsContext * context);

	/**
	\par
	This gets the controls OpenGL context and calls
	the swapBuffers() function on it. This in turn
	calls the native windowing systems GL function for 
	swapping the front and back buffers. On Win32 this
	resolves to a call to 
	<a href="http://windowssdk.msdn.microsoft.com/library/default.asp?url=/library/en-us/OpenGL/ntopnglr_1ss3.asp">
	SwapBuffers()</a>. On Mac OS X, this should resolve to
	<a href="http://edr.euro.apple.com/documentation/GraphicsImaging/Reference/AGL_OpenGL/Reference/reference.html#//apple_ref/doc/uid/TP30000414-F15030">
	aglSwapBuffers</a>.
	*/
	virtual void swapBuffers();

	virtual void afterCreate( ComponentEvent* event );

protected:

};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:47  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/12 22:01:46  ddiego
*doc updates.
*
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/21 20:18:39  pallindo
*Removed some unused files, and cleaned up the interface to the OpenGLControl
*
*Revision 1.1.2.3  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 21:13:58  ddiego
*made a few changes to the new OpenGLKit files, adjusting where the
*CVS log was put, and changed a few cases for the export-import definition
*was used. Also added the two projects to the vcfAllProject workspace
*and added the script generated VC7 and VC71 projects as well.
*
*Revision 1.1.2.1  2004/04/29 15:38:12  pallindo
*Initial attempt at an OpenGLKit
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.6.3  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.5.6.2  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.5.6.1  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.5  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.20.1  2003/01/08 00:19:43  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_OPENGLCONTROL_H__


