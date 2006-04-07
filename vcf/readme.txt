Visual Component Framework 0.9.0

Readme
Bugs fixed include:
- 1458095 TextControl not operational
- 1449840 Undesirable repeatable desktop update
- 1276040 DefaultMenuItem::clearChildren doesn't call the peer
- 1251431 Drag and Drop example doesn't work with images
- 1249777 Win32ProcessIORedirector
- 1228429 ComboBox drop down list font is unchangable
- 1227570 Win32PrintSession::setDefaultPageSettings pointer...
- 1184442 Components move through each other when shrinking window
- 1171985 printInfo_.docInfo_.lpszDocName pointing to orphan pointer
- 1121899 ApplicationKitRTTI.inl error
- 1102590 Difficulty changing Windows themes
- 1090689 problem loading png image

- Added proper repainting when windows system settings changes
- Fixed bugs in Scrollbars that caused them to not move
as fluidly as they should
- Fixed bug in TreeListControl for incorrect calculation of virtual height
- Fixed bug in TreeListControl that caused the header control to be
misplaced.
- Fixed a number of appearance glitches in various examples
- Fixed a bug in the Win32Locales code that caused currency string
formatting to not show up correctly.
-fixed bug in document manager that left hanging document instances
in SDI policy mode.




New features include:
- Added basic XP theming for most controls.
- Added HTML Help integration
- Added better tooltip integration and support for fancier customization
of the tooltip
- Further OS X support, still ongoing.
- Consolidated some of the Item classes
- Added more documentation to both the source files and to the core
reference manual documentation.
- Added new compiler support in the form of mingw and CodeBlocks
support.
-Added new compiler support for Visual C++ 2005, including the Express
Edition.
- Added JPEG and PNG builtin support to the GraphicsKit
- Added HTMLKit and added new features to HTMLBrowserControl allowing
fairly advanced customization of the browser and navigation of the
HTML DOM.
- Added InternetKit
- Added several new examples
- updated AGG to the newest version (2.4)
- added Boost smart pointer integration
- added min/max constraints for windows
- revamped PropertyEditor interface and implementations
- revamped ComponentEditor interface and implementations
- added better support for reading in the Visual Form File format
- Proper support for inheritance in reading VFF files. This means that
one file can be specified for a base class, and another class which
derives from the base, will inherit and process the values from the original
base class's VFF before processing it's own.


Side note: A lot of time was spent on the VCF Builder (http://vcfbuilder.org) and 
getting that to work better, especially the Form Designer part.

Issues:
Some of the examples will not compile or work right with the Borland Free compiler,
specifically TeXLabel, and SharedLibraries.


Visual Component Framework 0.6.8

Readme

Bugs fixed include:
1212502 The TabbedPages control flickers
1044515	Selection problem in a tree control
940183	VCFSrcOnlyInstaller-0.6.4.exe doesn't 'install' VS6 wizards
585091	AcceleratorKey not routed correctly
1044747	PushButton has wrong size
1082362	App Icons do not appear on the Task Manager and others can't
1089345	CommonColor needs first choose basic colors on Win32
1089382	ComboBox fires a SelectionChanged msg when loosing focus
1096732	Application crashes when closing
1099910	ComboBox of AbstractPropertyEditor crash when loosing focus
1103156	Scrolling error in ListBox in Controls example
1108954	user "data" is not assigned to the SubItem of the TreeItem
1109025	The check mark is not drawn on CheckBox TreeItem
1111096	input by num keypad arent registered by TextControls
1112867	Press Return on ComboBox changes the selected item's caption
1119206	Win32MenuItem::isChecked returns "false". Allways!!!
1150771	When selecting all the text in the editor, setText is called
1150773	Win32Edit loses last n characters past the last 2048 written
1152064	Control's setEnabled doesn't force a repaint
1152067	PushButton doesn't show disabled status
1155518	Multi-column TreeListControl
1157348	SaveAs and cancel cause problem in DocumentManager class
1159282	ListBoxControl::setImageList
1161656	Window resize
1166682	Selecting a Listbox item through code
1175667	Lack of SysTray Icon Transparency
1176555	Mem Leak
1177879	Changing MultilineTextControl color in Window create
1177882	Changing Font color on a TextControl doesn't work
1177893	Most controls ignore system text color
1184431	Window scrollbars not visible until resize
1184432	Tables cell edit box follows scroll movement
1197970	UnicodeString::copy(UnicodeString::AnsiChar
1197974	Accelerator looks on a single control ony (recursive lookup)
1200128	TextControl's replaceText method doesn't work properly
1208948	DocViewAdvanced throws unknown framework exception.
1214627	Horizontal Scrolling bug
1216187	Add vc70 vc71 app wizards to installers
1227549	HorizontalLayoutContainer set the heights in the wrong rows.
1179853	memory problems around memset
1160871	VCF::String has no operator <<
1044740	PushButton ignores the second click of a double-click

Other bugs fixed were some goofs in the ResourceBundle implementation,
performance issues, miscellaneous bugs in the TableControl and 
TreeListControl.


New features included:

RunLoops, which allow for repitive loop behaviour, and the ability to 
now post an event from any RunLoop to another RunLoop. Each RunLoop
associated with a Thread.

Introduction of a ThreadManager to help manage threads and run loops.

Format class for replacing var arg functions like System::println().
Conceptually similar to boost's format class but not as fancy, at 
least not yet.

Consolidation of menu handling with addition of MenuManager. This was 
done to make menu handling work better both on Mac OSX and Win32.

Adjustments in the TextPeer class to allow for more flexible handling
of styled text. 

Port of VCF to CodeWarrior IDE completed.

Adjustments and some new features added to use AcceleratorKey objects.



Other work included a lot more documentation, both in the reference 
manual and in the source documentation.

Some refactoring in the Model classes and events, and changes in the 
TextModel.

Further work on OSX, almost all peer classes now implemented, at least 
to some degree.



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