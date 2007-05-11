#ifndef _VCF_COMBOBOXCONTROL_H__
#define _VCF_COMBOBOXCONTROL_H__
//ComboBoxControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */


#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__

#ifndef _VCF_LISTITEM_H__
#	include "vcf/ApplicationKit/ListItem.h"
#endif // _VCF_LISTITEM_H__

#ifndef _VCF_LISTMODELEVENT_H__
#	include "vcf/ApplicationKit/ListModelEvent.h"
#endif // _VCF_LISTMODELEVENT_H__



namespace VCF {

class TextControl;

#define COMBOBOXCONTROL_CLASSID		"4A9D66D5-3B26-11d4-B54C-00C04F0196DA"


/**
*The various styles for a ComboBoxControl. Currently there are only 2.
*/
enum ComboBoxStyleType {
	cbsDropDown = 0,
	cbsDropDownWithEdit
};


static String ComboBoxStyleTypeNames[] = { "cbsDropDown",
                                         "cbsDropDownWithEdit" };



/**
\class ComboBoxControl ComboBoxControl.h "vcf/ApplicationKit/ComboBoxControl.h"
*A combo box control is a control that is used to display a selection from a list of choices
*in a single field. When the down arrow is clicked on a popup list is displayed that shows
*all the possible choices for the control.
*<p>
*The ComboBoxControl uses the ListModel, same abstract model as the ListBoxControl and
*ListViewControl controls, to store it's presentation data in.

@delegates
	@del ComboBoxControl::SelectionChanged

*/
class APPLICATIONKIT_API ComboBoxControl : public VCF::CustomControl {
public:

	ComboBoxControl();

	virtual ~ComboBoxControl();

	void init();

	/**
	@delegate SelectionChanged this is fired when the selection changes in the
	combo box.
	@event ItemEvent
	@eventtype ITEM_EVENT_SELECTED
	*/
	DELEGATE(SelectionChanged)

	/**
	*returns the ListModel currently associated with it.
	*@return ListModel the list model for the control
	*/
	ListModel* getListModel();

	/**
	*sets the ListModel for the Control. If there was a previous ListModel
	*already associated with the control, then the old ListModel's release() method
	*will be called prior to setting the new ListModel. The control will
	*call the newly set ListModel's addRef() after setting.
	*@param ListModel the new model to set for this control
	*/
	void setListModel(ListModel * model);

	/**
	*the overriden paint method
	*/
	virtual void paint( GraphicsContext* context );


	void onListModelContentsChanged( ListModelEvent* event );

	void onItemAdded( ListModelEvent* event );

	void onItemDeleted( ListModelEvent* event );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void mouseEnter( MouseEvent* event );

	virtual void mouseLeave( MouseEvent* event );

	virtual void keyPressed( KeyboardEvent* event );

	/**
	*returns the currently selected item.
	*@return ListItem the currently selected tiem. If nothing is selected then
	*the return value will be NULL.
	*/
	ListItem* getSelectedItem();

	/**
	*sets the currently selected item. Causes a SelectionChanged
	*event to be fired.
	@param ListItem the item to be selected
	*/
	void setSelectedItem( ListItem* selectedItem );

	/**
	*sets the currently selected item as specified by the index.
	*Causes a SelectionChanged event to be fired.
	@param uint32 the index of the item to be selected
	*/
	void setSelectedItemIndex( const uint32& selectedIndex );

	/**
	*returns the combo box style.
	*The style may be cbsDropDown, which means the entry in the combo box field
	*is non editable, or cbsDropDownWithEdit, which means the user can edit the
	*fields data.
	@return ComboBoxStyleType the current style of the ComboBoxControl
	*/
	ComboBoxStyleType getComboBoxStyle() {
		return comboBoxStyle_;
	}

	/**
	*sets the style of the combo box
	*@param ComboBoxStyleType the new style of the ComboBoxControl
	*/
	void setComboBoxStyle( const ComboBoxStyleType& comboBoxStyle );

	/**
	*adds a new ListItem. This method simply calls the models ListModel::addItem()
	*method and returns the newly created ListItem. Currently the default implementation
	*creates a DefaultListItem to add.
	*@param String the caption of the new item
	*@param uint32 th image index of the new item. The default value is 0
	*@return ListItem the newly added item
	*/
	ListItem* addItem( const String& caption, const uint32 imageIndex=0 );

	/**
	*adds a new ListItem. This method simply calls the models ListModel::addItem()
	*method.
	*@param ListItem the item top be added to the control's ListModel
	*/
	void addItem( ListItem* item );

	/**
	*sets the drop down count. This is used to specify how many
	*items are visible in the drop down list before scrollbars
	*become neccessary
	*@param uint32 the new drop down count
	*/
	void setDropDownCount( const uint32& dropDownCount );

	/**
	*returns the current drop down count
	*/
	uint32 getDropDownCount() {
		return dropDownCount_;
	}

	/**
	*sets the drop down width. This is used to specify the width
	*of the drop down list if the user prefers it bigger then
	*the ComboBoxControl's width itself
	*@param uint32 the new drop down witdh
	*/
	void setDropDownWidth( const uint32& dropDownCount );

	/**
	*returns the current drop down witdh
	*/
	uint32 getDropDownWidth() {
		return (uint32)dropDownWidth_;
	}

	/**
	*sets true to allow the drop down list to extend to the full screen height
	*@param bool the new state of drop down list extension
	*/
	void setDropDownExtendFullScreen( const bool& dropDownExtendFullScreen );

	/**
	*returns true if the drop down list is allowed to extend to the full screen height
	*/
	bool getDropDownExtendFullScreen() {
		return dropDownExtendFullScreen_;
	}

	/**
	*sets true to allow the drop down list to be scrolled only by discrete amounts.
	*@param bool, true if only discrete amounts are allowed.
	*/
	void setDiscreteScroll( const bool& discreteScroll );

	/**
	*returns true if only a scrolling by discrete amounts are allowed.
	*/
	bool getDiscreteScroll() {
		return discreteScroll_;
	}

	/**
	*sets if the item has been selected through the drop down list
	*( i.e. manually by the user ) or through calls by source code
	* by using the function setSelectedItem
	*@param bool state telling if selected by the drop down list ( for reset )
	*/
	void setDropDownSelected( const bool& dropDownSelected );

	/**
	*returns the current state telling if the item has been selected by
	*clicking the drop down list
	*/
	bool getDropDownSelected() {
		return dropDownSelected_;
	}

	/**
	* lookup for an item in the dropdown list starting by a given text string.
	*@param const String& text, the string to lookup
	*@param const bool& ignoreCase, true if the lettercase is ignored in the search
	*@return ListItem*, the item in the list starting with the given text.
	*/
	ListItem* lookupItem( const String& text, const bool& ignoreCase=false );

	/**
	*sets if the autoLookup of typed items is enabled
	*@param bool state telling if the autoLookup is enabled
	*/
	void setAutoLookup( const bool& autoLookup );

	/**
	*returns the current state telling if the autoLookup is enabled
	*/
	bool getAutoLookup() {
		return autoLookup_;
	}

	/**
	*sets if the autoLookup is done ignoring then letter's case
	*@param bool state telling if the autoLookup is done ignoring then letter's case
	*/
	void setAutoLookupIgnoreCase( const bool& ignoreCase );

	/**
	*returns the current state telling if the autoLookup is done ignoring then letter's case
	*/
	bool getAutoLookupIgnoreCase() {
		return autoLookupIgnoreCase_;
	}

	virtual bool keepsArrowKeys() {
		return true;
	}

	void setEnabled( const bool& enabled );

	String getCurrentText();

	virtual void setCurrentText( const String& text );

	Rect getEditBounds();

	virtual double getPreferredHeight();

	virtual void selectItems( const bool& select );

	virtual bool generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue );
protected:
	void onDropDownLostFocus( WindowEvent* event );
	void closeDropDown( Event* event );
	void onEditKeyPressed( KeyboardEvent* event );
	void onEditReturnKeyPressed( KeyboardEvent* event );

	void onFocusGained( FocusEvent* event );

	void onPostSelect( ItemEvent* e );

	virtual void destroy();

protected:
	Window* dropDown_;
	ListModel* listModel_;
	ListItem* selectedItem_;
	uint32 selectedIndex_;
	bool arrowPressed_;
	//Rect arrowRect_;
	Rect viewRect_;
	bool mouseOver_;
	ComboBoxStyleType comboBoxStyle_;
	TextControl* edit_;
	void updateEditBounds();
	uint32 dropDownCount_;
	double dropDownWidth_;
	bool dropDownExtendFullScreen_;
	bool discreteScroll_;
	bool dropDownSelected_;
	bool autoLookup_;
	bool autoLookupIgnoreCase_;
};

}; //namespace VCF


#endif // _VCF_COMBOBOXCONTROL_H__

/**
$Id$
*/
