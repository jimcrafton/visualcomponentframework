//OSXProcessPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/OSXProcessPeer.h"
#include <sys/wait.h>


using namespace VCF;

OSXProcessPeer::OSXProcessPeer():
	processTerminated_(false)
{
	memset( &processHandle_, 0, sizeof(processHandle_) );
	memset( &processHandle_.launchBlock, 0, sizeof(processHandle_.launchBlock) );
}

OSXProcessPeer::~OSXProcessPeer()
{

}


int OSXProcessPeer::getProcessThreadID()
{
	return 0;
}

bool OSXProcessPeer::createProcess( const String& processName, const String& arguments )
{
	bool result = false;
	processTerminated_ = false;

	memset( &processHandle_, 0, sizeof(processHandle_) );
	memset( &processHandle_.launchBlock, 0, sizeof(processHandle_.launchBlock) );
	processHandle_.pid = 0;
	
	CFTextString pName(processName);
	CFRefObject<CFURLRef> url = (CFURLRef)pName;
	
	LSItemInfoRecord itemInfo;
	
	String tmp = processName;
	tmp += " " + arguments;
	
	CommandLine cmdLine;
	cmdLine.splitLine( tmp );
	
	const std::vector<String>& args = cmdLine.getOriginalCommandLine();
	
	CFRefObject<CFURLRef> docURL = NULL;
	
	if ( args.size() > 1 ) {		
		CFTextString docName(args[1]);
		docURL = (CFURLRef)docName;
	}
	
	//is this app a Bundle based (OSX) app, or a unix app (default)?
	processHandle_.isUnixProcess = true;
	if ( LSCopyItemInfoForURL( url, kLSRequestAllInfo, &itemInfo ) == noErr ) {
		if ( (itemInfo.flags & kLSItemInfoIsApplication) ) {
			processHandle_.isUnixProcess = false;
		}
	}
	
	if ( !processHandle_.isUnixProcess ) {
		//use LaunchApplication
		FSRef fsRef;
		if ( CFURLGetFSRef( url, &fsRef ) ) {
			FSSpec    fsSpec;
			if ( noErr == FSGetCatalogInfo( &fsRef, kFSCatInfoNone, NULL, NULL, &fsSpec, NULL ) ) {
				FSSpec    doc_fsSpec;
				FSRef doc_fsRef;
				if ( docURL != NULL ) {
					
					if ( !CFURLGetFSRef( docURL, &doc_fsRef ) ) {
						return -1;
					}
					
					if ( noErr != FSGetCatalogInfo( &doc_fsRef, kFSCatInfoNone, NULL, NULL, &doc_fsSpec, NULL ) ) {
						return -1;
					}
				}
				
				
				static const EventTypeSpec events[] ={
												{ kEventClassApplication, kEventAppTerminated }
											};
											

				//install event handler for appl close!
				InstallApplicationEventHandler(OSXProcessPeer::osxProcessTerminated, 
												sizeof(events) / sizeof(EventTypeSpec), 
												events, this, NULL);

				
				
				/**
				AE vars
				*/
				AEAddressDesc appAddr;
				AEDescList fileList;
				AEDesc fileListElt, paraDesc;
				AppleEvent theEvent;
				AppleEvent eventReply;
				Size paraSize;
				AppParametersPtr paraData;
				
				if ( docURL != NULL ) {
					CFDataRef theData;
					theData = CFURLCreateData(nil, docURL, kCFStringEncodingUTF8, true);
					
					
					
					AECreateDesc(typeNull, NULL, 0, &appAddr);
					AECreateDesc(typeNull, NULL, 0, &fileList);
					AECreateDesc(typeNull, NULL, 0, &fileListElt);
					AECreateDesc(typeNull, NULL, 0, &theEvent);
					AECreateDesc(typeNull, NULL, 0, &eventReply);
					AECreateDesc(typeNull, NULL, 0, &paraDesc);
					
					/* create an open documents Apple Event */
					OSStatus err = AECreateDesc(typeApplSignature,	(Ptr)&itemInfo.creator, 
												sizeof(OSType), &appAddr);
					
					//create the event!
					err = AECreateAppleEvent(kCoreEventClass, kAEOpenDocuments,
											 &appAddr, kAutoGenerateReturnID, 
											 kAnyTransactionID, &theEvent);
					
					//create a single list
					err = AECreateList(NULL, 0, false, &fileList);			
					
					////create one element for the doc file name
					//err = AECreateDesc('furl', CFDataGetBytePtr(theData),CFDataGetLength(theData), &fileListElt);
					
					//CFRelease(theData);
					
					err = AECreateDesc(typeFSRef, (Ptr) (&doc_fsRef),  sizeof(FSRef), &fileListElt);
					
					err = AEPutDesc(&fileList, 0, &fileListElt);
					
					err = AEPutParamDesc(&theEvent, keyDirectObject, &fileList);
					
					
					//send the open doc event
					err = AESend(&theEvent, &eventReply, kAENoReply,kAENormalPriority, kNoTimeOut, NULL, NULL);
					
					
					/* ask the Apple Event Manager to coerce the Apple
						event into a launch application parameter block
						record. */
					err = AECoerceDesc(&theEvent, typeAppParameters,
									   &paraDesc);
					
					paraSize = AEGetDescDataSize(&paraDesc);
					paraData = (AppParametersPtr) NewPtr(paraSize);
					err = AEGetDescData(&paraDesc, paraData, paraSize );
				}
				else {
					paraData = NULL;
				}
				
		
				
				
				processHandle_.launchBlock.launchBlockID = extendedBlock;
				processHandle_.launchBlock.launchEPBLength = extendedBlockLen;
				processHandle_.launchBlock.launchFileFlags = 0;
				processHandle_.launchBlock.launchControlFlags = launchNoFileFlags | launchContinue | launchDontSwitch;
				processHandle_.launchBlock.launchAppSpec = &fsSpec;
				processHandle_.launchBlock.launchAppParameters = paraData;				
				LaunchApplication( &processHandle_.launchBlock );
				
				pid_t pid = 0;
				if ( noErr == GetProcessPID( &processHandle_.launchBlock.launchProcessSN, &pid ) ) {
					processHandle_.pid = pid;								
				}
				
				
				if (paraData != NULL) DisposePtr((Ptr) paraData);
				
				if ( docURL != NULL ) {
					AEDisposeDesc(&paraDesc);
					AEDisposeDesc(&appAddr);
					AEDisposeDesc(&fileListElt);
					AEDisposeDesc(&fileList);
					AEDisposeDesc(&theEvent);
					AEDisposeDesc(&eventReply);
				}
				/*
				EventRef theRecvdEvent;				
				while  (ReceiveNextEvent(0, NULL,kEventDurationForever,true,
										 
										 &theRecvdEvent)== noErr)
					
				{	
					SendEventToEventTarget (theRecvdEvent, GetEventDispatcherTarget());
					
					ReleaseEvent(theRecvdEvent);
					if ( processQuit ) {
						printf( "Process quit!\n" );
						break;
					}
				}
				*/
				
				//printf("Launch done!\n") ;
			}
		}
	}
	else {
		//use unix style
		int pid = 0;
		
		char** unixArgs = new char*[args.size()];
		for (size_t i=0;i<args.size();i++ ) {
			AnsiString s = args[i];
			char* arg = new char[s.size()+1];
			s.copy( arg, s.size() );
			arg[s.size()] = 0;
			unixArgs[i] = arg;
		}
		
		//fork child process		
		pid = fork();
		if ( pid < 0 ) {
			printf( "fork failed!!\n");			
		}		
		
		
		//child executes the code
		if (pid == 0) {
			execvp(unixArgs[0], unixArgs);			
			exit(1);
		}
		
		processHandle_.pid = pid;
		
		//clean up args
		for (size_t i=0;i<args.size();i++ ) {			
			delete [] unixArgs[i];
		}
		delete [] unixArgs;
		
		//block and spin - not very efficient???
		//while (wait(&waitStatus) != pid); 		
	}

	return result;
}

String OSXProcessPeer::getProcessFileName()
{
	return processFileName_;
}


ulong32 OSXProcessPeer::terminate()
{
	if ( processHandle_.isUnixProcess ) {
		kill( processHandle_.pid, SIGKILL );
	}
	else {
		AEAddressDesc appPSN;
		AppleEvent quitEvent;	
		
		OSStatus err = AECreateDesc(typeProcessSerialNumber,
									(Ptr)&processHandle_.launchBlock.launchProcessSN, 
									sizeof(processHandle_.launchBlock.launchProcessSN), 
									&appPSN);
		
		//create the event!
		err = AECreateAppleEvent(kCoreEventClass, kAEQuitApplication ,
								 &appPSN, kAutoGenerateReturnID, 
								 kAnyTransactionID, &quitEvent);
		
		
		
		//send the open doc event
		err = AESend(&quitEvent, NULL, kAENoReply,kAENormalPriority, kNoTimeOut, NULL, NULL);
		
		AEDisposeDesc(&appPSN);
		AEDisposeDesc(&quitEvent);
	}
    return 0;
}


Waitable::WaitResult OSXProcessPeer::wait( uint32 milliseconds )
{
	Waitable::WaitResult result = Waitable::wrWaitFinished;
	
	return result;
}

Waitable::WaitResult OSXProcessPeer::wait()
{
	Waitable::WaitResult result = Waitable::wrWaitFinished;
	
	//the following is probably wrong, we need another solution???
	if ( processHandle_.isUnixProcess ) {
	}
	else {		
		EventRef theRecvdEvent;				
		while  (ReceiveNextEvent(0, NULL,kEventDurationForever,true,
								 
								 &theRecvdEvent)== noErr)
			
		{	
			
			SendEventToEventTarget (theRecvdEvent, GetEventDispatcherTarget());
			
			ProcessSerialNumber psn = {0};
			OSStatus err = GetEventParameter( theRecvdEvent,
                                        kEventParamProcessID,
                                        typeProcessSerialNumber,
                                        NULL,
                                        sizeof(psn),
                                        NULL,
                                        &psn );
			
			ReleaseEvent(theRecvdEvent);
			if ( processTerminated_ && (psn.highLongOfPSN == processHandle_.launchBlock.launchProcessSN.highLongOfPSN) &&
					(psn.lowLongOfPSN == processHandle_.launchBlock.launchProcessSN.lowLongOfPSN) ) {
				printf( "Process quit!\n" );
				break;
			}
		}
	}
	
	return result;
}

OSStatus OSXProcessPeer::osxProcessTerminated( EventHandlerCallRef inHandlerCallRef, EventRef inEvent, void * inUserData )
{
	OSXProcessPeer* thisPtr = (OSXProcessPeer*)inUserData;
	thisPtr->processTerminated_ = true;
	
	return noErr;
}


/**
*CVS Log info
 *$Log$
 *Revision 1.4  2006/04/07 02:35:34  ddiego
 *initial checkin of merge from 0.6.9 dev branch.
 *
 *Revision 1.3.4.3  2006/01/14 21:49:21  ddiego
 *general osx checkin
 *
 *Revision 1.3.4.2  2005/11/27 23:55:45  ddiego
 *more osx updates.
 *
 *Revision 1.3.4.1  2005/11/10 02:02:38  ddiego
 *updated the osx build so that it
 *compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
 *
 *Revision 1.3  2004/12/01 04:31:41  ddiego
 *merged over devmain-0-6-6 code. Marcello did a kick ass job
 *of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
 *that he found. Many, many thanks for this Marcello.
 *
 *Revision 1.2.2.1  2004/10/10 20:42:08  ddiego
 *osx updates
 *
 *Revision 1.2  2004/08/07 02:49:14  ddiego
 *merged in the devmain-0-6-5 branch to stable
 *
 *Revision 1.1.2.6  2004/06/06 07:05:32  marcelloptr
 *changed macros, text reformatting, copyright sections
 *
 *Revision 1.1.2.4  2004/05/03 03:44:53  ddiego
 *This checks in a bunch of changes to the FoundationKit for OSX
 *porting. The thread, mutex, semaphor, condition, and file peers
 *have all been implemented and tested. The file peer could be improved
 *and needs search functionality. The locale peer is only partially
 *complete, but the functions will return values. The unicode transition
 *is also finished and works OK now.
 *
 *Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
 *added OSX changes for unicode migration
 *
 *Revision 1.4  2004/04/03 15:48:47  ddiego
 *Merged over code from the 0-6-3 branch.
 *
 *Revision 1.3.2.1  2004/02/21 03:27:09  ddiego
 *updates for OSX porting
 *
 *Revision 1.2  2003/08/09 02:56:46  ddiego
 *merge over from the devmain-0-6-1 branch
 *Changes
 *Features:
 *-Added additional implementation to better support the MVC architecture in
 *the VCF
 *
 *-Added a Document/View architecure that is similar to MFC's or NextSteps's
 *Doc/View architectures
 *
 *-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
 *now basic support for it in terms of drawing vector shapes
 *(fills and strokes). Image support will come in the next release
 *
 *-Added several documented graphics tutorials
 *
 *Bugfixes:
 *
 *[ 775744 ] wrong buttons on a dialog
 *[ 585239 ] Painting weirdness in a modal dialog ?
 *[ 585238 ] Modal dialog which makes a modal Dialog
 *[ 509004 ] Opening a modal Dialog causes flicker
 *[ 524878 ] onDropped not called for MLTcontrol
 *
 *Plus an issue with some focus and getting the right popup window to activate
 *has also been fixed
 *
 *Revision 1.1.2.2  2003/06/23 23:16:55  ddiego
 *added some furtther implementation for the osx port
 *
 *Revision 1.1.2.1  2003/05/22 04:40:05  ddiego
 *removed the .cpp files in favor of .mm files to allow Objective-C++ compiling
 *
 *Revision 1.2  2003/05/17 20:37:34  ddiego
 *this is the checkin for the 0.6.1 release - represents the merge over from
 *the devmain-0-6-0 branch plus a few minor bug fixes
 *
 *Revision 1.1.2.1  2003/05/15 03:01:03  ddiego
 *added initial osx source( FoundationKit only),
 *plus some fixes to compile under GCC 3.x compilers
 *
 */


