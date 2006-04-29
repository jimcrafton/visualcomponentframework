#ifndef _VCF_WIN32OBJECT_H__
#define _VCF_WIN32OBJECT_H__
//Win32Object.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

#define SIMPLE_VIEW				WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED
#define BORDERED_VIEW			WS_CHILD | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN
#define SIMPLE_DIALOG			WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN
#define FRAME_WINDOW			WS_OVERLAPPEDWINDOW

class Control;

class APPLICATIONKIT_API Win32Object : public ObjectWithEvents
{
public:

	typedef std::pair<DWORD,DWORD> CreateParams;

	Win32Object();
	virtual ~Win32Object();

	void registerWin32Class( const String& className, WNDPROC wndProc );

	static void addRegisterWin32Class( const String& className );

	/**
	*Checks whether the class has been registered. Performs a
	*std::find() using the registeredWindowClasses_ static list
	*/
	bool isRegistered();

	/**
	*called before the create window is called. Overide this to change the
	style and style ex parameters. Returns a pair, the pair.first is the style
	parameter, the pair.second is the style ex paramater.
	*/
	virtual CreateParams createParams();

	/**
	*This is where the window is actually created. Called from constructors
	*/
	void init();
	
	/**
	returns true if no further handling is required, otherwise returns false, which means 
	the rest of the handling needs to be done by the default wnd proc.
	*/
	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	static Win32Object* getWin32ObjectFromHWND( HWND hwnd );

	static void registerWin32Object( Win32Object* wndObj );

	HWND getHwnd();

	LRESULT defaultWndProcedure( UINT message, WPARAM wParam, LPARAM lParam );

	void setCreated( const bool& creationComplete );

	bool isCreated();

	void setPeerControl( Control* control );

	Control* getPeerControl();

	virtual bool acceptsWMCommandMessages(){
		return false;
	}

	void subclassWindow();

protected:
	void destroyWindowHandle();

	static std::vector< String > registeredWindowClasses_;
	static std::map<HWND, Win32Object*> windowMap_;
	/**
	*this actually contains the current window proc
	*/
	WNDPROC wndProc_;
	/**
	*this contains the window proc used for window
	*subclassing or just performing the default
	*behaviour. By default it is set
	*to point to ::DefWindowProc()
	*/
	WNDPROC defaultWndProc_;
	HWND hwnd_;
	bool created_;
	Control* peerControl_;
};



};


#endif // _VCF_WIN32OBJECT_H__

/**
$Id$
*/
