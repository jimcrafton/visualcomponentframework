#ifndef _VCF_ABSTRACTGTKCONTROL_H__
#define _VCF_ABSTRACTGTKCONTROL_H__
//AbstractGTKControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
This class serves as a common implementation
for various methods of the ControlPeer interface.
Usually a class like GTKControl, GTKWindow, etc will share
most of the same functionality, and only differ by a few overridden methods
*/
class AbstractGTKControl : public Object, public ControlPeer {
public:

	AbstractGTKControl();

	virtual ~AbstractGTKControl();

	virtual OSHandleID getHandleID() {
		return wndHandle_;
	}

	virtual void create( Control* owningControl );

	virtual void destroyControl();

	/**
	* returns a text associated with the component. This usually gets used in the Control::getCaption() method.
	*/
	virtual String getText();

	/**
	* sets the text for the widget
	*/
	virtual void setText( const String& text );

	/**
	* sets the bounds for the component. Bounds are specified in the coordinate system of the componenents parent.
	*/
	virtual void setBounds( Rect* rect );

	/**
	*advanced function for changing the size of multiple child windows
	*/
	virtual bool beginSetBounds( const ulong32& numberOfChildren );

	virtual void endSetBounds();

	/**
	* returns the bounds of the component in the coordinate system of the parent.
	*/
	virtual Rect getBounds();

	/**
	* shows or hides the component.
	* This does NOT close the component (if invoked on a frame based component ).
	*/
	virtual void setVisible( const bool& visible );

	/**
	* returns wether or not the component is currently visible.
	*/
	virtual bool getVisible();

	/**
	* returns a bit-masked unsigned long that contains style constants.
	*  These style constants are defined in the VCF, and must
	* be translated to the particular windowing system being used.
	*/

	/**
	* returns the component that this Peer is attached to.
	*/
	virtual Control* getControl();

	/**
	* attahces the Peer to a particular component. This should only be done once.
	*/
	virtual void setControl( Control* component );

	virtual void setCursor( Cursor* cursor );

	virtual void setParent( Control* parent );

	virtual Control* getParent();

	virtual bool isFocused();

	virtual void setFocused();

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void setFont( Font* font );

	virtual void repaint( Rect* repaintRect=NULL );

	/**
	*this keeps the mouse events being sent to this control, even is the
	*mouse leaves the physical bounds of the control
	*/
	virtual void keepMouseEvents();

	/**
	*releases mouse events - goes back to normal event handling
	*/
	virtual void releaseMouseEvents();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );

	virtual gboolean handleEvent( GdkEvent* gtkEvent );

	static AbstractGTKControl* getGTKControlFromWidget( GtkWidget* wndHandle );

	Rect internal_getBounds() {
		return bounds_;
	}

	void internal_setBounds( const Rect& bounds ) {
		bounds_ = bounds;
	}
protected:
	virtual void initGdkEventHandlers();

	typedef std::map<GtkWidget*,AbstractGTKControl*> GTKControlMap;

	static void registerGTKControl( AbstractGTKControl* gtkControl );
	static void unRegisterGTKControl( AbstractGTKControl* gtkControl );

	static GTKControlMap gtkControlMap;

	AbstractGTKControl* parent_;
	bool enabled_;

	GtkWidget* wndHandle_;
	Control* control_;

	Rect bounds_;

	bool repainted_;

	static gboolean onGdkEvent( GtkWidget *widget, GdkEvent *event, gpointer user_data );

	/*
	static gboolean onGdkExpose( GtkWidget *widget, GdkEventExpose *event, gpointer user_data);

	static gboolean onGdkFocus( GtkWidget *widget, GtkDirectionType arg1, gpointer user_data );

	static gboolean onGdkKeyPress( GtkWidget *widget, GdkEventKey *event, gpointer user_data );
	static gboolean onGdkKeyRelease( GtkWidget *widget, GdkEventKey *event, gpointer user_data );

	static gboolean onGdkEnterNotify( GtkWidget *widget, GdkEventCrossing *event, gpointer user_data );
	static gboolean onGdkLeaveNotify( GtkWidget *widget, GdkEventCrossing *event, gpointer user_data );

	static gboolean onGdkScroll( GtkWidget *widget, GdkEvent *event, gpointer user_data );

	static gboolean onGdkButtonPress( GtkWidget *widget, GdkEventButton *event, gpointer user_data );
	static gboolean onGdkMotion( GtkWidget *widget, GdkEventMotion *event, gpointer user_data );
	static gboolean onGdkButtonRelease( GtkWidget *widget, GdkEventButton *event, gpointer user_data );

	static gboolean onGdkDestroy( GtkWidget *widget, GdkEvent *event, gpointer user_data );
*/

public:
	static GtkType getGTKType();

	struct ContainerChild {
		int x;
		int y;
		int width;
		int height;
		GtkWidget* widget;
	};



	struct Container {

		GtkContainer container;

		/* The adjustment object that stores the data for this container */
		GtkAdjustment *adjustment;

		AbstractGTKControl* gtkControlPeer_;
/*
		int x;
		int y;
		int width;
		int height;
		*/
		GList* children;

		static AbstractGTKControl* getControlPeer( GtkWidget* widget );

		static Rect getBounds( GtkWidget* widget );

		static void move( GtkWidget* widget,
							int x,
							int y,
							int width,
							int height );

		static void moveChild( Container *container,
							GtkWidget* child,
							int x,
							int y,
							int width,
							int height );

		static Rect getChildBounds( Container *container,
								GtkWidget* child );



		static GtkWidget* create( GtkAdjustment *adjustment, AbstractGTKControl* gtkControlPeer );

		static GtkAdjustment* getAdjustment( Container *container );

		static void setUpdatePolicy( Container *container,
										 GtkUpdateType policy );
		static void setAdjustment( Container *container,
									  GtkAdjustment *adjustment );

		static void init( Container *container );


		static void destroy ( GtkObject *object );

		static void realize( GtkWidget *widget );

		static void sizeRequest( GtkWidget *widget, GtkRequisition *requisition );

		static void sizeAllocate( GtkWidget *widget, GtkAllocation *allocation );

		static gboolean expose( GtkWidget *widget, GdkEventExpose *event );

		static void adjustmentChanged( GtkAdjustment *adjustment, gpointer data );

		static void adjustmentValueChanged( GtkAdjustment *adjustment, gpointer data );

		static void add ( GtkContainer* container, GtkWidget* widget );

		static void remove ( GtkContainer* container, GtkWidget* widget );

		static void forall( GtkContainer* container,
							gboolean include_internals,
							  GtkCallback callback,
							  gpointer callback_data );

		static GType getChildType( GtkContainer* container );

	};

	struct ContainerClass {
		GtkContainerClass parent_class;

		static void init ( ContainerClass *klass );
	};
};


}; //end of namespace VCF



#define GTK_VCF_CONTAINER(obj) \
	GTK_CHECK_CAST (obj, AbstractGTKControl::getGTKType (), VCF::AbstractGTKControl::Container)


#define GTK_VCF_CONTAINER_CLASS(klass) \
 GTK_CHECK_CLASS_CAST (klass, AbstractGTKControl::getGTKType (), VCF::AbstractGTKControl::ContainerClass)


#define GTK_IS_VCF_CONTAINER(obj)  \
	GTK_CHECK_TYPE (obj, AbstractGTKControl::getGTKType ())


#endif // _VCF_ABSTRACTGTKCONTROL_H__

/**
$Id$
*/
