#ifndef _VCF_CONTROLSKIT_H__
#define _VCF_CONTROLSKIT_H__
//ControlsKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifdef WIN32
	#ifdef CONTROLSKITDLL_EXPORTS
		#define CONTROLKIT_API __declspec(dllexport)
	#else
		#define CONTROLKIT_API __declspec(dllimport)
	#endif //CONTROLSKITDLL_EXPORTS
#else
	#define CONTROLKIT_API
#endif //WIN32


/**
*Use this include header for adding support for common controls in the VCF
*/

#ifndef _VCF_PANEL_H__
#	include "vcf/ApplicationKit/Panel.h"
#endif // _VCF_PANEL_H__

#ifndef _VCF_LABEL_H__
#	include "vcf/ApplicationKit/Label.h"
#endif // _VCF_LABEL_H__


#ifndef _VCF_LISTVIEWCONTROL_H__
#	include "vcf/ApplicationKit/ListViewControl.h"
#endif // _VCF_LISTVIEWCONTROL_H__

#ifndef _VCF_TEXTCONTROL_H__
#	include "vcf/ApplicationKit/TextControl.h"
#endif // _VCF_TEXTCONTROL_H__

#ifndef _VCF_MULTILINETEXTCONTROL_H__
#	include "vcf/ApplicationKit/MultilineTextControl.h"
#endif // _VCF_MULTILINETEXTCONTROL_H__

#ifndef _VCF_TREECONTROL_H__
#	include "vcf/ApplicationKit/TreeControl.h"
#endif // _VCF_TREECONTROL_H__

#ifndef _VCF_LISTBOXCONTROL_H__
#	include "vcf/ApplicationKit/ListBoxControl.h"
#endif // _VCF_LISTBOXCONTROL_H__

#ifndef _VCF_IMAGECONTROL_H__
#	include "vcf/ApplicationKit/ImageControl.h"
#endif // _VCF_IMAGECONTROL_H__

#ifndef _VCF_HTMLBROWSERCONTROL_H__
#	include "vcf/ApplicationKit/HTMLBrowserControl.h"
#endif // _VCF_HTMLBROWSERCONTROL_H__


#ifndef _VCF_TOGGLEDBUTTON_H__
#	include "vcf/ApplicationKit/ToggledButton.h"
#endif // _VCF_TOGGLEDBUTTON_H__

#ifndef _VCF_CHECKBOXCONTROL_H__
#	include "vcf/ApplicationKit/CheckBoxControl.h"
#endif // _VCF_CHECKBOXCONTROL_H__

#ifndef _VCF_COMMANDBUTTON_H__
#	include "vcf/ApplicationKit/CommandButton.h"
#endif // _VCF_COMMANDBUTTON_H__

#ifndef _VCF_COMBOBOXCONTROL_H__
#	include "vcf/ApplicationKit/ComboBoxControl.h"
#endif // _VCF_COMBOBOXCONTROL_H__

#ifndef _VCF_RADIOBUTTONCONTROL_H__
#	include "vcf/ApplicationKit/RadioButtonControl.h"
#endif // _VCF_RADIOBUTTONCONTROL_H__

#ifndef _VCF_TABPAGE_H__
#	include "vcf/ApplicationKit/TabPage.h"
#endif // _VCF_TABPAGE_H__

#ifndef _VCF_TABBEDPAGES_H__
#	include "vcf/ApplicationKit/TabbedPages.h"
#endif // _VCF_TABBEDPAGES_H__

#ifndef _VCF_TOOLBARDOCK_H__
#	include "vcf/ApplicationKit/ToolbarDock.h"
#endif // _VCF_TOOLBARDOCK_H__

#ifndef _VCF_HEADERCONTROL_H__
#	include "vcf/ApplicationKit/HeaderControl.h"
#endif // _VCF_HEADERCONTROL_H__

#ifndef _VCF_PUSHBUTTON_H__
#	include "vcf/ApplicationKit/PushButton.h"
#endif // _VCF_PUSHBUTTON_H__

#ifndef _VCF_SPLITTER_H__
#	include "vcf/ApplicationKit/Splitter.h"
#endif // _VCF_SPLITTER_H__

#ifndef _VCF_STATUSBAR_H__
#	include "vcf/ApplicationKit/StatusBar.h"
#endif // _VCF_STATUSBAR_H__

#ifndef _VCF_TABLECONTROL_H__
#	include "vcf/ApplicationKit/TableControl.h"
#endif // _VCF_TABLECONTROL_H__

#ifndef _VCF_TABLEITEMEDITOR_H__
#	include "vcf/ApplicationKit/TableItemEditor.h"
#endif // _VCF_TABLEITEMEDITOR_H__

#ifndef _VCF_BASICTABLEITEMEDITOR_H__
#	include "vcf/ApplicationKit/BasicTableItemEditor.h"
#endif // _VCF_BASICTABLEITEMEDITOR_H__

#ifndef _VCF_TOOLBAR_H__
#	include "vcf/ApplicationKit/Toolbar.h"
#endif // _VCF_TOOLBAR_H__


#ifndef _VCF_TREELISTCONTROL_H__
#	include "vcf/ApplicationKit/TreeListControl.h"
#endif // _VCF_TREELISTCONTROL_H__


#ifndef _VCF_PROGRESSCONTROL_H__
#	include "vcf/ApplicationKit/ProgressControl.h"
#endif // _VCF_PROGRESSCONTROL_H__


#ifndef _VCF_SLIDERCONTROL_H__
#	include "vcf/ApplicationKit/SliderControl.h"
#endif // _VCF_SLIDERCONTROL_H__


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.4.4.1  2004/04/26 21:58:15  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.6.4  2003/12/02 05:50:04  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.3.6.3  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*Revision 1.3.6.2  2003/09/12 00:09:31  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.3.6.1  2003/09/06 19:45:44  ddiego
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
*Revision 1.3  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.14.2  2003/01/11 19:52:09  marcelloptr
*deleted core/ControlsKit.h graphics/GraphicsKit.h and remote/RemoteObjectKit.h
*
*Revision 1.2.14.1  2002/12/25 22:06:11  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.1  2002/05/01 01:19:50  ddiego
*added remaining new files from switching stuff around
*like the peer classes and some of the drag drop stuff
*
*
*Revision 1.2  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CONTROLSKIT_H__


