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

bool OSXFileOpenDialog::execute() 
{
	bool result = false;
	selectedFiles_.clear();
	fileName_ = "";
	
	buildFileTypesMap();
	
	NavGetDefaultDialogCreationOptions (&openDlgOptions_ );
	
	NavDialogRef openDlg;
	CFTextString title;
	title = title_;
	openDlgOptions_.modality = kWindowModalityAppModal;
	openDlgOptions_.windowTitle = title;
	CFStringRef* descriptionArray = NULL;
	
	if ( !filter_.empty() ) {
		descriptionArray = new CFStringRef[filter_.size()];
		int index = 0;
		
		//create the CFArray of file filter descriptions!
		std::vector<FilterPair>::iterator it = filter_.begin();
		while ( it != filter_.end() ) {
			String description = (*it).first;
			descriptionArray[index] = CFStringCreateWithCharacters( NULL, description.c_str(), description.size() );
			index ++;
			it ++;
		}
		
		openDlgOptions_.popupExtension = CFArrayCreate( NULL, 
														(const void**) descriptionArray, 
														filter_.size(), NULL);
	
		
		openDlgOptions_.optionFlags &= ~kNavNoTypePopup;																
	}
	
	if ( filter_.empty() ) {
		openDlgOptions_.optionFlags |= kNavSupportPackages;
	}
	
	if ( !allowsMultiSelect_ ) {
		openDlgOptions_.optionFlags ^= kNavAllowMultipleFiles;
	}
	
	//Finally!!! Create our goddamn dialog....
	
	OSStatus err = NavCreateGetFileDialog (&openDlgOptions_, 
												NULL,
												OSXFileOpenDialog::openNavEventProc,
												NULL,
												OSXFileOpenDialog::openFileFilterProc,
												this,
												&openDlg);
												
	if ( noErr != err ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("NavCreateGetFileDialog failed!") );
	}
	
	
	//set the directory
	if ( !directory_.empty() ) {
		CFTextString dir;
		dir = directory_;
		CFRefObject<CFURLRef> url;
		url = (CFURLRef)dir;
		FSRef fsRef;
		if ( CFURLGetFSRef( url, &fsRef ) ) {
			FSSpec fsSpec;
			if ( noErr == FSGetCatalogInfo( &fsRef, kFSCatInfoNone, NULL, NULL, &fsSpec, NULL ) ) {
				AEDesc desc;
				if ( AECreateDesc( typeFSS, &fsSpec, sizeof(FSSpec), &desc ) == noErr ) {
					NavCustomControl( openDlg, kNavCtlSetLocation, (void*)&desc );
				}
			}
		}
	}
	
	//Holy Crap Batman - it's time to run the stupid dialog!!
	
	err = NavDialogRun( openDlg );
	
	
	//free up the CFStringRefs and the CFArray
	if ( NULL != openDlgOptions_.popupExtension ) {
		CFRelease( openDlgOptions_.popupExtension );
	}
	
	for ( int i=0;i<filter_.size();i++ ) {
		CFRelease( descriptionArray[i] );
	}
	
	delete [] descriptionArray;
	
	//now check the response
	NavReplyRecord reply;
	err = NavDialogGetReply(openDlg, &reply);
	if ( err == noErr ) {
		long numItems;
		err = AECountItems((const AEDescList *)&reply.selection, &numItems);
		int i = 1;
		for (i=1;i<=numItems;i++ ) {
			AEKeyword   theKeyword;
			DescType    actualType;
			::Size        actualSize;
			FSRef       theFSRef;
			err = AEGetNthPtr(&(reply.selection), i, typeFSRef, &theKeyword, &actualType,
							  &theFSRef, sizeof(theFSRef), &actualSize);
			
			CFRefObject<CFURLRef> url = CFURLCreateFromFSRef( NULL, &theFSRef );  
			char buf[256];
			String fileName;
			if ( CFURLGetFileSystemRepresentation( url, true, (UInt8*)buf, sizeof(buf) ) ) {
				fileName = buf;
				selectedFiles_.push_back( fileName );
			}
		}
		
	}
	
	NavDialogDispose( openDlg );
	
	if ( !selectedFiles_.empty() ) {
		fileName_ = selectedFiles_.front();
		result = true;
	}
													
	return result;
}

bool OSXFileOpenDialog::matchFileType( NavFileOrFolderInfo* info, FSRef* fileRef )
{
	bool result = false;
	
	if ( filter_.empty() ) {
		return true;
	}
	
	LSItemInfoRecord itemInfo;
	LSCopyItemInfoForRef( fileRef, kLSRequestAllInfo, &itemInfo );
	String ext;
	FilterPair filterEntry = filter_[ selectedFileTypeIndex_ ];
	
		
	
	if ( info->fileAndFolder.fileInfo.finderInfo.fdType != 0 ) {
		std::map<String,OSType>::iterator found = fileTypesFilterMap_.begin();
		while ( found != fileTypesFilterMap_.end() )  {
			//find and match in the filer entry for the extension
			
			if ( filterEntry.second.find( found->first ) != String::npos ) {
				//check the OSType
				if ( found->second == info->fileAndFolder.fileInfo.finderInfo.fdType ) {
					result = true;
				}
				break;
			}
			found ++;
		}
	}
	
	if ( !result ) {
		if ( itemInfo.extension ) {
			CFTextString tmp;
			tmp = itemInfo.extension;
			ext = tmp;
			ext.insert( 0, "." );
		}
		
		if ( !ext.empty() ) {
			if ( filterEntry.second.find( ext ) != String::npos ) {
				OSType type = fileTypesFilterMap_[ext];
				if ( type != 0 ) {
					if ( type == itemInfo.filetype ) {
						result = true;
					} 
				}
				else {
					//no type, so since we are in the filterEntry mask, then assume true!
					result = true;
				}
				
				if ( !result ) {
					//damn STILL no match, well again resort to the fact that
					//our file extension was in our filter mask
					result = true;
				}
			}
		}
	}
	
	
	return result;
}

pascal Boolean OSXFileOpenDialog::openFileFilterProc( AEDesc* theItem, void* info, NavCallBackUserData callBackUD, NavFilterModes filterMode )
{
	Boolean result = true;
	NavFileOrFolderInfo *theInfo = (NavFileOrFolderInfo *)info;
	OSXFileOpenDialog* thisPtr = (OSXFileOpenDialog*)callBackUD;
	VCF_ASSERT( thisPtr != NULL );
	
	if ( !theInfo->isFolder ) {
		if ( theItem->descriptorType == typeFSS ) {			
			FSSpec fileSpec;
			if ( AEGetDescData(theItem, &fileSpec, sizeof(FSSpec)) == noErr ) {
				printf( "WARNING : We don't support getting FSSpec info yet...\n" );
			}
			result = true;			
		}
		else if ( theItem->descriptorType == typeFSRef ) { //OK we have an FSRef type - this we can work with
			FSRef fileRef;
			result = false;
			if ( AEGetDescData(theItem, &fileRef, sizeof(FSRef)) == noErr ) {
				result = thisPtr->matchFileType( theInfo, &fileRef );
			}
		}
	}
	else {
		//it's a folder - return true
		result = true;
	}
	
	return result;	
}

pascal void OSXFileOpenDialog::openNavEventProc( NavEventCallbackMessage inSelector, NavCBRecPtr ioParams, 
													NavCallBackUserData	ioUserData)
{
	OSXFileOpenDialog* thisPtr = (OSXFileOpenDialog*)ioUserData;
	VCF_ASSERT( thisPtr != NULL );
	switch( inSelector ) {
		case kNavCBStart : {
			// Initialize the popup menu
			NavMenuItemSpec menuItem;
			menuItem.version = kNavMenuItemSpecVersion;
			menuItem.menuCreator = 0;
			menuItem.menuType = thisPtr->selectedFileTypeIndex_;
			menuItem.menuItemName[0] = 0;
			OSErr error = NavCustomControl(ioParams->context, kNavCtlSelectCustomType, &menuItem);		
		}
		break;
		
		case kNavCBPopupMenuSelect : {
			/**
			This gets called when the user selects something in the popup menu.
			 It would *appear* (and I put this in quotes because Nav Services is apparently
								kind of buggy on OS X) that the menuType field represents the index of the 
			 array of menu popup names that we pass in to the NavCreateGetFileDialog
			 in the openDlgOptions_.popupExtension. Other code on the internet apparently relies 
			 on this as well, so hopefully this won't change (knock on wood) in the near future.
			 */
			NavMenuItemSpec* menuItemSpec = (NavMenuItemSpec *)ioParams->eventData.eventDataParms.param;
			thisPtr->selectedFileTypeIndex_ = menuItemSpec->menuType;
			FilterPair filt = thisPtr->filter_[thisPtr->selectedFileTypeIndex_];
			thisPtr->selectedFileExt_ = filt.second;
		}
		break;
		
		case kNavCtlGetLocation : {
			AEDesc* desc = (AEDesc *)ioParams->eventData.eventDataParms.param;
			if ( NULL != desc ) {
				if ( desc->descriptorType == typeFSS ) {			
					FSSpec fileSpec;
					if ( AEGetDescData(desc, &fileSpec, sizeof(FSSpec)) == noErr ) {
						FSRef fileRef;
						FSGetCatalogInfo(&fileRef, kFSCatInfoNone, NULL, NULL, &fileSpec, NULL);
						CFRefObject<CFURLRef> url = CFURLCreateFromFSRef(kCFAllocatorDefault, &fileRef);
						if ( NULL != url ) {
							//finally, set our directory_ member
							char buf[256];
							if ( CFURLGetFileSystemRepresentation( url, true, (UInt8*)buf, sizeof(buf) ) ) {
								thisPtr->directory_ = buf;
							}
						}
					}
				}
			}
		}
		break;
	}	
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
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.5  2004/11/10 06:16:40  ddiego
*started adding osx menu code
*
*Revision 1.1.2.4  2004/11/07 19:32:19  marcelloptr
*more documentation
*
*/



