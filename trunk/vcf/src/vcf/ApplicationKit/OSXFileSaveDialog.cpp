/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXFileSaveDialog.h"
#include "vcf/FoundationKit/StringTokenizer.h"



namespace VCF {

OSXFileSaveDialog::OSXFileSaveDialog( Control* owner ) :
	fileMustExist_(false),
	owner_(owner),
	selectedFileTypeIndex_(0)
{
	
}

OSXFileSaveDialog::~OSXFileSaveDialog() 
{

}

void OSXFileSaveDialog::setTitle( const String& title ) 
{
	title_ = title;
}

bool OSXFileSaveDialog::execute() 
{
	bool result = false;
	
	
	NSSavePanel* savePanel = [NSSavePanel savePanel];
	CFTextString tmp;
	tmp = title_;
	[savePanel setTitle: tmp];
	[savePanel setCanCreateDirectories:NO];
	
	NSMutableArray* fileTypes = [[NSMutableArray alloc] init];	
	std::vector<FilterPair>::iterator it = filter_.begin();
	while ( it != filter_.end() ) {
		String ext;
		String filt = (*it).second;
		
		//loop through multiple extensions if we have any
		//and remove extraneous "*" chars
		StringTokenizer tok( filt, ";");
		if ( tok.hasMoreElements() ) {
			while ( tok.hasMoreElements() ) {
				ext = tok.nextElement();
				size_t pos = ext.find( "*." );
				
				if ( pos != String::npos ) {
					ext = ext.erase( pos, 2 );
				}
				CFTextString tmp(ext);
				[fileTypes addObject: (NSString*) tmp];
			}
		}
		else {
			ext = tok.nextElement();
			size_t pos = ext.find( "*." );
			
			if ( pos != String::npos ) {
				ext = ext.erase( pos, 2 );
			}
			CFTextString tmp(ext);
			[fileTypes addObject: (NSString*) tmp];
		}
		it ++;
	}
	
	[savePanel setAllowedFileTypes:fileTypes];
	
	CFTextString dir;
	NSString* dirStr = nil;
	if ( !directory_.empty() ) {		
		dir = directory_;
		dirStr = dir;
	}
	
	CFTextString file(fileName_);
	
	if ( NSOKButton == [savePanel runModalForDirectory:dirStr file:file ] ) {
		file = [savePanel filename];
		fileName_ = file;
		result = true;
	}			
	return result;
}

void OSXFileSaveDialog::addFilter( const String & description, const String & extension ) 
{
	FilterPair entry(description,extension);
	
	std::vector<FilterPair>::iterator found = std::find( filter_.begin(), filter_.end(), entry );
	if ( found == filter_.end() ) {
		filter_.push_back( entry );
	}
}

void OSXFileSaveDialog::setDirectory( const String & directory ) 
{
	directory_ = directory;
}

void OSXFileSaveDialog::setFileName( const String & filename ) 
{
	fileName_ = filename;
}

String OSXFileSaveDialog::getFileName() 
{
	return fileName_;
}

String OSXFileSaveDialog::getDirectory() 
{
	return directory_;
}

String OSXFileSaveDialog::getFileExtension() 
{
	return selectedFileExt_;
}

uint32 OSXFileSaveDialog::getSelectedFileCount() 
{
	return 0;
}

Enumerator<String>* OSXFileSaveDialog::getSelectedFiles() {
	return NULL;
}

void OSXFileSaveDialog::setAllowsMultiSelect( const bool& allowsMultiSelect ) 
{

}

void OSXFileSaveDialog::setSelectedFilter( const String& selectedFilter ) 
{
	//FilterPair entry(description,extension);
	
	std::vector<FilterPair>::iterator found = filter_.begin();
	while ( found != filter_.end() ) {
	
		found ++;
	}
	
	//selectedFileTypeIndex_
}

void OSXFileSaveDialog::setFileMustExist( const bool& fileMustExist ) 
{

}


};


/**
$Id$
*/
