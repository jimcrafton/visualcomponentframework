Visual Component Framework 0.6.6

Readme

Bugs fixed include:
1074768	VCF application slows down modal dialogs.
1045603 Some comparison operators of the class point are not const
1042623 Incorect handling of DC in win32font
1026443 Small windows with wrong border
1016150 Listbox Horizontal Scrollbar (show-through)
1015786 Listbox Horizontal Scrollbar (show-through)
1015368 ListBoxControl Mousemove error
A number of other miscellaneous bugs were fixed as well.
	
New features include:
1015739 recursive findComponent(), findControl()
999710 add method to System to get Resources dir
999698 migrate resources over to foundation kit

Printing, printing, printing!!! We have (finally) added an easy to use 
API for printing (see the PrintSession class). You can see this in action 
in the vcf/examples/Printing and vcf/examples/TextEdit examples.

We have added support for the system tray on Win32. Not implemented (yet) 
on OS X.

We have migrated the ResourceBundle class to the FoundationKit, so that console, 
non-gui apps can also use resources. 

We have added support for "bundle" resources, i.e. loading resources based on a 
formal directory pattern, in addition to be able to load resources from a binary 
file (i.e. Win32 rc style resources). 

Along with this "bundle" support we have modified the way processes and shared 
libraries (DLLs) are loaded, so that we can load a bundle directory as a process 
(just like OS X can) or shared lib. Along with this comes the notion of extra 
process/library meta data in the form of the ProgramInfo class. This allows us 
to retrieve what version the app is, the author, etc. This information may be stored 
in the exectuable bundle, or directly in the executable itself (Win32 only as 
VS_VERSIONINFO data).

Full transformation support was cleared up, or fixed in the GraphicsContext class. 
You can now transform any path, or image. Partial text transforms are supported in 
the form of translation and rotation. You can see this in the vcf/examples/Transformations 
example.

There is also more documentation in this release. A number of the core graphics 
classes have better, more complete source documentation for how/why they work. 
Marcello also contributed source documentation to the Document/View classes. Several 
new examples were added, namely TextEdit, which demonstrates a full Doc/View app 
that allows you to open, edit, save, and print text documents, and also demonstrated 
how to add undo/redo support, Resources, a simple console program which demonstrates 
how to load resources, AppResources, a simple GUI app that demonstrates resource loading, 
Dialogs, a small app that show how to call up the various standard dialogs as well as 
write your own custom dialogs, and Transformations, a gui demo that show how to transform 
graphics. Another example is the ParticleEditor which uses the OpenGLKit and demonstrate 
a little editor that lets you control a particle system.



Tasks for this release:
56662	implement printer support
101508	Add OSX MenuItem peer
101516	Add OSX UIToolkit peer
101514	Add OSX Window peer
101498	Add OSX Control peer
101507	Add OSX MenuBar peer
101502	Add OSX Dialog peer
101495	Add OSX Common folder browser dialog peer
101494	Add OSX Common file dialog peer
101496	Add OSX Common color dialog peer
101484	Add OSX Process peer
101480	Add OSX Library peer
101492	Add OSX Button peer
101500	Add OSX Cursor peer



Known issues:
You may need to change the output directory on some of the projects so that 
the executable is output at the same level as the "Resources" directory if one
is present. The projects that this needs to be done for are:

  -AppResources
  -Resources
  -DocViewAdvanced
  -DocViewBasics
  -TextEdit
  -Locales  

Also remove the "vc6" suffix (or vc7, vc71, depending on your compiler) from 
the executable name in the link settings.

The OSX port is still a work in progress. Further work was accomplished and the window, 
and control peers are basically done. Support was added for handling mouse event properly, 
loading processes and shared libs, using dialogs (including support for sheets), common 
dialog peers are all but done with the exception of the font dialog. Menu items work, but 
we still need a bit more work to handle them at the application level, so that differences 
in how Win32 vs. OS X see menus are all handled transparently. 




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