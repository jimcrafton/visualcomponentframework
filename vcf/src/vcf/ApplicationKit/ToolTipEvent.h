#ifndef _VCF_TOOLTIPEVENT_H__
#define _VCF_TOOLTIPEVENT_H__
//ToolTipEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class GraphicsContext;

#define TOOLTIP_EVENT_TIP_REQESTED		CUSTOM_EVENT_TYPES + 3000



/**
\class ToolTipEvent ToolTipEvent.h "vcf/ApplicationKit/ToolTipEvent.h" 
The tooltip event is fired when tooltip text is being requested and/or 
just before the tooltip is ready to be shown, allowing the 
handler to customize the tooltip's data or presentation.
*/
class APPLICATIONKIT_API ToolTipEvent : public Event {
public:
	ToolTipEvent( Object* source, const ulong32& type ):
	  Event( source, type ),
		  customToolTipGraphicsCtx_(NULL),
		  embeddedControl_(NULL),
			autoDestroyEmbeddedControl_(true){		  
		  tooltipLocation_.x_ = 0.0;
		  tooltipLocation_.y_ = 0.0;
		  
		  tooltipSize_.height_ = 0.0;
		  tooltipSize_.width_ = 0.0;
		  
		  tooltipString_ = "";

		  backgroundColor_ = *GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP );
	}

	ToolTipEvent( const ToolTipEvent& rhs ):Event(rhs),
		customToolTipGraphicsCtx_(NULL),embeddedControl_(NULL),autoDestroyEmbeddedControl_(true) {
		*this = rhs;
	}

	virtual ~ToolTipEvent(){};


	ToolTipEvent& operator=( const ToolTipEvent& rhs ) {
		Event::operator =( rhs );

		tooltipString_ = rhs.tooltipString_;
		customToolTipGraphicsCtx_ = rhs.customToolTipGraphicsCtx_;
		tooltipLocation_ = rhs.tooltipLocation_;
		tooltipSize_ = rhs.tooltipSize_;
		embeddedControl_ = rhs.embeddedControl_;
		autoDestroyEmbeddedControl_ = rhs.autoDestroyEmbeddedControl_;
		backgroundColor_ = rhs.backgroundColor_;

		return *this;
	}

	String getToolTipString() {
		return tooltipString_;
	}

	virtual Object* clone( bool deep=false ) {
		return new ToolTipEvent(*this);
	}

	void setToolTipString( const String& tooltipString ) {
		tooltipString_ = tooltipString;
	}

	Point* getToolTipLocation() {
		return &tooltipLocation_;
	}

	void setToolTipLocation( Point* pt ) {
		tooltipLocation_ = *pt;
	}

	Size* getToolTipSize() {
		return &tooltipSize_;
	}

	void setToolTipSize( Size* size ) {
		tooltipSize_ = *size;
	}

	GraphicsContext* getCustomToolTipContext() {
		return customToolTipGraphicsCtx_;
	}

	void setCustomTooltipContext( GraphicsContext* customToolTipGraphicsCtx ) {
		customToolTipGraphicsCtx_ = customToolTipGraphicsCtx;
	}

	Control* getEmbeddedControl() {
		return embeddedControl_;
	}

	void setEmbeddedControl( Control* val ) {
		embeddedControl_ = val;
	}

	bool getAutoDestroyEmbeddedControl() {
		return autoDestroyEmbeddedControl_;
	}

	void setAutoDestroyEmbeddedControl( const bool& val ) {
		autoDestroyEmbeddedControl_ = val;
	}

	Color* getBackgroundColor() {
		return &backgroundColor_;
	}

	void setBackgroundColor( Color* color ) {
		backgroundColor_ = *color;
	}

	
protected:
	String tooltipString_;
	GraphicsContext* customToolTipGraphicsCtx_;
	Point tooltipLocation_;
	Size tooltipSize_;
	Control* embeddedControl_;
	bool autoDestroyEmbeddedControl_;
	Color backgroundColor_;
};





/**
*ToolTipEventHandler
*handles the following:
*onToolTipRequested
*onToolTip
*/
template <class SOURCE_TYPE>
class ToolTipEventHandler : public EventHandlerInstance<SOURCE_TYPE,ToolTipEvent> {
public:
	ToolTipEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ToolTipEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ToolTipEvent>( source, handlerMethod, handlerName ) {

	}

};


}; //end of namespace VCF


#endif // _VCF_TOOLTIPEVENT_H__

/**
$Id$
*/
