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
class Control;

#define TOOLTIP_EVENT_TIP_REQESTED		CUSTOM_EVENT_TYPES + 3000



/**
\class ToolTipEvent ToolTipEvent.h "vcf/ApplicationKit/ToolTipEvent.h" 
The tooltip event is fired when tooltip text is being requested and/or 
just before the tooltip is ready to be shown, allowing the 
handler to customize the tooltip's data or presentation.
*/
class APPLICATIONKIT_API ToolTipEvent : public Event {
public:
	ToolTipEvent( Object* source, const uint32& type ):
	  Event( source, type ),		  
		  embeddedControl(NULL),
			autoDestroyEmbeddedControl(true){		  
		  tooltipLocation.x_ = 0.0;
		  tooltipLocation.y_ = 0.0;
		  
		  tooltipSize.height_ = 0.0;
		  tooltipSize.width_ = 0.0;
		  
		  tooltipString = "";

		  backgroundColor = *GraphicsToolkit::getSystemColor( SYSCOLOR_TOOLTIP );
	}

	ToolTipEvent( const ToolTipEvent& rhs ):Event(rhs),
		embeddedControl(NULL),autoDestroyEmbeddedControl(true) {
		*this = rhs;
	}

	virtual ~ToolTipEvent(){};


	ToolTipEvent& operator=( const ToolTipEvent& rhs ) {
		Event::operator =( rhs );

		tooltipString = rhs.tooltipString;
		tooltipLocation = rhs.tooltipLocation;
		tooltipSize = rhs.tooltipSize;
		embeddedControl = rhs.embeddedControl;
		autoDestroyEmbeddedControl = rhs.autoDestroyEmbeddedControl;
		backgroundColor = rhs.backgroundColor;

		return *this;
	}

	virtual Object* clone( bool deep=false ) {
		return new ToolTipEvent(*this);
	}

	
	String tooltipString;	
	Point tooltipLocation;
	Size tooltipSize;
	Control* embeddedControl;
	bool autoDestroyEmbeddedControl;
	Color backgroundColor;
};





/**
*ToolTipEventHandler
*handles the following:
\li onToolTipRequested
\li onToolTip
*/
typedef Delegate1<ToolTipEvent*> ToolTipDelegate; 
typedef ToolTipDelegate::ProcedureType ToolTipHandler;

}; //end of namespace VCF


#endif // _VCF_TOOLTIPEVENT_H__

/**
$Id$
*/
