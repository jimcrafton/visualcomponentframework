//TabModel.cpp

/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TabModel.h"


using namespace VCF;


TabModel::TabModel():
	selectedIndex_(TabModel::NoPageSelected)
{

}

TabModel::~TabModel()
{

}

void TabModel::setSelectedPage( const uint32& index )
{
	if ( selectedIndex_ != index ) {
		selectedIndex_ = index;
		TabModelEvent event(this, index);
		TabPageSelected( &event );
	}
}
