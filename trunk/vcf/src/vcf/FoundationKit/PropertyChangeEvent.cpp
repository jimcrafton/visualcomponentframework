//PropertyChangeEvent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


PropertyChangeEvent::PropertyChangeEvent( Object * source, VariantData* changeValue, VariantData* originalValue ):
	Event( source )
{
	this->changeValue_ = changeValue;
	this->originalValue_ = originalValue;
}

PropertyChangeEvent::~PropertyChangeEvent()
{

}

VariantData* PropertyChangeEvent::getChangeValue()
{
	return this->changeValue_;
}

VariantData* PropertyChangeEvent::getOriginalValue()
{
	return this->originalValue_;
}


/**
$Id$
*/
