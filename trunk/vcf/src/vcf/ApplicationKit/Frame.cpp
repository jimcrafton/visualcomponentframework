//Frame.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Containers.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;

Frame* Frame::currentActiveFrame = NULL;



Frame::State::State()
{
	
}


void Frame::State::applyState( Frame* frame )
{
	frame->setBounds( &bounds_ );
	frame->setVisible( visible_ );
	Window* window = dynamic_cast<Window*>( frame );
	if ( NULL != window ) {
		switch ( displayState_ ) {
			case Frame::State::fdsMaximized : {
				window->setMaximized( true );
			}
			break;

			case Frame::State::fdsMinimized : {
				window->setMinimized( true );
			}
			break;
		}
	}
}

void Frame::State::initState( Frame* frame )
{
	bounds_ = frame->getBounds();
	visible_ = frame->getVisible();
	displayState_ = Frame::State::fdsNormal;

	Window* window = dynamic_cast<Window*>( frame );
	if ( NULL != window ) {
		if ( window->isMaximized() ) {
			displayState_ = Frame::State::fdsMaximized;
		}
		else if ( window->isMinimized() ) {
			displayState_ = Frame::State::fdsMinimized;
		}
	}
}

void Frame::State::loadFromStream( InputStream* stream )
{
	stream->read( static_cast<Persistable*>(&bounds_) );
	stream->read( visible_ );
	long state;
	stream->read( state );
	displayState_ = (Frame::State::FrameDisplayState)state;
}

void Frame::State::saveToStream( OutputStream* stream )
{
	stream->write( &bounds_ );
	stream->write( visible_ );
	stream->write( displayState_ );
}




Frame::Frame():
	frameStyle_(fstSizeable),
	isTopmostFrame_(false),
	useColorForBackground_(false),
	allowFrameAsChildControl_(false)
{
	setContainerDelegate( this );
	setContainer( new StandardContainer() );	
}

Frame::~Frame()
{

}

void Frame::destroy()
{
	if ( Frame::currentActiveFrame == this ) {
		Frame::currentActiveFrame = NULL;
	}

	Control::destroy();
}

void Frame::paint( GraphicsContext * context )
{
	if ( NULL != getView() ) {
		getView()->paintView( context );
	}
	else {	

		Rect innerBounds = getClientBounds(false);
/*
		if ( NULL != border ){
			border->paint( this, context );
			Rect tmpBounds = border->getClientRect( &innerBounds, this );
			innerBounds = tmpBounds;
			innerBounds.inflate( -1, -1 );
		}
		*/

		
		
		if ( useColorForBackground_ ) {
			context->setColor( getColor() );
		
			context->rectangle( innerBounds.left_, innerBounds.top_, innerBounds.right_, innerBounds.bottom_ );
		
			context->fillPath();		
		}
		else {	
			BackgroundState bkg;
			bkg.setEnabled( isEnabled() );
			bkg.setActive( (this == Frame::getActiveFrame()) && isActiveFrame() );
			bkg.colorType_ = SYSCOLOR_WINDOW;	
			
			context->drawThemeBackground( &innerBounds, bkg );
		}
		


		context->setCurrentFont( getFont() );

		Scrollable* scrollable = getScrollable();
		if ( scrollable ) {
			Rect viewBounds = context->getViewableBounds();

			Point origin = context->getOrigin();

			adjustViewableBoundsAndOriginForScrollable( context, viewBounds, origin );

			context->setOrigin( origin );

			context->setViewableBounds( viewBounds );
		}
	}

	paintChildren( context );
}

void Frame::show()
{	
	setVisible( true );
	repaint();

	activate();
}

void Frame::hide()
{
	setVisible( false );
}

void Frame::setCaption( const String& caption )
{
	caption_ = caption;
}

String Frame::getCaption()
{
	return caption_;
}

bool Frame::isFrameTopmost()
{
	return isTopmostFrame_;
}

void Frame::setFrameTopmost( const bool& isTopmost )
{
	isTopmostFrame_ = isTopmost;
}


void Frame::setIsActive( const bool& active )
{


}

void Frame::activate()
{
	if ( false == allowsActivation() ) {
		return;
	}

	if ( this->isDesigning() ) {
		return;
	}
	

	if ( this != Frame::currentActiveFrame ) {

		
		Frame* oldActiveFrame = Frame::currentActiveFrame;

		Frame::currentActiveFrame = this;


		if ( (NULL != oldActiveFrame) && (this != oldActiveFrame) ) {

			
			if ( oldActiveFrame->getComponentState() == Component::csNormal ) {
				
				VCF::WindowEvent event( oldActiveFrame, Frame::ACTIVATION_EVENT );

				//StringUtils::trace( Format( "oldActiveFrame->FrameActivation.fireEvent, this[%s]@ %s\n" ) %
				//					oldActiveFrame->getClassName() % oldActiveFrame->toString() );

				oldActiveFrame->FrameActivation.fireEvent( &event );
			}
		}

		if ( getComponentState() == Component::csNormal ) {
			
			VCF::WindowEvent event( this, Frame::ACTIVATION_EVENT );
			FrameActivation.fireEvent( &event );
		}
	}
}

bool Frame::isActive()
{
	return (this == Frame::currentActiveFrame) && (isActiveFrame());
}

Frame* Frame::getActiveFrame()
{
	/*
	StringUtils::trace( Format( "Frame::getActiveFrame(): %p\n" ) % Frame::currentActiveFrame );
	Control* c = Control::getCurrentFocusedControl();
	StringUtils::trace( Format( "Control::getCurrentFocusedControl(): %p\n" ) % c );

	if ( NULL == Frame::currentActiveFrame ) {
		Frame::currentActiveFrame = c->getParentFrame();
	}
	*/
	return Frame::currentActiveFrame;
}

void Frame::internal_setActiveFrame( Frame* activeFrame )
{
	Frame::currentActiveFrame = activeFrame;
}

void Frame::afterCreate( ComponentEvent* event )
{
	Control::afterCreate( event );	
}

bool Frame::allowClose()
{
	bool result = false;
	FrameEvent event( this, CLOSING_EVENT );
	FrameClosing.fireEvent( &event );
	result = event.isOkToClose();

	return result;
}

Dialog* Frame::createDialog( Class* dialogClazz, ResourceBundle* resBundle )
{
	Dialog* result = NULL;

	result = (Dialog*)Component::createComponentFromResources( dialogClazz, classid(VCF::Dialog), resBundle );

	return result;
}

Window* Frame::createWindow( Class* windowClazz, ResourceBundle* resBundle )
{
	Window* result = NULL;

	result = (Window*)Component::createComponentFromResources( windowClazz, classid(VCF::Window), resBundle );

	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.6  2005/10/11 00:54:51  ddiego
*added initial changes for grayscale image support. fixed some minor changes to form loading and creating.
*
*Revision 1.4.2.5  2005/09/18 22:54:47  ddiego
*fixed some minor bugs in vffinput stream and parser class.
*
*Revision 1.4.2.4  2005/09/16 01:12:01  ddiego
*fixed bug in component loaded function.
*
*Revision 1.4.2.3  2005/08/24 05:03:21  ddiego
*better component loading and creation functions.
*
*Revision 1.4.2.2  2005/08/05 01:11:38  ddiego
*splitter fixes finished.
*
*Revision 1.4.2.1  2005/08/01 18:50:31  marcelloptr
*minor changes
*
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/06/06 02:34:06  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/23 13:53:12  marcelloptr
*comments for setUseColorForBackground; setActiveFrame renamed as internal
*
*Revision 1.2.2.1  2004/09/06 21:30:19  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/30 17:27:13  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.4  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.27  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.26  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.24.2.2  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.24.2.1  2004/01/15 05:35:04  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.24  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.23.2.5  2003/10/13 04:02:52  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.23.2.4  2003/10/05 16:43:02  ddiego
*fixed a glitch in the cut handling of a Document - it was calling
*empty() by default - not exactly nice behaviour.
*
*Revision 1.23.2.3  2003/09/25 04:00:27  ddiego
*minor fixes to better adjust the voewable bounds when scrolling is enabled
*added a Scrolling example
*
*Revision 1.23.2.2  2003/09/05 21:03:21  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.23.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.23  2003/08/09 02:56:45  ddiego
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
*Revision 1.22.2.6  2003/08/01 00:49:26  ddiego
*added a fix for popup windows that also fixed a problem with the
*ComboBoxControl drop down list disapearing.
*
*Revision 1.22.2.5  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.22.2.4  2003/06/13 03:06:40  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.22.2.3  2003/06/09 03:57:16  ddiego
*fixed an issue with tooltip not showing up, and while fixing that found it
*accidentally caused another problem with application focus for the main
*window not being handled correctly. This is now working OK! Now just
*have to get rid of the dialog flicker...
*Also fixed the QTPlayer example. It had some syntax errors from using the older
*event macros (not using Delegates)
*
*Revision 1.22.2.2  2003/06/05 03:48:55  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.22.2.1  2003/05/27 04:45:40  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.22  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.21.2.4  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.21.2.3  2003/04/17 04:29:53  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.21.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.21.2.1  2003/03/12 03:13:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.21  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.20.2.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.20.2.3  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.20.2.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20.2.1  2002/12/27 23:05:02  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.19.4.1  2002/10/01 20:34:59  ddiego
*borders
*
*Revision 1.19  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.18.6.2  2002/09/10 04:07:51  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.18.6.1  2002/08/13 04:28:23  ddiego
*bugs fixed:
*[ 585085 ] Can't get at multi selected filenames - this was just a matter of exposing a function that was already available in the
*peer class
*
*features:
*58839 Add a method to query closing a Frame, this required a change that included added a new event (FrameEvent and the corresponding
*FrameEventHandler) and a method, bool Frame::allowClose()
*
*Also made fixes in the VCF Builder to now take advantage of this, so the MainWindow class will now register an event
*handler to handler the FrameClosing event, and attempt to set the current workspace to NULL. If this does not happen then
*the closing event will fail and prevent the widnow from being shutdown. Woo hoo !
*
*Revision 1.18  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.17  2002/03/31 19:54:33  ddiego
*fixed a release bug in the TreeListControl
*made sure that saving the state of a Frame works correctly
*
*Revision 1.16.4.1  2002/04/27 15:52:49  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.16  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.15  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


