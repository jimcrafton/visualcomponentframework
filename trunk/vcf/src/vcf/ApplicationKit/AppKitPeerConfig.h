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


#endif // _VCF_APPLICATIONKITPEERCONFIG_H__

/**
$Id$
*/
