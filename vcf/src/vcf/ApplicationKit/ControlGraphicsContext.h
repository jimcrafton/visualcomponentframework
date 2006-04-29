#ifndef _VCF_CONTROLGRAPHICSCONTEXT_H__
#define _VCF_CONTROLGRAPHICSCONTEXT_H__
//ControlGraphicsContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Control;

/**
\class ControlGraphicsContext ControlGraphicsContext.h "vcf/ApplicationKit/ControlGraphicsContext.h"
*the Graphics Context associated to a control.
* The control owns this same Graphics Context as this
* Graphics context belongs to it.
*@see GraphicsContext
*@see Win32ControlContext, for an example of a how it is used.
*/
class APPLICATIONKIT_API ControlGraphicsContext : public GraphicsContext {

public:
	/**
	*Creates a context based on the component. The context is attached to the component
	*for the duration of it's lifetime.
	*/
	ControlGraphicsContext( Control* control );

	virtual ~ControlGraphicsContext();

	void init();

	/**
	*returns the Control the Graphics context belongs to.
	* This is almost always a heavweight component.
	* If the context was created from scratch (in other words,
	* not as the result of a component being created), then it 
	* will return NULL as it is not associated to any control.
	*@return Control* the component that owns this context 
	* or NULL for memory contexts.
	*/
	Control* getOwningControl(){
		return 	owningControl_;
	};

	void setOwningControl( Control* owningComponent );

private:
	/**
	*the Control the Graphics context belongs to.
	*/
	Control* owningControl_;
};


}; // namespace VCF


#endif // _VCF_CONTROLGRAPHICSCONTEXT_H__

/**
$Id$
*/
