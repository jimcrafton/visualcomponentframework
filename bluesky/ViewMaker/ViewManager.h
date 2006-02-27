#ifndef _VIEWMANAGER_H__
#define _VIEWMANAGER_H__


#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/Splitter.h"

namespace VCF {
	

	enum ViewManagerArea{
		vmLeft = AlignLeft,
		vmTop = AlignTop,
		vmRight = AlignRight,
		vmBottom = AlignBottom,
		vmClient = AlignClient,
	};

	enum DockChangeState {
		dcsNotAllowed = 0,
		dcsNewTab,
		dcsToLeft,
		dcsToTop,
		dcsToRight,
		dcsToBottom,		
	};


	enum DockBarHitTest {
		dbMinimize = -3,
		dbMaximize = -2,
		dbThinAir = -1,
		dbTab = 0
	};

	class DockContainer : public StandardContainer {
	public:

		static double getTabBarHeight() {
			 
			return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htButtonHeight ) * 0.85;
		}

		DockBarHitTest hitTestDockBar( Point pt ) {
			DockBarHitTest result(dbThinAir);

			return result;
		}
	};


	class ViewSplitter : public Splitter {
	public:
		virtual void paint( GraphicsContext* ctx ) {
			CustomControl::paint( ctx );
		}
	};

	class ViewManagerContainer : public StandardContainer {
	public:

		void addSplitter( Control * child, const AlignmentType& alignment ) {
			Control* parent = getContainerControl();

			Splitter* s = new ViewSplitter();
			s->setBorder( NULL );

			switch ( alignment ) {
				case AlignTop : {
					s->setHeight( 3 );
					s->setCursorID( Cursor::SCT_SPLIT_HORZ );
					StandardContainer::add( s, AlignTop );
				}
				break;

				case AlignBottom : {
					s->setHeight( 3 );
					s->setCursorID( Cursor::SCT_SPLIT_HORZ );
					StandardContainer::insertBeforeControl( s, AlignBottom, child );
				}
				break;

				case AlignLeft : {
					s->setWidth( 3 );
					s->setCursorID( Cursor::SCT_SPLIT_VERT );
					StandardContainer::add( s, AlignLeft );
				}
				break;

				case AlignRight : {
					s->setWidth( 3 );
					s->setCursorID( Cursor::SCT_SPLIT_VERT );
					StandardContainer::insertBeforeControl( s, AlignRight, child );
				}
				break;

				case AlignClient : {

				}
				break;
			}
		}

		void removeSplitter( Control * child, const AlignmentType& alignment ) {
			Control* parent = getContainerControl();
			switch ( alignment ) {
				case AlignTop : {
					//get control after this child
				}
				break;

				case AlignBottom : {
					//get control before this child
				}
				break;

				case AlignLeft : {
					//get control after this child
				}
				break;

				case AlignRight : {
					//get control before this child
				}
				break;

				case AlignClient : {

				}
				break;
			}
		}

		virtual void add( Control * child ) {
			if ( !isDockablePanel(child) ) {
				throw RuntimeException( "Invalid Control - this container only accepts DockablePanel instances." );
			}

			StandardContainer::add( child );
			addSplitter( child, child->getAlignment() );
		}

		virtual void add( Control * child, const AlignmentType& alignment ) {
			if ( !isDockablePanel(child) ) {
				throw RuntimeException( "Invalid Control - this container only accepts DockablePanel instances." );
			}

			StandardContainer::add( child, alignment );
			addSplitter( child, alignment );
		}

		virtual void insertBeforeControl( Control * child, const AlignmentType& alignment, Control* beforeControl ) {
			if ( !isDockablePanel(child) ) {
				throw RuntimeException( "Invalid Control - this container only accepts DockablePanel instances." );
			}

			StandardContainer::insertBeforeControl( child, alignment, beforeControl );
		}

		virtual void insertAtIndex( Control * child, const AlignmentType& alignment, const ulong32& index ) {
			if ( !isDockablePanel(child) ) {
				throw RuntimeException( "Invalid Control - this container only accepts DockablePanel instances." );
			}

			StandardContainer::insertAtIndex( child, alignment, index );
		}

		bool isDockablePanel( Control* control );
	};

	class ViewManagerPanel : public Panel {
	public:
		ViewManagerPanel() {
			setBorder( NULL );
			setAlignment( AlignClient );
			setContainer( new ViewManagerContainer() );

			ControlSized += 
				new GenericEventHandler<ViewManagerPanel>( this, &ViewManagerPanel::sizeOrPosChanged, "ViewManagerPanel::sizeOrPosChanged" );			

			ControlPositioned += getEventHandler( "ViewManagerPanel::sizeOrPosChanged" );
			ControlParentChanged += getEventHandler( "ViewManagerPanel::sizeOrPosChanged" );
		}

		void sizeOrPosChanged( Event* e ) {
			if ( getAlignment() != AlignClient ) {
				throw RuntimeException( "Invalid alignment type specified! This control can only be aligned to the Client area of it's parent." );
			}
		}


		virtual void paint( GraphicsContext* ctx ) {
			Panel::paint( ctx );

		}
	};

	class DockableBorder : public Border {
	public:

		
		virtual void paint( Control* control, GraphicsContext* context ) {
			Rect bounds = control->getClientBounds(false);
			if ( !bounds.isEmpty() ){
				paint( &bounds, context );
			}
		}

		virtual void paint( Rect* bounds, GraphicsContext* context ) {
			if ( NULL != bounds ){
				Color* face = NULL;
				face = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
				
				context->rectangle( bounds );
				context->setColor( face );
				context->fillPath();

				Color* color = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );				
				context->setColor( color );

				Rect tmp = *bounds;
				tmp.inflate( -1,-1 );

				double arcAmt = 7;
				context->arc( tmp.left_ + arcAmt, tmp.top_ + arcAmt,
								arcAmt, arcAmt, 
								180, 270 );

				context->moveTo( tmp.left_ + arcAmt-1, tmp.top_ );
				context->lineTo( tmp.right_ - arcAmt - 1, tmp.top_ );

				context->arc( tmp.right_ - arcAmt-1, tmp.top_ + arcAmt,
								arcAmt, arcAmt, 
								270, 0 );

				context->moveTo( tmp.right_-1, tmp.top_ + arcAmt-1 );
				context->lineTo( tmp.right_-1, tmp.bottom_-1 );
				context->lineTo( tmp.left_, tmp.bottom_-1 );
				context->lineTo( tmp.left_, tmp.top_ + arcAmt );

				

				Rect bar = tmp;
				bar.bottom_ = bar.top_ + DockContainer::getTabBarHeight();
				context->moveTo( tmp.left_, bar.bottom_ );
				context->lineTo( tmp.right_, bar.bottom_ );

				context->strokePath();

				Rect btn = bar;
				btn.inflate( -4, -4 );
				btn.offset( -2, 0 );
				btn.left_ = btn.right_ - btn.getHeight();

				context->rectangle( &btn );
				

				btn.offset( -(btn.getWidth() + 2), 0 );
				context->rectangle( &btn );
				context->strokePath();
			}
		}

		Rect getTabArea( Rect* bounds ) {
			Rect bar = *bounds;

			bar.inflate( -1,-1 );
			bar.bottom_ = bar.top_ + DockContainer::getTabBarHeight();
			Rect btn = bar;
			btn.inflate( -4, -4 );
			btn.offset( -2, 0 );
			btn.left_ = btn.right_ - btn.getHeight();
			btn.offset( -(btn.getWidth() + 2), 0 );

			bar.right_ = btn.left_;

			bar.left_ += 5;


			return bar;
		}

		virtual Rect getClientRect( Rect* initialBounds, Control* control ) {
			Rect result;

			result = *initialBounds;

			result.inflate(-4,-4);
			result.top_ += DockContainer::getTabBarHeight();

			return result;
		}

	};

	

	class DockablePanel : public Panel {
	public:
		DockablePanel(): viewMgr_(NULL), dockParent_(NULL) {
			setContainer( new DockContainer() );
			setBorder( new DockableBorder() );


			ControlSized += 
				new GenericEventHandler<DockablePanel>( this, &DockablePanel::sizeOrPosChanged, "DockablePanel::sizeOrPosChanged" );			

			ControlPositioned += getEventHandler( "DockablePanel::sizeOrPosChanged" );
			ControlParentChanged += getEventHandler( "DockablePanel::sizeOrPosChanged" );
		}

		void sizeOrPosChanged( Event* e ) {
			

			if ( getViewManager() == NULL ) {
				throw RuntimeException( "You must add a view manager to this control before adding to another." );
			}

			if ( e->getType()  == Control::CONTROL_PARENT_CHANGED ) {
				//check the parent and save it to the
				//dockParent_ value
				if ( NULL != getParent() ) {
					dockParent_ = getParent();
				}
			}
		}

		virtual void paint( GraphicsContext* ctx ) {
			Panel::paint( ctx );

			DockableBorder* bdr = (DockableBorder*)getBorder();
			Rect r(0,0,getWidth(),getHeight());
			Rect tabRect = bdr->getTabArea( &r );

			Enumerator<Control*>* controls = getContainer()->getChildren();

			
			Rect tab = tabRect;
			while ( controls->hasMoreElements() ) {
				Control* child = controls->nextElement();

				paintControlTab( tabRect, tab, child, ctx );

				tab.left_ = tab.right_;

			}
		}


		void paintControlTab( Rect& tabRect, Rect& tab, Control* child, GraphicsContext* ctx ) {
			tab.right_ = tab.left_ + 
							ctx->getTextWidth( getControlName(child) ) + 5.0 + 
							tabRect.getHeight();
			
			ctx->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_ACTIVE_CAPTION ) );
			ctx->rectangle( &tab );
			ctx->fillPath();
			
			ctx->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_ACTIVE_BORDER ) );
			ctx->rectangle( &tab );
			ctx->strokePath();
		}


		void maximize() {

		}

		void minimize() {

		}

		void detachAndFloatFromDockParent() {

		}

		void reattachToDockParent() {
			
		}


		ViewManagerPanel* getViewManager() {
			return viewMgr_;
		}

		void setViewManager( ViewManagerPanel* viewMgr ) {
			viewMgr_ = viewMgr;
		}

		Control* getDockParent() {
			return dockParent_;
		}

		void setControlName( Control* control, const String& name ) {
			controlTabNames_[control] = name;
		}

		String getControlName( Control* control ) {
			String result;
			std::map<Control*,String>::iterator found = controlTabNames_.find( control );
			if ( found != controlTabNames_.end() ) {
				result = found->second;
			}

			if ( result.empty() ) {
				result = control->getName();
			}
			return result;
		}


		ViewManagerPanel* viewMgr_;
		Control* dockParent_;
		std::map<Control*,String> controlTabNames_;

	};







	bool ViewManagerContainer::isDockablePanel( Control* control )
	{
		return NULL != dynamic_cast<DockablePanel*>(control) ||
			NULL != dynamic_cast<ViewSplitter*>(control);
	}
};

#endif //_VIEWMANAGER_H__
