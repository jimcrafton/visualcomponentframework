//ApplicationKitRTTI.inl

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
this declares all the RTTI for the ApplicationKit's classes.
This was created to improved compile times
*/

#include "vcf/ApplicationKit/EtchedBorder.h"
#include "vcf/ApplicationKit/ColorEtchedBorder.h"
#include "vcf/ApplicationKit/TitledBorder.h"
#include "vcf/ApplicationKit/MessageDialog.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"
#include "vcf/ApplicationKit/SystemTray.h"


namespace VCF {


BEGIN_CLASSINFO(ImageList, "VCF::ImageList", "VCF::Component", IMAGELIST_CLASSID )
OBJECT_PROPERTY( Color, "transparentColor", ImageList::getTransparentColor, ImageList::setTransparentColor );
EVENT("VCF::ImageListEventHandler", ImageList, VCF::ImageListEvent, SizeChanged );
EVENT("VCF::ImageListEventHandler", ImageList, VCF::ImageListEvent, ImageAdded );
EVENT("VCF::ImageListEventHandler", ImageList, VCF::ImageListEvent, ImageDeleted );
END_CLASSINFO(ImageList)


BEGIN_ABSTRACT_CLASSINFO(Border, "VCF::Border", "VCF::Object", BORDER_CLASSID)
END_CLASSINFO(Border)

BEGIN_CLASSINFO(Basic3DBorder, "VCF::Basic3DBorder", "VCF::Border", BASIC3DBORDER_CLASSID)
END_CLASSINFO(Basic3DBorder)

BEGIN_CLASSINFO(ColorEtchedBorder, "VCF::ColorEtchedBorder", "VCF::EtchedBorder", COLORETCHEDBORDER_CLASSID)
END_CLASSINFO(ColorEtchedBorder)

BEGIN_CLASSINFO(EtchedBorder, "VCF::EtchedBorder", "VCF::Border", ETCHEDBORDER_CLASSID)
END_CLASSINFO(EtchedBorder)

BEGIN_CLASSINFO(Light3DBorder, "VCF::Light3DBorder", "VCF::Border", LIGHT3DBORDER_CLASSID)
END_CLASSINFO(Light3DBorder)

BEGIN_CLASSINFO(TitledBorder, "VCF::TitledBorder", "VCF::Border", TITLEDBORDER_CLASSID)
END_CLASSINFO(TitledBorder)


/*
BEGIN_ABSTRACT_CLASSINFO(AbstractListModel, "VCF::AbstractListModel", "VCF::ListModel", ABSTRACTLISTMODEL_CLASSID)
EVENT( "VCF::ModelEventHandler", AbstractListModel, VCF::ModelEvent, ModelEmptied )
EVENT( "VCF::ModelValidationEventHandler", AbstractListModel, VCF::ValidationEvent, ModelValidate )
EVENT( "VCF::ListModelEventHandler", AbstractListModel, VCF::ListModelEvent, ContentsChanged )
EVENT( "VCF::ListModelEventHandler", AbstractListModel, VCF::ListModelEvent, ItemAdded )
EVENT( "VCF::ListModelEventHandler", AbstractListModel, VCF::ListModelEvent, ItemDeleted )
END_CLASSINFO(AbstractListModel)
*/

BEGIN_ABSTRACT_CLASSINFO(AbstractModel, "VCF::AbstractModel", "VCF::Model", ABSTRACTMODEL_CLASSID)
EVENT( "VCF::ModelEventHandler", AbstractModel, VCF::ModelEvent, ModelChanged )
EVENT( "VCF::ModelValidationEventHandler", AbstractModel, VCF::ValidationEvent, ModelValidate )
END_CLASSINFO(AbstractModel)

/*
BEGIN_ABSTRACT_CLASSINFO(TextModel, "VCF::TextModel", "VCF::Model", TEXTMODEL_CLASSID)
ABSTRACT_EVENT("VCF::TextModelEventHandler", TextModel, VCF::TextEvent, TextModelChanged )
END_CLASSINFO(TextModel)
*/

/*
BEGIN_ABSTRACT_CLASSINFO(AbstractTextModel, "VCF::AbstractTextModel", "VCF::TextModel", ABSTRACTTEXTMODEL_CLASSID)

EVENT("VCF::TextModelEventHandler", AbstractTextModel, VCF::TextEvent, TextModelChanged )
END_CLASSINFO(AbstractTextModel)
*/

BEGIN_ABSTRACT_CLASSINFO(ColumnItem, "VCF::ColumnItem", "VCF::Item", COLUMNITEM_CLASSID)
END_CLASSINFO(ColumnItem)




BEGIN_ABSTRACT_CLASSINFO(ColumnModel, "VCF::ColumnModel", "VCF::Model", COLUMNMODEL_CLASSID)
ABSTRACT_EVENT( "VCF::ColumnModelEventHandler", ColumnModel, VCF::ColumnModelEvent, ContentsChanged )
ABSTRACT_EVENT( "VCF::ColumnModelEventHandler", ColumnModel, VCF::ColumnModelEvent, ItemAdded )
ABSTRACT_EVENT( "VCF::ColumnModelEventHandler", ColumnModel, VCF::ColumnModelEvent, ItemDeleted )
END_CLASSINFO(ColumnModel)

BEGIN_ABSTRACT_CLASSINFO(Component, "VCF::Component", "VCF::Object", COMPONENT_CLASSID)
PROPERTY( long, "tag", Component::getTag, Component::setTag, pdLong );
PROPERTY( String, "name", Component::getName, Component::setName, pdString );
EVENT("VCF::ComponentEventHandler", Component, VCF::ComponentEvent, ComponentCreated );
EVENT("VCF::ComponentEventHandler", Component, VCF::ComponentEvent, ComponentDeleted );
END_CLASSINFO(Component);


BEGIN_ABSTRACT_CLASSINFO(Control, "VCF::Control", "VCF::Component", CONTROL_CLASSID);
PROPERTY( double, "left", Control::getLeft, Control::setLeft, pdDouble );
PROPERTY( double, "top", Control::getTop, Control::setTop, pdDouble );
PROPERTY( double, "right", Control::getRight, Control::setRight, pdDouble );
PROPERTY( double, "bottom", Control::getBottom, Control::setBottom, pdDouble );
PROPERTY( bool, "visible", Control::getVisible, Control::setVisible, pdBool );
PROPERTY( double, "width", Control::getWidth, Control::setWidth, pdDouble );
PROPERTY( double, "height", Control::getHeight, Control::setHeight, pdDouble );
PROPERTY( bool, "enabled", Control::isEnabled, Control::setEnabled, pdBool );
PROPERTY( bool, "doubleBuffered", Control::isDoubleBuffered, Control::setDoubleBuffered, pdBool );
PROPERTY( bool, "useParentFont", Control::useParentFont, Control::setUseParentFont, pdBool );
PROPERTY( bool, "autoStartDragDrop", Control::getAutoStartDragDrop, Control::setAutoStartDragDrop, pdBool );
PROPERTY( bool, "tabStop", Control::getTabStop, Control::setTabStop, pdBool );
PROPERTY( long, "tabOrder", Control::getTabOrder, Control::setTabOrder, pdLong );
PROPERTY( String, "whatThisHelpString", Control::getWhatThisHelpString, Control::setWhatThisHelpString, pdString );
PROPERTY( String, "toolTipText", Control::getToolTipText, Control::setToolTipText, pdString );
OBJECT_PROPERTY( Border, "border", Control::getBorder, Control::setBorder );
OBJECT_PROPERTY( Color, "color", Control::getColor, Control::setColor );
OBJECT_PROPERTY( Font, "font", Control::getFont, Control::setFont );
OBJECT_PROPERTY( PopupMenu, "popupMenu", Control::getPopupMenu, Control::setPopupMenu );
LABELED_ENUM_PROPERTY( AlignmentType, "alignment", Control::getAlignment, Control::setAlignment,
					   AlignNone, AlignClient, 6, AlignmentTypeNames);

ENUM_SET_PROPERTY( "anchor", Control::getAnchor, Control::setAnchor, 5, AnchorTypeValues, AnchorTypeNames  );

EVENT("VCF::ControlEventHandler", Control, VCF::ControlEvent, ControlSized );
EVENT("VCF::ControlEventHandler", Control, VCF::ControlEvent, ControlPositioned );
EVENT("VCF::ControlEventHandler", Control, VCF::ControlEvent, ControlParentChanged );
EVENT("VCF::MouseEventHandler", Control, VCF::MouseEvent, MouseDoubleClicked );
EVENT("VCF::MouseEventHandler", Control, VCF::MouseEvent, MouseClicked );
EVENT("VCF::MouseEventHandler", Control, VCF::MouseEvent, MouseMove );
EVENT("VCF::MouseEventHandler", Control, VCF::MouseEvent, MouseUp );
EVENT("VCF::MouseEventHandler", Control, VCF::MouseEvent, MouseDown );
EVENT("VCF::MouseEventHandler", Control, VCF::MouseEvent, MouseEnter );
EVENT("VCF::MouseEventHandler", Control, VCF::MouseEvent, MouseLeave );
EVENT("VCF::KeyboardEventHandler", Control, VCF::KeyboardEvent, KeyPressed  );
EVENT("VCF::KeyboardEventHandler", Control, VCF::KeyboardEvent, KeyDown  );
EVENT("VCF::KeyboardEventHandler", Control, VCF::KeyboardEvent, KeyUp  );
EVENT("VCF::WhatsThisHelpEventHandler", Control, VCF::WhatsThisHelpEvent, ControlHelpRequested );
EVENT("VCF::HelpEventHandler", Control, VCF::HelpEvent, HelpRequested );
EVENT("VCF::FocusEventHandler", Control, VCF::FocusEvent, FocusLost  );
EVENT("VCF::FocusEventHandler", Control, VCF::FocusEvent, FocusGained );

EVENT("VCF::ToolTipEventHandler", Control, VCF::ToolTipEvent, ToolTipRequested  );
EVENT("VCF::ToolTipEventHandler", Control, VCF::ToolTipEvent, ToolTip  );

END_CLASSINFO(Control);


BEGIN_ABSTRACT_CLASSINFO(Document, "VCF::Document", "VCF::AbstractModel", DOCUMENT_CLASSID)
END_CLASSINFO(Document)


BEGIN_ABSTRACT_CLASSINFO(Frame, "VCF::Frame", "VCF::Control", FRAME_CLASSID )
PROPERTY( String, "caption", Frame::getCaption, Frame::setCaption, pdString );
PROPERTY( bool, "isTopmost", Frame::isFrameTopmost, Frame::setFrameTopmost, pdBool );
LABELED_ENUM_PROPERTY( FrameStyleType, "frameStyle", Frame::getFrameStyle, Frame::setFrameStyle,
					   fstSizeable, fstToolbarBorderFixed, 6, FrameStyleTypeNames);
EVENT("VCF::FrameEventHandler", Frame, FrameEvent, FrameClosing)
EVENT("VCF::WindowEventHandler", Frame, WindowEvent, FrameClose )
EVENT("VCF::WindowEventHandler", Frame, WindowEvent, FrameActivation )
END_CLASSINFO(Frame)




BEGIN_ABSTRACT_CLASSINFO(Item, "VCF::Item", "VCF::Object", ITEM_CLASSID)
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, ItemPaint );
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, ItemChanged );
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, ItemSelected );
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, ItemAdded );
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, ItemDeleted );
END_CLASSINFO(Item)


BEGIN_ABSTRACT_CLASSINFO(ListItem, "VCF::ListItem", "VCF::Item", LISTITEM_CLASSID)
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, SubItemChanged );
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, SubItemAdded );
ABSTRACT_EVENT("VCF::ItemEventHandler", Item, VCF::ItemEvent, SubItemDeleted );
PROPERTY( String, "name", ListItem::getCaption, ListItem::setCaption, pdString )
END_CLASSINFO(ListItem)


/*
BEGIN_ABSTRACT_CLASSINFO(ListModel, "VCF::ListModel", "VCF::Model", LISTMODEL_CLASSID)
OBJECT_COLLECTION_PROPERTY(ListItem*, "items", ListModel::getItems, ListModel::addItem, ListModel::insertItem, ListModel::deleteItem, ListModel::deleteItemAtIndex )
ABSTRACT_EVENT( "VCF::ListModelEventHandler", ListModel, VCF::ListModelEvent, ContentsChanged )
ABSTRACT_EVENT( "VCF::ListModelEventHandler", ListModel, VCF::ListModelEvent, ItemAdded )
ABSTRACT_EVENT( "VCF::ListModelEventHandler", ListModel, VCF::ListModelEvent, ItemDeleted )
END_CLASSINFO(ListModel)
*/


BEGIN_ABSTRACT_CLASSINFO(MenuItem, "VCF::MenuItem", "VCF::Item", MENUITEM_CLASSID)
ABSTRACT_EVENT( "VCF::MenuItemEventHandler", MenuItem, VCF::MenuItemEvent, MenuItemClicked )
ABSTRACT_EVENT( "VCF::MenuItemEventHandler", MenuItem, VCF::MenuItemEvent, MenuItemUpdate )
PROPERTY( String, "caption", MenuItem::getCaption, MenuItem::setCaption, pdString )
END_CLASSINFO(MenuItem)


BEGIN_ABSTRACT_CLASSINFO(Model, "VCF::Model", "VCF::Object", MODEL_CLASSID)
ABSTRACT_EVENT( "VCF::ModelEventHandler", Model, VCF::ModelEvent, ModelEmptied )
ABSTRACT_EVENT( "VCF::ModelValidationEventHandler", Model, VCF::ValidationEvent, ModelValidate )
END_CLASSINFO(Model)

/* 
JC - Note that we should change this to RTTI as an interface!!!
BEGIN_ABSTRACT_CLASSINFO(TabModel, "VCF::TabModel", "VCF::Model", TABMODEL_CLASSID )
ABSTRACT_EVENT("VCF::TabModelEventHandler", TabModel, VCF::TabModelEvent, TabPageAdded)
ABSTRACT_EVENT("VCF::TabModelEventHandler", TabModel, VCF::TabModelEvent, TabPageRemoved)
ABSTRACT_EVENT("VCF::TabModelEventHandler", TabModel, VCF::TabModelEvent, TabPageSelected)
END_CLASSINFO(TabModel)
*/


BEGIN_ABSTRACT_CLASSINFO(TabPage, "VCF::TabPage", "VCF::Item", TABPAGE_CLASSID)
END_CLASSINFO(TabPage)


BEGIN_ABSTRACT_CLASSINFO(TableCellItem, "VCF::TableCellItem", "VCF::Item", TABLECELLITEM_CLASSID)
END_CLASSINFO(TableCellItem)

BEGIN_ABSTRACT_CLASSINFO(TableItemEditor, "VCF::TableItemEditor", "VCF::Object", TABLEITEMEDITOR_CLASSID)
ABSTRACT_EVENT("VCF::ItemEditorEventHandler", TableItemEditor, VCF::ItemEditorEvent, CellItemChanged )
ABSTRACT_EVENT("VCF::ItemEditorEventHandler", TableItemEditor, VCF::ItemEditorEvent, CellItemValidateChange )
END_CLASSINFO(TableItemEditor)


/*
BEGIN_ABSTRACT_CLASSINFO(TableModel, "VCF::TableModel", "VCF::AbstractModel", TABLEMODEL_CLASSID )
EVENT( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableCellAdded )
EVENT( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableCellDeleted )
EVENT( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableRowsAdded )
EVENT( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableRowsDeleted )
EVENT( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableColumnsAdded )
EVENT( "VCF::TableModelEventHandler", TableModel, VCF::TableModelEvent, TableColumnsDeleted )
END_CLASSINFO(TableModel);
*/




BEGIN_ABSTRACT_CLASSINFO(ToggledButton, "VCF::ToggledButton", "VCF::CustomControl", TOGGLEDBUTTON_CLASSID)
PROPERTY(bool, "checked", ToggledButton::isChecked, ToggledButton::setChecked, pdBool);
PROPERTY(String, "caption", ToggledButton::getCaption, ToggledButton::setCaption, pdString);
EVENT( "VCF::ButtonEventHandler", ToggledButton, VCF::ButtonEvent, ButtonClicked )
END_CLASSINFO(ToggledButton)



BEGIN_ABSTRACT_CLASSINFO(TreeItem, "VCF::TreeItem", "VCF::Item", TREEITEM_CLASSID)
OBJECT_COLLECTION_PROPERTY(TreeItem*, "children", TreeItem::getChildren,
	           TreeItem::addChild, TreeItem::insertChild, TreeItem::deleteChild, TreeItem::deleteChildAtIndex )
PROPERTY( String, "name", TreeItem::getCaption, TreeItem::setCaption, pdString )
END_CLASSINFO(TreeItem)


/*
BEGIN_ABSTRACT_CLASSINFO(TreeModel, "VCF::TreeModel", "VCF::Model", TREEMODEL_CLASSID)
//	OBJECT_PROPERTY( TreeItem, "root", TreeModel::getRoot, TreeModel::setRoot );
ABSTRACT_EVENT( "VCF::TreeModelEventHandler", TreeModel, VCF::TreeModelEvent, RootNodeChanged )
ABSTRACT_EVENT( "VCF::TreeModelEventHandler", TreeModel, VCF::TreeModelEvent, NodeAdded )
ABSTRACT_EVENT( "VCF::TreeModelEventHandler", TreeModel, VCF::TreeModelEvent, NodeDeleted )
END_CLASSINFO(TreeModel)
*/


/**
-------------------------------------------------------------------------------
*/

/*
BEGIN_CLASSINFO(AbstractTreeModel, "VCF::AbstractTreeModel", "VCF::TreeModel", ABSTRACTTREEMODEL_CLASSID)
EVENT( "VCF::ModelEventHandler", AbstractTreeModel, VCF::ModelEvent, ModelEmptied )
EVENT( "VCF::ModelValidationEventHandler", AbstractTreeModel, VCF::ValidationEvent, ModelValidate )
EVENT( "VCF::TreeModelEventHandler", AbstractTreeModel, VCF::TreeModelEvent, RootNodeChanged )
EVENT( "VCF::TreeModelEventHandler", AbstractTreeModel, VCF::TreeModelEvent, NodeAdded )
EVENT( "VCF::TreeModelEventHandler", AbstractTreeModel, VCF::TreeModelEvent, NodeDeleted )
END_CLASSINFO(AbstractTreeModel)
*/


BEGIN_CLASSINFO(BasicTableItemEditor, "VCF::BasicTableItemEditor", "VCF::TableItemEditor", BASICTABLEITEMEDITOR_CLASSID)
EVENT("VCF::ItemEditorEventHandler", BasicTableItemEditor, VCF::ItemEditorEvent, CellItemChanged )
EVENT("VCF::ItemEditorEventHandler", BasicTableItemEditor, VCF::ItemEditorEvent, CellItemValidateChange )
END_CLASSINFO(BasicTableItemEditor)

BEGIN_CLASSINFO(CheckBoxControl, "VCF::CheckBoxControl", "VCF::ToggledButton", CHECKBOXCONTROL_CLASSID )
END_CLASSINFO(CheckBoxControl)


BEGIN_CLASSINFO(ComboBoxControl, "VCF::ComboBoxControl", "VCF::CustomControl", COMBOBOXCONTROL_CLASSID )
EVENT("ItemEventHandler", ComboBoxControl, VCF::ItemEvent, SelectionChanged )
END_CLASSINFO(ComboBoxControl)


BEGIN_CLASSINFO(CommandButton, "VCF::CommandButton", "VCF::Control", COMMANDBUTTON_CLASSID)
PROPERTY( String, "caption", CommandButton::getCaption, CommandButton::setCaption, pdString );
LABELED_ENUM_PROPERTY( ButtonCommandType, "commandType", CommandButton::getCommandType, CommandButton::setCommandType,
					   BC_NONE, BC_MAYBE, 6, ButtonCommandTypeNames);
EVENT( "VCF::ButtonEventHandler", CommandButton, VCF::ButtonEvent, ButtonClicked )
END_CLASSINFO(CommandButton)


BEGIN_CLASSINFO(ControlContainer, "VCF::ControlContainer", "VCF::CustomControl", CONTROLCONTAINER_CLASSID)
PROPERTY(double, "bottomBorderHeight", ControlContainer::getBottomBorderHeight, ControlContainer::setBottomBorderHeight, pdDouble);
PROPERTY(double, "topBorderHeight", ControlContainer::getTopBorderHeight, ControlContainer::setTopBorderHeight, pdDouble);
PROPERTY(double, "rightBorderWidth", ControlContainer::getRightBorderWidth, ControlContainer::setRightBorderWidth, pdDouble);
PROPERTY(double, "leftBorderWidth", ControlContainer::getLeftBorderWidth, ControlContainer::setLeftBorderWidth, pdDouble);
PROPERTY(double, "borderSize", ControlContainer::getBorderSize, ControlContainer::setBorderSize, pdDouble);
END_CLASSINFO(ControlContainer)


BEGIN_CLASSINFO(CustomControl, "VCF::CustomControl", "VCF::Control", CUSTOMCONTROL_CLASSID )
PROPERTY( bool, "transparent", CustomControl::isTransparent, CustomControl::setTransparent, pdBool );
END_CLASSINFO(CustomControl)


BEGIN_CLASSINFO(DefaultColumnItem, "VCF::DefaultColumnItem", "VCF::ColumnItem", DEFAULTCOLUMNITEM_CLASSID)
EVENT("VCF::ItemEventHandler", DefaultColumnItem, VCF::ItemEvent, ItemPaint );
EVENT("VCF::ItemEventHandler", DefaultColumnItem, VCF::ItemEvent, ItemChanged );
EVENT("VCF::ItemEventHandler", DefaultColumnItem, VCF::ItemEvent, ItemSelected );
EVENT("VCF::ItemEventHandler", DefaultColumnItem, VCF::ItemEvent, ItemAdded );
EVENT("VCF::ItemEventHandler", DefaultColumnItem, VCF::ItemEvent, ItemDeleted );
END_CLASSINFO(DefaultColumnItem)

BEGIN_CLASSINFO(DefaultColumnModel, "VCF::DefaultColumnModel", "VCF::ColumnModel", DEFAULTCOLUMNMODEL_CLASSID)
EVENT( "VCF::ColumnModelEventHandler", DefaultColumnModel, VCF::ColumnModelEvent, ContentsChanged )
EVENT( "VCF::ColumnModelEventHandler", DefaultColumnModel, VCF::ColumnModelEvent, ItemAdded )
EVENT( "VCF::ColumnModelEventHandler", DefaultColumnModel, VCF::ColumnModelEvent, ItemDeleted )
END_CLASSINFO(DefaultColumnModel)

BEGIN_CLASSINFO(DefaultMenuItem, "VCF::DefaultMenuItem", "VCF::MenuItem", DEFAULTMENUITEM_CLASSID)
EVENT( "VCF::MenuItemEventHandler", DefaultMenuItem, VCF::MenuItemEvent, MenuItemClicked )
EVENT( "VCF::MenuItemEventHandler", DefaultMenuItem, VCF::MenuItemEvent, MenuItemUpdate )
END_CLASSINFO(DefaultMenuItem)


BEGIN_CLASSINFO(DefaultListItem, "VCF::DefaultListItem", "VCF::ListItem", DEFAULTLISTITEM_CLASSID)
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, ItemPaint );
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, ItemChanged );
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, ItemSelected );
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, ItemAdded );
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, ItemDeleted );
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, SubItemChanged );
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, SubItemAdded );
EVENT("VCF::ItemEventHandler", DefaultListItem, VCF::ItemEvent, SubItemDeleted );
END_CLASSINFO(DefaultListItem)


BEGIN_CLASSINFO(DefaultListModel, "VCF::DefaultListModel", "VCF::AbstractModel", DEFAULTLISTMODEL_CLASSID)
END_CLASSINFO(DefaultListModel)


BEGIN_CLASSINFO(DefaultTabModel, "VCF::DefaultTabModel", "VCF::AbstractModel", DEFAULTTABMODEL_CLASSID )
	EVENT("VCF::TabModelEventHandler", DefaultTabModel, VCF::TabModelEvent, TabPageAdded )
	EVENT("VCF::TabModelEventHandler", DefaultTabModel, VCF::TabModelEvent, TabPageRemoved )
	EVENT("VCF::TabModelEventHandler", DefaultTabModel, VCF::TabModelEvent, TabPageSelected )
	EVENT( "VCF::ModelEventHandler", DefaultTabModel, VCF::ModelEvent, ModelEmptied )
	EVENT( "VCF::ModelValidationEventHandler", DefaultTabModel, VCF::ValidationEvent, ModelValidate )
END_CLASSINFO(DefaultTabModel)


BEGIN_CLASSINFO(DefaultTabPage, "VCF::DefaultTabPage", "VCF::TabPage", DEFAULTTABPAGE_CLASSID)
	EVENT("VCF::ItemEventHandler", DefaultTabPage, VCF::ItemEvent, ItemPaint );
	EVENT("VCF::ItemEventHandler", DefaultTabPage, VCF::ItemEvent, ItemChanged );
	EVENT("VCF::ItemEventHandler", DefaultTabPage, VCF::ItemEvent, ItemSelected );
	EVENT("VCF::ItemEventHandler", DefaultTabPage, VCF::ItemEvent, ItemAdded );
EVENT("VCF::ItemEventHandler", DefaultTabPage, VCF::ItemEvent, ItemDeleted );

END_CLASSINFO(DefaultTabPage)


BEGIN_CLASSINFO(DefaultTableCellItem, "VCF::DefaultTableCellItem", "VCF::TableCellItem", DEFAULTTABLECELLITEM_CLASSID)
	EVENT("VCF::ItemEventHandler", DefaultTableCellItem, VCF::ItemEvent, ItemPaint );
	EVENT("VCF::ItemEventHandler", DefaultTableCellItem, VCF::ItemEvent, ItemChanged );
	EVENT("VCF::ItemEventHandler", DefaultTableCellItem, VCF::ItemEvent, ItemSelected );
	EVENT("VCF::ItemEventHandler", DefaultTableCellItem, VCF::ItemEvent, ItemAdded );
	EVENT("VCF::ItemEventHandler", DefaultTableCellItem, VCF::ItemEvent, ItemDeleted );

END_CLASSINFO(DefaultTableCellItem)


BEGIN_CLASSINFO(DefaultTableModel, "VCF::DefaultTableModel", "VCF::AbstractModel", DEFAULTTABLEMODEL_CLASSID )
	EVENT( "VCF::TableModelEventHandler", DefaultTableModel, VCF::TableModelEvent, TableCellAdded )
	EVENT( "VCF::TableModelEventHandler", DefaultTableModel, VCF::TableModelEvent, TableCellDeleted )
	EVENT( "VCF::TableModelEventHandler", DefaultTableModel, VCF::TableModelEvent, TableRowsAdded )
	EVENT( "VCF::TableModelEventHandler", DefaultTableModel, VCF::TableModelEvent, TableRowsDeleted )
	EVENT( "VCF::TableModelEventHandler", DefaultTableModel, VCF::TableModelEvent, TableColumnsAdded )
	EVENT( "VCF::TableModelEventHandler", DefaultTableModel, VCF::TableModelEvent, TableColumnsDeleted )
END_CLASSINFO(DefaultTableModel)


BEGIN_CLASSINFO(DefaultTextModel, "VCF::DefaultTextModel", "VCF::AbstractModel", DEFAULTTEXTMODEL_CLASSID)
	EVENT("VCF::TextModelEventHandler", DefaultTextModel, VCF::TextEvent, TextModelChanged )
END_CLASSINFO(DefaultTextModel)


BEGIN_CLASSINFO(DefaultTreeItem, "VCF::DefaultTreeItem", "VCF::TreeItem", DEFAULTTREEITEM_CLASSID)
	EVENT("VCF::ItemEventHandler", DefaultTreeItem, VCF::ItemEvent, ItemPaint );
	EVENT("VCF::ItemEventHandler", DefaultTreeItem, VCF::ItemEvent, ItemChanged );
	EVENT("VCF::ItemEventHandler", DefaultTreeItem, VCF::ItemEvent, ItemSelected );
	EVENT("VCF::ItemEventHandler", DefaultTreeItem, VCF::ItemEvent, ItemAdded );
	EVENT("VCF::ItemEventHandler", DefaultTreeItem, VCF::ItemEvent, ItemDeleted );
END_CLASSINFO(DefaultTreeItem)


BEGIN_CLASSINFO(DefaultTreeModel, "VCF::DefaultTreeModel", "VCF::AbstractModel", DEFAULTTREEMODEL_CLASSID)
	EVENT( "VCF::TreeModelEventHandler", DefaultTreeModel, VCF::TreeModelEvent, RootNodeChanged )
	EVENT( "VCF::TreeModelEventHandler", DefaultTreeModel, VCF::TreeModelEvent, NodeAdded )
	EVENT( "VCF::TreeModelEventHandler", DefaultTreeModel, VCF::TreeModelEvent, NodeDeleted )
END_CLASSINFO(DefaultTreeModel)


BEGIN_CLASSINFO(Dialog, "VCF::Dialog", "VCF::Frame", DIALOG_CLASSID )
END_CLASSINFO(Dialog)


BEGIN_CLASSINFO(HTMLBrowserControl, "VCF::HTMLBrowserControl", "VCF::Control", HTMLBROWSERCONTROL_CLASSID)
END_CLASSINFO(HTMLBrowserControl)

BEGIN_CLASSINFO(HeaderControl, "VCF::HeaderControl", "VCF::CustomControl", HEADERCONTROL_CLASSID)
	OBJECT_PROPERTY( ColumnModel, "columnModel", HeaderControl::getColumnModel, HeaderControl::setColumnModel );
	EVENT("VCF::MouseEventHandler", HeaderControl, VCF::MouseEvent, ColumnItemClicked );
	EVENT("VCF::ItemEventHandler", HeaderControl, VCF::ItemEvent, ColumnWidthChanged );
END_CLASSINFO(HeaderControl)


BEGIN_CLASSINFO(ImageFilenameString, "VCF::ImageFilenameString", "VCF::Object", IMAGEFILENAMESTRING_CLASSID);
END_CLASSINFO( ImageFilenameString );


BEGIN_CLASSINFO(ImageControl, "VCF::ImageControl", "VCF::CustomControl", IMAGECONTROL_CLASSID)
OBJECT_PROPERTY( Image, "image", ImageControl::getImage, ImageControl::setImage );
PROPERTY(bool, "transparent", ImageControl::getTransparent, ImageControl::setTransparent, pdBool);
OBJECT_PROPERTY_REF(ImageFilenameString, "filename", ImageControl::getFilename, ImageControl::setFilename);
END_CLASSINFO(ImageControl)



BEGIN_CLASSINFO(Label, "VCF::Label", "VCF::CustomControl", LABEL_CLASSID )
PROPERTY( String, "caption", Label::getCaption, Label::setCaption, pdString );
LABELED_ENUM_PROPERTY( TextAlignmentType, "textAlignment", Label::getTextAlignment, Label::setTextAlignment,
					   taTextLeft, taTextRight, 3, TextAlignmentTypeNames);
LABELED_ENUM_PROPERTY( TextVerticalAlignment, "verticalAlignment", Label::getVerticalAlignment, Label::setVerticalAlignment,
					   tvaTextTop, tvaTextBottom, 3, TextVerticalAlignmentNames);

OBJECT_PROPERTY( Control, "focusControl", Label::getFocusControl, Label::setFocusControl );

PROPERTY( bool, "wordWrap", Label::getWordWrap, Label::setWordWrap, pdBool );

END_CLASSINFO(Label)



BEGIN_CLASSINFO(ListBoxControl, "VCF::ListBoxControl", "VCF::CustomControl", LISTBOXCONTROL_CLASSID )
PROPERTY( double, "defaultItemHeight", ListBoxControl::getDefaultItemHeight, ListBoxControl::setDefaultItemHeight, pdDouble );
PROPERTY( bool, "allowsMultiSelect", ListBoxControl::getAllowsMultiSelect, ListBoxControl::setAllowsMultiSelect, pdBool );
OBJECT_PROPERTY( ListModel, "listModel", ListBoxControl::getListModel, ListBoxControl::setListModel );
END_CLASSINFO(ListBoxControl)



BEGIN_CLASSINFO(ListViewControl, "VCF::ListViewControl", "VCF::Control", LISTVIEWCONTROL_CLASSID )
LABELED_ENUM_PROPERTY( IconStyleType, "iconStyle", ListViewControl::getIconStyle, ListViewControl::setIconStyle,
					   isLargeIcon, isDetails, 4, IconStyleTypeNames);
LABELED_ENUM_PROPERTY( IconAlignType, "iconAlignment", ListViewControl::getIconAlignment, ListViewControl::setIconAlignment,
					   iaNone, iaAutoArrange, 4, IconAlignTypeNames);
OBJECT_PROPERTY( ListModel, "listModel", ListViewControl::getListModel, ListViewControl::setListModel );

EVENT("VCF::ItemEventHandler", ListViewControl, VCF::ItemEvent, ItemSelectionChanged );
EVENT("VCF::MouseEventHandler", ListViewControl, VCF::MouseEvent, ColumnItemClicked );

END_CLASSINFO(ListViewControl)


BEGIN_CLASSINFO(Menu, "VCF::Menu", "VCF::Component", MENU_CLASSID )
OBJECT_PROPERTY( MenuItem, "rootMenuItem", Menu::getRootMenuItem, Menu::setRootMenuItem );
END_CLASSINFO(Menu)




BEGIN_CLASSINFO(MenuBar, "VCF::MenuBar", "VCF::Menu", MENUBAR_CLASSID )
END_CLASSINFO(MenuBar)


BEGIN_CLASSINFO( MessageDialog, "VCF::MessageDialog", "VCF::Dialog", MESSAGEDIALOG_CLASSID )
END_CLASSINFO( MessageDialog )


BEGIN_CLASSINFO(MultilineTextControl, "VCF::MultilineTextControl", "VCF::TextControl", MULTILINETEXTCONTROL_CLASSID)
END_CLASSINFO(MultilineTextControl)

/*
BEGIN_CLASSINFO(OpenGLControl, "VCF::OpenGLControl", "VCF::CustomControl", OPENGLCONTROL_CLASSID )
END_CLASSINFO(OpenGLControl)
*/

BEGIN_CLASSINFO(Panel, "VCF::Panel", "VCF::ControlContainer", PANEL_CLASSID )
END_CLASSINFO(Panel)


BEGIN_CLASSINFO(PopupMenu, "VCF::PopupMenu", "VCF::Menu", POPUPMENU_CLASSID )
END_CLASSINFO(PopupMenu)


BEGIN_CLASSINFO(PushButton, "PushButton", "VCF::Object", PUSHBUTTON_CLASSID)
END_CLASSINFO(PushButton)


BEGIN_CLASSINFO(RadioButtonControl, "VCF::RadioButtonControl", "VCF::ToggledButton", RADIOBUTTONCONTROL_CLASSID )
PROPERTY( long, "groupID", RadioButtonControl::getGroupID, RadioButtonControl::setGroupID, pdLong );
END_CLASSINFO(RadioButtonControl)



BEGIN_CLASSINFO(ScrollbarManager, "VCF::ScrollbarManager", "VCF::Component", SCROLLBARMANAGER_CLASSID)
OBJECT_PROPERTY( Control, "target", ScrollbarManager::getTarget, ScrollbarManager::setTarget );
PROPERTY( double, "virtualViewHeight", ScrollbarManager::getVirtualViewHeight, ScrollbarManager::setVirtualViewHeight, pdDouble );
PROPERTY( double, "virtualViewWidth", ScrollbarManager::getVirtualViewWidth, ScrollbarManager::setVirtualViewWidth, pdDouble );
PROPERTY( double, "verticalPosition", ScrollbarManager::getVerticalPosition, ScrollbarManager::setVerticalPosition, pdDouble );
PROPERTY( double, "horizontalPosition", ScrollbarManager::getHorizontalPosition, ScrollbarManager::setHorizontalPosition, pdDouble );
PROPERTY( double, "verticalTopScrollSpace", ScrollbarManager::getVerticalTopScrollSpace, ScrollbarManager::setVerticalTopScrollSpace, pdDouble );
PROPERTY( double, "verticalBottomScrollSpace", ScrollbarManager::getVerticalBottomScrollSpace, ScrollbarManager::setVerticalBottomScrollSpace, pdDouble );
PROPERTY( double, "horizontalLeftScrollSpace", ScrollbarManager::getHorizontalLeftScrollSpace, ScrollbarManager::setHorizontalLeftScrollSpace, pdDouble );
PROPERTY( double, "horizontalRightScrollSpace", ScrollbarManager::getHorizontalRightScrollSpace, ScrollbarManager::setHorizontalRightScrollSpace, pdDouble );
PROPERTY( bool, "hasVerticalScrollbar", ScrollbarManager::hasVerticalScrollBar, ScrollbarManager::setHasVerticalScrollbar, pdBool );
PROPERTY( bool, "hasHorizontalScrollbar", ScrollbarManager::hasHorizontalScrollBar, ScrollbarManager::setHasHorizontalScrollbar, pdBool );
END_CLASSINFO(ScrollbarManager)



BEGIN_CLASSINFO(Splitter, "VCF::Splitter", "VCF::CustomControl", SPLITTER_CLASSID)
//PROPERTY(bool,"updateAttachedControl",Splitter::getUpdateAttachedControl, Splitter::setUpdateAttachedControl,pdBool)
END_CLASSINFO(Splitter)


BEGIN_CLASSINFO(StatusBar, "VCF::StatusBar", "VCF::ControlContainer", STATUSBAR_CLASSID)
END_CLASSINFO(StatusBar)


BEGIN_CLASSINFO(TabbedPages, "VCF::TabbedPages", "VCF::CustomControl", TABBEDPAGES_CLASSID );
END_CLASSINFO(TabbedPages);



BEGIN_CLASSINFO(TableControl, "VCF::TableControl", "VCF::CustomControl", TABLECONTROL_CLASSID );
END_CLASSINFO(TableControl);



BEGIN_CLASSINFO(TextControl, "VCF::TextControl", "VCF::Control", TEXTCONTROL_CLASSID )
END_CLASSINFO(TextControl)


BEGIN_CLASSINFO(TimerComponent, "VCF::TimerComponent", "VCF::Component", TIMERCOMPONENT_CLASSID)
PROPERTY( bool, "active", TimerComponent::isActive, TimerComponent::setActivated, pdBool );
PROPERTY( long, "timeoutInterval", TimerComponent::getTimeoutInterval, TimerComponent::setTimeoutInterval, pdLong );
EVENT("VCF::TimerEventHandler", TimerComponent, VCF::TimerEvent, TimerActivated );
EVENT("VCF::TimerEventHandler", TimerComponent, VCF::TimerEvent, TimerDeactivated );
EVENT("VCF::TimerEventHandler", TimerComponent, VCF::TimerEvent, TimerPulse );
END_CLASSINFO(TimerComponent)


BEGIN_CLASSINFO(Toolbar, "VCF::Toolbar", "VCF::Control", TOOLBAR_CLASSID);
END_CLASSINFO(Toolbar);



BEGIN_CLASSINFO(ToolbarDock, "VCF::ToolbarDock", "VCF::CustomControl", TOOLBARDOCK_CLASSID);
LABELED_ENUM_PROPERTY( ToolbarDockSide, "dockSide", ToolbarDock::getDockSide, ToolbarDock::setDockSide,
					   tdsTop, tdsBottom, 4, ToolbarDockSideNames);

LABELED_ENUM_PROPERTY( ToolbarBackgroundStyle, "backgroundStyle", ToolbarDock::getBackgroundStyle, ToolbarDock::setBackgroundStyle,
					   tbksNone, tbksStretch, 3, ToolbarBackgroundStyleNames);

OBJECT_PROPERTY( Image, "background", ToolbarDock::getBackground, ToolbarDock::setBackground );

PROPERTY( bool, "usingBackground", ToolbarDock::isUsingBackground, ToolbarDock::setUsingBackground, pdBool );
PROPERTY( bool, "allowsDragging", ToolbarDock::allowsDragging, ToolbarDock::setAllowsDragging, pdBool );

END_CLASSINFO(ToolbarDock);



BEGIN_CLASSINFO(TreeControl, "VCF::TreeControl", "VCF::Control", TREECONTROL_CLASSID )
OBJECT_PROPERTY( TreeModel, "treeModel", TreeControl::getTreeModel, TreeControl::setTreeModel );
EVENT("VCF::ItemEventHandler", TreeControl, VCF::ItemEvent, ItemSelected );
EVENT("VCF::ItemEventHandler", TreeControl, VCF::ItemEvent, ItemExpanded );
EVENT("VCF::ItemEventHandler", TreeControl, VCF::ItemEvent, ItemStateChangeRequested );
END_CLASSINFO(TreeControl)



BEGIN_CLASSINFO(TreeListControl, "VCF::TreeListControl", "VCF::CustomControl", TREELISTCONTROL_CLASSID )
OBJECT_PROPERTY( TreeModel, "treeModel", TreeListControl::getTreeModel, TreeListControl::setTreeModel );
EVENT("VCF::ItemEventHandler", TreeListControl, VCF::ItemEvent, ItemSelected );
EVENT("VCF::ItemEventHandler", TreeListControl, VCF::ItemEvent, ItemExpanded );
EVENT("VCF::ItemEventHandler", TreeListControl, VCF::ItemEvent, ItemStateChangeRequested );
END_CLASSINFO(TreeListControl)

/*
BEGIN_CLASSINFO(UIApplication, "UIApplication", "Application", UIAPPLICATION_CLASSID)
END_CLASSINFO(UIApplication)
*/


BEGIN_CLASSINFO(Window, "VCF::Window", "VCF::Frame", WINDOW_CLASSID )
OBJECT_PROPERTY( MenuBar, "menuBar", Window::getMenuBar, Window::setMenuBar );
EVENT("VCF::WindowEventHandler", Window, VCF::WindowEvent, WindowRestore )
EVENT("VCF::WindowEventHandler", Window, VCF::WindowEvent, WindowMaximize )
EVENT("VCF::WindowEventHandler", Window, VCF::WindowEvent, WindowMinimize )
END_CLASSINFO(Window)



BEGIN_CLASSINFO(ProgressControl, "VCF::ProgressControl", "VCF::CustomControl", PROGRESSCONTROL_CLASSID )
END_CLASSINFO(ProgressControl)


BEGIN_CLASSINFO(SliderControl, "VCF::SliderControl", "VCF::CustomControl", SLIDERCONTROL_CLASSID )
END_CLASSINFO(SliderControl)


BEGIN_CLASSINFO(SystemTray, "VCF::SystemTray", "VCF::Component", SYSTEMTRAY_CLASSID )
	EVENT("VCF::GenericEventHandler", SystemTray, VCF::Event, TrayIconChanged )
	OBJECT_PROPERTY( PopupMenu, "popupMenu", SystemTray::getPopupMenu, Control::setPopupMenu );
	PROPERTY( String, "tooltipText", SystemTray::getTooltipText, SystemTray::setTooltipText, pdString );
END_CLASSINFO(SystemTray)





};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.5  2004/10/10 23:48:21  ddiego
*fixed duplicate delegate in DefaultTableModel class.
*
*Revision 1.2.2.4  2004/10/04 13:47:49  ddiego
*applicationkit rtti code fixed. Thanks to darko
*for finding the bug on bcb5.5
*
*Revision 1.2.2.3  2004/10/03 22:25:59  ddiego
*fixed a bug in the ApplicationKitRTTI inl file that had some
*leftover code from changing the various model class around.
*
*Revision 1.2.2.2  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.1  2004/08/20 03:08:13  ddiego
*added SystemTray component
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.5  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.4  2004/01/20 01:54:54  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.2.2.2  2004/01/18 04:52:33  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.2.2.1  2004/01/15 05:35:03  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.2.2.4  2004/01/30 05:08:14  ddiego
*added more rearrangements for the table control
*
*Revision 1.2.2.3  2004/01/29 22:26:47  ddiego
*table fixes, this still needs some more work
*
*Revision 1.2.2.2  2004/01/18 04:52:33  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.2.2.1  2004/01/15 05:35:03  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.2  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.7  2003/12/02 05:50:04  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.1.2.6  2003/10/30 04:23:10  ddiego
*added a toolbar peer so that we have native toolbars (instead of trying
*to implement a half-assed version from scratch)
*
*Revision 1.1.2.5  2003/10/28 20:23:01  ddiego
*minor header changes
*
*Revision 1.1.2.4  2003/10/25 04:30:20  ddiego
*added two more examples one for progress bars and one for slider controls.
*also added two more control classes to the ApplicationKit, a SliderControl
*and a ProgressControl.
*
*Revision 1.1.2.3  2003/09/22 01:48:03  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.1.2.2  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.1.2.1  2003/09/12 02:17:11  ddiego
*added missing file
*
*/


