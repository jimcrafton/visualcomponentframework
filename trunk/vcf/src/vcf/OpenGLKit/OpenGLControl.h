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
	OpenGLContext* glContext_;
};

}; //end of namespace VCF


#endif // _VCF_OPENGLCONTROL_H__

/**
$Id$
*/
