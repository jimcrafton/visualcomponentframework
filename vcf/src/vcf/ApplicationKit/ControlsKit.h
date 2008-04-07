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


#ifdef VCF_WIN
	#ifdef CONTROLSKITDLL_EXPORTS
		#define CONTROLKIT_API __declspec(dllexport)
	#else
		#define CONTROLKIT_API __declspec(dllimport)
	#endif //CONTROLSKITDLL_EXPORTS
#else
	#define CONTROLKIT_API
#endif //VCF_WIN


/**
*Use this include header for adding support for common controls in the VCF
*/

#ifndef _VCF_PANEL_H__
#	include "vcf/ApplicationKit/Panel.h"
#endif // _VCF_PANEL_H__

#ifndef _VCF_LABEL_H__
#	include "vcf/ApplicationKit/Label.h"
#endif // _VCF_LABEL_H__

#ifndef _VCF_LISTCONTROL_H__
#	include "vcf/ApplicationKit/ListControl.h"
#endif // _VCF_LISTCONTROL_H__

#ifndef _VCF_DROPDOWNCONTROL_H__
#	include "vcf/ApplicationKit/DropDownControl.h"
#endif // _VCF_DROPDOWNCONTROL_H__


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


#ifndef _VCF_PUSHBUTTON_H__
#	include "vcf/ApplicationKit/PushButton.h"
#endif // _VCF_PUSHBUTTON_H__

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


#endif // _VCF_CONTROLSKIT_H__

/**
$Id$
*/
