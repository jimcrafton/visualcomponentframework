#ifndef _VCF_APPLICATIONKIT_H__
#define _VCF_APPLICATIONKIT_H__
//ApplicationKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/FoundationKit.h"

#include "vcf/ApplicationKit/ApplicationKitSelectLib.h"

#include "vcf/GraphicsKit/GraphicsKit.h"

#include "vcf/ApplicationKit/KeyboardEvent.h"
#include "vcf/ApplicationKit/ScrollEvent.h"
#include "vcf/ApplicationKit/ValidationEvent.h"

#include "vcf/FoundationKit/InvalidStateException.h"
#include "vcf/ApplicationKit/ApplicationException.h"
#include "vcf/ApplicationKit/BadComponentStateException.h"
#include "vcf/ApplicationKit/BadModelStateException.h"

#include "vcf/ApplicationKit/ItemEditorEvent.h"


#include "vcf/ApplicationKit/ComponentEvent.h"
#include "vcf/ApplicationKit/Component.h"

/**
Action classes
*/
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"


/**
*Core model classes fopr the application kit
*/


#include "vcf/ApplicationKit/ModelEvent.h"
#include "vcf/ApplicationKit/Model.h"

#include "vcf/ApplicationKit/ItemEvent.h"
#include "vcf/ApplicationKit/Item.h"


/**
*Menus and menu items
*/
#include "vcf/ApplicationKit/MenuItem.h"
#include "vcf/ApplicationKit/MenuItemEvent.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"


#include "vcf/ApplicationKit/Menu.h"
#include "vcf/ApplicationKit/MenuBar.h"
#include "vcf/ApplicationKit/PopupMenu.h"



/**
*Clipboard
*/
#include "vcf/ApplicationKit/DataTypeNotSupportedException.h"
#include "vcf/ApplicationKit/DataObject.h"
#include "vcf/ApplicationKit/ClipboardEvent.h"
#include "vcf/ApplicationKit/Clipboard.h"

/**
*Drag Drop
*/
#include "vcf/ApplicationKit/DragSource.h"
#include "vcf/ApplicationKit/DragEvent.h"
#include "vcf/ApplicationKit/DragScrollEvent.h"

#include "vcf/ApplicationKit/DropEvent.h"


#include "vcf/ApplicationKit/DropTarget.h"


/**
*Application services
*/
#include "vcf/ApplicationKit/AbstractApplication.h"
#include "vcf/ApplicationKit/LibraryApplication.h"
#include "vcf/ApplicationKit/Application.h"



#include "vcf/ApplicationKit/Border.h"

#include "vcf/ApplicationKit/Cursor.h"

/**
*Control events
*/
#include "vcf/ApplicationKit/MouseEvent.h"
#include "vcf/ApplicationKit/FocusEvent.h"
#include "vcf/ApplicationKit/ToolTipEvent.h"
#include "vcf/ApplicationKit/WhatsThisHelpEvent.h"
#include "vcf/ApplicationKit/HelpEvent.h"

#include "vcf/ApplicationKit/ControlGraphicsContext.h"

/**
*Views
*/
#include "vcf/ApplicationKit/View.h"
#include "vcf/ApplicationKit/AbstractView.h"

/**
*Keyboard accelerators
*/
#include "vcf/ApplicationKit/AcceleratorKey.h"

/**
*Toolkit stuff
*/
#include "vcf/FoundationKit/NoToolKitFoundException.h"
#include "vcf/ApplicationKit/UIMetricsManager.h"
#include "vcf/ApplicationKit/UIPolicyManager.h"
#include "vcf/ApplicationKit/UIToolkit.h"



#include "vcf/ApplicationKit/Control.h"
#include "vcf/ApplicationKit/ControlEvent.h"


#include "vcf/ApplicationKit/CustomControl.h"
#include "vcf/ApplicationKit/Container.h"
#include "vcf/ApplicationKit/ControlContainer.h"
#include "vcf/ApplicationKit/Containers.h"

#include "vcf/ApplicationKit/FrameEvent.h"
#include "vcf/ApplicationKit/WindowEvent.h"

#include "vcf/ApplicationKit/Frame.h"

#include "vcf/ApplicationKit/Dialog.h"

/**
*Common dialogs, file open, file save, etc
*/
#include "vcf/ApplicationKit/CommonDialog.h"

#include "vcf/ApplicationKit/CommonFileDialog.h"
#include "vcf/ApplicationKit/CommonFileOpenDialog.h"
#include "vcf/ApplicationKit/CommonFileSaveDialog.h"
#include "vcf/ApplicationKit/CommonFontDialog.h"
#include "vcf/ApplicationKit/CommonPrintDialog.h"
#include "vcf/ApplicationKit/CommonColorDialog.h"
#include "vcf/ApplicationKit/CommonFileBrowseDialog.h"

/**
*Button classes
*/
#include "vcf/ApplicationKit/Button.h"
#include "vcf/ApplicationKit/ButtonEvent.h"


#include "vcf/ApplicationKit/Window.h"
#include "vcf/ApplicationKit/Scrollable.h"


#include "vcf/ApplicationKit/CursorManager.h"

#include "vcf/ApplicationKit/ImageListEvent.h"
#include "vcf/ApplicationKit/ImageList.h"


/**
*Borders
*/
#include "vcf/ApplicationKit/Basic3DBorder.h"
#include "vcf/ApplicationKit/Light3DBorder.h"


/**
*Desktop class
*/
#include "vcf/ApplicationKit/Desktop.h"



/**
*Application undo redo support - uses command pattern
*/
#include "vcf/ApplicationKit/Command.h"
#include "vcf/ApplicationKit/CommandGroup.h"
#include "vcf/ApplicationKit/UndoRedoEvent.h"
#include "vcf/ApplicationKit/AbstractCommand.h"
#include "vcf/ApplicationKit/UndoRedoStack.h"


/**
*Scrolling support
*/
#include "vcf/ApplicationKit/AbstractScrollable.h"
#include "vcf/ApplicationKit/ScrollbarManager.h"

#include "vcf/ApplicationKit/ComponentInfo.h"


/**
*Timers
*/
#include "vcf/ApplicationKit/TimerEvent.h"
#include "vcf/ApplicationKit/TimerComponent.h"


/**
*peer classes
*/

#include "vcf/ApplicationKit/CursorPeer.h"
#include "vcf/ApplicationKit/ApplicationPeer.h"
#include "vcf/ApplicationKit/ClipboardPeer.h"
#include "vcf/ApplicationKit/DataObjectPeer.h"
#include "vcf/ApplicationKit/DragDropPeer.h"
#include "vcf/ApplicationKit/DropTargetPeer.h"
#include "vcf/ApplicationKit/CommonDialogPeer.h"
#include "vcf/ApplicationKit/ControlPeer.h"


/**
\class ApplicationKit ApplicationKit.h "vcf/ApplicationKit/ApplicationKit.h"
*/
namespace VCF {
	class APPLICATIONKIT_API ApplicationKit {
	public:
		/**
		*initializes the Application Kit runtime.
		*This includes registering the basic classes in the runtime system
		*This MUST be called first off in the main() function of the app
		*This will automatically call
			FoundationKit::init();
		and
			GraphicsKit::init();
		*/
		static void init( int argc, char** argv );

		static void terminate();
	};
};


#endif // _VCF_APPLICATIONKIT_H__

/**
$Id$
*/
