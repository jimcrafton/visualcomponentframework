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
	browseDlgResult_ = false;
	OSStatus err = NavGetDefaultDialogCreationOptions (&dlgOptions_ );
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("NavGetDefaultDialogCreationOptions failed in OSXFolderBrowseDialog::execute()") );
	}
	CFTextString dlgTitle;
	dlgTitle = title_;
	dlgOptions_.windowTitle = dlgTitle;
	//dlgOptions_.parentWindow = ActiveNonFloatingWindow() ;						
	dlgOptions_.modality = kWindowModalityAppModal;
	
	NavDialogRef browseForFolder;
	err = NavCreateChooseFolderDialog( &dlgOptions_, 
										OSXFolderBrowseDialog::BrowseDlgCallbackProc, 
										NULL,
										this,
										&browseForFolder );
	if ( err != noErr ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("NavCreateChooseFolderDialog failed in OSXFolderBrowseDialog::execute()") );
	}
	
	err = NavDialogRun( browseForFolder );
	if ( noErr != err ) {
		result = false;
	}
	else {
		result = browseDlgResult_;
	}
	NavDialogDispose( browseForFolder );
														
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
	
void OSXFolderBrowseDialog::BrowseDlgCallbackProc( NavEventCallbackMessage callBackSelector, 
													NavCBRecPtr callBackParms, 
													void *callBackUD )
{
	OSXFolderBrowseDialog* thisPtr = (OSXFolderBrowseDialog*)callBackUD;
	VCF_ASSERT( thisPtr != NULL );
	
	VCF_ASSERT(callBackParms != NULL);
            
    if (callBackSelector == kNavCBUserAction) {
    
        NavDialogRef dialog = callBackParms->context;
        
        switch (callBackParms->userAction) {
            case kNavUserActionChoose: {
				NavReplyRecord reply;
				
				AEDescList selection;
				AEKeyword keyword;
				DescType type;
				FSRef folder;
				::Size size;
				long count;
	
                OSStatus err = NavDialogGetReply(dialog, &reply);
                
                selection = reply.selection;
                err = AECountItems(&selection, &count);
				printf( "AECountItems() %d count: %d\n", err, count );
				if ( err == noErr ) {
					err = AEGetNthPtr(&selection, 1, typeFSRef, &keyword, &type, &folder, sizeof(folder), &size);
                	printf( "AEGetNthPtr() %d\n", err );
					
					if ( err == noErr ) {
						CFRefObject<CFURLRef> url = CFURLCreateFromFSRef( NULL, &folder );
						
						char buf[256];
						
						if ( CFURLGetFileSystemRepresentation( url, true, (UInt8*)buf, sizeof(buf) ) ) {
							thisPtr->directory_ = buf;
						}
						else {
							thisPtr->directory_ = OSXUtils::extractStringValueFromCFType( url );						
						}
						printf( "thisPtr->directory_: %s\n", thisPtr->directory_.ansi_c_str() );
						
						 
						
						thisPtr->browseDlgResult_ = true;						
					}								
				}
			}
			break;
                
            case kNavUserActionCancel: {
				thisPtr->browseDlgResult_ = false;
			}
			break;
        }
    }
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
*Revision 1.1.2.1  2004/10/30 20:27:26  ddiego
*added osx color dialog and browse for folder dialog
**
*/



