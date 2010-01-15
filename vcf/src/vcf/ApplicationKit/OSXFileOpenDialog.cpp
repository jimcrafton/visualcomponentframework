/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXFileOpenDialog.h"
#include "vcf/FoundationKit/StringTokenizer.h"



namespace VCF {

OSXFileOpenDialog::OSXFileOpenDialog( Control* owner ) :
	allowsMultiSelect_(false),
	fileMustExist_(false),
	owner_(owner),
	selectedFileTypeIndex_(0)
{
	container_.initContainer( selectedFiles_ );
}

OSXFileOpenDialog::~OSXFileOpenDialog() 
{

}

void OSXFileOpenDialog::setTitle( const String& title ) 
{
	title_ = title;
}
/*
void OSXFileOpenDialog::buildFileTypesMap()
{
	//Can you say "Royal Pain In the Ass"? Yes? I knew you could!
	
	fileTypesFilterMap_.clear();
	
	ICInstance inst;
	ICStart( &inst, 'VCF ' );
	Handle entries = NewHandle(0);
	ICAttr attr;
	OSStatus err = ICFindPrefHandle(inst, "\pMapping", &attr, entries);
	if ( noErr != err ) {
		printf( "ICFindPrefHandle failed! Err: %d", err );
		filter_.clear();
		return;
	}
						
						
	ICMapEntry entry;
	
	std::vector<String> filters;
	
	
	//we are assuming that the filter_ has been populated with the following format:
	//FilterPair.first = a descriptive name for the file mask
	//FilterPair.second = a series of 1 or more masks of the form [*].<extension>
	//multiple masks MUST be separated by a ";" character
	//Example "Foo files", "*.foo;*.bar"
	
	std::vector<FilterPair>::iterator it = filter_.begin();
	while ( it != filter_.end() ) {
		String filt = (*it).second;
		
		//loop through multiple extensions if we have any
		//and remove extraneous "*" chars
		StringTokenizer tok( filt, ";");
		if ( tok.hasMoreElements() ) {
			while ( tok.hasMoreElements() ) {
				String ext = tok.nextElement();
				int pos = ext.find( "*" );
				
				filters.push_back( ext );
			}
		}
		else {
			filters.push_back( filt );
		}
		it ++;
	}
	
	std::vector<String>::iterator it2 = filters.begin();
	while ( it2 != filters.end() ) {
		String ext = *it2;
		int pos = ext.find( "*" );
		if ( pos != String::npos ) {
			ext.erase( pos, 1 );
		}
		
		//convert our Unicode string to a Pascal style string
		Str255 pstrExt;
		CopyCStringToPascal( ext.ansi_c_str(), pstrExt );
		
		//clear out entry
		memset( &entry, 0, sizeof(entry) );
		
		//get entry info for the extension
		
		err = ICMapEntriesFilename( inst, entries, pstrExt, &entry );
		if ( noErr == err ) {
			//add entry to map
			fileTypesFilterMap_[ext] = entry.fileType;
		}
		it2 ++;
	}
	
	DisposeHandle( entries );
	
	ICStop( inst );	
}
*/

bool OSXFileOpenDialog::execute() 
{
	bool result = false;
	
	CFTextString title;
	title = title_;
	
	NSOpenPanel* openPanel = [NSOpenPanel openPanel];
	[openPanel setCanChooseFiles:YES];
	[openPanel setAllowsMultipleSelection: allowsMultiSelect_ ? YES : NO ];
	[openPanel setCanChooseDirectories:NO];
	[openPanel setTitle:title];
	
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
	
	CFTextString dir;
	NSString* dirStr = nil;
	if ( !directory_.empty() ) {		
		dir = directory_;
		dirStr = dir;
	}
	if ( NSOKButton == [openPanel runModalForDirectory:dirStr file:nil types:fileTypes] ) {
		NSArray *filesToOpen = [openPanel filenames];
        int i, count = [filesToOpen count];
        for (i=0; i<count; i++) {
            NSString* aFile = [filesToOpen objectAtIndex:i];
			CFTextString tmp;
			tmp = aFile;
			
            selectedFiles_.push_back( tmp );
        }
	}
	
	if ( !selectedFiles_.empty() ) {
		fileName_ = selectedFiles_.front();
		result = true;
	}	
												
	return result;
}

void OSXFileOpenDialog::addFilter( const String & description, const String & extension ) 
{
	FilterPair entry(description,extension);
	
	std::vector<FilterPair>::iterator found = std::find( filter_.begin(), filter_.end(), entry );
	if ( found == filter_.end() ) {
		filter_.push_back( entry );
	}
}

void OSXFileOpenDialog::setDirectory( const String & directory ) 
{
	directory_ = directory;
}

void OSXFileOpenDialog::setFileName( const String & filename ) 
{
	fileName_ = filename;
}

String OSXFileOpenDialog::getFileName() 
{
	return fileName_;
}

String OSXFileOpenDialog::getDirectory() 
{
	return directory_;
}

String OSXFileOpenDialog::getFileExtension() 
{
	return selectedFileExt_;
}

uint32 OSXFileOpenDialog::getSelectedFileCount() 
{
	return selectedFiles_.size();
}

Enumerator<String>* OSXFileOpenDialog::getSelectedFiles() {
	return container_.getEnumerator();
}

void OSXFileOpenDialog::setAllowsMultiSelect( const bool& allowsMultiSelect ) 
{
	allowsMultiSelect_ = allowsMultiSelect;
}

void OSXFileOpenDialog::setSelectedFilter( const String& selectedFilter ) 
{
	//FilterPair entry(description,extension);
	
	std::vector<FilterPair>::iterator found = filter_.begin();
	while ( found != filter_.end() ) {
	
		found ++;
	}
	
	//selectedFileTypeIndex_
}

void OSXFileOpenDialog::setFileMustExist( const bool& fileMustExist ) 
{

}


}; // namespace VCF


/**
$Id$
*/
