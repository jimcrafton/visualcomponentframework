/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXFolderBrowseDialog.h"


namespace VCF {


OSXFolderBrowseDialog::OSXFolderBrowseDialog(Control* owner):
	browseDlgResult_(false)
{
	
}

OSXFolderBrowseDialog::~OSXFolderBrowseDialog()
{

}

void OSXFolderBrowseDialog::setTitle( const String& title )
{
	title_ = title;
}

bool OSXFolderBrowseDialog::execute()
{
	bool result = false;
	
	NSOpenPanel* openPanel = [NSOpenPanel openPanel];
	[openPanel setCanChooseFiles:NO];
	[openPanel setAllowsMultipleSelection: NO ];
	[openPanel setCanChooseDirectories:YES];
	CFTextString title(title_);
	[openPanel setTitle:title];
	
	CFTextString dir;
	NSString* dirStr = nil;
	if ( !directory_.empty() ) {		
		dir = directory_;
		dirStr = dir;
	}
	
	if ( NSOKButton == [openPanel runModalForDirectory:dirStr file:nil types:nil] ) {
		dir = [openPanel directory];
		directory_ = dir;
		result = true;
	}
																		
	return result;
}

void OSXFolderBrowseDialog::setDirectory( const String & directory )
{
	directory_ = directory;
}

String OSXFolderBrowseDialog::getDirectory()
{
	return directory_;
}
	

};


/**
$Id$
*/
