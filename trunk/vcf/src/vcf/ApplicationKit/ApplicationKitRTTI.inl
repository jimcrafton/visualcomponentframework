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
#include "vcf/ApplicationKit/ColumnLayoutContainer.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"
#include "vcf/ApplicationKit/SimpleListModel.h"
#include "vcf/ApplicationKit/TreeListModel.h"
#include "vcf/ApplicationKit/AdapterModels.h"

namespace VCF {

/**
*A string array for the controls alignement types
*/
static String AlignmentTypeNames[] = { "AlignNone",
                                         "AlignTop",
										 "AlignLeft",
										 "AlignRight",
										 "AlignBottom",
										 "AlignClient" };
										 
										 

/**
*an array of Anchor type names
*/
static String AnchorTypeNames[] = { "AnchorNone",
                                         "AnchorTop",
										 "AnchorLeft",
										 "AnchorBottom",
										 "AnchorRight" };
										 
										 
										 

static uint32 AnchorTypeValues[] = { AnchorNone,
                                         AnchorTop,
										 AnchorLeft,
										 AnchorBottom,
										 AnchorRight };	



static String TextAlignmentTypeNames[] = { "taTextLeft",
                                         "taTextCenter",
										 "taTextRight" };
										 

static uint32 KeyboardMaskValues[] = { kmUndefined, kmAlt, kmShift,kmCtrl };
static String KeyboardMaskNames[] = { "kmUndefined", "kmAlt", "kmShift","kmCtrl" };

/**
*an array of Anchor type names
*/
static String TreeDisplayOptionsNames[] = { "tdoNone",
                                         "tdoShowHierarchyLines",
										 "tdoShowRowLines",
										 "tdoShowColumnLines",
										 "tdoShowFullRowSelection",
										 "tdoShowColumnHeader" };
										 
										 
										 

static uint32 TreeDisplayOptionsValues[] = { tdoNone,
                                         tdoShowHierarchyLines,
										 tdoShowRowLines,
										 tdoShowColumnLines,
										 tdoShowFullRowSelection,
										 tdoShowColumnHeader };	





static String ItemDisplayStateNames[] = { "idsNone",
                                         "idsChecked",
										 "idsUnChecked",
										 "idsRadioUnpressed",
										 "idsRadioPressed" };
										 
										 
										 

static uint32 ItemDisplayStateValues[] = { idsNone,
                                         idsChecked,
										 idsUnChecked,
										 idsRadioUnpressed,
										 idsRadioPressed };	


//enum VirtualKeyCode{
static String VirtualKeyCodeNames[] = {	
	"vkF1",
	"vkF2",
	"vkF3",
	"vkF4",
	"vkF5",
	"vkF6",
	"vkF7",
	"vkF8",
	"vkF9",
	"vkF10",
	"vkF11",
	"vkF12",
	"vkUpArrow",
	"vkDownArrow",
	"vkLeftArrow",
	"vkRightArrow",
	"vkPgUp",
	"vkPgDown",
	"vkHome",
	"vkEnd",
	"vkInsert",
	"vkDelete",
	"vkBackSpace",
	"vkNumber0",
	"vkNumber1",
	"vkNumber2",
	"vkNumber3",
	"vkNumber4",
	"vkNumber5",
	"vkNumber6",
	"vkNumber7",
	"vkNumber8",
	"vkNumber9",
	"vkLetterA",
	"vkLetterB",
	"vkLetterC",
	"vkLetterD",
	"vkLetterE",
	"vkLetterF",
	"vkLetterG",
	"vkLetterH",
	"vkLetterI",
	"vkLetterJ",
	"vkLetterK",
	"vkLetterL",
	"vkLetterM",
	"vkLetterN",
	"vkLetterO",
	"vkLetterP",
	"vkLetterQ",
	"vkLetterR",
	"vkLetterS",
	"vkLetterT",
	"vkLetterU",
	"vkLetterV",
	"vkLetterW",
	"vkLetterX",
	"vkLetterY",
	"vkLetterZ",
	"vkSpaceBar",
	"vkReturn",
	"vkAlt",
	"vkShift",
	"vkCtrl",
	"vkTab",
	"vkEscape",
	"vkLeftApostrophe",			//`
	"vkTilde",					//~
	"vkExclamation",				//!
	"vkCommercialAt",				//@
	"vkNumberSign",				//#
	"vkDollarSign",				//$
	"vkPercent",					//%
	"vkCircumflex",				//^
	"vkAmpersand",				//&
	"vkAsterix",					//*
	"vkOpenParen",				//(
	"vkCloseParen",				//)
	"vkHyphen",					//-
	"vkUnderbar",					//_
	"vkEqualsSign",				//=
	"vkPlusSign",					//+
	"vkUprightBar",				//|
	"vkBackSlash",				/* \   */
	"vkOpenBracket",				//[
	"vkOpenBrace",				//{
	"vkCloseBracket",				//]
	"vkCloseBrace",				//}
	"vkSemiColon",
	"vkColon",
	"vkSingleQuote",
	"vkDoubleQuote",
	"vkComma",
	"vkLessThan",
	"vkPeriod",
	"vkGreaterThan",
	"vkForwardSlash",
	"vkQuestionMark",
	"vkPrintScreen",
	"vkScrollLock",
	"vkPause",
	"vkCapsLock",
	"vkMinusSign",
	"vkDivideSign",
	"vkMultiplySign",
	"vkEnter"
};




_class_abstract_rtti_(UIComponent, "VCF::Component", UICOMPONENT_CLASSID)
_class_rtti_end_

_class_rtti_(Action, "VCF::Component", ACTION_CLASSID)
_property_obj_dictionary_(UIComponent,uint32,"targets",getTarget,setTarget,getTargetIndexes,"")
_property_object_( AcceleratorKey, "accelerator", getAccelerator, setAcceleratorKey, "" );
_delegate_( ActionDelegate, Update )
_delegate_( ActionDelegate, Performed )
_class_rtti_end_


_class_rtti_(AcceleratorKey, "VCF::Component", ACCELERATORKEY_CLASSID)
_property_object_( Control, "control", getAssociatedControl, setAssociatedControl, "" );
_property_object_( MenuItem, "menuItem", getAssociatedMenuItem, setAssociatedMenuItem, "" );
_property_object_( Object, "object", getAssociatedObject, setAssociatedObject, "" );
_property_enumset_( VCF::KeyboardMasks, "modifiers", getModifierMask, setModifierMask, 4, KeyboardMaskValues, KeyboardMaskNames, ""  );
_property_enum_labeled_( uint32, "keyCode", getKeyCode, setKeyCode,
					   vkF1, vkCapsLock, 101, VirtualKeyCodeNames, "");
_property_( bool, "enabled", isEnabled, setEnabled, "" );
_class_rtti_end_



_class_rtti_(ImageList, "VCF::Component", IMAGELIST_CLASSID )
_property_object_( Color, "transparentColor", getTransparentColor, setTransparentColor, "" );
_property_( uint32, "imageWidth", getImageWidth, setImageWidth, "" );
_property_( uint32, "imageHeight", getImageHeight, setImageHeight, "" );
_delegate_(ImageListDelegate, SizeChanged );
_delegate_(ImageListDelegate, ImageAdded );
_delegate_(ImageListDelegate, ImageDeleted );
_class_rtti_end_


_class_abstract_rtti_(Border, "VCF::Component", BORDER_CLASSID)
_class_rtti_end_

_class_rtti_(Basic3DBorder, "VCF::Border", BASIC3DBORDER_CLASSID)
_property_( bool, "inverted", isInverted, setInverted, "" );
_class_rtti_end_


_class_rtti_(EtchedBorder, "VCF::Border", ETCHEDBORDER_CLASSID)
_property_( int32, "sidesToPaint", getSidesToPaint, setSidesToPaint, "" );
_property_( int32, "edgeStyle", getEdgeStyle, setEdgeStyle, "" );
_class_rtti_end_



_class_rtti_(ColorEtchedBorder, "VCF::EtchedBorder", COLORETCHEDBORDER_CLASSID)
_property_object_( Color, "highlight", getHighlight, setHighlight, "" );
_property_object_( Color, "shadow", getShadow, setShadow, "" );
_class_rtti_end_


_class_rtti_(Light3DBorder, "VCF::Border", LIGHT3DBORDER_CLASSID)
_property_( bool, "inverted", isInverted, setInverted, "" );
_class_rtti_end_

_class_rtti_(TitledBorder, "VCF::Border", TITLEDBORDER_CLASSID)
_property_( int32, "sidesToPaint", getSidesToPaint, setSidesToPaint, "" );
_property_object_( Font, "font", getFont, setFont, "" );
_property_( String, "caption", getCaption, setCaption, "" );
_class_rtti_end_


_class_abstract_rtti_(Container, "VCF::Component", CONTAINER_CLASSID)
_class_rtti_end_

_class_abstract_rtti_(AbstractContainer, "VCF::Container", ABSTRACTCONTAINER_CLASSID)
_class_rtti_end_

_class_rtti_(StandardContainer, "VCF::AbstractContainer", STANDARDCONTAINER_CLASSID)
_property_( double, "bottomBorderHeight", getBottomBorderHeight, setBottomBorderHeight, "" );
_property_( double, "topBorderHeight", getTopBorderHeight, setTopBorderHeight, "" );
_property_( double, "rightBorderWidth", getRightBorderWidth, setRightBorderWidth, "" );
_property_( double, "leftBorderWidth", getLeftBorderWidth, setLeftBorderWidth, "" );
_class_rtti_end_



_class_rtti_(FlowLayoutContainter, "VCF::StandardContainer", "FlowLayoutContainter")
_property_( double, "childSpacer", getChildSpacer, setChildSpacer, "" );
_property_( bool, "allowContentsToWrap", allowContentsToWrap, setAllowContentsToWrap, "" );
_property_enum_labeled_( FlowDirection, "direction", getFlowDirection, setFlowDirection,
					   fdVertical, fdHorizontal, 2, FlowDirectionNames, "");
_class_rtti_end_




_class_rtti_(ColumnLayoutContainer, "VCF::StandardContainer", COLUMNLAYOUTCONTAINER_CLASSID)
_property_array_( int, "columnWidths", getColumnWidth,setColumnWidth,insertColumnWidth,removeColumnWidth,getColumnCount, "" )
_class_rtti_end_

_class_rtti_(HorizontalLayoutContainer, "VCF::StandardContainer", HORIZONTALLAYOUTCONTAINER_CLASSID)
_property_( int32, "numberOfColumns", getNumberOfColumns, setNumberOfColumns, "" );
_property_( double, "maxRowHeight", getMaxRowHeight, setMaxRowHeight, "" );
_property_( double, "rowSpacerHeight", getRowSpacerHeight, setRowSpacerHeight, "" );
_property_( bool, "maximizeLastRow", getMaximizeLastRow, setMaximizeLastRow, "" );
_property_( bool, "equalizeHeights", getEqualizeHeights, setEqualizeHeights, "" );
_property_( bool, "averageHeights", getAverageHeights, setAverageHeights, "" );
_property_( bool, "keepControlsWidth", getKeepControlsWidth, setKeepControlsWidth, "" );
_property_array_( double, "widths", getColumnWidth,setColumnWidth,insertColumnWidth,removeColumnWidth,getNumberOfColumns, "" )
_property_array_( double, "tweenWidths", getColumnTweenWidth,setColumnTweenWidth,insertColumnTweenWidth,removeColumnTweenWidth,getColumnTweenCount, "" )
_class_rtti_end_


_class_abstract_rtti_(Model, "VCF::Component", MODEL_CLASSID)
_delegate_( ModelDelegate, ModelChanged )
_delegate_( ValidationDelegate, ModelValidating )
_delegate_( EventDelegate, ModelValidated )

_property_enum_labeled_( ModelUpdate, "updateMode", getUpdateMode, setUpdateMode,
						   muNone, muOnValidation, 2, ModelUpdateNames, "");

_property_object_( ValidationFormatter, "formatter", getFormatter, setFormatter, "" )
_property_object_( ValidationRuleCollection, "validator", getValidator, setValidator, "" )

_class_rtti_end_


_class_abstract_rtti_(ValidationFormatter, "VCF::Component", "ValidationFormatter")
	_property_( VariantData, "appliesToKey", getAppliesToKey, setAppliesToKey, "" );
_class_rtti_end_


_class_rtti_(NumericFormatter, "VCF::ValidationFormatter", "NumericFormatter")
	_property_( uint32, "decimalPlaces", getNumberOfDecimalPlaces, setNumberOfDecimalPlaces, "" );
_class_rtti_end_





_class_abstract_rtti_(ValidationRule, "VCF::Component", "ValidationRule")
	_property_enum_labeled_( ValidationLogicOp, "logicOp", getLogicOp, setLogicOp,
						   vlNone, vlOR, 3, ValidationLogicOpNames, "");
	_property_( String, "errorMessage", getErrorMessage, setErrorMessage, "" );
	_property_( VariantData, "appliesToKey", getAppliesToKey, setAppliesToKey, "" );
_class_rtti_end_

_class_rtti_(NullRule, "VCF::ValidationRule", "NullRule")
	_property_( bool, "allowsNull", allowsNull, setAllowsNull, "" );
_class_rtti_end_


_class_abstract_rtti_(DataRule, "VCF::ValidationRule", "DataRule")
	_property_( VariantData, "data", getData, setData, "" );
_class_rtti_end_


_class_rtti_(MinRule, "VCF::DataRule", "MinRule")
_class_rtti_end_

_class_rtti_(MaxRule, "VCF::DataRule", "MaxRule")
_class_rtti_end_

_class_rtti_(EqualsRule, "VCF::DataRule", "EqualsRule")
_class_rtti_end_

_class_rtti_(SimilarToRule, "VCF::DataRule", "SimilarToRule")
_class_rtti_end_


_class_rtti_(ValidationRuleCollection, "VCF::ValidationRule", "ValidationRuleCollection")
	_property_obj_array_(ValidationRule,"rules",getRule,setRule,insertRule,removeRule,getRuleCount,"")
_class_rtti_end_




_class_rtti_(ColumnItem, "VCF::Item", COLUMNITEM_CLASSID)
_property_( String, "caption", getCaption, setCaption, "" );
_property_( double, "width", getWidth, setWidth, "" );
_property_enum_labeled_( TextAlignmentType, "captionAlignment", getCaptionAlignment, setCaptionAlignment,
					   taTextLeft, taTextRight, 3, TextAlignmentTypeNames, "");

_class_rtti_end_





_class_abstract_rtti_(Control,  "VCF::UIComponent", CONTROL_CLASSID);
_property_( double, "left", getLeft, setLeft, "" );
_property_( double, "top", getTop, setTop, "" );
_property_( double, "right", getRight, setRight, "" );
_property_( double, "bottom", getBottom, setBottom, "" );
_property_( bool, "visible", getVisible, setVisible, "" );
_property_( double, "width", getWidth, setWidth, "" );
_property_( double, "height", getHeight, setHeight, "" );
_property_( bool, "enabled", isEnabled, setEnabled, "" );
_property_( bool, "doubleBuffered", isDoubleBuffered, setDoubleBuffered, "" );
_property_( bool, "useParentFont", useParentFont, setUseParentFont, "" );
_property_( bool, "autoStartDragDrop", getAutoStartDragDrop, setAutoStartDragDrop, "" );
_property_( bool, "tabStop", getTabStop, setTabStop, "" );
_property_( bool, "keepsTabKey",keepsTabKey, setKeepsTabKey, "" );
_property_( bool, "keepsReturnCharacter",keepsReturnCharacter, setKeepsReturnChar, "" );
_property_( bool, "keepsArrowKeys",keepsArrowKeys, setKeepsArrowKeys, "" );
_property_( int32, "tabOrder", getTabOrder, setTabOrder, "" );
_property_( String, "whatsThisHelpString", getWhatsThisHelpString, setWhatsThisHelpString, "" );
_property_( String, "toolTipText", getToolTipText, setToolTipText, "" );
_property_( VariantData, "modelKey", getModelKey, setModelKey, "" );

_property_( double, "minHeight", getMinHeight, setMinHeight, "" );
_property_( double, "minWidth", getMinWidth, setMinWidth, "" );

_property_( double, "maxHeight", getMaxHeight, setMaxHeight, "" );
_property_( double, "maxWidth", getMaxWidth, setMaxWidth, "" );

_property_( double, "bottom", getBottom, setBottom, "" );
_property_( double, "bottom", getBottom, setBottom, "" );

_property_object_( Border, "border", getBorder, setBorder, "" );
_property_object_( Color, "color", getColor, setColor, "" );
_property_object_( Font, "font", getFont, setFont, "" );
_property_object_( PopupMenu, "popupMenu", getPopupMenu, setPopupMenu, "" );
_property_object_( Container, "container", getContainer, setContainer, "" );
_property_object_( Model, "model", getModel, setModel, "" );

_property_enum_labeled_( AlignmentType, "alignment", getAlignment, setAlignment,
					   AlignNone, AlignClient, 6, AlignmentTypeNames, "");

_property_enumset_( VCF::AnchorTypes, "anchor", getAnchor, setAnchor, 5, AnchorTypeValues, AnchorTypeNames, ""  );

_property_typedef_( int32, "cursor", getCursorID, setCursorID, "VCF::Cursor::SystemCursorType", "" )

_property_obj_dictionary_(AcceleratorKey,uint32,"accelerators",getAcceleratorKey,setAcceleratorKey,getAcceleratorKeyIndexes,"")

_delegate_(EventDelegate, ControlSized );
_delegate_(ControlDelegate, ControlPositioned );
_delegate_(ControlDelegate, ControlParentChanged );
_delegate_(MouseDelegate, MouseDoubleClicked );
_delegate_(MouseDelegate, MouseClicked );
_delegate_(MouseDelegate, MouseMove );
_delegate_(MouseDelegate, MouseUp );
_delegate_(MouseDelegate, MouseDown );
_delegate_(MouseDelegate, MouseEnter );
_delegate_(MouseDelegate, MouseLeave );
_delegate_(KeyboardDelegate, KeyPressed  );
_delegate_(KeyboardDelegate, KeyDown  );
_delegate_(KeyboardDelegate, KeyUp  );
_delegate_(WhatsThisHelpDelegate, ControlHelpRequested );
_delegate_(HelpDelegate, HelpRequested );
_delegate_(FocusDelegate, FocusLost  );
_delegate_(FocusDelegate, FocusGained );

_delegate_(ToolTipDelegate, ToolTipRequested  );
_delegate_(ToolTipDelegate, ToolTip  );


_procedure4_(setBounds,const double&,const double&,const double&,const double&,"");
_class_rtti_end_


_class_rtti_(DropTarget, "VCF::Component", "DropTarget")
	_delegate_(DropTargetDelegate, DropTargetDraggingOver)
	_delegate_(DropTargetDelegate, DropTargetDropped)
	_delegate_(DropTargetDelegate, DropTargetLeft)
	_delegate_(DropTargetDelegate, DropTargetEntered)
	_property_obj_array_(Control,"targets",getTargetControl,setTargetControl,insertTargetControl,removeTargetControl,getTargetControlCount,"")
_class_rtti_end_



_class_abstract_rtti_(Document, "VCF::Model", DOCUMENT_CLASSID)
_class_rtti_end_




_class_abstract_rtti_(Frame, "VCF::Control", FRAME_CLASSID )
_property_( String, "caption", getCaption, setCaption, "" );
_property_( bool, "isTopmost", isFrameTopmost, setFrameTopmost, "" );
_property_( bool, "useColorForBackground", getUseColorForBackground, setUseColorForBackground, "" );
_property_enum_labeled_( FrameStyleType, "frameStyle", getFrameStyle, setFrameStyle,
					   fstSizeable, fstToolbarBorderFixed, 6, FrameStyleTypeNames, "");

_delegate_(FrameDelegate, FrameClosing)
_delegate_(FrameDelegate, FrameClose )
_delegate_(WindowDelegate, FrameActivation )

_procedure_(show)
_procedure_(hide)
_procedure_(close)
_class_rtti_end_




_class_abstract_rtti_(Item, "VCF::UIComponent", ITEM_CLASSID)
_property_( int32, "stateImageIndex", getStateImageIndex, setStateImageIndex, "" )
_property_( int32, "imageIndex", getImageIndex, setImageIndex, "" )
_property_( bool, "selected", isSelected, setSelected, "" )
_property_object_( Font, "font", getFont, setFont, "" )
_property_enumset_( uint32, "displayState", getDisplayState, setDisplayState, 5, ItemDisplayStateValues, ItemDisplayStateNames, ""  );
_class_rtti_end_




_class_rtti_(ToolbarItem, "VCF::Item", TOOLBARITEM_CLASSID)
_delegate_(ButtonDelegate, ItemClicked )
_delegate_(EventDelegate, ItemUpdate )
_property_( String, "caption", getCaption, setCaption, "" )
_property_( String, "tooltip", getTooltip, setTooltip, "" )
_property_( bool, "separator", isSeparator, setAsSeparator, "" )
_property_( bool, "pressed", isPressed, setPressed, "" )
_property_object_( Control, "itemControl", getItemControl, setItemControl, "" );
_property_( bool, "enabled", isEnabled, setEnabled, "" )
_property_( bool, "checked", isChecked, setChecked, "" )
_property_( bool, "grouped", isGrouped, setGrouped, "" )
_class_rtti_end_

_class_rtti_(ListItem, "VCF::Item", LISTITEM_CLASSID)
_property_( String, "caption", getCaption, setCaption, "" )
_class_rtti_end_

_class_rtti_(ListSubItem, "VCF::UIComponent", LISTSUBITEM_CLASSID)
_property_( String, "caption", getCaption, setCaption, "" )
_class_rtti_end_



_class_abstract_rtti_(ListModel, "VCF::Model", LISTMODEL_CLASSID)
	_delegate_(ListModelDelegate, ItemAdded )
	_delegate_(ListModelDelegate, ItemRemoved )
	_property_array_( String, "items", getAsString,setAsString,insert,remove,getCount, "" )
	_property_array_( VariantData, "objects", get,set,insert,remove,getCount, "" )
	_property_collection2_( VariantData, String, "subItems", getSubItemAtKey,setSubItemAtKey,insertSubItemAtKey,removeSubItemAtKey,getSubItemsCountAtKey, "" )
_class_rtti_end_

_class_rtti_(SimpleListModel, "VCF::ListModel", SIMPLELISTMODEL_CLASSID)	
_class_rtti_end_


_class_abstract_rtti_(MenuItem, "VCF::Item", MENUITEM_CLASSID)
_delegate_( MenuItemDelegate, MenuItemClicked )
_delegate_( MenuItemDelegate, MenuItemUpdate )
_property_( String, "caption", getCaption, setCaption, "" )
_property_( bool, "enabled", isEnabled, setEnabled, "" )
_property_( bool, "radioItem", getRadioItem, setRadioItem, "" )
_property_( bool, "checked", isChecked, setChecked, "" )
_property_( bool, "separator", isSeparator, setSeparator, "" )
_property_object_( AcceleratorKey, "accelerator", getAccelerator, setAcceleratorKey, "" );

_class_rtti_end_


_class_abstract_rtti_(TabPage, "VCF::Item", TABPAGE_CLASSID)
_class_rtti_end_


_class_abstract_rtti_(TableCellItem, "VCF::Item", TABLECELLITEM_CLASSID)
_class_rtti_end_

_class_abstract_rtti_(TableItemEditor, "VCF::Object", TABLEITEMEDITOR_CLASSID)
_delegate_(ItemEditorDelegate, CellItemChanged )
_delegate_(ItemEditorDelegate, CellItemValidateChange )
_class_rtti_end_



_class_abstract_rtti_(TableModel, "VCF::Model", TABLEMODEL_CLASSID )
_class_rtti_end_





_class_abstract_rtti_(ToggledButton, "VCF::CustomControl", TOGGLEDBUTTON_CLASSID)
_property_(bool, "checked", isChecked, setChecked, "");
_property_(String, "caption", getCaption, setCaption, "");
_delegate_( ButtonDelegate, ButtonClicked )
_class_rtti_end_



_class_rtti_(TreeItem, "VCF::Item", TREEITEM_CLASSID)
_property_( String, "caption", getCaption, setCaption, "" )
_class_rtti_end_

_class_rtti_(TreeSubItem, "VCF::UIComponent", TREESUBITEM_CLASSID)
_property_( String, "caption", getCaption, setCaption, "" )
_class_rtti_end_



_class_abstract_rtti_(TreeModel, "VCF::Model", TREEMODEL_CLASSID)
	_delegate_(TreeModelDelegate, NodeAdded )
	_delegate_(TreeModelDelegate, NodeRemoved )
_class_rtti_end_


_class_rtti_(DefaultTreeModel, "VCF::TreeModel", DEFAULTTREEMODEL_CLASSID)
	
_class_rtti_end_



_class_rtti_(TreeListModel, "VCF::DefaultTreeModel", TREELISTMODEL_CLASSID)
	
_class_rtti_end_



_class_rtti_(CheckBoxControl, "VCF::ToggledButton", CHECKBOXCONTROL_CLASSID )
_class_rtti_end_


_class_rtti_(ComboBoxControl, "VCF::CustomControl", COMBOBOXCONTROL_CLASSID )
_delegate_(ItemDelegate, SelectionChanged )
_class_rtti_end_


_class_rtti_(CommandButton, "VCF::Control", COMMANDBUTTON_CLASSID)
_property_( String, "caption", getCaption, setCaption, "" );
_property_( bool, "default", isDefaultBtn, setAsDefaultBtn, "" );
_property_enum_labeled_( ButtonCommandType, "commandType", getCommandType, setCommandType,
					   BC_NONE, BC_MAYBE, 6, ButtonCommandTypeNames, "");
_delegate_( ButtonDelegate, ButtonClicked )
_class_rtti_end_


_class_rtti_(ControlContainer, "VCF::CustomControl", CONTROLCONTAINER_CLASSID)
_property_(double, "bottomBorderHeight", getBottomBorderHeight, setBottomBorderHeight, "");
_property_(double, "topBorderHeight", getTopBorderHeight, setTopBorderHeight, "");
_property_(double, "rightBorderWidth", getRightBorderWidth, setRightBorderWidth, "");
_property_(double, "leftBorderWidth", getLeftBorderWidth, setLeftBorderWidth, "");
_property_(double, "borderSize", getBorderSize, setBorderSize, "");
_class_rtti_end_


_class_rtti_(CustomControl, "VCF::Control", CUSTOMCONTROL_CLASSID )
_property_( bool, "transparent", isTransparent, setTransparent, "" );
_property_( bool, "useColorForBackground", getUseColorForBackground, setUseColorForBackground, "" );
_class_rtti_end_



_class_rtti_(DefaultMenuItem, "VCF::MenuItem", DEFAULTMENUITEM_CLASSID)
_delegate_( MenuItemDelegate, MenuItemClicked )
_delegate_( MenuItemDelegate, MenuItemUpdate )
_class_rtti_end_


_class_rtti_(ColumnModel, "VCF::SimpleListModel", COLUMNMODEL_CLASSID)
_class_rtti_end_

_class_rtti_(DefaultListModel, "VCF::SimpleListModel", DEFAULTLISTMODEL_CLASSID)
_class_rtti_end_

_class_rtti_(TabModel, "VCF::SimpleListModel", TABMODEL_CLASSID )
	_delegate_(TabModelDelegate, TabPageSelected )
_class_rtti_end_



_class_rtti_(DefaultTabPage, "VCF::TabPage", DEFAULTTABPAGE_CLASSID)

_class_rtti_end_


_class_rtti_(DefaultTableCellItem, "VCF::TableCellItem", DEFAULTTABLECELLITEM_CLASSID)

_class_rtti_end_



_class_rtti_(DefaultTableModel, "VCF::TableModel", DEFAULTTABLEMODEL_CLASSID )
//	_delegate_( TableModelDelegate, TableCellAdded )
//	_delegate_( TableModelDelegate, TableCellDeleted )
//	_delegate_( TableModelDelegate, TableRowsAdded )
//	_delegate_( TableModelDelegate, TableRowsDeleted )
//	_delegate_( TableModelDelegate, TableColumnsAdded )
//	_delegate_( TableModelDelegate, TableColumnsDeleted )
_class_rtti_end_

_class_abstract_rtti_(TextModel, "VCF::Model", TEXTMODEL_CLASSID)	
_class_rtti_end_


_class_rtti_(DefaultTextModel, "VCF::TextModel", DEFAULTTEXTMODEL_CLASSID)	
_class_rtti_end_



_class_rtti_(Dialog, "VCF::Frame", DIALOG_CLASSID )
_class_rtti_end_


_class_rtti_(HeaderControl, "VCF::CustomControl", HEADERCONTROL_CLASSID)
	_property_object_( ColumnModel, "columnModel", getColumnModel, setColumnModel, "" );
	_delegate_(MouseDelegate, ColumnItemClicked );
	_delegate_(ItemDelegate, ColumnWidthChanged );
_class_rtti_end_



_class_rtti_(ImageComponent, "VCF::UIComponent", IMAGECOMPONENT_CLASSID)
_property_typedef_( String, "filename", getFilename, setFilename, "VCF::ImageFilenameString", "" );
_property_(bool, "transparent", getTransparent, setTransparent, "");
_class_rtti_end_

_class_rtti_(ImageControl, "VCF::CustomControl", IMAGECONTROL_CLASSID)
_property_object_( Image, "image", getImage, setImage, "" );
_property_(bool, "transparent", getTransparent, setTransparent, "");
//this is a typedef property registration, which allows a normal type, like a string, to 
//become defined with a different type name.
_property_typedef_( String, "filename", getFilename, setFilename, "VCF::ImageFilenameString", "" );
_class_rtti_end_



_class_rtti_(Label, "VCF::CustomControl", LABEL_CLASSID )
_property_( String, "caption", getCaption, setCaption, "" );
_property_enum_labeled_( TextAlignmentType, "textAlignment", getTextAlignment, setTextAlignment,
					   taTextLeft, taTextRight, 3, TextAlignmentTypeNames, "");
_property_enum_labeled_( TextVerticalAlignment, "verticalAlignment", getVerticalAlignment, setVerticalAlignment,
					   tvaTextTop, tvaTextBottom, 3, TextVerticalAlignmentNames, "");

_property_object_( Control, "focusControl", getFocusControl, setFocusControl, "" );

_property_( bool, "wordWrap", getWordWrap, setWordWrap, "" );

_class_rtti_end_



_class_rtti_(ListBoxControl, "VCF::ListControl", LISTBOXCONTROL_CLASSID )
_property_( double, "defaultItemHeight", getDefaultItemHeight, setDefaultItemHeight, "" );
//_property_( bool, "allowsMultiSelect", getAllowsMultiSelect, setAllowsMultiSelect, "" );
_class_rtti_end_



_class_abstract_rtti_(ListControl, "VCF::Control", LISTCONTROL_CLASSID )
_property_object_( ImageList, "smallImageList", getSmallImageList, setSmallImageList, "" );
_property_object_( ImageList, "largeImageList", getLargeImageList, setLargeImageList, "" );
_property_object_( ImageList, "statImageList", getStateImageList, setStateImageList, "" );

_property_object_( ListModel, "listModel", getListModel, setListModel, "" );

_delegate_(ItemDelegate, ItemSelectionChanged );
_class_rtti_end_


_class_rtti_(DropDownControl, "VCF::ListControl", DROPDOWNCONTROL_CLASSID )
_property_( String, "editText", getEditText, setEditText, "" );
_property_( double, "dropDownWidth", getDropDownWidth, setDropDownWidth, "" );
_property_( uint32, "dropDownCount", getDropDownCount, setDropDownCount, "" );
_property_( bool, "editBoxEnabled", editBoxEnabled, enableEditBox, "" );
_class_rtti_end_


_class_rtti_(ListViewControl, "VCF::ListControl", LISTVIEWCONTROL_CLASSID )
_property_enum_labeled_( IconStyleType, "iconStyle", getIconStyle, setIconStyle,
					   isLargeIcon, isDetails, 4, IconStyleTypeNames, "");
_property_enum_labeled_( IconAlignType, "iconAlignment", getIconAlignment, setIconAlignment,
					   iaNone, iaAutoArrange, 4, IconAlignTypeNames, "");

_property_object_( ColumnModel, "columnModel", getColumnModel, setColumnModel, "" );
//_property_object_ro_( ColumnModel, "columnModel", getColumnModel, "" );

_delegate_(MouseDelegate, ColumnItemClicked );

_class_rtti_end_


_class_rtti_(Menu, "VCF::Component", MENU_CLASSID )
_property_object_( MenuItem, "rootMenuItem", getRootMenuItem, setRootMenuItem, "" );
_class_rtti_end_




_class_rtti_(MenuBar, "VCF::Menu", MENUBAR_CLASSID )
_class_rtti_end_


_class_rtti_( MessageDialog, "VCF::Dialog", MESSAGEDIALOG_CLASSID )
_class_rtti_end_


_class_rtti_(MultilineTextControl, "VCF::TextControl", MULTILINETEXTCONTROL_CLASSID)
_class_rtti_end_

/*
_class_rtti_(OpenGLControl, "VCF::OpenGLControl", "VCF::CustomControl", OPENGLCONTROL_CLASSID )
_class_rtti_end_(OpenGLControl)
*/

_class_rtti_(Panel, "VCF::ControlContainer", PANEL_CLASSID )
_class_rtti_end_


_class_rtti_(PopupMenu, "VCF::Menu", POPUPMENU_CLASSID )
_class_rtti_end_


_class_rtti_(PushButton, "VCF::CustomControl", PUSHBUTTON_CLASSID)
_property_object_( ImageList, "imageList", getImageList, setImageList, "" );
_property_( String, "caption", getCaption, setCaption, "" );
_property_( bool, "showCaption", getShowCaption, setShowCaption, "" );
_class_rtti_end_


_class_rtti_(RadioButtonControl, "VCF::ToggledButton", RADIOBUTTONCONTROL_CLASSID )
_property_( int32, "groupID", getGroupID, setGroupID, "" );
_class_rtti_end_



_class_rtti_(ScrollbarManager, "VCF::Component", SCROLLBARMANAGER_CLASSID)
_property_object_( Control, "target", getTarget, setTarget, "" );
_property_( double, "virtualViewHeight", getVirtualViewHeight, setVirtualViewHeight, "" );
_property_( double, "virtualViewWidth", getVirtualViewWidth, setVirtualViewWidth, "" );
_property_( double, "verticalPosition", getVerticalPosition, setVerticalPosition, "" );
_property_( double, "horizontalPosition", getHorizontalPosition, setHorizontalPosition, "" );
_property_( double, "verticalTopScrollSpace", getVerticalTopScrollSpace, setVerticalTopScrollSpace, "" );
_property_( double, "verticalBottomScrollSpace", getVerticalBottomScrollSpace, setVerticalBottomScrollSpace, "" );
_property_( double, "horizontalLeftScrollSpace", getHorizontalLeftScrollSpace, setHorizontalLeftScrollSpace, "" );
_property_( double, "horizontalRightScrollSpace", getHorizontalRightScrollSpace, setHorizontalRightScrollSpace, "" );
_property_( bool, "hasVerticalScrollbar", hasVerticalScrollBar, setHasVerticalScrollbar, "" );
_property_( bool, "hasHorizontalScrollbar", hasHorizontalScrollBar, setHasHorizontalScrollbar, "" );
_class_rtti_end_



_class_rtti_(Splitter, "VCF::CustomControl", SPLITTER_CLASSID)
//_property_(bool,"updateAttachedControl",Splitter::getUpdateAttachedControl, Splitter::setUpdateAttachedControl,"")
_class_rtti_end_


_class_rtti_(StatusBar, "VCF::CustomControl", STATUSBAR_CLASSID)
	_property_(String,"statusText",getStatusText,setStatusText,"")
	_property_array_( String, "status", getStatusPaneText,setStatusPaneText,insertStatusPane,removeStatusPane,getStatusPaneCount, "" )
_class_rtti_end_


_class_rtti_(TabbedPages, "VCF::CustomControl", TABBEDPAGES_CLASSID )
	_property_(double, "tabHeight", getTabHeight, setTabHeight, "" )
	_property_(double, "borderWidth", getBorderWidth, setBorderWidth, "" )
	_property_object_( TabModel, "tabModel", getTabModel, setTabModel, "" )
	_property_object_( TabPage, "selectedPage", getSelectedPage, setSelectedPage, "" )
	_property_object_( TabSheet, "selectedSheet", getSelectedSheet, setSelectedSheet, "" )
_class_rtti_end_


_class_rtti_(TabSheet, "VCF::Panel", TABSHEET_CLASSID )	
	_property_object_( TabPage, "page", getPage, setPage, "" )
	_property_(String, "title", getTitle, setTitle, "" )
_class_rtti_end_



_class_rtti_(TableControl, "VCF::CustomControl", TABLECONTROL_CLASSID );
_class_rtti_end_



_class_rtti_(TextControl, "VCF::Control", TEXTCONTROL_CLASSID )
_property_( bool, "readonly",isReadOnly, setReadOnly, "" );
_property_( bool, "textWrapping",getTextWrapping, setTextWrapping, "" );
_property_( String, "text",getText, setText, "" );
_property_enum_labeled_( TextValidationStyle, "validationStyle", getValidationStyle, setValidationStyle,
					   tvsOnKeyEvent, tvsOnEnterKey, 3, TextValidationStyleNames, "");
_class_rtti_end_




_class_abstract_rtti_(InputValidator, "VCF::Component", "InputValidator")
_property_object_( TextControl, "inputControl", getInputControl, setInputControl, "" )
_class_rtti_end_



_class_rtti_(AlphaNumericValidator, "VCF::InputValidator", "AlphaNumericValidator")
_property_( String, "invalidCharacters",getInvalidCharacters, setInvalidCharacters, "" )
_class_rtti_end_




_class_rtti_(TimerComponent, "VCF::Component", TIMERCOMPONENT_CLASSID)
_property_( bool, "active",isActive, setActivated, "" );
_property_( int32, "timeoutInterval", getTimeoutInterval, setTimeoutInterval, "" );
_delegate_(TimerDelegate, TimerActivated );
_delegate_(TimerDelegate, TimerDeactivated );
_delegate_(TimerDelegate, TimerPulse );
_class_rtti_end_


_class_rtti_(Toolbar, "VCF::Control", TOOLBAR_CLASSID);
_property_( bool, "showButtonCaptions",getShowButtonCaptions, setShowButtonCaptions, "" );
_property_( bool, "horizontalCaptions",getButtonCaptionsHorizontal, setButtonCaptionsHorizontal, "" );
_property_( bool, "autoResizeEnabled",isAutoResizeEnabled, setEnableAutoResize, "" );
_property_object_( ImageList, "imageList", getImageList, setImageList, "" );

_class_rtti_end_



_class_rtti_(ToolbarDock, "VCF::CustomControl", TOOLBARDOCK_CLASSID);
_property_enum_labeled_( ToolbarDockSide, "dockSide", getDockSide, setDockSide,
					   tdsTop, tdsBottom, 4, ToolbarDockSideNames, "");

_property_enum_labeled_( ToolbarBackgroundStyle, "backgroundStyle", getBackgroundStyle, setBackgroundStyle,
					   tbksNone, tbksStretch, 3, ToolbarBackgroundStyleNames, "");

_property_object_( Image, "background", getBackground, setBackground, "" );

_property_( bool, "usingBackground", isUsingBackground, setUsingBackground, "" );
_property_( bool, "allowsDragging", allowsDragging, setAllowsDragging, "" );

_class_rtti_end_



_class_rtti_(TreeControl, "VCF::Control", TREECONTROL_CLASSID )
_property_object_( TreeModel, "treeModel", getTreeModel, setTreeModel, "" );
_delegate_(ItemDelegate, ItemSelected );
_delegate_(ItemDelegate, ItemExpanded );
_delegate_(ItemDelegate, ItemStateChangeRequested );
_property_object_( ImageList, "imageList", getImageList, setImageList, "" );
_property_object_( ImageList, "stateImageList", getStateImageList, setStateImageList, "" );
_property_enumset_( uint32, "displayOptions", getDisplayOptions, setDisplayOptions, 6, TreeDisplayOptionsValues, TreeDisplayOptionsNames, ""  );

_class_rtti_end_



_class_rtti_(TreeListControl, "VCF::TreeControl", TREELISTCONTROL_CLASSID )
_property_object_ro_( ColumnModel, "columnModel", getColumnModel, "" );
_property_object_( ImageList, "headerImageList", getHeaderImageList, setHeaderImageList, "" );
_delegate_(MouseDelegate, ColumnItemClicked );
_delegate_(ItemDelegate, ColumnWidthChanged );
_class_rtti_end_

/*
_class_rtti_(UIApplication, "UIApplication", "Application", UIAPPLICATION_CLASSID)
_class_rtti_end_(UIApplication)
*/


_class_rtti_(Window, "VCF::Frame", WINDOW_CLASSID )
_property_object_( MenuBar, "menuBar", getMenuBar, setMenuBar, "" );
_delegate_(WindowDelegate, WindowRestore )
_delegate_(WindowDelegate, WindowMaximize )
_delegate_(WindowDelegate, WindowMinimize )
_class_rtti_end_



_class_rtti_(ProgressControl, "VCF::CustomControl", PROGRESSCONTROL_CLASSID )
_property_( double, "minValue", getMinValue, setMinValue, "" );
_property_( double, "maxValue", getMaxValue, setMaxValue, "" );
_property_( double, "position", getPosition, setPosition, "" );
_property_( bool, "displayProgressText", getDisplayProgressText, setDisplayProgressText, "" );
_property_( bool, "useProgressFormatString", getUseProgressFormatString, setUseProgressFormatString, "" );
_property_( double, "stepItIncrement", getStepItIncrement, setStepItIncrement, "" );
_property_object_( Color, "progressBarColor", getProgressBarColor, setProgressBarColor, "" );
_property_object_( Color, "progressTextColor", getProgressTextColor, setProgressTextColor, "" );
_property_enum_labeled_( ProgressControl::ProgressAlignment, "displayAlignment", getDisplayAlignment, setDisplayAlignment,
					   ProgressControl::paVertical, ProgressControl::paHorizontal, 
					   2, ProgressAlignmentNames, "");

_class_rtti_end_


_class_rtti_(SliderControl, "VCF::CustomControl", SLIDERCONTROL_CLASSID )
_property_enum_labeled_( SliderControl::DisplayOrientation, "displayOrientation", getDisplayOrientation, setDisplayOrientation,
					   SliderControl::doHorizontal, SliderControl::doVertical, 2, ProgressAlignmentNames, "");
_property_( double, "minValue", getMinValue, setMinValue, "" );
_property_( double, "maxValue", getMaxValue, setMaxValue, "" );
_property_( double, "position", getPosition, setPosition, "" );
_property_( bool, "tickMarks", hasTickMarks, setHasTickMarks, "" );
_property_( int32, "tickFrequency", getTickFrequency, setTickFrequency, "" );
_property_( double, "stepIncrement", getStepIncrement, setStepIncrement, "" );
_property_( double, "stepIncrement", getPageIncrement, setPageIncrement, "" );
_class_rtti_end_


_class_rtti_(SystemTray, "VCF::Component", SYSTEMTRAY_CLASSID )
	_delegate_( EventDelegate, TrayIconChanged )
	_property_object_( PopupMenu, "popupMenu", getPopupMenu, setPopupMenu, "" );
	_property_( String, "tooltipText", getTooltipText, setTooltipText, "" );
_class_rtti_end_



//property editors!



#define ABSTRACTPROPERTYEDITOR_CLASSID	"e7bfe231-713e-4d32-b32f-fb8eecb4cf84"

_class_abstract_rtti_(AbstractPropertyEditor, "VCF::ObjectWithCallbacks", ABSTRACTPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define IMAGEPROPERTYEDITOR_CLASSID "c1ab05f9-ee5c-4e1d-a535-94a8f475fc81"

_class_rtti_(ImagePropertyEditor, "VCF::AbstractPropertyEditor", IMAGEPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define IMAGEFILENAMEPROPERTYEDITOR_CLASSID "4a519d27-c486-4501-8591-552f56609c00"

_class_rtti_(ImageFilenamePropertyEditor, "VCF::AbstractPropertyEditor", IMAGEFILENAMEPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define INTEGERPROPERTYEDITOR_CLASSID "4ab9c999-16e2-45b0-b586-0ff1c2dc6c6f"

_class_rtti_(IntegerPropertyEditor, "VCF::AbstractPropertyEditor", INTEGERPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define DOUBLEPROPERTYEDITOR_CLASSID "7f34bc88-c020-48fb-80a0-20d6d512fbfc"

_class_rtti_(DoublePropertyEditor, "VCF::AbstractPropertyEditor", DOUBLEPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define STRINGPROPERTYEDITOR_CLASSID "7039e0b6-17fd-4317-8749-d662822744ea"

_class_rtti_(StringPropertyEditor, "VCF::AbstractPropertyEditor", STRINGPROPERTYEDITOR_CLASSID)
_class_rtti_end_



#define BOOLPROPERTYEDITOR_CLASSID "cd440a0d-9f08-4c48-8185-b8cb2c6f7ef9"

_class_rtti_(BoolPropertyEditor, "VCF::AbstractPropertyEditor", BOOLPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define ENUMPROPERTYEDITOR_CLASSID "2221d216-6c19-4e7f-82a0-07c6b018ead6"

_class_rtti_(EnumPropertyEditor, "VCF::AbstractPropertyEditor", ENUMPROPERTYEDITOR_CLASSID)
_class_rtti_end_



#define ENUMSETPROPERTYEDITOR_CLASSID "7503b6d1-fe95-4167-9430-41e2d583bbdb"

_class_rtti_(EnumSetPropertyEditor, "VCF::AbstractPropertyEditor", ENUMSETPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define CURSORPROPERTYEDITOR_CLASSID "145181bc-70d6-47cb-9dc4-163540e82cf3"

_class_rtti_(CursorPropertyEditor, "VCF::AbstractPropertyEditor", CURSORPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define COLORPROPERTYEDITOR_CLASSID "5f7c1d05-78da-4e6b-b22b-fc290e5207e4"

_class_rtti_(ColorPropertyEditor, "VCF::AbstractPropertyEditor", COLORPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define FONTPROPERTYEDITOR_CLASSID "192e8624-94c6-46fb-8092-16ee2cb6fb27"

_class_rtti_(FontPropertyEditor, "VCF::AbstractPropertyEditor", FONTPROPERTYEDITOR_CLASSID)
_class_rtti_end_



#define DEFAULTMENUITEMPROPERTYEDITOR_CLASSID "b4cf4ef4-f135-4a23-8237-486144e5ba06"

_class_rtti_(DefaultMenuItemPropertyEditor, "VCF::AbstractPropertyEditor", DEFAULTMENUITEMPROPERTYEDITOR_CLASSID)
_class_rtti_end_


#define DEFAULTLISTMODELPROPERTYEDITOR_CLASSID "9f39a5a5-9910-4ae2-a6b3-c6ff38682283"

_class_rtti_(DefaultListModelPropertyEditor, "VCF::AbstractPropertyEditor", DEFAULTLISTMODELPROPERTYEDITOR_CLASSID)
_class_rtti_end_






_class_rtti_(ObjectModel, "VCF::Model", "ObjectModel")
	_property_object_( Object, "source", getSource, setSource, "" )
_class_rtti_end_

_class_rtti_(ObjectListModel, "VCF::SimpleListModel", "ObjectListModel")	
_class_rtti_end_


_class_rtti_(DictionaryModel, "VCF::Model", "DictionaryModel")	
_class_rtti_end_


_class_rtti_(ObjectColumnModel, "VCF::ColumnModel", "ObjectColumnModel")	
	_property_object_( ListModel, "listModel", getListModel, setListModel, "" )
_class_rtti_end_




};


/**
$Id$
*/
