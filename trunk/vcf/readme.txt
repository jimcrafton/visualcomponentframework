Visual Component Framework 0.6.5 

Readme

The 0-6-5 release fixes a number of bugs, plus adds a number of new features, and also adds 
more support for the OSX platform, as well as new compiler support for Borland's C/C++ compiler.

Some of the bugs fixed include:
  - better support for Win32 border drawing - this means that the controls draw the actual VCF
  border and adjust the non-client bounds accordingly.
  - 776440	ClassReg doesn't call addImplementedInterface
  - 932883	Wrong Scintilla link on homepage!
  - 937106	missing $(VCF_INCLUDE) in Strings example
  - 978678	Toolbar flickers when window resized.
  - 978679	Missing functionality in Actions Example.
  - 978681	Copy past example busted.
  - 980106	set Frame to null should cause removing of menubar.
  - 985136	StringUtils cast to (int) and ulong64.
  - 995642	delete LocalePeer in Locale.
  - 998161	Thread should not have pause and continue
  - some subtle bugs in the Doc/View DocumentManager code
  - some subtle draw errors were fixed in some of the VCF Controls including the 
  TableControl and TabbedPages control.

Some of the new features include:
 - A revamped file structure that should make it much much easier to deternmine which files
 belong with which kit.
 
 - A new kit. We now support OpenGL via the OpenGLKit. This work on Win32 and it is rumored to work on 
 linux as well.
 
 - A new API for the File, Directory, and Directory::Finder classes. This includes support 
 for getting the file creation/access/modification time, getting file size as an 64 bit number,
 getting an input and/or output stream to the file, getting file attributes and more.
 
 - The Unicode transition is now complete. For Win32 systems we now support a single library/
 binary that can work on either NT based system or Win9.x system without worrying about
 defining _MBCS or _UNICODE builds. 
 
 - Improved API for drawing various "theme" elements of a windowing system with support 
 for indicating the state of the element.
 
 - Much improved support on Win32 for drawing in the non-client area. This means that VCF wrapped
 controls will properly draw their border object and the non-client area dimensions will reflect 
 this.
 
 - Multi-lingual support in the locale class is now used in the ApplicationKit as well. So you
 can write your strings file with your language translations and it will show up in your UI 
 elements. Most UI elements have been transitioned to be "aware" of this (it's a single line of code 
 to support this, os if we missed anything it's easy to fix).
 
  - Better VC7/7.1 support. We now support Application wizards to make creating a VCF application
 as easy as it is on VC6.
 
 - XCode application wizards to make it easy to create VCF based applications with Apple's 
 XCode IDE.


We have new and improved examples, especially a much improved QuickTime media player that shows
how to use QuickTime on Win32 and demo using the locale translation features.

The Mac OSX port is coming along, with basic support for the FoundationKit, 
GraphicsKits and ApplicationKit. There's still lots to do, but we can run some of the samples
now on OSX. 

We have added an additional compiler that the VCF can be built on for Win32, You can now 
use Borland's C++ 5.5 or 6 compilers to build the VCF.

 
 
  
Other miscellaneous tasks for this release:
 - 82276	add auto init to Library class
 - 101572	Switch & rename default containers for controls
 - 101477	Add OSX FileStream peer
 - 101478	Add OSX Condition peer
 - 101479	Add OSX Thread peer	
 - 101481	Add OSX Mutex peer
 - 101482	Add OSX Semaphore peer
 - 101483	Add OSX System peer
 - 101488	Add OSX Context peer
 - 101487	Add OSX Font peer
 - 101489	Add OSX GraphicsToolkit
 - 101490	Add OSX Image class
 - 101491	Add OSX Application peer
 - 101499	Add OSX lightweight control peer
 - 37707	Port to Borland C++ 5.x compiler
 - 101573	Model, Items, Views Docs (3.3.9 - 3.3.11 of Ref.Manual)
 - 72693	Toolbar
 
Known issues:
The OSX port is still a work in progress. Some of the examples work,
namely:

Alignment
Conditions
DateTimeUI
DatesAndTime
Dictionaries
EventBasics
FilesAndDirectories
GraphicsBasics
HelloWorld
HelloWorld2
HelloWorld3
Reflection
Strings
TextLayout
ThreadBasics
WorkingWithEnumerators

There is still alot of work to be done on the osx port. Hopefully by the next release
(0-6-6) this will all be accomplished. 
That said you should be able to build the framework using the supplied 
projects. Look in vcf/build/xcode if you use XCode, or try the 
vcf/build/osx-pb fopr ProjectBuilder projects.



The linux port is also still in progress. Not much to say other than it 
needs a lot of help.




Visual Component Framework 0.5.9 

Readme

Known issues:




Visual Component Framework 0.5.4 

Readme

Known issues:

There may be path problems when trying to run executable that link with the VCF Runtime DLL's ( FoundationKit.dll, GraphicsKit.dll, and ApplicationKit.dll). These require a path variable called VCF_BIN to be added to your system PATH variable. The installer adds this to your user PATH but if this does not work then it will probably need to added to you local PATH. For this you'll need Administrator privileges. If you know of a better solution please contact me(ddiego@one.net) !  

Add-ins sometimes do not get added automatically to Dev Studio. These can be added manually by clicking the "Tools > Customize..." menu item and selecting the "Add-ins and macro files" tab page. Click on the "Browse..." button and look in the vcf\build\vc60\add-ins directory and then go to the specific add in project you want to add (generally VCFNewClassWiz\Release\VCFNewClassWiz.dll for now). Select the dll and click OK. The add-in will be plugged into Dev Studio for you. If there are no dlls then just build the add and repeat the previous steps. 


People experiencing any problems during or after the 
install should go to VCF Bugs(http://sourceforge.net/tracker/?func=add&group_id=6796&atid=106796) 
and submit a bug report.

Please note that documentation is currently under flux at the moment, but may be found in the following places:
	- http://sourceforge.net/docman/?group_id=6796
	- The installed documentation (for Win32 systems) in HTML Help format (*.chm), which should be in docs
	  docs directory under the root of wherever you chose to install the VCF.
	- 
