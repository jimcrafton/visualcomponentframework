#ifndef _VCF_CONTROL_H__
#define _VCF_CONTROL_H__
//Control.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


class Rect;
class Color;
class Border;
class Font;
class ControlPeer;
class GraphicsContext;
class ControlGraphicsContext;
class PopupMenu;
class Scrollable;
class Cursor;
class Model;
class AcceleratorKey;
class Container;
class Frame;

#define CONTROL_CLASSID		"B91B1828-3639-4bcf-9882-342F16C90E21"


/**
 The base class for all visual components in the Visual Component Framework.
 In addition it implements the View interface. This means that the
 Control is itself a specialized form of a View, though it may not have
 have a model, and can hold an external view, separate from itself.
 In addition a control receives a wide variety of events from the user
 such as paint events, mouse events, keyboard events, help events, etc.
 Controls can have parents, thus form a hierarchy of parent-child relationships.
 Controls can also have children if they implement the Container interface.
 Controls can also be aligned or anchored, which can aid in laying out the
 presentation of a UI.
 Finally a Control may also be lightweight or heavyweight, which determines
 how many  window system resources the control consumes. A heavyweight control
 has a native window/widget and takes up resources accordingly. In addition a
 heavyweight control also has a native graphics context associated with it that
 also takes up resources. In contrast, a lightweight control shares the underlying
 native window and graphics context resources with it's parent, and greatly
 reduces the number of resources the application will consume. This is especially
 useful when making complex custom controls that have many moving parts like a tree-list
 control, complete with a header and movable icons, etc.
 To aid in the drawing of a control, all controls are double buffered by default
 to prevent flicker, though this can be turned off and on at will.
 @delegates
	@del Control::ControlSized
	@del Control::ControlPositioned
	@del Control::ControlParentChanged
	@del Control::MouseDoubleClicked
	@del Control::MouseClicked
	@del Control::MouseMove
	@del Control::MouseUp
	@del Control::MouseDown
	@del Control::MouseEnter
	@del Control::MouseLeave
	@del Control::KeyPressed
	@del Control::KeyDown
	@del Control::KeyUp
	@del Control::ControlHelpRequested
	@del Control::HelpRequested
	@del Control::FocusLost
	@del Control::FocusGained
	@del Control::ToolTipRequested
	@del Control::ToolTip
	@del Control::ControlModelChanged
 */
class APPLICATIONKIT_API Control : public Component, public AbstractView {
public:
	//Anchor delta enums
	enum {
		ANCHOR_DTOP = 0,
		ANCHOR_DLEFT,
		ANCHOR_DBOTTOM,
		ANCHOR_DRIGHT
	};

	enum ControlEvents {
		CONTROL_EVENTS = COMPONENT_EVENTS_LAST + 200,
		CONTROL_SIZED,
		CONTROL_POSITIONED,
		CONTROL_PARENT_CHANGED,
		CONTROL_MODELCHANGED,
		FOCUS_GAINED,
		FOCUS_LOST,
		HELP_REQUESTED,
		WHATS_THIS_HELP_REQUESTED,
		KEYBOARD_DOWN,
		KEYBOARD_PRESSED,
		KEYBOARD_UP,
		KEYBOARD_ACCELERATOR,
		MOUSE_DOWN,
		MOUSE_MOVE,
		MOUSE_UP,
		MOUSE_CLICK,
		MOUSE_DBLCLICK,
		MOUSE_ENTERED,
		MOUSE_LEAVE,
		CONTROL_EVENTS_LAST
	};


	Control();
	virtual ~Control();

	/**
	@delegate ControlSized fires an ControlEvent, with a type set to Control::CONTROL_SIZED.
	Fired whenever the control's width or height changes. Calls to setBounds(), setHeight(), or
	setWidth() can trigger this.
	@event ControlEvent
	@eventtype Control::CONTROL_SIZED
	*/
	DELEGATE(ControlSized);

	/**
	@delegate ControlPositioned fires an ControlEvent, with a type set to Control::CONTROL_POSITIONED.
	Fired whenever the control's position (top or left coordinates) changes. Calls to setBounds(), setLeft(), or
	setTop() can trigger this.
	@event ControlEvent
	@eventtype Control::CONTROL_POSITIONED
	*/
	DELEGATE(ControlPositioned);

	/**
	@delegate ControlParentChanged fires an ControlEvent, with a type set to Control::CONTROL_PARENT_CHANGED.
	Fired whenever the control's parent changes. Calls to setParent() trigger this.
	@event ControlEvent
	@eventtype Control::CONTROL_PARENT_CHANGED
	*/
	DELEGATE(ControlParentChanged);

	/**
	@delegate MouseDoubleClicked fires an MouseEvent, with a type set to Control::MOUSE_DBLCLICK.
	Fired whenever the control receives a double click from the mouse. This is triggered by the
	underlying windowing system.
	@event MouseEvent
	@eventtype Control::MOUSE_DBLCLICK
	*/
	DELEGATE(MouseDoubleClicked);

	/**
	@delegate MouseClicked fires an MouseEvent, with a type set to Control::MOUSE_CLICK.
	Fired whenever the control receives a click from the mouse. This is triggered by the
	underlying windowing system.
	@event MouseEvent
	@eventtype Control::MOUSE_CLICK
	*/
	DELEGATE(MouseClicked);

	/**
	@delegate MouseMove fires an MouseEvent, with a type set to Control::MOUSE_MOVE.
	Fired whenever the control receives a move event from the mouse. This is triggered by the
	underlying windowing system.
	@event MouseEvent
	@eventtype Control::MOUSE_MOVE
	*/
	DELEGATE(MouseMove);

	/**
	@delegate MouseUp fires an MouseEvent, with a type set to Control::MOUSE_UP.
	Fired whenever the control receives notice that a mouse button has been released, or lifted up.
	This is triggered by the underlying windowing system.
	@event MouseEvent
	@eventtype Control::MOUSE_UP
	*/
	DELEGATE(MouseUp);

	/**
	@delegate MouseDown fires an MouseEvent, with a type set to Control::MOUSE_DOWN.
	Fired whenever the control receives notice a mouse button has been pressed down.
	This is triggered by the underlying windowing system.
	@event MouseEvent
	@eventtype Control::MOUSE_DOWN
	*/
	DELEGATE(MouseDown);

	/**
	@delegate MouseEnter fires an MouseEvent, with a type set to Control::MOUSE_ENTERED.
	Fired whenever the control receives notice the mouse has first entered the control's bounds.
	This is triggered by the underlying windowing system.
	@event MouseEvent
	@eventtype Control::MOUSE_ENTERED
	*/
	DELEGATE(MouseEnter);

	/**
	@delegate MouseLeave fires an MouseEvent, with a type set to Control::MOUSE_LEAVE.
	Fired whenever the control receives notice the mouse has left the control's bounds.
	This is triggered by the underlying windowing system.
	@event MouseEvent
	@eventtype Control::MOUSE_LEAVE
	*/
	DELEGATE(MouseLeave);

	/**
	@delegate KeyPressed fires an KeyboardEvent, with a type set to Control::KEYBOARD_PRESSED.
	Fired whenever the control receives a keypress. This is triggered by the
	underlying windowing system.
	@event KeyboardEvent
	@eventtype Control::KEYBOARD_PRESSED
	*/
	DELEGATE(KeyPressed);

	/**
	@delegate KeyDown fires an KeyboardEvent, with a type set to Control::KEYBOARD_DOWN.
	Fired whenever the control receives notice a key has been pressed down. This is triggered by the
	underlying windowing system.
	@event KeyboardEvent
	@eventtype Control::KEYBOARD_DOWN
	*/
	DELEGATE(KeyDown);

	/**
	@delegate KeyUp fires an KeyboardEvent, with a type set to Control::KEYBOARD_UP.
	Fired whenever the control receives notice a key has been released. This is triggered by the
	underlying windowing system.
	@event KeyboardEvent
	@eventtype Control::KEYBOARD_UP
	*/
	DELEGATE(KeyUp);

	/**
	@delegate ControlHelpRequested fires an WhatsThisHelpEvent, with a type set to Control::WHATS_THIS_HELP_REQUESTED.
	Fired whenever the control receives notice of a context sensitive help event.
	This is triggered by the underlying windowing system. On Win32 this is frequently triggered
	by right clicking on a control, and clicking on the "Whats This?" context menu item.
	@event WhatsThisHelpEvent
	@eventtype Control::WHATS_THIS_HELP_REQUESTED
	*/
	DELEGATE(ControlHelpRequested);

	/**
	@delegate HelpRequested fires an HelpEvent, with a type set to Control::HELP_REQUESTED.
	Fired whenever the control receives notice the F1 key (or some other acknowledged help key)
	has been pressed. This is triggered by the underlying windowing system.
	@event HelpEvent
	@eventtype Control::HELP_REQUESTED
	*/
	DELEGATE(HelpRequested);

	/**
	@delegate FocusGained fires an FocusEvent, with a type set to Control::FOCUS_GAINED.
	Fired whenever the control receives notice that it has become the focused control. This is
	triggered by the underlying windowing system.
	@event FocusEvent
	@eventtype Control::FOCUS_GAINED
	*/
	DELEGATE(FocusGained);

	/**
	@delegate FocusLost fires an FocusEvent, with a type set to Control::FOCUS_LOST.
	Fired whenever the control receives notice that it has lost focus. This is
	triggered by the underlying windowing system.
	@event FocusEvent
	@eventtype Control::FOCUS_LOST
	*/
	DELEGATE(FocusLost);

	/**
	@delegate ToolTipRequested fires an ToolTipEvent, with a type set to TOOLTIP_EVENT_TIP_REQESTED.
	This is fired if the VCF framework determines a tooltip can be displayed for this
	control, and no tootip text was defined for the control.
	@event ToolTipEvent
	@eventtype TOOLTIP_EVENT_TIP_REQESTED
	@see ToolTipEvent.h for more on TOOLTIP_EVENT_TIP_REQESTED #define
	@see ToolTipEvent
	*/
	DELEGATE(ToolTipRequested);

	/**
	@delegate ToolTip fires an ControlEvent.
	Fired by the framework when it determins a tooltip can be displayed for a control.
	Typically this is caused by hovering the mouse over a control for some fixed amount
	of time, usually determine by the underlying windowing system's setting.
	@event ToolTipEvent
	*/
	DELEGATE(ToolTip);

	/**
	@delegate ControlModelChanged fires an ControlEvent.
	Fired by the control when the control's setViewModel is called. This event
	indicates that the control's model pointer has changed, and anyone interested in
	listening to the control's model should update accordingly.
	@event ControlEvent
	@eventtype Control::CONTROL_MODELCHANGED
	*/
	DELEGATE(ControlModelChanged);

	

	/**
	This gets called by the ControlPeer for any windowing system mouse events,
	as well as for any windowing system keyboard events and for any
	windowing system events like size changes, position changes, etc.
	Once inside the event the Control determines the type, and behaves accordingly,
	as well as notifying any appropriate listeners.
	*/
	virtual void handleEvent( Event* event );

	/**
	calls handleEvent on this control, and then
	calls handleEventToChildren() on any child controls the
	container of this control may have.
	*/
	void handleEventAndForwardToChildren( Event* event );

	/**
	*Returns the control's current border object, if any
	*/
	Border* getBorder();

	/**
	\p
	Sets the border for this control. The control will check the
	border's owner value, and if it's NULL then it will set itself
	as the component owner of the border.
	*/
	void setBorder( Border* border );

	/**
	returns the bounds in parent coordinates of the Control. The Control derived class must call it's Peer's getBounds() method
	*/
	virtual Rect getBounds() ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	Returns the bounds in terms of the control's coordinates. Thus the top and
	left will typically be 0.0, 0.0, and the right and bottom of the bounds
	will typically equal the width and height of the control.
	*/
	virtual Rect getClientBounds( const bool& includeBorder = true ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	Returns the left position in parent coordinates
	*/
	virtual double getLeft() ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	Returns the right position in parent coordinates
	*/
	virtual double getRight() ;

	/**
	*returns the width of the control
	*/
	virtual double getWidth() ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*returns the top position in parent coordinates
	*/
	virtual double getTop() ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*returns the bottom position in parent coordinates
	*/
	virtual double getBottom() ;

	/**
	*returns the height of the control
	*/
	virtual double getHeight() ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*is this control visible to the user.
	*@return bool true if the control is visible, otherwise
	*false.
	*/
	virtual bool getVisible() ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	\p
	Returns the control's alignment. These alignment values are used by
	the basic container type, the StandardContainer class, which uses these
	values to determine how to layout the controls. Other layout implementations
	may choose to ignore these values. For example, the HorizontalLayoutContainer
	doesn't pay any attention to these value, it just lays out the controls
	as they are added.
	@see isIgnoredForLayout()
	@see setIgnoredForLayout()
	*/
	AlignmentType getAlignment();

	/**
	\p
	Returns whether this control must be ignored in the control container's
	layout implementation. Unlike the alignment values returned by getAlignment(),
	which are optional for the container to use, this \em must be honored.
	Failure to do so may result in dire intergalatic consequences, or
	worse, result in a shortage of SUVs.
	\p
	If this is false, the default value, then the control is laid out however the
	container is implemented to accomplish this. If the value is true, then the
	container should simply place the control wherever the controls bounds
	indicate. Container implementations that have some sort of layout that processes
	controls sequentially, such as the HorizontalLayoutContainer, \em must
	ignore a control that returns false.
	*/
	bool isIgnoredForLayout();

	void setIgnoredForLayout( const bool& val );

	/**
	sets the bounds of the control. You can pass in left, top, width and height as the
	new position for the control.
	@param double x the new left coordinate of the control
	@param double y the new top coordinate of the control
	@param double width the new width of the control
	@param double height the new height of the control
	*/
	void setBounds( const double& x, const double& y, const double& width, const double& height );

	/**
	*sets the bounds of the control. The values in the rect parameter must be
	*in the corrdinate system of the parent control
	*@param Rect the new bounds of the control. If the control
	*implements the Container interface, then any child controls
	*wil be resized via the Container::resizeChildren() automatically.
	*/
	virtual void setBounds( Rect* rect, const bool& anchorDeltasNeedUpdating=true ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*sets the alignment of the control
	*/
	void setAlignment( const AlignmentType& alignment );

	/**
	*sets the left value for the control, immediately updates the
	*controls position.
	*/
	virtual void setLeft( const double& left ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*sets the right value of the control. This value is in the
	*coordinates of the parent control.
	*/
	virtual void setRight( const double& right ) ;

	/**
	*sets the width of the control.
	*If the control implements the Container interface,
	*then any child controls will be resized via the
	*Container::resizeChildren() automatically.
	*/
	virtual void setWidth( const double& width ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*sets the top value of the control. This value is in the
	*coordinates of the parent control.
	*/
	virtual void setTop( const double& top ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*sets the bottom value of the control. This value is in the
	*coordinates of the parent control.
	*/
	virtual void setBottom( const double& bottom ) ;

	/**
	*sets the height of the control.
	*If the control implements the Container interface,
	*then any child controls will be resized via the
	*Container::resizeChildren() automatically.
	*/
	virtual void setHeight( const double& height ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*determines whether or not the control is visible,
	* and set it visible if it wasn't.
	*@param bool true to show the control, false to hide it
	*/
	virtual void setVisible( const bool& visible ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/


	/**
	*if autoStartDragDrop_ is true then this method checks to see if
	*the Controls dragging is with the windowing system's tolernace
	*for a drag drop operation to start. other wise it returns false.
	*If  autoStartDragDrop_ is false then it returns false unless some
	*derived class overides the functionality.
	*/
	virtual bool canBeginDragDrop( Point* point );

	/**
	*sets auto start dragging to true or false
	*/
	void setAutoStartDragDrop(const bool& canAutoStartDragDrop);

	/**
	*returns whether or not auto dragging is on or off.
	*@return bool true if auto dragging is on, otherwise false.
	*/
	bool getAutoStartDragDrop();

	/**
	*Override this to provide functionality for handling the
	*start of drag-drop operation
	*This will get called automatically by the framework if it
	*detects that a mouse-move has occured that indicates a
	*drag-drop operation COULD occur.
	*@return bool must return true if a drag-drop operation
	*was started, otherwise should return false
	*/
	virtual bool beginDragDrop( MouseEvent* event );

	/**
	*returns the control's native peer interface
	*/
	virtual ControlPeer* getPeer();

	/**
	*sets the parent for the control
	*/
	virtual void setParent( Control* parent ) ;/**throw( InvalidPeer ); -JEC - FIXME later*/

	/**
	*returns the control's current parent
	*/
	virtual Control* getParent() ;/**throw( InvalidPeer ); -JEC - FIXME later*/


	void removeFromParent( const bool& freeInstance=true );

	/**
	*does this control currently have focus?
	*@return bool true if the control has focus, otehr wise false. If a control
	*has focus, it will receive keyboard events. Currently all controls
	*get focused when they receive a mouse down event.
	*/
	bool isFocused();

	/**
	Makes this control the currently focused control. A control with focus
	will receive keyboard events.
	@return Control - the previously focused control (which will receive a
	FocusLost event).
	*/
	Control* setFocused();

	/**
	*returns whether the control is enabled or not. A control that is
	*enabled can receive mouse events. A control that is not enabled
	*will not respond to either mouse events or keyboard events.
	*/
	bool isEnabled();

	/**
	This checks not only to see if the control itself is
	enabled, but will return false if any parent control is
	not enabled. This function traverse all the parent child
	relationships till the frame window is hit, and checks the
	enabled status of each control. The first control that is
	\em not enabled stops the search and the methods returns
	false, otherwise it continues till it finds a NULL
	parent and returns true.
	*/
	bool areParentsEnabled();

	/**
	*sets whether the control is enabled or not.
	*@param bool true if the control is enabled, otherwise false.
	*/
	void setEnabled( const bool& enabled );

	/**
	*paints the control. Called by the underlying windowing system whenever
	*the control needs to be painted. Note that in some cases the GraphicsContext
	*passed in to this method may not be the same pointer as the GraphicsContext
	*that the control holds itself. During the paint() mehtod you should only
	*use the context value for all your drawing and not the one returned in
	*getContext(). The value returned by getContext() should be used for drawing
	*that takes place outside of the paint() method.
	*<p>Note: This should <b><i>NEVER</i></b> be called
	*by programmers using the VCF, it will be called for during the course of your
	*applications native event loop, and is only here for providing custom drawing
	*routines for controls. In other words: you implement it, you never call it
	*yourself.
	*/
	virtual void paint( GraphicsContext * context )=0;

	/**
	Paints the border for the control. This is called by the framework during the
	painting of the control. Do not count on this being called at the same time as the
	paint() method, as the order in which this is called is dependant on the
	underlying windowing system. For example, on Win32 systems this call may
	be made by the framework outside of the WM_PAINT message handling, while on
	Mac OS X this will be called in the same event handler that dispatches
	the control's paint() method.
	*/
	void paintBorder( GraphicsContext * context );
	/**
	*Called when the mouse first enters the control's bounds.
	*override this to provide specific behaviours when the control is
	*first entered, like highlighting the control
	*/
	virtual void mouseEnter( MouseEvent* event );

	/**
	*Called when one (or more) of the mouse buttons are held down.
	*override this to provide specific behaviours when
	*the mouse buttons are held down
	*/
	virtual void mouseDown( MouseEvent* event );

	/**
	*Called when the mouse moves over the control.
	*override this to provide specific behaviours when
	*the mouse moves over the control.
	*/
	virtual void mouseMove( MouseEvent* event );

	/**
	*Called when one (or more) of the mouse buttons are released.
	*override this to provide specific behaviours when
	*the mouse buttons are released.
	*/
	virtual void mouseUp( MouseEvent* event );

	/**
	*Called when one or mouse buttons are held down and
	*immediately released ( a "mouse click" ).
	**override this to provide specific behaviours when
	*a mouse click occurs
	*/
	virtual void mouseClick(  MouseEvent* event );

	/**
	*Called when one or mouse buttons are held down and
	*immediately released ( a "mouse double click" ) twice, within
	*some specific time period, as determined on the windowing
	*system.
	**override this to provide specific behaviours when
	*a mouse double click occurs
	*/
	virtual void mouseDblClick(  MouseEvent* event );

	/**
	*Called when the mouse leaves the control's bounds.
	*override this to provide specific behaviours when the control is
	*left, like highlighting the control
	*/
	virtual void mouseLeave( MouseEvent* event );

	/**
	*called when the user presses the key down
	*/
	virtual void keyDown( KeyboardEvent* event );

	/**
	*called when the user simply presses the key and represents a
	*full key cycle having occurred, in other words the key has been
	*pressed down and then released
	*/
	virtual void keyPressed( KeyboardEvent* event );

	/**
	*called when the user releases the key
	*/
	virtual void keyUp( KeyboardEvent* event );

	/**
	*translate the point from this controls coordinate system to
	*the parent controls coordinate system
	*/
	void translateToParent( Point* point );

	/**
	*translate the point from parent controls coordinate system
	*to this controls coordinate system
	*/
	void translateToLocal( Point* point );

	/**
	Takes the coordinates in pt, which are in the coordinate system of
	this control, and translates them into the coordinate system of the
	Screen.
	@param Point the initial point value, in the coordinate system of the
	control this method is called on.
	*/
	void translateToScreenCoords( Point* pt );

	/**
	Takes the coordinates in rect, which are in the coordinate system of
	this control, and translates them into the coordinate system of the
	Screen.
	@param Rect the initial rect value, in the coordinate system of the
	control this method is called on.
	*/
	void translateToScreenCoords( Rect* rect );

	/**
	Takes the coordinates in pt, which are in the coordinate system of
	the Screen, and translates them into the coordinate system of this
	control.
	@param Point the initial point value, in the coordinate system of the
	Screen.
	*/
	void translateFromScreenCoords( Point* pt );

	/**
	Takes the coordinates in rect, which are in the coordinate system of
	the Screen, and translates them into the coordinate system of this
	control.
	@param Rect the initial rect value, in the coordinate system of the
	Screen.
	*/
	void translateFromScreenCoords( Rect* rect );


	/**
	*identifies the control as a lightweight control. Lightweight control's
	*do not take up windowing system resources, instead, they rely on all events
	*and paint notification be sent to them via their parents. The default return for
	*this is false, so only those controls specifically actign as light weight Controls
	*need to return true
	*/
	virtual bool isLightWeight();

	/**
	*Returns the first parent of the Control that is a heavweight Control, i.e it's isLighweight()
	*method return false.
	*/
	virtual Control* getHeavyweightParent();

	/**
	*returns the color used to fill the background of this control
	*@see CustomControl::setUseColorForBackground
	*/
	Color* getColor();

	/**
	*sets the color to fill this control's background with
	*/
	void setColor( Color* color );

	/**
	* called just prior to completely destroying the control
	* and it's associated memory.
	*@see Component::beforeDestroy()
	*/
	virtual void beforeDestroy( ComponentEvent* event );

	/**
	* Special initializations may then happen here.
	*@see Component::afterCreate()
	*/
	virtual void afterCreate( ComponentEvent* event );

	/**
	*Returns the font associated with this control
	*/
	Font* getFont();

	/**
	*sets the font attributes. Note the internal font is <b><i>not</i></b>
	*reassigned, but rather the data is copied over from the font instance
	*passed in to the method.
	*The caller completely owns the font instance that is passed in, and is
	*responsible for cleaning up it's memory.
	*@param Font the font to copy data from in replacing attributes of the
	*control's font.
	*/
	void setFont( Font* font );

	/**
	*returns whether this control will use the font settings of the
	*parent's font.
	*@return bool true if the control does use it's parent's font settings
	*otherwise false.
	*/
	bool useParentFont();

	/**
	*sets whether the control should use it's parent font's settigns or
	*use it's own independent of it's parent's font.
	*/
	void setUseParentFont( const bool& useParentFont );

	/**
	*repaint the control. This post a message to the windowing systems
	*message queue.
	*@param Rect a rectangle may be specified indicating the precise
	*region of the control that should be repainted. If this is
	*NULL, then the entire visible region of the control is repainted
	*/
	void repaint( Rect* repaintRect=NULL );

	/**
	*is this component double buffered.
	*@return bool true if the component is double buffered, otherwise
	*false.
	*/
	bool isDoubleBuffered();

	/**
	*sets whether or not this control is double buffered. A control
	*that is double buffered will automatically use a memory graphics
	*context to draw on, and then blit the contents of this on the
	*actual graphics context for the control. Doing this results in
	*completely flicker free drawing of your controls, but is slighty
	*slower. Without double buffering, the painting of the control
	*takes place directly on the control's graphics context, and can
	*result in flicker, but is slighlty faster. Controls have this
	*set to true by default, with the exception of the OpenGL control,
	*which lets the underlying OpenGL graphics engine take care of
	*the double buffering for it.
	*@param bool true to enable the double buffered drawing, otherwise
	*false
	*/
	void setDoubleBuffered( const bool& doubleBuffered );

	/**
	Returns true if the Control should take advantage of the GraphicsContexts'
	render buffer for anti-aliased vector graphics (based on the AGG library).
	*/
	bool isUsingRenderBuffer() {
		return useRenderBuffer_;
	};

	/**
	sets whether or not the control is using the render buffer of it's
	GraphicsContext. Using the render buffer allows the control to
	take advantage of the GraphicsContext's advanced anti-aliasing vector
	graphics. This will create snapshot image that is retained and used
	to draw into. When the drawing is done (i.e. paint() returns), the image
	contents are copied back to the actual GraphicsContext. If the
	control is resized the image is resized as well
	*/
	void setUsingRenderBuffer( const bool& useRenderBuffer ) {
		useRenderBuffer_ = useRenderBuffer;
	}
	/**
	*this keeps the mouse events being sent to this control, even if the
	*mouse leaves the physical bounds of the control
	*/
	void keepMouseEvents();

	/**
	*releases mouse events - goes back to normal event handling
	*/
	void releaseMouseEvents();

	/**
	*return a pointer to the graphics context of the control.
	*/
	GraphicsContext* getContext();

	/**
	*returns the Control's PopupMenu, if any.
	*The popupmenu will be displayed whenever the user
	*right clicks the mouse over the control.
	*/
	PopupMenu* getPopupMenu();

	/**
	*sets the popup menu for this control.
	*/
	void setPopupMenu( PopupMenu* popupMenu );

	/**
	*returns the view associated with this control
	*/
	View* getView();

	/**
	*sets the view to associate with this control
	*/
	void setView( View* view );

	/**
	*returns the preferred width for this control. This is used
	*when determing the width of the control when it is first created.
	*Override it to provide a different value that is more acceptable
	*for your control's initial display size.
	*/
	virtual double getPreferredWidth(){
		return 100.0;
	};

	/**
	*returns the preferred height for this control. This is used
	*when determing the height of the control when it is first created.
	*Override it to provide a different value that is more acceptable
	*for your control's initial display size.
	*/
	virtual double getPreferredHeight() {
		return 25.0;
	}

	/**
	*set the preferred width. This is used when determing the height
	*of the control when it is first created.
	*/
	virtual void setPreferredWidth( const double& width ){};

	/**
	*set the preferred height. This is used when determing the height
	*of the control when it is first created.
	*/
	virtual void setPreferredHeight( const double& height ){};

	/**
	*returns an object implementing the Scrollable interface
	*The default value is NULL, indicating the control does not support
	*scrolling behaviour
	*/
	Scrollable* getScrollable() {
		return scrollable_;
	}

	/**
	*sets the scrollable for the control. Control's with a
	*scrollable object will be able to provide scroll bars
	*when neccessary.
	*@see Scrollable
	*@see Scrollable::setVirtualViewHeight
	*@see Scrollable::setVirtualViewWidth
	*/
	virtual void setScrollable( Scrollable* scrollable );

	/**
	Call this method to adjust the view bounds (i.e. what the GraphicsContext::getViewableBounds()
	method returns) to take into consideration the presence of scroll bars
	*/
	void adjustViewableBoundsAndOriginForScrollable( GraphicsContext* context, Rect& viewBounds, Point& origin );

	/**
	*returns a string that is used for context sensitive help
	*for the control.
	*/
	String getWhatThisHelpString() {
		return whatThisHelpString_;
	}

	/**
	*sets the string that is used for context sensitive help
	*for the control.
	*/
	void setWhatThisHelpString( const String& whatThisHelpString ) {
		whatThisHelpString_ = whatThisHelpString;
	}

	/**
	*
	*/
	void processWhatsThisHelpEvent();

	/**
	*returns a string that is used to display in the tooltip
	*for the control.
	*/
	String getToolTipText() {
		return toolTip_;
	}

	/**
	*sets the string that is used to display in the tooltip
	*for the control.
	*/
	void setToolTipText( const String& tooltip );

	/**
	*returns the cursor ID for the control. The cursor id represents an id tag that
	*identifies a Cursor object to be used to for controling the display of the
	*mouse cursor. To access the Cursor object directly call the CursorManager::getCursor()
	*method.
	*@return long the id of the cursor
	*@see CursorManager
	*@see CursorManager::getCursor()
	*@see Cursor
	*/
	long getCursorID() {
		return cursorID_;
	}

	/**
	*sets the cursor ID for the control. This will change the
	*cursor appearance whenever the mouse is over the control.
	*/
	void setCursorID( const long& cursorID );

	/**
	*returns the anchor mask value for this control.
	*Anchors allow you to customize the sizing behavior of a particular control.
	*Setting the alignment may be done at any time after the control has been instantiated.
	*By anchoring a control you can have finer control over how the control gets resized
	*when it's parent is resized than simply specifying an alignment value. However,
	*changing the anchor value of a control will automatically set the control's alignment
	*to ALIGN_NONE, while changing the control's alignment will automatically set the control's
	*anchor value to ANCHOR_NONE. The two values are mutually exclusive, you can get one or
	*the other, but not both. The following table describes the meanings of the various
	*mask values for the anchor value, which can have either the value of ANCHOR_NONE
	*or any combination of the other four mask types.
	*<table width="100%" cellpadding="2" cellspacing="0" border="1" bordercolor="#C0C0C0">
	*<tr>
	*<td width="20%" bgcolor="#C0C0C0" valign=TOP>
	*Value</td>
	*<td width="80%" bgcolor="#C0C0C0" valign=TOP>
	*Meaning</td>
	*</tr>
	*<tr>
	* <td width="20%" valign=TOP>
	*	<code>ANCHOR_NONE</code></td>
	* <td width="80%" valign=TOP>
	*   This is the default value for a control's anchor property. No layout
	*	adjustments are performed on the control.</td>
	*</tr>
	*<tr>
	* <td width="20%" valign=TOP>
	*   <code>ANCHOR_TOP</code></td>
	* <td width="80%" valign=TOP>
	*   The Control is anchored to the top edge of the parent control it
	*	belongs to. Whatever the distance between the top edge and the top
	*	coordinate of the control when this is set, is maintained whenever
	*	the parent control's dimensions change. </td>
	*</tr>
	*<tr>
	* <td width="20%" valign=TOP>
	*   <code>ANCHOR_LEFT</code></td>
	* <td width="80%" valign=TOP>
	*   The Control is anchored to the left edge of the parent control it
	*	belongs to. Whatever the distance between the left edge and the left
	*	coordinate of the control when this is set, is maintained whenever
	*	the parent control's dimensions change. </td>
	*</tr>
	*<tr>
	* <td width="20%" valign=TOP>
	*   <code>ANCHOR_BOTTOM</code></td>
	* <td width="80%" valign=TOP>
	*   The Control is anchored to the bottom edge of the parent control it belongs
	*	to. Whatever the distance between the bottom edge and the bottom coordinate
	*	of the control when this is set, is maintained whenever the parent control's
	*	dimensions change. </td>
	*</tr>
	*<tr>
	* <td width="20%" valign=TOP>
	*   <code>ANCHOR_RIGHT</code></td>
	* <td width="80%" valign=TOP>
	*   The Control is anchored to the right edge of the parent control it belongs to.
	*	Whatever the distance between the right edge and the right coordinate of the
	*	control when this is set, is maintained whenever the parent control's dimensions
	*	change.</td>
	*</tr>
	*</table>
	*/
	unsigned long getAnchor() {
		return anchor_;
	}

	/**
	*sets the anchor mask value for the control. See
	*getAnchor() for a complete description of the various values
	*and what they mean for the control's alignment.
	*@see getAnchor()
	*/
	void setAnchor( const unsigned long& anchor );

	/**
	*returns the current delta for each of the anchors.
	*There will be a delta for the left, the top, the right,
	*and the bottom sides. These deltas are recalculated whenever
	*the controls bounds are set with the anchorDeltasNeedUpdating
	*param set to true.
	*/
	float* getAnchorDeltas() {
		return anchorDeltas_;
	}

	/**
	*this function determines if the control keeps the key event
	*when the return key is pressed, or if it will relinquish the event
	*for the system to process. Most controls will return false with the
	*exception of keyboard entry controls. If the control does keep the
	*event, then any default buttons will NOT receive their enter key
	*event until they receive focus.
	*@see Button::setDefault()
	*/
	virtual bool keepReturnCharacter() {
		return false;
	}

	/**
	*This function determines whether or not the
	*control should have precedence and prevent the
	*the tab key from switching focus
	*to another control. Typically this will return
	*false, with the exception of keyboard entry controls
	*like the TextControl. To prevent the tab key from
	*causing a the framework to switch to another control,
	*override this and return true.
	*@return bool returns false, indicating the framework can
	*go ahead and switch the focus to the next tabbed control
	*when appropriate, otherwise if it returns true the control
	*will keep the tabbed key event and process it
	*/
	virtual bool keepsTabKey() {
		return false;
	}

	/**
	*This function determines whether or not the
	*control should have precedence and prevent the
	*the arrow keys from switching focus
	*to another control. Typically this will return
	*false, with the exception of keyboard entry controls
	*like the TextControl. To prevent the tab key from
	*causing a the framework to switch to another control,
	*override this and return true.
	*@return bool returns false, indicating the framework can
	*go ahead and switch the focus to the next tabbed control
	*when appropriate, otherwise if it returns true the control
	*will keep the tabbed key event and process it
	*/
	virtual bool keepsArrowKeys() {
		return false;
	}


	/**
	*Indicates whether the control responds to the TAB key
	*to set it's focus when tabbing from control to control.
	*@return bool whether the control responds to the Tab key. If the
	*return value is true then the control will allow itself to become
	*focused, while a value of false indicates the control does not respond
	*to the tab key and will not become focused.
	*/
	bool getTabStop() {
		return tabStop_;
	}

	/**
	*sets the tab stop value of the control. The default value
	*is true.
	*@param bool the new value for the tab stop property
	*@see getTabStop()
	*/
	void setTabStop( const bool& tabStop );

	/**
	*Returns the tab order of the control. Tab order may be specified
	*independently of the controls child order within it's parent
	*Container.
	*@return
	*/
	long getTabOrder() {
		return tabOrder_;
	}

	/**
	*
	*/
	void setTabOrder( const long& tabOrder );


	/**
	Returns the AcceleratorKey instance that is associated with this control and
	the specified key code and modifier mask. The AcceleratorKey will be activated
	whenever the corresponding keyboard combination is pressed.
	@param VirtualKeyCode the key code that represents this AcceleratorKey. For
	example, vkLetterV is used to indicated an accelerator that is triggered whenever
	the "V" key is pressed.
	@param ulong32 a mask of special keys that can be pressed together with the
	specified key code, such as Shift, Alt or Ctrl.
	@see AcceleratorKey
	*/
	AcceleratorKey* getAccelerator( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	/**
	Associates a new AcceleratorKey with the Control.
	The key code, modifier mask and event handler
	all become the attributes of the new AcceleratorKey
	*/
	void addAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask, EventHandler* eventHandler );

	/**
	Associates a new AcceleratorKey with the Control.
	The key code, modifier mask and the action's
	accelerator event handler all become the attributes
	of the new AcceleratorKey instance.
	*/
	void addAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask, Action* action );

	/**
	This should generally not be called. It's for framework usage only at this
	point.
	*/
	void addAcceleratorKey( AcceleratorKey* accelerator );

	/**
	Pressing the accelerator character will cause the control's
	mnemonicActivate() method to be fired, which by default
	sets focus to the control
	*/
	virtual void mnemonicActivate();

	/**
	This returns a pointer to the top level frame that this control is associated with
	@return Frame the top level froma instance for this control. This may not be the
	parent instance as the control's current parent.
	@see Control::getParent()
	*/
	Frame* getParentFrame();

	/**
	This returns a value that indicates whether or not hte control is considered to
	be active. A control is considered active if it belongs to, i.e. is a child
	eitehr directly or indirectly, (or is) the active frame. This is
	determined by checking if the control's getParentFrame() equals the Frame::getActiveFrame().
	@return bool true if the control is active, otherwise false.
	*/
	bool isActive();

	/**
	Can the control accept focus?
	This method determines if the control can recieve focus.
	@return bool returns true if the control is enabled and all
	of it's parents are enabled as well. Otherwise it returns
	false.
	*/
	bool canAcceptFocus();

	/**
	returns the current container for this control.
	The container determines whether or not the control
	can contain child controls. By default a control
	container is NULL, indicating it cannot hold any
	child controls.
	@return Container returns the current container for
	the control. If the value returned is NULL, then
	the control has no container, and cannot have any child
	controls.
	@see Container
	*/
	Container* getContainer() {
		return container_;
	}

	/**
	sets the current container for a control. Setting
	a control's container, will enable (or disable, if
	the container value passed in is NULL) the control's
	ability to handle child controls
	@see Container
	*/
	void setContainer( Container* container );


	/**
	sets a new model for the view
	Once set, the control fires a ControlModelChanged event.
	*/
	virtual void setViewModel( Model* viewModel );

	/**
	tells if the control is currently sending a repaint message
	when resizing, or not.
	*/
	bool getRepaintOnSize() {
		return repaintOnSize_;
	}

	/**
	let the user to control if the control will send a repaint message
	when is resized, or not.
	*/
	void setRepaintOnSize( const bool& repaint ) {
		repaintOnSize_ = repaint;
	}

	/**
	*returns the current control that has captured the mouse input.
	*This may return NULL if no control has expressly captured the
	*mouse input through the Control::keepMouseEvents() method.
	*/
	static Control* getCapturedMouseControl();

	/**
	*sets the control that has captured the mouse. Used internally
	*only. <b>DO NOT<b> call, this is for internal framework use only.
	*/
	static void setCapturedMouseControl( Control* control );

	/**
	*returns the currently focused control.
	*/
	static Control* getCurrentFocusedControl();

	/**
	*returns the control the mouse was previously over, if any.
	*/
	static Control* getPreviousMouseOverControl();

	static void setPreviousMouseOverControl( Control* control );

	static void buildTabList( Control* control, std::vector<Control*>& tabList );

protected:
	void updateAnchorDeltas();

	virtual void destroy();

protected:
	static Control* currentFocusedControl;
	static Control* previousMouseOverControl;
	static Control* capturedMouseControl;

	ControlPeer* peer_;
	ControlGraphicsContext* context_;
	Control * parent_;
	AlignmentType aligment_;
	unsigned long anchor_;
	Rect* bounds_;
	Rect* clientBounds_;
	Border* border_;
	Color* color_;
	Font* font_;
	View* view_;
	bool useParentFont_;
	bool doubleBuffered_;
	bool hasMouseCapture_;
	bool autoStartDragDrop_;
	PopupMenu* popupMenu_;
	Scrollable* scrollable_;
	String whatThisHelpString_;
	String toolTip_;
	long cursorID_;
	Cursor* cursor_;
	float anchorDeltas_[4];
	bool tabStop_;
	long tabOrder_;
	Point clickPt_;
	bool useRenderBuffer_;
	Container* container_;
	bool ignoredForLayout_;
	bool repaintOnSize_;

};


}; // namespace VCF 


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.8  2005/06/29 20:30:15  marcelloptr
*second step to remove flickering when dragging a splitter
*
*Revision 1.3.2.7  2005/06/29 05:00:03  marcelloptr
*some white spaces
*
*Revision 1.3.2.6  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.5  2005/04/09 17:20:35  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3.2.4  2005/03/20 04:29:21  ddiego
*added ability to set image lists for list box control.
*
*Revision 1.3.2.3  2005/03/15 05:29:01  ddiego
*makes the accelerator check logic a bit smarter and also changes
*teh way menu items test to check whether or not they are enabled.
*
*Revision 1.3.2.2  2005/03/10 00:17:27  marcelloptr
*set discrete scrolling as default behaviour for ListBoxControls
*
*Revision 1.3.2.1  2005/03/06 22:50:58  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.3  2004/12/01 04:31:20  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.5  2004/11/10 19:07:32  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2.2.4  2004/11/07 19:32:18  marcelloptr
*more documentation
*
*Revision 1.2.2.3  2004/10/23 13:53:12  marcelloptr
*comments for setUseColorForBackground; setActiveFrame renamed as internal
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
*Revision 1.2.2.1  2004/09/06 21:30:19  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/22 04:18:58  ddiego
*fixed bug 995642 delete LoalePeer in Locale, and added some miscellaneous changes to the QTPlayer. Also fixing (not finished yet) a bug that
*prevents the TreePeer from being properly notified when the tree model's
*item is deleted.
*
*Revision 1.1.2.4  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.3.2.1  2004/07/06 03:27:12  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.36.2.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.36  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.35.2.1  2004/01/18 04:52:45  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.35  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.34.2.11  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.34.2.10  2003/11/10 01:57:03  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.34.2.9  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.34.2.8  2003/10/13 04:00:19  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.34.2.7  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.34.2.6  2003/09/06 19:45:44  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.34.2.5  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.34.2.4  2003/08/23 02:01:23  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.34.2.3  2003/08/18 19:52:32  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.34.2.2  2003/08/12 20:29:22  marcelloptr
*just moved down the paint() declaration
*
*Revision 1.34.2.1  2003/08/12 02:52:41  ddiego
*added properties getBottom/getRight/setBottom/setRight to Control
*
*Revision 1.34  2003/08/09 02:56:42  ddiego
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
*Revision 1.33.2.1  2003/06/20 04:41:04  ddiego
*more AGG integration
*
*Revision 1.33  2003/05/17 20:37:02  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.32.2.2  2003/04/17 04:29:45  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.32.2.1  2003/03/12 03:09:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.32  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.31.8.3  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.31.8.2  2003/01/08 00:19:42  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.31.8.1  2002/12/25 22:06:18  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.31  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.30.6.2  2002/07/14 05:40:01  ddiego
**** empty log message ***
*
*Revision 1.30.6.1  2002/06/28 17:45:29  ddiego
*migrated over lucki's changes (from his branch) for drag drop
*compiles OK, made chages to control and UIToolkit as neccessary
*still testing though.
*
*Revision 1.30  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.29  2002/03/21 01:36:29  ddiego
*fix [ 532623 ] alignment problem & [ 525214 ] alignment loss after resize JEC 20-03-2002
*there was an incorrect comparison being done in AbstractContainer::insertBefore() that
*was resulting in controls being respositioned in the incorrect order. Should be cool now.
*
*Revision 1.28  2002/03/19 01:39:40  ddiego
*minor changes to ComboBoxControl to fix tabbing error with arrow keys
*fixes bug 531678 Bad behaviour of arrow keys in Combobox
*
*Revision 1.27  2002/02/20 04:07:49  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.26  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CONTROL_H__


