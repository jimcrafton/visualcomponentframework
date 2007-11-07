#ifndef _VCF_OUTPUTREADYEVENT_H__
#define _VCF_OUTPUTREADYEVENT_H__
//OutputReadyEvent.h

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
\class OutputReadyEvent OutputReadyEvent.h "vcf/FoundationKit/OutputReadyEvent.h"
*/
class FOUNDATIONKIT_API OutputReadyEvent : public Event {
public:
	OutputReadyEvent( Object* source, const String& outputData ):
	  Event(source),outputData_(outputData){};


	OutputReadyEvent( const OutputReadyEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	OutputReadyEvent& operator=( const OutputReadyEvent& rhs ) {
		Event::operator =( rhs );
		outputData_ = rhs.outputData_;

		return *this;
	}

	String getOutputData() {
		return outputData_;
	}

	virtual Object* clone( bool deep=false ) const {
		return new OutputReadyEvent(*this);
	}
protected:
	String outputData_;
};

typedef Delegate1<OutputReadyEvent*> OutputReadyDelegate;
typedef OutputReadyDelegate::ProcedureType OutputReadyHandler;

};


#endif // _VCF_OUTPUTREADYEVENT_H__

/**
$Id$
*/
