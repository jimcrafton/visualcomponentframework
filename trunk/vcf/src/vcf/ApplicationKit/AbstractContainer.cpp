//AbstractContainer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractContainer.h"
#include <algorithm>

using namespace VCF;



AbstractContainer::AbstractContainer():
	controlContainer_(NULL),
	currentTabControlIndex_(0),
	controlHandler_(NULL),
	mouseHandler_(NULL)
{
	init();
}

AbstractContainer::AbstractContainer( Component* owner ):
	Container(owner),
	controlContainer_(NULL),
	currentTabControlIndex_(0),
	controlHandler_(NULL),
	mouseHandler_(NULL)
{
	init();
}

AbstractContainer::~AbstractContainer()
{
	if ( NULL != controlContainer_ ){
		controlContainer_->ControlSized -= controlHandler_;

		controlContainer_->MouseDoubleClicked -= mouseHandler_;
		controlContainer_->MouseClicked -= mouseHandler_;
		controlContainer_->MouseMove -= mouseHandler_;
		controlContainer_->MouseUp -= mouseHandler_;
		controlContainer_->MouseDown -= mouseHandler_;
		controlContainer_->MouseLeave -= mouseHandler_;
		controlContainer_->MouseEnter -= mouseHandler_;
	}

	controls_.clear();
}

void AbstractContainer::containerResized( ControlEvent* event )
{
	resizeChildren( NULL );
}

/**
*Translate points to screen coords
*Translate points back to client coords
*for each child, pass the event to it's process mouse event
*/
void AbstractContainer::onMouseEvent( MouseEvent* event )
{
	Control* previousMouseEnteredChild = Control::getPreviousMouseOverControl();
	Point tmp(0.0,0.0);
	tmp = *event->getPoint();
	//check for scollable to get rid of it's offsets
	Scrollable* scrollable = getContainerControl()->getScrollable();
	if ( NULL != scrollable ) {
		tmp.x_ -= scrollable->getHorizontalPosition();
		tmp.y_ -= scrollable->getVerticalPosition();
	}


	Rect childBounds;


	Control* capturedControl = Control::getCapturedMouseControl();
	if ( NULL != capturedControl ){
		Control* container = getContainerControl();

		Control* parent = capturedControl->getParent();
		if ( parent == container ){ //then the captured control is a child of this container so keep sedning it the messages
			childBounds = capturedControl->getBounds();
			//if ( true == childBounds->containsPt( &tmp ) ){
				capturedControl->translateToLocal( &tmp );
				MouseEvent localEvent( capturedControl, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
				capturedControl->handleEvent( &localEvent );
				event->setConsumed(true);//localEvent.isConsumed());
			//}
		}
	}
	else {
		std::vector<Control*>::reverse_iterator it = controls_.rbegin();

		while ( it != controls_.rend() ){
			Control* child = *it;

			if ( NULL == child ) {
				throw RuntimeException (MAKE_ERROR_MSG_2(INVALID_POINTER_ERROR)) ;
			}


			childBounds = child->getBounds();
			if ( Control::MOUSE_LEAVE == event->getType() ) {
				if ( (false == childBounds.containsPt( &tmp )) && (child->isLightWeight() && child->getVisible()) ){
					if ( (NULL != previousMouseEnteredChild) && (previousMouseEnteredChild == child) ) {
						//if ( child->isLightWeight() ){
						child->translateToLocal( &tmp );
						MouseEvent localEvent( child, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
						child->handleEvent( &localEvent );

						event->setConsumed(true);//localEvent.isConsumed());
						break;
					}
				}
			}
			else if ( Control::MOUSE_ENTERED == event->getType() ) {
				Rect tmpRect = child->getBounds();
				tmpRect.inflate( 2, 2 );
				if ( (tmpRect.containsPt( &tmp )) && (child->isLightWeight() && child->getVisible()) ){
					Control::setPreviousMouseOverControl( child );
					child->translateToLocal( &tmp );
					MouseEvent localEvent( child, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
					child->handleEvent( &localEvent );

					event->setConsumed(true);//localEvent.isConsumed());
					break;
				}
			}
			else {
				if ( (true == childBounds.containsPt( &tmp )) && (child->isLightWeight() && child->getVisible()) ){
					child->translateToLocal( &tmp );
					if ( Control::MOUSE_MOVE == event->getType() ) {
						if ( child != previousMouseEnteredChild ) {
							if ( NULL != previousMouseEnteredChild ) {
								Point tmp2 = *event->getPoint();
								previousMouseEnteredChild->translateToLocal( &tmp2 );
								MouseEvent localEvent( previousMouseEnteredChild, Control::MOUSE_LEAVE, event->getButtonMask(), event->getKeyMask(), &tmp2 );
								previousMouseEnteredChild->handleEvent( &localEvent );
							}
							Control::setPreviousMouseOverControl( child );
							previousMouseEnteredChild = Control::getPreviousMouseOverControl();
							if ( NULL != previousMouseEnteredChild ) {
								Point tmp2 = *event->getPoint();
								child->translateToLocal( &tmp2 );
								MouseEvent localEvent( child, Control::MOUSE_ENTERED, event->getButtonMask(), event->getKeyMask(), &tmp2 );
								child->handleEvent( &localEvent );
							}
						}
					}


					if ( event->getType() != Control::MOUSE_CLICK ) {
						MouseEvent localEvent( child, event->getType(), event->getButtonMask(), event->getKeyMask(), &tmp );
						child->handleEvent( &localEvent );
						event->setConsumed(true);//localEvent.isConsumed());
					}
					break;
				}
				else if ( (Control::MOUSE_MOVE == event->getType()) && (child == previousMouseEnteredChild) ) {
					Point tmp2 = *event->getPoint();
					previousMouseEnteredChild->translateToLocal( &tmp2 );
					MouseEvent localEvent( previousMouseEnteredChild, Control::MOUSE_LEAVE, event->getButtonMask(), event->getKeyMask(), &tmp2 );
					previousMouseEnteredChild->handleEvent( &localEvent );
					Control::setPreviousMouseOverControl( NULL );
				}
			}

			it ++;
		}
	}
}




void AbstractContainer::init()
{
	currentTabControlIndex_ = 0;


	controlHandler_ =
		new ControlEventHandler<AbstractContainer>( this, &AbstractContainer::containerResized,
													"AbstractContainer::containerResized");

	mouseHandler_ =
		new MouseEventHandler<AbstractContainer>( this,&AbstractContainer::onMouseEvent,
													"AbstractContainer::onMouseEvent");

	controlContainer_ = NULL;
	controlsContainer_.initContainer( controls_ );
}

void AbstractContainer::add( Control * child )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	//verify we don't already have this control
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}

		child->setParent( controlContainer_ );

		controls_.push_back( child );

		child->setTabOrder( controls_.size() - 1 );
		resizeChildren( child );
	}
}

void AbstractContainer::add( Control * child, const AlignmentType& alignment )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}

		child->setParent( controlContainer_ );
		child->setAlignment( alignment );

		controls_.push_back( child );

		child->setTabOrder( controls_.size() - 1 );
		resizeChildren( child );
	}
}

void AbstractContainer::remove( Control* child )
{
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );
	if ( found != controls_.end() ){
		controls_.erase( found );

		child->setParent( NULL );

		resizeChildren(NULL);

		std::map<long,Control*>::iterator it = tabOrderMap_.begin();
		while ( it != tabOrderMap_.end() ) {
			if ( child == it->second ) {
				tabOrderMap_.erase( it );
				break;
			}
			it ++;
		}
	}
}

void AbstractContainer::clear()
{
	controls_.clear();
	tabOrderMap_.clear();
	resizeChildren(NULL);
}


void AbstractContainer::paintChildren( GraphicsContext* context ){

	Enumerator<Control*>* children = controlsContainer_.getEnumerator();
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};

	double originX = 0.0;
	double originY = 0.0;

	Scrollable* scrollable = controlContainer_->getScrollable();

	Rect oldClipRect = context->getClippingRect();
	Rect mainBounds;
	if ( controlContainer_->getParent() ) {
		mainBounds = controlContainer_->getBounds();
		mainBounds.offset( -controlContainer_->getLeft(), -controlContainer_->getTop() );
	}
	else {
		mainBounds = controlContainer_->getClientBounds();
	}

	Rect childClipRect;
	Rect bounds;


	while ( true == children->hasMoreElements() ){
		Control* child = children->nextElement();
		VCF_ASSERT( NULL != child );

		if ( child->isLightWeight() && child->getVisible() ){
			bounds = child->getBounds();

			childClipRect.left_ = maxVal<>(bounds.left_,mainBounds.left_);
			childClipRect.top_ = maxVal<>(bounds.top_,mainBounds.top_);
			childClipRect.right_ = minVal<>(bounds.right_,mainBounds.right_);
			childClipRect.bottom_ = minVal<>(bounds.bottom_,mainBounds.bottom_);

			childClipRect.offset( -bounds.left_, -bounds.top_ );

			Point oldOrigin = context->getOrigin();
			originX = bounds.left_ + oldOrigin.x_;
			originY = bounds.top_ + oldOrigin.y_;
			if ( NULL != scrollable ) {
				originX += 	scrollable->getHorizontalPosition();
				originY += 	scrollable->getVerticalPosition();
			}


			context->setOrigin( originX, originY );


			//do this to prevent matrix changes from
			//screwing up the state for the child control
			Matrix2D xfrm;
			int gcs = context->saveState();
			context->setCurrentTransform( xfrm );
			context->setClippingRect( &childClipRect );

			child->paintBorder( context );

			child->paint( context );

			context->restoreState( gcs );


			context->setOrigin( oldOrigin.x_, oldOrigin.y_ );
			context->setClippingRect( &oldClipRect );
		}
	}
}

Enumerator<Control*>* AbstractContainer::getChildren()
{
	return controlsContainer_.getEnumerator();
}

unsigned long AbstractContainer::getChildCount()
{
	return controls_.size();
}


Control* AbstractContainer::findControl( const String& controlName )
{
	Control* result = NULL;
	//this is very slow !! for the moment !
	std::vector<Control*>::iterator it = controls_.begin();
	bool notFound = true;
	while ( it != controls_.end() ){
		Control* child = *it;
		if ( controlName == child->getName() ){
			result = child;
			break;
		}
		it ++;
	}

	return result;
}

void AbstractContainer::updateTabOrder( Control* child, ulong32& newTabOrder )
{
	long currentTabOrder = child->getTabOrder();
	if ( newTabOrder >= 0 ) {

		if ( newTabOrder > tabOrderMap_.size() ) {
			newTabOrder = tabOrderMap_.size() - 1;
		}
		else if ( newTabOrder < 0 ) {
			newTabOrder = 0;
		}
		std::map<long,Control*>::iterator found = tabOrderMap_.find( currentTabOrder );
		if ( found != tabOrderMap_.end() ) {
			tabOrderMap_.erase( found );
		}

		tabOrderMap_[newTabOrder] = child;
	}
}

void AbstractContainer::getTabList( std::vector<Control*>& tabList )
{
	std::map<long,Control*>::iterator it = tabOrderMap_.begin();
	while ( it != tabOrderMap_.end() ) {
		Control::buildTabList( it->second, tabList );
		it ++;
	}
}


Control* AbstractContainer::getControlAtIndex( const ulong32& index )
{
	Control* result = NULL;

	if ( index < controls_.size() ) {
		std::vector<Control*>::iterator found = controls_.begin() + index;
		if ( found != controls_.end() ) {
			result = *found;
		}
	}

	return result;
}

long AbstractContainer::getControlIndex( Control* control )
{
	long result = -1;

	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );
	if ( found != controls_.end() ) {
		result = found - controls_.begin();
	}

	return result;
}

void AbstractContainer::insertBeforeControl( Control * child, const AlignmentType& alignment, Control* beforeControl )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	std::vector<Control*>::iterator insertAt = std::find( controls_.begin(), controls_.end(), beforeControl );

	//the control is not present
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}
	}
	else { // OK we already have this child so remove it first before changing it's position in the list
		controls_.erase( found );
	}



	child->setParent( controlContainer_ );
	child->setAlignment( alignment );
	child->setTabOrder( controls_.size()/*-1*/ );

	resizeChildren( child );

	if ( insertAt != controls_.end() ) {
		controls_.insert( insertAt, child );
	}
	else {
		controls_.insert( controls_.begin(), child );
	}
}

void AbstractContainer::insertAtIndex( Control * child, const AlignmentType& alignment, const ulong32& index )
{
	if ( NULL == controlContainer_ ){
		throw InvalidPointerException(MAKE_ERROR_MSG(INVALID_POINTER_ERROR), __LINE__);
	};
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	std::vector<Control*>::iterator insertAt = controls_.begin() + index;

	//the control is not present
	if ( found == controls_.end() ) {
		//check for a previous parent, if found then remove it from the parent !
		Control* parent = child->getParent();
		if ( NULL != parent ) {
			Container* parentContainer = parent->getContainer();
			if ( NULL != parentContainer ) {
				parentContainer->remove( child );
			}
		}
	}
	else { // OK we already have this child so remove it first before changing it's position in the list
		controls_.erase( found );
	}



	child->setParent( controlContainer_ );
	child->setAlignment( alignment );
	child->setTabOrder( controls_.size()/*-1*/ );

	resizeChildren( child );

	if ( insertAt != controls_.end() ) {
		controls_.insert( insertAt, child );
	}
	else {
		controls_.push_back( child );
	}
}

void AbstractContainer::sendControlToFront( Control* child )
{
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	if ( found != controls_.end() ) {
		controls_.erase( found );
		controls_.insert( controls_.begin(), child );
		resizeChildren(NULL);
	}
	else {
		throw NoSuchElementException();
	}
}

void AbstractContainer::sendControlToBack( Control* child )
{
	std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), child );

	if ( found != controls_.end() ) {
		controls_.erase( found );
		controls_.push_back( child );
		resizeChildren(NULL);
	}
	else {
		throw NoSuchElementException();
	}
}

void AbstractContainer::setContainerControl( Control* control )
{
	if ( NULL != controlContainer_ ){
		controlContainer_->ControlSized -= controlHandler_;

		controlContainer_->MouseDoubleClicked -= mouseHandler_;
		controlContainer_->MouseClicked.removeHandler( mouseHandler_ );
		controlContainer_->MouseMove.removeHandler( mouseHandler_ );
		controlContainer_->MouseUp.removeHandler( mouseHandler_ );
		controlContainer_->MouseDown.removeHandler( mouseHandler_ );
		controlContainer_->MouseLeave.removeHandler( mouseHandler_ );
		controlContainer_->MouseEnter.removeHandler( mouseHandler_ );
	}
	controlContainer_ = control;
	controlContainer_->ControlSized.addHandler( controlHandler_ );

	controlContainer_->MouseDoubleClicked.addHandler( mouseHandler_ );
	controlContainer_->MouseClicked.addHandler( mouseHandler_ );
	controlContainer_->MouseMove.addHandler( mouseHandler_ );
	controlContainer_->MouseUp.addHandler( mouseHandler_ );
	controlContainer_->MouseDown.addHandler( mouseHandler_ );
	controlContainer_->MouseLeave.addHandler( mouseHandler_ );
	controlContainer_->MouseEnter.addHandler( mouseHandler_ );
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.2.5  2005/06/25 22:19:34  marcelloptr
*[bugfix 1227549] HorizontalLayoutContainer set the heights in the wrong rows.
*AbstractContainer::add() needs to resizeChildren *after* the child control has been added.
*
*Revision 1.4.2.3  2005/04/20 02:25:59  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.4.2.2  2005/03/14 04:17:22  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.4.2.1  2005/03/06 22:50:58  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.4  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3  2004/08/19 02:24:53  ddiego
*fixed bug [ 1007039 ] lightweight controls do not paint correctly.
*
*Revision 1.2.2.6  2004/11/15 05:41:27  ddiego
*finished almost all the osx menu code except for custom drawing. This completes this releases osx effort.
*
*Revision 1.2.2.5  2004/09/09 03:09:22  marcelloptr
*minor change for style
*
*Revision 1.2.2.4  2004/09/08 03:49:05  ddiego
*minor win32 tree mods
*
*Revision 1.2.2.3  2004/09/06 21:30:18  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2.2.2  2004/09/03 04:05:46  ddiego
*fixes to add matrix transform support for images.
*
*Revision 1.2.2.1  2004/08/19 03:22:53  ddiego
*updates so new system tray code compiles
*
*Revision 1.3  2004/08/19 02:24:53  ddiego
*fixed bug [ 1007039 ] lightweight controls do not paint correctly.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/12 02:05:45  ddiego
*fixed a subtle bug (that only showed up when using a lightweight
*control) that happened with MouseClick events being handled twice.
*
*Revision 1.1.2.3  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.48  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.47  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.46.2.1  2004/01/19 23:32:06  ddiego
*Revision 1.46  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.45.2.7  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.45.2.6  2003/10/20 03:40:13  ddiego
* made some minor changes fixed a bug in color where we forget to actually
*assign hls/hsv values.
*
*Revision 1.45.2.5  2003/10/12 06:34:13  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.45.2.4  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.45.2.3  2003/09/02 02:11:13  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.45.2.2  2003/08/27 20:11:33  ddiego
*adjustments to how hte DataObject class work and copy/paste
*
*Revision 1.45.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.45  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.44.2.2  2003/08/01 00:49:25  ddiego
*added a fix for popup windows that also fixed a problem with the
*ComboBoxControl drop down list disapearing.
*
*Revision 1.44.2.1  2003/06/13 03:06:39  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.44  2003/05/17 20:37:44  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.43.2.3  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.43.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.43.2.1  2003/03/12 03:12:53  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.43  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.42.2.7  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.42.2.6  2003/02/02 04:56:40  ddiego
*fixed a bug in AbstractX11Control::getBounds() that was incorrectly setting the bounds reported
*by XGetGeometry - the error was due to adding a negative int and an unsigned int together! Ooops
*The problem was manifewsting itself in the TabbedPages control with it's scroll buttons.
*Changed PushButton to be a heavyweight control
*
*Revision 1.42.2.5  2003/01/08 00:19:56  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.42.2.4  2003/01/02 04:07:47  ddiego
*adding more event support, plus added further Font implementation
*
*Revision 1.42.2.3  2002/12/27 23:04:58  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.42.2.2  2002/12/25 22:06:32  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.42.2.1  2002/12/02 00:38:36  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.42  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.41.4.3  2002/10/04 05:02:55  ddiego
*added beggining support for add new classes. Basic GUI is now in place.
*Also preliminary support for class templates and class wizards
*some documentation done on the format for the XML based class template
*
*Revision 1.41.4.2  2002/09/30 02:16:52  ddiego
*misc piddling
*
*Revision 1.41.4.1  2002/09/24 21:02:37  ddiego
*started to work on fixing up the tabbedpages control
*
*Revision 1.41  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.40.6.1  2002/07/26 04:24:29  ddiego
*added more support for properly querying modified document, and removing the
*documents from the doc tab pages, made some changes in TabbedPages to support
*this as well
*
*Revision 1.40  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.39  2002/03/22 04:30:18  ddiego
*bug fixes for weird resizing of win32 common controls (it figures) with the
*new code I put in yesterday. Put back the old code and it seems to work OK.
*Sigh...
*
*Revision 1.38  2002/03/21 01:36:36  ddiego
*fix [ 532623 ] alignment problem & [ 525214 ] alignment loss after resize JEC 20-03-2002
*there was an incorrect comparison being done in AbstractContainer::insertBefore() that
*was resulting in controls being respositioned in the incorrect order. Should be cool now.
*

*Revision 1.37  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.36  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


