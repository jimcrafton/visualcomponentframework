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

void OSXFileSaveDialog::buildFileTypesMap()
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

bool OSXFileSaveDialog::execute() 
{
	bool result = false;
	fileName_ = "";
	selectedFilter_ = "";
	selectedFileExt_ = "";
			
	
	buildFileTypesMap();
	
	NavDialogCreationOptions saveDlgOptions;
	
	NavGetDefaultDialogCreationOptions (&saveDlgOptions );
	
	NavDialogRef saveDlg;
	CFTextString title;
	title = title_;
	saveDlgOptions.modality = kWindowModalityAppModal;
	saveDlgOptions.windowTitle = title;
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
		
		saveDlgOptions.popupExtension = CFArrayCreate( NULL, 
														(const void**) descriptionArray, 
														filter_.size(), NULL);
	
		
		saveDlgOptions.optionFlags &= ~kNavNoTypePopup;																
	}
	
	if ( filter_.empty() ) {
		saveDlgOptions.optionFlags |= kNavSupportPackages;
	}
	
	
	//Finally!!! Create our goddamn dialog....
	
	OSStatus err = NavCreatePutFileDialog (&saveDlgOptions, 
												kNavGenericSignature,
												kNavGenericSignature,
												OSXFileSaveDialog::saveNavEventProc,
												this,
												&saveDlg);
												
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
					NavCustomControl( saveDlg, kNavCtlSetLocation, (void*)&desc );
				}
			}
		}
	}
	
	//Holy Crap Batman - it's time to run the stupid dialog!!
	
	err = NavDialogRun( saveDlg );
	
	
	//free up the CFStringRefs and the CFArray
	if ( NULL != saveDlgOptions.popupExtension ) {
		CFRelease( saveDlgOptions.popupExtension );
	}
	
	for ( int i=0;i<filter_.size();i++ ) {
		CFRelease( descriptionArray[i] );
	}
	
	delete [] descriptionArray;

	//now check the response
	NavReplyRecord reply;
	err = NavDialogGetReply(saveDlg, &reply);
	if ( err == noErr ) {
		
		CFTextString fileName;
		fileName = NavDialogGetSaveFileName( saveDlg );
		if ( fileName.length() > 0 ) {
			
			long numItems;
			AEKeyword   theKeyword;
			DescType    actualType;
			::Size        actualSize;
			FSRef       theFSRef;
			err = AEGetNthPtr(&(reply.selection), i, typeFSRef, &theKeyword, &actualType,
							  &theFSRef, sizeof(theFSRef), &actualSize);
			
			CFRefObject<CFURLRef> url = CFURLCreateFromFSRef( NULL, &theFSRef );  
			char buf[256];
			if ( CFURLGetFileSystemRepresentation( url, true, (UInt8*)buf, sizeof(buf) ) ) {
				fileName_ = buf;
				if ( fileName_[fileName_.size()-1] != '/' ) {
					fileName_ += "/";
				}
			}
			fileName_ += fileName;
			
			result = !fileName_.empty();
		}
	}
	
	
	NavDialogDispose( saveDlg );
													
	return result;
}

bool OSXFileSaveDialog::matchFileType( NavFileOrFolderInfo* info, FSRef* fileRef )
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


pascal void OSXFileSaveDialog::saveNavEventProc( NavEventCallbackMessage inSelector, NavCBRecPtr ioParams, 
													NavCallBackUserData	ioUserData)
{
	OSXFileSaveDialog* thisPtr = (OSXFileSaveDialog*)ioUserData;
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
			 in the saveDlgOptions.popupExtension. Other code on the internet apparently relies 
			 on this as well, so hopefully this won't change (knock on wood) in the near future.
			 */
			NavMenuItemSpec* menuItemSpec = (NavMenuItemSpec *)ioParams->eventData.eventDataParms.param;
			thisPtr->selectedFileTypeIndex_ = menuItemSpec->menuType;
			FilterPair filt = thisPtr->filter_[thisPtr->selectedFileTypeIndex_];
			thisPtr->selectedFilter_ = filt.second;
			thisPtr->selectedFileExt_ = filt.second;
			int pos =  thisPtr->selectedFileExt_.find( "*" );
			if ( pos != String::npos ) {
				thisPtr->selectedFileExt_.erase( 0, pos+1 );
			}
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
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:31:37  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.1  2004/11/10 06:16:40  ddiego
*started adding osx menu code
*
*
*/
