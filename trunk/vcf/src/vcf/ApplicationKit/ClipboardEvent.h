#ifndef _VCF_CLIPBOARDEVENT_H__
#define _VCF_CLIPBOARDEVENT_H__
//ClipboardEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

#define CLIPBOARD_EVENT_ITEM_ADDED			CUSTOM_EVENT_TYPES + 200
#define CLIPBOARD_EVENT_ITEM_DELETED		CUSTOM_EVENT_TYPES + 201


/**
\class ClipboardEvent ClipboardEvent.h "vcf/ApplicationKit/ClipboardEvent.h"
*A ClipboardEvent is fired during changes ot the system clipboard.
*These chnages may include copying or pasting data to the clipboard.
*/
class APPLICATIONKIT_API ClipboardEvent : public Event{
public:

	ClipboardEvent( Object * source): Event(source){}

	virtual ~ClipboardEvent() {}

	virtual Object* clone( bool deep=false ) {
		return new ClipboardEvent(*this);
	}
};



typedef VCF::Delegate1<ClipboardEvent*> ClipboardDelegate;
typedef ClipboardDelegate::ProcedureType ClipboardHandler;
};


#endif // _VCF_CLIPBOARDEVENT_H__

/**
$Id$
*/
