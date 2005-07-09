//Toolbar.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Toolbar.h"
#include "vcf/ApplicationKit/ToolbarPeer.h"
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


//******************************************************************************
//ToolbarItem
//******************************************************************************

ToolbarItem::ToolbarItem():
	control_(NULL),
	state_(tisEnabled),
	model_(NULL),
	data_(NULL),
	imageIndex_(0),
	imageStateIndex_(0),
	itemControl_(NULL)
{
	tag_ = -1;
}

void ToolbarItem::click()
{
	ButtonEvent event( this, ToolbarItem::tbItemClicked );

	Action* action = getAction();
	if ( NULL != action ) {
		action->perform( &event );
	}
	else {
		ItemClicked.fireEvent( &event );
	}

}

bool ToolbarItem::updateAction()
{
	if ( !Component::updateAction() ) {
		Event event( this, ToolbarItem::tbItemUpdate );
		ItemUpdate.fireEvent( &event );
		return true;
	}

	return false;
}

void ToolbarItem::handleEvent( Event* event )
{
	Component::handleEvent( event );
	switch ( event->getType() ){
		case Action::UpdateEvent : {
			ActionEvent* actionEvent = (ActionEvent*)event;


			setEnabled( actionEvent->isEnabled() );

			Toolbar* toolbar = (Toolbar*)control_;

			if ( NULL != toolbar ) {
				if ( toolbar->getShowButtonCaptions() ) {
					setCaption( actionEvent->getText() );
				}
				else {
					setTooltip( actionEvent->getText() );
				}
			}

			if ( this->isChecked() && (actionEvent->getState() & tisPressed) ) {
				setPressed( true );
			}
			else if ( isChecked() ) {
				setPressed( false );
			}
		}
		break;	
		
		
	}
}

bool ToolbarItem::containsPoint( Point * pt )
{
	return bounds_.containsPt(pt);
}

void ToolbarItem::setItemControl( Control* control )
{
	itemControl_ = control;

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbItemControlAdded, this );
	}
}

void ToolbarItem::setAsSeparator()
{
	setState( tisSeparator );
}

void ToolbarItem::setPressed( bool val )
{
	if ( ( (state_ & ToolbarItem::tisPressed) != 0 ) == val ) {
		return;
	}

	long state = state_;
	if ( val ) {
		state |= tisPressed;
	}
	else {
		state &= ~tisPressed;
	}
	setState( state );
}

bool ToolbarItem::isEnabled()
{
	return (state_ & ToolbarItem::tisEnabled) ? true : false;
}

void ToolbarItem::setEnabled( const bool& val )
{
	if ( isEnabled() == val ) {
		return;
	}

	long state = state_;
	if ( val ) {
		state |= ToolbarItem::tisEnabled;
	}
	else {
		state &= ~ToolbarItem::tisEnabled;
	}

	setState( state );
}

void ToolbarItem::setState( const long& state )
{
	if ( state_ == state ) {
		return ;
	}

	state_ = state;

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbStateChanged, this );
	}
}

void ToolbarItem::setStateImageIndex( const long& index )
{
	imageStateIndex_ = index;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbStateImageIndexChanged, this );
	}
}

ulong32 ToolbarItem::getIndex()
{
	return ((ToolbarModel*)model_)->getItemIndex(this);
}

void ToolbarItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbImageIndexChanged, this );
	}
}

void ToolbarItem::setIndex( const unsigned long& index )
{
	//no-op
}

bool ToolbarItem::isSelected()
{
	return (state_ & tisSelected) ? true : false;
}

void ToolbarItem::setSelected( const bool& selected )
{
	if ( isSelected() == selected ) {
		return;
	}

	if ( selected ) {
		state_ |= tisSelected;
	}
	else {
		state_ &= ~tisSelected;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbSelected, this );
	}
}

void ToolbarItem::internal_setBounds( const Rect& bounds ) //Parameter made const for ANSI compliance - ACH
{
	bounds_ = bounds;
	if ( NULL != itemControl_ ) {
		Rect controlBounds = itemControl_->getBounds();
		//if ( !(controlBounds == bounds_) ) {
			itemControl_->setBounds( &bounds_ );
		//}
	}
}

void ToolbarItem::setBounds( Rect* bounds )
{
	internal_setBounds( *bounds );
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbDimensionsChanged, this );
	}
}

void ToolbarItem::setWidth( const double& val )
{
	bounds_.right_ = bounds_.left_ + val;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbDimensionsChanged, this );
	}
}


void ToolbarItem::setCaption( const String& val )
{
	if ( val == caption_ ) {
		return;
	}

	caption_ = val;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbCaptionChanged, this );
	}
}

void ToolbarItem::setTooltip( const String& val )
{
	if ( val == tooltip_ ) {
		return;
	}

	tooltip_ = val;
	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbTooltipChanged, this );
	}
}

void ToolbarItem::setGrouped( const bool& val )
{
	if ( val == isGrouped() ) {
		return;
	}

	if ( val ) {
		state_ |= tisGrouped;
	}
	else {
		state_ &= ~tisGrouped;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbGroupChanged, this );
	}
}

bool ToolbarItem::isGrouped()
{
	return (state_ & tisGrouped) ? true : false;
}

void ToolbarItem::setChecked( const bool& val )
{
	if ( val == isChecked() ) {
		return;
	}

	if ( val ) {
		state_ |= tisChecked;
	}
	else {
		state_ &= ~tisChecked;
	}

	if ( NULL != model_ ) {
		((ToolbarModel*)model_)->itemChanged( ToolbarItem::tbCheckChanged, this );
	}
}

bool ToolbarItem::isChecked()
{
	return (state_ & tisChecked) ? true : false;
}

//******************************************************************************
//ToolbarModel
//******************************************************************************

ToolbarModel::ToolbarModel()
{
	itemsContainer_.initContainer( toolbarItems_ );
}

ToolbarModel::~ToolbarModel()
{
	std::vector<ToolbarItem*>::iterator it = toolbarItems_.begin();
	while ( it != toolbarItems_.end() ) {
		ToolbarItem* item = *it;
		item->release();
		it ++;
	}

	toolbarItems_.clear();
}

void ToolbarModel::addItem( ToolbarItem* item )
{
	toolbarItems_.push_back( item );
	item->setModel( this );
	itemChanged( ToolbarItem::tbAdded, item );
}

void ToolbarModel::insertItem( ToolbarItem* item, const ulong32& index )
{
	toolbarItems_.insert( toolbarItems_.begin() + index, item );
	item->setModel( this );
	itemChanged( ToolbarItem::tbAdded, item );
}

void ToolbarModel::removeItem( ToolbarItem* item )
{
	std::vector<ToolbarItem*>::iterator found = std::find( toolbarItems_.begin(), toolbarItems_.end(), item );
	if ( found != toolbarItems_.end() ) {

		toolbarItems_.erase( found );

		itemChanged( ToolbarItem::tbRemoved, item );
	}
}

void ToolbarModel::itemChanged( const ulong32& eventType, ToolbarItem* item )
{
	ToolbarModelEvent e(this, eventType);
	e.setItem( item );

	ModelChanged.fireEvent( &e );
}

ulong32 ToolbarModel::getItemIndex( ToolbarItem* item )
{
	std::vector<ToolbarItem*>::iterator found = std::find( toolbarItems_.begin(), toolbarItems_.end(), item );
	if ( found != toolbarItems_.end() ) {
		return found - toolbarItems_.begin();
	}
	return 0;
}

void ToolbarModel::setItemIndex( ToolbarItem* item, const ulong32& newIndex )
{
	std::vector<ToolbarItem*>::iterator found = std::find( toolbarItems_.begin(), toolbarItems_.end(), item );
	if ( found != toolbarItems_.end() ) {
		toolbarItems_.erase( found );

		toolbarItems_.insert( toolbarItems_.begin()+newIndex, item );

		itemChanged( ToolbarItem::tbAdded, item );
	}
}







//******************************************************************************
//Toolbar
//******************************************************************************

Toolbar::Toolbar():
	Control(),
	toolbarPeer_(NULL),
	showButtonCaptions_(false),
	buttonCaptionsHorizontal_(false)
{
	toolbarPeer_ = UIToolkit::createToolbarPeer( this );
	peer_ = dynamic_cast<ControlPeer*>(toolbarPeer_);	

	setViewModel( new ToolbarModel() );

	peer_->create( this );

	setVisible( true );

	setContainer( new StandardContainer() );
}


Toolbar::~Toolbar()
{
	this->removeFromUpdateTimer();
}


void Toolbar::setImageList( ImageList* imageList )
{
	imageList_ = imageList;
	toolbarPeer_->setImageList( imageList );
}

void Toolbar::setShowButtonCaptions( const bool& val )
{
	showButtonCaptions_ = val;
	toolbarPeer_->showButtonCaptions( showButtonCaptions_ );

	Control* parent = getParent();
	if ( NULL != parent ) {
		parent->getContainer()->resizeChildren(NULL);
	}
}

void Toolbar::setButtonSize( const Size& buttonSize )
{
	buttonSize_ = buttonSize;
	toolbarPeer_->setButtonSize( buttonSize_ );

	Control* parent = getParent();
	if ( NULL != parent ) {
		parent->getContainer()->resizeChildren(NULL);
	}
}

void Toolbar::setButtonCaptionsHorizontal( const bool& val )
{
	buttonCaptionsHorizontal_ = val;

	toolbarPeer_->setButtonCaptionPlacementHorizontal( val );

	Control* parent = getParent();
	if ( NULL != parent ) {
		parent->getContainer()->resizeChildren(NULL);
	}
}

void Toolbar::handleEvent( Event* event )
{
	Control::handleEvent( event );
	switch ( event->getType() ){
		/*
		case Component::COMPONENT_NEEDS_UPDATING : {
			ToolbarModel* model = getToolbarModel();
			if ( NULL != model ) {
				Enumerator<ToolbarItem*>* items = model->getToolbarItems();
				while ( items->hasMoreElements() ) {
					ToolbarItem* item = items->nextElement();
					item->handleEvent( event );
				}
			}
		}
		break;
		*/

		case CONTROL_SIZED:{
			Control::handleEvent( event );
			if ( getParent() ) {
				getParent()->getContainer()->resizeChildren( NULL );
			}
		}
		break;
	}
}

void Toolbar::paint( GraphicsContext* context )
{
	Rect innerBounds = getClientBounds( true );
	BackgroundState bkg;
	bkg.setEnabled( isEnabled() );
	bkg.setActive( isActive() );
	bkg.colorType_ = SYSCOLOR_FACE;	
	
	context->drawThemeBackground( &innerBounds, bkg );	
}

void Toolbar::setEnableAutoResize( const bool& val )
{
	toolbarPeer_->setEnableAutoResize( val );
}

bool Toolbar::isAutoResizeEnabled()
{
	return toolbarPeer_->isAutoResizeEnabled();
}







//******************************************************************************
//Toolbar::FloatingToolbar
//******************************************************************************


Toolbar::FloatingToolbar::FloatingToolbar()
{
	this->setFrameStyle( fstToolbarBorderFixed );
}

Toolbar::FloatingToolbar::~FloatingToolbar()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:56  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.4  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.3  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.3.2.2  2005/04/11 17:04:51  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.3.2.1  2005/01/07 01:13:58  ddiego
*fixed a foundation kit but that was cause a crash by releasing the system instance and then making use of a member variable for it. The member variable is now static, which is more appropriate.
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
*Revision 1.2.2.1  2004/09/06 21:30:20  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/14 04:56:01  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.4  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.3  2004/07/08 15:08:05  ddiego
*made the change to the StandardContainer name - the
*old StandardContainer is now called DesignTimeContainer and
*the old FixedStandardContainer is now renamed to StandardContainer.
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.27  2004/04/03 15:48:45  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.26.2.1  2004/02/12 14:55:45  marcelloptr
*minor fix: warning eliminated of unsafe mix of types in operation
*
*Revision 1.26  2003/12/19 15:05:24  ddiego
*addded a minor little fix to toolbar code.
*
*Revision 1.25  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.24.4.6  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.24.4.5  2003/12/02 22:11:30  ddiego
*some minor changes to support Actions. Still not done yet.
*
*Revision 1.24.4.4  2003/12/02 05:50:06  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.24.4.3  2003/12/01 03:44:13  ddiego
*added some fixes to the Win32Toolbar impl. A few minor changes to the
*toolbar example (which also got added). Some minor changes to docs
*as well.
*
*Revision 1.24.4.2  2003/10/31 05:06:38  ddiego
*added toolbar impl
*
*Revision 1.24.4.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.24  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.23.2.3  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.23.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.23.2.1  2003/03/12 03:13:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.23  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.22.2.2  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.22.2.1  2002/12/27 23:05:10  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.22  2002/11/18 00:46:10  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.21  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.20.4.2  2002/04/27 15:52:52  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.20.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.20  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


