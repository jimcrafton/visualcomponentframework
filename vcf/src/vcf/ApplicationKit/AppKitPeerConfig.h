#ifndef _VCF_APPLICATIONKITPEERCONFIG_H__
#define _VCF_APPLICATIONKITPEERCONFIG_H__
//AppKitPeerConfig.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifdef WIN32
//COM stuff
#include "vcf/ApplicationKit/VCFCOM.h"
#include "COMObject.h"
#include "vcf/ApplicationKit/EnumObject.h"
#include "vcf/ApplicationKit/COMDataObject.h"
#include "COMDropTarget.h"

//controls & GDI stuff
#include <Commdlg.h>

#include "vcf/ApplicationKit/Win32ToolKit.h"
#include "vcf/ApplicationKit/Win32Object.h"
#include "vcf/ApplicationKit/AbstractWin32Component.h"
#include "vcf/ApplicationKit/Win32ResourceBundle.h"
#include "vcf/ApplicationKit/Win32ResourceStream.h"
#include "vcf/ApplicationKit/Win32Component.h"
#include "vcf/ApplicationKit/Win32Window.h"
#include "vcf/GraphicsKit/Win32Context.h"
#include "vcf/GraphicsKit/Win32Image.h"
#include "vcf/ApplicationKit/Win32Application.h"
#include "vcf/ApplicationKit/Win32Edit.h"
#include "vcf/ApplicationKit/Win32Tree.h"
#include "vcf/ApplicationKit/Win32Listview.h"
#include "vcf/ApplicationKit/Win32Dialog.h"
#include "vcf/ApplicationKit/Win32Button.h"
#include "vcf/ApplicationKit/Win32MenuItem.h"
#include "vcf/ApplicationKit/Win32MenuBar.h"
#include "vcf/ApplicationKit/Win32FileOpenDialog.h"
#include "vcf/ApplicationKit/Win32FileSaveDialog.h"
#include "vcf/ApplicationKit/Win32ColorDialog.h"
#include "vcf/ApplicationKit/Win32DropTargetPeer.h"
#include "vcf/ApplicationKit/Win32ControlContext.h"
#include "vcf/ApplicationKit/Win32PopupMenu.h"
#include "vcf/ApplicationKit/Win32FolderBrowseDialog.h"
#include "vcf/ApplicationKit/Win32FontDialog.h"
#include "vcf/ApplicationKit/Win32Desktop.h"
#include "vcf/ApplicationKit/Win32ScrollPeer.h"
#include "vcf/ApplicationKit/Win32CursorPeer.h"
#include "vcf/ApplicationKit/Win32ToolKit.h"
#endif


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.2  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.6.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.6  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.1  2003/01/08 00:19:44  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.3  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_APPLICATIONKITPEERCONFIG_H__


